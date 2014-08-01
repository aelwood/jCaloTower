void turnOns()
{
  TFile * f_ttbar= new TFile("/afs/cern.ch/work/m/mcitron/public/TTBAR/140622/ttbar_output.root");
  TFile * f_out= new TFile("./turnOn.root","recreate");
  TTree * tree_ttbar = f_ttbar->Get("demo/L1Tree");
  std::vector<TString> PUSregime;
  PUSregime.push_back("5400_calib_nopus");
  PUSregime.push_back("5450_calib_nopus");
//  PUSregime.push_back("5400_calib_donut");
  PUSregime.push_back("5450_calib_donut");
  PUSregime.push_back("5400_calib_global");
  PUSregime.push_back("gct_calib_gen");

  std::vector<TString> jetnum;
  //jetnum.push_back("0");
  //jetnum.push_back("1");
  //jetnum.push_back("2");
  jetnum.push_back("3");

  std::vector<TString> genptcut;
  genptcut.push_back("50");
  //genptcut.push_back("150");
//  genptcut.push_back("250");
  //genptcut.push_back("200");
  //genptcut.push_back("400");
  //genptcut.push_back("500");
  TString bins = "(1000,0,1000)";
  f_out->cd();
  for (auto iType = PUSregime.begin(); iType!=PUSregime.end(); iType++)
  {      
    TDirectory * dir = f_out->mkdir((*iType).Data());
    dir->cd();
    for (auto iNum = jetnum.begin(); iNum!=jetnum.end(); iNum++)
    {

      tree_ttbar->Draw("jetPt_"+*iType+"["+*iNum+"]>>denom_"+*iNum+bins,"");
      TH1F *denom = (TH1F*)gPad->GetPrimitive("denom_"+*iNum);
      denom->Write();
      denom->Rebin(10);
      denom->Sumw2();
      for (auto iPt = genptcut.begin(); iPt!=genptcut.end(); iPt++)
      {
	tree_ttbar->Draw("jetPt_"+*iType+"["+*iNum+"]>>num_"+*iNum+"_"+*iPt+bins,"jetPt_ak4_gen["+*iNum+"]>"+*iPt);
	TH1F *num = (TH1F*)gPad->GetPrimitive("num_"+*iNum+"_"+*iPt);
	num->Write();
	num->Rebin(10);
	num->Sumw2();
	TGraphAsymmErrors * result=(effDiv(num,denom));
	result->Write((*iNum+"_"+*iPt));
      } 
    }
  }
  f_out->Close();
}

TGraphAsymmErrors * effDiv(TH1F * matchedhist, TH1F * allhist)
{
  TGraphAsymmErrors* matchCurve = new TGraphAsymmErrors();
  matchCurve->SetName("matchCurve");

  //TH1D matcheff = ((*matchedhist).Divide(allhist));
  //matchedhist->Divide(allhist);
  //matchedhist->Draw();

  matchCurve->Divide(matchedhist,allhist);
  return matchCurve;
}
