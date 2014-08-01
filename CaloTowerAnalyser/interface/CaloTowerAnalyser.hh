#ifndef CALOTOWERANALYSER_HH
#define CALOTOWERANALYSER_HH

// -*- C++ -*-
//
// Package:    CaloTowerAnalyser
// Class:      CaloTowerAnalyser
// 
/**\class CaloTowerAnalyser CaloTowerAnalyser.cc jCaloTower/CaloTowerAnalyser/src/CaloTowerAnalyser.cc

Description: [one line class summary]

Implementation:
[Notes on implementation]
 */
//
// Original Author:  Jad Marrouche
//         Created:  Fri Jun 21 08:28:06 BST 2013
// $Id$
//
//

//Switches

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/JetReco/interface/GenJetCollection.h"

#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/CaloTowers/interface/CaloTowerFwd.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/L1GlobalCaloTrigger/interface/L1GctCollections.h"

#include "DataFormats/L1Trigger/interface/L1JetParticle.h"
#include "DataFormats/L1Trigger/interface/L1EtMissParticle.h"

#include "DataFormats/L1Trigger/interface/Jet.h"
#include "DataFormats/L1Trigger/interface/EtSum.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"

#include "SimDataFormats/SLHC/interface/L1CaloTower.h"
#include "SimDataFormats/SLHC/interface/L1CaloTowerFwd.h"

#include "SLHCUpgradeSimulations/L1CaloTrigger/interface/TriggerTowerGeometry_new.h"

#include "jCaloTower/CaloTowerAnalyser/interface/jad_jet_class.hh"
#include "jCaloTower/CaloTowerAnalyser/interface/matching_algo.hh"
#include "jCaloTower/CaloTowerAnalyser/interface/mask.hh"
#include "jCaloTower/CaloTowerAnalyser/interface/calibration_params.hh"

#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/ClusterSequenceArea.hh"
#include "fastjet/tools/Filter.hh"
#include "fastjet/tools/Pruner.hh"
#include "fastjet/GhostedAreaSpec.hh"
#include "fastjet/tools/GridMedianBackgroundEstimator.hh"
#include <fastjet/PseudoJet.hh>

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TString.h"
#include "TH2.h"
#include "TTree.h"
#include "TROOT.h"
#include "TCanvas.h"
#include "TProfile.h"

//Switches
//
//
// class declaration
//

class CaloTowerAnalyser : public edm::EDAnalyzer {
  public:
    explicit CaloTowerAnalyser(const edm::ParameterSet&);
    ~CaloTowerAnalyser();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

    void getJets(std::vector < fastjet::PseudoJet > &constits,std::vector < fastjet::PseudoJet > &jets);
    std::vector<jJet> getL1Jets(const std::vector< std::vector<int> > & input, int jetsize, int vetowindowsize, int seedthresh1, int seedthresh2); 
    std::vector<jJet> getL1JetsMask(const std::vector< std::vector<int> > & input, std::vector<std::vector <int> > mask, std::vector<std::vector <int > > donut_mask,int nstrips, int seedthresh1, int seedthresh2);
    std::vector<jJet> getL1JetsMask(const std::vector< std::vector<int> > & input,const std::vector< std::vector<int> > & inputEC,const std::vector< std::vector<int> > & inputHC, std::vector<std::vector <int> > mask, std::vector<std::vector <int > > donut_mask,int nstrips, int seedthresh1, int seedthresh2);
    //void compareJetCollections(const std::vector<jJet> & col1, const std::vector<jJet> & col2, std::string folderName, bool isgct);
    void MakeJetTree(const std::vector<jJet> & col1,const std::vector<jJet> & col2,TString folderName, bool isgct, bool isuct=false);
    void MakeSumTree(const std::vector<jJet> & col1,TString folderName,bool isgct, bool iscalibgct=false, bool isuct=false);
    void MakeMatchTree(const std::vector<jJet> & col1,const std::vector<jJet> & col2,TString folderName,bool isgct);
    void MakeCalibration(const std::vector<jJet> & col1,const std::vector<jJet> & col2, TString folderName);
    void printOneEvent(const edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers, const std::vector<jJet> & L1jets, const std::vector<fastjet::PseudoJet> & ak4ttjets, const reco::GenJetCollection * ak4genjets, std::vector<fastjet::PseudoJet> & ak4genjetsp);
    void printOneEvent(const edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers, const std::map <TString,std::vector<jJet> > & L1jets, const std::map<TString,std::vector<fastjet::PseudoJet>> & ak4jets,std::map<TString,const reco::GenJetCollection *> ak4genjets);
    std::vector<int> closestJetDistance(const std::vector<jJet> & jJets);
    void SetNPV(int NPV);
    int GetNPV();
    void setL1Sizes(std::vector<TString> l1Sizes);
    void setL1PusVars(std::vector<TString> l1Vars);
    void setGlobalPusVars(std::vector<TString> globalVars);
    void setEtaBins(std::map<TString,int> etaBins);
    void setPtBins(std::map<TString,int> ptBins);
    void setNintBins(std::map<TString,int> nintBins);
    double getMedian(const std::vector<jJet> & jets);
    int getMedianSeed(const std::vector<jJet> & jets);
    double calculateHT(const std::vector<jJet> & jets,const int & thresh);
    std::vector<double> calculateMHT(const std::vector<jJet> & jets,const int & thresh);


  private:
    double mGctHtMissUncalib;
    double mGctHtMissCalib;
    double mGctHtCalib;
    double mGctHtUncalib;
    double mUctHtMissCalib;
    double mUctHtCalib;
    TTree* tree;
    //TTree* masterTree;
    std::map<TString, std::vector<Float_t> *> jetPt_;
    std::map<TString, std::vector<Float_t> *> jetMinDR_;
    std::map<TString, std::vector<Float_t> *> jetPhi_;
    std::map<TString, std::vector<Float_t> *> jetDonut_;
    std::map<TString, std::vector<Float_t> *> jetArea_;
    std::map<TString, std::vector<Float_t> *> jetFirEta_;
    std::map<TString, std::vector<Float_t> *> jetFirPhi_;
    std::map<TString, std::vector<Float_t> *> jetSecEta_;
    std::map<TString, std::vector<Float_t> *> jetSecPhi_;
    std::map<TString, std::vector<Float_t> *> jetCovEtaPhi_;
    std::map<TString, std::vector<Float_t> *> jetEta_;
    std::map<TString, std::vector<Float_t> *> jetMatchedPt_;
    std::map<TString, double> sumsHT_;
    std::map<TString, double> sumsMHT_;
    std::map<TString, double> sumsMHTx_;
    std::map<TString, double> sumsMHTy_;
    bool mMaster;
    double sumsET_;
    double sumsMET_;
    double sumsMETx_;
    double sumsMETy_;
    uint8_t jetTower[100][81];
    std::map<TString, std::vector<Int_t> *> genJetMatchAlgo1_;
    std::map<TString, std::vector<Int_t> *> genJetMatchAlgo2_;
    std::map<TString, std::vector<Int_t> *> jetTowerEnergyUp1_;
    std::map<TString, std::vector<Int_t> *> jetTowerEnergyUp2_;
    std::map<TString, std::vector<Int_t> *> jetTowerEnergyUp3_;
    std::map<TString, std::vector<Int_t> *> jetTowerEnergyUp4_;
    std::map<TString, std::vector<Int_t> *> jetTowerEnergyUp5_;
    std::map<TString, std::vector<Int_t> *> jetTowerEnergyUp8_;

    std::map<TString, std::vector<Float_t> *> jetOuterStripsArea_;
    std::map<TString, std::vector<Float_t> *> jetOuterStripsEnergy_;
    std::map<TString, std::vector<Float_t> *> jetRingSumsArea_;
    std::map<TString, std::vector<Float_t> *> jetRingSumsEnergy_;
    std::map<TString, std::vector<Float_t> *> jetRingSumsECAL_;
    std::map<TString, std::vector<Float_t> *> jetRingSumsHCAL_;
    std::map<TString, std::vector<Float_t> *> jetRingSumsHighest_;

    std::map<TString,TProfile *> col2_calib_ratio_profile;
    std::map<TString,TProfile *> col2_calib_corr_profile;

    bool mPrintMe=false;
    virtual void beginJob() ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;
    TH1D * towerPtWeightEta;
    TH1D * maxTowerPts;
    TH1D * towerPts;
    TH2D * towerPtsNint;

    TH2D * towerPtJetPtmNPV15to25;
    TH2D * towerPtJetPtmNPV25to35;
    TH2D * towerPtJetPtmNPV35to45;
    TH2D * towerPtJetPtmNPV45to55;
    TH2D * towerPtJetPtmNPV55to65;



    //void Make2DMap(const edm::Handle<l1slhc::L1CaloTowerCollection> triggertowers, const edm::Handle<CaloTowerCollection> calotowers, const int eventNumber);

    //virtual void beginRun(edm::Run const&, edm::EventSetup const&);
    //virtual void endRun(edm::Run const&, edm::EventSetup const&);
    //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
    //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

    // ----------member data ---------------------------
    int mEventNumber;
    int mNPV;
    double medianRho=0.;
    int numHotTow=0.;
    int numHotTow12=0.;
    double mET=0.;
    std::vector<double> mMET;
    std::vector<pair_info> pairs;
    std::map<TString, TProfile*> pusProfile_;
    std::vector<TString> globalPusVars_;
    std::vector<TString> l1Sizes_;
    std::vector<TString> l1PusVars_;
    std::map<TString, int> etaBins_;
    std::map<TString, int> ptBins_;
    std::map<TString, int> nintBins_;


    std::string mskim;
    bool mgct;
    TriggerTowerGeometry g; //to run the constructor -- could also make this static




    std::map<TString,bool> pMade;

};

void CaloTowerAnalyser::SetNPV(int npv) { mNPV = npv; }
int CaloTowerAnalyser::GetNPV() { return mNPV; }

void CaloTowerAnalyser::setL1Sizes(std::vector<TString> l1Sizes){
  l1Sizes_=l1Sizes;
}
void CaloTowerAnalyser::setL1PusVars(std::vector<TString> l1Vars){
  l1PusVars_=l1Vars;
}
void CaloTowerAnalyser::setGlobalPusVars(std::vector<TString> globalVars){
  globalPusVars_=globalVars;
}
void CaloTowerAnalyser::setEtaBins(std::map<TString,int> etaBins){
  etaBins_=etaBins;
}
void CaloTowerAnalyser::setPtBins(std::map<TString,int> ptBins){
  ptBins_=ptBins;
}
void CaloTowerAnalyser::setNintBins(std::map<TString,int> nintBins){
  nintBins_=nintBins;
}
#endif
