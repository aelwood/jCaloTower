#include "TCut.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1.h"
#include "TProfile.h"
#include <iostream>

TH1F * makeCumu(TH1F*,double);

void makeTowerResponse(){
  TFile * f_ttbar= new TFile("output/ttbar-output-PU40-2014-07-09.root");
  TFile * f_out= new TFile("./studyTowers.root","recreate");
  TTree * tree_ttbar = (TTree *)f_ttbar->Get("demo/L1Tree");

  std::vector<TString> jetType;
  jetType.push_back("L1_for_Nick");
  std::vector<TString> towerLim;
  towerLim.push_back("Up1");
  towerLim.push_back("Up2");
  towerLim.push_back("Up3");

  TString bins = "(100,-0.5,99.5)";
  std::vector<TString> ptBins;
  ptBins.push_back("0");
  ptBins.push_back("40");
  ptBins.push_back("80");
  ptBins.push_back("120");
  ptBins.push_back("1000");
  std::vector<TString> etaBins;
  etaBins.push_back("-3");
  etaBins.push_back("-2");
  etaBins.push_back("2");
  etaBins.push_back("3");
  TString matchedPt = "25";

  for (std::vector<TString>::iterator iType = jetType.begin(); iType != jetType.end(); iType++)
  {
    TCut matchedcut = TCut("jetMatchedPt_"+*iType+">"+matchedPt);
    for (unsigned int j = 0;j < etaBins.size()-1; j++)
    {
      TCut jetetacut = TCut("jetEta_"+*iType+">"+etaBins.at(j)+" && jetEta_"+*iType+"<"+etaBins.at(j+1) );
      TDirectory * dir = f_out->mkdir("etaBin_"+etaBins.at(j)+"to"+etaBins.at(j+1));
      dir->cd();
      for (unsigned int i = 0;i < ptBins.size()-1; i++)
      {
	TCut jetptcut = TCut("jetPt_"+*iType+">"+ptBins.at(i)+" && jetPt_"+*iType+"<"+ptBins.at(i+1) );
	for (std::vector<TString>::iterator iTow = towerLim.begin(); iTow != towerLim.end(); iTow++)
	{

	  tree_ttbar->Draw("((jetPt_"+*iType+")-jetTowerEnergy"+*iTow+"_"+*iType+"-jetMatchedPt_"+*iType+")/jetMatchedPt_"+*iType+":mNPV>>"+*iType+*iTow+ptBins.at(i+1)+etaBins.at(j+1)+bins,matchedcut&&jetptcut&&jetetacut,"prof");
	  TProfile *test2 = (TProfile*)gDirectory->Get(*iType+*iTow+ptBins.at(i+1)+etaBins.at(j+1));
	  test2->SetName(*iType+"_"+*iTow+"_"+ptBins.at(i)+"to"+ptBins.at(i+1)+"_"+etaBins.at(j)+"to"+etaBins.at(j+1));
	  test2->GetXaxis()->SetTitle("Nint");
	  test2->GetYaxis()->SetTitle("Resolution");
	  std::cout << "HERE" << std::endl;
	  test2->Write();
	}
      }
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
