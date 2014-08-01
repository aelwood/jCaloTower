void plotRate(){
  //TFile * f_ttbar= new TFile("ttbar-output-2014-06-22.root");
  TFile * f= new TFile("./rateTest.root");
  std::vector<TString> jetnum;
  //jetnum.push_back("0");
  //jetnum.push_back("1");
  //jetnum.push_back("2");
  jetnum.push_back("3");
  std::vector<TString> truejetnum;
  //truejetnum.push_back("1");
//  truejetnum.push_back("2");
//  truejetnum.push_back("3");
  truejetnum.push_back("4");
  //jetType.push_back("calib_gct");
  int i = -1;
  for (iNum = jetnum.begin();iNum != jetnum.end(); iNum++)
  {
    i++;
    std::cout <<"jetNumber_"+*iNum+"/5400_calib_nopus_"+*iNum+"_Rate" << std::endl;
    TH1D* nopus = f->Get("jetNumber_"+*iNum+"/5400_calib_nopus_"+*iNum+"_Rate");
    TH1D* donutseed = f->Get("jetNumber_"+*iNum+"/5450_calib_donut_"+*iNum+"_Rate");
    TH1D* nopusseed = f->Get("jetNumber_"+*iNum+"/5450_calib_nopus_"+*iNum+"_Rate");
    TH1D* global = f->Get("jetNumber_"+*iNum+"/5400_calib_global_"+*iNum+"_Rate");
    TH1D* gct = f->Get("jetNumber_"+*iNum+"/gct_calib_gen_"+*iNum+"_Rate");


    TLegend* leg = new TLegend(0.55,0.55,0.85,0.85);
    leg->SetFillColor(0);
    TCanvas * c = new TCanvas("Turn on Curve "+*iNum+" (p_{T} ","",600,600);

    c->cd();
    nopus->GetXaxis()->SetTitle("Pt/GeV");
    nopus->SetTitle("");
    gStyle->SetOptStat(0);
    nopus->GetXaxis()->SetTitleOffset(1.4);
    nopus->GetYaxis()->SetTitle("Rate for jet "+truejetnum.at(i)+"/Hz");
    nopus->GetYaxis()->SetTitleOffset(1.4);
    nopus->SetLineColor(1);
    nopus->GetXaxis()->SetRangeUser(25,45);
    nopusseed->SetLineStyle(2);
    donutseed->SetLineColor(2);
    donutseed->SetMarkerColor(2);
    global->SetLineColor(4);
    gct->SetLineColor(8);
    global->SetMarkerColor(4);
    nopus->Draw();
    nopusseed->Draw("same");
    donutseed->Draw("same");
    global->Draw("same");
    gct->Draw("same");
    leg->AddEntry(nopus,"No PUS","l");
    leg->AddEntry(nopusseed,"No PUS (Seed 5)","l");
    leg->AddEntry(donutseed,"Donut Sub (Seed 5)","l");
    leg->AddEntry(global,"Global Sub","l");
    leg->AddEntry(gct,"GCT","l");
    leg->Draw("L");
    c->SaveAs("output/cmsweek/rate"+*iNum+".png");
  }
  return;
}
