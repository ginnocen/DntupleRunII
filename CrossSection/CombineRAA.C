#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"


void CombineRAA()
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile* filePPMB = new TFile("outputRAAMB.root");  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");

  TFile* filePP = new TFile("outputRAA.root");  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  
  TFile *fRAA=new TFile("/afs/cern.ch/work/g/ginnocen/public/PlotRAA.root");
  TH1D*hTrackPt_trkCorr_PbPb_copy1=(TH1D*)fRAA->Get("hTrackPt_trkCorr_PbPb_copy1");
  

  TCanvas*canvasRAA=new TCanvas("canvasRAA","canvasRAA",550,500);
  canvasRAA->cd();
  canvasRAA->SetLogx();
  TH2F* hemptyEff=new TH2F("hemptyEff","",50,0.,120.,10.,0,1.5);  
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("D^{0} R_{AA}");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.9);
  hemptyEff->GetYaxis()->SetTitleOffset(1.);
  hemptyEff->GetXaxis()->SetTitleSize(0.045);
  hemptyEff->GetYaxis()->SetTitleSize(0.045);
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.035);
  hemptyEff->GetYaxis()->SetLabelSize(0.035);  
  hemptyEff->SetMaximum(2);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();
  gNuclearModification->SetFillColor(4);
  gNuclearModification->SetFillStyle(0); 
  gNuclearModification->SetLineWidth(3);
  gNuclearModification->SetLineColor(4);
  gNuclearModification->Draw("5same");
  gNuclearModificationMB->SetFillColor(1);
  gNuclearModificationMB->SetFillStyle(0); 
  gNuclearModificationMB->SetLineWidth(3);
  gNuclearModificationMB->SetLineColor(1);
  gNuclearModificationMB->Draw("5same");

  hNuclearModification->SetLineColor(4);
  hNuclearModification->SetLineWidth(3);
  hNuclearModification->Draw("same");
  hNuclearModificationMB->SetLineColor(1);
  hNuclearModificationMB->SetLineWidth(3);
  hNuclearModificationMB->Draw("same");
  
  hTrackPt_trkCorr_PbPb_copy1->Draw("same");
  hTrackPt_trkCorr_PbPb_copy1->SetLineWidth(3);

  TLatex * tlatexeff=new TLatex(0.2612903,0.9025793,"CMS Preliminary     PbPb #sqrt{s_{NN}}= 5.02 TeV");
  tlatexeff->SetNDC();
  tlatexeff->SetTextColor(1);
  tlatexeff->SetTextFont(42);
  tlatexeff->SetTextSize(0.04);
  tlatexeff->Draw();
  TLatex * tlatexeff2=new TLatex(0.2612903,0.8425793,"Centrality 0-100%");
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextSize(0.04);
  tlatexeff2->Draw();

  TLegend *legendSigma=new TLegend(0.5100806,0.6268644,0.8084677,0.7805932,"");
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.05);

  TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(hNuclearModification,"R_{AA} D triggers.","pf");
  ent_Dhighpt->SetTextFont(42);
  ent_Dhighpt->SetLineColor(4);
  ent_Dhighpt->SetMarkerColor(4);
  ent_Dhighpt->SetTextSize(0.03);
  
  TLegendEntry *ent_DMB=legendSigma->AddEntry(hNuclearModificationMB,"R_{AA} D MB.","pf");
  ent_DMB->SetTextFont(42);
  ent_DMB->SetLineColor(1);
  ent_DMB->SetMarkerColor(1);
  ent_DMB->SetTextSize(0.03);
  
  TLegendEntry *ent_Charged=legendSigma->AddEntry(hTrackPt_trkCorr_PbPb_copy1,"R_{AA} charged hadrons.","pf");
  ent_Charged->SetTextFont(42);
  ent_Charged->SetLineColor(1);
  ent_Charged->SetMarkerColor(1);
  ent_Charged->SetTextSize(0.03);
  
  legendSigma->Draw();
  canvasRAA->SaveAs("canvasRAAComparison.pdf");

  }

