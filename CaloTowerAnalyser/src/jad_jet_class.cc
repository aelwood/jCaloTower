//#include "jCaloTower/CaloTowerAnalyser/interface/jad_jet_class.hh"
#include "jCaloTower/CaloTowerAnalyser/interface/jad_jet_class.hh"

jJet::jJet(double pt, int ieta, int iphi) : mpt(pt), mieta(ieta), miphi(iphi) {}
jJet::jJet(double pt, int geta, int gphi,int bx) : mpt(pt), mgeta(geta), mgphi(gphi),mbx(bx) {}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums,std::vector<int> ringmax, double jetFirMomEta,double jetFirMomPhi,double jetSecMomEta,double jetSecMomPhi, double covEtaPhi,std::vector<double> ringareas,std::vector<std::pair<int,double> > outerstrips, std::vector<uint8_t> towers, double jetarea) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums),mringmax(ringmax),mfireta(jetFirMomEta),mfirphi(jetFirMomPhi),mseceta(jetSecMomEta),msecphi(jetSecMomPhi),mcov(covEtaPhi), mringareas(ringareas), mouterstrips(outerstrips),mtowers(towers),marea(jetarea) {
   std::sort(mouterstrips.begin(), mouterstrips.end());
//   std::sort(mtowers.begin(), mtowers.end());
}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums,std::vector<int> ringsumsec,std::vector<int> ringsumshc,std::vector<int> ringmax, double jetFirMomEta,double jetFirMomPhi,double jetSecMomEta,double jetSecMomPhi,double covEtaPhi, std::vector<double> ringareas, std::vector<std::pair<int,double> > outerstrips, std::vector<uint8_t> towers, double jetarea) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums),mringsumsec(ringsumsec),mringsumshc(ringsumshc),mringmax(ringmax),mfireta(jetFirMomEta),mfirphi(jetFirMomPhi),mseceta(jetSecMomEta),msecphi(jetSecMomPhi),mcov(covEtaPhi), mringareas(ringareas), mouterstrips(outerstrips),mtowers(towers),marea(jetarea) {
   std::sort(mouterstrips.begin(), mouterstrips.end());
 //  std::sort(mtowers.begin(), mtowers.end());

}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<double> ringareas, std::vector<std::pair<int,double> > outerstrips, std::vector<uint8_t> towers, double jetarea) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums), mringareas(ringareas), mouterstrips(outerstrips),mtowers(towers),marea(jetarea) {
   std::sort(mouterstrips.begin(), mouterstrips.end());
//   std::sort(mtowers.begin(), mtowers.end());
}
jJet::jJet(double pt, int ieta, int iphi, std::vector<int> ringsums, std::vector<double> ringareas, std::vector<std::pair<int,double> > outerstrips, std::vector<uint8_t> towers, double jetarea,int seedtower) : mpt(pt), mieta(ieta), miphi(iphi), mringsums(ringsums), mringareas(ringareas), mouterstrips(outerstrips),mtowers(towers),marea(jetarea),mseed(seedtower) {
   std::sort(mouterstrips.begin(), mouterstrips.end());
//   std::sort(mtowers.begin(), mtowers.end());
}

int jJet::iEta() const { return mieta; }
int jJet::iPhi() const { return miphi; }
int jJet::gEta() const { return mgeta; }
int jJet::gPhi() const { return mgphi; }
double jJet::pt() const { return mpt; }
double jJet::firEta() const { return mfireta; }
double jJet::firPhi() const { return mfirphi; }
double jJet::secEta() const { return mseceta; }
double jJet::secPhi() const { return msecphi; }
double jJet::covEtaPhi() const { return mcov; }
std::vector<int> jJet::ringSums() const { return mringsums; }
std::vector<int> jJet::ringSumsEC() const { return mringsumsec; }
std::vector<int> jJet::ringSumsHC() const { return mringsumshc; }
std::vector<int> jJet::ringMax() const { return mringmax; }
std::vector<double> jJet::ringAreas() const { return mringareas; }
std::vector<std::pair<int,double> > jJet::getOuterStrips() const { return mouterstrips; }
std::vector<uint8_t> jJet::getTowers() const { return mtowers; }

int jJet::getOuterSum() const 
{ 
   int outerRing = 0;
   for (auto ring = mouterstrips.begin(); ring != mouterstrips.end(); ring++) outerRing+=ring->first;
   return outerRing;
}
int jJet::PUE() {
int medianStrip = mouterstrips.size()/2;

 return (mouterstrips[medianStrip-1].first + mouterstrips[medianStrip].first); } //i.e. sum up the middle two energies

void jJet::setPt(double pt) 
{
   mpt=pt;
}
double jJet::eatDonut() {
   //double lastringsum = this->ringSums().at(this->ringSums().size() - 1);
   int medianStrip = mouterstrips.size()/2; 
   double scaleDonut = (double)marea/(double)(mouterstrips[medianStrip-1].second + mouterstrips[medianStrip].second);
   double donutenergy = this->PUE() * scaleDonut; //3.5 = 7x7 / 2x7
   return (this->pt() - donutenergy);
}
double jJet::eatGlobe(double median) {
   return (this->pt() - median*this->area());
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
int jJet::minDeltaR2(const std::vector<jJet>& jetCollection) const {
  int drmin=9999;
  for (auto jet = jetCollection.begin(); jet != jetCollection.end();jet++)
  {
  int  drtemp=this->DeltaR2(*jet);
    if(drmin > drtemp && drtemp > 0.01) drmin = drtemp;
  }
  return drmin;
}
double jJet::area() const
{
  return marea;
}
