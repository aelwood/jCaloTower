void efficienciesNVTXsan(){
//TFile * f_ttbar= new TFile("ttbar_output.root");
TFile * f_ttbar= new TFile("/afs/cern.ch/work/m/mcitron/public/TTBAR/140622/ttbar_output.root");
//TFile * f_ttbar= new TFile("ttbar-output-2014-06-22.root");
TFile * f_out= new TFile("./effTestNVTX.root","recreate");
TTree * tree_ttbar = f_ttbar->Get("demo/L1Tree;");
std::vector<TString> jetnum;
jetnum.push_back("0");
jetnum.push_back("1");
jetnum.push_back("2");
jetnum.push_back("3");
int cut = 50;
TString gencut = "25";
std::vector<TString> jetType;
jetType.push_back("5400_calib_nopus");
jetType.push_back("5450_calib_nopus");
jetType.push_back("5450_calib_donut");
jetType.push_back("5400_calib_donut");
jetType.push_back("5400_calib_global");
jetType.push_back("gct_calib_gen");

TString bins2 = "(10,0,100,1000,0,1000)";
double xpoints[50];
double ypoints[50];
double ypointserror[50];
for (iNum = jetnum.begin();iNum != jetnum.end(); iNum++)
{
  TDirectory * jnum = f_out->mkdir("jetNumber_"+*iNum);
  jnum->cd();
  TCut genptcut = "jetPt_ak4_gen["+*iNum+"]>"+gencut;
  tree_ttbar->Draw("jetPt_ak4_gen["+*iNum+"]:mNPV>>overall_"+*iNum+bins2,genptcut,"colz");
  TH2D *overall = (TH2D*)gPad->GetPrimitive("overall_"+*iNum);
  for (iType = jetType.begin();iType != jetType.end(); iType++)
  {

    TCut matchedcut = "jetMatchedPt_"+*iType+"["+*iNum+"]!=-1";

    tree_ttbar->Draw("jetPt_"+*iType+"["+*iNum+"]:mNPV>>"+*iType+"_"+*iNum+bins2,genptcut&&matchedcut,"colz");
    TH2F *fullL1NVTX = (TH2F*)gPad->GetPrimitive(*iType+"_"+*iNum);

    int i =0;

    for(int nvtx=1; nvtx < fullL1NVTX->GetNbinsX(); nvtx+=1){
      char buffer[1000];
      sprintf(buffer,"Nvtx%dto%d",nvtx,nvtx+1);
      TH1D * dummyplot = fullL1NVTX->ProjectionY("temp"+*iType+*iNum,nvtx,nvtx+1);
      TH1D * dummyoverall = overall->ProjectionY("overalltemp"+*iType+*iNum,nvtx,nvtx+1);
      double overallNorm = dummyoverall->GetEntries();
      //std::cout << dummyplot->GetEntries() << "  " << dummyoverall->GetEntries() << std::endl;
      //dummyplot->Write();
      if(dummyplot->GetEntries() != 0){
	TH1D * cumuplot=makeCumu(dummyplot,overallNorm);
	cumuplot->SetTitle(buffer);
	cumuplot->Write();
	ypoints[i]=cumuplot->GetBinContent(cumuplot->FindBin(cut));
	ypointserror[i]=cumuplot->GetBinError(cumuplot->FindBin(cut));
	std::cout << ypointserror[i]<< std::endl;
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

    rate_nvtx_bin_graph->SetTitle("ptCut"+*iType+*iNum);
    rate_nvtx_bin_graph->GetXaxis()->SetTitle("nvtx");
    rate_nvtx_bin_graph->GetYaxis()->SetTitle("Rate");
    rate_nvtx_bin_graph->SetName("ptCut"+*iType+*iNum);
    rate_nvtx_bin_graph->SetMarkerStyle(5);
    //  rate_nvtx_bin_graph->SetLineStyle(0);
    rate_nvtx_bin_graph->GetYaxis()->SetRangeUser(0,1);
    rate_nvtx_bin_graph->Write();
  }
}
f_out->Close();
return;
}

TH1D * makeCumu(TH1D * input, double overallNorm){

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
