#include <utility>
void plotRateEff(){
/*
  std::vector<TString> jetnum;
  jetnum.push_back("jet0"); 
  jetnum.push_back("jet3"); 
  jetnum.push_back("ht");
*/
  std::vector<TString> histDir;
  std::vector<TString> xName;
  std::vector<TString> yName;
  std::vector< double > xLimitsLow;
  std::vector< double > xLimitsHigh;
  std::vector< double > yLimitsLow;
  std::vector< double > yLimitsHigh;

  histDir.push_back("rate_eff/rate_efficiency_jet0"); 
  xName.push_back("Efficiency");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(0.8);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(30000.);

  histDir.push_back("rate_eff/rate_efficiency_jet1"); 
  xName.push_back("Efficiency");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(0.8);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(30000.);

  histDir.push_back("rate_eff/rate_efficiency_jet3"); 
  xName.push_back("Efficiency");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.5); xLimitsHigh.push_back(1.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(30000.);

  histDir.push_back("rate_eff/rate_efficiency_ht");
  xName.push_back("Efficiency");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.5); xLimitsHigh.push_back(1.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(30000.);

  histDir.push_back("rate_eff/rate_efficiency_mht");
  xName.push_back("Efficiency");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.7); xLimitsHigh.push_back(1.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(30000.);

  histDir.push_back("rate/nvtx_ptCut_0");
  xName.push_back("NInts");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(70.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(100000.);

  histDir.push_back("rate/nvtx_ptCut_3");
  xName.push_back("NInts");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(70.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(100000.);
/*
  histDir.push_back("rate/Rate_0");
  xName.push_back("Cut");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(1000.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1000000.);
  
  histDir.push_back("rate/Rate_3");
  xName.push_back("Cut");
  yName.push_back("Rate");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(600.);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1000000.);
*/
  histDir.push_back("efficiency/nvtx_ptCut_0");
  xName.push_back("NInts");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(70.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("efficiency/nvtx_ptCut_3");
  xName.push_back("NInts");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(70.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("jetTurnons/turnon_0_50.");
  xName.push_back("Gen pT");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(400.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("jetTurnons/turnon_0_100.");
  xName.push_back("Gen pT");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(400.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("jetTurnons/turnon_0_150.");
  xName.push_back("Gen pT");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(400.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("jetTurnons/turnon_3_50.");
  xName.push_back("Gen pT");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(400.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("jetTurnons/turnon_3_100.");
  xName.push_back("Gen pT");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(400.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("jetTurnons/turnon_3_150.");
  xName.push_back("Gen pT");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(400.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("sums/ht_200.");
  xName.push_back("Gen pT");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(700.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);

  histDir.push_back("sums/mht_200.");
  xName.push_back("Gen pT");
  yName.push_back("Efficiency");
  xLimitsLow.push_back(0.); xLimitsHigh.push_back(700.0);
  yLimitsLow.push_back(0.); yLimitsHigh.push_back(1.);


  TFile* f = TFile::Open("../jetPlots.root");
  //TFile* f = TFile::Open("../test.root");

  int i=0;
  for(auto iHist = histDir.begin(); iHist!=histDir.end();iHist++){

    std::cout << "Starting " << iHist->Data() << std::endl;

    TGraphAsymmErrors* nopus = f->Get("calib_s0_nopus/"+*iHist);
    TGraphAsymmErrors* nopusseed = f->Get("calib_s5_nopus/"+*iHist);
    TGraphAsymmErrors* nopuscseed = f->Get("calib_c10_nopus/"+*iHist);
    TGraphAsymmErrors* donut = f->Get("calib_s0_donut/"+*iHist);
    TGraphAsymmErrors* donutseed = f->Get("calib_s5_donut/"+*iHist);
    TGraphAsymmErrors* donutcseed = f->Get("calib_c10_donut/"+*iHist);
    TGraphAsymmErrors* chunkyseed = f->Get("calib_s5_chunky/"+*iHist);
    TGraphAsymmErrors* tsup1seed = f->Get("calib_s5_tsup1/"+*iHist);
    TGraphAsymmErrors* tsup2seed = f->Get("calib_s5_tsup2/"+*iHist);
    TGraphAsymmErrors* global = f->Get("calib_s0_global/"+*iHist);
    TGraphAsymmErrors* globalseed = f->Get("calib_s5_global/"+*iHist);
    TGraphAsymmErrors* uct = f->Get("calib_uct/"+*iHist);
    TGraphAsymmErrors* gct = f->Get("calib_gct/"+*iHist);
    TGraphAsymmErrors* met;
    if(*iHist=="rate_eff/rate_efficiency_mht") met=f->Get("met/rate_eff/rate_efficiency_mht");

    TMultiGraph * hs = new TMultiGraph();

    TLegend* leg = new TLegend(0.2,0.5,0.5,0.8);
    leg->SetFillColor(0);
    TCanvas * c = new TCanvas("c","",600,600);

    c->cd();

    if(*iHist=="rate_eff/rate_efficiency_mht"){
      met->SetLineColor(13);
      met->SetMarkerColor(13);
    }

    nopus->SetLineColor(1);
    nopus->SetMarkerColor(1);
    nopus->SetLineStyle(2);
    nopusseed->SetLineColor(1);
    nopusseed->SetMarkerColor(1);
    nopuscseed->SetLineColor(1);
    nopuscseed->SetMarkerColor(1);
    nopuscseed->SetLineStyle(3);
    //nopus->Draw("alp");

    donut->SetLineColor(2);
    donut->SetMarkerColor(2);
    donut->SetLineStyle(2);
    donutseed->SetLineColor(2);
    donutseed->SetMarkerColor(2);
    donutcseed->SetLineColor(2);
    donutcseed->SetMarkerColor(2);
    donutcseed->SetLineStyle(3);
    //donut->Draw("lp same");

    global->SetLineColor(4);
    global->SetMarkerColor(4);
    global->SetLineStyle(2);
    globalseed->SetLineColor(4);
    globalseed->SetMarkerColor(4);

    chunkyseed->SetLineColor(6);
    chunkyseed->SetMarkerColor(6);

    tsup1seed->SetLineColor(44);
    tsup1seed->SetMarkerColor(44);

    tsup2seed->SetLineColor(46);
    tsup2seed->SetMarkerColor(46);

    uct->SetLineColor(8);
    uct->SetMarkerColor(8);

    gct->SetLineColor(8);
    gct->SetMarkerColor(8);
    gct->SetLineStyle(2);

    hs->Add(nopus,"lp");
    hs->Add(nopusseed,"lp");
    hs->Add(donutseed,"lp");
    hs->Add(donut,"lp");
    hs->Add(global,"lp");
    hs->Add(globalseed,"lp");
    hs->Add(chunkyseed,"lp");
    hs->Add(tsup1seed,"lp");
    hs->Add(tsup2seed,"lp");
    hs->Add(uct,"lp");
    hs->Add(gct,"lp");

    if(*iHist=="rate_eff/rate_efficiency_mht") hs->Add(met,"lp");

    hs->Draw("a");
    hs->GetXaxis()->SetTitle(xName[i]);
    hs->GetXaxis()->SetTitleOffset(1.2);
    hs->GetXaxis()->SetRangeUser(xLimitsLow[i],xLimitsHigh[i]);
    hs->GetYaxis()->SetTitle(yName[i]);
    hs->GetYaxis()->SetTitleOffset(2);
    hs->GetYaxis()->SetRangeUser(yLimitsLow[i],yLimitsHigh[i]);
    leg->AddEntry(nopus,"No PUS","l");
    leg->AddEntry(nopusseed,"No PUS (Seed 5)","l");
    leg->AddEntry(donut,"Donut Sub","l");
    leg->AddEntry(donutseed,"Donut Sub (Seed 5)","l");
    leg->AddEntry(global,"Global Sub","l");
    leg->AddEntry(globalseed,"Global Sub (Seed 5)","l");
    leg->AddEntry(chunkyseed,"Chunky Donut (Seed 5)","l");
    leg->AddEntry(tsup1seed,"TSup 1 (Seed 5)","l");
    leg->AddEntry(tsup2seed,"TSup 2 (Seed 5)","l");
    leg->AddEntry(gct,"GCT","l");
    leg->AddEntry(uct,"UCT","l");
    if(*iHist=="rate_eff/rate_efficiency_mht") leg->AddEntry(met,"MET","l");

    leg->Draw("L");


    c->SaveAs(*iHist+".png");
    c->SaveAs(*iHist+".root");

    i++;
  }
}
