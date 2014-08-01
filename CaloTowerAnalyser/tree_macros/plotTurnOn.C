void plotTurnOn(){
  //TFile * f_ttbar= new TFile("ttbar-output-2014-06-22.root");
  TFile * f= new TFile("./turnOn.root");
  std::vector<TString> jetnum;
  //jetnum.push_back("0");
  //jetnum.push_back("1");
  //  //jetnum.push_back("2");
    jetnum.push_back("3");
  std::vector<TString> truejetnum;
  truejetnum.push_back("1");
  //  truejetnum.push_back("2");
  //  truejetnum.push_back("3");
  truejetnum.push_back("4");
  //jetType.push_back("calib_gct");
  std::vector<TString> jetcut;
  //jetcut.push_back("100");
  jetcut.push_back("50");
  int i = -1;
  for (iNum = jetnum.begin();iNum != jetnum.end(); iNum++)
  {
    for (iCut = jetcut.begin();iCut != jetcut.end(); iCut++)
    {
      i++;
      std::cout <<"5400_calib_nopus/"+*iNum+"_"+*iCut << std::endl;
      TGraphErrors* nopus = f->Get("5400_calib_nopus/"+*iNum+"_"+*iCut);
      TGraphErrors* donutseed = f->Get("5450_calib_donut/"+*iNum+"_"+*iCut);
      TGraphErrors* nopusseed = f->Get("5450_calib_nopus/"+*iNum+"_"+*iCut);
      TGraphErrors* global = f->Get("5400_calib_global/"+*iNum+"_"+*iCut);
      TGraphErrors* gct = f->Get("gct_calib_gen/"+*iNum+"_"+*iCut);

      TMultiGraph * hs = new TMultiGraph();
      TLegend* leg = new TLegend(0.5,0.2,0.8,0.5);
      leg->SetFillColor(0);
      TCanvas * c = new TCanvas("Turn on Curve "+*iNum+" (p_{T} "+*iCut+")","",600,600);

      c->cd();
      hs->SetTitle("");
      gStyle->SetOptStat(0);


      nopus->SetLineColor(1);
      nopusseed->SetLineStyle(2);
      donutseed->SetLineColor(2);
      donutseed->SetMarkerColor(2);
      global->SetLineColor(4);
      global->SetMarkerColor(4);
      gct->SetLineColor(8);

      hs->Add(nopus,"lp");
      hs->Add(nopusseed,"lp");
      hs->Add(donutseed,"lp");
      hs->Add(global,"lp");
      hs->Add(gct,"lp");

      hs->Draw("a");
      hs->GetYaxis()->SetTitle("Efficiency (p_{T} cut "+*iCut+" GeV)");
      hs->GetYaxis()->SetTitleOffset(1.4);
      hs->GetXaxis()->SetTitle("p_{T}/GeV");
      hs->GetXaxis()->SetTitleOffset(1.4);
      hs->GetXaxis()->SetRangeUser(0,250);

      leg->AddEntry(nopus,"No PUS","l");
      leg->AddEntry(nopusseed,"No PUS (Seed 5)","l");
      leg->AddEntry(donutseed,"Donut Sub (Seed 5)","l");
      leg->AddEntry(global,"Global Sub","l");
      leg->AddEntry(gct,"GCT","l");
      leg->Draw("L");
      c->SaveAs("output/cmsweek/turnon"+*iNum+"_"+*iCut+".png");
    }
  }
  return;
}
