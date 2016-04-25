#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "../Systematics/systematics.C"

void CombineTriggerCrossSectionsPP()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);


  const int nFiles = 5;
  TString myfiles[nFiles] = {"ROOTfiles/CrossSectionFONLLPPMB_extended.root", 
                                            "ROOTfiles/CrossSectionFONLLPP_8.root",
                                            "ROOTfiles/CrossSectionFONLLPP_15.root",
                                            "ROOTfiles/CrossSectionFONLLPP_30.root",
                                            "ROOTfiles/CrossSectionFONLLPP_50.root"};
  TString label[nFiles] = {"MB", "HLTD8", "HLTD15", "HLTD30","HLTD30"};

  int colors[nFiles] = {1,2,3,4,6};

  TH1D* hYieldTriggerCorrected[nFiles];
  TH1D* hTriggerEfficiency[nFiles];
  TH1D* hYieldTriggerCorrectedFONLLnorm[nFiles];
  TFile* files[nFiles];
  TLegendEntry *entry[nFiles];
  
  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    hYieldTriggerCorrected[ifile] = (TH1D*)files[ifile]->Get("hYieldTriggerCorrected");
    hYieldTriggerCorrectedFONLLnorm[ifile] = (TH1D*)files[ifile]->Get("hYieldTriggerCorrectedFONLLnorm");
    if(ifile>0) hTriggerEfficiency[ifile] = (TH1D*)files[ifile]->Get("hTriggerEfficiencyPtBins");
  }
    
  TCanvas* cSigma = new TCanvas("cSigma","",1000,500);
  cSigma->Divide(2,1);
  cSigma->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1e0,1.e12);  
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
  
  cSigma->cd(2);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,3,100.,10.,1,20);
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("RATIO/FONLL");
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
    hYieldTriggerCorrectedFONLLnorm[ifile] ->SetMarkerColor(colors[ifile]);
    hYieldTriggerCorrectedFONLLnorm[ifile] ->Draw("psame");  
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


}


void CombineTriggerCrossSectionsPbPb()
{
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
  TH1D* hYieldTriggerCorrectedFONLLnorm[nFiles];
  TFile* files[nFiles];
  TLegendEntry *entry[nFiles];
  
  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    hYieldTriggerCorrected[ifile] = (TH1D*)files[ifile]->Get("hYieldTriggerCorrected");
    hYieldTriggerCorrectedFONLLnorm[ifile] = (TH1D*)files[ifile]->Get("gaeRatioCrossFONLLstat");
  }
    
  TCanvas* cSigma = new TCanvas("cSigma","",1000,500);
  cSigma->Divide(2,1);
  cSigma->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1e0,1.e9);  
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
  
  TLegend *legendSigma=new TLegend(0.54,0.66,0.87,0.84,"");//0.5100806,0.5868644,0.8084677,0.7605932
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
  
  cSigma->cd(2);
  gPad->SetLogy();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,10,100.,10.,0.01,200);
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("RATIO/FONLL");
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
    hYieldTriggerCorrectedFONLLnorm[ifile] ->SetMarkerColor(colors[ifile]);
    hYieldTriggerCorrectedFONLLnorm[ifile] ->Draw("psame");  
  }
    legendSigma->Draw("same");
  cSigma->SaveAs("TriggerCrossSectionPbPb.pdf");
}

