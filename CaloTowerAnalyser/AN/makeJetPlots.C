#include "TCut.h"
#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TH2.h"
#include "TProfile.h"
#include <iostream>

namespace{

  int N_50NS_BUNCHES=1368;
  int N_25NS_BUNCHES=2508;
  int LHC_FREQUENCY=11246;

  int ZB_XSECTION=LHC_FREQUENCY*N_25NS_BUNCHES;

}

void makeJetPlots()
{
  TFile * fout = new TFile("jetPlots.root","recreate");

  TFile * finNeutrino = new TFile("calibJetsNGun.root");
  TTree * treeNeut = (TTree *)finNeutrino->Get("jetTree");
  //treeNeut->AddFriend("demo/L1Tree",
  //    "/afs/cern.ch/work/a/aelwood/public/NGUN/140801/ngun_14-08-01.root");
  //TChain* chainNeut = new TChain("demo/L1Tree");
  //chainNeut->Add("/afs/cern.ch/work/a/aelwood/public/NGUN/TwentyFiveNs/140805/output*.root");
  //treeNeut->AddFriend(chainNeut);

  TFile * finTtbar = new TFile("calibJetsSignal.root");
  TTree * treeTtbar = (TTree *)finTtbar->Get("jetTree");
  //treeTtbar->AddFriend("demo/L1Tree",
  //    "/afs/cern.ch/work/a/aelwood/public/TTBAR/TwentyFiveNs/140805/ttbar_14-08-05.root");
  //treeTtbar->AddFriend("calibJetsTtbar.root");

  std::vector<TString> jetTypes;
  
  //jetTypes.push_back("s0_nopus");
  //jetTypes.push_back("s5_chunky");
  //jetTypes.push_back("s5_global");
  jetTypes.push_back("calib_s0_nopus");
  jetTypes.push_back("calib_s0_donut");
  jetTypes.push_back("calib_s0_global");
  //jetTypes.push_back("s0_tsup1");
  //jetTypes.push_back("s0_tsup2");
  //jetTypes.push_back("s0_tsup3");
  jetTypes.push_back("calib_s5_nopus");
  jetTypes.push_back("calib_s5_donut");
  jetTypes.push_back("calib_s5_global");
  jetTypes.push_back("calib_s5_chunky");
  jetTypes.push_back("calib_s5_tsup1");
  jetTypes.push_back("calib_s5_tsup2");
  jetTypes.push_back("calib_c10_nopus");
  jetTypes.push_back("calib_c10_donut");
  //jetTypes.push_back("s5_tsup3");
  jetTypes.push_back("calib_gen");
  

  jetTypes.push_back("met");
  jetTypes.push_back("calib_gct");
  jetTypes.push_back("calib_uct");
/*
  jetTypes.push_back("calib_s0_nopus");
  // jetTypes.push_back("s8_nopus");
  jetTypes.push_back("calib_s10_nopus");
  jetTypes.push_back("calib_s15_nopus");
  jetTypes.push_back("calib_s20_nopus");
  // jetTypes.push_back("c15_nopus");
  jetTypes.push_back("calib_c20_nopus");
  jetTypes.push_back("calib_c25_nopus");
  jetTypes.push_back("calib_c30_nopus");
  //jetTypes.push_back("s0_donut");
  jetTypes.push_back("calib_s0_global");
  // jetTypes.push_back("s8_global");
  jetTypes.push_back("calib_s10_global");
  jetTypes.push_back("calib_s15_global");
  jetTypes.push_back("calib_s20_global");
  // jetTypes.push_back("c15_global");
  jetTypes.push_back("calib_c20_global");
  jetTypes.push_back("calib_c25_global");
  jetTypes.push_back("calib_c30_global");
  jetTypes.push_back("calib_s0_chunky");
  // jetTypes.push_back("s8_chunky");
  jetTypes.push_back("calib_s10_chunky");
  jetTypes.push_back("calib_s15_chunky");
  jetTypes.push_back("calib_s20_chunky");
  // jetTypes.push_back("c15_chunky");
  jetTypes.push_back("calib_c20_chunky");
  jetTypes.push_back("calib_c25_chunky");
  jetTypes.push_back("calib_c30_chunky");
*/
  std::vector<TString> jetnum;
  jetnum.push_back("0");
  jetnum.push_back("1");
  //jetnum.push_back("2");
  jetnum.push_back("3");

  //Cuts for turnons
  std::vector<TString> genPtCuts;
  genPtCuts.push_back("50.");
  genPtCuts.push_back("100.");
  genPtCuts.push_back("150.");

  std::vector<TString> sumPtCuts;
  sumPtCuts.push_back("100.");
  sumPtCuts.push_back("150.");
  sumPtCuts.push_back("200.");
  sumPtCuts.push_back("300.");

  for(std::vector<TString>::const_iterator iType=jetTypes.begin();
      iType!=jetTypes.end(); iType++){

    //Make a directory for each of the jet types
    TDirectory* jetDir = fout->mkdir(*iType);

    TDirectory* effDir = jetDir->mkdir("efficiency");
    TDirectory* rateDir = jetDir->mkdir("rate");
    TDirectory* sumsEffDir = jetDir->mkdir("sumsEfficiency");
    TDirectory* sumsRateDir = jetDir->mkdir("sumsRate");
    TDirectory* rateEffDir = jetDir->mkdir("rate_eff");
    TDirectory* sumsDir = jetDir->mkdir("sums");
    TDirectory* turnonDir = jetDir->mkdir("jetTurnons");
    TDirectory* sumsTurnonDir = jetDir->mkdir("sumTurnons");

    if(*iType=="calib_gen"){

      makeSums(treeTtbar, sumsDir, *iType, "ttbar");

    }else if(*iType=="met"){

      TH1F* etEff = new TH1F();
      TH1F* metEff = new TH1F();
      TH1F* etRate = new TH1F();
      TH1F* metRate = new TH1F();
      makeSumsEfficiency(treeTtbar,sumsEffDir,*iType,etEff,metEff);
      makeSumsRate(treeNeut, sumsRateDir, *iType, etRate, metRate);
      makeSumsRateEff(rateEffDir, etRate, etEff, metRate, metEff);

    }else if(*iType=="calib_gct" || *iType=="calib_uct"){

      makeSums(treeTtbar, sumsDir, *iType, "ttbar");
      //makeSums(chainNeut, sumsDir, *iType, "ngun",true);
      makeSums(treeNeut, sumsDir, *iType, "ngun");

      makeSumsTurnon(treeTtbar, sumsTurnonDir, *iType, sumPtCuts);
      TH1F* htEff = new TH1F();
      TH1F* mhtEff = new TH1F();
      TH1F* htRate = new TH1F();
      TH1F* mhtRate = new TH1F();
      makeSumsEfficiency(treeTtbar, sumsEffDir, *iType, htEff, mhtEff);
      //makeSumsRate(chainNeut, sumsRateDir, *iType, htRate, mhtRate,true);
      makeSumsRate(treeNeut, sumsRateDir, *iType, htRate, mhtRate);
      makeSumsRateEff(rateEffDir, htRate, htEff, mhtRate, mhtEff);

      makeMatchingEff(treeTtbar, effDir,*iType);

      for(std::vector<TString>::const_iterator iNum=jetnum.begin();
          iNum!=jetnum.end(); iNum++){

        TH1F* eff = makeEfficiency(treeTtbar, effDir, *iType, *iNum);
        //TH1F* rate = makeRate(chainNeut, rateDir, *iType, *iNum);
        TH1F* rate = makeRate(treeNeut, rateDir, *iType, *iNum);

        makeRateEff(rateEffDir, rate, eff, *iNum);

        makeTurnon(treeTtbar, turnonDir, *iType, *iNum, genPtCuts);

        makeEfficienciesNvtx(treeTtbar, effDir, *iType, *iNum);
        makeRatesNvtx(treeNeut, rateDir, *iType, *iNum);
      }

    }else{

      makeSums(treeTtbar, sumsDir, *iType, "ttbar");
      makeSums(treeNeut, sumsDir, *iType, "ngun");
      makeSumsTurnon(treeTtbar, sumsTurnonDir, *iType, sumPtCuts);
      TH1F* htEff = new TH1F();
      TH1F* mhtEff = new TH1F();
      TH1F* htRate = new TH1F();
      TH1F* mhtRate = new TH1F();
      makeSumsEfficiency(treeTtbar, sumsEffDir, *iType, htEff, mhtEff);
      makeSumsRate(treeNeut, sumsRateDir, *iType, htRate, mhtRate);
      makeSumsRateEff(rateEffDir, htRate, htEff, mhtRate, mhtEff);

      makeMatchingEff(treeTtbar, effDir,*iType);

      for(std::vector<TString>::const_iterator iNum=jetnum.begin();
          iNum!=jetnum.end(); iNum++){

        TH1F* eff = makeEfficiency(treeTtbar, effDir, *iType, *iNum);
        TH1F* rate = makeRate(treeNeut, rateDir, *iType, *iNum);

        makeRateEff(rateEffDir, rate, eff, *iNum);

        makeTurnon(treeTtbar, turnonDir, *iType, *iNum, genPtCuts);

        makeEfficienciesNvtx(treeTtbar, effDir, *iType, *iNum);
        makeRatesNvtx(treeNeut, rateDir, *iType, *iNum);
      }
    }
    std::cout << "Done " << iType->Data() << std::endl;

  }

}

void makeRatesNvtx(TTree* tree, TDirectory* dir, TString jetType, TString jetNum){

  dir->cd();
  int cut;
  if(jetNum=="0") cut= 150;
  else if(jetNum=="3") cut= 50;
  TString bins2 = "(20,0,100,1000,0,1000)";
  TString bins = "(20,0,100)";
  double xpoints[50];
  double ypoints[50];
  double ypointserror[50];

  //tree->Draw("jetPt_calib_s0_nopus[0]:nInts_calib>>overall"+bins2,"","colz");
  tree->Draw("nInts_calib>>overall"+bins,"","");
  TH1F *overall = (TH1F*)gDirectory->Get("overall");


  tree->Draw("jetPt_"+jetType+"["+jetNum+"]:nInts_calib>>"+jetType+"_"+jetNum+bins2,"","colz");
  TH2F *fullL1NVTX = (TH2F*)gPad->GetPrimitive(jetType+"_"+jetNum);

  int i=0;

  for(int nvtx=1; nvtx < fullL1NVTX->GetNbinsX(); nvtx+=1){
    char buffer[100];
    sprintf(buffer,"Nvtx%dto%d",nvtx,nvtx+1);
    TH1D * dummyplot = fullL1NVTX->ProjectionY("temp"+jetType+jetNum,nvtx,nvtx+1);
    //TH1D * dummyoverall = overall->ProjectionY("overall"+jetType+jetNum,nvtx,nvtx+1);
    //int overallNorm=dummyoverall->GetEntries();
    int overallNorm=overall->GetBinContent(nvtx);
    //std::cout<<overallNorm<<std::endl;
    //std::cout << dummyplot->GetEntries() <<" "<<dummyoverall->GetEntries() << std::endl;
    if(dummyplot->GetEntries() != 0 && overallNorm!=0){
      TH1D * cumuplot=makeEffNvtxCumu(dummyplot,overallNorm);
      cumuplot->SetTitle(buffer);
      //cumuplot->Write();
      ypoints[i]=cumuplot->GetBinContent(cumuplot->FindBin(cut));
      ypointserror[i]=cumuplot->GetBinError(cumuplot->FindBin(cut));
      //std::cout << ypoints[i]<< std::endl;
    }
    else
    {
      ypoints[i]=0.;
      ypointserror[i]=0.;
    }
    xpoints[i]=fullL1NVTX->GetXaxis()->GetBinCenter(nvtx);
    i++;
  }

  TGraphErrors *rate_nvtx_bin_graph = new TGraphErrors(fullL1NVTX->GetNbinsX()-1,
      &xpoints[0],&ypoints[0],0,&ypointserror[0]);
  //TGraph *rate_nvtx_bin_graph = new TGraph(dummyplot->GetNbinsX(),&xpoints[0],&ypoints[0]);

  rate_nvtx_bin_graph->SetTitle("ptCut"+jetType+jetNum);
  rate_nvtx_bin_graph->GetXaxis()->SetTitle("nvtx");
  rate_nvtx_bin_graph->GetYaxis()->SetTitle("Rate");
  rate_nvtx_bin_graph->SetName("nvtx_ptCut_"+jetNum);
  rate_nvtx_bin_graph->SetMarkerStyle(5);
  //  rate_nvtx_bin_graph->SetLineStyle(0);
  //rate_nvtx_bin_graph->GetYaxis()->SetRangeUser(0,);
  rate_nvtx_bin_graph->Write();

}

void makeEfficienciesNvtx(TTree* tree, TDirectory* dir, TString jetType, TString jetNum){

  dir->cd();
  TString bins2 = "(20,0,100,1000,0,1000)";
  TString bins = "(20,0,100)";
  int cut;
  TCut genptcut;
  if(jetNum=="0"){ 
    cut= 150;
    genptcut = "jetPt_calib_gen["+jetNum+"]>150";
  }
  else if(jetNum=="3"){
    cut= 50;
    genptcut = "jetPt_calib_gen["+jetNum+"]>50";
  }
  else cut=50;
  double xpoints[50];
  double ypoints[50];
  double ypointserror[50];

  //tree->Draw("jetPt_calib_gen["+jetNum+"]:nInts_calib>>overall_"+jetNum+bins2,genptcut,"colz");
  //TH2D *overall = (TH2D*)gDirectory->Get("overall_"+jetNum);
  tree->Draw("nInts_calib>>overall"+bins,"","");
  TH1F *overall = (TH1F*)gDirectory->Get("overall");

  TCut matchedcut = "jetMatchedPt_"+jetType+"["+jetNum+"]!=-1";

  tree->Draw("jetPt_"+jetType+"["+jetNum+"]:nInts_calib>>"+jetType+"_"+jetNum+bins2,
      genptcut&&matchedcut,"colz");
  TH2F *fullL1NVTX = (TH2F*)gDirectory->Get(jetType+"_"+jetNum);

  int i =0;

  for(int nvtx=1; nvtx < fullL1NVTX->GetNbinsX(); nvtx+=1){
    char buffer[100];
    sprintf(buffer,"Nvtx%dto%d",nvtx,nvtx+1);
    TH1D * dummyplot = fullL1NVTX->ProjectionY("temp"+jetType+jetNum,nvtx,nvtx+1);
    //TH1D * dummyoverall = overall->ProjectionY("overalltemp"+jetType+jetNum,nvtx,nvtx+1);
    //double overallNorm = dummyoverall->GetEntries();
    double overallNorm = overall->GetBinContent(nvtx);
    //std::cout << dummyplot->GetEntries() << "  " << dummyoverall->GetEntries() << std::endl;
    //dummyplot->Write();
    if(dummyplot->GetEntries() != 0 && overallNorm!=0){
      TH1D * cumuplot=makeEffNvtxCumu(dummyplot,overallNorm);
      cumuplot->SetTitle(buffer);
      //cumuplot->Write();
      ypoints[i]=cumuplot->GetBinContent(cumuplot->FindBin(cut));
      ypointserror[i]=cumuplot->GetBinError(cumuplot->FindBin(cut));
      //std::cout << ypointserror[i]<< std::endl;
    }
    else
    {
      ypoints[i]=0.;
    }
    xpoints[i]=fullL1NVTX->GetXaxis()->GetBinCenter(nvtx);
    i++;
  }

  TGraphErrors *rate_nvtx_bin_graph = new TGraphErrors(fullL1NVTX->GetNbinsX()-1,&xpoints[0],&ypoints[0],0,&ypointserror[0]);
  //TGraph *rate_nvtx_bin_graph = new TGraph(dummyplot->GetNbinsX(),&xpoints[0],&ypoints[0]);

  rate_nvtx_bin_graph->SetTitle("ptCut"+jetType+jetNum);
  rate_nvtx_bin_graph->GetXaxis()->SetTitle("nvtx");
  rate_nvtx_bin_graph->GetYaxis()->SetTitle("Rate");
  rate_nvtx_bin_graph->SetName("nvtx_ptCut_"+jetNum);
  rate_nvtx_bin_graph->SetMarkerStyle(5);
  //  rate_nvtx_bin_graph->SetLineStyle(0);
  rate_nvtx_bin_graph->GetYaxis()->SetRangeUser(0,1);
  rate_nvtx_bin_graph->Write();


}

void makeTurnon(TTree* tree, TDirectory* dir, TString jetType, TString jetNum,
    const std::vector<TString>& genptcut){

  //TDirectory* subdir = dir->mkdir("jetTurnons");
  //subdir->cd();
  dir->cd();
  tree->Draw("jetMatchedPt_"+jetType+"["+jetNum+"]>>denom_"+jetNum+"(1000,0.,1000.)",
      "jetMatchedPt_"+jetType+"["+jetNum+"]!=-1");
  TH1F *denom = (TH1F*)gDirectory->Get("denom_"+jetNum);
  denom->Write();
  denom->Rebin(10);
  denom->Sumw2();

  for (std::vector<TString>::const_iterator iPt = genptcut.begin(); 
      iPt!=genptcut.end(); iPt++){

    tree->Draw("jetMatchedPt_"+jetType+"["+jetNum+"]>>num_"+jetNum+"_"+*iPt+"(1000.,0.,1000.)",
        "jetPt_"+jetType+"["+jetNum+"]>"+*iPt+"&&jetMatchedPt_"+jetType+"["+jetNum+"]!=-1");
    TH1F *num = (TH1F*)gDirectory->Get("num_"+jetNum+"_"+*iPt);
    num->Write();
    num->Rebin(10);
    num->Sumw2();
    TGraphAsymmErrors * result=(effDiv(num,denom));
    result->Write(("turnon_"+jetNum+"_"+*iPt));
  } 


}

void makeSumsTurnon(TTree* tree, TDirectory* dir, TString jetType,
    const std::vector<TString>& sumptcut){

  tree->Draw("ht_calib_gen>>denom(400,0.,4000.)");
  TH1F *denom = (TH1F*)gDirectory->Get("denom");
  denom->Write();
  //denom->Rebin(10);
  denom->Sumw2();

  for (std::vector<TString>::const_iterator iPt = sumptcut.begin(); 
      iPt!=sumptcut.end(); iPt++){

    tree->Draw("ht_calib_gen>>num_"+*iPt+"(400,0.,4000.)",
        "ht_"+jetType+">"+*iPt);

    TH1F *num = (TH1F*)gDirectory->Get("num_"+*iPt);
    num->Write();
    //num->Rebin(10);
    num->Sumw2();
    TGraphAsymmErrors * result=(effDiv(num,denom));
    result->Write(("ht_"+*iPt));

  } 

  tree->Draw("mht_calib_gen>>denom(400,0.,4000.)");
  TH1F *denom = (TH1F*)gDirectory->Get("denom");
  denom->Write();
  //denom->Rebin(10);
  denom->Sumw2();

  for (std::vector<TString>::const_iterator iPt = sumptcut.begin(); 
      iPt!=sumptcut.end(); iPt++){

    tree->Draw("mht_calib_gen>>num_"+*iPt+"(400,0.,4000.)",
        "mht_"+jetType+">"+*iPt);
    TH1F *num = (TH1F*)gDirectory->Get("num_"+*iPt);
    num->Write();
    //num->Rebin(10);
    num->Sumw2();
    TGraphAsymmErrors * result=(effDiv(num,denom));
    result->Write(("mht_"+*iPt));

  } 


}

void makeMatchingEff(TTree* tree, TDirectory* dir, TString jetType){

  dir->cd();


  tree->Draw("jetPt_"+jetType+">>tmp(100,0.,500.)");
  TH1F *denom = (TH1F*)gDirectory->Get("tmp");
  denom->Sumw2();
  tree->Draw("jetPt_"+jetType+">>tmp2(100,0.,500.)","jetMatchedPt_"+jetType+">0.","");
  TH1F *num = (TH1F*)gDirectory->Get("tmp2");
  num->Sumw2();

  TGraphAsymmErrors * result=(effDiv(num,denom));
  result->SetName("MatchingEff");
  result->Write();


}

void makeRateEff(TDirectory* dir, TH1F* rate, TH1F* efficiency, TString jetNum){

  dir->cd();
  if(rate->GetNbinsX() != efficiency->GetNbinsX()) 
    std::cout << "Different binning between rate and efficiency\n";
  else{

    TGraph * rate_efficiency =
      new TGraph(rate->GetNbinsX());
    rate_efficiency->SetName("rate_efficiency_jet"+jetNum);
    rate_efficiency->SetTitle(";Efficiency (ttbar normalised rate);Rate (0 bias normalised rate)");

    for(unsigned bin=0; bin<rate->GetNbinsX(); bin++){

      rate_efficiency->SetPoint(bin, 
          efficiency->GetBinContent(bin), rate->GetBinContent(bin));

    }

    rate_efficiency->RemovePoint(rate_efficiency->GetN());
    rate_efficiency->Write();
  }

}

void makeSumsRateEff(TDirectory* dir, TH1F* htRate, TH1F* htEff, TH1F* mhtRate, TH1F* mhtEff){

  dir->cd();
  if(htRate->GetNbinsX() != htEff->GetNbinsX()) 
    std::cout << "Different binning between rate and efficiency\n";
  else{

    TGraph * rate_efficiency =
      new TGraph(htRate->GetNbinsX());
    rate_efficiency->SetName("rate_efficiency_ht");
    rate_efficiency->SetTitle(";Efficiency (ttbar normalised rate);Rate (0 bias normalised rate)");

    for(unsigned bin=0; bin<htRate->GetNbinsX(); bin++){

      rate_efficiency->SetPoint(bin, 
          htEff->GetBinContent(bin), htRate->GetBinContent(bin));

    }

    rate_efficiency->RemovePoint(rate_efficiency->GetN());
    rate_efficiency->Write();
  }

  if(mhtRate->GetNbinsX() != mhtEff->GetNbinsX()) 
    std::cout << "Different binning between rate and efficiency\n";
  else{

    TGraph * rate_efficiency =
      new TGraph(mhtRate->GetNbinsX());
    rate_efficiency->SetName("rate_efficiency_mht");
    rate_efficiency->SetTitle(";Efficiency (ttbar normalised rate);Rate (0 bias normalised rate)");

    for(unsigned bin=0; bin<mhtRate->GetNbinsX(); bin++){

      rate_efficiency->SetPoint(bin, 
          mhtEff->GetBinContent(bin), mhtRate->GetBinContent(bin));

    }

    rate_efficiency->RemovePoint(rate_efficiency->GetN());
    rate_efficiency->Write();
  }

}

void makeSums(TTree *tree, TDirectory* dir, TString jetType, TString dataset){

  dir->cd();
  tree->Draw("ht_"+jetType+">>ht_"+jetType+dataset+"(400,0.,4000.)");
  TH1F* test = (TH1F*) gDirectory->Get("ht_"+jetType+dataset);
  test->Write();
  tree->Draw("mhtX_"+jetType+">>mhtX_"+jetType+dataset+"(400,-2000.,2000.)");
  TH1F* test = (TH1F*) gDirectory->Get("mhtX_"+jetType+dataset);
  test->Write();
  tree->Draw("mhtY_"+jetType+">>mhtY_"+jetType+dataset+"(400,-2000.,2000.)");
  TH1F* test = (TH1F*) gDirectory->Get("mhtY_"+jetType+dataset);
  test->Write();
  tree->Draw("mht_"+jetType+">>mht_"+jetType+dataset+"(400,0.,4000.)");
  TH1F* test = (TH1F*) gDirectory->Get("mht_"+jetType+dataset);
  test->Write();
}

TH1F* makeEfficiency(TTree *tree, TDirectory* dir, TString jetType, TString jetNum){

  dir->cd();
  if(jetNum=="0"){
    TCut genptcut = "jetPt_calib_gen["+jetNum+"]>150";
  }else if(jetNum=="1"){
    TCut genptcut = "jetPt_calib_gen["+jetNum+"]>110";
  }else{
    TCut genptcut = "jetPt_calib_gen["+jetNum+"]>50";
  }
  tree->Draw("jetPt_calib_gen["+jetNum+"]>>overall_"+jetNum,genptcut,"");
  TH1F *overall = (TH1F*)gDirectory->Get("overall_"+jetNum);
  double overallNorm = overall->GetEntries();

  TCut matchedcut = "jetMatchedPt_"+jetType+"["+jetNum+"]!=-1";


  tree->Draw("jetPt_"+jetType+"["+jetNum+"]>>"+jetType+"_"+jetNum+"(500,0.,500.)",
      genptcut,"");
  //tree->Draw("jetPt_"+jetType+"["+jetNum+"]>>"+jetType+"_"+jetNum+"(1000,0.,1000.)",
  //    genptcut&&matchedcut,"");
  TH1F *test = (TH1F*)gDirectory->Get(jetType+"_"+jetNum);
  test->Write();
  test->SetName("Efficiency_"+jetNum);

  TH1F* cumuplot = makeEfficiencyCumu(test,overallNorm);
  cumuplot->Write();

  return cumuplot;

}

void makeSumsEfficiency(TTree *tree, TDirectory* dir, TString jetType, TH1F* htEff, TH1F* mhtEff){

  dir->cd();
  TCut genptcut = "ht_calib_gen>200";
  tree->Draw("ht_calib_gen>>overall",genptcut,"");
  TH1F *overall = (TH1F*)gDirectory->Get("overall");
  double overallNorm = overall->GetEntries();

  if(jetType=="met"){
    tree->Draw("et_calib>>"+jetType+"(400,0.,4000.)",
        genptcut,"");
  }else{
    tree->Draw("ht_"+jetType+">>"+jetType+"(400,0.,4000.)",
        genptcut,"");
  }
  TH1F *test = (TH1F*)gDirectory->Get(jetType);
  test->Write();
  test->SetName("ht_Efficiency");

  TH1F* cumuplot = makeEfficiencyCumu(test,overallNorm);
  cumuplot->Write();

  *htEff=*cumuplot;

  TCut genptcut = "mht_calib_gen>200";
  tree->Draw("mht_calib_gen>>overall",genptcut,"");
  TH1F *overall = (TH1F*)gDirectory->Get("overall");
  double overallNorm = overall->GetEntries();

  if(jetType=="met"){
    tree->Draw("met_calib>>"+jetType+"(400,0.,4000.)",
        genptcut,"");
  }else{
    tree->Draw("mht_"+jetType+">>"+jetType+"(400,0.,4000.)",
        genptcut,"");
  }
  TH1F *test = (TH1F*)gDirectory->Get(jetType);
  test->Write();
  test->SetName("mht_Efficiency");

  TH1F* cumuplot = makeEfficiencyCumu(test,overallNorm);
  cumuplot->Write();

  *mhtEff=*cumuplot;

}

TH1F* makeRate(TTree *tree, TDirectory* dir, TString jetType, TString jetNum){

  dir->cd();
  tree->Draw("jetPt_"+jetType+"["+jetNum+"]>>"+jetType+"_"+jetNum+"(500,0.,500.)");
  TH1F *test = (TH1F*)gDirectory->Get(jetType+"_"+jetNum);
  test->Write();
  test->SetName("Rate_"+jetNum);
  TH1F* cumuplot = makeRateCumu(test,tree->GetEntries());
  cumuplot->Write();

  return cumuplot;

}

void makeSumsRate(TTree *tree, TDirectory* dir, TString jetType, TH1F* htRate, TH1F* mhtRate){

  dir->cd();
  if(jetType=="met"){
    tree->Draw("et_calib>>ht_"+jetType+"(400,0.,4000.)");
  }else{
    tree->Draw("ht_"+jetType+">>ht_"+jetType+"(400,0.,4000.)");
  }
  TH1F *test = (TH1F*)gDirectory->Get("ht_"+jetType);
  test->Write();
  test->SetName("ht_Rate");
  TH1F* cumuplot = makeRateCumu(test,tree->GetEntries());
  cumuplot->Write();

  *htRate = *cumuplot;

  if(jetType=="met"){
    tree->Draw("met_calib>>mht_"+jetType+"(400,0.,4000.)");
  }else{
    tree->Draw("mht_"+jetType+">>mht_"+jetType+"(400,0.,4000.)");
  }
  TH1F *test = (TH1F*)gDirectory->Get("mht_"+jetType);
  test->Write();
  test->SetName("mht_Rate");
  TH1F* cumuplot = makeRateCumu(test,tree->GetEntries());
  cumuplot->Write();

  *mhtRate = *cumuplot;
}
/*
   TH1F * makeEfficiencyCumu(TH1F * input, double overallNorm){

   TH1F * output = new TH1F(*input);
//output=input;
int norm = input->GetEntries();
//output->SetBinContent(0,1.);
int nXbins = input->GetNbinsX();
int nYbins = input->GetNbinsY();
int dummy = input->GetBinContent(nXbins+1);
for (int xbins = 0; xbins <= nXbins; xbins++)
{
dummy += input->GetBinContent(nXbins-xbins);
output->SetBinContent((nXbins-xbins),((double)dummy)/overallNorm);
}

return output;
}
*/

TH1F * makeEfficiencyCumu(TH1F * input, double norm){

  TH1F * output = (TH1F*)input->Clone();
  int nXbins = input->GetNbinsX();
  int dummy=0;
  for (int xbins = 0; xbins <= nXbins+1; xbins++)
  {
    dummy += output->GetBinContent(nXbins+1-xbins);
    output->SetBinContent(nXbins+1-xbins,(double)dummy/norm);

  }
  return output;

}

TH1F * makeRateCumu(TH1F * input, double overallNorm){
  std::cout << "overall norm: " << overallNorm << std::endl;

  TH1F * output = new TH1F(*input);
  //output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  int nXbins = input->GetNbinsX();
  int nYbins = input->GetNbinsY();
  int dummy = 0;
  for (int xbins = 0; xbins <= nXbins+1; xbins++)
  {
    dummy += input->GetBinContent(nXbins+1-xbins);
    output->SetBinContent((nXbins+1-xbins),ZB_XSECTION*((double)dummy)/overallNorm);
    //output->SetBinContent((nXbins+1-xbins),((double)dummy)/overallNorm);
  }

  return output;
}

TGraphAsymmErrors * effDiv(TH1F * matchedhist, TH1F * allhist)
{
  TGraphAsymmErrors* matchCurve = new TGraphAsymmErrors();
  matchCurve->SetName("matchCurve");

  //TH1D matcheff = ((*matchedhist).Divide(allhist));
  //matchedhist->Divide(allhist);
  //matchedhist->Draw();

  matchCurve->BayesDivide(matchedhist,allhist);
  return matchCurve;
}

TH1D * makeEffNvtxCumu(TH1D * input, double overallNorm){

  TH1D * output = new TH1D(*input);
  //output=input;
  int norm = input->GetEntries();
  //output->SetBinContent(0,1.);
  int nXbins = input->GetNbinsX();
  int nYbins = input->GetNbinsY();
  int dummy = input->GetBinContent(nXbins+1);
  for (int xbins = 0; xbins <= nXbins; xbins++)
  {
    dummy += input->GetBinContent(nXbins-xbins);
    output->SetBinContent((nXbins-xbins),((double)dummy)/overallNorm);
    output->SetBinError((nXbins-xbins),(sqrt((double)dummy))/overallNorm);
  }

  return output;
}
