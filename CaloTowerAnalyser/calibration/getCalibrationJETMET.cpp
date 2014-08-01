// M
// Modified by Adam Elwood Mar 2014
// Line 900 changed the conditions for failed fits, checks for errors
// as well.
//
// Changed the type of error plotted from RMS to error on fit
//
// Line 1452 bodged it to ignor the irrelevant hists
// 
// Tentative change L330, appears not to seg fault so far ...
//

#include <TFile.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TH3.h>
#include <TProfile.h>
#include <TEfficiency.h>
#include "TGraphErrors.h"
#include <TGraphAsymmErrors.h>
#include <TStyle.h>
#include <TROOT.h>
#include <TKey.h>
#include <TCanvas.h>
#include <TPaveStats.h>
#include <THStack.h>
#include <TLegend.h>
#include <TMath.h>
#include <TLatex.h>
#include <stdlib.h>

#include <map>
#include <set>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>


// #include <string>
// #include <sys/types.h>
// #include <sys/stat.h>
/*

TODO: MAKE THIS A LIST OF VECTORS TO RUN OVER
WILL ENABLE PU-PU COMPARISONS!!! AND REDUCE WAITING TIMES BETWEEN PROCESSING PLOTS

*/


// ****************************************************************************************************
// <JetMET stuff>

/// default fit with gaussian in niter iteration of mean 
void fit_gaussian(TH1D*& hrsp,
    const double nsigma,
    const double fitMin,
    const int niter);

void adjust_fitrange(TH1* h,double& min,double& max);

  template <class T> 
bool from_string(T& t, 
    const std::string& s, 
    std::ios_base& (*f)(std::ios_base&)) 
{ 
  std::istringstream iss(s); 
  return !(iss >> f >> t).fail();
}



// </JetMET stuff>
// ****************************************************************************************************


//


// Switch on whether to fit the L1 pt vs inverse response curve
//#define FITTING




double CrystalBall(double* x, double* par){
  //http://en.wikipedia.org/wiki/Crystal_Ball_function
  double xcur = x[0];
  double alpha = par[0];
  double n = par[1];
  double mu = par[2];
  double sigma = par[3];
  double N = par[4];
  TF1* exp = new TF1("exp","exp(x)",1e-20,1e20);
  double A; double B;
  if (alpha < 0){
    A = pow((n/(-1*alpha)),n)*exp->Eval((-1)*alpha*alpha/2);
    B = n/(-1*alpha) + alpha;}
  else {
    A = pow((n/alpha),n)*exp->Eval((-1)*alpha*alpha/2);
    B = n/alpha - alpha;}
    double f;
    if ((xcur-mu)/sigma > (-1)*alpha)
      f = N*exp->Eval((-1)*(xcur-mu)*(xcur-mu)/
          (2*sigma*sigma));
    else
      f = N*A*pow((B- (xcur-mu)/sigma),(-1*n));
    delete exp;
    return f;
}




// Structure for containing calibration data from fits
struct calibData{

  calibData(int _iEta, std::vector<double> _p):iEta(_iEta), p(_p){}

  int iEta;                // iEta bin
  std::vector<double> p;   // polynomial value, index = order

};


// Print debugging messages                                                                                                                                    
//#define VERBOSE 

// Print histograms
#define PRINT_HIST


#ifdef VERBOSE
#    define PRINT(outputStr) std::cout << "\n************************************************************\n" << "Making: " << (outputStr) << "\n" << "************************************************************\n\n";
#    define SUBPRINT(outputStr) std::cout << "\t" << outputStr << "\n";
#    define QUIT(outputStr) std::cout << "\n\n\n" << outputStr << "\n\n\n"; exit(0);
#else
#    define PRINT(outputStr)
#    define SUBPRINT(outputStr)
#    define QUIT(outputStr)
#endif


using namespace std;


TString calibLUTFile = "etaPtCalibrationLUT.txt";
TString calibFitFile = "etaPtCalibrationFit.txt";

// Minimum and maximum jet pT (GeV) fit range
double xMin   = 25;
double xMax   = 300;
// The OffPT_vs_L1PT fitting function
TF1 *fitOffPT_vs_L1PT = new TF1("fitOffPT_vs_L1PT", "pol2", xMin, xMax);
// Extract the number of fit parameters


// pT step in scanning fit to jet pT
double ptStep = 5;



//======================
// Output options
//=======================


//TString filename = "/afs/cern.ch/work/m/mcitron/public/QCD/140622/qcd_output.root";
TString filename = "qcd_jetTree_newAreas.root";


// Directory inside ROOT file
//   TString ROOTdir  = "analyzer/";
TString ROOTdir  = "";
// Directory to store plots
//  TString plotDirectory = "plots/Mk1Release/Presentation/8x8_PreFix/";
int nEtaBins=8;
bool doChi2=false;
double setPtBin=2;
double setPtMin=0;
double setPtMax=600;
TString plotDirectory = "qcd_0to600b2_";



//========================
// Function prototypes
//========================

std::vector <TString> splitString(TString inputStr, TString splitChar);
Bool_t objectExists(TFile* file,  TString directory, TString objectName);


// Returns a vector [ntuplePath, objectName]
std::vector < std::pair <TString, TString> > getROOTobjects(TFile* f, TString rootDir, TString objectType);
std::vector < std::pair <TString, TString> > getROOTDirs(TFile* f, TString rootDir);


Bool_t map1DKeyExists(std::map <TString,TH1*> hist1D, TString histogram){
  /*  std::map <TString,TH1*>::const_iterator it = hist1D.find(histogram);
      return it! = hist1D.end();
      */
  return !(hist1D.find(histogram) == hist1D.end());
}

// Directory functions
Bool_t dirExists(TString dir);
void makeFullDir(TString baseDir, TString dir);
void makeDirectory(TString& directoryName);







//===================================================================
// Main function
//===================================================================


int getCalibration(){


  // Enable batch mode
  gROOT->SetBatch(kTRUE);


  unsigned int nParams = fitOffPT_vs_L1PT->GetNpar();

  // Create the directory in which to store the plots
  makeDirectory(plotDirectory);

  // list of histogram names in ROOT file with their corresponding directory structure
  std::vector < std::pair <TString, TString> > fileHistPair;

  // storage containers for histograms of various dimensions and their storage directory
  std::map <TString,TH1*> histogram1D;
  std::map <TString,TH2*> histogram2D;
  std::map <TString,TProfile*> histogramProf;
  std::map <TString,TString>   histogramDirectory;

  //Make new file for Chi2
  TFile* chi2File = new TFile(plotDirectory+"Chi2Fits.root","RECREATE");

  // temporary name of filepath and histogram
  TString filepath, filepathRaw, histogramName, histogramNameRaw;


  //================================================================
  // Automatically extract the histogram names from ROOT file and 
  // store them in maps
  //================================================================


  // open filestream
  TFile* f = new TFile(filename, "OPEN");

  // Check file exists
  if ( f->IsZombie() ) {
    std::cout << "\nERROR: File '" << filename << "' does not exist\n\n";
    exit(-1);
  }




  // Get a list of the main directories in the ROOT file
  std::vector < std::pair <TString, TString> > directories = getROOTobjects(f, ROOTdir, "TDirectoryFile");


  // Loop through all the directories
  for (uint iDir = 0; iDir < directories.size(); ++iDir){

    // Get current main directory
    ROOTdir = directories[iDir].second;
    std::cout << "Analysing the directory: " << ROOTdir << "\n\n\n";


    // *****************************************************************************************************************************
    // *                                                            TH2                                                            *
    // *****************************************************************************************************************************

    //=========================
    // 2D Histograms
    //=========================
    SUBPRINT("2D Histograms")
      // get list of histograms in file
      fileHistPair = getROOTobjects(f, ROOTdir, "TH2");


    // Subdirectories to run calibrations over
    std::vector<TString> subDirs;

    // ak5PUSRaw vs ak5PUS

    //subDirs.push_back( "s0_donut" );
    //subDirs.push_back( "s0_global" );
    //subDirs.push_back( "s0_nopus" );
    //subDirs.push_back( "s0_chunky" );
    //subDirs.push_back( "s0_tsup1" );
    //subDirs.push_back( "s0_tsup2" );
    //subDirs.push_back( "s0_tsup3" );
    //subDirs.push_back( "s5_donut" );
    //subDirs.push_back( "s5_global" );
    //subDirs.push_back( "s5_nopus" );
    subDirs.push_back( "s5_chunky" );
    subDirs.push_back( "s5_tsup1" );
    subDirs.push_back( "s5_tsup2" );
    subDirs.push_back( "s5_tsup3" );
    subDirs.push_back( "c10_donut" );
    subDirs.push_back( "c10_global" );
    subDirs.push_back( "c10_nopus" );
    subDirs.push_back( "c10_chunky" );
    subDirs.push_back( "c10_tsup1" );
    subDirs.push_back( "c10_tsup2" );
    subDirs.push_back( "c10_tsup3" );


    std::map <TString, TString> typeLabel;
    //typeLabel[ "s0_donut" ] = "s0_donut_4Jets";
    //typeLabel[ "s0_global" ] = "s0_global_4Jets";
    //typeLabel[ "s0_nopus" ] = "s0_nopus_4Jets";
    //typeLabel[ "s0_chunky" ] = "s0_chunky_4Jets";
    //typeLabel[ "s0_tsup1" ] = "s0_tsup1_4Jets";
    //typeLabel[ "s0_tsup2" ] = "s0_tsup2_4Jets";
    //typeLabel[ "s0_tsup3" ] = "s0_tsup3_4Jets";
    //typeLabel[ "s5_donut" ] = "s5_donut_4Jets";
    //typeLabel[ "s5_global" ] = "s5_global_4Jets";
    //typeLabel[ "s5_nopus" ] = "s5_nopus_4Jets";
    typeLabel[ "s5_chunky" ] = "s5_chunky_4Jets";
    typeLabel[ "s5_tsup1" ] = "s5_tsup1_4Jets";
    typeLabel[ "s5_tsup2" ] = "s5_tsup2_4Jets";
    typeLabel[ "s5_tsup3" ] = "s5_tsup3_4Jets";
    typeLabel[ "c10_donut" ] = "c10_donut_4Jets";
    typeLabel[ "c10_global" ] = "c10_global_4Jets";
    typeLabel[ "c10_nopus" ] = "c10_nopus_4Jets";
    typeLabel[ "c10_chunky" ] = "c10_chunky_4Jets";
    typeLabel[ "c10_tsup1" ] = "c10_tsup1_4Jets";
    typeLabel[ "c10_tsup2" ] = "c10_tsup2_4Jets";
    typeLabel[ "c10_tsup3" ] = "c10_tsup3_4Jets";


     //Check labels are defined for each sample analysed
    for (uint iSub = 0; iSub < subDirs.size(); ++iSub ){

      // Check a label exists for the current subdir
      TString subDir = subDirs[ iSub ];
      std::map<TString, TString>::iterator labelIt = typeLabel.find( subDir );
      if ( labelIt == typeLabel.end() ){
        std::cout << "ERROR: No label was defined for subdir '" << subDir << "'\n\n"; 
        exit(1);
      }

    }


    // eta binning, key = lowerBin, value = binning range string. Used to obtain an eta ordered list of etabins
    std::map< double, TString > etaBins;

    std::cout << "Got here 1\n";
    for ( unsigned int iSub = 0; iSub < subDirs.size(); ++iSub ){

      // Get the current subdirectory to process
      TString curSubDir = subDirs[iSub];
      TH2D* responseChi2;
      TH2D* ptChi2;
      if(doChi2){
        responseChi2 = new TH2D(typeLabel[subDirs[iSub]]+"responseChi2","Chi2 for the response fits",int((setPtMax-setPtMin)/setPtBin),setPtMin,setPtMax,nEtaBins,0.,nEtaBins);
        ptChi2 = new TH2D(typeLabel[subDirs[iSub]]+"ptChi2","Chi2 for the pt correlation fits",int((setPtMax-setPtMin)/setPtBin),setPtMin,setPtMax,nEtaBins,0.,nEtaBins);
      }
      for (unsigned int i = 0;i < fileHistPair.size(); i++){

        // Extract the directory and name of the histogram
        filepathRaw      = fileHistPair[i].first;
        histogramNameRaw = fileHistPair[i].second;

        // pdf compatible filenames
        // TENATATIVELY CHANGE THIS, APPEARS TO STILL WORK
        histogramName    = typeLabel[subDirs[iSub]]+histogramNameRaw;
        //
        filepath         = filepathRaw;

        // Find the directory with the calibration plots, currently e.g. : /JetHist/Calibration/Calibration_PrePUS_akPUS/iEtaBinned/iEta_-28to-25
        //if (filepath.Contains("calibration") != 0){
        // Only load the EtaBinned distributions
        //if (filepath.Contains("EtaBinned") != 0)
        //	  if (filepath.Contains("iEtaBinned") != 0)

        std::cout << filepath.Data() << '\t' << curSubDir.Data() << std::endl;
        // Restrict to current subdirectory
        if ( filepath.Contains( curSubDir ) != 0 ){
          // TEMPORARY TO SPEED UP DEVELOPMENT RESTRICT TO RELEVENT COLLECTIONS
          //	if ( (filepath.Contains("_PrePUS_") != 0) || (filepath.Contains("_PUS_") != 0) || (filepath.Contains("_LPUS_") != 0) )
          // Do not load NVTX binned distributions
          //if (filepath.Contains("NVTXBinned") == 0)

            //std::cout << "Got here 2a\n";

          // Restrict to calibration plots
          if ( ( histogramName.Contains("ratio") != 0 ) || ( histogramName.Contains("corr") != 0 ) ) {

            histogramName.ReplaceAll("(","{").ReplaceAll(")","}"); // Replace brackets to allow pdf printing
            filepath.ReplaceAll("(","{").ReplaceAll(")","}");

            //	      std::cout << "NEW = " << filepath << "\t" << histogramName << "\n";

            // store histogram and its storage directory
            histogram2D[ histogramName ]        = (TH2*)f->Get(filepathRaw + "/" + histogramNameRaw)->Clone();
            histogramDirectory[ histogramName ] = filepath;

            // Ensure a directory is created to store the histogram
            makeFullDir( plotDirectory, filepath );

            // change name to avoid memory conflicts
            histogram2D[ histogramName ] ->SetName(histogramName);


            std::cout << "Got here 2\n";

            // Get Eta label
            TString EtaStr = histogramName;{
              while ( EtaStr.Contains("Eta") )
                EtaStr = EtaStr.Remove( 0, EtaStr.Index("Eta") + 4);
            }

            TString etaLowStr  = EtaStr;
            etaLowStr = etaLowStr.Remove( etaLowStr.Index("_to_") );
            // 		  TString etaHighStr = EtaStr;
            // 		  etaHighStr = etaHighStr.Remove( 0, etaHighStr.Index("_to_") + 4);  

            etaLowStr.ReplaceAll("m","-");
            etaLowStr.ReplaceAll("p","\.");
            double etaLow  = etaLowStr.Atof();
            //		  double etaHigh = etaHighStr.Atof();
            etaBins[ etaLow ] = EtaStr;


          }
        }
        //}
      }


      // Store an ordered vector of bins
      std::vector<TString> etaBinsOrdered;
      map<double, TString>::const_iterator itrBin;
      for (itrBin = etaBins.begin(); itrBin != etaBins.end(); ++itrBin){

        //	double etaLow  = itrBin->first;    // Extract bin lower eta
        TString etaBin = itrBin->second; 

        etaBinsOrdered.push_back( etaBin );

      }



      // ************************************************************************************
      // *                               Plotting histograms                                *
      // ************************************************************************************
      PRINT("Plotting 2D Histograms")
        // Enable the fit box
        gStyle->SetOptFit(111111);

      //=========================
      // 2D Histograms
      //=========================
      SUBPRINT("2D Histograms")
        // iterate through all histograms in the map
        map<TString, TH2*>::const_iterator itr2D;









      // **************************************************
      // *             Calibration parameters             *
      // **************************************************

      // pT width of bins
      int ptBinning = setPtBin;

      // Range over which to make profiles
      double ptMin = setPtMin; 

      //double ptMax = 120;
      double ptMax = setPtMax;

      //Choose whether to do a fit or take the most common value
      bool doFit = true;
      bool doMostCommon = false;

      //Rebinning options
      bool doRebin = true;
      int responseRebin=1;
      int ptRebin=2;

      //Option to replace fits with large errors with histograms
      bool replaceBadPoints = false;
      bool removeBadPoints = true;

      //The allowed difference between the mean of the fit
      //and the hist mean
      double allowedFitDifference = 0.2;//2.0;//0.1;
      double allowedPtErr = ptBinning*2.0;//*1.5;
      double allowedReciprocalResponseErr = 0.3;//0.1;


      // **************************************************


      // Determine the number of profile plots to produce (should probably round up?)
      int totalProfs = int(( ptMax - ptMin )/ptBinning);


      //DEBUGGING    
      //DEBUGGING
      //DEBUGGING
      //      totalProfs = 3;
      //DEBUGGING
      //DEBUGGING
      //DEBUGGING


      // Points stored for the calibration fit, indices = [iEta][ptBin]
      std::map<TString, std::vector< std::vector< std::pair<double,double> > > > collectioniEtaPTBinnedPoint;
      std::map<TString, std::vector< std::vector< std::pair<double,double> > > > collectioniEtaPTBinnedPointError;



      //       //   // Points stored for the calibration fit, indices = [iEta][ptBin]
      //       //   std::vector< std::vector< std::pair<double,double> > > iEtaPTBinnedPoint;
      //       //   // Resize to fit the required data
      //       //   iEtaPTBinnedPoint.resize( 56, std::vector< std::pair<double,double> >( totalProfs ) );

      //       // Store whether to avoid processing the specified iEta
      //       std::vector<bool> iEtaVeto(56, false);


      for(itr2D = histogram2D.begin(); itr2D != histogram2D.end(); ++itr2D){

        TString histName = itr2D->first;    // Extract histogram name
        TH2*    hist2D   = itr2D->second;   // Extract histogram
        filepath = histogramDirectory[ histName ] + "/"; // Extract directory
        TCanvas* canv = new TCanvas();




        // Get the current eta bin
        int etaIndex;
        TString EtaStr;
        for ( uint iEtaBin = 0; iEtaBin < etaBinsOrdered.size(); ++iEtaBin ){

          TString tempEtaBin = etaBinsOrdered[ iEtaBin ];
          if ( histName.Contains( tempEtaBin ) != 0 ){
            EtaStr = tempEtaBin;
            etaIndex = iEtaBin;

            std::cout << EtaStr << "\t" << histName << "\n";
            break;
          }

        }

        TString EtaStrLabel = EtaStr;
        EtaStrLabel.ReplaceAll("_to_", ", ");
        EtaStrLabel = "[" + EtaStrLabel + "]";



        hist2D->Draw("COLZ");                   
        canv->SaveAs(plotDirectory + filepath + histName + ".png");   // write histogram to file
        //canv->SaveAs(plotDirectory + filepath + histName + ".pdf");   // write histogram to file

        // Store the name of the collection being calibrated, used to store the calibration data
        TString histBaseName = histName;

        if (histBaseName.Contains("ratio") != 0){
          histBaseName = histBaseName.Remove( histBaseName.Index( "ratio" ) );
          //      std::cout << "RES " << histBaseName << "\n";
        }
        else if(histBaseName.Contains("corr") != 0 ){
          histBaseName = histBaseName.Remove( histBaseName.Index( "corr" ) );
          //      std::cout << "PT " << histBaseName << "\n";
        }
        else{
          std::cout << "ERROR: Could not extract the collection type from '" << histName << "'\n";
          exit(1);
        }

        // Check whether storage exists for the current collection
        map<TString, std::vector< std::vector< std::pair<double,double> > > >::iterator it = collectioniEtaPTBinnedPoint.find( histBaseName );
        if ( it == collectioniEtaPTBinnedPoint.end() ) { 
          // Doesn't exist, make new storage

          // Points stored for the calibration fit, indices = [iEta][ptBin] 
          std::vector< std::vector< std::pair<double,double> > > iEtaPTBinnedPoint;
          std::vector< std::vector< std::pair<double,double> > > iEtaPTBinnedPointError;

          int size = etaBinsOrdered.size();

          // Resize to fit the required data 
          iEtaPTBinnedPoint.resize( size, std::vector< std::pair<double,double> >( totalProfs ) );
          collectioniEtaPTBinnedPoint[ histBaseName ] = iEtaPTBinnedPoint; 
          iEtaPTBinnedPointError.resize( size, std::vector< std::pair<double,double> >( totalProfs ) );
          collectioniEtaPTBinnedPointError[ histBaseName ] = iEtaPTBinnedPointError; 

          std::cout << "Made collection '" << histBaseName << "'\n";
        }

        // ****************************************************************************************************
        // *                                          Jet calibration                                         *
        // ****************************************************************************************************

        // Read details of the TH2
        int nBinsX      = hist2D->GetNbinsX();
        double binWidth = hist2D->GetBinWidth(1);
        double xPtMin   = hist2D->GetXaxis()->GetXmin();

        // Get current pt range to profile
        double ptLow, ptHigh;

        for ( int iBin = 0; iBin < totalProfs; ++iBin){

          ptLow  = ptMin + iBin*ptBinning;
          ptHigh = ptMin + (iBin + 1)*ptBinning - 1;

          // Indices of the bins to project over, add one to account for underflow bin
          int binLow  = (ptLow  - xPtMin)/binWidth + 1;
          int binHigh = (ptHigh - xPtMin)/binWidth + 1;


          //	std::cout << ptLow << " = " << hist2D->GetBinCenter( binLow ) << "\t" << ptHigh << " = " << hist2D->GetBinCenter( binHigh ) << "\n";

          TString ptLowStr  =  TString(Form("%d",Int_t(ptLow)));
          TString ptHighStr =  TString(Form("%d",Int_t(ptHigh)));
          TString ptRangeStr = ptLowStr + "_to_" + ptHighStr;

          TString label = typeLabel[ curSubDir ];

          TString newSaveName = "_prof_" + ptRangeStr;
          TString newHistName = "#eta #in " + EtaStrLabel + ", " + "p_{T} #in [" + ptLowStr + ", " + ptHighStr + "]";


          if ( histName.Contains("ratio") != 0 ){
            newHistName = label + " Response - " + newHistName;
          }
          else if ( histName.Contains("corr") != 0 ) {
            newHistName = label + " L1 P_{T} - " + newHistName;
          }


          TH1D *yProject = hist2D->ProjectionY( newHistName, binLow, binHigh, "eo");




          // ********************************************************************************
          // *                           Jet response calibration                           *
          // ********************************************************************************

          bool drawStats = false;
          if ( histName.Contains("ratio") != 0 ){

            //	    yProject->Rebin(5);
            if(!drawStats) yProject->SetStats(0);
            yProject->SetTitle(ptRangeStr+"GeV");
            yProject->GetXaxis()->SetTitle("P^{L1}_{T}/P^{GEN}_{T}");
            yProject->Draw();

            TPaveStats *fitStat;

            // ****************************************
            // *             Fit gaussian             *
            // ****************************************

            double response    = -1;
            double responseErr = -1;

            // Ensure the histogram contains entries
            if ( yProject->GetEntries() != 0){

              const double nSigma = 1.5;
              const double fitMin = -999;
              const int    nIter  = 3;

              if(doRebin) yProject->Rebin(responseRebin);
              if(doFit) fit_gaussian( yProject, nSigma, fitMin, nIter );


              yProject->GetXaxis()->SetRangeUser(0.,2.5);

              TF1* gausResFit = (TF1*) yProject->GetListOfFunctions()->Last();

              //statsbox wizardry
              gPad->Update();
              if(drawStats){
                fitStat = (TPaveStats*)yProject->FindObject("stats");
                fitStat->SetTextColor(kBlue);
                fitStat->SetX1NDC(.57); fitStat->SetX2NDC(.88); fitStat->SetY1NDC(.14); fitStat->SetY2NDC(.53);
                fitStat->Draw();
              }

              if (doFit && gausResFit) {
                //		yProject->Fit(gausResFit,"QR");
                gausResFit->SetLineColor(kRed);
                gausResFit->SetLineWidth(1);
                gausResFit->Draw("SAME");
              }
              canv->SaveAs(plotDirectory + filepath + histName + newSaveName + "FitGaus.png");   // write histogram to file
              //    canv->SaveAs(plotDirectory + filepath + histName + newSaveName + "FitGaus.pdf");   // write histogram to file


              if ( doFit && gausResFit) {

                // Get gaussian fit mean 
                response    = gausResFit->GetParameter( 1 );
                //responseErr = gausResFit->GetParameter( 2 );
                responseErr = gausResFit->GetParError( 1 );

                //Fill the chi2
                if(doChi2) responseChi2->Fill((ptLow+ptHigh)/2.0,etaIndex+0.5,gausResFit->GetChisquare()/(yProject->GetNbinsX()-3.0));
              }else if(doMostCommon){
                response = yProject->GetBinCenter(yProject->GetMaximumBin());

                //For fwhm, go from the centre so as not to be effected by being bound below by 0

                //int bin1Fwhm = yProject->FindFirstBinAbove(yProject->GetMaximum()/2.);
                int bin2Fwhm = yProject->FindLastBinAbove(yProject->GetMaximum()/2.);
                double fwhm = yProject->GetBinCenter(bin2Fwhm) - response;
                responseErr = fwhm/1.2;
              }
              std::cout << "Final fit: Response = " << response << " +/- " << responseErr << "\n";

            }

            double histMean = yProject->GetMean();
            double histErr  = yProject->GetRMS();

            double absRelDiff = fabs(response - histMean)/histMean;
            // Check whether there is a large disagreement (>10%) between the fit m\
            // ean and histogram mean
            if ( (absRelDiff > allowedFitDifference) && replaceBadPoints ){
              response   = histMean;
              responseErr = histErr;
            }



            std::cout << "Eta = " << EtaStr << "\tResponse = " << response << "\t+/- " << responseErr << "\n";	

            double reciprocalResponse = 0;
            double reciprocalResponseErr = 0;

            if (response != 0){
              reciprocalResponse    = 1/response;
              reciprocalResponseErr = responseErr/(response*response);
            }

            //Check the errors aren't too huge to include the points in the fit
            if((reciprocalResponseErr > allowedReciprocalResponseErr) && removeBadPoints){
              reciprocalResponse=-1.;
              reciprocalResponseErr=-1.;
            }

            // Store the inverted mean for plotting
            collectioniEtaPTBinnedPoint[ histBaseName ][etaIndex][iBin].second      = reciprocalResponse;
            // Error in reciprocal is given by: responseErr / Response^2
            collectioniEtaPTBinnedPointError[ histBaseName ][etaIndex][iBin].second = reciprocalResponseErr;

          }



          // ********************************************************************************
          // *                              Jet PT calibration                              *
          // ********************************************************************************

          if ( (histName.Contains("corr") != 0) ){

            //	    yProject->Rebin(4);
            yProject->Draw();

            TPaveStats *fitStat;

            if(!drawStats) yProject->SetStats(0);

            //          yProject->GetXaxis()->SetRangeUser(0.,200.);

            // ****************************************
            // *             Fit gaussian             *
            // ****************************************

            double l1Pt    = -1;
            double l1PtErr = -1;


            // Ensure the histogram contains entries
            if ( yProject->GetEntries() != 0){

              const double nSigma = 1.5;
              const double fitMin = -999;
              const int    nIter  = 3;

              if(doRebin) yProject->Rebin(ptRebin);


              if(doFit) fit_gaussian( yProject, nSigma, fitMin, nIter );

              yProject->GetXaxis()->SetRangeUser(0.,500.);

              TF1* gausPtFit = (TF1*) yProject->GetListOfFunctions()->Last();



              //statsbox wizardry
              gPad->Update();
              if(drawStats){
                fitStat = (TPaveStats*)yProject->FindObject("stats");
                fitStat->SetTextColor(kBlue);
                fitStat->SetX1NDC(.57); fitStat->SetX2NDC(.88); fitStat->SetY1NDC(.14); fitStat->SetY2NDC(.53);
                fitStat->Draw();
              }
              if ( doFit && gausPtFit) { 
                //		yProject->Fit(gausPtFit,"QR"); 
                gausPtFit->SetLineColor(kRed);
                gausPtFit->SetLineWidth(1);
                gausPtFit->Draw("SAME");
              }
              canv->SaveAs(plotDirectory + filepath + histName + newSaveName + "FitGaus.png");   // write histogram to file
              //      canv->SaveAs(plotDirectory + filepath + histName + newSaveName + "FitGaus.pdf");   // write histogram to file


              if (doFit && gausPtFit){
                // Get gaussian fit mean
                l1Pt    = gausPtFit->GetParameter( 1 );
                //l1PtErr = gausPtFit->GetParameter( 2 );
                l1PtErr = gausPtFit->GetParError( 1 );

                //Fill the chi2
                if(doChi2) ptChi2->Fill((ptLow+ptHigh)/2.0,etaIndex+0.5,gausPtFit->GetChisquare()/(yProject->GetNbinsX()-3.0));
              }else if(doMostCommon){
                l1Pt = yProject->GetBinCenter(yProject->GetMaximumBin());

                //For fwhm, go from the centre so as not to be effected by being bound below by 0

                //int bin1Fwhm = yProject->FindFirstBinAbove(yProject->GetMaximum()/2.);
                int bin2Fwhm2 = yProject->FindLastBinAbove(yProject->GetMaximum()/2.);

                double fwhm = yProject->GetBinCenter(bin2Fwhm2) - l1Pt;
                l1PtErr = fwhm/1.2;
              }

              std::cout << "Final fit: L1Pt = " << l1Pt << " +/- " << l1PtErr << "\n";

            }

            double histMean = yProject->GetMean();
            double histErr  = yProject->GetRMS();

            double absRelDiff = fabs(l1Pt - histMean)/histMean;
            // Check whether there is a large disagreement (>10%) between the fit m\
            // ean and histogram mean
            if ( (absRelDiff > allowedFitDifference) && replaceBadPoints ){
              l1Pt    = histMean;
              l1PtErr = histErr;
            }

            //Check the errors aren't too huge to include the points in the fit
            if((l1PtErr > allowedPtErr) && removeBadPoints){
              l1Pt=-1.;
              l1PtErr=-1.;
            }

            std::cout << "Eta = " << EtaStr << "\tl1Pt = " << l1Pt << "+/-\t" << l1PtErr << "\n";	
            // Store the mean for plotting
            collectioniEtaPTBinnedPoint[ histBaseName ][etaIndex][iBin].first      = l1Pt;
            collectioniEtaPTBinnedPointError[ histBaseName ][etaIndex][iBin].first = l1PtErr;

          }




        }


      }


      //#ifdef DEBUG_OFF  

      // ******************************************************************
      // *                    Plot calibration TGraphs                    *
      // ******************************************************************



      // E
      //      gStyle->SetOptFit(11111);




      std::map<TString, std::vector< std::vector< std::pair<double,double> > > >::const_iterator calibIt;

      for(calibIt = collectioniEtaPTBinnedPoint.begin(); calibIt != collectioniEtaPTBinnedPoint.end(); ++calibIt){


        TString collName = calibIt->first;    // Extract collection
        std::cout << "\n\nProcessing collection: " << collName << "------------------------------------------------------------\n\n\n\n";


        // ROOT file to store calibration TGraphs
        TFile* graphFile = new TFile( plotDirectory + collName + ".root", "RECREATE");

        // Extract the directory to store plots
        TString calibFilePath = filepath;
        calibFilePath = calibFilePath.Remove( calibFilePath.Index( "EtaBinned" ) );


        // Create a CMSSW compatable LUT
        TString outputCMSSW = "\t" + collName + "LUT = cms.vdouble(\n";

        // Iterate over iEta bins
        //	for (int iEtaIndex = 0; iEtaIndex < 56; ++iEtaIndex)
        for (uint etaIndex = 0; etaIndex < etaBinsOrdered.size(); ++etaIndex){

          TString EtaStr = etaBinsOrdered[ etaIndex ];
          TString EtaStrLabel = EtaStr;
          EtaStrLabel.ReplaceAll("_to_", ", ");
          EtaStrLabel = "[" + EtaStrLabel + "]";

          // Make a TGraph for each iEta bin
          double xArr[999],    yArr[999];
          double xErrArr[999], yErrArr[999];
          // Residuals
          double xResArr[999], yResArr[999];

          int failedPoints = 0;

          for (int iProf = 0; iProf < totalProfs; ++iProf){

            double x    = collectioniEtaPTBinnedPoint[collName][etaIndex][iProf].first;
            double y    = collectioniEtaPTBinnedPoint[collName][etaIndex][iProf].second;
            double xErr = collectioniEtaPTBinnedPointError[collName][etaIndex][iProf].first;
            double yErr = collectioniEtaPTBinnedPointError[collName][etaIndex][iProf].second;

            // Skip failed fits
            /*      if ( ( x = -1) || ( y == -1) 
                    /       //Check for errors as well! Added my own
                    || (xErr == -1) || (yErr == -1) 
                    ){ continue; }
                    */
            if ( ( x < 0. ) || ( y < 0.) 
                //Check for errors as well! Added my own
                || (xErr <0. ) || (yErr < 0.) 
               ){
              failedPoints++;  
              continue;
            }
            std::cout << "[ " << x << ", " << y << " )\n";

            // Store data in arrays for TGraph input
            xArr[ iProf - failedPoints ] = x;
            yArr[ iProf - failedPoints ] = y;
            xErrArr[ iProf - failedPoints ] = xErr;
            yErrArr[ iProf - failedPoints ] = yErr;

          }

          // Make the Eta binned TGraph
          TGraphErrors*  calibGraph = new TGraphErrors( totalProfs-failedPoints, xArr, yArr, xErrArr, yErrArr );
          calibGraph->SetTitle("#eta #in " + EtaStrLabel + ";<L1 p_{T}> (GeV);<L1 p_{T}/GEN p_{T}>^{-1}");
          calibGraph->SetMarkerStyle(8);
          calibGraph->SetMarkerSize(0.5);

          TCanvas* canv = new TCanvas();
          canv->SetGridx();
          canv->SetGridy();

          calibGraph->Draw("AP*");
          canv->SaveAs(plotDirectory + calibFilePath + "calibGraph_iEta_" + EtaStr + ".png");   // write histogram to file    
          //canv->SaveAs(plotDirectory + calibFilePath + "calibGraph_iEta_" + EtaStr + ".pdf");   // write histogram to file    

          TString EtaStrROOT = EtaStr;
          EtaStrROOT.ReplaceAll("-","minus");

          // Save to the ROOT file
          calibGraph->Write( "Eta_" + EtaStrROOT );


        }

        outputCMSSW += "\n\t),";
        /*
           ofstream calibLUT;
           calibLUT.open( plotDirectory + collName + "LUT.txt" );
           calibLUT << outputCMSSW;
           calibLUT.close();

*/
        std::cout << "Made LUT: " + plotDirectory + collName + "LUT.txt" + "\n";
        std::cout << outputCMSSW << "\n\n";


        std::cout << "\n\nMade ROOT file: " + plotDirectory + collName + ".root" + "\n";
        // Close the ROOT file
        graphFile->Close();

      }


      // Delete the previous contents of the container
      histogram2D.clear();

      if(doChi2){
        //Save the Chi2 histograms
        chi2File->cd();
        responseChi2->Write();
        ptChi2->Write();
      }
      f->cd();
    }





    // Delete the previous contents of the container
    histogramDirectory.clear();


  } // Directory loop







  // **************************************************************************************************
  // *                                          Provenance                                            *
  // **************************************************************************************************


  // To test different text positions run root in interactive mode with the code:
  // TCanvas canv;
  // canv.SetGrid();
  // canv.DrawFrame(0,0,1,1);
  //
  // Print statistics of the program running
  TCanvas statCanv;
  TLatex latex;
  Float_t curY = 0.95; // current Y coordinate of text
  latex.SetTextSize(0.04);
  latex.DrawLatex(0.05, curY, "Input file:");
  latex.SetTextSize(0.025);
  curY -= 0.02;;
  latex.DrawLatex(0.05, curY, filename);


  // save and close .eps
  statCanv.SaveAs( plotDirectory + "Provenance.png" );
  //statCanv.SaveAs( plotDirectory + "Provenance.pdf" );



  // Make webpage
  chdir( plotDirectory.Data() );
  system( "/home/hep/mb1512/.scripts/makeHTML.py" );


  std::cout << "\n\n\nOutput histograms to webpage: \n\n\t"
    << plotDirectory.ReplaceAll("/home/hep/", "http://www.hep.ph.ic.ac.uk/~").ReplaceAll("/public_html","") 
    << "\n\n\n";//mb1512/public_html/plots/";

  f->Close();
  chi2File->Close();
  return 0;

}

// --------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------
// --------------------------------------------------------------------------------------------------------------------------------------------








// // Stores all histograms in memory which are of a given TObject type

// void loadHistograms(TFile* f, TString rootDir, TString histType, std::vector < pair <TString, TString> > fileHistPair,
// 		    std::map <TString,TH1*> histMap){


//   // get list of histograms in file of specified type
//   fileHistPair = getROOTobjects(f, rootDir, histType);

//   for (unsigned int i = 0;i < fileHistPair.size(); i++){

//     // Extract the directory and name of the histogram
//     filepath         = fileHistPair[i].first;
//     histogramNameRaw = fileHistPair[i].second;

//     // create a .pdf compatible filename
//     histogramName    = histogramNameRaw;
//     histogramName.ReplaceAll("(","{").ReplaceAll(")","}"); // Replace brackets to allow pdf printing
//     filepath.ReplaceAll("(","{").ReplaceAll(")","}");

//     std::cout << "NEW = " << filepath << "\t" << histogramName << "\n";


//     // store histogram and its storage directory
//     histogramMap[ histogramName ]       = (TH1*)f->Get(filepath + "/" + histogramNameRaw)->Clone();
//     histogramDirectory[ histogramName ] = filepath;

//     // Ensure a directory is created to store the histogram
//     makeFullDir( plotDirectory, filepath );

//     // change name to avoid memory conflicts
//     histogramMap[ histogramName ] ->SetName(histogramName);

//   }

// }














//##############################################
//## TFile functions
//##############################################

//Returns a boolean value of whether the object in the specified directory exists
//Checks first whether directory exists to avoid Segfaults
Bool_t objectExists(TFile* file,  TString directory, TString objectName){
  //Key to determine whether specified objects exist
  TKey *key;

  if (directory != ""){

    //Check if the directory has more than one level
    if (directory.Contains("/")){
      std::vector <TString> dirLevel = splitString(directory,"/");
      TString curDir = "";

      //Loop through all the levels of the directory
      for (unsigned int i = 0;i < dirLevel.size();i++){
        if (curDir == "")
          //Check first level exists
          key = file->FindKey(dirLevel[i]);
        else{
          //Check higher levels exist
          key = file->GetDirectory(curDir)->FindKey(dirLevel[i]);
        }

        //Check if the directory was not found
        if (key == 0)	
          return false;

        curDir += dirLevel[i] + "/";
      }
    }
    else{
      //Check directory exists for a single level directory
      key = file->FindKey(directory);
    }
  }


  //Directory exists so now attempt to find the object
  key = file->GetDirectory(directory)->FindKey(objectName);

  //Return false if the object was not found
  return (key != 0);
}
//##############################################


std::vector <TString> splitString(TString inputStr, TString splitChar){

  //Vector to store the split substrings
  std::vector <TString> splitArr;

  //Initialise values so that it is detectable if the split character is not present
  Int_t index(-1), tempIndex(-1);

  //Find the first index of the split character, returns -1 if char not found
  tempIndex = inputStr.Index(splitChar,0);	

  TString tempStr, inputCopy;

  //Keep looping while the character is found
  while(tempIndex != -1){

    //KEEP THE SUBSRING LEFT OF THE STRIP CHARACTER
    inputCopy = inputStr; //Make a fresh copy of the input string
    inputCopy.Remove(tempIndex,inputCopy.Length());
    //if (index != 0)
    //  index +=1;
    inputCopy.Remove(0,index+1);

    //Store if the substring isn't empty
    if (inputCopy != "")
      splitArr.push_back(inputCopy);

    index = tempIndex;
    //Search for next instance of the character from index tempIndex+1 onwards
    tempIndex = inputStr.Index(splitChar,tempIndex+1);

  }

  //Check that the split character was found
  if (index == -1){
    std::cout << "\nError the character: \'" << splitChar 
      << "\' was not found in the string: \"" << inputStr << "\"\n\n";
    exit(1);
  }

  //Recover the last substring which is right of the final character

  inputCopy = inputStr;
  tempStr = inputCopy.Remove(0,index+1);

  if (tempStr != "")
    splitArr.push_back(tempStr);


  return splitArr;
}



// Returns a list of the specified objectType in a given rootDir
// "TDirectoryFile"
// [ntuplePath, objectName]
std::vector < std::pair <TString, TString> > getROOTobjects(TFile* f, TString rootDir, TString objectType){

  std::vector < std::pair <TString, TString> > objectList;

  //std::cout << "Got here, getROOTobjects\n";

  TIter nextkey(f->GetDirectory(rootDir)->GetListOfKeys());
  TKey *key;
  TString objName, objClassName;
  TString ntuplePath;

  while ((key=(TKey*)nextkey())) {  //Loop while the current key is valid

    TObject *obj = key->ReadObj(); //Point to the object with the current key

    objName      = key->GetName();

    //Modified to cut down on number of directories
    if(objName.Contains("L1Tree") || objName.Contains("_Calib") || objName.Contains("l1") || objName.Contains("global_histograms") || objName.Contains("calib30") || objName.Contains("calib50")) continue;
    std::cout << objName.Data() << std::endl;
    //std::cout << objectList.size() << std::endl;

    objClassName = obj->ClassName();

    //    if ( objClassName == objectType )
    if ( objClassName.Contains(objectType) ){

      ntuplePath = rootDir;
      //Modified to only get the relevant histograms
      //if(objName.Contains("L1PT_vs_OffPT") || objName.Contains("JetResponse_vs_OffPT") ) objectList.push_back( std::make_pair(rootDir,objName) );
      objectList.push_back( std::make_pair(rootDir,objName) );
      //      std::cout << objName << "\t" << objClassName << "\n";

    }
    else if ( objClassName == "TDirectoryFile"){


      //       std::cout << "----------------------------------------------------------------------------------\n\n";
      //       std::cout << objName << "\t" << objClassName << "\n\n";

      // Object is a directory so ammend the new ntuple path
      ntuplePath = rootDir + "/" + objName;
      // Look for the specified object in this new ntuple path
      std::vector < std::pair <TString, TString> > subDirObjectList = getROOTobjects(f, ntuplePath, objectType);

      if (subDirObjectList.size() == 0){
        //	std::cout << "No objects of type " << objectType << " found in directory: " << ntuplePath << "\n";
      }
      else{

        // Add the found objects to the stored list
        objectList.insert(objectList.end(), subDirObjectList.begin(), subDirObjectList.end());

      }


    }

  }



  return objectList;
}



std::vector < std::pair <TString, TString> > getROOTDirs(TFile* f, TString rootDir){

  std::vector < std::pair <TString, TString> > objectList;

  TIter nextkey(f->GetDirectory(rootDir)->GetListOfKeys());
  TKey *key;
  TString objName, objClassName;
  TString ntuplePath;

  TString objectType = "TDirectoryFile";


  while ((key=(TKey*)nextkey())) {  //Loop while the current key is valid

    TObject *obj = key->ReadObj(); //Point to the object with the current key

    objName      = key->GetName();
    objClassName = obj->ClassName();


    if ( objClassName.Contains(objectType) ){

      ntuplePath = rootDir;
      objectList.push_back( std::make_pair(rootDir,objName) );
      std::cout << objName << "\t" << objClassName << "\n";

      // Object is a directory so ammend the new ntuple path                                                                                                   
      ntuplePath = rootDir + "/" + objName;
      // Look for the specified object in this new ntuple path
      std::vector < std::pair <TString, TString> > subDirObjectList = getROOTDirs(f, ntuplePath);

      if ( !(subDirObjectList.empty()) ){

        // Add the found objects to the stored list 
        objectList.insert(objectList.end(), subDirObjectList.begin(), subDirObjectList.end());

      }

    }

  }



  return objectList;
}





//##############################################
//## Directory functions
//##############################################

// Returns a boolean value of whether the directory exists
Bool_t dirExists(TString dir){
  //Check if directory already exists
  struct stat sb; 

  if (stat(dir, &sb) == 0) // stat == 0 <=> Directory exists
    return true;
  else
    return false;
}


// Makes the entire file structure required to create the uppermost directory
void makeFullDir(TString baseDir, TString dir){


  if ( !(dir.Contains("/")) ){
    dir += "/";
  }

  // Generate list of all the subdirectories
  std::vector <TString> subDirs = splitString(dir,"/");

  TString subDir = "";

  // Check each directory exists to the uppermost directory
  for (unsigned int iSplit = 0; iSplit < subDirs.size(); iSplit++){


    TString curDir = subDirs[iSplit];
    subDir += curDir + "/";

    TString filePath = baseDir + subDir;

    //      std::cout << "LAME    " << filePath << "\n";


    if ( !dirExists(filePath)){
      //Make the directory with the corresponding RW permissions
      mkdir( filePath.Data(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
      //      std::cout << "Made directory: " << filePath << "\n";
    }

  }


}

// Takes a directory name and makes a unique directory with a revision number.
// Modifies the input directory so that it matches this new directory name.
void makeDirectory(TString& directoryName){


  // Get current date to use for a folder name
  time_t rawTime;
  struct tm* timeInfo;
  char curDate[80];

  time(&rawTime);
  timeInfo = localtime(&rawTime);
  strftime(curDate,80,"%d_%m_%y",timeInfo);  // Extract date in format : dd_mm_yyyy

  //Store the directory name with date
  directoryName.Append(curDate);

  //Check if directory already exists, if so add a 'revision' prefix
  if (dirExists(directoryName)){
    Int_t num = 1;
    TString tempStr = "";

    do{

      tempStr = directoryName + "_rev";
      tempStr += num;

      num++;
    }while(dirExists(tempStr)); //Loop while the pathname already exists

    //Store the directory filename
    directoryName = tempStr;
  }

  directoryName += "/";

  //Make the directory with the corresponding RW permissions
  mkdir(directoryName.Data(),S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

}




//______________________________________________________________________________ 
//
// JETMET additions
//______________________________________________________________________________                                                                              
void fit_gaussian( TH1D*& hrsp, const double nsigma, const double fitMin, const int niter){ 

  if (0==hrsp) {
    cout<<"ERROR: Empty pointer to fit_gaussian()"<<endl;return;
  }

  string histname = hrsp->GetName();
  double mean     = hrsp->GetMean();
  double rms      = hrsp->GetRMS();
  double ptRefMax(1.0),rspMax(0.0);

  double norm  = hrsp->GetMaximumStored();
  double peak  = mean;
  double sigma = rms;

  std::cout << "\n\nInitial fit: Norm = " << norm << "\tPeak = " << peak << "\tSigma = " << sigma << "\n"; 

  //   int pos1     = histname.find("RefPt");
  //   int pos2     = histname.find("to",pos1);
  //   string ss    = histname.substr(pos1+5,pos2);
  //   if (from_string(ptRefMax,ss,std::dec)) {
  //     if (histname.find("RelRsp")==0)
  //       rspMax = jtptmin/ptRefMax;
  //     if (histname.find("AbsRsp")==0)
  //       rspMax = jtptmin-ptRefMax;
  //   }


  // Fit range
  double xmin  = hrsp->GetXaxis()->GetXmin();
  double xmax  = hrsp->GetXaxis()->GetXmax();
  TF1* fitfnc(0); int fitstatus(-1);

  // Perform the specified number of fitting iterations
  for (int iiter=0;iiter<niter;iiter++) {

    vector<double> vv;
    vv.push_back( fitMin );
    vv.push_back(xmin);
    vv.push_back(peak-nsigma*sigma);
    // Modify fit range
    double fitrange_min = *std::max_element(vv.begin(),vv.end());
    double fitrange_max = std::min(xmax,peak+nsigma*sigma);

    std::cout << "Fit range: " << fitrange_min << " " << fitrange_max << std::endl;
    adjust_fitrange( hrsp, fitrange_min, fitrange_max );



    // Create new function fitting over specified range
    fitfnc = new TF1("fgaus","gaus",fitrange_min,fitrange_max);
    fitfnc->SetParNames("N","#mu","#sigma");
    fitfnc->SetParameter(0,norm);
    fitfnc->SetParameter(1,peak);
    fitfnc->SetParameter(2,sigma);
    fitstatus = hrsp->Fit(fitfnc,"RQ0");
    delete fitfnc;
    fitfnc = hrsp->GetFunction("fgaus");
    //fitfnc->ResetBit(TF1::kNotDraw); 
    if (fitfnc) {
      norm  = fitfnc->GetParameter(0);
      peak  = fitfnc->GetParameter(1);
      sigma = fitfnc->GetParameter(2);
      std::cout << "Fit iteration = " << iiter << "\tNorm = " << norm << "\tPeak = " << peak << "\tSigma = " << sigma << "\n"; 
    }
  }
  if(hrsp->GetFunction("fgaus")==0)
  {
    cout << "No function recorded in histogram " << hrsp->GetName() << endl;
  }
  if (0!=fitstatus){
    cout<<"fit_gaussian() to "<<hrsp->GetName()
      <<" failed. Fitstatus: "<<fitstatus
      <<" - FNC deleted."<<endl;
    hrsp->GetListOfFunctions()->Delete();
  }
}

//______________________________________________________________________________ 

void adjust_fitrange(TH1* h,double& min,double& max)
{
  int imin=1; while (h->GetBinLowEdge(imin)<min) imin++;
  int imax=1; while (h->GetBinLowEdge(imax)<max) imax++;
  while ((imax-imin)<8) {
    if (imin>1) {imin--; min = h->GetBinCenter(imin); }
    if (imax<h->GetNbinsX()-1) { imax++; max=h->GetBinCenter(imax); }
  }
}

