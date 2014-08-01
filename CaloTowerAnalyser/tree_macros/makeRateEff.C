void makeRateEff()
{

  TFile * f_rate = TFile::Open("rateTest.root");
  TFile * f_eff = TFile::Open("effTest.root"); 
  std::vector<TString> jetType;
jetType.push_back("5400_calib_nopus");
jetType.push_back("5450_calib_nopus");
jetType.push_back("5450_calib_donut");
jetType.push_back("5400_calib_donut");
jetType.push_back("5400_calib_global");

  TFile* top = new TFile("ratePlotsEff.root","recreate");
  //TH1D * matchedhist_global_global =  (f->Get("demo/ak4_global_pus/col2_matched_global_alljet_pt"));
  //TH1D * matchedhist_local_global =  (f->Get("demo/ak4_global_pus/col2_matched_local_alljet_pt"));

  for (auto iPUS = jetType.begin(); iPUS!=jetType.end(); iPUS++)
  {
    TDirectory * dir = top->mkdir((*iPUS).Data());
    dir->cd();
    //for (auto iJet = jetnum.begin(); iJet!=jetnum.end(); iJet++)
    {
      std::cout << *iPUS << std::endl;
      TH1D * origplot_rate = f_rate->Get("jetNumber_3/"+(*iPUS+TString("_3_Rate")));
      TH1D * origplot_eff = f_eff->Get("jetNumber_3/"+(*iPUS+TString("_3_Efficiency")));

      //Plot the rates for different bins against one another
      if(origplot_rate->GetNbinsX() != origplot_eff->GetNbinsX()) std::cout << "Different binning between rate and efficiency\n";
      else{

	TGraph * rate_efficiency =
	  new TGraph(origplot_rate->GetNbinsX());
	rate_efficiency->SetName("rate_efficiency");
	rate_efficiency->SetTitle(";Efficiency (ttbar normalised rate);Rate (0 bias normalised rate)");

	for(unsigned bin=0; bin<origplot_rate->GetNbinsX(); bin++){
	  rate_efficiency->SetPoint(bin, origplot_eff->GetBinContent(bin), origplot_rate->GetBinContent(bin));
	}

	rate_efficiency->RemovePoint(rate_efficiency->GetN());
	rate_efficiency->Write();
      }


      origplot_rate->Write();
      origplot_eff->Write();
    }
  }

  //f_out->Close();

}
