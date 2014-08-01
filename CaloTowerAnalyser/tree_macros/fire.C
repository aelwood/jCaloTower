void fire(){
  TFile * f_in= new TFile("/afs/cern.ch/work/m/mcitron/public/TTBAR/140622/ttbar_output.root");
  TFile * f_out= new TFile("./fireTest.root","recreate");
  TTree * tree = f_in->Get("demo/L1Tree;1");
  TString bins ="(50,-0.95,99.5,19,0,1)";
  TDirectory * Profile = f_out->mkdir("Profile");
  Profile->cd();
  tree->Draw("(jetOuterStripsEnergy_6_5450_3_strips_nopus+jetOuterStripsEnergy_5_5450_3_strips_nopus)/(jetOuterStripsArea_6_5450_3_strips_nopus+jetOuterStripsArea_5_5450_3_strips_nopus):mNPV>>threestrips","","prof");
  TProfile * threeStrips = (TProfile*)gPad->GetPrimitive("threestrips");
  threeStrips->Write(); 
  tree->Draw("(jetOuterStripsEnergy_6_5450_squares_nopus+jetOuterStripsEnergy_5_5450_squares_nopus)/(jetOuterStripsArea_6_5450_squares_nopus+jetOuterStripsArea_5_5450_squares_nopus):mNPV>>squares","","prof");
  TProfile * squares = (TProfile*)gPad->GetPrimitive("squares");
  squares->Write(); 
  tree->Draw("(jetOuterStripsEnergy_3_5450_2_strips_nopus+jetOuterStripsEnergy_4_5450_2_strips_nopus)/(jetOuterStripsArea_4_5450_2_strips_nopus+jetOuterStripsArea_3_5450_2_strips_nopus):mNPV>>twostrips","","prof");
  TProfile * twoStrips = (TProfile*)gPad->GetPrimitive("twostrips");
  twoStrips->Write(); 
  tree->Draw("(jetOuterStripsEnergy_1_5450_nopus+jetOuterStripsEnergy_2_5450_nopus)/(jetOuterStripsArea_1_5450_nopus+jetOuterStripsArea_2_5450_nopus):mNPV>>onestrips","","prof");
  TProfile * oneStrips = (TProfile*)gPad->GetPrimitive("onestrips");
  oneStrips->Write(); 
  tree->Draw("medianRho:mNPV>>median","","prof");
  TProfile * median = (TProfile*)gPad->GetPrimitive("median");
  median->Write(); 

  TDirectory * Hist = f_out->mkdir("Hist");
  Hist->cd();
  tree->Draw("(jetOuterStripsEnergy_6_5450_3_strips_nopus+jetOuterStripsEnergy_5_5450_3_strips_nopus)/(jetOuterStripsArea_6_5450_3_strips_nopus+jetOuterStripsArea_5_5450_3_strips_nopus):mNPV>>threestrips"+bins,"","colz");
  TH2D * threeStripsHist = (TH2D*)gPad->GetPrimitive("threestrips");
  threeStripsHist->Write(); 
  tree->Draw("(jetOuterStripsEnergy_6_5450_squares_nopus+jetOuterStripsEnergy_5_5450_squares_nopus)/(jetOuterStripsArea_6_5450_squares_nopus+jetOuterStripsArea_5_5450_squares_nopus):mNPV>>squares"+bins,"","colz");
  TProfile * squaresHist = (TProfile*)gPad->GetPrimitive("squares");
  squaresHist->Write(); 
  tree->Draw("(jetOuterStripsEnergy_3_5450_2_strips_nopus+jetOuterStripsEnergy_4_5450_2_strips_nopus)/(jetOuterStripsArea_4_5450_2_strips_nopus+jetOuterStripsArea_3_5450_2_strips_nopus):mNPV>>twostrips"+bins,"","colz");
  TH2D * twoStripsHist = (TH2D*)gPad->GetPrimitive("twostrips");
  twoStripsHist->Write(); 
  tree->Draw("(jetOuterStripsEnergy_1_5450_nopus+jetOuterStripsEnergy_2_5450_nopus)/(jetOuterStripsArea_1_5450_nopus+jetOuterStripsArea_2_5450_nopus):mNPV>>onestrips"+bins,"","colz");
  TH2D * oneStripsHist = (TH2D*)gPad->GetPrimitive("onestrips");
  oneStripsHist->Write(); 
  tree->Draw("medianRho:mNPV>>median"+bins,"","colz");
  TH2D * medianHist = (TH2D*)gPad->GetPrimitive("median");
  medianHist->Write(); 

  f_out->Close();
  return;
}
