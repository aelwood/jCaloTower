void plotRateEff(){

  std::vector<TString> jettype;
  //jettype.push_back("5450");
  std::vector<TString> jetnum;
  //jetnum.push_back("alljet");
  jetnum.push_back("0"); 
  TFile* f = TFile::Open("ratePlotsEff.root");

  for(auto iJet = jetnum.begin(); iJet!=jetnum.end();iJet++){

    TGraphAsymmErrors* nopus = f->Get("5400_calib_nopus/rate_efficiency");
    TGraphAsymmErrors* nopusseed = f->Get("5450_calib_nopus/rate_efficiency");
    TGraphAsymmErrors* donutseed = f->Get("5450_calib_donut/rate_efficiency");
    TGraphAsymmErrors* global = f->Get("5400_calib_global/rate_efficiency");
    //TGraphAsymmErrors* gct = f->Get("gct_calib/rate_efficiency"+*iJet);

    TMultiGraph * hs = new TMultiGraph();

    TLegend* leg = new TLegend(0.2,0.5,0.5,0.8);
    leg->SetFillColor(0);
    TCanvas * c = new TCanvas("Turn on Curve "+*iJet+" (p_{T} ","",600,600);

    c->cd();

    nopus->SetLineColor(1);
    nopusseed->SetLineStyle(2);
    //nopus->Draw("alp");

    donutseed->SetLineColor(2);
    donutseed->SetMarkerColor(2);
    //donut->Draw("lp same");

    global->SetLineColor(4);
    global->SetMarkerColor(4);
    //if(*iPt="40") {gct->SetLineColor(8);}
    //global->Draw("lp same");
    //gct->SetLineColor(8);
    //gct->SetMarkerColor(8);
/*    for (int i=0; i < global->GetN(); i++)
    {
      if (global->GetX()[i] < 0.1)
      {
	global->RemovePoint(i);
      }
    }
    for (int i=0; i < global->GetN(); i++)
    {
      if (global->GetX()[i] < 0.1)
      {
//	std::cout<< global->GetX()[i] << std::endl;
      } 
    }*/ 
    //global->SetMinimum(0.5);
    hs->Add(nopus,"lp");
    hs->Add(nopusseed,"lp");
    hs->Add(donutseed,"lp");
    hs->Add(global,"lp");
    //hs->Add(gct,"lp");

    hs->Draw("a");
    //hs->GetXaxis()->SetRangeUser(0.5,1);
    hs->GetXaxis()->SetTitle("Efficiency");
    hs->GetXaxis()->SetTitleOffset(1.2);
    //hs->GetXaxis()->SetRangeUser(0.94,0.98);
    hs->GetYaxis()->SetTitle("Rate");
    hs->GetYaxis()->SetTitleOffset(1.2);
    hs->GetYaxis()->SetRangeUser(0,10000);
    leg->AddEntry(nopus,"No PUS","l");
    leg->AddEntry(nopusseed,"No PUS (Seed 5)","l");
    leg->AddEntry(donutseed,"Donut Sub (Seed 5)","l");
    leg->AddEntry(global,"Global Sub","l");
    //leg->AddEntry(gct,"GCT","l");

    leg->Draw("L");


    c->SaveAs("output/cmsweek/rateseff1.png");
  }
}
