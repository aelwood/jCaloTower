void plotSums(){
  //TFile * f_ttbar= new TFile("ttbar-output-2014-06-22.root");
  TFile * f= new TFile("./sumsTest.root");
  std::vector<TString> sum;
  //sum.push_back("HT");
  //sum.push_back("MHT");
  sum.push_back("MHTX");
  sum.push_back("MHTY");
  //jetType.push_back("calib_gct");
  int i = -1;
  for (iSum = sum.begin();iSum != sum.end(); iSum++)
  {
    i++;
    std::cout << "arb"+*iSum+"/"+*iSum+"_5400_calib_nopus" << std::endl;
    TH1D* nopus = f->Get("arb"+*iSum+"/"+*iSum+"_5400_calib_nopus");
    TH1D* nopusseed = f->Get("arb"+*iSum+"/"+*iSum+"_5450_calib_nopus");
    TH1D* donutseed = f->Get("arb"+*iSum+"/"+*iSum+"_5450_calib_donut");
    TH1D* global = f->Get("arb"+*iSum+"/"+*iSum+"_5400_calib_global");
    TH1D* gen = f->Get("arb"+*iSum+"/"+*iSum+"_ak4_gen");


    TLegend* leg = new TLegend(0.55,0.5,0.85,0.8);
    leg->SetFillColor(0);
    TCanvas * c = new TCanvas("Sum "+*iSum+" (p_{T} ","",600,600);

    c->cd();
    nopus->GetXaxis()->SetTitle(*iSum+"/GeV");
    nopus->SetTitle("");
    gStyle->SetOptStat(0);
    nopus->GetXaxis()->SetTitleOffset(1.2);
    //nopus->GetYaxis()->SetTitle("Efficiency for jet "+sum.at(i));
    // nopus->GetYaxis()->SetTitleOffset(1.2);
    nopus->SetLineColor(1);
    nopus->GetXaxis()->SetRangeUser(-500,500);
    nopus->GetYaxis()->SetRangeUser(0,10000);
    nopusseed->SetLineStyle(2);
    donutseed->SetLineColor(2);
    donutseed->SetMarkerColor(2);
    global->SetLineColor(4);
    global->SetMarkerColor(4);
    gen->SetLineColor(8);
    nopus->Draw();
    nopusseed->Draw("same");
    donutseed->Draw("same");
    global->Draw("same");
    gen->Draw("same");
    leg->AddEntry(nopus,"No PUS","l");
    leg->AddEntry(nopusseed,"No PUS (Seed 5)","l");
    leg->AddEntry(donutseed,"Donut Sub (Seed 5)","l");
    leg->AddEntry(global,"Global Sub","l");
    leg->AddEntry(gen,"Gen","l");
    leg->Draw("L");
    c->SaveAs("output/cmsweek/sums_"+*iSum+".png");
  }
  return;
}
