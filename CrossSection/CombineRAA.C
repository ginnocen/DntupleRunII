#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"


void CombineRAA(TString fileMB="ROOTfiles/outputRAAMB.root", TString file="ROOTfiles/outputRAA.root", TString filecharged="/afs/cern.ch/work/g/ginnocen/public/Spectra_March17_evtselCorrData.root" )
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TFile* filePPMB = new TFile(fileMB.Data());  
  TGraphAsymmErrors* gNuclearModificationMB = (TGraphAsymmErrors*)filePPMB->Get("gNuclearModification");
  TH1D* hNuclearModificationMB = (TH1D*)filePPMB->Get("hNuclearModification");

  TFile* filePP = new TFile(file.Data());  
  TGraphAsymmErrors* gNuclearModification = (TGraphAsymmErrors*)filePP->Get("gNuclearModification");
  TH1D* hNuclearModification = (TH1D*)filePP->Get("hNuclearModification");
  
  TFile *fRAA=new TFile(filecharged.Data());
  TH1D*hTrackPt_trkCorr_PbPb_copy1=(TH1D*)fRAA->Get("RAA_0_100");
  

  TCanvas*canvasRAA=new TCanvas("canvasRAA","canvasRAA",500,500);//550,500
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

  TH2F* hemptyEff=new TH2F("hemptyEff","",50,0.7,120.,10.,0,1.45);//50,-2,120.,10.,0,1.5
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("D^{0} R_{AA}");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.15);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.070);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.070);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.060);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.060);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(-0.01);
  hemptyEff->SetMaximum(2);
  hemptyEff->SetMinimum(0.);
  hemptyEff->Draw();

  TLine *line = new TLine(0.7,1,120,1);
  line->SetLineStyle(2);
  line->SetLineWidth(2);
  line->Draw();

  gNuclearModification->SetFillColor(5);//1
  gNuclearModification->SetFillStyle(1001);//0 
  gNuclearModification->SetLineWidth(1);//3
  gNuclearModification->SetLineColor(1);
  gNuclearModification->SetMarkerColor(1);
  gNuclearModification->SetMarkerSize(1);
  gNuclearModification->SetMarkerStyle(21);
  gNuclearModification->Draw("5same");
  gNuclearModificationMB->SetFillColor(5);//1
  gNuclearModificationMB->SetFillStyle(1001);//0 
  gNuclearModificationMB->SetLineWidth(1);//3
  gNuclearModificationMB->SetLineColor(1);
  gNuclearModificationMB->SetMarkerColor(1);
  gNuclearModificationMB->SetMarkerSize(1);
  gNuclearModificationMB->SetMarkerStyle(21);
  gNuclearModificationMB->Draw("5same");

  hNuclearModification->SetLineColor(1);
  hNuclearModification->SetLineWidth(3);
  hNuclearModification->SetMarkerColor(1);
  hNuclearModification->SetMarkerSize(1);
  hNuclearModification->SetMarkerStyle(21);
  hNuclearModification->Draw("psame");//same
  hNuclearModificationMB->SetLineColor(1);
  hNuclearModificationMB->SetLineWidth(3);
  hNuclearModificationMB->SetMarkerColor(1);
  hNuclearModificationMB->SetMarkerSize(1);
  hNuclearModificationMB->SetMarkerStyle(21);
  hNuclearModificationMB->Draw("psame");//same
  
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerColor(2);
  hTrackPt_trkCorr_PbPb_copy1->SetLineColor(2);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerSize(1);
  hTrackPt_trkCorr_PbPb_copy1->SetMarkerStyle(20);  
  hTrackPt_trkCorr_PbPb_copy1->Draw("same");
  hTrackPt_trkCorr_PbPb_copy1->SetLineWidth(3);

  TLatex* texlumi = new TLatex(0.19,0.936,"25.8 pb^{-1} (5.02 TeV pp) + 404 #mub^{-1} (5.02 TeV PbPb)");
  texlumi->SetNDC();
  //texlumi->SetTextAlign(31);
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.038);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  TLatex* texcms = new TLatex(0.22,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.22,0.84,"Preliminary");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();

  TLatex * tlatexeff2=new TLatex(0.65,0.20,"Centrality 0-100%");//0.2612903,0.8425793
  tlatexeff2->SetNDC();
  tlatexeff2->SetTextColor(1);
  tlatexeff2->SetTextFont(42);
  tlatexeff2->SetTextSize(0.04);
  tlatexeff2->SetLineWidth(2);
  tlatexeff2->Draw();

  TLegend *legendSigma=new TLegend(0.50,0.75,0.90,0.90,"");//0.5100806,0.6268644,0.8084677,0.7805932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.04);//0.05

/*
  TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(hNuclearModification,"R_{AA} D triggers.","pf");
  ent_Dhighpt->SetTextFont(42);
  ent_Dhighpt->SetLineColor(1);
  ent_Dhighpt->SetMarkerColor(1);
  ent_Dhighpt->SetTextSize(0.03);

  TLegendEntry *ent_DMB=legendSigma->AddEntry(hNuclearModificationMB,"R_{AA} D MB.","pf");
  ent_DMB->SetTextFont(42);
  ent_DMB->SetLineColor(1);
  ent_DMB->SetMarkerColor(1);
  ent_DMB->SetTextSize(0.03);
  */

  TLegendEntry *ent_Dhighpt=legendSigma->AddEntry(gNuclearModification,"R_{AA} D^{0}","pf");
  ent_Dhighpt->SetTextFont(42);
  ent_Dhighpt->SetLineColor(4);
  ent_Dhighpt->SetMarkerColor(4);
  ent_Dhighpt->SetTextSize(0.04);

  TLegendEntry *ent_Charged=legendSigma->AddEntry(hTrackPt_trkCorr_PbPb_copy1,"R_{AA} charged hadrons.","pl");//pf
  ent_Charged->SetTextFont(42);
  ent_Charged->SetLineColor(1);
  ent_Charged->SetMarkerColor(1);
  ent_Charged->SetTextSize(0.04);//0.03
  
  legendSigma->Draw();
  canvasRAA->SaveAs("canvasRAAComparison.pdf");
  canvasRAA->SaveAs("canvasRAAComparison.png");

  }

int main(int argc, char *argv[])
{
  if((argc != 4))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }

  if(argc ==4)
    CombineRAA(argv[1], argv[2],argv[3]);
  return 0;
}



