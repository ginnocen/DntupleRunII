using namespace std;
#include "uti.h"

#define BIN_NUM_PP 14
Float_t ptbins_PP[BIN_NUM_PP+1] = {2.,3.,4.,5.,6.,8.,10.,12.5,15.0,20.,25.,30.,40.,60.,100};
#define BIN_NUM_PbPb 13
Float_t ptbins_PbPb[BIN_NUM_PbPb+1] = {2.,4.,5.,6.,8.,10.,12.5,15.0,20.,25.,30.,40.,60.,100};

void plotFractions()
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
  gStyle->SetOptStat(0);
  gStyle->SetMarkerStyle(20);
  gStyle->SetMarkerSize(0.9);

  Float_t aPfracCtv_PP[BIN_NUM_PP];
  Float_t aPfracErr_PP[BIN_NUM_PP];
  Float_t aPfracCtv_PbPb[BIN_NUM_PbPb];
  Float_t aPfracErr_PbPb[BIN_NUM_PbPb];

  TFile* fPbPb = new TFile("bFeedDownResultPbPb.root");
  TGraphErrors* grPbPb = fPbPb->Get("grPromptFraction");
  TFile* fPP = new TFile("bFeedDownResultPP.root");
  TGraphErrors* grPP = fPP->Get("grPromptFraction");

  for(int i=0; i<BIN_NUM_PP; i++)
    {
      aPfracCtv_PP[i] = grPP->GetY()[i];
      aPfracErr_PP[i] = grPP->GetEY()[i];
    }

  for(int i=0; i<BIN_NUM_PbPb; i++)
    {
      aPfracCtv_PbPb[i] =grPbPb->GetY()[i];
      aPfracErr_PbPb[i] =grPbPb->GetEY()[i];
    }

  Float_t aXptCtv_PP[BIN_NUM_PP], aXptErr_PP[BIN_NUM_PP], aNPfracCtv_PP[BIN_NUM_PP], aNPfracErr_PP[BIN_NUM_PP];
  Float_t aXptCtv_PbPb[BIN_NUM_PbPb], aXptErr_PbPb[BIN_NUM_PbPb], aNPfracCtv_PbPb[BIN_NUM_PbPb], aNPfracErr_PbPb[BIN_NUM_PbPb];

  for(int i=0;i<BIN_NUM_PP;i++)
    {
      aXptCtv_PP[i] = (ptbins_PP[i]+ptbins_PP[i+1])/2.;
      aXptErr_PP[i] = (ptbins_PP[i+1]-ptbins_PP[i])/2.;
      aNPfracCtv_PP[i] = 1. - aPfracCtv_PP[i];
      aNPfracErr_PP[i] = aPfracErr_PP[i];
    }
  for(int i=0;i<BIN_NUM_PbPb;i++)
    {
      aXptCtv_PbPb[i] = (ptbins_PbPb[i]+ptbins_PbPb[i+1])/2.;
      aXptErr_PbPb[i] = (ptbins_PbPb[i+1]-ptbins_PbPb[i])/2.;
      aNPfracCtv_PbPb[i] = 1. - aPfracCtv_PbPb[i];
      aNPfracErr_PbPb[i] = aPfracErr_PbPb[i];
    }

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.04);
  texCms->SetTextFont(42);
  TLatex* texCol_PP = new TLatex(0.96,0.93, "PP #sqrt{s_{NN}} = 5.02 TeV");
  texCol_PP->SetNDC();
  texCol_PP->SetTextAlign(32);
  texCol_PP->SetTextSize(0.04);
  texCol_PP->SetTextFont(42);
  TLatex* texCol_PbPb = new TLatex(0.96,0.93, "PbPb #sqrt{s_{NN}} = 5.02 TeV");
  texCol_PbPb->SetNDC();
  texCol_PbPb->SetTextAlign(32);
  texCol_PbPb->SetTextSize(0.04);
  texCol_PbPb->SetTextFont(42);
  TLatex* texY = new TLatex(0.59,0.65,"|y| < 1.0");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.04);

  TGraphErrors* gPfrac_PP = new TGraphErrors(BIN_NUM_PP,aXptCtv_PP,aPfracCtv_PP,aXptErr_PP,aPfracErr_PP);
  gPfrac_PP->SetLineColor(2);
  gPfrac_PP->SetLineWidth(2);
  gPfrac_PP->SetMarkerColor(2);
  TGraphErrors* gNPfrac_PP = new TGraphErrors(BIN_NUM_PP,aXptCtv_PP,aNPfracCtv_PP,aXptErr_PP,aNPfracErr_PP);
  gNPfrac_PP->SetLineColor(4);
  gNPfrac_PP->SetLineWidth(2);
  gNPfrac_PP->SetMarkerColor(4);

  TH2F* hempty_PP = new TH2F("hempty_PP","",20,0,105,10,0,1);
  hempty_PP->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty_PP->GetYaxis()->SetTitle("Fraction");
  hempty_PP->GetXaxis()->CenterTitle();
  hempty_PP->GetYaxis()->CenterTitle();
  hempty_PP->GetXaxis()->SetTitleOffset(1.2);
  hempty_PP->GetYaxis()->SetTitleOffset(1.2);
  hempty_PP->GetXaxis()->SetTitleSize(0.045);
  hempty_PP->GetYaxis()->SetTitleSize(0.045);
  hempty_PP->GetXaxis()->SetTitleFont(42);
  hempty_PP->GetYaxis()->SetTitleFont(42);
  hempty_PP->GetXaxis()->SetLabelFont(42);
  hempty_PP->GetYaxis()->SetLabelFont(42);
  hempty_PP->GetXaxis()->SetLabelSize(0.04);
  hempty_PP->GetYaxis()->SetLabelSize(0.04);
  TLegend* leg_PP = new TLegend(0.57,0.51,0.85,0.63,NULL,"brNDC");
  leg_PP->SetBorderSize(0);
  leg_PP->SetTextSize(0.04);
  leg_PP->SetTextFont(42);
  leg_PP->SetFillStyle(0);
  leg_PP->AddEntry(gPfrac_PP,"Prompt","pl");
  leg_PP->AddEntry(gNPfrac_PP,"Non-prompt","pl");
  TCanvas* cPNPfrac_PP = new TCanvas("cPNPfrac_PP","",600,600);
  hempty_PP->Draw();
  gPfrac_PP->Draw("psame");
  gNPfrac_PP->Draw("psame");
  texCms->Draw();
  texCol_PP->Draw();
  texY->Draw();
  leg_PP->Draw("same");

  TH1D* bFeedDownFractionSysPP = new TH1D("bFeedDownFractionSysPP","",BIN_NUM_PP,ptbins_PP);
  bFeedDownFractionSysPP->SetBinContent(1,    10);
  bFeedDownFractionSysPP->SetBinContent(2,    5);
  bFeedDownFractionSysPP->SetBinContent(3,    5);
  bFeedDownFractionSysPP->SetBinContent(4,    5);
  bFeedDownFractionSysPP->SetBinContent(5,    5);
  bFeedDownFractionSysPP->SetBinContent(6,    5);
  bFeedDownFractionSysPP->SetBinContent(7,    5);
  bFeedDownFractionSysPP->SetBinContent(8,    5);
  bFeedDownFractionSysPP->SetBinContent(9,    5);
  bFeedDownFractionSysPP->SetBinContent(10,    5);
  bFeedDownFractionSysPP->SetBinContent(11,    5);
  bFeedDownFractionSysPP->SetBinContent(12,    5);
  bFeedDownFractionSysPP->SetBinContent(13,    5);
  bFeedDownFractionSysPP->SetBinContent(14,    5);

  for(int i=0;i<BIN_NUM_PP;i++) {
    double x1 = bFeedDownFractionSysPP->GetXaxis()->GetBinLowEdge(i+1);
    double x2 = bFeedDownFractionSysPP->GetXaxis()->GetBinUpEdge(i+1);
    double y1 = aPfracCtv_PP[i]-bFeedDownFractionSysPP->GetBinContent(i+1)*0.01;
    double y2 = aPfracCtv_PP[i]+bFeedDownFractionSysPP->GetBinContent(i+1)*0.01;

    TBox *box = new TBox(x1, y1, x2, y2);
    box->SetLineColor(kPink+1);
    box->SetFillColor(kPink+1);
    box->Draw("same");
  }

  for(int i=0;i<BIN_NUM_PP;i++) {
    double x1 = bFeedDownFractionSysPP->GetXaxis()->GetBinLowEdge(i+1);
    double x2 = bFeedDownFractionSysPP->GetXaxis()->GetBinUpEdge(i+1);
    double y1 = 1-aPfracCtv_PP[i]-bFeedDownFractionSysPP->GetBinContent(i+1)*0.01;
    double y2 = 1-aPfracCtv_PP[i]+bFeedDownFractionSysPP->GetBinContent(i+1)*0.01;

    TBox *box = new TBox(x1, y1, x2, y2);
    box->SetLineColor(kCyan);
    box->SetFillColor(kCyan);
    box->Draw("same");
  }

  gPfrac_PP->Draw("psame");
  gNPfrac_PP->Draw("psame");
  cPNPfrac_PP->SaveAs("cPNPfrac_PP.pdf");

  TGraphErrors* gPfrac_PbPb = new TGraphErrors(BIN_NUM_PbPb,aXptCtv_PbPb,aPfracCtv_PbPb,aXptErr_PbPb,aPfracErr_PbPb);
  gPfrac_PbPb->SetLineColor(2);
  gPfrac_PbPb->SetLineWidth(2);
  gPfrac_PbPb->SetMarkerColor(2);
  TGraphErrors* gNPfrac_PbPb = new TGraphErrors(BIN_NUM_PbPb,aXptCtv_PbPb,aNPfracCtv_PbPb,aXptErr_PbPb,aNPfracErr_PbPb);
  gNPfrac_PbPb->SetLineColor(4);
  gNPfrac_PbPb->SetLineWidth(2);
  gNPfrac_PbPb->SetMarkerColor(4);
  TH2F* hempty_PbPb = new TH2F("hempty_PbPb","",20,0,105,10,0,1);
  hempty_PbPb->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty_PbPb->GetYaxis()->SetTitle("Fraction");
  hempty_PbPb->GetXaxis()->CenterTitle();
  hempty_PbPb->GetYaxis()->CenterTitle();
  hempty_PbPb->GetXaxis()->SetTitleOffset(1.2);
  hempty_PbPb->GetYaxis()->SetTitleOffset(1.2);
  hempty_PbPb->GetXaxis()->SetTitleSize(0.045);
  hempty_PbPb->GetYaxis()->SetTitleSize(0.045);
  hempty_PbPb->GetXaxis()->SetTitleFont(42);
  hempty_PbPb->GetYaxis()->SetTitleFont(42);
  hempty_PbPb->GetXaxis()->SetLabelFont(42);
  hempty_PbPb->GetYaxis()->SetLabelFont(42);
  hempty_PbPb->GetXaxis()->SetLabelSize(0.04);
  hempty_PbPb->GetYaxis()->SetLabelSize(0.04);
  TLegend* leg_PbPb = new TLegend(0.57,0.51,0.85,0.63,NULL,"brNDC");
  leg_PbPb->SetBorderSize(0);
  leg_PbPb->SetTextSize(0.04);
  leg_PbPb->SetTextFont(42);
  leg_PbPb->SetFillStyle(0);
  leg_PbPb->AddEntry(gPfrac_PbPb,"Prompt","pl");
  leg_PbPb->AddEntry(gNPfrac_PbPb,"Non-prompt","pl");
  TCanvas* cPNPfrac_PbPb = new TCanvas("cPNPfrac_PbPb","",600,600);
  hempty_PbPb->Draw();
  gPfrac_PbPb->Draw("psame");
  gNPfrac_PbPb->Draw("psame");
  texCms->Draw();
  texCol_PbPb->Draw();
  texY->Draw();
  leg_PbPb->Draw("same");

  TH1D* bFeedDownFractionSysPbPb = new TH1D("bFeedDownFractionSysPbPb","",BIN_NUM_PbPb,ptbins_PbPb);
  bFeedDownFractionSysPbPb->SetBinContent(1,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(2,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(3,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(4,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(5,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(6,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(7,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(8,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(9,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(10,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(11,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(12,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(13,    10.);
  bFeedDownFractionSysPbPb->SetBinContent(14,    10.);

  for(int i=0;i<BIN_NUM_PbPb;i++) {
    double x1 = bFeedDownFractionSysPbPb->GetXaxis()->GetBinLowEdge(i+1);
    double x2 = bFeedDownFractionSysPbPb->GetXaxis()->GetBinUpEdge(i+1);
    double y1 = aPfracCtv_PbPb[i]-bFeedDownFractionSysPbPb->GetBinContent(i+1)*0.01;
    double y2 = aPfracCtv_PbPb[i]+bFeedDownFractionSysPbPb->GetBinContent(i+1)*0.01;

    TBox *box = new TBox(x1, y1, x2, y2);
    box->SetLineColor(kPink+1);
    box->SetFillColor(kPink+1);
    box->Draw("same");
  }

  for(int i=0;i<BIN_NUM_PbPb;i++) {
    double x1 = bFeedDownFractionSysPbPb->GetXaxis()->GetBinLowEdge(i+1);
    double x2 = bFeedDownFractionSysPbPb->GetXaxis()->GetBinUpEdge(i+1);
    double y1 = 1-aPfracCtv_PbPb[i]-bFeedDownFractionSysPbPb->GetBinContent(i+1)*0.01;
    double y2 = 1-aPfracCtv_PbPb[i]+bFeedDownFractionSysPbPb->GetBinContent(i+1)*0.01;

    TBox *box = new TBox(x1, y1, x2, y2);
    box->SetLineColor(kCyan);
    box->SetFillColor(kCyan);
    box->Draw("same");
  }

  gPfrac_PbPb->Draw("psame");
  gNPfrac_PbPb->Draw("psame");

  cPNPfrac_PbPb->SaveAs("cPNPfrac_PbPb.pdf");

}
