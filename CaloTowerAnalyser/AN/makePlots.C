#include "TCut.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TH2.h"
#include "TProfile.h"
#include <iostream>

void make2DPlot(TTree *, TDirectory *,TString, TString,TString,TString);

void makePlots()
{
  TFile * fout = new TFile("plots.root","recreate");

  TFile * finNeutrino = new TFile("/afs/cern.ch/work/m/mcitron/public/NEUTRINO/140716/neutrino_output.root");
  TTree * treeNeut = (TTree *)finNeutrino->Get("demo/L1Tree");

  TFile * finTtbar = new TFile("/home/adam/ttbar_14-07-10.root");
  TTree * treeTtbar = (TTree *)finTtbar->Get("demo/L1Tree");

  std::map<TString,TString> drawNint;
  drawNint["energy"] = "sumsET_:mNPV>>energy(100,-0.5,99.5,3000,-0.5,2999.5)";
  drawNint["rho"] = "medianRho:mNPV>>rho(100,-0.5,99.5,100,-0.005,0.995)";
  drawNint["donut"] = "(jetOuterStripsEnergy_0_L1_for_Nick+jetOuterStripsEnergy_1_L1_for_Nick)/(jetOuterStripsArea_0_L1_for_Nick+jetOuterStripsArea_1_L1_for_Nick):mNPV>>donut(100,-0.5,99.5,100,-0.005,0.995)";
  drawNint["chunkydonut"] = "(jetOuterStripsEnergy_0_5400_chunky+jetOuterStripsEnergy_1_5400_chunky)/(jetOuterStripsArea_0_5400_chunky+jetOuterStripsArea_1_5400_chunky):mNPV>>chunkydonut(100,-0.5,99.5,100,-0.005,0.995)";
  drawNint["seed"] = "jetRingSumsEnergy_0_L1_for_Nick:mNPV>>seed(100,-0.5,99.5,300,-0.5,299.5)";
  drawNint["bigSeed"] = "(jetRingSumsEnergy_0_L1_for_Nick+jetRingSumsEnergy_1_L1_for_Nick):mNPV>>bigSeed(100,-0.5,99.5,300,-0.5,299.5)";

  std::map<TString,TString> drawJetPt;
  drawJetPt["rho"] = "medianRho:jetPt_L1_for_Nick[0]>>rho(500,-0.5,499.5,100,-0.005,0.995)";
  drawJetPt["seed"] = "jetRingSumsEnergy_0_L1_for_Nick:jetPt_L1_for_Nick>>seed(500,-0.5,499.5,300,-0.5,299.5)";
  drawJetPt["bigSeed"] = "(jetRingSumsEnergy_0_L1_for_Nick+jetRingSumsEnergy_1_L1_for_Nick):jetPt_L1_for_Nick>>bigSeed(500,-0.5,499.5,300,-0.5,299.5)";

  TDirectory * neutrinoDir = fout->mkdir("Neutrino"); 
  TDirectory * ttbarDir = fout->mkdir("Ttbar"); 

  TDirectory * nintDir=neutrinoDir->mkdir("Nint");
  for (std::map<TString,TString>::iterator iDraw = drawNint.begin(); iDraw != drawNint.end(); iDraw++)
  {
    TDirectory * dir = nintDir->mkdir(iDraw->first);
    make2DPlot(treeNeut,dir,iDraw->first,iDraw->second,"","Nint");
  }

  TDirectory * jetPtDir=neutrinoDir->mkdir("JetPt");
  for (std::map<TString,TString>::iterator iDraw = drawJetPt.begin(); iDraw != drawJetPt.end(); iDraw++)
  {
    TDirectory * dir = jetPtDir->mkdir(iDraw->first);
    make2DPlot(treeNeut,dir,iDraw->first,iDraw->second,"","jetPt");
  }

  TDirectory * nintDirTtbar=ttbarDir->mkdir("Nint");
  for (std::map<TString,TString>::iterator iDraw = drawNint.begin(); iDraw != drawNint.end(); iDraw++)
  {
    TDirectory * dir = nintDirTtbar->mkdir(iDraw->first);
    make2DPlot(treeTtbar,dir,iDraw->first,iDraw->second,"","Nint");
  }

  TDirectory * jetPtDirTtbar=ttbarDir->mkdir("JetPt");
  for (std::map<TString,TString>::iterator iDraw = drawJetPt.begin(); iDraw != drawJetPt.end(); iDraw++)
  {
    TDirectory * dir = jetPtDirTtbar->mkdir(iDraw->first);
    make2DPlot(treeTtbar,dir,iDraw->first,iDraw->second,"","jetPt");
  }
  fout->Close();
}

void make2DPlot(TTree * tree,TDirectory * dir,TString name,TString draw,TString opt,TString xlab)
{
  dir->cd();
  tree->Draw(draw,opt,"colz");
  TH2F * energyDensity = (TH2F*) gDirectory->Get(name);
  TProfile * energyDensityProf = energyDensity->ProfileX();
  energyDensity->GetXaxis()->SetTitle(xlab);
  energyDensity->GetYaxis()->SetTitle(name);
  energyDensity->Write();
  energyDensityProf->Write();
}
