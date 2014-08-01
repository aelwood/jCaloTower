#ifndef __JAD_JET_STRUCT__
#define __JAD_JET_STRUCT__

#include "SLHCUpgradeSimulations/L1CaloTrigger/interface/TriggerTowerGeometry_new.h"

//struct jJet{
//  double pt;
//  int ieta;
//  int iphi;
//  jJet(double mpt, int mieta, int miphi) : pt(mpt), ieta(mieta), iphi(miphi) {}
//};

class jJet {

public:
  jJet(double pt, int ieta, int iphi);
  jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<int> outerstrips);
  int iEta() const;
  int iPhi() const;
  double pt() const;
  std::vector<int> ringSums() const;
  std::vector<int> ringAreas() const;
  std::vector<int> getOuterStrips() const;
  int DeltaR2(const jJet & jet2) const;
  int PUE();
  bool isolatedJet(const std::vector<jJet>& jetCollection, double dR2Max);
  double eatDonut(); //the energy after PUsubtraction

private:
  double mpt;
  int mieta;
  int miphi;
  std::vector<int> mringsums;
  std::vector<int> mringareas;
  std::vector<int> mouterstrips;
};

jJet::jJet(double pt, int ieta, int iphi) : mpt(pt), mieta(ieta), miphi(iphi) {}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<int> ringareas, std::vector<int> outerstrips) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums), mringareas(ringareas), mouterstrips(outerstrips) {
  std::sort(mouterstrips.begin(), mouterstrips.end());
}

int jJet::iEta() const { return mieta; }
int jJet::iPhi() const { return miphi; }
double jJet::pt() const { return mpt; }
std::vector<int> jJet::ringSums() const { return mringsums; }
std::vector<int> jJet::ringAreas() const { return mringareas; }
std::vector<int> jJet::getOuterStrips() const { return mouterstrips; }
int jJet::PUE() { return (mouterstrips[1] + mouterstrips[2]); } //i.e. sum up the middle two energies

double jJet::eatDonut() {
  double lastringsum = this->ringSums().at(this->ringSums().size() - 1);
  double donutenergy = this->PUE() * 3.5; //3.5 = 7x7 / 2x7
  return (this->pt() - lastringsum - donutenergy);
}

int jJet::DeltaR2(const jJet & jet2) const {

  TriggerTowerGeometry g;

  int newEtaIndex1 = g.new_iEta(this->iEta());
  int newEtaIndex2 = g.new_iEta(jet2.iEta());
  int newPhiIndex1 = g.new_iPhi(this->iPhi());
  int newPhiIndex2 = g.new_iPhi(jet2.iPhi());

  int deltaPhi = abs(newPhiIndex1 - newPhiIndex2);
  if( deltaPhi > 36) {
    deltaPhi = 72 - deltaPhi;
  }

  int deltaR2 = ((newEtaIndex1 - newEtaIndex2) * (newEtaIndex1 - newEtaIndex2)) + (deltaPhi * deltaPhi);

  return deltaR2;

}

bool jJet::isolatedJet(const std::vector<jJet>& jetCollection, double dR2Max){
  int closeJets=0;
  for(std::vector<jJet>::const_iterator jetIt = jetCollection.begin();
      jetIt!=jetCollection.end(); jetIt++){
    if(this->DeltaR2(*jetIt)<dR2Max) closeJets++;//Check it's not witin 7x7
  }
  if(closeJets>1) return false;
  else return true;
}

bool sortbypt(const jJet &a, const jJet &b) { return a.pt() > b.pt(); }

#endif
