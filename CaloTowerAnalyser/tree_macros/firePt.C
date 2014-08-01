void firePt(){
  TFile * f_in= new TFile("/afs/cern.ch/work/m/mcitron/public/TTBAR/140622/ttbar_output.root");
  TFile * f_out= new TFile("./fireTestPt.root","recreate");
  TTree * tree = f_in->Get("demo/L1Tree;1");
  TString bins ="(100,-0.95,99.5,100,-0.005,0.995)";
  TDirectory * Profile = f_out->mkdir("Profile");
  Profile->cd();
  TCut iso ="jetMinDR_5450_nopus>100";
  tree->Draw("jetArea_5450_3_strips_nopus*(jetOuterStripsEnergy_6_5450_3_strips_nopus+jetOuterStripsEnergy_5_5450_3_strips_nopus)/(jetOuterStripsArea_6_5450_3_strips_nopus+jetOuterStripsArea_5_5450_3_strips_nopus):jetPt_5450_nopus>>threestrips",iso,"profs");
  TProfile * threeStrips = (TProfile*)gPad->GetPrimitive("threestrips");
  threeStrips->Write(); 
  tree->Draw("jetArea_5450_squares_nopus*(jetOuterStripsEnergy_6_5450_squares_nopus+jetOuterStripsEnergy_5_5450_squares_nopus)/(jetOuterStripsArea_6_5450_squares_nopus+jetOuterStripsArea_5_5450_squares_nopus):jetPt_5450_nopus>>squares","","profs");
  TProfile * squares = (TProfile*)gPad->GetPrimitive("squares");
  squares->Write(); 
  tree->Draw("jetArea_5450_2_strips_nopus*(jetOuterStripsEnergy_3_5450_2_strips_nopus+jetOuterStripsEnergy_4_5450_2_strips_nopus)/(jetOuterStripsArea_4_5450_2_strips_nopus+jetOuterStripsArea_3_5450_2_strips_nopus):jetPt_5450_nopus>>twostrips",iso,"profs");
  TProfile * twoStrips = (TProfile*)gPad->GetPrimitive("twostrips");
  twoStrips->Write(); 
  tree->Draw("jetArea_5450_nopus*(jetOuterStripsEnergy_1_5450_nopus+jetOuterStripsEnergy_2_5450_nopus)/(jetOuterStripsArea_1_5450_nopus+jetOuterStripsArea_2_5450_nopus):jetPt_5450_nopus>>onestrips",iso,"profs");
  TProfile * oneStrips = (TProfile*)gPad->GetPrimitive("onestrips");
  oneStrips->Write(); 
  tree->Draw("medianRho*jetArea_5450_nopus:jetPt_5450_nopus>>median",iso,"profs");
  TProfile * median = (TProfile*)gPad->GetPrimitive("median");
  median->Write(); 

  TDirectory * Hist = f_out->mkdir("Hist");
  Hist->cd();
  tree->Draw("jetArea_5450_3_strips_nopus*(jetOuterStripsEnergy_6_5450_3_strips_nopus+jetOuterStripsEnergy_5_5450_3_strips_nopus)/(jetOuterStripsArea_6_5450_3_strips_nopus+jetOuterStripsArea_5_5450_3_strips_nopus):jetPt_5450_nopus>>threestrips"+bins,"","colz");
  TH2D * threeStripsHist = (TH2D*)gPad->GetPrimitive("threestrips");
  threeStripsHist->Write(); 
  tree->Draw("jetArea_5450_squares_nopus*(jetOuterStripsEnergy_6_5450_squares_nopus+jetOuterStripsEnergy_5_5450_squares_nopus)/(jetOuterStripsArea_6_5450_squares_nopus+jetOuterStripsArea_5_5450_squares_nopus):jetPt_5450_nopus>>squares","","colz");
  TProfile * squaresHist = (TProfile*)gPad->GetPrimitive("squares");
  squaresHist->Write(); 
  tree->Draw("jetArea_5450_2_strips_nopus*(jetOuterStripsEnergy_3_5450_2_strips_nopus+jetOuterStripsEnergy_4_5450_2_strips_nopus)/(jetOuterStripsArea_4_5450_2_strips_nopus+jetOuterStripsArea_3_5450_2_strips_nopus):jetPt_5450_nopus>>twostrips"+bins,"","colz");
  TH2D * twoStripsHist = (TH2D*)gPad->GetPrimitive("twostrips");
  twoStripsHist->Write(); 
  tree->Draw("jetArea_5450_nopus*(jetOuterStripsEnergy_1_5450_nopus+jetOuterStripsEnergy_2_5450_nopus)/(jetOuterStripsArea_1_5450_nopus+jetOuterStripsArea_2_5450_nopus):jetPt_5450_nopus>>onestrips"+bins,"","colz");
  TH2D * oneStripsHist = (TH2D*)gPad->GetPrimitive("onestrips");
  oneStripsHist->Write(); 
  tree->Draw("medianRho*jetArea_5450_nopus:jetPt_5450_nopus>>median"+bins,"","colz");
  TH2D * medianHist = (TH2D*)gPad->GetPrimitive("median");
  medianHist->Write(); 

  f_out->Close();
  return;
}
