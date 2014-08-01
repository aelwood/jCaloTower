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

  int ZB_XSECTION=LHC_FREQUENCY*N_50NS_BUNCHES;

}

void makeJetPlots()
{
  TFile * fout = new TFile("jetPlots_newAreas.root","recreate");

  TFile * finNeutrino = new TFile("ngun_calibJets_newAreas.root");
  TTree * treeNeut = (TTree *)finNeutrino->Get("jetTree");
  treeNeut->AddFriend("demo/L1Tree",
      "/afs/cern.ch/work/a/aelwood/public/NGUN/140729/ngun_14-07-29.root");
  TChain* chainNeut = new TChain("demo/L1Tree");
  chainNeut->Add("/afs/cern.ch/work/a/aelwood/public/NGUN/140729/output*.root");
  //treeNeut->AddFriend("calibJetNgun.root");

  TFile * finTtbar = new TFile("ttbar_calibJets_newAreas.root");
  TTree * treeTtbar = (TTree *)finTtbar->Get("jetTree");
  treeTtbar->AddFriend("demo/L1Tree",
      "/afs/cern.ch/work/a/aelwood/public/TTBAR/140729/ttbar_14-07-29.root");
  //treeTtbar->AddFriend("calibJetsTtbar.root");

  std::vector<TString> jetTypes;
  jetTypes.push_back("calib_s0_nopus");
  jetTypes.push_back("calib_s0_donut");
  jetTypes.push_back("calib_s0_global");
  //jetTypes.push_back("s0_chunky");
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
  jetTypes.push_back("gen");
  jetTypes.push_back("uct_calib_gen");
  jetTypes.push_back("gct_calib_gen");

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

    if(*iType=="gen"){

      makeSums(treeTtbar, sumsDir, *iType, "ttbar", false);

    }else if(iType->Contains("calib_gen")){

      makeSums(treeTtbar, sumsDir, *iType, "ttbar",true);
      makeSums(chainNeut, sumsDir, *iType, "ngun",true);

      makeSumsTurnon(treeTtbar, sumsTurnonDir, *iType, sumPtCuts,true);
      TH1F* htEff = new TH1F();
      TH1F* mhtEff = new TH1F();
      TH1F* htRate = new TH1F();
      TH1F* mhtRate = new TH1F();
      makeSumsEfficiency(treeTtbar, sumsEffDir, *iType, htEff, mhtEff,true);
      makeSumsRate(chainNeut, sumsRateDir, *iType, htRate, mhtRate,true);
      makeSumsRateEff(rateEffDir, htRate, htEff, mhtRate, mhtEff);

      for(std::vector<TString>::const_iterator iNum=jetnum.begin();
          iNum!=jetnum.end(); iNum++){

        TH1F* eff = makeEfficiency(treeTtbar, effDir, *iType, *iNum);
        TH1F* rate = makeRate(chainNeut, rateDir, *iType, *iNum);

        makeRateEff(rateEffDir, rate, eff, *iNum);

        makeTurnon(treeTtbar, turnonDir, *iType, *iNum, genPtCuts);

        makeEfficienciesNvtx(treeTtbar, effDir, *iType, *iNum);
        //makeRatesNvtx(chainNeut, rateDir, *iType, *iNum);
      }

    }else{

      makeSums(treeTtbar, sumsDir, *iType, "ttbar", false);
      makeSums(treeNeut, sumsDir, *iType, "ngun",false);
      makeSumsTurnon(treeTtbar, sumsTurnonDir, *iType, sumPtCuts,false);
      TH1F* htEff = new TH1F();
      TH1F* mhtEff = new TH1F();
      TH1F* htRate = new TH1F();
      TH1F* mhtRate = new TH1F();
      makeSumsEfficiency(treeTtbar, sumsEffDir, *iType, htEff, mhtEff,false);
      makeSumsRate(treeNeut, sumsRateDir, *iType, htRate, mhtRate,false);
      makeSumsRateEff(rateEffDir, htRate, htEff, mhtRate, mhtEff);

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
  if(jetNum=="0") cut= 100;
  else if(jetNum=="3") cut= 30;
  TString bins2 = "(10,0,100,1000,0,1000)";
  TString bins = "(10,0,100)";
  double xpoints[50];
  double ypoints[50];
  double ypointserror[50];

  tree->Draw("jetPt_calib_s0_nopus[0]:mNPV>>overall"+bins2,"","colz");
  TH2F *overall = (TH2F*)gDirectory->Get("overall");

  tree->Draw("jetPt_"+jetType+"["+jetNum+"]:mNPV>>"+jetType+"_"+jetNum+bins2,"","colz");
  TH2F *fullL1NVTX = (TH2F*)gPad->GetPrimitive(jetType+"_"+jetNum);

  int i=0;

  for(int nvtx=1; nvtx < fullL1NVTX->GetNbinsX(); nvtx+=1){
    char buffer[100];
    sprintf(buffer,"Nvtx%dto%d",nvtx,nvtx+1);
    TH1D * dummyplot = fullL1NVTX->ProjectionY("temp"+jetType+jetNum,nvtx,nvtx+1);
    TH1D * dummyoverall = overall->ProjectionY("overall"+jetType+jetNum,nvtx,nvtx+1);
    int overallNorm=dummyoverall->GetEntries();
    //std::cout << dummyplot->GetEntries() <<" "<<dummyoverall->GetEntries() << std::endl;
    if(dummyplot->GetEntries() != 0){
      TH1D * cumuplot=makeEffNvtxCumu(dummyplot,overallNorm);
      cumuplot->SetTitle(buffer);
      //cumuplot->Write();
      ypoints[i]=ZB_XSECTION*cumuplot->GetBinContent(cumuplot->FindBin(cut));
      ypointserror[i]=ZB_XSECTION*cumuplot->GetBinError(cumuplot->FindBin(cut));
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
  rate_nvtx_bin_graph->GetYaxis()->SetRangeUser(0,1);
  rate_nvtx_bin_graph->Write();

}

void makeEfficienciesNvtx(TTree* tree, TDirectory* dir, TString jetType, TString jetNum){

  dir->cd();
  TString bins2 = "(10,0,100,1000,0,1000)";
  int cut;
  if(jetNum=="0") cut= 150;
  else if(jetNum=="3") cut= 50;
  else cut=50;
  double xpoints[50];
  double ypoints[50];
  double ypointserror[50];

  TCut genptcut = "jetPt_ak4_gen["+jetNum+"]>25";
  tree->Draw("jetPt_ak4_gen["+jetNum+"]:mNPV>>overall_"+jetNum+bins2,genptcut,"colz");
  TH2D *overall = (TH2D*)gDirectory->Get("overall_"+jetNum);

  TCut matchedcut = "jetMatchedPt_"+jetType+"["+jetNum+"]!=-1";

  tree->Draw("jetPt_"+jetType+"["+jetNum+"]:mNPV>>"+jetType+"_"+jetNum+bins2,
      genptcut&&matchedcut,"colz");
  TH2F *fullL1NVTX = (TH2F*)gDirectory->Get(jetType+"_"+jetNum);

  int i =0;

  for(int nvtx=1; nvtx < fullL1NVTX->GetNbinsX(); nvtx+=1){
    char buffer[100];
    sprintf(buffer,"Nvtx%dto%d",nvtx,nvtx+1);
    TH1D * dummyplot = fullL1NVTX->ProjectionY("temp"+jetType+jetNum,nvtx,nvtx+1);
    TH1D * dummyoverall = overall->ProjectionY("overalltemp"+jetType+jetNum,nvtx,nvtx+1);
    double overallNorm = dummyoverall->GetEntries();
    //std::cout << dummyplot->GetEntries() << "  " << dummyoverall->GetEntries() << std::endl;
    //dummyplot->Write();
    if(dummyplot->GetEntries() != 0){
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
    const std::vector<TString>& sumptcut, bool doUct){

  tree->Draw("sumsHT_ak4_gen_sum>>denom(400,0.,4000.)");
  TH1F *denom = (TH1F*)gDirectory->Get("denom");
  denom->Write();
  //denom->Rebin(10);
  denom->Sumw2();

  for (std::vector<TString>::const_iterator iPt = sumptcut.begin(); 
      iPt!=sumptcut.end(); iPt++){

    if(doUct){
      tree->Draw("sumsHT_ak4_gen_sum>>num_"+*iPt+"(400,0.,4000.)",
          "sumsHT_"+jetType+"_sum>"+*iPt);
    }else{
      tree->Draw("sumsHT_ak4_gen_sum>>num_"+*iPt+"(400,0.,4000.)",
          "ht_"+jetType+">"+*iPt);
    }
    TH1F *num = (TH1F*)gDirectory->Get("num_"+*iPt);
    num->Write();
    //num->Rebin(10);
    num->Sumw2();
    TGraphAsymmErrors * result=(effDiv(num,denom));
    result->Write(("ht_"+*iPt));

  } 

  tree->Draw("sumsMHT_ak4_gen_sum>>denom(400,0.,4000.)");
  TH1F *denom = (TH1F*)gDirectory->Get("denom");
  denom->Write();
  //denom->Rebin(10);
  denom->Sumw2();

  for (std::vector<TString>::const_iterator iPt = sumptcut.begin(); 
      iPt!=sumptcut.end(); iPt++){

    if(doUct){
      tree->Draw("sumsMHT_ak4_gen_sum>>num_"+*iPt+"(400,0.,4000.)",
          "sumsMHT_"+jetType+"_sum>"+*iPt);
    }else{
      tree->Draw("sumsMHT_ak4_gen_sum>>num_"+*iPt+"(400,0.,4000.)",
          "mht_"+jetType+">"+*iPt);
    }
    TH1F *num = (TH1F*)gDirectory->Get("num_"+*iPt);
    num->Write();
    //num->Rebin(10);
    num->Sumw2();
    TGraphAsymmErrors * result=(effDiv(num,denom));
    result->Write(("mht_"+*iPt));

  } 


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

void makeSums(TTree *tree, TDirectory* dir, TString jetType, TString dataset, bool doUct){

  dir->cd();
  if(doUct){

    tree->Draw("sumsHT_"+jetType+"_sum>>ht_"+jetType+dataset+"(400,0.,4000.)");
    TH1F* test = (TH1F*) gDirectory->Get("ht_"+jetType+dataset);
    test->Write();
    tree->Draw("sumsMHTx_"+jetType+"_sum>>mhtX_"+jetType+dataset+"(400,-2000.,2000.)");
    TH1F* test = (TH1F*) gDirectory->Get("mhtX_"+jetType+dataset);
    test->Write();
    tree->Draw("sumsMHTy_"+jetType+"_sum>>mhtY_"+jetType+dataset+"(400,-2000.,2000.)");
    TH1F* test = (TH1F*) gDirectory->Get("mhtY_"+jetType+dataset);
    test->Write();
    tree->Draw("sumsMHT_"+jetType+"_sum>>mht_"+jetType+dataset+"(400,0.,4000.)");
    TH1F* test = (TH1F*) gDirectory->Get("mht_"+jetType+dataset);
    test->Write();

  }else{
    if(jetType=="gen"){
      tree->Draw("sumsHT_ak4_gen_sum>>ht_gen_"+dataset+"(400,0.,4000.)");
      TH1F* test = (TH1F*) gDirectory->Get("ht_gen_"+dataset);
      test->Write();
      tree->Draw("sumsMHTx_ak4_gen_sum>>mhtX_gen_"+dataset+"(400,-2000.,2000.)");
      TH1F* test = (TH1F*) gDirectory->Get("mhtX_gen_"+dataset);
      test->Write();
      tree->Draw("sumsMHTy_ak4_gen_sum>>mhtY_gen_"+dataset+"(400,-2000.,2000.)");
      TH1F* test = (TH1F*) gDirectory->Get("mhtY_gen_"+dataset);
      test->Write();
      tree->Draw("sumsMHT_ak4_gen_sum>>mht_gen_"+dataset+"(400,0.,2000.)");
      TH1F* test = (TH1F*) gDirectory->Get("mht_gen_"+dataset);
      test->Write();
    }else{
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
  }
}

TH1F* makeEfficiency(TTree *tree, TDirectory* dir, TString jetType, TString jetNum){

  dir->cd();
  if(jetNum=="0"){
    TCut genptcut = "jetPt_ak4_gen["+jetNum+"]>200";
  }else{
    TCut genptcut = "jetPt_ak4_gen["+jetNum+"]>50";
  }
  tree->Draw("jetPt_ak4_gen["+jetNum+"]>>overall_"+jetNum,genptcut,"");
  TH1F *overall = (TH1F*)gDirectory->Get("overall_"+jetNum);
  double overallNorm = overall->GetEntries();

  TCut matchedcut = "jetMatchedPt_"+jetType+"["+jetNum+"]!=-1";


  tree->Draw("jetPt_"+jetType+"["+jetNum+"]>>"+jetType+"_"+jetNum+"(1000,0.,1000.)",
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

void makeSumsEfficiency(TTree *tree, TDirectory* dir, TString jetType, TH1F* htEff, TH1F* mhtEff, bool doUct){

  dir->cd();
  TCut genptcut = "sumsHT_ak4_gen_sum>200";
  tree->Draw("sumsHT_ak4_gen_sum>>overall",genptcut,"");
  TH1F *overall = (TH1F*)gDirectory->Get("overall");
  double overallNorm = overall->GetEntries();

  if(doUct){
    tree->Draw("sumsHT_"+jetType+"_sum>>"+jetType+"(400,0.,4000.)",
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

  TCut genptcut = "sumsMHT_ak4_gen_sum>200";
  tree->Draw("sumsMHT_ak4_gen_sum>>overall",genptcut,"");
  TH1F *overall = (TH1F*)gDirectory->Get("overall");
  double overallNorm = overall->GetEntries();

  if(doUct){
    tree->Draw("sumsMHT_"+jetType+"_sum>>"+jetType+"(400,0.,4000.)",
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
  tree->Draw("jetPt_"+jetType+"["+jetNum+"]>>"+jetType+"_"+jetNum+"(1000,-0.5,999.5)");
  TH1F *test = (TH1F*)gDirectory->Get(jetType+"_"+jetNum);
  test->Write();
  test->SetName("Rate_"+jetNum);
  TH1F* cumuplot = makeRateCumu(test,tree->GetEntries());
  cumuplot->Write();

  return cumuplot;

}

void makeSumsRate(TTree *tree, TDirectory* dir, TString jetType, TH1F* htRate, TH1F* mhtRate, bool doUct){

  dir->cd();
  if(doUct){
    tree->Draw("sumsHT_"+jetType+"_sum>>ht_"+jetType+"(400,0.,4000.)");
  }else{
    tree->Draw("ht_"+jetType+">>ht_"+jetType+"(400,0.,4000.)");
  }
  TH1F *test = (TH1F*)gDirectory->Get("ht_"+jetType);
  test->Write();
  test->SetName("ht_Rate");
  TH1F* cumuplot = makeRateCumu(test,tree->GetEntries());
  cumuplot->Write();

  *htRate = *cumuplot;

  if(doUct){
    tree->Draw("sumsMHT_"+jetType+"_sum>>mht_"+jetType+"(400,0.,4000.)");
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

TH1F * makeRateCumu(TH1F * input, double overallNorm){

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

  matchCurve->Divide(matchedhist,allhist);
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