void efficiencies(){
  //TFile * f_ttbar= new TFile("ttbar-output-2014-06-22.root");
  TFile * f_ttbar= new TFile("/afs/cern.ch/work/m/mcitron/public/TTBAR/140622/ttbar_output.root");
  TFile * f_out= new TFile("./effTest.root","recreate");
  TTree * tree_ttbar = f_ttbar->Get("demo/L1Tree");
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
  //jetType.push_back("calib_gct");
  TString bins = "(1000,0,1000)";
  for (iNum = jetnum.begin();iNum != jetnum.end(); iNum++)
  {
    TDirectory * jnum = f_out->mkdir("jetNumber_"+*iNum);
    jnum->cd();
    TCut genptcut = "jetPt_ak4_gen["+*iNum+"]>50";
    tree_ttbar->Draw("jetPt_ak4_gen["+*iNum+"]>>overall_"+*iNum,genptcut,"");
    TH1F *overall = (TH1F*)gPad->GetPrimitive("overall_"+*iNum);
    double overallNorm = overall->GetEntries();
    for (iType = jetType.begin();iType != jetType.end(); iType++)
    {

      TCut matchedcut = "jetMatchedPt_"+*iType+"["+*iNum+"]!=-1";


      tree_ttbar->Draw("jetPt_"+*iType+"["+*iNum+"]>>"+*iType+"_"+*iNum+bins,genptcut&&matchedcut,"");
      TH1F *test = (TH1F*)gPad->GetPrimitive(*iType+"_"+*iNum);
      test->Write();
      test->SetName(*iType+"_"+*iNum+"_"+"Efficiency");

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
  int dummy = input->GetBinContent(nXbins+1);
  for (int xbins = 0; xbins <= nXbins; xbins++)
  {
    dummy += input->GetBinContent(nXbins-xbins);
    output->SetBinContent((nXbins-xbins),((double)dummy)/overallNorm);
  }

  return output;
}
