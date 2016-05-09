#include "uti.h"

void compareEfficiency()
{
  
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nFiles = 6;
  TString labelh[3]={"D20 yield","D40 yield","D60 yield"};
  TString labelg[3]={"D20 counting","D40 counting","D60 counting"};
  
  TFile*filegraph=new TFile("result_PbPbHPPlusMB/fefficiency.root");
  TFile*filehisto20=new TFile("fitefficiencyPbPb/fileoutput__HLT_HIDmesonHITrackingGlobal_Dpt20_v2_pt.root");
  TFile*filehisto40=new TFile("fitefficiencyPbPb/fileoutput__HLT_HIDmesonHITrackingGlobal_Dpt40_v1_pt.root");
  TFile*filehisto60=new TFile("fitefficiencyPbPb/fileoutput__HLT_HIDmesonHITrackingGlobal_Dpt60_v1_pt.root");
  
  int colors[3]={1,2,4};
    int colors2[nFiles] = {7,8,6};

  TGraphAsymmErrors* geff[3];
  geff[0] =(TGraphAsymmErrors*)filegraph->Get("g20");
  geff[1] =(TGraphAsymmErrors*)filegraph->Get("g40");
  geff[2] =(TGraphAsymmErrors*)filegraph->Get("g60");
  
  
  TH1D* hEff[3];
  hEff[0]=(TH1D*)filehisto20->Get("hEff");
  hEff[1]=(TH1D*)filehisto40->Get("hEff");
  hEff[2]=(TH1D*)filehisto60->Get("hEff");


  TCanvas* cRatio = new TCanvas("cRatio","",500,500);
  cRatio->cd(1);
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,0,100.,10.,0.0,2.0);
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("Trigger efficiency");
  hemptyRatio->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
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


  TLegend *legendSigma=new TLegend(0.3111702,0.5744337,0.6396277,0.8754045,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);

TLegendEntry *entryh[3];
TLegendEntry *entryg[3];
    
  /*
  for (int ifile=0;ifile<3;ifile++){
    geff[ifile] ->SetLineColor(colors[ifile]);
    geff[ifile] ->SetMarkerColor(colors[ifile]);
    geff[ifile] ->SetLineWidth(3);
    geff[ifile] ->Draw("epsame");  
    entryg[ifile]=legendSigma->AddEntry(geff[ifile],labelg[ifile].Data(),"");
    entryg[ifile]->SetTextFont(42);
    entryg[ifile]->SetTextColor(colors[ifile]);
  }
  */
  for (int ifile=0;ifile<3;ifile++){
    hEff[ifile] ->SetLineColor(colors2[ifile]);
    hEff[ifile] ->SetMarkerColor(colors2[ifile]);
    hEff[ifile] ->SetLineWidth(3);
    hEff[ifile] ->Draw("same");  
    entryh[ifile]=legendSigma->AddEntry(hEff[ifile],labelh[ifile].Data(),"");
    entryh[ifile]->SetTextFont(42);
    entryh[ifile]->SetTextColor(colors2[ifile]);
  }

  legendSigma->Draw("same");
}
