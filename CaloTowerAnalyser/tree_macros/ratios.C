void ratios(){
TFile * f_neut= new TFile("output/neutrino-output-2014-06-23.root");
TFile * f_ttbar= new TFile("/afs/cern.ch/work/m/mcitron/public/TTBAR/140622/ttbar_output.root");

TTree * tree_ttbar = f_ttbar->Get("demo/L1Tree;");
TTree * tree_neutrino = f_neut->Get("demo/L1Tree;");
TFile * f_out= new TFile("./ratio_test.root","recreate");
f_out->cd();
//tree_neutrino->Draw("jetRingSumsEnergy_1_5400_nopus/jetRingSumsEnergy_0_5400_nopus","jetRingSumsEnergy_0_5400_nopus>5&&jetPt_5400_nopus>10","");
//tree_ttbar->Draw("jetRingSumsEnergy_1_5400_nopus/jetRingSumsEnergy_0_5400_nopus","jetMatchedPt_5400_nopus>50&&jetRingSumsEnergy_0_5400_nopus>5","same");
TCut ring0cut = "jetRingSumsEnergy_0_5400_nopus>=5";
TCut ring1cut = "jetRingSumsEnergy_1_5400_nopus>=1";
TCut ring2cut = "jetRingSumsEnergy_2_5400_nopus>=1";
TCut ring3cut = "jetRingSumsEnergy_3_5400_nopus>=1";
TCut ring4cut = "jetRingSumsEnergy_4_5400_nopus>=1";
//TCut matchedcut = "";
TCut matchedcut = "jetMatchedPt_5400_nopus>25";
TCut unmatchedcut = "jetMatchedPt_5400_nopus==-1";
TCut ptcut = "jetPt_5400_nopus>10";
TString bins = "(25,0,1)";

//tree_ttbar->Draw("(jetRingSumsHighest_2_5400_nopus)/jetRingSumsHighest_0_5400_nopus:jetMatchedPt_5400_nopus",ring0cut&&ptcut&&matchedcut,"profs");
//tree_ttbar->Draw("(jetRingSumsHighest_1_5400_nopus)/jetRingSumsHighest_0_5400_nopus:jetMatchedPt_5400_nopus",ring0cut&&ptcut&&matchedcut,"sameprofs");
//test->Draw("colz");

tree_ttbar->Draw("(jetRingSumsHighest_4_5400_nopus)/jetRingSumsHighest_0_5400_nopus>>ttbar4r0"+bins,ring0cut&&matchedcut&&ptcut,"norm");
TH1F *ttbar4r0 = (TH1F*)gPad->GetPrimitive("ttbar4r0");
tree_ttbar->Draw("(jetRingSumsHighest_4_5400_nopus)/jetRingSumsHighest_0_5400_nopus>>ttbar4r0PU"+bins,ring0cut&&unmatchedcut&&ptcut,"norm");
TH1F *ttbar4r0PU = (TH1F*)gPad->GetPrimitive("ttbar4r0PU");
ttbar4r0->SetTitle("");
ttbar4r0->GetXaxis()->SetTitle("Ring 4 Over Ring 0");
ttbar4r0PU->SetTitle("");
ttbar4r0PU->GetXaxis()->SetTitle("Ring 4 Over Ring 0");
ttbar4r0->Write();
ttbar4r0PU->Write();

f_out->Close();
return;

}

/*
tree_ttbar->Draw("jetRingSumsEnergy_1_5400_nopus/jetRingSumsEnergy_0_5400_nopus>>ttbar1r0"+bins,ring0cut&&matchedcut,"norm");
//tree_ttbar->Draw("(jetRingSumsEnergy_1_5400_nopus+jetRingSumsEnergy_0_5400_nopus)/(jetRingSumsEnergy_2_5400_nopus+jetRingSumsEnergy_3_5400_nopus)>>ttbar1r0"+bins,(ring2cut||ring3cut)&&matchedcut&&ptcut,"norm");
TH1F *ttbar1r0 = (TH1F*)gPad->GetPrimitive("ttbar1r0");
//tree_neutrino->Draw("(jetRingSumsEnergy_1_5400_nopus+jetRingSumsEnergy_0_5400_nopus)/(jetRingSumsEnergy_2_5400_nopus+jetRingSumsEnergy_3_5400_nopus)>>neutr1r0"+bins,(ring2cut||ring3cut)&&ptcut,"norm");
tree_neutrino->Draw("(jetRingSumsEnergy_1_5400_nopus)/(jetRingSumsEnergy_0_5400_nopus)>>neutr1r0"+bins,(ring0cut)&&ptcut,"norm");
TH1F *neutr1r0 = (TH1F*)gPad->GetPrimitive("neutr1r0");

tree_ttbar->Draw("jetRingSumsEnergy_2_5400_nopus/jetRingSumsEnergy_1_5400_nopus>>ttbar2r1"+bins,ring1cut&&matchedcut,"norm");
TH1F *ttbar2r1 = (TH1F*)gPad->GetPrimitive("ttbar2r1");
tree_neutrino->Draw("jetRingSumsEnergy_2_5400_nopus/jetRingSumsEnergy_1_5400_nopus>>neutr2r1"+bins,ring1cut&&ptcut,"norm");
TH1F *neutr2r1 = (TH1F*)gPad->GetPrimitive("neutr2r1");

tree_ttbar->Draw("jetRingSumsEnergy_3_5400_nopus/jetRingSumsEnergy_2_5400_nopus>>ttbar3r2"+bins,ring2cut&&matchedcut,"norm");
TH1F *ttbar3r2 = (TH1F*)gPad->GetPrimitive("ttbar3r2");
tree_neutrino->Draw("jetRingSumsEnergy_3_5400_nopus/jetRingSumsEnergy_2_5400_nopus>>neutr3r2"+bins,ring2cut&&ptcut,"norm");
TH1F *neutr3r2 = (TH1F*)gPad->GetPrimitive("neutr3r2");

tree_ttbar->Draw("jetRingSumsEnergy_4_5400_nopus/jetRingSumsEnergy_3_5400_nopus>>ttbar4r3"+bins,ring3cut&&matchedcut,"norm");
TH1F *ttbar4r3 = (TH1F*)gPad->GetPrimitive("ttbar4r3");
tree_neutrino->Draw("jetRingSumsEnergy_3_5400_nopus/jetRingSumsEnergy_4_5400_nopus>>neutr4r3"+bins,ring3cut&&ptcut,"norm");
TH1F *neutr4r3 = (TH1F*)gPad->GetPrimitive("neutr4r3");
*/
