int N_50NS_BUNCHES=1368;
int N_25NS_BUNCHES=2508;
int LHC_FREQUENCY=11246;

int ZB_XSECTION=LHC_FREQUENCY*N_50NS_BUNCHES;
void rates(){
TFile * f_ttbar= new TFile("output/neutrino-output-2014-06-23.root");
TFile * f_out= new TFile("./rateTest.root","recreate");
TTree * tree_ttbar = f_ttbar->Get("demo/L1Tree;19");
std::vector<TString> jetnum;
jetnum.push_back("0");
jetnum.push_back("1");
jetnum.push_back("2");
jetnum.push_back("3");
std::vector<TString> jetType;

jetType.push_back("5400_calib_nopus");
jetType.push_back("5450_calib_nopus");
jetType.push_back("5450_calib_donut");
jetType.push_back("5400_calib_donut");
jetType.push_back("5400_calib_global");


jetType.push_back("gct_calib_gen");
TString bins = "(1000,-0.5,999.5)";

tree_ttbar->Draw("mNPV>>overall(100,0,100)");
TH1F *overall = (TH1F*)gPad->GetPrimitive("overall");
double overallNorm = overall->GetEntries();
std::cout << overallNorm << std::endl;
for (iNum = jetnum.begin();iNum != jetnum.end(); iNum++)
{
  TDirectory * jnum = f_out->mkdir("jetNumber_"+*iNum);
  jnum->cd();
  for (iType = jetType.begin();iType != jetType.end(); iType++)
  {

    //TCut matchedcut = "jetMatchedPt_"+*iType+"["+*iNum+"]!=-1";


    tree_ttbar->Draw("jetPt_"+*iType+"["+*iNum+"]>>"+*iType+"_"+*iNum+bins);
    TH1F *test = (TH1F*)gPad->GetPrimitive(*iType+"_"+*iNum);
    test->Write();
    test->SetName(*iType+"_"+*iNum+"_"+"Rate");
    std::cout << *iType+" "<< test->GetEntries() << std::endl;
    TH1F* cumuplot = makeCumu(test,overallNorm);
    cumuplot->Write();
  }
}
f_out->Close();
return;
}

TH1F * makeCumu(TH1F * input, double overallNorm){

  TH1F * output = new TH1F(*input);
  //output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  int nXbins = input->GetNbinsX();
  int nYbins = input->GetNbinsY();
  int dummy = 0;
  for (int xbins = 0; xbins <= nXbins+1; xbins++)
  {
    dummy += input->GetBinContent(nXbins+1-xbins);
    output->SetBinContent((nXbins+1-xbins),ZB_XSECTION*((double)dummy)/overallNorm);
  }

  return output;
}
