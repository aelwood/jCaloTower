#include "TCut.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"

TH1F * makeCumu(TH1F*,double);

void makeSeedStudy(){
  TFile * f_ttbar= new TFile("/home/matthew/ttbar_output.root");
  TFile * f_out= new TFile("./studySeed.root","recreate");
  TTree * tree_ttbar = (TTree *)f_ttbar->Get("demo/L1Tree");

  std::vector<TString> jetType;
  jetType.push_back("L1_for_Nick");


  TString bins = "(1000,-0.5,999.5)";

  for (std::vector<TString>::iterator iType = jetType.begin(); iType != jetType.end(); iType++)
  {
    std::vector<TString> seedSize;
    seedSize.push_back("jetRingSumsEnergy_0_"+*iType);
    seedSize.push_back("jetRingSumsEnergy_0_"+*iType+"+ jetRingSumsEnergy_1_"+*iType);

    TCut unmatchedcut = TCut("jetMatchedPt_"+*iType+"!=-1");
    TCut matchedcut = TCut("jetMatchedPt_"+*iType+">25");
    TCut jetptcut = TCut("jetPt_"+*iType+">25");

    for (std::vector<TString>::iterator iSeed = seedSize.begin(); iSeed != seedSize.end(); iSeed++)
    {

      tree_ttbar->Draw(*iSeed+">>"+*iType+*iSeed+"unmatch"+bins,unmatchedcut,"");
      TH1F *test = (TH1F*)gDirectory->Get(*iType+*iSeed+"unmatch");
      test->Write();
      double overallNorm = test->GetEntries();
      test->SetName(*iType+"_"+*iSeed+"unmatch_Rate");
      TH1F* cumuplot = makeCumu(test,overallNorm);
      cumuplot->Write();

      tree_ttbar->Draw(*iSeed+">>"+*iType+*iSeed+"match"+bins,matchedcut,"");
      TH1F *test2 = (TH1F*)gDirectory->Get(*iType+*iSeed+"match");
      test2->Write();
      overallNorm = test2->GetEntries();
      test2->SetName(*iType+"_"+*iSeed+"match_Rate");
      TH1F* cumuplot2 = makeCumu(test2,overallNorm);
      cumuplot2->Write();
    }
  }
  f_out->Close();
  return;
}

TH1F * makeCumu(TH1F * input, double overallNorm){

  TH1F * output = new TH1F(*input);
  //output=input;
//  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  int nXbins = input->GetNbinsX();
  int dummy = 0;
  for (int xbins = 0; xbins <= nXbins+1; xbins++)
  {
    dummy += input->GetBinContent(nXbins+1-xbins);
    output->SetBinContent((nXbins+1-xbins),((double)dummy)/overallNorm);
  }

  return output;
}
