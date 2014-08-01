void rms(){
  TFile * f_ttbar= new TFile("/afs/cern.ch/work/m/mcitron/public/TTBAR/140622/ttbar_output.root");
  TFile * f_neutrino= new TFile("output/neutrino-output-2014-06-23.root");
  TFile * f_out = new TFile("rms.root","recreate");
  TCut matchedcut = "jetMatchedPt_5450_nopus>25";
  TCut unmatchedcut = "jetMatchedPt_5450_nopus==-1";
  TCut ptcut = "jetPt_5450_nopus<50&&jetPt_5450_nopus>30";
  TTree * tree_ttbar = f_ttbar->Get("demo/L1Tree");    
  TTree * tree_neutrino = f_neutrino->Get("demo/L1Tree");    

  tree_ttbar->Draw("jetRms_5450_nopus>>rmsmatched",matchedcut&&ptcut,"norm");
  TH1F *test = (TH1F*)gPad->GetPrimitive("rmsmatched");
  test->Write();

  tree_ttbar->Draw("jetRms_5450_nopus>>rmsunmatched",unmatchedcut&&ptcut,"norm");
  TH1F *test2 = (TH1F*)gPad->GetPrimitive("rmsunmatched");
  test2->Write();

  tree_neutrino->Draw("jetRms_5450_nopus>>rmsneut",ptcut,"norm");
  TH1F *test3 = (TH1F*)gPad->GetPrimitive("rmsneut");
  test3->Write();
}
