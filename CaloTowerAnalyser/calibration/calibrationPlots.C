#include "/afs/cern.ch/work/a/aelwood/trigger/jets/jadjet/CMSSW_6_2_0/src/SLHCUpgradeSimulations/L1CaloTrigger/interface/TriggerTowerGeometry_new.h"
#include "TFile.h"
#include "TH2D.h"
#include "TTree.h"
#include "TString.h"
#include "TDirectory.h"
#include <vector>
#include <iostream>

TString getEtaCut(int x, char* lim){
  TriggerTowerGeometry g;
  double xReal = g.eta(x);
  char buffer[20];
  sprintf(buffer,lim,xReal);
  return TString(buffer);
}

int calibrationPlots(){
  //Load files
  TFile* inFile = new TFile("/afs/cern.ch/work/a/aelwood/trigger/jets/jadjet/CMSSW_6_2_0/src/jCaloTower/CaloTowerAnalyser/JetMaker/jetTree.root");
  TTree* tree = (TTree*)inFile->Get("jetTree");

  TFile* outFile = new TFile("calibPlots.root","RECREATE");

  //Jet types
  std::vector<TString> jetType;
  jetType.push_back("s0_nopus");
  jetType.push_back("s0_donut");
  jetType.push_back("s0_global");
  jetType.push_back("s0_chunky");
  jetType.push_back("s0_tsup1");
  jetType.push_back("s0_tsup2");
  jetType.push_back("s0_tsup3");
  jetType.push_back("s5_nopus");
  jetType.push_back("s5_donut");
  jetType.push_back("s5_global");
  jetType.push_back("s5_chunky");
  jetType.push_back("s5_tsup1");
  jetType.push_back("s5_tsup2");
  jetType.push_back("s5_tsup3");
  jetType.push_back("c10_nopus");
  jetType.push_back("c10_donut");
  jetType.push_back("c10_global");
  jetType.push_back("c10_chunky");
  jetType.push_back("c10_tsup1");
  jetType.push_back("c10_tsup2");
  jetType.push_back("c10_tsup3");

  //Eta cuts
  //  if(inJetEta[i]>=g.eta(-28) && inJetEta[i]<g.eta(-21));
  std::vector<TString> etaCutsLow;
  std::vector<TString> etaCutsHigh;
  std::vector<TString> etaCutsName;
  etaCutsLow.push_back(getEtaCut(-28,">=%f"));
  etaCutsHigh.push_back(getEtaCut(-21,"<%f"));
  etaCutsName.push_back("Eta_m28_m21");
  etaCutsLow.push_back(getEtaCut(-21,">=%f"));
  etaCutsHigh.push_back(getEtaCut(-14,"<%f"));
  etaCutsName.push_back("Eta_m21_m14");
  etaCutsLow.push_back(getEtaCut(-14,">=%f"));
  etaCutsHigh.push_back(getEtaCut(-7,"<%f"));
  etaCutsName.push_back("Eta_m14_m7");
  etaCutsLow.push_back(getEtaCut(-7,">=%f"));
  etaCutsHigh.push_back(getEtaCut(-1,"<=%f"));
  etaCutsName.push_back("Eta_m7_0");
  etaCutsLow.push_back(getEtaCut(1,">=%f"));
  etaCutsHigh.push_back(getEtaCut(7,"<=%f"));
  etaCutsName.push_back("Eta_0_7");
  etaCutsLow.push_back(getEtaCut(7,">%f"));
  etaCutsHigh.push_back(getEtaCut(14,"<=%f"));
  etaCutsName.push_back("Eta_7_14");
  etaCutsLow.push_back(getEtaCut(14,">%f"));
  etaCutsHigh.push_back(getEtaCut(21,"<=%f"));
  etaCutsName.push_back("Eta_14_21");
  etaCutsLow.push_back(getEtaCut(21,">%f"));
  etaCutsHigh.push_back(getEtaCut(28,"<=%f"));
  etaCutsName.push_back("Eta_21_28");

  TriggerTowerGeometry g;

  //Make plots


  for(std::vector<TString>::const_iterator iJet=jetType.begin(); iJet!=jetType.end(); iJet++){

    TDirectory* dir = outFile->mkdir(*iJet);
    dir->cd();

    for(int i=0; i<etaCutsName.size(); i++){

      tree->Draw("jetPt_"+*iJet+"/jetMatchedPt_"+*iJet+":jetMatchedPt_"+*iJet+">>ratio_"+*iJet+etaCutsName[i]+"(1000,-0.5,999.5,100,-1.,5.)",
          "jetMatchedPt_"+*iJet+"!=-1&&jetEta_"+*iJet+etaCutsLow[i]+"&&jetEta_"+*iJet+etaCutsHigh[i],"colz");
      TH2D* tmpHist = (TH2D*) gDirectory->Get("ratio_"+*iJet+etaCutsName[i]);
      tmpHist->Write();

      tree->Draw("jetPt_"+*iJet+":jetMatchedPt_"+*iJet+">>corr_"+*iJet+etaCutsName[i]+"(1000,-0.5,999.5,1000,-0.5,999.5)",
          "jetMatchedPt_"+*iJet+"!=-1&&jetEta_"+*iJet+etaCutsLow[i]+"&&jetEta_"+*iJet+etaCutsHigh[i],"colz");
      tmpHist = (TH2D*) gDirectory->Get("corr_"+*iJet+etaCutsName[i]);
      tmpHist->Write();

    }

    std::cout << "Done: " << iJet->Data() << std::endl;
  }

  //Write out
  return 0;
}


