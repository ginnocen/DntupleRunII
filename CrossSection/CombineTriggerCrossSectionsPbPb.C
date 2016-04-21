#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "../Systematics/systematics.C"

void CombineTriggerCrossSectionsPbPb()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile* fileMB = new TFile("ROOTfiles/CrossSectionFONLLPbPbMB_extended.root");  
  TFile* file20 = new TFile("ROOTfiles/CrossSectionFONLLPbPb_20.root");  
  TFile* file40 = new TFile("ROOTfiles/CrossSectionFONLLPbPb_40.root");  
  TFile* file60 = new TFile("ROOTfiles/CrossSectionFONLLPbPb_60.root");  
  
  TH1D* hSigmaStatMB_Original = (TH1D*)fileMB->Get("hPtSigma");
  TH1D* hSigmaStat20 = (TH1D*)file20->Get("hPtSigma");
  TH1D* hSigmaStat40 = (TH1D*)file40->Get("hPtSigma");
  TH1D* hSigmaStat60 = (TH1D*)file60->Get("hPtSigma");
  
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

  hSigmaStatMB_Original->SetLineColor(6);
  hSigmaStatMB_Original->SetLineWidth(3);
  hSigmaStatMB_Original->SetMarkerColor(6);
  hSigmaStatMB_Original->Draw("same");

  hSigmaStat20->SetLineColor(1);
  hSigmaStat20->SetLineWidth(3);
  hSigmaStat20->SetMarkerColor(1);
  hSigmaStat20->Draw("same");

  hSigmaStat40->SetLineColor(2);
  hSigmaStat40->SetLineWidth(3);
  hSigmaStat40->SetMarkerColor(2);
  hSigmaStat40->Draw("same");

  hSigmaStat60->SetLineColor(4);
  hSigmaStat60->SetLineWidth(3);
  hSigmaStat60->SetMarkerColor(4);
  hSigmaStat60->Draw("same");

  TLegend *legendSigma=new TLegend(0.54,0.66,0.87,0.84,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);
      
  TLegendEntry *ent_SigmaMB = legendSigma->AddEntry(hSigmaStatMB_Original,"MB pp ref.","f");
  ent_SigmaMB->SetTextFont(42);
  ent_SigmaMB->SetLineColor(6);
  ent_SigmaMB->SetMarkerColor(6);
  TLegendEntry *ent_SigmaHLT20 = legendSigma->AddEntry(hSigmaStat20,"HLT20 pp ref.","f");
  ent_SigmaHLT20->SetTextFont(42);
  ent_SigmaHLT20->SetLineColor(1);
  ent_SigmaHLT20->SetMarkerColor(1);
  TLegendEntry *ent_SigmaHLT40 = legendSigma->AddEntry(hSigmaStat40,"HLT40 pp ref.","f");
  ent_SigmaHLT40->SetTextFont(42);
  ent_SigmaHLT40->SetLineColor(2);
  ent_SigmaHLT40->SetMarkerColor(2);
  TLegendEntry *ent_SigmaHLT60 = legendSigma->AddEntry(hSigmaStat60,"HLT60 pp ref.","f");
  ent_SigmaHLT60->SetTextFont(42);
  ent_SigmaHLT60->SetLineColor(4);
  ent_SigmaHLT60->SetMarkerColor(4);
  legendSigma->Draw("same");
  
  cSigma->cd(2);

  TH1D* hSigmaStatRatio40 = (TH1D*)hSigmaStat40->Clone("hSigmaStatRatio40");
  TH1D* hSigmaStatRatio60 = (TH1D*)hSigmaStat60->Clone("hSigmaStatRatio60");
  
  hSigmaStatRatio40->Divide(hSigmaStat20);
  hSigmaStatRatio60->Divide(hSigmaStat40);
  
  hSigmaStatRatio40->SetBinContent(6,0);
  hSigmaStatRatio40->SetBinError(6,0);
  hSigmaStatRatio40->SetBinContent(7,0);
  hSigmaStatRatio40->SetBinError(7,0);

  hSigmaStatRatio60->SetBinContent(1,0);
  hSigmaStatRatio60->SetBinError(1,0);
  hSigmaStatRatio60->SetBinContent(2,0);
  hSigmaStatRatio60->SetBinError(2,0);
  hSigmaStatRatio60->SetBinContent(3,0);
  hSigmaStatRatio60->SetBinError(3,0);

  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,0.,110.,10.,0.,2.0);//50,0.,110.,10.,0.,4
  hemptyRatio->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Ratio HLT D trigger /previous HLT trigger");
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

  TLine* line = new TLine(2.2,1,110,1);//10,1,105,1
  line->SetLineWidth(2);
  line->SetLineStyle(2);  


  const int binsMB=3;
  double ptBinsMB[4]={20,25,30,40};
  TH1D* hSigmaStatMBreduced = new TH1D("hSigmaStatMBreduced","",binsMB,ptBinsMB);
  hSigmaStatMBreduced->SetBinContent(1,hSigmaStatMB_Original->GetBinContent(hSigmaStatMB_Original->FindBin(22.5)));
  hSigmaStatMBreduced->SetBinContent(2,hSigmaStatMB_Original->GetBinContent(hSigmaStatMB_Original->FindBin(27.5)));
  hSigmaStatMBreduced->SetBinContent(3,hSigmaStatMB_Original->GetBinContent(hSigmaStatMB_Original->FindBin(35.5)));
  hSigmaStatMBreduced->SetBinError(1,hSigmaStatMB_Original->GetBinError(hSigmaStatMB_Original->FindBin(22.5)));
  hSigmaStatMBreduced->SetBinError(2,hSigmaStatMB_Original->GetBinError(hSigmaStatMB_Original->FindBin(27.5)));
  hSigmaStatMBreduced->SetBinError(3,hSigmaStatMB_Original->GetBinError(hSigmaStatMB_Original->FindBin(35.0)));
  
  TH1D* hSigmaStatRatio20 = new TH1D("hSigmaStatRatio20","",binsMB,ptBinsMB);
  hSigmaStatRatio20->SetBinContent(1,hSigmaStat20->GetBinContent(hSigmaStat20->FindBin(22.5)));
  hSigmaStatRatio20->SetBinContent(2,hSigmaStat20->GetBinContent(hSigmaStat20->FindBin(27.5)));
  hSigmaStatRatio20->SetBinContent(3,hSigmaStat20->GetBinContent(hSigmaStat20->FindBin(35.0)));
  hSigmaStatRatio20->SetBinError(1,hSigmaStat20->GetBinError(hSigmaStat20->FindBin(22.5)));
  hSigmaStatRatio20->SetBinError(2,hSigmaStat20->GetBinError(hSigmaStat20->FindBin(27.5)));
  hSigmaStatRatio20->SetBinError(3,hSigmaStat20->GetBinError(hSigmaStat20->FindBin(35.0)));
  
  hSigmaStatRatio20->Divide(hSigmaStatMBreduced);
  hSigmaStatRatio20->SetLineColor(1);
  hSigmaStatRatio20->SetLineWidth(3);
  hSigmaStatRatio20->SetMarkerColor(1);
  hSigmaStatRatio20->Draw("same");

  hSigmaStatRatio40->SetLineColor(2);
  hSigmaStatRatio40->SetLineWidth(3);
  hSigmaStatRatio40->SetMarkerColor(2);
  hSigmaStatRatio40->Draw("same");

  hSigmaStatRatio60->SetLineColor(4);
  hSigmaStatRatio60->SetLineWidth(3);
  hSigmaStatRatio60->SetMarkerColor(4);
  hSigmaStatRatio60->Draw("same");
  cSigma->SaveAs("TriggerCrossSectionPbPb.pdf");

}
