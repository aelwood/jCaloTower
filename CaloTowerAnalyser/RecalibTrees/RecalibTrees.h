//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul  8 14:51:38 2014 by ROOT version 5.34/07
// from TTree L1Tree/L1Tree
// found on file: /home/adam/ttbar_output.root
//////////////////////////////////////////////////////////

#ifndef RecalibTrees_h
#define RecalibTrees_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TLorentzVector.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>
#include <iostream>

// Fixed size dimensions of array or collections stored in the TTree if any.

class RecalibTrees {
  public :
    TTree          *fChain;   //!pointer to the analyzed TTree or TChain
    Int_t           fCurrent; //!current Tree number in a TChain

    //Add a new "friend" tree
    TFile* outFile;
    TTree* friendTree;

    bool doNGun;
    double etaCut;
    
    std::vector<TString> jetTypes;
    std::map<TString, std::vector<float>* > jetPts;
    std::map<TString, std::vector<float>* > jetCalibPts;
    std::map<TString, std::vector<float>* > jetCalibMatchedPts;
    std::map<TString, std::vector<float>* > jetCalibPhis;
    std::map<TString, std::vector<float>* > jetCalibEtas;
    std::map<TString, std::vector<float>* > jetEtas;
    std::map<TString, std::vector<float>* > jetPhis;
    std::map<TString, double > htCalib;
    std::map<TString, double > mhtXCalib;
    std::map<TString, double > mhtCalib;
    std::map<TString, double > mhtYCalib;
    std::map<TString, TBranch* > jetPtBranches;
    std::map<TString, TBranch* > jetEtaBranches;
    std::map<TString, TBranch* > jetPhiBranches;

    RecalibTrees(bool doingNGun=false, double useEtaCut=3.0);
    virtual ~RecalibTrees();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef RecalibTrees_cxx
RecalibTrees::RecalibTrees(bool doingNGun, double useEtaCut) //: fChain(0) 
{
  doNGun=doingNGun;

  etaCut = useEtaCut;
  
  TString s1,s2;
  //TTree* tree;
  //TTree* fullTree;

  if(doNGun){
    s1="ngun_jetTree_newAreas.root";
    s2="/afs/cern.ch/work/a/aelwood/public/NGUN/140729/ngun_14-07-29.root";
  }else{
    s1="ttbar_jetTree_newAreas.root";
    s2="/afs/cern.ch/work/a/aelwood/public/TTBAR/140729/ttbar_14-07-29.root";
  }


  TFile *f1 = (TFile*)gROOT->GetListOfFiles()->FindObject(s1);

  if (!f1 || !f1->IsOpen()) {
    f1 = new TFile(s1);
  }

  TTree * tree = (TTree *)f1->Get("jetTree");
  if(!doNGun){
    tree->AddFriend("demo/L1Tree",s2);
  }
  //Define the jet types
  jetTypes.push_back("s0_nopus");
  jetTypes.push_back("s0_donut");
  jetTypes.push_back("s0_global");
  jetTypes.push_back("s0_chunky");
  jetTypes.push_back("s0_tsup1");
  jetTypes.push_back("s0_tsup2");
  //jetTypes.push_back("s0_tsup3");
  jetTypes.push_back("s5_nopus");
  jetTypes.push_back("s5_donut");
  jetTypes.push_back("s5_global");
  jetTypes.push_back("s5_chunky");
  jetTypes.push_back("s5_tsup1");
  jetTypes.push_back("s5_tsup2");
  //jetTypes.push_back("s5_tsup3");
  jetTypes.push_back("c10_nopus");
  jetTypes.push_back("c10_donut");
  jetTypes.push_back("c10_global");
  jetTypes.push_back("c10_chunky");
  jetTypes.push_back("c10_tsup1");
  jetTypes.push_back("c10_tsup2");


  Init(tree);

  if(doNGun){
    outFile = new TFile("calibJetsNGun.root","RECREATE");
  }else{
    outFile = new TFile("calibJetsTtbar.root","RECREATE");
  }

  friendTree = new TTree("jetTree","jetTree");

  //Initialise memory for the friend tree
  for(std::vector<TString>::const_iterator iType=jetTypes.begin();
      iType!=jetTypes.end(); iType++){

    jetCalibPts[*iType] = new std::vector<float>();
    jetCalibPhis[*iType] = new std::vector<float>();
    jetCalibEtas[*iType] = new std::vector<float>();
    jetCalibMatchedPts[*iType] = new std::vector<float>();
    htCalib[*iType] = 0;
    mhtXCalib[*iType] = 0;
    mhtYCalib[*iType] = 0;
    mhtCalib[*iType] = 0;
    friendTree->Branch("jetPt_calib_"+*iType, "std::vector<float>", &jetCalibPts[*iType] );
    friendTree->Branch("jetEta_calib_"+*iType, "std::vector<float>", &jetCalibEtas[*iType] );
    friendTree->Branch("jetPhi_calib_"+*iType, "std::vector<float>", &jetCalibPhis[*iType] );
    friendTree->Branch("jetMatchedPt_calib_"+*iType, "std::vector<float>", &jetCalibMatchedPts[*iType] );
    friendTree->Branch("ht_calib_"+*iType, &htCalib[*iType], "ht_calib_"+*iType+"/D");
    friendTree->Branch("mhtX_calib_"+*iType, &mhtXCalib[*iType], "mhtX_calib_"+*iType+"/D");
    friendTree->Branch("mht_calib_"+*iType, &mhtCalib[*iType], "mht_calib_"+*iType+"/D");
    friendTree->Branch("mhtY_calib_"+*iType, &mhtYCalib[*iType], "mhtY_calib_"+*iType+"/D");

  }

}

RecalibTrees::~RecalibTrees()
{

  if (!fChain) return;
  delete fChain->GetCurrentFile();
  //  delete friendTree;

}

Int_t RecalibTrees::GetEntry(Long64_t entry)
{
  // Read contents of entry.
  if (!fChain) return 0;
  return fChain->GetEntry(entry);
}
Long64_t RecalibTrees::LoadTree(Long64_t entry)
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

void RecalibTrees::Init(TTree *tree)
{
  // The Init() function is called when the selector needs to initialize
  // a new tree or chain. Typically here the branch addresses and branch
  // pointers of the tree will be set.
  // It is normally not necessary to make changes to the generated
  // code, but the routine can be extended by the user if needed.
  // Init() will be called many times when running on PROOF
  // (once per file to be processed).

  // Set object pointer

  for(std::vector<TString>::const_iterator iType=jetTypes.begin();
      iType!=jetTypes.end(); iType++){

    jetPts[*iType]=0;
    jetEtas[*iType]=0;
    jetPhis[*iType]=0;

  }

  // Set branch addresses and branch pointers
  if (!tree) return;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);

  //Get the gen information
  if(!doNGun){
    fChain->SetBranchAddress("jetPt_ak4_gen",&jetPts["Gen"],&jetPtBranches["Gen"]);
    fChain->SetBranchAddress("jetEta_ak4_gen",&jetEtas["Gen"],&jetEtaBranches["Gen"]);
    fChain->SetBranchAddress("jetPhi_ak4_gen",&jetPhis["Gen"],&jetPhiBranches["Gen"]);
  }

  for(std::vector<TString>::const_iterator iType=jetTypes.begin();
      iType!=jetTypes.end(); iType++){

    fChain->SetBranchAddress("jetPt_"+*iType, &jetPts[*iType], &jetPtBranches[*iType]);
    fChain->SetBranchAddress("jetEta_"+*iType, &jetEtas[*iType], &jetEtaBranches[*iType]);
    fChain->SetBranchAddress("jetPhi_"+*iType, &jetPhis[*iType], &jetPhiBranches[*iType]);
  }

  Notify();
}

Bool_t RecalibTrees::Notify()
{
  // The Notify() function is called when a new file is opened. This
  // can be either for a new TTree in a TChain or when when a new TTree
  // is started when using PROOF. It is normally not necessary to make changes
  // to the generated code, but the routine can be extended by the
  // user if needed. The return value is currently not used.

  return kTRUE;
}

void RecalibTrees::Show(Long64_t entry)
{
  // Print contents of entry.
  // If entry is not specified, print current entry
  if (!fChain) return;
  fChain->Show(entry);
}
Int_t RecalibTrees::Cut(Long64_t entry)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  return 1;
}
#endif // #ifdef RecalibTrees_cxx
