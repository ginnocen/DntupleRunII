#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "../Systematics/systematics.C"

void CombineTriggerCrossSectionsPbPb()
{

  TString cut="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)";
  TString selection="1";
  double TAA=392.4/(70.*1e9);

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nFiles = 4;
  TString myfiles[nFiles] = {"ROOTfiles/CrossSectionFONLLPbPbMB_extended.root", 
                                            "ROOTfiles/CrossSectionFONLLPbPb_20.root",
                                            "ROOTfiles/CrossSectionFONLLPbPb_40.root",
                                            "ROOTfiles/CrossSectionFONLLPbPb_60.root"};
  TString label[nFiles] = {"MB", "HLTD20", "HLTD40", "HLTD60"};

  int colors[nFiles] = {1,2,3,4};

  TH1D* hYieldTriggerCorrected[nFiles];
  TH1D* hTriggerEfficiency[nFiles];
  TH1D* hYieldTriggerCorrectedFONLLnorm[nFiles];
  TH1D* hDcandidatesTriggerCorrectedFONLLnorm[nFiles];
  
  TFile* files[nFiles];
  TLegendEntry *entry[nFiles];
  
  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    hYieldTriggerCorrected[ifile] = (TH1D*)files[ifile]->Get("hYieldTriggerCorrected");
    hYieldTriggerCorrectedFONLLnorm[ifile] = (TH1D*)files[ifile]->Get("hYieldTriggerCorrectedFONLLnorm");
    hDcandidatesTriggerCorrectedFONLLnorm[ifile] = (TH1D*)files[ifile]->Get("hDcandidatesTriggerCorrectedFONLLnorm");
    if(ifile>0) hTriggerEfficiency[ifile] = (TH1D*)files[ifile]->Get("hTriggerEfficiencyPtBins");
  }
    
  TCanvas* cSigmaAll = new TCanvas("cSigmaAll","",1000,500);
  cSigmaAll->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1e-5,1.e12);  
  hemptySigma->GetXaxis()->CenterTitle();
  hemptySigma->GetYaxis()->CenterTitle();
  hemptySigma->GetYaxis()->SetTitle("1/T_{AA} * dN / dp_{T}( pb GeV^{-1}c)");
  hemptySigma->GetXaxis()->SetTitleOffset(1.);
  hemptySigma->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptySigma->GetXaxis()->SetTitleSize(0.045);
  hemptySigma->GetYaxis()->SetTitleSize(0.045);
  hemptySigma->GetXaxis()->SetTitleFont(42);
  hemptySigma->GetYaxis()->SetTitleFont(42);
  hemptySigma->GetXaxis()->SetLabelFont(42);
  hemptySigma->GetYaxis()->SetLabelFont(42);
  hemptySigma->GetXaxis()->SetLabelSize(0.04);
  hemptySigma->GetYaxis()->SetLabelSize(0.04);  
  hemptySigma->Draw();
  
  TLegend *legendSigma=new TLegend(0.311747,0.6945694,0.6401439,0.8740055,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);

      
  for (int ifile=0;ifile<nFiles;ifile++){
    hYieldTriggerCorrected[ifile] ->SetLineColor(colors[ifile]);
    hYieldTriggerCorrected[ifile] ->SetLineWidth(3);
    hYieldTriggerCorrected[ifile] ->SetMarkerColor(colors[ifile]);
    hYieldTriggerCorrected[ifile] ->Draw("same");  
    entry[ifile]=legendSigma->AddEntry(hYieldTriggerCorrected[ifile],label[ifile].Data(),"f");
    entry[ifile]->SetTextFont(42);
    entry[ifile]->SetLineColor(colors[ifile]);
    entry[ifile]->SetMarkerColor(colors[ifile]);
  }
  legendSigma->Draw("same");
  

  TCanvas* cSigma = new TCanvas("cSigma","",1000,500);
  cSigma->Divide(2,1);
  cSigma->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,3,100.,10.,0.00001,5);
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Corrected yields/FONLL");
  hemptyRatio->GetXaxis()->SetTitleOffset(1.);
  hemptyRatio->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyRatio->GetXaxis()->SetTitleSize(0.045);
  hemptyRatio->GetYaxis()->SetTitleSize(0.045);
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetXaxis()->SetLabelSize(0.04);
  hemptyRatio->GetYaxis()->SetLabelSize(0.04);  
  hemptyRatio->Draw();

  for (int ifile=0;ifile<nFiles;ifile++){
    hYieldTriggerCorrectedFONLLnorm[ifile] ->SetLineColor(colors[ifile]);
    hYieldTriggerCorrectedFONLLnorm[ifile] ->SetLineWidth(3);
    if(ifile==0)hYieldTriggerCorrectedFONLLnorm[ifile] ->SetLineWidth(6);
    hYieldTriggerCorrectedFONLLnorm[ifile] ->SetMarkerColor(colors[ifile]);
    hYieldTriggerCorrectedFONLLnorm[ifile] ->Draw("psame");  
  }
    legendSigma->Draw("same");
    
  cSigma->cd(2);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptyRatioCounting=new TH2F("hemptyRatioCounting","",50,3,100.,10.,0.00001,5);
  hemptyRatioCounting->GetXaxis()->CenterTitle();
  hemptyRatioCounting->GetYaxis()->CenterTitle();
  hemptyRatioCounting->GetYaxis()->SetTitle("D counting/FONLL");
  hemptyRatioCounting->GetXaxis()->SetTitleOffset(1.);
  hemptyRatioCounting->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyRatioCounting->GetXaxis()->SetTitleSize(0.045);
  hemptyRatioCounting->GetYaxis()->SetTitleSize(0.045);
  hemptyRatioCounting->GetXaxis()->SetTitleFont(42);
  hemptyRatioCounting->GetYaxis()->SetTitleFont(42);
  hemptyRatioCounting->GetXaxis()->SetLabelFont(42);
  hemptyRatioCounting->GetYaxis()->SetLabelFont(42);
  hemptyRatioCounting->GetXaxis()->SetLabelSize(0.04);
  hemptyRatioCounting->GetYaxis()->SetLabelSize(0.04);  
  hemptyRatioCounting->Draw();

  for (int ifile=0;ifile<nFiles;ifile++){
    hDcandidatesTriggerCorrectedFONLLnorm[ifile] ->SetLineColor(colors[ifile]);
    hDcandidatesTriggerCorrectedFONLLnorm[ifile] ->SetLineWidth(3);
    if(ifile==0)hDcandidatesTriggerCorrectedFONLLnorm[ifile] ->SetLineWidth(6);
    hDcandidatesTriggerCorrectedFONLLnorm[ifile] ->SetMarkerColor(colors[ifile]);
    hDcandidatesTriggerCorrectedFONLLnorm[ifile] ->Draw("psame");  
  }
    legendSigma->Draw("same");
  cSigma->SaveAs("TriggerCrossSectionPP.pdf");

  TCanvas* cTriggerEff = new TCanvas("cTriggerEff","",500,500);
  cTriggerEff->cd();
  TH2F* hemptyEff=new TH2F("hemptyEff","",50,10,100.,10.,0.,1.9);
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("Triggere efficiency");
  hemptyEff->GetXaxis()->SetTitleOffset(1.);
  hemptyEff->GetYaxis()->SetTitleOffset(1.4);//1.3
  hemptyEff->GetXaxis()->SetTitleSize(0.045);
  hemptyEff->GetYaxis()->SetTitleSize(0.045);
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.04);
  hemptyEff->GetYaxis()->SetLabelSize(0.04);   
  hemptyEff->Draw();
  
  for (int ifile=1;ifile<nFiles;ifile++){
    hTriggerEfficiency[ifile] ->SetLineColor(colors[ifile]);
    hTriggerEfficiency[ifile] ->SetLineWidth(3);
    hTriggerEfficiency[ifile] ->SetMarkerColor(colors[ifile]);
    hTriggerEfficiency[ifile] ->SetMarkerStyle(23);
    hTriggerEfficiency[ifile] ->SetMarkerSize(1);
    hTriggerEfficiency[ifile] ->Draw("psame");  
  }
  
 legendSigma->Draw("same");
 cTriggerEff->SaveAs("TriggerEffPP.pdf");

 /*
  TString inputfilePbPbMB="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root";
  TFile* filePbPbMBraw = new TFile(inputfilePbPbMB.Data());  
  TTree* HltTreePbPbMB= (TTree*) filePbPbMBraw->Get("ntHlt");
  TTree* HltHiPbPbMB= (TTree*) filePbPbMBraw->Get("ntHi");
  HltTreePbPbMB->AddFriend(HltHiPbPbMB);
  
  TH1D*hcountsMBPbPb=new TH1D("hcountsMBPbPb","hcountsMBPbPb",2,-200,200);
  HltTreePbPbMB->Draw("1>>hcountsMBPbPb",Form("%s&&%s",cut.Data(),selection.Data()));
  double ncountsMBPbPb=hcountsMBPbPb->GetEntries();
  */
  double ncountsMBPbPb=1.48357e+08;
  double lumiPbPbMB=ncountsMBPbPb*TAA;
  cout<<"ncountsMBPbPb="<<ncountsMBPbPb<<endl;
  cout<<"luminosity MB="<<lumiPbPbMB<<endl;


  const int nbinsstudy=3;
  double binsstudy[nbinsstudy+1]={15.,20.,25.,30.};
  double binmedium[nbinsstudy]={17.5,22.5,27.5};
  
  TH1D* hValuesMB = new TH1D("hValuesMB","",nbinsstudy,binsstudy);
  TH1D* hValuesD20 = new TH1D("hValuesD20","",nbinsstudy,binsstudy);
  TH1D* hDcandValuesMB = new TH1D("hDcandValuesMB","",nbinsstudy,binsstudy);
  TH1D* hDcandValuesD20 = new TH1D("hDcandValuesD20","",nbinsstudy,binsstudy);

  for (int i=0;i<nbinsstudy;i++){
  
    double valueMB=hYieldTriggerCorrected[0]->GetBinContent(hYieldTriggerCorrected[0]->FindBin(binmedium[i]));
    double errvalueMB=hYieldTriggerCorrected[0]->GetBinError(hYieldTriggerCorrected[0]->FindBin(binmedium[i]));
    double valueD20=hYieldTriggerCorrected[1]->GetBinContent(hYieldTriggerCorrected[1]->FindBin(binmedium[i]));
    double errvalueD20=hYieldTriggerCorrected[1]->GetBinError(hYieldTriggerCorrected[1]->FindBin(binmedium[i]));
    
    double DcandvalueMB=hDcandidatesTriggerCorrectedFONLLnorm[0]->GetBinContent(hDcandidatesTriggerCorrectedFONLLnorm[0]->FindBin(binmedium[i]));
    double DcanderrvalueMB=hDcandidatesTriggerCorrectedFONLLnorm[0]->GetBinError(hDcandidatesTriggerCorrectedFONLLnorm[0]->FindBin(binmedium[i]));
    double DcandvalueD20=hDcandidatesTriggerCorrectedFONLLnorm[1]->GetBinContent(hDcandidatesTriggerCorrectedFONLLnorm[1]->FindBin(binmedium[i]));
    double DcanderrvalueD20=hDcandidatesTriggerCorrectedFONLLnorm[1]->GetBinError(hDcandidatesTriggerCorrectedFONLLnorm[1]->FindBin(binmedium[i]));

    hValuesMB->SetBinContent(i+1,valueMB);
    hValuesMB->SetBinError(i+1,errvalueMB);
    hValuesD20->SetBinContent(i+1,valueD20);
    hValuesD20->SetBinError(i+1,errvalueD20);
    
    hDcandValuesMB->SetBinContent(i+1,DcandvalueMB);
    hDcandValuesMB->SetBinError(i+1,DcanderrvalueMB);
    hDcandValuesD20->SetBinContent(i+1,DcandvalueD20);
    hDcandValuesD20->SetBinError(i+1,DcanderrvalueD20);

  }

  hValuesD20->Sumw2();
  hValuesMB->Sumw2();
  hDcandValuesD20->Sumw2();
  hDcandValuesMB->Sumw2();
  
  TH1D* hRatioTriggeredOverMB = (TH1D*)hValuesD20->Clone("hRatioTriggeredOverMB");
  hRatioTriggeredOverMB->Divide(hValuesMB);
  hRatioTriggeredOverMB->Scale(lumiPbPbMB);  
  
  TH1D* hRatioTriggeredOverMBDcand = (TH1D*)hDcandValuesD20->Clone("hRatioTriggeredOverMBDcand");
  hRatioTriggeredOverMBDcand->Divide(hDcandValuesMB);
  hRatioTriggeredOverMBDcand->Scale(lumiPbPbMB);  

  for (int i=1;i<3;i++) cout<<"luminosity="<<hRatioTriggeredOverMB->GetBinContent(i)<<"with error="<<hRatioTriggeredOverMB->GetBinError(i)<<endl;
  for (int i=1;i<3;i++) cout<<"luminosity Dcand="<<hRatioTriggeredOverMBDcand->GetBinContent(i)<<"with error="<<hRatioTriggeredOverMBDcand->GetBinError(i)<<endl;

  TCanvas*canvas=new TCanvas("canvas","canvas",1000,500);
  canvas->Divide(2,1);
  canvas->cd(1);
  TH2F* hemptyLumi=new TH2F("hemptyLumi","",50,15,35,10.,0,30); 
  hemptyLumi->GetXaxis()->CenterTitle();
  hemptyLumi->GetYaxis()->CenterTitle();
  hemptyLumi->GetYaxis()->SetTitle("Luminosity (pb)");
  hemptyLumi->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyLumi->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyLumi->GetYaxis()->SetTitleOffset(1.24);//1.
  hemptyLumi->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyLumi->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyLumi->GetXaxis()->SetTitleFont(42);
  hemptyLumi->GetYaxis()->SetTitleFont(42);
  hemptyLumi->GetXaxis()->SetLabelFont(42);
  hemptyLumi->GetYaxis()->SetLabelFont(42);
  hemptyLumi->GetXaxis()->SetLabelSize(0.040);//0.035
  hemptyLumi->GetYaxis()->SetLabelSize(0.040);//0.035  
  hemptyLumi->GetXaxis()->SetLabelOffset(0.01);
  hemptyLumi->Draw();
  hRatioTriggeredOverMB->Draw("same");
  hRatioTriggeredOverMB->Fit("pol0","","",20,30);
  canvas->cd(2);
  hemptyLumi->Draw();
  hRatioTriggeredOverMBDcand->Draw("same");
  hRatioTriggeredOverMBDcand->Fit("pol0","","",20,30);

}
