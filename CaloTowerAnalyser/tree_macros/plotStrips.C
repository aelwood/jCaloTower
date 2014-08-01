void plotStrips(){
  //TFile * f_ttbar= new TFile("ttbar-output-2014-06-22.root");
  TFile * f= new TFile("./fireTest.root");
  std::vector<TString> strips;
  strips.push_back("onestrips");
  strips.push_back("twostrips");
  strips.push_back("threestrips");
  strips.push_back("squares");
  strips.push_back("median");
  for (iStrip = strips.begin();iStrip != strips.end(); iStrip++)
  {
    TProfile * tempP = f->Get("Profile/"+*iStrip);
    TH2F * tempH = f->Get("Hist/"+*iStrip);


    TCanvas * c = new TCanvas("Strips_"+*iStrip,"",600,600);

    c->cd();
    tempH->GetXaxis()->SetTitle("Number of Interactions");
    tempH->SetTitle(*iStrip);
    c->SetLogz();
    gStyle->SetOptStat(0);
    tempH->GetXaxis()->SetTitleOffset(1.4);
    tempH->GetYaxis()->SetTitleOffset(1.4);
    tempH->GetYaxis()->SetTitle("Energy Density/(GeV/Tower)");
    tempH->GetXaxis()->SetRangeUser(20,70);
    tempH->GetYaxis()->SetRangeUser(0,0.5);
    tempP->SetMarkerStyle(20);
    tempH->Draw("colz");
    tempP->Draw("same");
    c->SaveAs("output/cmsweek/strips_"+*iStrip+".png");
  }
  return;
}
