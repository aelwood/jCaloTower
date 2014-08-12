#ifndef CALIBRATIONPARAMS_HH
#define CALIBRATIONPARAMS_HH

#include "calibrationLuts.hh"
#include "/afs/cern.ch/work/a/aelwood/trigger/jets/jadjet/CMSSW_6_2_0/src/SLHCUpgradeSimulations/L1CaloTrigger/interface/TriggerTowerGeometry_new.h"

double calibFit( Double_t *v, Double_t *par ){

  // JETMET uses log10 rather than the ln used here...
  double logX = log(v[0]);

  double term1 = par[1] / ( logX * logX + par[2] );
  double term2 = par[3] * exp( -par[4]*((logX - par[5])*(logX - par[5])) );

  // Final fitting function 
  double f    = par[0] + term1 + term2; 

  return f;
  //return 1.0/f;
}

namespace{
  TString l1s0donut="s0_donut";
  TString l1s0global="s0_global";
  TString l1s0nopus="s0_nopus";
  TString l1s0chunky="s0_chunky";
  TString l1s0tsup1="s0_tsup1";
  TString l1s0tsup2="s0_tsup2";
  TString l1s5donut="s5_donut";
  TString l1s5nopus="s5_nopus";
  TString l1s5global="s5_global";
  TString l1s5chunky="s5_chunky";
  TString l1s5tsup1="s5_tsup1";
  TString l1s5tsup2="s5_tsup2";
  TString l1c10donut="c10_donut";
  TString l1c10nopus="c10_nopus";
  TString l1c10global="c10_global";
  TString l1c10chunky="c10_chunky";
  TString l1c10tsup1="c10_tsup1";
  TString l1c10tsup2="c10_tsup2";
}

std::vector<TLorentzVector> calibrateL1Jets(const std::vector<TLorentzVector>& inJets, TString type, double ptMin, double ptMax){

  std::vector<double> lut;

  TriggerTowerGeometry g;

  std::vector<TLorentzVector> outJets;

  for(int i=0; i<48; i++){

    if(type==l1s0global) lut.push_back(lutss0GeV::globalLut[i]);
    else if(type==l1s0donut) lut.push_back(lutss0GeV::donutLut[i]);
    else if(type==l1s0nopus) lut.push_back(lutss0GeV::nopusLut[i]);
    else if(type==l1s0chunky) lut.push_back(lutss0GeV::chunkyLut[i]);
    else if(type==l1s0tsup1) lut.push_back(lutss0GeV::tsup1Lut[i]);
    else if(type==l1s0tsup2) lut.push_back(lutss0GeV::tsup2Lut[i]);
    else if(type==l1s5donut) lut.push_back(lutss5GeV::donutLut[i]);
    else if(type==l1s5global) lut.push_back(lutss5GeV::globalLut[i]);
    else if(type==l1s5nopus) lut.push_back(lutss5GeV::nopusLut[i]);
    else if(type==l1s5chunky) lut.push_back(lutss5GeV::chunkyLut[i]);
    else if(type==l1s5tsup1) lut.push_back(lutss5GeV::tsup1Lut[i]);
    else if(type==l1s5tsup2) lut.push_back(lutss5GeV::tsup2Lut[i]);
    else if(type==l1c10donut) lut.push_back(lutsc10GeV::donutLut[i]);
    else if(type==l1c10nopus) lut.push_back(lutsc10GeV::nopusLut[i]);
    else if(type==l1c10chunky) lut.push_back(lutsc10GeV::chunkyLut[i]);
    else if(type==l1c10tsup1) lut.push_back(lutsc10GeV::tsup1Lut[i]);
    else if(type==l1c10tsup2) lut.push_back(lutsc10GeV::tsup2Lut[i]);
    else if(type==l1c10global) lut.push_back(lutsc10GeV::globalLut[i]);

    else std::cout << "Invalid type to get lut" << std::endl;

  }


  for(unsigned i=0; i<inJets.size(); i++){

    //If the pt of the jet is outside of the calibration range, add the jet to the calibrated jets and do nothing
    if(inJets[i].Pt()>ptMax){
      outJets.push_back(inJets[i]);
    }
    else if(inJets[i].Pt()>ptMin){

      double p[6]; //These are the parameters of the fit
      double v[1]; //This is the pt value

      //Load the lut based on the correct eta bin
      if(inJets[i].Eta()<g.eta(-21)){ //inJets[i].Eta()>=g.eta(-28) && 
        p[0]=lut[0];
        p[1]=lut[1];
        p[2]=lut[2];
        p[3]=lut[3];
        p[4]=lut[4];
        p[5]=lut[5];
      }else if(inJets[i].Eta()>=g.eta(-21) && inJets[i].Eta()<g.eta(-14)){
        p[0]=lut[6];
        p[1]=lut[7];
        p[2]=lut[8];
        p[3]=lut[9];
        p[4]=lut[10];
        p[5]=lut[11];
      }else if(inJets[i].Eta()>=g.eta(-14) && inJets[i].Eta()<g.eta(-7)){
        p[0]=lut[12];
        p[1]=lut[13];
        p[2]=lut[14];
        p[3]=lut[15];
        p[4]=lut[16];
        p[5]=lut[17];
      }else if(inJets[i].Eta()>=g.eta(-7) && inJets[i].Eta()<g.eta(0)){
        p[0]=lut[18];
        p[1]=lut[19];
        p[2]=lut[20];
        p[3]=lut[21];
        p[4]=lut[22];
        p[5]=lut[23];
      }else if(inJets[i].Eta()>g.eta(0) && inJets[i].Eta()<=g.eta(7)){
        p[0]=lut[24];
        p[1]=lut[25];
        p[2]=lut[26];
        p[3]=lut[27];
        p[4]=lut[28];
        p[5]=lut[29];
      }else if(inJets[i].Eta()>g.eta(7) && inJets[i].Eta()<=g.eta(14)){
        p[0]=lut[30];
        p[1]=lut[31];
        p[2]=lut[32];
        p[3]=lut[33];
        p[4]=lut[34];
        p[5]=lut[35];
      }else if(inJets[i].Eta()>g.eta(14) && inJets[i].Eta()<=g.eta(21)){
        p[0]=lut[36];
        p[1]=lut[37];
        p[2]=lut[38];
        p[3]=lut[39];
        p[4]=lut[40];
        p[5]=lut[41];
      }else if(inJets[i].Eta()>g.eta(21)){ //&& inJets[i].Eta()<=g.eta(28)
        p[0]=lut[42];
        p[1]=lut[43];
        p[2]=lut[44];
        p[3]=lut[45];
        p[4]=lut[46];
        p[5]=lut[47];
      }
      v[0]=inJets[i].Pt();
      double correction=calibFit(v,p);

      TLorentzVector jet;
      jet.SetPtEtaPhiM(correction*inJets[i].Pt(),inJets[i].Eta(),inJets[i].Phi(),0.);
      if(jet.Eta()>100 || jet.Eta()<-100) std::cout << "Calibration\n" << inJets[i].Pt() << "\t" << correction << "\t" 
        << inJets[i].Eta() << "\t" << inJets[i].Phi() << "\t" << type.Data() <<"\n" 
          << p[0] << "\t"<< p[1] << "\t"<< p[2] << "\t"<< p[3] << "\t"<< p[4] << "\t"<< p[5] << "\n" 
          << calibFit(v,p) << "\n";

      outJets.push_back(jet);

    }

  }
  return outJets;
}
/*
std::vector<TLorentzVector> calibrateL1Jets(const std::vector<TLorentzVector>& inJets, TString type, int CALIBMODE){

  std::vector<TLorentzVector> outJets;
  double tmPT,tmETA,tmHOE,tmSOPT;

  if(CALIBMODE<1 || CALIBMODE>4){
    std::cout << "Invalid calib bdt mode" << std::endl;
    return outJets;
  }

  TMVA::Reader *tmvaReader_ = new TMVA::Reader();

  tmvaReader_->AddVariable("pt" ,&tmPT );
  tmvaReader_->AddVariable("eta",&tmETA);

  if (CALIBMODE==2)  tmvaReader_->AddVariable("hoe",&tmHOE);
  if (CALIBMODE==3)  tmvaReader_->AddVariable("sopt",&tmSOPT);
  if (CALIBMODE==4)  {
    tmvaReader_->AddVariable("hoe",&tmHOE);
    tmvaReader_->AddVariable("sopt",&tmSOPT);
  }


  if(type=="s5_global"){

    if(CALIBMODE==1) tmvaReader_->BookMVA("BDTG","/afs/cern.ch/user/n/nckw/public/forAdam/global_rho_weights/weights/TMVARegresion_BDTG.weights.xml ");
    else if (CALIBMODE==2) tmvaReader_->BookMVA("BDTG","/afs/cern.ch/user/n/nckw/public/forAdam/global_rho_weights/weights/TMVARegresion_BDTG_3var_hoe.weights.xml ");
    else if (CALIBMODE==3) tmvaReader_->BookMVA("BDTG","/afs/cern.ch/user/n/nckw/public/forAdam/global_rho_weights/weights/TMVARegresion_BDTG_3var_sopt.weights.xml ");
    else if (CALIBMODE==4) tmvaReader_->BookMVA("BDTG","/afs/cern.ch/user/n/nckw/public/forAdam/global_rho_weights/weights/TMVARegresion_BDTG_4var.weights.xml ");

  }else if(type=="s5_chunky"){

    if(CALIBMODE==1) tmvaReader_->BookMVA("BDTG","/afs/cern.ch/user/n/nckw/public/forAdam/chunky_donut_weights/weights/TMVARegresion_BDTG.weights.xml ");
    else if (CALIBMODE==2) tmvaReader_->BookMVA("BDTG","/afs/cern.ch/user/n/nckw/public/forAdam/chunky_donut_weights/weights/TMVARegresion_BDTG_3var_hoe.weights.xml ");
    else if (CALIBMODE==3) tmvaReader_->BookMVA("BDTG","/afs/cern.ch/user/n/nckw/public/forAdam/chunky_donut_weights/weights/TMVARegresion_BDTG_3var_sopt.weights.xml ");
    else if (CALIBMODE==4) tmvaReader_->BookMVA("BDTG","/afs/cern.ch/user/n/nckw/public/forAdam/chunky_donut_weights/weights/TMVARegresion_BDTG_4var.weights.xml ");

  }else{
    std::cout << "Can't use BDT method on this jet type" << std::endl;
    return outJets;
  }


  // in the loop, set the variables and get the scale factor


  for(unsigned i=0; i<inJets.size(); i++){

    tmPT=inJets[i].pt();
    tmETA=inJets[i].eta();

    tmHOE= hoe ;
    tmSOPT= sopt ;

    double correction = tmvaReader_->EvaluateRegression(0,"BDTG");

    TLorentzVector jet;
    jet.SetPtEtaPhiM(correction*inJets[i].Pt(),inJets[i].Eta(),inJets[i].Phi(),0.);

    outJets.push_back(jet);
  }

  return outJets;
}
*/
#endif

