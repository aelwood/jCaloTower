#ifndef __JMATCH__
#define __JMATCH__

#include <iostream>
#include <algorithm>
#include <vector>
#include <TLorentzVector.h>

class pair_info {

  public:
    pair_info(int id1, int id2, double dr2);
    int ID1();
    int ID2();
    double DR2();
    void Print();

  private:
    int mId1;
    int mId2;
    double mDR2;
};

pair_info::pair_info(int id1, int id2, double dr2) {
  mId1 = id1;
  mId2 = id2;
  mDR2 = dr2;
}

double pair_info::DR2() {
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

std::vector<pair_info> make_pairs(const std::vector<TLorentzVector>& col1, const std::vector<TLorentzVector>& col2) {

  std::vector<pair_info> pinfo;

  for(unsigned int i=0; i<col1.size(); i++) {
    for(unsigned int j=0; j<col2.size(); j++) {
      pinfo.push_back(pair_info(i,j, col1[i].DeltaR(col2[j])));
    }
  }

  std::sort(pinfo.begin(), pinfo.end(), sortDR);

  return pinfo;

}

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

#endif
