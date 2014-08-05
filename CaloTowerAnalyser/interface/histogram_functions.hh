#ifndef HISTOGRAM_FUNCTIONS_HH
#define HISTOGRAM_FUNCTIONS_HH

void CaloTowerAnalyser::MakeJetTree(const std::vector<jJet> & col1, const std::vector<jJet> & col2, TString folderName, bool isgct, bool isuct) {


  if(!pMade[folderName+"_jet"])
  {
    std::cout << folderName+"_jet" <<std::endl;
    jetPt_[folderName+"_jet"] = new std::vector<Float_t>();
    jetArea_[folderName+"_jet"] = new std::vector<Float_t>();
    jetFirEta_[folderName+"_jet"] = new std::vector<Float_t>();
    jetCovEtaPhi_[folderName+"_jet"] = new std::vector<Float_t>();
    jetFirPhi_[folderName+"_jet"] = new std::vector<Float_t>();
    jetSecEta_[folderName+"_jet"] = new std::vector<Float_t>();
    jetSecPhi_[folderName+"_jet"] = new std::vector<Float_t>();
    jetPhi_[folderName+"_jet"] = new std::vector<Float_t>();
    jetEta_[folderName+"_jet"] = new std::vector<Float_t>();
    jetDonut_[folderName+"_jet"] = new std::vector<Float_t>();
    jetMatchedPt_[folderName+"_jet"] = new std::vector<Float_t>();
    jetMinDR_[folderName+"_jet"] = new std::vector<Float_t>();
    jetTowerEnergyUp1_[folderName+"_jet"] = new std::vector<int>();
    jetTowerEnergyUp2_[folderName+"_jet"] = new std::vector<int>();
    jetTowerEnergyUp3_[folderName+"_jet"] = new std::vector<int>();
    jetTowerEnergyUp4_[folderName+"_jet"] = new std::vector<int>();
    jetTowerEnergyUp5_[folderName+"_jet"] = new std::vector<int>();
    jetTowerEnergyUp8_[folderName+"_jet"] = new std::vector<int>();

    tree->Branch("jetPt_"+TString(folderName), "std::vector<float>", &jetPt_[folderName+"_jet"]);
    tree->Branch("jetArea_"+TString(folderName), "std::vector<float>", &jetArea_[folderName+"_jet"]);
    tree->Branch("jetFirEta_"+TString(folderName), "std::vector<float>", &jetFirEta_[folderName+"_jet"]);
    tree->Branch("jetCovEtaPhi_"+TString(folderName), "std::vector<float>", &jetCovEtaPhi_[folderName+"_jet"]);
    tree->Branch("jetFirPhi_"+TString(folderName), "std::vector<float>", &jetFirPhi_[folderName+"_jet"]);
    tree->Branch("jetSecEta_"+TString(folderName), "std::vector<float>", &jetSecEta_[folderName+"_jet"]);
    tree->Branch("jetSecPhi_"+TString(folderName), "std::vector<float>", &jetSecPhi_[folderName+"_jet"]);
    tree->Branch("jetPhi_"+TString(folderName), "std::vector<float>", &jetPhi_[folderName+"_jet"]);
    tree->Branch("jetEta_"+TString(folderName), "std::vector<float>", &jetEta_[folderName+"_jet"]);
    tree->Branch("jetDonut_"+TString(folderName), "std::vector<float>", &jetDonut_[folderName+"_jet"]);
    tree->Branch("jetMatchedPt_"+TString(folderName), "std::vector<float>", &jetMatchedPt_[folderName+"_jet"]);
    tree->Branch("jetMinDR_"+TString(folderName), "std::vector<float>", &jetMinDR_[folderName+"_jet"]);

    tree->Branch("jetTowerEnergyUp1_"+TString(folderName), "std::vector<int>", &jetTowerEnergyUp1_[folderName+"_jet"]);
    tree->Branch("jetTowerEnergyUp2_"+TString(folderName), "std::vector<int>", &jetTowerEnergyUp2_[folderName+"_jet"]);
    tree->Branch("jetTowerEnergyUp3_"+TString(folderName), "std::vector<int>", &jetTowerEnergyUp3_[folderName+"_jet"]);
    tree->Branch("jetTowerEnergyUp4_"+TString(folderName), "std::vector<int>", &jetTowerEnergyUp4_[folderName+"_jet"]);
    tree->Branch("jetTowerEnergyUp5_"+TString(folderName), "std::vector<int>", &jetTowerEnergyUp5_[folderName+"_jet"]);
    tree->Branch("jetTowerEnergyUp8_"+TString(folderName), "std::vector<int>", &jetTowerEnergyUp8_[folderName+"_jet"]);

    pMade[folderName+"_jet"]=true;
    for (unsigned int i = 0; i  != col1.at(0).getOuterStrips().size(); i++)
    {
      std::string s = std::to_string(i);
      jetOuterStripsArea_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      jetOuterStripsEnergy_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      tree->Branch("jetOuterStripsEnergy_"+s+"_"+TString(folderName), "std::vector<float>", &jetOuterStripsEnergy_[folderName+"_jet_"+s]);
      tree->Branch("jetOuterStripsArea_"+s+"_"+TString(folderName), "std::vector<float>", &jetOuterStripsArea_[folderName+"_jet_"+s]);
    } 
    for (unsigned int i = 0; i  != col1.at(0).ringSums().size(); i++)
    {
      std::string s = std::to_string(i);
      jetRingSumsArea_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      jetRingSumsEnergy_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      jetRingSumsHighest_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      tree->Branch("jetRingSumsEnergy_"+s+"_"+TString(folderName), "std::vector<float>", &jetRingSumsEnergy_[folderName+"_jet_"+s]);
      tree->Branch("jetRingSumsHighest_"+s+"_"+TString(folderName), "std::vector<float>", &jetRingSumsHighest_[folderName+"_jet_"+s]);
      tree->Branch("jetRingSumsArea_"+s+"_"+TString(folderName), "std::vector<float>", &jetRingSumsArea_[folderName+"_jet_"+s]);
    } 
    for (unsigned int i = 0; i  != col1.at(0).ringSumsEC().size(); i++)
    {
      std::string s = std::to_string(i);
      jetRingSumsECAL_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      tree->Branch("jetRingSumsECAL_"+s+"_"+TString(folderName), "std::vector<float>", &jetRingSumsECAL_[folderName+"_jet_"+s]);
    } 
    for (unsigned int i = 0; i  != col1.at(0).ringSumsHC().size(); i++)
    {
      std::string s = std::to_string(i);
      jetRingSumsHCAL_[folderName+"_jet_"+s]= new std::vector<Float_t>();
      tree->Branch("jetRingSumsHCAL_"+s+"_"+TString(folderName), "std::vector<float>", &jetRingSumsHCAL_[folderName+"_jet_"+s]);
    } 
  }


  //std::cout << col1_matched_index_algo1.at(0) << std::endl;
  jetPt_[folderName+"_jet"]->clear();
  jetArea_[folderName+"_jet"]->clear();
  jetFirEta_[folderName+"_jet"]->clear();
  jetCovEtaPhi_[folderName+"_jet"]->clear();
  jetFirPhi_[folderName+"_jet"]->clear();
  jetSecEta_[folderName+"_jet"]->clear();
  jetSecPhi_[folderName+"_jet"]->clear();
  jetPhi_[folderName+"_jet"]->clear();
  jetEta_[folderName+"_jet"]->clear();
  jetDonut_[folderName+"_jet"]->clear();
  jetMatchedPt_[folderName+"_jet"]->clear();
  jetMinDR_[folderName+"_jet"]->clear();

  jetTowerEnergyUp1_[folderName+"_jet"]->clear();
  jetTowerEnergyUp2_[folderName+"_jet"]->clear();
  jetTowerEnergyUp3_[folderName+"_jet"]->clear();
  jetTowerEnergyUp4_[folderName+"_jet"]->clear();
  jetTowerEnergyUp5_[folderName+"_jet"]->clear();
  jetTowerEnergyUp8_[folderName+"_jet"]->clear();

  if(!isuct && !isgct){

    for (unsigned int i = 0; i  != col1.at(0).getOuterStrips().size(); i++)
    {
      std::string s = std::to_string(i);
      jetOuterStripsEnergy_[folderName+"_jet_"+s]->clear();
      jetOuterStripsArea_[folderName+"_jet_"+s]->clear();
    }
    for (unsigned int i = 0; i  != col1.at(0).ringSums().size(); i++)
    {
      std::string s = std::to_string(i);
      jetRingSumsEnergy_[folderName+"_jet_"+s]->clear();
      jetRingSumsHighest_[folderName+"_jet_"+s]->clear();
      jetRingSumsArea_[folderName+"_jet_"+s]->clear();
    }
    for (unsigned int i = 0; i  != col1.at(0).ringSumsEC().size(); i++)
    {
      std::string s = std::to_string(i);
      jetRingSumsECAL_[folderName+"_jet_"+s]->clear();
    }
    for (unsigned int i = 0; i  != col1.at(0).ringSumsHC().size(); i++)
    {
      std::string s = std::to_string(i);
      jetRingSumsHCAL_[folderName+"_jet_"+s]->clear();
    }
    //  std::vector <Float_t> * jetPhi_[folderName+"_jet"] = new std::vector<Float_t>();
    //  std::vector <Float_t> *  jetEta_[folderName+"_jet"] = new std::vector<Float_t>();
    //
  }
  std::vector<jJet> test = col1;
  std::vector<int> col1_matched_index_algo1; 

  if(col1.size()!=0){
    pairs = (isgct) ? make_gct_pairs(col2,col1) : make_pairs(col2, col1);
    if(!isgct&&!isuct){
      col1_matched_index_algo1 = analyse_pairs_local(pairs, col1.size(), 33);
    }else{
      col1_matched_index_algo1 = analyse_pairs_local(pairs, col1.size(), 60);
    }
  }

  int i=0;
  for (auto jet = col1.begin(); jet != col1.end(); jet++)
  {
    jetPt_[folderName+"_jet"]->push_back(jet->pt());
    if(!isgct)
    {
      jetPhi_[folderName+"_jet"]->push_back(g.phi(jet->iPhi()));
      jetEta_[folderName+"_jet"]->push_back(g.eta(jet->iEta()));
    }else{
      jetPhi_[folderName+"_jet"]->push_back(g.phiFromGct(jet->gPhi()));
      jetEta_[folderName+"_jet"]->push_back(g.etaFromGct(jet->gEta()));
    }
    //if(isuct){
    //  jetPhi_[folderName+"_jet"]->push_back(g.phi(jet->iPhi()));
    //  jetEta_[folderName+"_jet"]->push_back(g.eta(jet->iEta()));
    //}
    jetDonut_[folderName+"_jet"]->push_back(jet->getOuterSum());
    jetArea_[folderName+"_jet"]->push_back(jet->area());
    jetFirEta_[folderName+"_jet"]->push_back(jet->firEta());
    jetFirPhi_[folderName+"_jet"]->push_back(jet->firPhi());
    jetSecEta_[folderName+"_jet"]->push_back(jet->secEta());
    jetSecPhi_[folderName+"_jet"]->push_back(jet->secPhi());
    jetCovEtaPhi_[folderName+"_jet"]->push_back(jet->covEtaPhi());

    jetMinDR_[folderName+"_jet"]->push_back(test.at(i).minDeltaR2(col1));
    std::vector<uint8_t> towers = jet->getTowers();
    int dummy1=0;
    int dummy2=0;
    int dummy3=0;
    int dummy4=0;
    int dummy5=0;
    int dummy8=0;
    for (unsigned int j = 0; j < towers.size(); j++)
    {
      if (towers.at(j) <= 1) dummy1 += towers.at(j);
      if (towers.at(j) <= 2) dummy2 += towers.at(j);
      if (towers.at(j) <= 3) dummy3 += towers.at(j);
      if (towers.at(j) <= 4) dummy4 += towers.at(j);
      if (towers.at(j) <= 5) dummy5 += towers.at(j);
      if (towers.at(j) <= 8) dummy8 += towers.at(j);
    }
    jetTowerEnergyUp1_[folderName+"_jet"]->push_back(dummy1);
    jetTowerEnergyUp2_[folderName+"_jet"]->push_back(dummy2);
    jetTowerEnergyUp3_[folderName+"_jet"]->push_back(dummy3);
    jetTowerEnergyUp4_[folderName+"_jet"]->push_back(dummy4);
    jetTowerEnergyUp5_[folderName+"_jet"]->push_back(dummy5);
    jetTowerEnergyUp8_[folderName+"_jet"]->push_back(dummy8);
    for (unsigned int j = 0; j  != jet->getOuterStrips().size(); j++)
    {
      std::string s = std::to_string(j);
      jetOuterStripsArea_[folderName+"_jet_"+s]->push_back(jet->getOuterStrips().at(j).second);
      jetOuterStripsEnergy_[folderName+"_jet_"+s]->push_back(jet->getOuterStrips().at(j).first);
    }
    for (unsigned int j = 0; j  != jet->ringSums().size(); j++)
    {
      std::string s = std::to_string(j);
      jetRingSumsArea_[folderName+"_jet_"+s]->push_back(jet->ringAreas().at(j));
      jetRingSumsEnergy_[folderName+"_jet_"+s]->push_back(jet->ringSums().at(j));
      jetRingSumsHighest_[folderName+"_jet_"+s]->push_back(jet->ringMax().at(j));
    }
    for (unsigned int j = 0; j  != col1.at(0).ringSumsEC().size(); j++)
    {
      std::string s = std::to_string(j);
      jetRingSumsECAL_[folderName+"_jet_"+s]->push_back(jet->ringSumsEC().at(j));
    }
    for (unsigned int j = 0; j  != col1.at(0).ringSumsHC().size(); j++)
    {
      std::string s = std::to_string(j);
      jetRingSumsHCAL_[folderName+"_jet_"+s]->push_back(jet->ringSumsHC().at(j));
    }

    if (col1_matched_index_algo1[i]!=-1)
    {
      jetMatchedPt_[folderName+"_jet"]->push_back(col2.at(col1_matched_index_algo1.at(i)).pt());
    }
    else
    {
      jetMatchedPt_[folderName+"_jet"]->push_back(-1);
    }
    i+=1;
  }

  return;
}
void CaloTowerAnalyser::MakeMatchTree(const std::vector<jJet> & col1,const std::vector<jJet> & col2, TString folderName,bool isgct) {

  //if (col1.size()!=0){

  if(!pMade[folderName+"_match"])
  {
    std::cout << folderName+"_match" <<std::endl;
    genJetMatchAlgo1_[folderName+"_match"] = new std::vector<Int_t>();
    genJetMatchAlgo2_[folderName+"_match"] = new std::vector<Int_t>();
    tree->Branch("genJetMatchAlgo1_"+TString(folderName), "std::vector<int>", &genJetMatchAlgo1_[folderName+"_match"]);
    tree->Branch("genJetMatchAlgo2_"+TString(folderName), "std::vector<int>", &genJetMatchAlgo2_[folderName+"_match"]);
    pMade[folderName+"_match"]=true;
  }

  genJetMatchAlgo1_[folderName+"_match"]->clear();
  genJetMatchAlgo2_[folderName+"_match"]->clear();

  pairs = (isgct) ? make_gct_pairs(col1,col2) : make_pairs(col1, col2);
  std::vector<int> col2_matched_index_algo1 = analyse_pairs_local(pairs, col2.size(), 33);
  std::vector<int> col2_matched_index_algo2 = analyse_pairs_global(pairs, col2.size(), 33);


  for (unsigned int i = 0; i < col2.size(); i++)
  {
    genJetMatchAlgo1_[folderName+"_match"]->push_back(col2_matched_index_algo1[i]);
    genJetMatchAlgo2_[folderName+"_match"]->push_back(col2_matched_index_algo2[i]);
  }

  // }
  return;
}

void CaloTowerAnalyser::MakeSumTree(const std::vector<jJet> & col1,TString folderName,bool isgct, bool iscalibgct, bool isuct) {


  if(!pMade[folderName+"_sum"])
  {
    std::cout << folderName+"_sum" <<std::endl;
    sumsHT_[folderName+"_sum"] = 0.0; 
    sumsMHT_[folderName+"_sum"] = 0.0; 
    sumsMHTx_[folderName+"_sum"] = 0.0; 
    sumsMHTy_[folderName+"_sum"] = 0.0; 
    tree->Branch("sumsHT_"+TString(folderName+"_sum"), &sumsHT_[folderName+"_sum"],"sumsHT/D");
    tree->Branch("sumsMHT_"+TString(folderName+"_sum"), &sumsMHT_[folderName+"_sum"],"sumsMHT/D");
    tree->Branch("sumsMHTx_"+TString(folderName+"_sum"), &sumsMHTx_[folderName+"_sum"],"sumsMHTx/D");
    tree->Branch("sumsMHTy_"+TString(folderName+"_sum"), &sumsMHTy_[folderName+"_sum"],"sumsMHTy/D");
    pMade[folderName+"_sum"]=true;
  }

  //  std::vector <Float_t> * jetPhi_[folderName+"_sum"] = new std::vector<Float_t>();
  //  std::vector <Float_t> *  jetEta_[folderName+"_sum"] = new std::vector<Float_t>();
  double HTcol1;
  double MHTcol1;
  double MHTcol1_x;
  double MHTcol1_y;
  if(isuct)
  {
    HTcol1=mUctHtCalib;
    MHTcol1=mUctHtMissCalib;
    MHTcol1_x=0;
    MHTcol1_y=0;
  }
  else if (!isgct)
  {
    HTcol1=calculateHT(col1,20);
    MHTcol1_x=calculateMHT(col1,20)[0];
    MHTcol1_y=calculateMHT(col1,20)[1];
    MHTcol1=calculateMHT(col1,20)[2];
  }
  else if(iscalibgct)
  {
    HTcol1=mGctHtCalib;
    MHTcol1=mGctHtMissCalib;
    MHTcol1_x=0;
    MHTcol1_y=0;
  }
  else
  {
    HTcol1=mGctHtUncalib;
    MHTcol1=mGctHtMissUncalib;
    MHTcol1_x=0;
    MHTcol1_y=0;
  }
  sumsHT_[folderName+"_sum"]=HTcol1;
  sumsMHT_[folderName+"_sum"]=(MHTcol1);
  sumsMHTx_[folderName+"_sum"]=(MHTcol1_x);
  sumsMHTy_[folderName+"_sum"]=(MHTcol1_y);

  return;
}

#endif
