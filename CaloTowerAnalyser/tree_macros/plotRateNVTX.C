void plotRateNVTX(){
  //TFile * f_ttbar= new TFile("ttbar-output-2014-06-22.root");
  TFile * f= new TFile("./rateTestNVTX.root");
  std::vector<TString> jetnum;
  jetnum.push_back("0");
  //jetnum.push_back("1");
  //jetnum.push_back("2");
//  jetnum.push_back("3");
  std::vector<TString> truejetnum;
  truejetnum.push_back("1");
//  truejetnum.push_back("2");
//  truejetnum.push_back("3");
  //truejetnum.push_back("4");
  //jetType.push_back("calib_gct");
  int i = -1;
  for (iNum = jetnum.begin();iNum != jetnum.end(); iNum++)
  {
    i++;
    std::cout <<"jetNumber_"+*iNum+"/ptCut5400_calib_nopus"+*iNum<< std::endl;
    TGraphErrors* nopus = f->Get("jetNumber_"+*iNum+"/ptCut5400_calib_nopus"+*iNum);
    TGraphErrors* donutseed = f->Get("jetNumber_"+*iNum+"/ptCut5450_calib_donut"+*iNum);
    TGraphErrors* nopusseed = f->Get("jetNumber_"+*iNum+"/ptCut5450_calib_nopus"+*iNum);
    TGraphErrors* global = f->Get("jetNumber_"+*iNum+"/ptCut5400_calib_global"+*iNum);

    TMultiGraph * hs = new TMultiGraph();
    TLegend* leg = new TLegend(0.5,0.59,0.8,0.89);
    leg->SetFillColor(0);
    TCanvas * c = new TCanvas("Turn on Curve "+*iNum+" (p_{T} ","",600,600);

    c->cd();
    hs->SetTitle("");
    gStyle->SetOptStat(0);


    nopus->SetLineColor(1);
    nopusseed->SetLineStyle(2);
    donutseed->SetLineColor(2);
    donutseed->SetMarkerColor(2);
    global->SetLineColor(4);
    global->SetMarkerColor(4);

    hs->Add(nopus,"lp");
    hs->Add(nopusseed,"lp");
    hs->Add(donutseed,"lp");
    hs->Add(global,"lp");

    hs->Draw("a");
    hs->GetXaxis()->SetTitle("Ninteractions");
    hs->GetXaxis()->SetTitleOffset(1.2);
    hs->GetYaxis()->SetTitle("Rate for jet "+truejetnum.at(i)+"(30GeV cut)");
    hs->GetYaxis()->SetTitleOffset(1.4);
    hs->GetYaxis()->SetRangeUser(0,1);
    hs->GetXaxis()->SetRangeUser(15,60);

    leg->AddEntry(nopus,"No PUS","l");
    leg->AddEntry(nopusseed,"No PUS (Seed 5)","l");
    leg->AddEntry(donutseed,"Donut Sub (Seed 5)","l");
    leg->AddEntry(global,"Global Sub","l");
    leg->Draw("L");
    c->SaveAs("output/cmsweek/rateNVTX"+*iNum+".png");
  }
  return;
}
