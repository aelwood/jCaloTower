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
    std::map<TString, std::vector<float>* > jetMatchedPts;
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
    std::map<TString, TBranch* > jetMatchedPtBranches;
    std::map<TString, TBranch* > jetEtaBranches;
    std::map<TString, TBranch* > jetPhiBranches;
    std::map<TString, double > ht;
    std::map<TString, double > mhtX;
    std::map<TString, double > mht;
    std::map<TString, double > mhtY;
    std::map<TString, TBranch* > htBranches;
    std::map<TString, TBranch* > mhtXBranches;
    std::map<TString, TBranch* > mhtBranches;
    std::map<TString, TBranch* > mhtYBranches;

    double met,metCalib,et,etCalib;
    TBranch* metBranch;
    TBranch* etBranch;
    TBranch* nIntsBranch;
    int nInts,nIntsCalib;

    RecalibTrees(TTree* tree=0, bool doingNGun=false, double useEtaCut=3.0);
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
RecalibTrees::RecalibTrees(TTree* tree, bool doingNGun, double useEtaCut) : fChain(0) 
{
  doNGun=doingNGun;

  etaCut = useEtaCut;

  if(tree==0){
    std::cout << "Please input a tree" << std::endl;
  }else{

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
    jetTypes.push_back("gen");
    jetTypes.push_back("uct");
    jetTypes.push_back("gct");


    Init(tree);

    if(doNGun){
      outFile = new TFile("calibJetsNGun.root","RECREATE");
    }else{
      outFile = new TFile("calibJetsSignal.root","RECREATE");
    }

    friendTree = new TTree("jetTree","jetTree");

    //Initialise memory for the friend tree
    for(std::vector<TString>::const_iterator iType=jetTypes.begin();
        iType!=jetTypes.end(); iType++){

      jetCalibPts[*iType] = new std::vector<float>();
      jetCalibPhis[*iType] = new std::vector<float>();
      jetCalibEtas[*iType] = new std::vector<float>();
      jetCalibMatchedPts[*iType] = new std::vector<float>();
      //htCalib[*iType] = 0;
      //mhtXCalib[*iType] = 0;
      //mhtYCalib[*iType] = 0;
      //mhtCalib[*iType] = 0;
      friendTree->Branch("jetPt_calib_"+*iType, "std::vector<float>", &jetCalibPts[*iType] );
      friendTree->Branch("jetEta_calib_"+*iType, "std::vector<float>", &jetCalibEtas[*iType] );
      friendTree->Branch("jetPhi_calib_"+*iType, "std::vector<float>", &jetCalibPhis[*iType] );
      friendTree->Branch("jetMatchedPt_calib_"+*iType, "std::vector<float>", &jetCalibMatchedPts[*iType] );
      friendTree->Branch("ht_calib_"+*iType, &htCalib[*iType], "ht_calib_"+*iType+"/D");
      friendTree->Branch("mhtX_calib_"+*iType, &mhtXCalib[*iType], "mhtX_calib_"+*iType+"/D");
      friendTree->Branch("mht_calib_"+*iType, &mhtCalib[*iType], "mht_calib_"+*iType+"/D");
      friendTree->Branch("mhtY_calib_"+*iType, &mhtYCalib[*iType], "mhtY_calib_"+*iType+"/D");

    }
    friendTree->Branch("met_calib", &metCalib, "met_calib/D");
    friendTree->Branch("et_calib", &etCalib, "et_calib/D");
    friendTree->Branch("nInts_calib", &nIntsCalib, "nInts_calib/I");

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
    jetMatchedPts[*iType]=0;
    jetEtas[*iType]=0;
    jetPhis[*iType]=0;

  }

  // Set branch addresses and branch pointers
  if (!tree) return;
  std::cout<<"setting fchain" << std::endl;
  fChain = tree;
  fCurrent = -1;
  fChain->SetMakeClass(1);


  for(std::vector<TString>::const_iterator iType=jetTypes.begin();
      iType!=jetTypes.end(); iType++){

    //if(doNGun && *iType=="gen") continue;
    fChain->SetBranchAddress("jetPt_"+*iType, &jetPts[*iType], &jetPtBranches[*iType]);
    fChain->SetBranchAddress("jetMatchedPt_"+*iType, &jetMatchedPts[*iType], &jetMatchedPtBranches[*iType]);
    fChain->SetBranchAddress("jetEta_"+*iType, &jetEtas[*iType], &jetEtaBranches[*iType]);
    fChain->SetBranchAddress("jetPhi_"+*iType, &jetPhis[*iType], &jetPhiBranches[*iType]);
    fChain->SetBranchAddress("mht_"+*iType, &mht[*iType], &mhtBranches[*iType]);
    fChain->SetBranchAddress("ht_"+*iType, &ht[*iType], &htBranches[*iType]);
    fChain->SetBranchAddress("mhtX_"+*iType, &mhtX[*iType], &mhtXBranches[*iType]);
    fChain->SetBranchAddress("mhtY_"+*iType, &mhtY[*iType], &mhtYBranches[*iType]);
  }
  fChain->SetBranchAddress("met", &met, &metBranch);
  fChain->SetBranchAddress("et", &et, &etBranch);
  fChain->SetBranchAddress("nInts", &nInts, &nIntsBranch);

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
