#define RecalibTrees_cxx

#include "RecalibTrees.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include "calibration_params.hh"
#include "MatchingAlgo.h"

namespace{

  bool sortbypt(const TLorentzVector &a, const TLorentzVector &b) { return a.Pt() > b.Pt(); } 

  void getESums(const std::vector<TLorentzVector>& jets, 
      double& ht, double& mhtX, double& mhtY, double& mht){

    ht=0;
    TLorentzVector mhtVec;

    for(unsigned i=0; i<jets.size(); i++){
      if(jets[i].Pt()>20.){
        ht+=jets[i].Pt();
        mhtVec+=jets[i];
      }
    }
    mhtX=-1.0*mhtVec.Px();
    mhtY=-1.0*mhtVec.Py();
    mht=sqrt(mhtVec.Px()*mhtVec.Px()+mhtVec.Py()*mhtVec.Py());
  }

}

void RecalibTrees::Loop()
{
  //   In a ROOT session, you can do:
  //      Root > .L RecalibTrees.C
  //      Root > RecalibTrees t
  //      Root > t.GetEntry(12); // Fill t data members with entry number 12
  //      Root > t.Show();       // Show values of entry 12
  //      Root > t.Show(16);     // Read and show values of entry 16
  //      Root > t.Loop();       // Loop on all entries
  //

  //     This is the loop skeleton where:
  //    jentry is the global entry number in the chain
  //    ientry is the entry number in the current Tree
  //  Note that the argument to GetEntry must be:
  //    jentry for TChain::GetEntry
  //    ientry for TTree::GetEntry and TBranch::GetEntry
  //
  //       To read only selected branches, Insert statements like:
  // METHOD1:
  //    fChain->SetBranchStatus("*",0);  // disable all branches
  //    fChain->SetBranchStatus("branchname",1);  // activate branchname
  // METHOD2: replace line
  //    fChain->GetEntry(jentry);       //read all branches
  //by  b_branchname->GetEntry(ientry); //read only this branch
  if (fChain == 0) return;

  Long64_t nentries = fChain->GetEntriesFast();

  //nentries = 10000;

  outFile->cd();

  //Long64_t nbytes = 0, nb = 0;
  for (Long64_t jentry=0; jentry<nentries;jentry++) {
    //Long64_t ientry = LoadTree(jentry);
    //if (ientry < 0) break;
    //nb = fChain->GetEntry(jentry);   nbytes += nb;
    // if (Cut(ientry) < 0) continue;
    //

    //Get the relevant entry to start work
    GetEntry(jentry); 

    //Make TLorentzVector jet candidates
    std::map< TString,std::vector<TLorentzVector> > jetObjects;
    std::map< TString,std::vector<TLorentzVector> > calibJetObjects;
    std::vector<TLorentzVector> genJetObjects;

    //For Gen
    if(!doNGun){
      for(unsigned i=0; i<jetPts["Gen"]->size(); i++){
        TLorentzVector jet;
        jet.SetPtEtaPhiM(jetPts["Gen"]->at(i),jetEtas["Gen"]->at(i),
            jetPhis["Gen"]->at(i),0.);
        if(jet.Eta()>100 || jet.Eta()<-100) std::cout << "Gen\n";
        genJetObjects.push_back(jet);
      }
    }

    for(std::vector<TString>::const_iterator iType=jetTypes.begin();
        iType!=jetTypes.end(); iType++){

      //Add the other jets
      for(unsigned i=0; i<jetPts[*iType]->size(); i++){
        if(fabs(jetEtas[*iType]->at(i)) < etaCut){
          TLorentzVector jet;
          jet.SetPtEtaPhiM(jetPts[*iType]->at(i),jetEtas[*iType]->at(i),
              jetPhis[*iType]->at(i),0.);
          if(jet.Eta()>100 || jet.Eta()<-100) std::cout << "Other\n";

          jetObjects[*iType].push_back(jet);
        }
      }

      calibJetObjects[*iType] = calibrateL1Jets(jetObjects[*iType],*iType,10.,9999.);

      //Sort the new calibrated objects
      std::sort(calibJetObjects[*iType].begin(),calibJetObjects[*iType].end(),sortbypt);

      //Redo the matching!
      std::vector<int> l1_matched_index_algo1;
      if(!doNGun){
        //Make all possible pairs of jets
        std::vector<pair_info> pairs = make_pairs(genJetObjects, jetObjects[*iType]);

        //Find the index of the gen jet that is matched to L1
        l1_matched_index_algo1 
          = analyse_pairs_local(pairs, jetObjects[*iType].size(),0.49);
      }

      getESums(calibJetObjects[*iType],htCalib[*iType],mhtXCalib[*iType],mhtYCalib[*iType],mhtCalib[*iType]);

      //Write to the tree and fill

      jetCalibPts[*iType]->clear();
      jetCalibMatchedPts[*iType]->clear();
      jetCalibEtas[*iType]->clear();
      jetCalibPhis[*iType]->clear();

      for(unsigned j=0; j<calibJetObjects[*iType].size(); j++){

        jetCalibPts[*iType]->push_back(calibJetObjects[*iType][j].Pt());
        jetCalibEtas[*iType]->push_back(calibJetObjects[*iType][j].Eta());
        jetCalibPhis[*iType]->push_back(calibJetObjects[*iType][j].Phi());

        if(!doNGun){
          //Fill for the matched
          if (l1_matched_index_algo1[j]!=-1)
          {
            jetCalibMatchedPts[*iType]->push_back(
                genJetObjects.at(l1_matched_index_algo1.at(j)).Pt());
          }
          else
          {
            jetCalibMatchedPts[*iType]->push_back(-1.);
          }
        }

      }
    }

    friendTree->Fill();

    if(jentry%500==0) std::cout << "Done: " << jentry << std::endl;
  }

  friendTree->Write();

  outFile->Close();
}
