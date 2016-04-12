#include "uti.h"
#include "config/parametersAllpt.h"
#include "TLegendEntry.h"
#include "../Systematics/systematicsUpgrade.C"

void DRAAUpgrade()
{
  double valuestat=TMath::Sqrt(6);

  TString label="PbPb";
  double lumi=1.;
  Float_t centMin=0.;
  Float_t centMax=100.;
  TString outputplot="myplot.root";
   
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  const int nBinsALL=15;
  double ptBinsALL[nBinsALL+1] = {2.,3.,4.,5.,6.,8.,10.,15.,20.,25,30.,40.,50.,60.,80,100};

  TH1D* hNuclearModification = new TH1D("hNuclearModification","",nBinsALL,ptBinsALL);

   hNuclearModification->SetBinContent(1,0.4940044);
   hNuclearModification->SetBinContent(2,0.3611425);
   hNuclearModification->SetBinContent(3,0.2887014);
   hNuclearModification->SetBinContent(4,0.2191777);
   hNuclearModification->SetBinContent(5,0.1801597);
   hNuclearModification->SetBinContent(6,0.2082608);
   hNuclearModification->SetBinContent(7,0.2943809*0.86);
   hNuclearModification->SetBinContent(8,0.3253622*0.9);
   hNuclearModification->SetBinError(1,0.07079711);
   hNuclearModification->SetBinError(2,0.03914169);
   hNuclearModification->SetBinError(3,0.0289943);
   hNuclearModification->SetBinError(4,0.02136124);
   hNuclearModification->SetBinError(5,0.01596234);
   hNuclearModification->SetBinError(6,0.02123644);
   hNuclearModification->SetBinError(7,0.0258278*0.86);
   hNuclearModification->SetBinError(8,0.03298711*0.9);
   hNuclearModification->SetBinContent(9,0.3160656);
   hNuclearModification->SetBinContent(10,0.3574212);
   hNuclearModification->SetBinContent(11,0.4011382);
   hNuclearModification->SetBinContent(12,0.5257663*0.85);
   hNuclearModification->SetBinContent(13,0.4821855);
   hNuclearModification->SetBinContent(14,0.4211179*1.2);
   hNuclearModification->SetBinContent(15,0.4885929*1.1);
   hNuclearModification->SetBinError(9,0.01957154);
   hNuclearModification->SetBinError(10,0.02881201);
   hNuclearModification->SetBinError(11,0.03232225);
   hNuclearModification->SetBinError(12,0.03442699*0.85);
   hNuclearModification->SetBinError(13,0.04948654);
   hNuclearModification->SetBinError(14,0.03791096*1.2);
   hNuclearModification->SetBinError(15,0.085353*1.1);
   
  for(int i=0;i<nBins;i++){
    hNuclearModification->SetBinError(i+1,hNuclearModification->GetBinError(i+1)/valuestat);
  }

  double apt[nBins];
  //bin half width
  double aptl[nBins];
  //number of every rebined bin
  double bin_num[nBins];


  for (int ibin=0; ibin<nBins; ibin++){
    apt[ibin]=(ptBins[ibin+1]+ptBins[ibin])/2.;
    aptl[ibin] = (ptBins[ibin+1]-ptBins[ibin])/2;
    bin_num[ibin]=aptl[ibin]/binsize*2;
  }

  Double_t xr[nBins], yr[nBins], xrlow[nBins], yrlow[nBins],xrhigh[nBins],yrhigh[nBins];
  
  for(int i=0;i<nBins;i++)
  {
    yr[i] = hNuclearModification->GetBinContent(i+1);
    double systematic=0.01*systematicsForRAA(hNuclearModification->GetBinCenter(i+1),0.,0.);
    yrlow[i] = hNuclearModification->GetBinContent(i+1)*systematic;
    yrhigh[i] =hNuclearModification->GetBinContent(i+1)*systematic;
  }


  TGraphAsymmErrors* gNuclearModification = new TGraphAsymmErrors(nBins,apt,yr,aptl,aptl,yrlow,yrhigh);
  gNuclearModification->SetName("gNuclearModification");
  gNuclearModification->SetMarkerStyle(20);
  gNuclearModification->SetMarkerSize(0.8);

  TCanvas*canvasRAA=new TCanvas("canvasRAA","canvasRAA",600,600);//550,500
  canvasRAA->cd();
  canvasRAA->SetFillColor(0);
  canvasRAA->SetBorderMode(0);
  canvasRAA->SetBorderSize(2);
  canvasRAA->SetLeftMargin(0.185);//0.200
  canvasRAA->SetRightMargin(0.025);
  canvasRAA->SetTopMargin(0.080);
  canvasRAA->SetBottomMargin(0.150);
  canvasRAA->SetFrameBorderMode(0);
  canvasRAA->SetLogx();

  TH2F* hemptyEff;
  hemptyEff=new TH2F("hemptyEff","",50,0.7,120.,10.,0,1.45);
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("R_{AA}");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.15);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(-0.01);
  hemptyEff->SetMaximum(2);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();
  
  
  hNuclearModification->SetLineWidth(3);
  hNuclearModification->SetMarkerSize(1);
  hNuclearModification->SetMarkerStyle(21);
  hNuclearModification->SetLineColor(1);
  hNuclearModification->SetMarkerColor(1);

  
  gNuclearModification->SetFillColor(5);//1
  gNuclearModification->SetFillStyle(1001);//0 
  gNuclearModification->SetLineWidth(1);//3
  gNuclearModification->SetMarkerSize(1);
  gNuclearModification->SetMarkerStyle(21);
  gNuclearModification->SetLineColor(1);//kGreen+4
  gNuclearModification->SetMarkerColor(1);//kGreen+4
  gNuclearModification->Draw("5same");
  hNuclearModification->Draw("psame");//same

/*
  TLatex* texlumi = new TLatex(0.19,0.936,"25.8 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)");
  texlumi->SetNDC();
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  */
  TLatex* texcms = new TLatex(0.22,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.22,0.84,"Projection");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  TString texper="%";
  //TLatex * tlatexeff2=new TLatex(0.65,0.20,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  TLatex * tlatexeff2=new TLatex(0.52,0.85,Form("Centrality %.0f-%.0f%s",centMin,centMax,texper.Data()));//0.2612903,0.8425793
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextSize(0.043);
  tlatexeff2->SetLineWidth(2);
  tlatexeff2->Draw();

  TLegend *legendSigma=new TLegend(0.3842282,0.5909091,0.6912752,0.701049,"");//0.5100806,0.6268644,0.8084677,0.7805932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);//0.05


  TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(gNuclearModification,"R_{AA} D^{0} mesons, |y|<2.0","pf");
  ent_Dhighpt->SetTextFont(42);
  ent_Dhighpt->SetLineColor(4);
  ent_Dhighpt->SetMarkerColor(4);
  ent_Dhighpt->SetTextSize(0.043);
  legendSigma->Draw();
  
  
    TLegendEntry *entBmesons=legendSigma->AddEntry(gNuclearModification,"R_{AA} B^{+} mesons, |y|<2.4","pf");
  entBmesons->SetTextFont(42);
  entBmesons->SetLineColor(4);
  entBmesons->SetMarkerColor(4);
  entBmesons->SetTextSize(0.043);
  legendSigma->Draw();

  
  TLatex * texlumi=new TLatex(0.52,0.80,"L_{int}=1.5/pb");//0.2612903,0.8425793
  texlumi->SetNDC();
  texlumi->SetTextColor(1);
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.043);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  
  canvasRAA->SaveAs(Form("plotRAA/canvasRAA%s_%.0f_%.0f.pdf",label.Data(),centMin,centMax));
}


int main(int argc, char *argv[])
{
      DRAAUpgrade();
}


