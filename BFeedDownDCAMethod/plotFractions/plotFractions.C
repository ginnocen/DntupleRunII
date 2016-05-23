using namespace std;
#include "uti.h"

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

  TFile* fPbPb = new TFile("bFeedDownResultPbPb.root");
  TGraphErrors* grPPbPb = fPbPb->Get("grPromptFraction");
  TFile* fPP = new TFile("bFeedDownResultPP.root");
  TGraphErrors* grPPP = fPP->Get("grPromptFraction");

  TGraphErrors* grNpPP = grPPP->Clone("grNpPP");
  for(int i=0; i<grNpPP->GetN(); i++)
    grNpPP->SetPoint(i, grPPP->GetX()[i], 1-grPPP->GetY()[i]);

  TGraphErrors* grPPPSys = grPPP->Clone("grPPPSys");
  for(int i=0; i<grPPPSys->GetN(); i++)
    {
      if(i==0)
	grPPPSys->SetPointError(i, grPPP->GetEX()[i], 0.1);
      else
        grPPPSys->SetPointError(i, grPPP->GetEX()[i], 0.05);
    }

  TGraphErrors* grNpPPSys = grPPPSys->Clone("grNpPPSys");
  for(int i=0; i<grNpPPSys->GetN(); i++)
    grNpPPSys->SetPoint(i, grPPPSys->GetX()[i], 1-grPPPSys->GetY()[i]);

  TGraphErrors* grNpPbPb = grPPbPb->Clone("grNpPbPb");
  for(int i=0; i<grNpPbPb->GetN(); i++)
    grNpPbPb->SetPoint(i, grPPbPb->GetX()[i], 1-grPPbPb->GetY()[i]);

  TGraphErrors* grPPbPbSys = grPPbPb->Clone("grPPbPbSys");
  for(int i=0; i<grPPbPbSys->GetN(); i++)
    grPPbPbSys->SetPointError(i, grPPbPb->GetEX()[i], 0.1);

  TGraphErrors* grNpPbPbSys = grPPbPbSys->Clone("grNpPbPbSys");
  for(int i=0; i<grNpPbPbSys->GetN(); i++)
    grNpPbPbSys->SetPoint(i, grPPbPbSys->GetX()[i], 1-grPPbPbSys->GetY()[i]);

  grPPP->SetLineColor(2);
  grPPP->SetLineWidth(2);
  grPPP->SetMarkerColor(2);

  grNpPP->SetLineColor(4);
  grNpPP->SetLineWidth(2);
  grNpPP->SetMarkerColor(4);

  /*
  grPPPSys->SetLineColor(kRed-9);
  grPPPSys->SetFillColor(kRed-9);
  grPPPSys->SetFillStyle(1001);

  grNpPPSys->SetLineColor(kBlue-9);
  grNpPPSys->SetFillColor(kBlue-9);
  grNpPPSys->SetFillStyle(1001);
  */

  grPPPSys->SetLineColor(kRed);
  grPPPSys->SetLineWidth(2);
  grPPPSys->SetFillStyle(0);

  grNpPPSys->SetLineColor(kBlue);
  grNpPPSys->SetLineWidth(2);
  grNpPPSys->SetFillStyle(0);

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

  TLatex* texY = new TLatex(0.59,0.6,"|y| < 1.0");
  texY->SetNDC();
  texY->SetTextFont(42);
  texY->SetTextSize(0.04);

  TH2F* hempty = new TH2F("hempty","",20,0,105,10,0,1);
  hempty->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hempty->GetYaxis()->SetTitle("Fraction");
  hempty->GetXaxis()->CenterTitle();
  hempty->GetYaxis()->CenterTitle();
  hempty->GetXaxis()->SetTitleOffset(1.2);
  hempty->GetYaxis()->SetTitleOffset(1.2);
  hempty->GetXaxis()->SetTitleSize(0.045);
  hempty->GetYaxis()->SetTitleSize(0.045);
  hempty->GetXaxis()->SetTitleFont(42);
  hempty->GetYaxis()->SetTitleFont(42);
  hempty->GetXaxis()->SetLabelFont(42);
  hempty->GetYaxis()->SetLabelFont(42);
  hempty->GetXaxis()->SetLabelSize(0.04);
  hempty->GetYaxis()->SetLabelSize(0.04);

  TLegend* leg_PP = new TLegend(0.57,0.46,0.85,0.58,NULL,"brNDC");
  leg_PP->SetBorderSize(0);
  leg_PP->SetTextSize(0.04);
  leg_PP->SetTextFont(42);
  leg_PP->SetFillStyle(0);
  leg_PP->AddEntry(grPPP,"Prompt","pl");
  leg_PP->AddEntry(grNpPP,"Non-prompt","pl");

  TCanvas* c1 = new TCanvas("c1","",600,600);
  hempty->Draw();
  texCms->Draw();
  texCol_PP->Draw();
  texY->Draw();
  leg_PP->Draw("same");

  grPPPSys->Draw("5same");
  grNpPPSys->Draw("5same");
  grPPP->Draw("psame");
  grNpPP->Draw("psame");
  c1->SaveAs("FractionPP.pdf");

  /////////

  grPPbPb->SetLineColor(2);
  grPPbPb->SetLineWidth(2);
  grPPbPb->SetMarkerColor(2);

  grNpPbPb->SetLineColor(4);
  grNpPbPb->SetLineWidth(2);
  grNpPbPb->SetMarkerColor(4);

  /*
  grPPbPbSys->SetLineColor(kRed-9);
  grPPbPbSys->SetFillColor(kRed-9);
  grPPbPbSys->SetFillStyle(1001);

  grNpPbPbSys->SetLineColor(kBlue-9);
  grNpPbPbSys->SetFillColor(kBlue-9);
  grNpPbPbSys->SetFillStyle(1001);
  */

  grPPbPbSys->SetLineColor(kRed);
  grPPbPbSys->SetLineWidth(2);
  grPPbPbSys->SetFillStyle(0);

  grNpPbPbSys->SetLineColor(kBlue);
  grNpPbPbSys->SetLineWidth(2);
  grNpPbPbSys->SetFillStyle(0);

  TLegend* leg_PbPb = new TLegend(0.57,0.46,0.85,0.58,NULL,"brNDC");
  leg_PbPb->SetBorderSize(0);
  leg_PbPb->SetTextSize(0.04);
  leg_PbPb->SetTextFont(42);
  leg_PbPb->SetFillStyle(0);
  leg_PbPb->AddEntry(grPPbPb,"Prompt","pl");
  leg_PbPb->AddEntry(grNpPbPb,"Non-prompt","pl");

  hempty->Draw();
  texCms->Draw();
  texCol_PbPb->Draw();
  texY->Draw();
  leg_PbPb->Draw("same");

  grPPbPbSys->Draw("5same");
  grNpPbPbSys->Draw("5same");
  grPPbPb->Draw("psame");
  grNpPbPb->Draw("psame");
  c1->SaveAs("FractionPbPb.pdf");

  /////////

  grPPP->SetLineColor(4);
  grPPP->SetMarkerColor(4);

  grPPbPbSys->SetLineColor(kRed);
  grPPbPbSys->SetFillColor(kRed);

  grPPPSys->SetLineColor(kBlue);
  grPPPSys->SetFillColor(kBlue);

  grPPPSys->SetLineWidth(2);
  grPPbPbSys->SetLineWidth(2);
  grPPPSys->SetFillStyle(0);
  grPPbPbSys->SetFillStyle(0);

  TLegend* leg_compare = new TLegend(0.3,0.36,0.85,0.48,NULL,"brNDC");
  leg_compare->SetBorderSize(0);
  leg_compare->SetTextSize(0.04);
  leg_compare->SetTextFont(42);
  leg_compare->SetFillStyle(0);
  leg_compare->AddEntry(grPPP,"pp 25.8 pb^{-1}","pl");
  leg_compare->AddEntry(grPPbPb,"PbPb Centrality 0-100% 404 #mub^{-1}","pl");

  TLatex* texY2 = new TLatex(0.33,0.5,"|y| < 1.0");
  texY2->SetNDC();
  texY2->SetTextFont(42);
  texY2->SetTextSize(0.04);

  TLatex* texCol = new TLatex(0.96,0.93, "#sqrt{s_{NN}} = 5.02 TeV");
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.04);
  texCol->SetTextFont(42);

  hempty->GetYaxis()->SetTitle("Prompt fraction");

  c1->SetLogx();
  hempty->Draw();
  texCms->Draw();
  texY2->Draw();
  texCol->Draw();
  leg_compare->Draw("same");
  //  grPPPSys->Draw("[]same");
  //  grPPbPbSys->Draw("[]same");
  grPPPSys->Draw("5same");
  grPPbPbSys->Draw("5same");
  grPPP->Draw("psame");
  grPPbPb->Draw("psame");

  c1->SaveAs("FractionPPPbPb.pdf");
}
