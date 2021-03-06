//Uncommented lines 231 to 281

#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>
#include <TProfile.h>
#include <TCanvas.h>
#include <TGraphErrors.h>
#include <iostream>
#include <TMath.h>
#include <TLine.h>
#include <TKey.h>
#include <fstream> 
#include <stdio.h>

// Returns a vector [ntuplePath, objectName] 
std::vector < std::pair <TString, TString> > getROOTobjects(TFile* f, TString rootDir, TString objectType);



double calibFit( Double_t *v, Double_t *par ){

  // JETMET uses log10 rather than the ln used here...
  double logX = log(v[0]);

  double term1 = par[1] / ( logX * logX + par[2] );
  double term2 = par[3] * exp( -par[4]*((logX - par[5])*(logX - par[5])) );

  // Final fitting function 
  double f    = par[0] + term1 + term2; 

  return f;
  //return 1.0/f;
}


//double calibrateGraph();


std::vector<TString> getJetTypes(){
  std::vector<TString> jetTypes;
  jetTypes.push_back("s0_nopus");
  jetTypes.push_back("s0_donut");
  jetTypes.push_back("s0_global");
  jetTypes.push_back("s0_chunky");
  jetTypes.push_back("s0_tsup1");
  jetTypes.push_back("s0_tsup2");
  jetTypes.push_back("s0_tsup3");
  jetTypes.push_back("s5_nopus");
  jetTypes.push_back("s5_donut");
  jetTypes.push_back("s5_global");
  jetTypes.push_back("s5_chunky");
  jetTypes.push_back("s5_tsup1");
  jetTypes.push_back("s5_tsup2");
  jetTypes.push_back("s5_tsup3");
  jetTypes.push_back("c10_nopus");
  jetTypes.push_back("c10_donut");
  jetTypes.push_back("c10_global");
  jetTypes.push_back("c10_chunky");
  jetTypes.push_back("c10_tsup1");
  jetTypes.push_back("c10_tsup2");
  jetTypes.push_back("c10_tsup3");
  return jetTypes;
}



// TFile *f = new TFile("/vols/cms04/mb1512/Batch/2014-02-03_SingleMu_12Dec_11x11/SingleMu_12Dec_11x11.root","OPEN")
// recalibrateGraph( f, "/vols/cms04/mb1512/Batch/2014-02-03_SingleMu_12Dec_11x11/", CMSSW, 0, 200, "/JetHist/Calibration/Calibration_CalibPrePUS_ak5PUS/EtaBinned/", "Eta_-2.500_to_-2.172/Recalib/Calibration_CalibPrePUS_ak5PUS_JetResponse_vs_L1PT_Eta_-2.500_to_-2.172_prof")


/*
   void recalibrateGraph(TFile *file, TString directory, TString &outputLowPt, TString &outputHighPt, TString &outputNVTXResponse,
   double calibFitMin    = 0, 
   double calibFitMiddle = 45,
   double calibFitMax    = 200, 
   TString jetCollection = "Calibration_CalibPrePUS_ak5PUS",
   TString etaRange      = "Eta_-0.174_to_0.000",
   bool NVTXCorrection   = false ){



//JetHist/Calibration/Calibration_CalibPrePUS_ak5PUS/EtaBinned/Eta_-0.174_to_0.000/Recalib/Calibration_CalibPrePUS_ak5PUS_JetResponse_vs_L1PT_Eta_-0.174_to_0.000_prof

//   TString jetCollection = "Calibration_CalibPrePUS_ak5PUS";
//   TString etaRange      = "Eta_-0.174_to_0.000";
TString graph         = "JetHist/Calibration/" + jetCollection + "/EtaBinned/" + etaRange + "/Recalib/" + jetCollection 
+ "_JetResponse_vs_L1PT_" + etaRange + "_prof";


TProfile* gr1 = (TProfile*)file->Get( graph )->Clone();


// Low-pT fitting
// ------------------------------------------------------------

// Fit the calibration curve over low pT
TF1 *calibrationFitLow = new TF1("recalibFitLowPt", "pol9", calibFitMin, calibFitMiddle);
calibrationFitLow->SetLineColor(kRed);
gr1->Fit( calibrationFitLow, "MR");

// Extract calibration parameters
TString p0 = Form("%e", calibrationFitLow->GetParameter( 0 ));
TString p1 = Form("%e", calibrationFitLow->GetParameter( 1 ));
TString p2 = Form("%e", calibrationFitLow->GetParameter( 2 ));
TString p3 = Form("%e", calibrationFitLow->GetParameter( 3 ));
TString p4 = Form("%e", calibrationFitLow->GetParameter( 4 ));
TString p5 = Form("%e", calibrationFitLow->GetParameter( 5 ));
TString p6 = Form("%e", calibrationFitLow->GetParameter( 6 ));
TString p7 = Form("%e", calibrationFitLow->GetParameter( 7 ));
TString p8 = Form("%e", calibrationFitLow->GetParameter( 8 ));
TString p9 = Form("%e", calibrationFitLow->GetParameter( 9 ));


// Output fit parameters
outputLowPt += p0 + "\t" + p1 + "\t" + p2 + "\t" + p3 + "\t" + p4 + "\t" + p5 + 
"\t" + p6 + "\t" + p7 + "\t" + p8 + "\t" + p9 + "\n";
//  std::cout << outputLowPt;



// High-pT fitting
// ------------------------------------------------------------

// Fit the calibration curve over high pT
TF1 *calibrationFitHigh = new TF1("recalibFitHighPt", "pol2", calibFitMiddle, calibFitMax);
calibrationFitHigh->SetLineColor(kBlue);
gr1->Fit( calibrationFitHigh, "MR");

// Extract calibration parameters
TString p0High = Form("%e", calibrationFitHigh->GetParameter( 0 ));
TString p1High = Form("%e", calibrationFitHigh->GetParameter( 1 ));
TString p2High = Form("%e", calibrationFitHigh->GetParameter( 2 ));


// Output fit parameters 
outputHighPt += p0High + "\t" + p1High + "\t" + p2High + "\n";
//  std::cout << outputHighPt;



// NVTX correction
// ------------------------------------------------------------

TProfile* jetResponseProf;
TF1 *NVTXFit;

if ( NVTXCorrection ){

  int NVTXMin = 2;
  int NVTXMax = 35;

  // Assumes this exists as well!!!!
  TString recalibJetCollection = jetCollection;
  recalibJetCollection.ReplaceAll("_Calib", "_Recalib"); //Calibration_CalibPrePUS_ak5PUS


  TString NVTXGraph = "JetHist/Calibration/" + recalibJetCollection + "/EtaBinned/" + etaRange + "/Recalib/" + recalibJetCollection 
    + "_JetResponse_vs_NVTX_L1Ptge12_" + etaRange + "_prof";

  jetResponseProf = (TProfile*)file->Get( NVTXGraph )->Clone();

  // Fit the jetRessponse-NVTX graph
  NVTXFit = new TF1("recalibNVTXFit", "pol1", NVTXMin, NVTXMax);
  NVTXFit->SetLineColor(kRed);
  jetResponseProf->Fit( NVTXFit, "MR");

  // Extract calibration parameters
  TString p0Re = Form("%e", NVTXFit->GetParameter( 0 ));
  TString p1Re = Form("%e", NVTXFit->GetParameter( 1 ));

  // Output fit parameters
  outputNVTXResponse += p0Re + "\t" + p1Re + "\n";

}




// ********************************************************************************
// Output stuff
// ********************************************************************************
TCanvas *canvOut = new TCanvas();

// Fit plot
gr1->Draw("AP");

calibrationFitLow->Draw("SAME");
canvOut->SaveAs( directory + "JetResponse_vs_L1PT_" + etaRange + "_fit.png" );
//canvOut->SaveAs( directory + "JetResponse_vs_L1PT_" + etaRange + "_fit.pdf" );

if ( NVTXCorrection ){
  // NVTX plot
  jetResponseProf->Draw("AP");
  NVTXFit->Draw("SAME");
  canvOut->SaveAs( directory + "JetResponse_vs_NVTX_" + etaRange + "_fit.png" );
  //canvOut->SaveAs( directory + "JetResponse_vs_NVTX_" + etaRange + "_fit.pdf" );
}

}
*/

// TFile *f = new TFile("/home/hep/mb1512/public_html/plots/07_02_14/Calibration_PrePUS_ak5PUS.root","OPEN");
// TString outputStr; 
// calibrateGraph( f, "/home/hep/mb1512/public_html/plots/07_02_14/", outputStr, 0, 300, "Eta_1.566_to_1.740" )


double calibrateGraph(TFile *file, TString directory, TString &outputCMSSW, double calibFitMin = 0, double calibFitMax = 300, TString graph = "Eta_minus3.000_to_minus2.172", bool silent = false ){

  char charName[20];
  sprintf(charName,"chi2Fits_%d_to_%d",int(calibFitMin),int(calibFitMax));

  file->cd(charName);

  TGraphErrors *gr1 = (TGraphErrors*)file->Get( graph );

  //gr1->GetXaxis()->SetLimits(0.,250.);

  // Fit the calibration curve over a restricted range 
  TF1 *calibrationFit = new TF1("calibrationFit", calibFit, calibFitMin, calibFitMax, 6);

  // ********************************************************************************                                                                 
  // FROM: jet_l3_correction_x.cc      


  //   TF1 *calibrationFit = new TF1("calibrationFit","[0]-[1]/(pow(log10(x),2)+[2])-[3]*exp((-[4]*(log10(x)-[5])*(log10(x)-[5]))+([6]*(log10(x)-[5])))",
  // 				calibFitMin, calibFitMax );

  calibrationFit->SetLineColor(kRed); 
  calibrationFit->SetLineWidth(1);

  calibrationFit->SetParameter(0,0.96);
  calibrationFit->SetParameter(1,0.033);
  calibrationFit->SetParameter(2,-0.7);
  calibrationFit->SetParameter(3,0.02);
  calibrationFit->SetParameter(4,1.02);
  calibrationFit->SetParameter(5,2.7);
  calibrationFit->SetParameter(6,0.016);


  //   // Restrict to only positive correlation with RECO.
  calibrationFit->SetParLimits(0, 0, 10);
  calibrationFit->SetParLimits(1, 0, 10);
  calibrationFit->SetParLimits(2, -1, 10);
  calibrationFit->SetParLimits(3, 0, 10);
  // Restrict the exponetial decay to be strictly postive
  calibrationFit->SetParLimits(4, 0, 10);
  calibrationFit->SetParLimits(5, 0, 10);

  //   // Set initial parameter values 
  //   calibrationFit->SetParameter(0, 0.78);
  //   calibrationFit->SetParameter(1, 4.33);
  //   calibrationFit->SetParameter(2, 2.67);
  //   calibrationFit->SetParameter(3, 0.57);
  //   calibrationFit->SetParameter(4, 0.88);
  //   calibrationFit->SetParameter(5, 0.41);

  //gr1->Fit(calibrationFit,"MQR");
  gr1->Fit(calibrationFit,"MQR");

  //   //int fitStatus = gr1->Fit( calibrationFit, "MR");
  //   gr1->Fit( calibrationFit, "MR");

  //UNCOMMENTED
  // Check fit was good
  // ************************************************************
  bool checkFit = false;
  if (checkFit){
    // x and y points of TGraph
    double x, y;
    int point = 0;

    bool badFit;
    do{
      badFit = false;

      // Read all the points and calculate the residual
      while( gr1->GetPoint(point, x, y) != -1 ){

        // Get function prediction
        double fitY = calibrationFit->Eval(x);
        // Calculate residual
        double yRes = fitY - y;

        double minPT = 15;
        // Fit was bad in the required pT regime, try and improve fit
        if ( x > minPT ){
          if ( fabs(yRes) > 0.1 ){

            std::cout << "FIT WAS BAD!!!!\n";
            badFit = true;

            calibFitMax -= 1;
            if (calibFitMax == calibFitMin){
              std::cout << "ERROR - Fit could not converge\n";
              exit(1);
            }

            std::cout << "New maximum = " << calibFitMax << "\n";
            calibrationFit = new TF1("calibrationFit", calibFit, calibFitMin, calibFitMax, 6);
            gr1->Fit( calibrationFit, "MR");
            break;
          }
        }


        point++;
      }


    }while(badFit);
  }

  //UNCOMMMENTED!!

  // Extract calibration parameters
  TString p0 = Form("%f", calibrationFit->GetParameter( 0 ));
  TString p1 = Form("%f", calibrationFit->GetParameter( 1 ));
  TString p2 = Form("%f", calibrationFit->GetParameter( 2 ));
  TString p3 = Form("%f", calibrationFit->GetParameter( 3 ));
  TString p4 = Form("%f", calibrationFit->GetParameter( 4 ));
  TString p5 = Form("%f", calibrationFit->GetParameter( 5 ));

  // Output fit parameters
  //   std::cout << "\tp0 = " << p0 << "\n"
  // 	    << "\tp1 = " << p1 << "\n"
  // 	    << "\tp2 = " << p2 << "\n"
  // 	    << "\tp3 = " << p3 << "\n"
  // 	    << "\tp4 = " << p4 << "\n"
  // 	    << "\tp5 = " << p5 << "\n\n\n";

  // ACCOUNT FOR CURRENT REGION LEVEL BINNING, REMOVE THIS LATER!
  outputCMSSW += "\t\t" + p0 + ",\t" + p1 + ",\t" + p2 + ",\t" + p3 + ",\t" + p4 + ",\t" + p5 + ",\n";
  //  outputCMSSW += "\t\t" + p0 + ",\t" + p1 + ",\t" + p2 + ",\t" + p3 + ",\t" + p4 + ",\t" + p5 + ",\n";
  //   outputCMSSW += "\t\t" + p0 + ",\t" + p1 + ",\t" + p2 + ",\t" + p3 + ",\t" + p4 + ",\t" + p5 + ",\n";
  //   outputCMSSW += "\t\t" + p0 + ",\t" + p1 + ",\t" + p2 + ",\t" + p3 + ",\t" + p4 + ",\t" + p5 + ",\n";
  //  std::cout << outputCMSSW;

  // Create a split canvas
  TCanvas *canv = new TCanvas();
  canv->Divide( 2, 1);


  if (silent == false){

    // ************************************************************
    // *                     Plot fit function                    *
    // ************************************************************
    //gr1->GetXaxis()->SetRangeUser(5.,250.);
    canv->cd(1);
    gr1->Draw("AP");
  }


  // ************************************************************
  // *                       Plot residual                      *
  // ************************************************************

  TH1F *residual = new TH1F("res", "Residuals;<L1 p_{T}> (GeV);Response residual", 360, 0, 360);
  residual->SetMarkerStyle(8);
  residual->SetMarkerSize(0.5);
  residual->SetFillColor(kRed);

  double yMin = -0.1;
  double yMax =  0.1;

  residual->SetMinimum( yMin );
  residual->SetMaximum( yMax );

  // x and y points of TGraph
  double x, y;
  int point = 0;


  // Read all the points and calculate the residual
  while( gr1->GetPoint(point, x, y) != -1 ){


    // Get function prediction
    double fitY = calibrationFit->Eval(x);
    // Calculate residual
    double yRes = fitY - y;

    // Stop plotting errors with inf
    if ( yRes > 999 ){
      yRes = 999;
    }
    if ( yRes < -999 ){
      yRes = -999;
    }

    residual->Fill( x, yRes );

    point++;
  }

  if (silent == false){
    canv->cd(2);
    residual->Draw("PL");
  }
  //  residual->Draw("E4");


  // ********************************************************************************
  // Output stuff
  // ********************************************************************************
  TCanvas *canvOut = new TCanvas();

  // Fit plot
  //gr1->GetXaxis()->SetRangeUser(5.,250.);
  gr1->SetName(graph+"_withfit"); 
  gr1->Write();
  gr1->Draw("AP");
  canvOut->SaveAs( directory + graph + "_fit.png" );
  //canvOut->SaveAs( directory + graph + "_fit.pdf" );


  // Residual of fit
  residual->Draw("PL");
  TLine *fitMinLine = new TLine( calibFitMin, yMin, calibFitMin, yMax);
  TLine *fitMaxLine = new TLine( calibFitMax, yMin, calibFitMax, yMax);
  fitMinLine->SetLineColor(kBlue);  fitMaxLine->SetLineColor(kBlue);
  fitMinLine->SetLineStyle(9);      fitMaxLine->SetLineStyle(9);
  fitMinLine->Draw();               fitMaxLine->Draw();

  //canvOut->SaveAs( directory + graph + "_res.png" );
  //canvOut->SaveAs( directory + graph + "_res.pdf" );


  //return residual->GetRMS();
  return calibrationFit->GetChisquare();
}


int scanRange( TFile *file, TString directory, double min = 20, double initialMax = 100, double max = 170, int scanSteps = 70, TString graph = "Eta_minus3.000_to_minus2.172" ){

  double scanWidth = (max - initialMax)/double(scanSteps);

  TH1F *rmsHist = new TH1F("rmsHist", "RMS as function of max range", 250, 0, 250 );

  TString outputCMSSW;

  // Scan maximum
  for (int i = 0; i < scanSteps; ++i){

    double currentMax = initialMax + scanWidth*i;
    std::cout << "\nCurrent maximum = " << currentMax << "\n\n";

    double RMS = calibrateGraph( file, directory, outputCMSSW, min, currentMax, graph, true );

    rmsHist->Fill( currentMax, RMS );
  }


  TCanvas *canv1 = new TCanvas();
  rmsHist->Draw();


  return 0;
}



// calibrateFile("/home/hep/mb1512/public_html/plots/07_02_14/Calibration_PUS_ak5PUS.root");

int calibrateFile(TString ROOTFile,  double calibFitMin = 0, double calibFitMax = 300, bool silent = false ){




  // Find the directory in which the ROOT file resides
  TString directory = ROOTFile;
  int index = 0;
  while ( directory.Index("/", index) != -1 ){
    index = directory.Index("/", index) + 1;
  }
  directory.Remove(index, directory.Length() );

  TString lutOut = ROOTFile;
  index = 0;
  while ( lutOut.Index(".", index) != -1 ){
    index = lutOut.Index(".", index) + 1;
  }
  lutOut.Remove(index, lutOut.Length() );
  lutOut=lutOut+"lut";

  // Open the ROOT file
  //TFile *f = new TFile(ROOTFile, "OPEN");
  TFile *f = new TFile(ROOTFile, "UPDATE");

  char charName[20];
  sprintf(charName,"chi2Fits_%d_to_%d",int(calibFitMin),int(calibFitMax));

  TH1D* chi2Fits = new TH1D("chi2Fits","Chi2 for each eta bin", 8,0.,8.);


  // list of histogram names in ROOT file with their corresponding directory structure 
  std::vector < std::pair <TString, TString> > fileHistPair;
  // get list of histograms in file 
  fileHistPair = getROOTobjects(f, "", "TGraphErrors");

  TString outputCMSSW;

  f->mkdir(charName);

  int etaBin=0;
  // Calibrate each histogram in the ROOTfile
  for (unsigned int i = 0; i < fileHistPair.size(); i++){

    // Extract the directory and name of the histogram 
    //    TString filepathRaw      = fileHistPair[i].first;
    TString histogramName = fileHistPair[i].second;

    // Run calibration on the graph
    if(!histogramName.Contains("withfit")){
      //calibrateGraph( f, directory, outputCMSSW, calibFitMin, calibFitMax, histogramName, silent );
      double chi2 = calibrateGraph( f, directory, outputCMSSW, calibFitMin, calibFitMax, histogramName, silent );
      std::cout << std::endl << histogramName.Data() << " chi2: " << chi2 << std::endl;
      chi2Fits->Fill(etaBin,chi2);
      etaBin++;
    }
  }

  f->cd(charName);

  chi2Fits->Write();

  f->Close();

  std::cout << "Output LUT: \n\n";
  std::cout << outputCMSSW << "\n\n";

  ofstream outputLutFile;
  outputLutFile.open (lutOut.Data());
  outputLutFile << outputCMSSW << "\n";
  outputLutFile.close();

  return 0;
}





// recalibrateFile( "/vols/cms04/mb1512/Batch/2014-02-03_SingleMu_12Dec_11x11/SingleMu_12Dec_11x11.root" );
// recalibrateFile( "/vols/cms04/mb1512/Batch/2014-02-07_SingleMu_12Dec_11x11/SingleMu_12Dec_11x11.root", "Calibration_CalibPUS_ak5PUS" )
/*

   int recalibrateFile( TString ROOTFile, TString jetCollection = "Calibration_CalibPrePUS_ak5PUS", double transitionPt = 45, bool NVTXCorrection = false ){




// Find the directory in which the ROOT file resides
TString directory = ROOTFile;
int index = 0;
while ( directory.Index("/", index) != -1 ){
index = directory.Index("/", index) + 1;
}
directory.Remove(index, directory.Length() );

// Open the ROOT file
TFile *f = new TFile(ROOTFile, "OPEN");





// list of histogram names in ROOT file with their corresponding directory structure 
std::vector < std::pair <TString, TString> > fileHistPair;
// get list of histograms in file 
fileHistPair = getROOTobjects(f, "", "TProfile");

TString outputLowPt, outputHighPt, outputNVTXResponse;

// Calibrate each histogram in the ROOTfile
for (unsigned int i = 0; i < fileHistPair.size(); i++){

// Extract the directory and name of the histogram 
TString filepathRaw      = fileHistPair[i].first;
TString histogramName = fileHistPair[i].second;

// Skip directories that are non pertinent
if ( filepathRaw.Contains("/Calibration/") == 0 ){
continue;
}
if ( filepathRaw.Contains( jetCollection ) == 0 ){
continue;
}
if ( filepathRaw.Contains("/Recalib") == 0 ){
continue;
}
// Get only relavent histograms
if ( histogramName.Contains("JetResponse_vs_L1PT") == 0 ){
continue;
}

TString etaRange = histogramName;
etaRange.ReplaceAll(jetCollection + "_JetResponse_vs_L1PT_","");
etaRange.ReplaceAll("_prof","");

// Run recalibration on the graph
recalibrateGraph( f, directory, outputLowPt, outputHighPt, outputNVTXResponse, 0, transitionPt, 200, jetCollection, etaRange, NVTXCorrection );

}









// Write low-pT LUT  
std::ofstream iWriteLowPt (directory + jetCollection + "LowPt.LUT", std::ofstream::out);
iWriteLowPt << outputLowPt;
iWriteLowPt.close();

// Write high-pT LUT  
std::ofstream iWriteHighPt (directory + jetCollection + "HighPt.LUT", std::ofstream::out);
iWriteHighPt << outputHighPt;
iWriteHighPt.close();

// Write offset LUT  
std::ofstream iWriteNVTXResponse (directory + jetCollection + "NVTXResponse.LUT", std::ofstream::out);
iWriteNVTXResponse << outputNVTXResponse;
iWriteNVTXResponse.close();


std::cout << "\n\n\n\nWritten LUTs:\n\n" 
<< "\t" << directory + jetCollection + "LowPt.LUT"        << "\n"
<< "\t" << directory + jetCollection + "HighPt.LUT"       << "\n"
<< "\t" << directory + jetCollection + "NVTXResponse.LUT" << "\n\n";






return 0;
}

*/












// ****************************************************************************************************
// ****************************************************************************************************


// Returns a list of the specified objectType in a given rootDir 
// "TDirectoryFile" 
// [ntuplePath, objectName] 
std::vector < std::pair <TString, TString> > getROOTobjects(TFile* f, TString rootDir, TString objectType){

  std::vector < std::pair <TString, TString> > objectList;

  TIter nextkey(f->GetDirectory(rootDir)->GetListOfKeys());
  TKey *key;
  TString objName, objClassName;
  TString ntuplePath;

  while ((key=(TKey*)nextkey())) {  //Loop while the current key is valid 

    TObject *obj = key->ReadObj(); //Point to the object with the current key 

    objName      = key->GetName();
    objClassName = obj->ClassName();

    //    if ( objClassName == objectType ){ 
    if ( objClassName.Contains(objectType) ){

      ntuplePath = rootDir;
      objectList.push_back( std::make_pair(rootDir,objName) );
      //      std::cout << objName << "\t" << objClassName << "\n"; 

    }
    else if ( objClassName == "TDirectoryFile"){

      // Object is a directory so ammend the new ntuple path 
      ntuplePath = rootDir + "/" + objName;
      // Look for the specified object in this new ntuple path 
      std::vector < std::pair <TString, TString> > subDirObjectList = getROOTobjects(f, ntuplePath, objectType);

      if (subDirObjectList.size() == 0){
        //      std::cout << "No objects of type " << objectType << " found in directory: " << ntuplePath << "\n"; 
      }
      else{

        // Add the found objects to the stored list 
        objectList.insert(objectList.end(), subDirObjectList.begin(), subDirObjectList.end());

      }
    }
  }


  return objectList;
  }






