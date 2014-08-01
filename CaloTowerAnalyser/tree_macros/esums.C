void esums(){
  TFile * f_in= new TFile("/afs/cern.ch/work/m/mcitron/public/TTBAR/140622/ttbar_output.root");

  TTree * tree = f_in->Get("demo/L1Tree");
  TFile * f_out= new TFile("./sumsTest.root","recreate");
  f_out->cd();
  std::vector<TString> jetType;
  jetType.push_back("5400_calib_nopus");
  jetType.push_back("5450_calib_nopus");
  jetType.push_back("5450_calib_donut");
  jetType.push_back("5400_calib_donut");
  jetType.push_back("5400_calib_global");
  jetType.push_back("ak4_gen");
  //TCut matchedcut = "";
  std::vector<TString> sumType;
  sumType.push_back("HT");
  sumType.push_back("MHT");
  sumType.push_back("MHTX");
  sumType.push_back("MHTY");

  std::vector<TString> index;
  index.push_back("0");
  index.push_back("1");
  index.push_back("2");
  index.push_back("3");

  TString bins = "(400,-2000,2000)";
  int i = 0;
  for (auto iSum = sumType.begin(); iSum!=sumType.end();iSum++)
  {
    std::cout << *iSum << std::endl;
    TDirectory * sumdir = f_out->mkdir("arb"+(*iSum));
    sumdir->cd();
    for (auto iType = jetType.begin(); iType!=jetType.end();iType++)
    {
      tree->Draw("sums_"+*iType+"_sum["+index.at(i)+"]>>"+*iSum+"_"+*iType+bins);
      TH1F *test = (TH1F*)gPad->GetPrimitive(*iSum+"_"+*iType);
      test->Write();

    }
    i++;
  }
    f_out->Close();
  return;

}

