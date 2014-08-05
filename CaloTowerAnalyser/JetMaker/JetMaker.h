//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 10 14:19:32 2014 by ROOT version 5.34/07
// from TTree L1Tree/L1Tree
// found on file: /home/adam/ttbar_14-07-10.root
//////////////////////////////////////////////////////////

#ifndef JetMaker_h
#define JetMaker_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH2D.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

class JetMaker {
  public :
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    bool doNGun; //Turn off gen for the neutrino gun

    //Add output tree
    TFile* outFile;
    TTree* jetTree;

    //Output histograms for calibration
    std::vector<TString> etaBins;
    std::map<TString, TH2D* > corrHists;
    std::map<TString, TH2D* > ratioHists;

    //Maps for the output variables
    std::vector<TString> jetTypes;
    std::map<TString, std::vector<float>* > jetPt;
    std::map<TString, std::vector<float>* > jetMatchedPt;
    std::map<TString, std::vector<float>* > jetPhi;
    std::map<TString, std::vector<float>* > jetEta;
    std::map<TString, double> ht;
    std::map<TString, double> mhtX;
    std::map<TString, double> mhtY;

    // Declaration of leaf types
    Int_t           mNPV;
    Int_t           numHotTow;
    Int_t           numHotTow12;
    Double_t        medianRho;
    Double_t        sumsET_;
    Double_t        sumsMETx__;
    Double_t        sumsMETy_;
    Double_t        sumsMET_;
    vector<float>   *jetPt_ak4_gen;
    vector<float>   *jetArea_ak4_gen;
    vector<float>   *jetFirEta_ak4_gen;
    vector<float>   *jetCovEtaPhi_ak4_gen;
    vector<float>   *jetFirPhi_ak4_gen;
    vector<float>   *jetSecEta_ak4_gen;
    vector<float>   *jetSecPhi_ak4_gen;
    vector<float>   *jetPhi_ak4_gen;
    vector<float>   *jetEta_ak4_gen;
    vector<float>   *jetDonut_ak4_gen;
    vector<float>   *jetMatchedPt_ak4_gen;
    vector<float>   *jetMinDR_ak4_gen;
    vector<int>     *jetTowerEnergyUp1_ak4_gen;
    vector<int>     *jetTowerEnergyUp2_ak4_gen;
    vector<int>     *jetTowerEnergyUp3_ak4_gen;
    vector<int>     *jetTowerEnergyUp4_ak4_gen;
    vector<int>     *jetTowerEnergyUp5_ak4_gen;
    vector<int>     *jetTowerEnergyUp8_ak4_gen;
    Double_t        sumsHT_ak4_gen_sum;
    Double_t        sumsMHT_ak4_gen_sum;
    Double_t        sumsMHTx_ak4_gen_sum;
    Double_t        sumsMHTy_ak4_gen_sum;
    vector<int>     *genJetMatchAlgo1_ak4_gen;
    vector<int>     *genJetMatchAlgo2_ak4_gen;
    vector<float>   *jetPt_5400_chunky;
    vector<float>   *jetArea_5400_chunky;
    vector<float>   *jetFirEta_5400_chunky;
    vector<float>   *jetCovEtaPhi_5400_chunky;
    vector<float>   *jetFirPhi_5400_chunky;
    vector<float>   *jetSecEta_5400_chunky;
    vector<float>   *jetSecPhi_5400_chunky;
    vector<float>   *jetPhi_5400_chunky;
    vector<float>   *jetEta_5400_chunky;
    vector<float>   *jetDonut_5400_chunky;
    vector<float>   *jetMatchedPt_5400_chunky;
    vector<float>   *jetMinDR_5400_chunky;
    vector<int>     *jetTowerEnergyUp1_5400_chunky;
    vector<int>     *jetTowerEnergyUp2_5400_chunky;
    vector<int>     *jetTowerEnergyUp3_5400_chunky;
    vector<int>     *jetTowerEnergyUp4_5400_chunky;
    vector<int>     *jetTowerEnergyUp5_5400_chunky;
    vector<int>     *jetTowerEnergyUp8_5400_chunky;
    vector<float>   *jetOuterStripsEnergy_0_5400_chunky;
    vector<float>   *jetOuterStripsArea_0_5400_chunky;
    vector<float>   *jetOuterStripsEnergy_1_5400_chunky;
    vector<float>   *jetOuterStripsArea_1_5400_chunky;
    vector<float>   *jetOuterStripsEnergy_2_5400_chunky;
    vector<float>   *jetOuterStripsArea_2_5400_chunky;
    vector<float>   *jetOuterStripsEnergy_3_5400_chunky;
    vector<float>   *jetOuterStripsArea_3_5400_chunky;
    vector<float>   *jetRingSumsEnergy_0_5400_chunky;
    vector<float>   *jetRingSumsHighest_0_5400_chunky;
    vector<float>   *jetRingSumsArea_0_5400_chunky;
    vector<float>   *jetRingSumsEnergy_1_5400_chunky;
    vector<float>   *jetRingSumsHighest_1_5400_chunky;
    vector<float>   *jetRingSumsArea_1_5400_chunky;
    vector<float>   *jetRingSumsEnergy_2_5400_chunky;
    vector<float>   *jetRingSumsHighest_2_5400_chunky;
    vector<float>   *jetRingSumsArea_2_5400_chunky;
    vector<float>   *jetRingSumsEnergy_3_5400_chunky;
    vector<float>   *jetRingSumsHighest_3_5400_chunky;
    vector<float>   *jetRingSumsArea_3_5400_chunky;
    vector<float>   *jetRingSumsEnergy_4_5400_chunky;
    vector<float>   *jetRingSumsHighest_4_5400_chunky;
    vector<float>   *jetRingSumsArea_4_5400_chunky;
    vector<int>     *genJetMatchAlgo1_5400_chunky;
    vector<int>     *genJetMatchAlgo2_5400_chunky;
    Double_t        sumsHT_5400_chunky_sum;
    Double_t        sumsMHT_5400_chunky_sum;
    Double_t        sumsMHTx_5400_chunky_sum;
    Double_t        sumsMHTy_5400_chunky_sum;
    vector<float>   *jetPt_L1_for_Nick;
    vector<float>   *jetArea_L1_for_Nick;
    vector<float>   *jetFirEta_L1_for_Nick;
    vector<float>   *jetCovEtaPhi_L1_for_Nick;
    vector<float>   *jetFirPhi_L1_for_Nick;
    vector<float>   *jetSecEta_L1_for_Nick;
    vector<float>   *jetSecPhi_L1_for_Nick;
    vector<float>   *jetPhi_L1_for_Nick;
    vector<float>   *jetEta_L1_for_Nick;
    vector<float>   *jetDonut_L1_for_Nick;
    vector<float>   *jetMatchedPt_L1_for_Nick;
    vector<float>   *jetMinDR_L1_for_Nick;
    vector<int>     *jetTowerEnergyUp1_L1_for_Nick;
    vector<int>     *jetTowerEnergyUp2_L1_for_Nick;
    vector<int>     *jetTowerEnergyUp3_L1_for_Nick;
    vector<int>     *jetTowerEnergyUp4_L1_for_Nick;
    vector<int>     *jetTowerEnergyUp5_L1_for_Nick;
    vector<int>     *jetTowerEnergyUp8_L1_for_Nick;
    vector<float>   *jetOuterStripsEnergy_0_L1_for_Nick;
    vector<float>   *jetOuterStripsArea_0_L1_for_Nick;
    vector<float>   *jetOuterStripsEnergy_1_L1_for_Nick;
    vector<float>   *jetOuterStripsArea_1_L1_for_Nick;
    vector<float>   *jetOuterStripsEnergy_2_L1_for_Nick;
    vector<float>   *jetOuterStripsArea_2_L1_for_Nick;
    vector<float>   *jetOuterStripsEnergy_3_L1_for_Nick;
    vector<float>   *jetOuterStripsArea_3_L1_for_Nick;
    vector<float>   *jetRingSumsEnergy_0_L1_for_Nick;
    vector<float>   *jetRingSumsHighest_0_L1_for_Nick;
    vector<float>   *jetRingSumsArea_0_L1_for_Nick;
    vector<float>   *jetRingSumsEnergy_1_L1_for_Nick;
    vector<float>   *jetRingSumsHighest_1_L1_for_Nick;
    vector<float>   *jetRingSumsArea_1_L1_for_Nick;
    vector<float>   *jetRingSumsEnergy_2_L1_for_Nick;
    vector<float>   *jetRingSumsHighest_2_L1_for_Nick;
    vector<float>   *jetRingSumsArea_2_L1_for_Nick;
    vector<float>   *jetRingSumsEnergy_3_L1_for_Nick;
    vector<float>   *jetRingSumsHighest_3_L1_for_Nick;
    vector<float>   *jetRingSumsArea_3_L1_for_Nick;
    vector<float>   *jetRingSumsEnergy_4_L1_for_Nick;
    vector<float>   *jetRingSumsHighest_4_L1_for_Nick;
    vector<float>   *jetRingSumsArea_4_L1_for_Nick;
    vector<float>   *jetRingSumsECAL_0_L1_for_Nick;
    vector<float>   *jetRingSumsECAL_1_L1_for_Nick;
    vector<float>   *jetRingSumsECAL_2_L1_for_Nick;
    vector<float>   *jetRingSumsECAL_3_L1_for_Nick;
    vector<float>   *jetRingSumsECAL_4_L1_for_Nick;
    vector<float>   *jetRingSumsHCAL_0_L1_for_Nick;
    vector<float>   *jetRingSumsHCAL_1_L1_for_Nick;
    vector<float>   *jetRingSumsHCAL_2_L1_for_Nick;
    vector<float>   *jetRingSumsHCAL_3_L1_for_Nick;
    vector<float>   *jetRingSumsHCAL_4_L1_for_Nick;
    vector<int>     *genJetMatchAlgo1_L1_for_Nick;
    vector<int>     *genJetMatchAlgo2_L1_for_Nick;
    Double_t        sumsHT_L1_for_Nick_sum;
    Double_t        sumsMHT_L1_for_Nick_sum;
    Double_t        sumsMHTx_L1_for_Nick_sum;
    Double_t        sumsMHTy_L1_for_Nick_sum;
    vector<float>   *jetPt_gct_calib_gen;
    vector<float>   *jetArea_gct_calib_gen;
    vector<float>   *jetFirEta_gct_calib_gen;
    vector<float>   *jetCovEtaPhi_gct_calib_gen;
    vector<float>   *jetFirPhi_gct_calib_gen;
    vector<float>   *jetSecEta_gct_calib_gen;
    vector<float>   *jetSecPhi_gct_calib_gen;
    vector<float>   *jetPhi_gct_calib_gen;
    vector<float>   *jetEta_gct_calib_gen;
    vector<float>   *jetDonut_gct_calib_gen;
    vector<float>   *jetMatchedPt_gct_calib_gen;
    vector<float>   *jetMinDR_gct_calib_gen;
    vector<int>     *jetTowerEnergyUp1_gct_calib_gen;
    vector<int>     *jetTowerEnergyUp2_gct_calib_gen;
    vector<int>     *jetTowerEnergyUp3_gct_calib_gen;
    vector<int>     *jetTowerEnergyUp4_gct_calib_gen;
    vector<int>     *jetTowerEnergyUp5_gct_calib_gen;
    vector<int>     *jetTowerEnergyUp8_gct_calib_gen;
    vector<int>     *genJetMatchAlgo1_gct_calib_gen;
    vector<int>     *genJetMatchAlgo2_gct_calib_gen;
    Double_t        sumsHT_gct_calib_gen_sum;
    Double_t        sumsMHT_gct_calib_gen_sum;
    Double_t        sumsMHTx_gct_calib_gen_sum;
    Double_t        sumsMHTy_gct_calib_gen_sum;
    vector<float>   *jetPt_gct_uncalib_gen;
    vector<float>   *jetArea_gct_uncalib_gen;
    vector<float>   *jetFirEta_gct_uncalib_gen;
    vector<float>   *jetCovEtaPhi_gct_uncalib_gen;
    vector<float>   *jetFirPhi_gct_uncalib_gen;
    vector<float>   *jetSecEta_gct_uncalib_gen;
    vector<float>   *jetSecPhi_gct_uncalib_gen;
    vector<float>   *jetPhi_gct_uncalib_gen;
    vector<float>   *jetEta_gct_uncalib_gen;
    vector<float>   *jetDonut_gct_uncalib_gen;
    vector<float>   *jetMatchedPt_gct_uncalib_gen;
    vector<float>   *jetMinDR_gct_uncalib_gen;
    vector<int>     *jetTowerEnergyUp1_gct_uncalib_gen;
    vector<int>     *jetTowerEnergyUp2_gct_uncalib_gen;
    vector<int>     *jetTowerEnergyUp3_gct_uncalib_gen;
    vector<int>     *jetTowerEnergyUp4_gct_uncalib_gen;
    vector<int>     *jetTowerEnergyUp5_gct_uncalib_gen;
    vector<int>     *jetTowerEnergyUp8_gct_uncalib_gen;
    vector<int>     *genJetMatchAlgo1_gct_uncalib_gen;
    vector<int>     *genJetMatchAlgo2_gct_uncalib_gen;
    Double_t        sumsHT_gct_uncalib_gen_sum;
    Double_t        sumsMHT_gct_uncalib_gen_sum;
    Double_t        sumsMHTx_gct_uncalib_gen_sum;
    Double_t        sumsMHTy_gct_uncalib_gen_sum;

    // List of branches
    TBranch        *b_mNPV;   //!
    TBranch        *b_numHotTow;   //!
    TBranch        *b_numHotTow12;   //!
    TBranch        *b_medianRho;   //!
    TBranch        *b_ET;   //!
    TBranch        *b_METx;   //!
    TBranch        *b_METy;   //!
    TBranch        *b_MET;   //!
    TBranch        *b_jetPt_ak4_gen;   //!
    TBranch        *b_jetArea_ak4_gen;   //!
    TBranch        *b_jetFirEta_ak4_gen;   //!
    TBranch        *b_jetCovEtaPhi_ak4_gen;   //!
    TBranch        *b_jetFirPhi_ak4_gen;   //!
    TBranch        *b_jetSecEta_ak4_gen;   //!
    TBranch        *b_jetSecPhi_ak4_gen;   //!
    TBranch        *b_jetPhi_ak4_gen;   //!
    TBranch        *b_jetEta_ak4_gen;   //!
    TBranch        *b_jetDonut_ak4_gen;   //!
    TBranch        *b_jetMatchedPt_ak4_gen;   //!
    TBranch        *b_jetMinDR_ak4_gen;   //!
    TBranch        *b_jetTowerEnergyUp1_ak4_gen;   //!
    TBranch        *b_jetTowerEnergyUp2_ak4_gen;   //!
    TBranch        *b_jetTowerEnergyUp3_ak4_gen;   //!
    TBranch        *b_jetTowerEnergyUp4_ak4_gen;   //!
    TBranch        *b_jetTowerEnergyUp5_ak4_gen;   //!
    TBranch        *b_jetTowerEnergyUp8_ak4_gen;   //!
    TBranch        *b_sumsHT_ak4_gen_sum;   //!
    TBranch        *b_sumsMHT_ak4_gen_sum;   //!
    TBranch        *b_sumsMHTx_ak4_gen_sum;   //!
    TBranch        *b_sumsMHTy_ak4_gen_sum;   //!
    TBranch        *b_genJetMatchAlgo1_ak4_gen;   //!
    TBranch        *b_genJetMatchAlgo2_ak4_gen;   //!
    TBranch        *b_jetPt_5400_chunky;   //!
    TBranch        *b_jetArea_5400_chunky;   //!
    TBranch        *b_jetFirEta_5400_chunky;   //!
    TBranch        *b_jetCovEtaPhi_5400_chunky;   //!
    TBranch        *b_jetFirPhi_5400_chunky;   //!
    TBranch        *b_jetSecEta_5400_chunky;   //!
    TBranch        *b_jetSecPhi_5400_chunky;   //!
    TBranch        *b_jetPhi_5400_chunky;   //!
    TBranch        *b_jetEta_5400_chunky;   //!
    TBranch        *b_jetDonut_5400_chunky;   //!
    TBranch        *b_jetMatchedPt_5400_chunky;   //!
    TBranch        *b_jetMinDR_5400_chunky;   //!
    TBranch        *b_jetTowerEnergyUp1_5400_chunky;   //!
    TBranch        *b_jetTowerEnergyUp2_5400_chunky;   //!
    TBranch        *b_jetTowerEnergyUp3_5400_chunky;   //!
    TBranch        *b_jetTowerEnergyUp4_5400_chunky;   //!
    TBranch        *b_jetTowerEnergyUp5_5400_chunky;   //!
    TBranch        *b_jetTowerEnergyUp8_5400_chunky;   //!
    TBranch        *b_jetOuterStripsEnergy_0_5400_chunky;   //!
    TBranch        *b_jetOuterStripsArea_0_5400_chunky;   //!
    TBranch        *b_jetOuterStripsEnergy_1_5400_chunky;   //!
    TBranch        *b_jetOuterStripsArea_1_5400_chunky;   //!
    TBranch        *b_jetOuterStripsEnergy_2_5400_chunky;   //!
    TBranch        *b_jetOuterStripsArea_2_5400_chunky;   //!
    TBranch        *b_jetOuterStripsEnergy_3_5400_chunky;   //!
    TBranch        *b_jetOuterStripsArea_3_5400_chunky;   //!
    TBranch        *b_jetRingSumsEnergy_0_5400_chunky;   //!
    TBranch        *b_jetRingSumsHighest_0_5400_chunky;   //!
    TBranch        *b_jetRingSumsArea_0_5400_chunky;   //!
    TBranch        *b_jetRingSumsEnergy_1_5400_chunky;   //!
    TBranch        *b_jetRingSumsHighest_1_5400_chunky;   //!
    TBranch        *b_jetRingSumsArea_1_5400_chunky;   //!
    TBranch        *b_jetRingSumsEnergy_2_5400_chunky;   //!
    TBranch        *b_jetRingSumsHighest_2_5400_chunky;   //!
    TBranch        *b_jetRingSumsArea_2_5400_chunky;   //!
    TBranch        *b_jetRingSumsEnergy_3_5400_chunky;   //!
    TBranch        *b_jetRingSumsHighest_3_5400_chunky;   //!
    TBranch        *b_jetRingSumsArea_3_5400_chunky;   //!
    TBranch        *b_jetRingSumsEnergy_4_5400_chunky;   //!
    TBranch        *b_jetRingSumsHighest_4_5400_chunky;   //!
    TBranch        *b_jetRingSumsArea_4_5400_chunky;   //!
    TBranch        *b_genJetMatchAlgo1_5400_chunky;   //!
    TBranch        *b_genJetMatchAlgo2_5400_chunky;   //!
    TBranch        *b_sumsHT_5400_chunky_sum;   //!
    TBranch        *b_sumsMHT_5400_chunky_sum;   //!
    TBranch        *b_sumsMHTx_5400_chunky_sum;   //!
    TBranch        *b_sumsMHTy_5400_chunky_sum;   //!
    TBranch        *b_jetPt_L1_for_Nick;   //!
    TBranch        *b_jetArea_L1_for_Nick;   //!
    TBranch        *b_jetFirEta_L1_for_Nick;   //!
    TBranch        *b_jetCovEtaPhi_L1_for_Nick;   //!
    TBranch        *b_jetFirPhi_L1_for_Nick;   //!
    TBranch        *b_jetSecEta_L1_for_Nick;   //!
    TBranch        *b_jetSecPhi_L1_for_Nick;   //!
    TBranch        *b_jetPhi_L1_for_Nick;   //!
    TBranch        *b_jetEta_L1_for_Nick;   //!
    TBranch        *b_jetDonut_L1_for_Nick;   //!
    TBranch        *b_jetMatchedPt_L1_for_Nick;   //!
    TBranch        *b_jetMinDR_L1_for_Nick;   //!
    TBranch        *b_jetTowerEnergyUp1_L1_for_Nick;   //!
    TBranch        *b_jetTowerEnergyUp2_L1_for_Nick;   //!
    TBranch        *b_jetTowerEnergyUp3_L1_for_Nick;   //!
    TBranch        *b_jetTowerEnergyUp4_L1_for_Nick;   //!
    TBranch        *b_jetTowerEnergyUp5_L1_for_Nick;   //!
    TBranch        *b_jetTowerEnergyUp8_L1_for_Nick;   //!
    TBranch        *b_jetOuterStripsEnergy_0_L1_for_Nick;   //!
    TBranch        *b_jetOuterStripsArea_0_L1_for_Nick;   //!
    TBranch        *b_jetOuterStripsEnergy_1_L1_for_Nick;   //!
    TBranch        *b_jetOuterStripsArea_1_L1_for_Nick;   //!
    TBranch        *b_jetOuterStripsEnergy_2_L1_for_Nick;   //!
    TBranch        *b_jetOuterStripsArea_2_L1_for_Nick;   //!
    TBranch        *b_jetOuterStripsEnergy_3_L1_for_Nick;   //!
    TBranch        *b_jetOuterStripsArea_3_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsEnergy_0_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHighest_0_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsArea_0_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsEnergy_1_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHighest_1_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsArea_1_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsEnergy_2_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHighest_2_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsArea_2_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsEnergy_3_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHighest_3_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsArea_3_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsEnergy_4_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHighest_4_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsArea_4_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsECAL_0_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsECAL_1_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsECAL_2_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsECAL_3_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsECAL_4_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHCAL_0_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHCAL_1_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHCAL_2_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHCAL_3_L1_for_Nick;   //!
    TBranch        *b_jetRingSumsHCAL_4_L1_for_Nick;   //!
    TBranch        *b_genJetMatchAlgo1_L1_for_Nick;   //!
    TBranch        *b_genJetMatchAlgo2_L1_for_Nick;   //!
    TBranch        *b_sumsHT_L1_for_Nick_sum;   //!
    TBranch        *b_sumsMHT_L1_for_Nick_sum;   //!
    TBranch        *b_sumsMHTx_L1_for_Nick_sum;   //!
    TBranch        *b_sumsMHTy_L1_for_Nick_sum;   //!
    TBranch        *b_jetPt_gct_calib_gen;   //!
    TBranch        *b_jetArea_gct_calib_gen;   //!
    TBranch        *b_jetFirEta_gct_calib_gen;   //!
    TBranch        *b_jetCovEtaPhi_gct_calib_gen;   //!
    TBranch        *b_jetFirPhi_gct_calib_gen;   //!
    TBranch        *b_jetSecEta_gct_calib_gen;   //!
    TBranch        *b_jetSecPhi_gct_calib_gen;   //!
    TBranch        *b_jetPhi_gct_calib_gen;   //!
    TBranch        *b_jetEta_gct_calib_gen;   //!
    TBranch        *b_jetDonut_gct_calib_gen;   //!
    TBranch        *b_jetMatchedPt_gct_calib_gen;   //!
    TBranch        *b_jetMinDR_gct_calib_gen;   //!
    TBranch        *b_jetTowerEnergyUp1_gct_calib_gen;   //!
    TBranch        *b_jetTowerEnergyUp2_gct_calib_gen;   //!
    TBranch        *b_jetTowerEnergyUp3_gct_calib_gen;   //!
    TBranch        *b_jetTowerEnergyUp4_gct_calib_gen;   //!
    TBranch        *b_jetTowerEnergyUp5_gct_calib_gen;   //!
    TBranch        *b_jetTowerEnergyUp8_gct_calib_gen;   //!
    TBranch        *b_genJetMatchAlgo1_gct_calib_gen;   //!
    TBranch        *b_genJetMatchAlgo2_gct_calib_gen;   //!
    TBranch        *b_sumsHT_gct_calib_gen_sum;   //!
    TBranch        *b_sumsMHT_gct_calib_gen_sum;   //!
    TBranch        *b_sumsMHTx_gct_calib_gen_sum;   //!
    TBranch        *b_sumsMHTy_gct_calib_gen_sum;   //!
    TBranch        *b_jetPt_gct_uncalib_gen;   //!
    TBranch        *b_jetArea_gct_uncalib_gen;   //!
    TBranch        *b_jetFirEta_gct_uncalib_gen;   //!
    TBranch        *b_jetCovEtaPhi_gct_uncalib_gen;   //!
    TBranch        *b_jetFirPhi_gct_uncalib_gen;   //!
    TBranch        *b_jetSecEta_gct_uncalib_gen;   //!
    TBranch        *b_jetSecPhi_gct_uncalib_gen;   //!
    TBranch        *b_jetPhi_gct_uncalib_gen;   //!
    TBranch        *b_jetEta_gct_uncalib_gen;   //!
    TBranch        *b_jetDonut_gct_uncalib_gen;   //!
    TBranch        *b_jetMatchedPt_gct_uncalib_gen;   //!
    TBranch        *b_jetMinDR_gct_uncalib_gen;   //!
    TBranch        *b_jetTowerEnergyUp1_gct_uncalib_gen;   //!
    TBranch        *b_jetTowerEnergyUp2_gct_uncalib_gen;   //!
    TBranch        *b_jetTowerEnergyUp3_gct_uncalib_gen;   //!
    TBranch        *b_jetTowerEnergyUp4_gct_uncalib_gen;   //!
    TBranch        *b_jetTowerEnergyUp5_gct_uncalib_gen;   //!
    TBranch        *b_jetTowerEnergyUp8_gct_uncalib_gen;   //!
    TBranch        *b_genJetMatchAlgo1_gct_uncalib_gen;   //!
    TBranch        *b_genJetMatchAlgo2_gct_uncalib_gen;   //!
    TBranch        *b_sumsHT_gct_uncalib_gen_sum;   //!
    TBranch        *b_sumsMHT_gct_uncalib_gen_sum;   //!
    TBranch        *b_sumsMHTx_gct_uncalib_gen_sum;   //!
    TBranch        *b_sumsMHTy_gct_uncalib_gen_sum;   //!

    JetMaker(TTree *tree=0, bool doingNgun=false);
    virtual ~JetMaker();
    //virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef JetMaker_cxx
JetMaker::JetMaker(TTree *tree, bool doingNGun) : fChain(0) 
{
  doNGun = doingNGun;
  // if parameter tree is not specified (or zero), connect the file
  // used to generate this class and read the Tree.
  if (tree == 0) {
    TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/adam/ttbar_14-07-10.root");
    if (!f || !f->IsOpen()) {
      f = new TFile("/home/adam/ttbar_14-07-10.root");
    }
    TDirectory * dir = (TDirectory*)f->Get("/home/adam/ttbar_14-07-10.root:/demo");
    dir->GetObject("L1Tree",tree);

  }
  Init(tree);

  //Initialise the memory for the new tree
  if(doingNGun){
    outFile = new TFile("jetTreeNgun.root","RECREATE");
  }else{
    outFile = new TFile("jetTreeTtbar.root","RECREATE");
  }
  jetTree = new TTree("jetTree","jetTree");

  //Add the eta bins for the calibration

  etaBins.push_back("Eta_m3p00_to_m2p25");
  etaBins.push_back("Eta_m2p25_to_m1p50");
  etaBins.push_back("Eta_m1p50_to_m0p75");
  etaBins.push_back("Eta_m0p75_to_0p00");
  etaBins.push_back("Eta_0p00_to_0p75");
  etaBins.push_back("Eta_0p75_to_1p50");
  etaBins.push_back("Eta_1p50_to_2p25");
  etaBins.push_back("Eta_2p25_to_3p00");

  //Declare the types of PUS jets to be made
  jetTypes.push_back("s0_nopus");
  jetTypes.push_back("s0_donut");
  jetTypes.push_back("s0_global");
  jetTypes.push_back("s0_chunky");
  jetTypes.push_back("s0_tsup1");
  jetTypes.push_back("s0_tsup2");
  jetTypes.push_back("s0_tsup3");
  jetTypes.push_back("s5_nopus");
  jetTypes.push_back("s5_donut");
  jetTypes.push_back("s5_global");
  jetTypes.push_back("s5_chunky");
  jetTypes.push_back("s5_tsup1");
  jetTypes.push_back("s5_tsup2");
  jetTypes.push_back("s5_tsup3");
  jetTypes.push_back("c10_nopus");
  jetTypes.push_back("c10_donut");
  jetTypes.push_back("c10_global");
  jetTypes.push_back("c10_chunky");
  jetTypes.push_back("c10_tsup1");
  jetTypes.push_back("c10_tsup2");
  jetTypes.push_back("c10_tsup3");

  //Assign the memory for all the different types of jets
  for(std::vector<TString>::const_iterator it=jetTypes.begin(); 
      it!=jetTypes.end(); it++){
    jetPt[*it] = new std::vector<float>();
    jetMatchedPt[*it] = new std::vector<float>();
    jetEta[*it] = new std::vector<float>();
    jetPhi[*it] = new std::vector<float>();
    ht[*it] = 0;
    mhtX[*it] = 0;
    mhtY[*it] = 0;

    //Assign memory for the calibration histograms
    for(std::vector<TString>::const_iterator eBin=etaBins.begin();
        eBin!=etaBins.end(); eBin++){
      corrHists[*it+*eBin] = new TH2D("corr_"+*it+"_"+*eBin,";Gen pT; L1 pT",1000,0.,1000.,1000,0.,1000.);
      ratioHists[*it+*eBin] = new TH2D("ratio_"+*it+"_"+*eBin,";Gen pT; L1 pT",1000,0.,1000.,1000,-10.,10.);
    }
  }

  //Make Branches in the tree
  for(std::vector<TString>::const_iterator it=jetTypes.begin(); 
      it!=jetTypes.end(); it++){
    jetTree->Branch("jetPt_"+*it,"std::vector<float>",&jetPt[*it]);
    jetTree->Branch("jetMatchedPt_"+*it,"std::vector<float>",&jetMatchedPt[*it]);
    jetTree->Branch("jetEta_"+*it,"std::vector<float>",&jetEta[*it]);
    jetTree->Branch("jetPhi_"+*it,"std::vector<float>",&jetPhi[*it]);
    jetTree->Branch("ht_"+*it,&ht[*it],"ht_"+*it+"/D");
    jetTree->Branch("mhtX_"+*it,&mhtX[*it],"mhtX_"+*it+"/D");
    jetTree->Branch("mhtY_"+*it,&mhtY[*it],"mhtY_"+*it+"/D");
  }

}

JetMaker::~JetMaker()
{
  if (!fChain) return;
  delete fChain->GetCurrentFile();
}

Int_t JetMaker::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t JetMaker::LoadTree(Long64_t entry)
{
  // Set the environment to read one entry
  if (!fChain) return -5;
  Long64_t centry = fChain->LoadTree(entry);
  if (centry < 0) return centry;
  if (fChain->GetTreeNumber() != fCurrent) {
    fCurrent = fChain->GetTreeNumber();
    Notify();
  }
  return centry;
}

void JetMaker::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer
  jetPt_ak4_gen = 0;
  jetArea_ak4_gen = 0;
  jetFirEta_ak4_gen = 0;
  jetCovEtaPhi_ak4_gen = 0;
  jetFirPhi_ak4_gen = 0;
  jetSecEta_ak4_gen = 0;
  jetSecPhi_ak4_gen = 0;
  jetPhi_ak4_gen = 0;
  jetEta_ak4_gen = 0;
  jetDonut_ak4_gen = 0;
  jetMatchedPt_ak4_gen = 0;
  jetMinDR_ak4_gen = 0;
  jetTowerEnergyUp1_ak4_gen = 0;
  jetTowerEnergyUp2_ak4_gen = 0;
  jetTowerEnergyUp3_ak4_gen = 0;
  jetTowerEnergyUp4_ak4_gen = 0;
  jetTowerEnergyUp5_ak4_gen = 0;
  jetTowerEnergyUp8_ak4_gen = 0;
  genJetMatchAlgo1_ak4_gen = 0;
  genJetMatchAlgo2_ak4_gen = 0;
  jetPt_5400_chunky = 0;
  jetArea_5400_chunky = 0;
  jetFirEta_5400_chunky = 0;
  jetCovEtaPhi_5400_chunky = 0;
  jetFirPhi_5400_chunky = 0;
  jetSecEta_5400_chunky = 0;
  jetSecPhi_5400_chunky = 0;
  jetPhi_5400_chunky = 0;
  jetEta_5400_chunky = 0;
  jetDonut_5400_chunky = 0;
  jetMatchedPt_5400_chunky = 0;
  jetMinDR_5400_chunky = 0;
  jetTowerEnergyUp1_5400_chunky = 0;
  jetTowerEnergyUp2_5400_chunky = 0;
  jetTowerEnergyUp3_5400_chunky = 0;
  jetTowerEnergyUp4_5400_chunky = 0;
  jetTowerEnergyUp5_5400_chunky = 0;
  jetTowerEnergyUp8_5400_chunky = 0;
  jetOuterStripsEnergy_0_5400_chunky = 0;
  jetOuterStripsArea_0_5400_chunky = 0;
  jetOuterStripsEnergy_1_5400_chunky = 0;
  jetOuterStripsArea_1_5400_chunky = 0;
  jetOuterStripsEnergy_2_5400_chunky = 0;
  jetOuterStripsArea_2_5400_chunky = 0;
  jetOuterStripsEnergy_3_5400_chunky = 0;
  jetOuterStripsArea_3_5400_chunky = 0;
  jetRingSumsEnergy_0_5400_chunky = 0;
  jetRingSumsHighest_0_5400_chunky = 0;
  jetRingSumsArea_0_5400_chunky = 0;
  jetRingSumsEnergy_1_5400_chunky = 0;
  jetRingSumsHighest_1_5400_chunky = 0;
  jetRingSumsArea_1_5400_chunky = 0;
  jetRingSumsEnergy_2_5400_chunky = 0;
  jetRingSumsHighest_2_5400_chunky = 0;
  jetRingSumsArea_2_5400_chunky = 0;
  jetRingSumsEnergy_3_5400_chunky = 0;
  jetRingSumsHighest_3_5400_chunky = 0;
  jetRingSumsArea_3_5400_chunky = 0;
  jetRingSumsEnergy_4_5400_chunky = 0;
  jetRingSumsHighest_4_5400_chunky = 0;
  jetRingSumsArea_4_5400_chunky = 0;
  genJetMatchAlgo1_5400_chunky = 0;
  genJetMatchAlgo2_5400_chunky = 0;
  jetPt_L1_for_Nick = 0;
  jetArea_L1_for_Nick = 0;
  jetFirEta_L1_for_Nick = 0;
  jetCovEtaPhi_L1_for_Nick = 0;
  jetFirPhi_L1_for_Nick = 0;
  jetSecEta_L1_for_Nick = 0;
  jetSecPhi_L1_for_Nick = 0;
  jetPhi_L1_for_Nick = 0;
  jetEta_L1_for_Nick = 0;
  jetDonut_L1_for_Nick = 0;
  jetMatchedPt_L1_for_Nick = 0;
  jetMinDR_L1_for_Nick = 0;
  jetTowerEnergyUp1_L1_for_Nick = 0;
  jetTowerEnergyUp2_L1_for_Nick = 0;
  jetTowerEnergyUp3_L1_for_Nick = 0;
  jetTowerEnergyUp4_L1_for_Nick = 0;
  jetTowerEnergyUp5_L1_for_Nick = 0;
  jetTowerEnergyUp8_L1_for_Nick = 0;
  jetOuterStripsEnergy_0_L1_for_Nick = 0;
  jetOuterStripsArea_0_L1_for_Nick = 0;
  jetOuterStripsEnergy_1_L1_for_Nick = 0;
  jetOuterStripsArea_1_L1_for_Nick = 0;
  jetOuterStripsEnergy_2_L1_for_Nick = 0;
  jetOuterStripsArea_2_L1_for_Nick = 0;
  jetOuterStripsEnergy_3_L1_for_Nick = 0;
  jetOuterStripsArea_3_L1_for_Nick = 0;
  jetRingSumsEnergy_0_L1_for_Nick = 0;
  jetRingSumsHighest_0_L1_for_Nick = 0;
  jetRingSumsArea_0_L1_for_Nick = 0;
  jetRingSumsEnergy_1_L1_for_Nick = 0;
  jetRingSumsHighest_1_L1_for_Nick = 0;
  jetRingSumsArea_1_L1_for_Nick = 0;
  jetRingSumsEnergy_2_L1_for_Nick = 0;
  jetRingSumsHighest_2_L1_for_Nick = 0;
  jetRingSumsArea_2_L1_for_Nick = 0;
  jetRingSumsEnergy_3_L1_for_Nick = 0;
  jetRingSumsHighest_3_L1_for_Nick = 0;
  jetRingSumsArea_3_L1_for_Nick = 0;
  jetRingSumsEnergy_4_L1_for_Nick = 0;
  jetRingSumsHighest_4_L1_for_Nick = 0;
  jetRingSumsArea_4_L1_for_Nick = 0;
  jetRingSumsECAL_0_L1_for_Nick = 0;
  jetRingSumsECAL_1_L1_for_Nick = 0;
  jetRingSumsECAL_2_L1_for_Nick = 0;
  jetRingSumsECAL_3_L1_for_Nick = 0;
  jetRingSumsECAL_4_L1_for_Nick = 0;
  jetRingSumsHCAL_0_L1_for_Nick = 0;
  jetRingSumsHCAL_1_L1_for_Nick = 0;
  jetRingSumsHCAL_2_L1_for_Nick = 0;
  jetRingSumsHCAL_3_L1_for_Nick = 0;
  jetRingSumsHCAL_4_L1_for_Nick = 0;
  genJetMatchAlgo1_L1_for_Nick = 0;
  genJetMatchAlgo2_L1_for_Nick = 0;
  jetPt_gct_calib_gen = 0;
  jetArea_gct_calib_gen = 0;
  jetFirEta_gct_calib_gen = 0;
  jetCovEtaPhi_gct_calib_gen = 0;
  jetFirPhi_gct_calib_gen = 0;
  jetSecEta_gct_calib_gen = 0;
  jetSecPhi_gct_calib_gen = 0;
  jetPhi_gct_calib_gen = 0;
  jetEta_gct_calib_gen = 0;
  jetDonut_gct_calib_gen = 0;
  jetMatchedPt_gct_calib_gen = 0;
  jetMinDR_gct_calib_gen = 0;
  jetTowerEnergyUp1_gct_calib_gen = 0;
  jetTowerEnergyUp2_gct_calib_gen = 0;
  jetTowerEnergyUp3_gct_calib_gen = 0;
  jetTowerEnergyUp4_gct_calib_gen = 0;
  jetTowerEnergyUp5_gct_calib_gen = 0;
  jetTowerEnergyUp8_gct_calib_gen = 0;
  genJetMatchAlgo1_gct_calib_gen = 0;
  genJetMatchAlgo2_gct_calib_gen = 0;
  jetPt_gct_uncalib_gen = 0;
  jetArea_gct_uncalib_gen = 0;
  jetFirEta_gct_uncalib_gen = 0;
  jetCovEtaPhi_gct_uncalib_gen = 0;
  jetFirPhi_gct_uncalib_gen = 0;
  jetSecEta_gct_uncalib_gen = 0;
  jetSecPhi_gct_uncalib_gen = 0;
  jetPhi_gct_uncalib_gen = 0;
  jetEta_gct_uncalib_gen = 0;
  jetDonut_gct_uncalib_gen = 0;
  jetMatchedPt_gct_uncalib_gen = 0;
  jetMinDR_gct_uncalib_gen = 0;
  jetTowerEnergyUp1_gct_uncalib_gen = 0;
  jetTowerEnergyUp2_gct_uncalib_gen = 0;
  jetTowerEnergyUp3_gct_uncalib_gen = 0;
  jetTowerEnergyUp4_gct_uncalib_gen = 0;
  jetTowerEnergyUp5_gct_uncalib_gen = 0;
  jetTowerEnergyUp8_gct_uncalib_gen = 0;
  genJetMatchAlgo1_gct_uncalib_gen = 0;
  genJetMatchAlgo2_gct_uncalib_gen = 0;
  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  fChain->SetBranchAddress("mNPV", &mNPV, &b_mNPV);
  fChain->SetBranchAddress("numHotTow", &numHotTow, &b_numHotTow);
  fChain->SetBranchAddress("numHotTow12", &numHotTow12, &b_numHotTow12);
  fChain->SetBranchAddress("medianRho", &medianRho, &b_medianRho);
  fChain->SetBranchAddress("sumsET_", &sumsET_, &b_ET);
  fChain->SetBranchAddress("sumsMETx_,", &sumsMETx__, &b_METx);
  fChain->SetBranchAddress("sumsMETy_", &sumsMETy_, &b_METy);
  fChain->SetBranchAddress("sumsMET_", &sumsMET_, &b_MET);
  if(!doNGun){
    fChain->SetBranchAddress("jetPt_ak4_gen", &jetPt_ak4_gen, &b_jetPt_ak4_gen);
    fChain->SetBranchAddress("jetArea_ak4_gen", &jetArea_ak4_gen, &b_jetArea_ak4_gen);
    fChain->SetBranchAddress("jetFirEta_ak4_gen", &jetFirEta_ak4_gen, &b_jetFirEta_ak4_gen);
    fChain->SetBranchAddress("jetCovEtaPhi_ak4_gen", &jetCovEtaPhi_ak4_gen, &b_jetCovEtaPhi_ak4_gen);
    fChain->SetBranchAddress("jetFirPhi_ak4_gen", &jetFirPhi_ak4_gen, &b_jetFirPhi_ak4_gen);
    fChain->SetBranchAddress("jetSecEta_ak4_gen", &jetSecEta_ak4_gen, &b_jetSecEta_ak4_gen);
    fChain->SetBranchAddress("jetSecPhi_ak4_gen", &jetSecPhi_ak4_gen, &b_jetSecPhi_ak4_gen);
    fChain->SetBranchAddress("jetPhi_ak4_gen", &jetPhi_ak4_gen, &b_jetPhi_ak4_gen);
    fChain->SetBranchAddress("jetEta_ak4_gen", &jetEta_ak4_gen, &b_jetEta_ak4_gen);
    fChain->SetBranchAddress("jetDonut_ak4_gen", &jetDonut_ak4_gen, &b_jetDonut_ak4_gen);
    fChain->SetBranchAddress("jetMatchedPt_ak4_gen", &jetMatchedPt_ak4_gen, &b_jetMatchedPt_ak4_gen);
    fChain->SetBranchAddress("jetMinDR_ak4_gen", &jetMinDR_ak4_gen, &b_jetMinDR_ak4_gen);
    fChain->SetBranchAddress("jetTowerEnergyUp1_ak4_gen", &jetTowerEnergyUp1_ak4_gen, &b_jetTowerEnergyUp1_ak4_gen);
    fChain->SetBranchAddress("jetTowerEnergyUp2_ak4_gen", &jetTowerEnergyUp2_ak4_gen, &b_jetTowerEnergyUp2_ak4_gen);
    fChain->SetBranchAddress("jetTowerEnergyUp3_ak4_gen", &jetTowerEnergyUp3_ak4_gen, &b_jetTowerEnergyUp3_ak4_gen);
    fChain->SetBranchAddress("jetTowerEnergyUp4_ak4_gen", &jetTowerEnergyUp4_ak4_gen, &b_jetTowerEnergyUp4_ak4_gen);
    fChain->SetBranchAddress("jetTowerEnergyUp5_ak4_gen", &jetTowerEnergyUp5_ak4_gen, &b_jetTowerEnergyUp5_ak4_gen);
    fChain->SetBranchAddress("jetTowerEnergyUp8_ak4_gen", &jetTowerEnergyUp8_ak4_gen, &b_jetTowerEnergyUp8_ak4_gen);
    fChain->SetBranchAddress("sumsHT_ak4_gen_sum", &sumsHT_ak4_gen_sum, &b_sumsHT_ak4_gen_sum);
    fChain->SetBranchAddress("sumsMHT_ak4_gen_sum", &sumsMHT_ak4_gen_sum, &b_sumsMHT_ak4_gen_sum);
    fChain->SetBranchAddress("sumsMHTx_ak4_gen_sum", &sumsMHTx_ak4_gen_sum, &b_sumsMHTx_ak4_gen_sum);
    fChain->SetBranchAddress("sumsMHTy_ak4_gen_sum", &sumsMHTy_ak4_gen_sum, &b_sumsMHTy_ak4_gen_sum);
    fChain->SetBranchAddress("genJetMatchAlgo1_ak4_gen", &genJetMatchAlgo1_ak4_gen, &b_genJetMatchAlgo1_ak4_gen);
    fChain->SetBranchAddress("genJetMatchAlgo2_ak4_gen", &genJetMatchAlgo2_ak4_gen, &b_genJetMatchAlgo2_ak4_gen);
  }
  fChain->SetBranchAddress("jetPt_5400_chunky", &jetPt_5400_chunky, &b_jetPt_5400_chunky);
  fChain->SetBranchAddress("jetArea_5400_chunky", &jetArea_5400_chunky, &b_jetArea_5400_chunky);
  fChain->SetBranchAddress("jetFirEta_5400_chunky", &jetFirEta_5400_chunky, &b_jetFirEta_5400_chunky);
  fChain->SetBranchAddress("jetCovEtaPhi_5400_chunky", &jetCovEtaPhi_5400_chunky, &b_jetCovEtaPhi_5400_chunky);
  fChain->SetBranchAddress("jetFirPhi_5400_chunky", &jetFirPhi_5400_chunky, &b_jetFirPhi_5400_chunky);
  fChain->SetBranchAddress("jetSecEta_5400_chunky", &jetSecEta_5400_chunky, &b_jetSecEta_5400_chunky);
  fChain->SetBranchAddress("jetSecPhi_5400_chunky", &jetSecPhi_5400_chunky, &b_jetSecPhi_5400_chunky);
  fChain->SetBranchAddress("jetPhi_5400_chunky", &jetPhi_5400_chunky, &b_jetPhi_5400_chunky);
  fChain->SetBranchAddress("jetEta_5400_chunky", &jetEta_5400_chunky, &b_jetEta_5400_chunky);
  fChain->SetBranchAddress("jetDonut_5400_chunky", &jetDonut_5400_chunky, &b_jetDonut_5400_chunky);
  fChain->SetBranchAddress("jetMatchedPt_5400_chunky", &jetMatchedPt_5400_chunky, &b_jetMatchedPt_5400_chunky);
  fChain->SetBranchAddress("jetMinDR_5400_chunky", &jetMinDR_5400_chunky, &b_jetMinDR_5400_chunky);
  fChain->SetBranchAddress("jetTowerEnergyUp1_5400_chunky", &jetTowerEnergyUp1_5400_chunky, &b_jetTowerEnergyUp1_5400_chunky);
  fChain->SetBranchAddress("jetTowerEnergyUp2_5400_chunky", &jetTowerEnergyUp2_5400_chunky, &b_jetTowerEnergyUp2_5400_chunky);
  fChain->SetBranchAddress("jetTowerEnergyUp3_5400_chunky", &jetTowerEnergyUp3_5400_chunky, &b_jetTowerEnergyUp3_5400_chunky);
  fChain->SetBranchAddress("jetTowerEnergyUp4_5400_chunky", &jetTowerEnergyUp4_5400_chunky, &b_jetTowerEnergyUp4_5400_chunky);
  fChain->SetBranchAddress("jetTowerEnergyUp5_5400_chunky", &jetTowerEnergyUp5_5400_chunky, &b_jetTowerEnergyUp5_5400_chunky);
  fChain->SetBranchAddress("jetTowerEnergyUp8_5400_chunky", &jetTowerEnergyUp8_5400_chunky, &b_jetTowerEnergyUp8_5400_chunky);
  fChain->SetBranchAddress("jetOuterStripsEnergy_0_5400_chunky", &jetOuterStripsEnergy_0_5400_chunky, &b_jetOuterStripsEnergy_0_5400_chunky);
  fChain->SetBranchAddress("jetOuterStripsArea_0_5400_chunky", &jetOuterStripsArea_0_5400_chunky, &b_jetOuterStripsArea_0_5400_chunky);
  fChain->SetBranchAddress("jetOuterStripsEnergy_1_5400_chunky", &jetOuterStripsEnergy_1_5400_chunky, &b_jetOuterStripsEnergy_1_5400_chunky);
  fChain->SetBranchAddress("jetOuterStripsArea_1_5400_chunky", &jetOuterStripsArea_1_5400_chunky, &b_jetOuterStripsArea_1_5400_chunky);
  fChain->SetBranchAddress("jetOuterStripsEnergy_2_5400_chunky", &jetOuterStripsEnergy_2_5400_chunky, &b_jetOuterStripsEnergy_2_5400_chunky);
  fChain->SetBranchAddress("jetOuterStripsArea_2_5400_chunky", &jetOuterStripsArea_2_5400_chunky, &b_jetOuterStripsArea_2_5400_chunky);
  fChain->SetBranchAddress("jetOuterStripsEnergy_3_5400_chunky", &jetOuterStripsEnergy_3_5400_chunky, &b_jetOuterStripsEnergy_3_5400_chunky);
  fChain->SetBranchAddress("jetOuterStripsArea_3_5400_chunky", &jetOuterStripsArea_3_5400_chunky, &b_jetOuterStripsArea_3_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsEnergy_0_5400_chunky", &jetRingSumsEnergy_0_5400_chunky, &b_jetRingSumsEnergy_0_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsHighest_0_5400_chunky", &jetRingSumsHighest_0_5400_chunky, &b_jetRingSumsHighest_0_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsArea_0_5400_chunky", &jetRingSumsArea_0_5400_chunky, &b_jetRingSumsArea_0_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsEnergy_1_5400_chunky", &jetRingSumsEnergy_1_5400_chunky, &b_jetRingSumsEnergy_1_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsHighest_1_5400_chunky", &jetRingSumsHighest_1_5400_chunky, &b_jetRingSumsHighest_1_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsArea_1_5400_chunky", &jetRingSumsArea_1_5400_chunky, &b_jetRingSumsArea_1_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsEnergy_2_5400_chunky", &jetRingSumsEnergy_2_5400_chunky, &b_jetRingSumsEnergy_2_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsHighest_2_5400_chunky", &jetRingSumsHighest_2_5400_chunky, &b_jetRingSumsHighest_2_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsArea_2_5400_chunky", &jetRingSumsArea_2_5400_chunky, &b_jetRingSumsArea_2_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsEnergy_3_5400_chunky", &jetRingSumsEnergy_3_5400_chunky, &b_jetRingSumsEnergy_3_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsHighest_3_5400_chunky", &jetRingSumsHighest_3_5400_chunky, &b_jetRingSumsHighest_3_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsArea_3_5400_chunky", &jetRingSumsArea_3_5400_chunky, &b_jetRingSumsArea_3_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsEnergy_4_5400_chunky", &jetRingSumsEnergy_4_5400_chunky, &b_jetRingSumsEnergy_4_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsHighest_4_5400_chunky", &jetRingSumsHighest_4_5400_chunky, &b_jetRingSumsHighest_4_5400_chunky);
  fChain->SetBranchAddress("jetRingSumsArea_4_5400_chunky", &jetRingSumsArea_4_5400_chunky, &b_jetRingSumsArea_4_5400_chunky);
  fChain->SetBranchAddress("genJetMatchAlgo1_5400_chunky", &genJetMatchAlgo1_5400_chunky, &b_genJetMatchAlgo1_5400_chunky);
  fChain->SetBranchAddress("genJetMatchAlgo2_5400_chunky", &genJetMatchAlgo2_5400_chunky, &b_genJetMatchAlgo2_5400_chunky);
  fChain->SetBranchAddress("sumsHT_5400_chunky_sum", &sumsHT_5400_chunky_sum, &b_sumsHT_5400_chunky_sum);
  fChain->SetBranchAddress("sumsMHT_5400_chunky_sum", &sumsMHT_5400_chunky_sum, &b_sumsMHT_5400_chunky_sum);
  fChain->SetBranchAddress("sumsMHTx_5400_chunky_sum", &sumsMHTx_5400_chunky_sum, &b_sumsMHTx_5400_chunky_sum);
  fChain->SetBranchAddress("sumsMHTy_5400_chunky_sum", &sumsMHTy_5400_chunky_sum, &b_sumsMHTy_5400_chunky_sum);
  fChain->SetBranchAddress("jetPt_L1_for_Nick", &jetPt_L1_for_Nick, &b_jetPt_L1_for_Nick);
  fChain->SetBranchAddress("jetArea_L1_for_Nick", &jetArea_L1_for_Nick, &b_jetArea_L1_for_Nick);
  fChain->SetBranchAddress("jetFirEta_L1_for_Nick", &jetFirEta_L1_for_Nick, &b_jetFirEta_L1_for_Nick);
  fChain->SetBranchAddress("jetCovEtaPhi_L1_for_Nick", &jetCovEtaPhi_L1_for_Nick, &b_jetCovEtaPhi_L1_for_Nick);
  fChain->SetBranchAddress("jetFirPhi_L1_for_Nick", &jetFirPhi_L1_for_Nick, &b_jetFirPhi_L1_for_Nick);
  fChain->SetBranchAddress("jetSecEta_L1_for_Nick", &jetSecEta_L1_for_Nick, &b_jetSecEta_L1_for_Nick);
  fChain->SetBranchAddress("jetSecPhi_L1_for_Nick", &jetSecPhi_L1_for_Nick, &b_jetSecPhi_L1_for_Nick);
  fChain->SetBranchAddress("jetPhi_L1_for_Nick", &jetPhi_L1_for_Nick, &b_jetPhi_L1_for_Nick);
  fChain->SetBranchAddress("jetEta_L1_for_Nick", &jetEta_L1_for_Nick, &b_jetEta_L1_for_Nick);
  fChain->SetBranchAddress("jetDonut_L1_for_Nick", &jetDonut_L1_for_Nick, &b_jetDonut_L1_for_Nick);
  fChain->SetBranchAddress("jetMatchedPt_L1_for_Nick", &jetMatchedPt_L1_for_Nick, &b_jetMatchedPt_L1_for_Nick);
  fChain->SetBranchAddress("jetMinDR_L1_for_Nick", &jetMinDR_L1_for_Nick, &b_jetMinDR_L1_for_Nick);
  fChain->SetBranchAddress("jetTowerEnergyUp1_L1_for_Nick", &jetTowerEnergyUp1_L1_for_Nick, &b_jetTowerEnergyUp1_L1_for_Nick);
  fChain->SetBranchAddress("jetTowerEnergyUp2_L1_for_Nick", &jetTowerEnergyUp2_L1_for_Nick, &b_jetTowerEnergyUp2_L1_for_Nick);
  fChain->SetBranchAddress("jetTowerEnergyUp3_L1_for_Nick", &jetTowerEnergyUp3_L1_for_Nick, &b_jetTowerEnergyUp3_L1_for_Nick);
  fChain->SetBranchAddress("jetTowerEnergyUp4_L1_for_Nick", &jetTowerEnergyUp4_L1_for_Nick, &b_jetTowerEnergyUp4_L1_for_Nick);
  fChain->SetBranchAddress("jetTowerEnergyUp5_L1_for_Nick", &jetTowerEnergyUp5_L1_for_Nick, &b_jetTowerEnergyUp5_L1_for_Nick);
  fChain->SetBranchAddress("jetTowerEnergyUp8_L1_for_Nick", &jetTowerEnergyUp8_L1_for_Nick, &b_jetTowerEnergyUp8_L1_for_Nick);
  fChain->SetBranchAddress("jetOuterStripsEnergy_0_L1_for_Nick", &jetOuterStripsEnergy_0_L1_for_Nick, &b_jetOuterStripsEnergy_0_L1_for_Nick);
  fChain->SetBranchAddress("jetOuterStripsArea_0_L1_for_Nick", &jetOuterStripsArea_0_L1_for_Nick, &b_jetOuterStripsArea_0_L1_for_Nick);
  fChain->SetBranchAddress("jetOuterStripsEnergy_1_L1_for_Nick", &jetOuterStripsEnergy_1_L1_for_Nick, &b_jetOuterStripsEnergy_1_L1_for_Nick);
  fChain->SetBranchAddress("jetOuterStripsArea_1_L1_for_Nick", &jetOuterStripsArea_1_L1_for_Nick, &b_jetOuterStripsArea_1_L1_for_Nick);
  fChain->SetBranchAddress("jetOuterStripsEnergy_2_L1_for_Nick", &jetOuterStripsEnergy_2_L1_for_Nick, &b_jetOuterStripsEnergy_2_L1_for_Nick);
  fChain->SetBranchAddress("jetOuterStripsArea_2_L1_for_Nick", &jetOuterStripsArea_2_L1_for_Nick, &b_jetOuterStripsArea_2_L1_for_Nick);
  fChain->SetBranchAddress("jetOuterStripsEnergy_3_L1_for_Nick", &jetOuterStripsEnergy_3_L1_for_Nick, &b_jetOuterStripsEnergy_3_L1_for_Nick);
  fChain->SetBranchAddress("jetOuterStripsArea_3_L1_for_Nick", &jetOuterStripsArea_3_L1_for_Nick, &b_jetOuterStripsArea_3_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsEnergy_0_L1_for_Nick", &jetRingSumsEnergy_0_L1_for_Nick, &b_jetRingSumsEnergy_0_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHighest_0_L1_for_Nick", &jetRingSumsHighest_0_L1_for_Nick, &b_jetRingSumsHighest_0_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsArea_0_L1_for_Nick", &jetRingSumsArea_0_L1_for_Nick, &b_jetRingSumsArea_0_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsEnergy_1_L1_for_Nick", &jetRingSumsEnergy_1_L1_for_Nick, &b_jetRingSumsEnergy_1_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHighest_1_L1_for_Nick", &jetRingSumsHighest_1_L1_for_Nick, &b_jetRingSumsHighest_1_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsArea_1_L1_for_Nick", &jetRingSumsArea_1_L1_for_Nick, &b_jetRingSumsArea_1_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsEnergy_2_L1_for_Nick", &jetRingSumsEnergy_2_L1_for_Nick, &b_jetRingSumsEnergy_2_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHighest_2_L1_for_Nick", &jetRingSumsHighest_2_L1_for_Nick, &b_jetRingSumsHighest_2_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsArea_2_L1_for_Nick", &jetRingSumsArea_2_L1_for_Nick, &b_jetRingSumsArea_2_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsEnergy_3_L1_for_Nick", &jetRingSumsEnergy_3_L1_for_Nick, &b_jetRingSumsEnergy_3_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHighest_3_L1_for_Nick", &jetRingSumsHighest_3_L1_for_Nick, &b_jetRingSumsHighest_3_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsArea_3_L1_for_Nick", &jetRingSumsArea_3_L1_for_Nick, &b_jetRingSumsArea_3_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsEnergy_4_L1_for_Nick", &jetRingSumsEnergy_4_L1_for_Nick, &b_jetRingSumsEnergy_4_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHighest_4_L1_for_Nick", &jetRingSumsHighest_4_L1_for_Nick, &b_jetRingSumsHighest_4_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsArea_4_L1_for_Nick", &jetRingSumsArea_4_L1_for_Nick, &b_jetRingSumsArea_4_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsECAL_0_L1_for_Nick", &jetRingSumsECAL_0_L1_for_Nick, &b_jetRingSumsECAL_0_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsECAL_1_L1_for_Nick", &jetRingSumsECAL_1_L1_for_Nick, &b_jetRingSumsECAL_1_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsECAL_2_L1_for_Nick", &jetRingSumsECAL_2_L1_for_Nick, &b_jetRingSumsECAL_2_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsECAL_3_L1_for_Nick", &jetRingSumsECAL_3_L1_for_Nick, &b_jetRingSumsECAL_3_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsECAL_4_L1_for_Nick", &jetRingSumsECAL_4_L1_for_Nick, &b_jetRingSumsECAL_4_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHCAL_0_L1_for_Nick", &jetRingSumsHCAL_0_L1_for_Nick, &b_jetRingSumsHCAL_0_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHCAL_1_L1_for_Nick", &jetRingSumsHCAL_1_L1_for_Nick, &b_jetRingSumsHCAL_1_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHCAL_2_L1_for_Nick", &jetRingSumsHCAL_2_L1_for_Nick, &b_jetRingSumsHCAL_2_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHCAL_3_L1_for_Nick", &jetRingSumsHCAL_3_L1_for_Nick, &b_jetRingSumsHCAL_3_L1_for_Nick);
  fChain->SetBranchAddress("jetRingSumsHCAL_4_L1_for_Nick", &jetRingSumsHCAL_4_L1_for_Nick, &b_jetRingSumsHCAL_4_L1_for_Nick);
  fChain->SetBranchAddress("genJetMatchAlgo1_L1_for_Nick", &genJetMatchAlgo1_L1_for_Nick, &b_genJetMatchAlgo1_L1_for_Nick);
  fChain->SetBranchAddress("genJetMatchAlgo2_L1_for_Nick", &genJetMatchAlgo2_L1_for_Nick, &b_genJetMatchAlgo2_L1_for_Nick);
  fChain->SetBranchAddress("sumsHT_L1_for_Nick_sum", &sumsHT_L1_for_Nick_sum, &b_sumsHT_L1_for_Nick_sum);
  fChain->SetBranchAddress("sumsMHT_L1_for_Nick_sum", &sumsMHT_L1_for_Nick_sum, &b_sumsMHT_L1_for_Nick_sum);
  fChain->SetBranchAddress("sumsMHTx_L1_for_Nick_sum", &sumsMHTx_L1_for_Nick_sum, &b_sumsMHTx_L1_for_Nick_sum);
  fChain->SetBranchAddress("sumsMHTy_L1_for_Nick_sum", &sumsMHTy_L1_for_Nick_sum, &b_sumsMHTy_L1_for_Nick_sum);
  fChain->SetBranchAddress("jetPt_gct_calib_gen", &jetPt_gct_calib_gen, &b_jetPt_gct_calib_gen);
  fChain->SetBranchAddress("jetArea_gct_calib_gen", &jetArea_gct_calib_gen, &b_jetArea_gct_calib_gen);
  fChain->SetBranchAddress("jetFirEta_gct_calib_gen", &jetFirEta_gct_calib_gen, &b_jetFirEta_gct_calib_gen);
  fChain->SetBranchAddress("jetCovEtaPhi_gct_calib_gen", &jetCovEtaPhi_gct_calib_gen, &b_jetCovEtaPhi_gct_calib_gen);
  fChain->SetBranchAddress("jetFirPhi_gct_calib_gen", &jetFirPhi_gct_calib_gen, &b_jetFirPhi_gct_calib_gen);
  fChain->SetBranchAddress("jetSecEta_gct_calib_gen", &jetSecEta_gct_calib_gen, &b_jetSecEta_gct_calib_gen);
  fChain->SetBranchAddress("jetSecPhi_gct_calib_gen", &jetSecPhi_gct_calib_gen, &b_jetSecPhi_gct_calib_gen);
  fChain->SetBranchAddress("jetPhi_gct_calib_gen", &jetPhi_gct_calib_gen, &b_jetPhi_gct_calib_gen);
  fChain->SetBranchAddress("jetEta_gct_calib_gen", &jetEta_gct_calib_gen, &b_jetEta_gct_calib_gen);
  fChain->SetBranchAddress("jetDonut_gct_calib_gen", &jetDonut_gct_calib_gen, &b_jetDonut_gct_calib_gen);
  fChain->SetBranchAddress("jetMatchedPt_gct_calib_gen", &jetMatchedPt_gct_calib_gen, &b_jetMatchedPt_gct_calib_gen);
  fChain->SetBranchAddress("jetMinDR_gct_calib_gen", &jetMinDR_gct_calib_gen, &b_jetMinDR_gct_calib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp1_gct_calib_gen", &jetTowerEnergyUp1_gct_calib_gen, &b_jetTowerEnergyUp1_gct_calib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp2_gct_calib_gen", &jetTowerEnergyUp2_gct_calib_gen, &b_jetTowerEnergyUp2_gct_calib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp3_gct_calib_gen", &jetTowerEnergyUp3_gct_calib_gen, &b_jetTowerEnergyUp3_gct_calib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp4_gct_calib_gen", &jetTowerEnergyUp4_gct_calib_gen, &b_jetTowerEnergyUp4_gct_calib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp5_gct_calib_gen", &jetTowerEnergyUp5_gct_calib_gen, &b_jetTowerEnergyUp5_gct_calib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp8_gct_calib_gen", &jetTowerEnergyUp8_gct_calib_gen, &b_jetTowerEnergyUp8_gct_calib_gen);
  fChain->SetBranchAddress("genJetMatchAlgo1_gct_calib_gen", &genJetMatchAlgo1_gct_calib_gen, &b_genJetMatchAlgo1_gct_calib_gen);
  fChain->SetBranchAddress("genJetMatchAlgo2_gct_calib_gen", &genJetMatchAlgo2_gct_calib_gen, &b_genJetMatchAlgo2_gct_calib_gen);
  fChain->SetBranchAddress("sumsHT_gct_calib_gen_sum", &sumsHT_gct_calib_gen_sum, &b_sumsHT_gct_calib_gen_sum);
  fChain->SetBranchAddress("sumsMHT_gct_calib_gen_sum", &sumsMHT_gct_calib_gen_sum, &b_sumsMHT_gct_calib_gen_sum);
  fChain->SetBranchAddress("sumsMHTx_gct_calib_gen_sum", &sumsMHTx_gct_calib_gen_sum, &b_sumsMHTx_gct_calib_gen_sum);
  fChain->SetBranchAddress("sumsMHTy_gct_calib_gen_sum", &sumsMHTy_gct_calib_gen_sum, &b_sumsMHTy_gct_calib_gen_sum);
  fChain->SetBranchAddress("jetPt_gct_uncalib_gen", &jetPt_gct_uncalib_gen, &b_jetPt_gct_uncalib_gen);
  fChain->SetBranchAddress("jetArea_gct_uncalib_gen", &jetArea_gct_uncalib_gen, &b_jetArea_gct_uncalib_gen);
  fChain->SetBranchAddress("jetFirEta_gct_uncalib_gen", &jetFirEta_gct_uncalib_gen, &b_jetFirEta_gct_uncalib_gen);
  fChain->SetBranchAddress("jetCovEtaPhi_gct_uncalib_gen", &jetCovEtaPhi_gct_uncalib_gen, &b_jetCovEtaPhi_gct_uncalib_gen);
  fChain->SetBranchAddress("jetFirPhi_gct_uncalib_gen", &jetFirPhi_gct_uncalib_gen, &b_jetFirPhi_gct_uncalib_gen);
  fChain->SetBranchAddress("jetSecEta_gct_uncalib_gen", &jetSecEta_gct_uncalib_gen, &b_jetSecEta_gct_uncalib_gen);
  fChain->SetBranchAddress("jetSecPhi_gct_uncalib_gen", &jetSecPhi_gct_uncalib_gen, &b_jetSecPhi_gct_uncalib_gen);
  fChain->SetBranchAddress("jetPhi_gct_uncalib_gen", &jetPhi_gct_uncalib_gen, &b_jetPhi_gct_uncalib_gen);
  fChain->SetBranchAddress("jetEta_gct_uncalib_gen", &jetEta_gct_uncalib_gen, &b_jetEta_gct_uncalib_gen);
  fChain->SetBranchAddress("jetDonut_gct_uncalib_gen", &jetDonut_gct_uncalib_gen, &b_jetDonut_gct_uncalib_gen);
  fChain->SetBranchAddress("jetMatchedPt_gct_uncalib_gen", &jetMatchedPt_gct_uncalib_gen, &b_jetMatchedPt_gct_uncalib_gen);
  fChain->SetBranchAddress("jetMinDR_gct_uncalib_gen", &jetMinDR_gct_uncalib_gen, &b_jetMinDR_gct_uncalib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp1_gct_uncalib_gen", &jetTowerEnergyUp1_gct_uncalib_gen, &b_jetTowerEnergyUp1_gct_uncalib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp2_gct_uncalib_gen", &jetTowerEnergyUp2_gct_uncalib_gen, &b_jetTowerEnergyUp2_gct_uncalib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp3_gct_uncalib_gen", &jetTowerEnergyUp3_gct_uncalib_gen, &b_jetTowerEnergyUp3_gct_uncalib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp4_gct_uncalib_gen", &jetTowerEnergyUp4_gct_uncalib_gen, &b_jetTowerEnergyUp4_gct_uncalib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp5_gct_uncalib_gen", &jetTowerEnergyUp5_gct_uncalib_gen, &b_jetTowerEnergyUp5_gct_uncalib_gen);
  fChain->SetBranchAddress("jetTowerEnergyUp8_gct_uncalib_gen", &jetTowerEnergyUp8_gct_uncalib_gen, &b_jetTowerEnergyUp8_gct_uncalib_gen);
  fChain->SetBranchAddress("genJetMatchAlgo1_gct_uncalib_gen", &genJetMatchAlgo1_gct_uncalib_gen, &b_genJetMatchAlgo1_gct_uncalib_gen);
  fChain->SetBranchAddress("genJetMatchAlgo2_gct_uncalib_gen", &genJetMatchAlgo2_gct_uncalib_gen, &b_genJetMatchAlgo2_gct_uncalib_gen);
  fChain->SetBranchAddress("sumsHT_gct_uncalib_gen_sum", &sumsHT_gct_uncalib_gen_sum, &b_sumsHT_gct_uncalib_gen_sum);
  fChain->SetBranchAddress("sumsMHT_gct_uncalib_gen_sum", &sumsMHT_gct_uncalib_gen_sum, &b_sumsMHT_gct_uncalib_gen_sum);
  fChain->SetBranchAddress("sumsMHTx_gct_uncalib_gen_sum", &sumsMHTx_gct_uncalib_gen_sum, &b_sumsMHTx_gct_uncalib_gen_sum);
  fChain->SetBranchAddress("sumsMHTy_gct_uncalib_gen_sum", &sumsMHTy_gct_uncalib_gen_sum, &b_sumsMHTy_gct_uncalib_gen_sum);
  Notify();
}

Bool_t JetMaker::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void JetMaker::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
/*Int_t JetMaker::Cut(Long64_t entry)
  {
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
return 1;
}*/
#endif // #ifdef JetMaker_cxx
