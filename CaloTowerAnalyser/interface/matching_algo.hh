#ifndef __JMATCH__
#define __JMATCH__

#include <iostream>
#include <algorithm>
#include <vector>
#include "jCaloTower/CaloTowerAnalyser/interface/jad_jet_class.hh"
//#include <string>
//#include <sstream>
//#include "TLorentzVector.h"

class pair_info {

public:
  pair_info(int id1, int id2, int dr2);
  int ID1();
  int ID2();
  int DR2();
  void Print();

private:
  int mId1;
  int mId2;
  int mDR2;
};

pair_info::pair_info(int id1, int id2, int dr2) {
  mId1 = id1;
  mId2 = id2;
  mDR2 = dr2;
}

int pair_info::DR2() {
  return mDR2;
}

int pair_info::ID1() {
  return mId1;
}

int pair_info::ID2() {
  return mId2;
}

void pair_info::Print() {

  std::cout << "ID1 = " << this->ID1() << ", ID2 = " << this->ID2() << ", DeltaR2 = " << this->DR2() << std::endl;
  return;

}

bool sortDR(pair_info vec1, pair_info vec2) {

  return (vec1.DR2() < vec2.DR2());
  
}

//std::vector<pair_info> make_pairs(const std::vector<TLorentzVector> & col1, const std::vector<TLorentzVector> & reco_vec) {

std::vector<pair_info> make_pairs(const std::vector<jJet> & col1, const std::vector<jJet> & col2) {

  std::vector<pair_info> pinfo;

  for(unsigned int i=0; i<col1.size(); i++) {
    for(unsigned int j=0; j<col2.size(); j++) {
      pinfo.push_back(pair_info(i,j, col1[i].DeltaR2(col2[j])));
    }
  }

  std::sort(pinfo.begin(), pinfo.end(), sortDR);

  return pinfo;

}

std::vector<pair_info> make_gct_pairs(const std::vector<jJet> & gct_vec, const std::vector<jJet> & col1) {

  std::vector<pair_info> pinfo;
  TriggerTowerGeometry g;

  for(unsigned int i=0; i<gct_vec.size(); i++) {
    for(unsigned int j=0; j<col1.size(); j++) {

        int dEta = gct_vec.at(i).gEta() - g.gct_iEta(col1.at(j).iEta()); 
        int dPhi = gct_vec.at(i).gPhi() - g.gct_iPhi(col1.at(j).iPhi()); 
        int deltaR2 = (dEta*dEta+dPhi*dPhi)*16;
        pinfo.push_back(pair_info(i,j, deltaR2));
    }
  }
  return pinfo;
}

//std::string get_flavour(int gen_index) {
//  //return "cheese and onion"; //obviously, this bit of code looks up the gen index and returns corresponding flavour
//  //temporary - it just returns index as string:
//  std::ostringstream convert;
//  convert << gen_index;
//  return convert.str();
//}

bool in_array(std::vector<int> array, int value) {

  for(unsigned int i=0; i<array.size(); i++) {
    if(array[i] == value) {
      return true;
    }
  }

  return false;

}

std::vector<int> analyse_pairs_global(std::vector<pair_info> & pairs, int reco_size, double DR2max) {

  //std::vector<std::string> reco_matched_index(reco_size, "other");
  std::vector<int> reco_matched_index(reco_size, -1);

  std::vector<int> gen_matched;
  std::vector<int> reco_matched;

  for(unsigned int i=0; i< pairs.size(); i++) {
    if(!in_array(reco_matched, pairs[i].ID2()) && pairs[i].DR2() < DR2max) {
      gen_matched.push_back(pairs[i].ID1());
      reco_matched.push_back(pairs[i].ID2());
      //reco_matched_index[pairs[i].ID2()] = get_flavour(pairs[i].ID1());
      reco_matched_index[pairs[i].ID2()] = pairs[i].ID1();
    }
  }

  return reco_matched_index;

}

std::vector<int> analyse_pairs_local(std::vector<pair_info> & pairs, int reco_size, double DR2max) {

  //std::vector<std::string> reco_matched_index(reco_size, "other");
  std::vector<int> reco_matched_index(reco_size, -1);

  std::vector<int> gen_matched;
  std::vector<int> reco_matched;

  for(unsigned int i=0; i< pairs.size(); i++) {
    if(!in_array(gen_matched, pairs[i].ID1()) && !in_array(reco_matched, pairs[i].ID2()) && pairs[i].DR2() < DR2max) {
      gen_matched.push_back(pairs[i].ID1());
      reco_matched.push_back(pairs[i].ID2());
      //reco_matched_index[pairs[i].ID2()] = get_flavour(pairs[i].ID1());
      reco_matched_index[pairs[i].ID2()] = pairs[i].ID1();
    }
  }

  return reco_matched_index;

}

/*
int main(void) {

  TLorentzVector gen_a(1.0, 2.0, 3.0, 4.0);
  TLorentzVector gen_b(5.0, 6.0, 7.0, 8.0);
  TLorentzVector gen_c(9.0, 10.0, 11.0, 12.0);

  std::vector<TLorentzVector> gen_vec;
  gen_vec.push_back(gen_a);
  gen_vec.push_back(gen_b);
  gen_vec.push_back(gen_c);

  TLorentzVector reco_a(1.1, 2.1, 3.1, 4.0);
  TLorentzVector reco_b(5.1, 6.1, 7.1, 8.0);
  TLorentzVector reco_c(9.1, 10.1, 11.1, 12.0);
  TLorentzVector reco_d(9.0, 10.0, 11.0, 12.0);

  std::vector<TLorentzVector> reco_vec;
  reco_vec.push_back(reco_a);
  reco_vec.push_back(reco_b);
  reco_vec.push_back(reco_c);
  reco_vec.push_back(reco_d);

  std::vector<pair_info> pairs = make_pairs(gen_vec, reco_vec);

  std::sort(pairs.begin(), pairs.end(), sortDR);

  for(unsigned int i=0; i<pairs.size(); i++) {
    pairs[i].Print();
  }

  std::vector<std::string> reco_matched_index = analyse_pairs(pairs, reco_vec.size(), 0.5);

  for(unsigned int i=0; i<reco_matched_index.size(); i++) {
    std::cout << "reco jet with index " << i << " is matched to flavour: " << reco_matched_index[i] << std::endl;
  }


  return 0;

}
*/
#endif
