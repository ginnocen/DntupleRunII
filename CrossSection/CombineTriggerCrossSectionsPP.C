#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"
#include "../Systematics/systematics.C"

double lumiPP=25.8;
double lumiPPMB=0.0361128;

void CombineTriggerCrossSectionsPP(bool isLumiNorm=true)
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
  TString label[nFiles] = {"MB", "HLTD8", "HLTD15", "HLTD30","HLTD50"};

  int colors[nFiles] = {1,2,3,4,6};

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
    if(isLumiNorm&&ifile==0) {
      hYieldTriggerCorrected[ifile]->Scale(1/lumiPPMB);
      hYieldTriggerCorrectedFONLLnorm[ifile]->Scale(1/lumiPPMB);
      hDcandidatesTriggerCorrectedFONLLnorm[ifile]->Scale(1/lumiPPMB);
    }
    if(isLumiNorm&&ifile>0) {
      hYieldTriggerCorrected[ifile]->Scale(1/lumiPP);
      hYieldTriggerCorrectedFONLLnorm[ifile]->Scale(1/lumiPP);
      hDcandidatesTriggerCorrectedFONLLnorm[ifile]->Scale(1/lumiPP);
    }
  }
    
  TCanvas* cSigmaAll = new TCanvas("cSigmaAll","",1000,500);
  cSigmaAll->cd(1);
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptySigma=new TH2F("hemptySigma","",50,0.,110.,10.,1e-3,1.e12);  
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
  gPad->SetLogx();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,3,100.,10.,0.,0.2);
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
  gPad->SetLogx();
  TH2F* hemptyRatioCounting=new TH2F("hemptyRatioCounting","",50,3,100.,10.,0.,0.2);
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

  TH1D* ratioHLT30_50=(TH1D*)hDcandidatesTriggerCorrectedFONLLnorm[3]->Clone("ratioHLT30_50");
  ratioHLT30_50->Divide(hDcandidatesTriggerCorrectedFONLLnorm[4]);

  TH1D* ratioHLT15_30=(TH1D*)hDcandidatesTriggerCorrectedFONLLnorm[2]->Clone("ratioHLT15_30");
  ratioHLT15_30->Divide(hDcandidatesTriggerCorrectedFONLLnorm[3]);

  TH1D* ratioHLT8_15=(TH1D*)hDcandidatesTriggerCorrectedFONLLnorm[1]->Clone("ratioHLT8_15");
  ratioHLT8_15->Divide(hDcandidatesTriggerCorrectedFONLLnorm[2]);
  
  TH1D* ratioHLT15_50=(TH1D*)hDcandidatesTriggerCorrectedFONLLnorm[2]->Clone("ratioHLT15_50");
  ratioHLT15_50->Divide(hDcandidatesTriggerCorrectedFONLLnorm[4]);
  
  TCanvas*canvasPrescale=new TCanvas("canvasPrescale","canvasPrescale",1000,1000);
  canvasPrescale->Divide(2,2);
  TH2F* hemptyPrescale=new TH2F("hemptyPrescale","",50,0,100,10.,0,2.); 
  hemptyPrescale->GetXaxis()->CenterTitle();
  hemptyPrescale->GetYaxis()->CenterTitle();
  hemptyPrescale->GetYaxis()->SetTitle("Data driven prescale / HLT prescales");
  hemptyPrescale->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyPrescale->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyPrescale->GetYaxis()->SetTitleOffset(1.24);//1.
  hemptyPrescale->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyPrescale->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyPrescale->GetXaxis()->SetTitleFont(42);
  hemptyPrescale->GetYaxis()->SetTitleFont(42);
  hemptyPrescale->GetXaxis()->SetLabelFont(42);
  hemptyPrescale->GetYaxis()->SetLabelFont(42);
  hemptyPrescale->GetXaxis()->SetLabelSize(0.040);//0.035
  hemptyPrescale->GetYaxis()->SetLabelSize(0.040);//0.035  
  hemptyPrescale->GetXaxis()->SetLabelOffset(0.01);
  canvasPrescale->cd(1);
 // gPad->SetLogy();
  hemptyPrescale->Draw();
  ratioHLT8_15->SetLineColor(1);
  ratioHLT8_15->Draw("same");
  TF1 *pol0_0= new TF1("pol0_0","pol0_0",20,30);
  ratioHLT8_15->Fit("pol0_0","","",20,30);
  TLatex *  tex_0 = new TLatex(1.82,1.836,Form("Ratio(HLT8/HLT15)= %f #pm %f",pol0_0->GetParameter(0),pol0_0->GetParError(0)));
  tex_0->SetTextSize(0.04);
  tex_0->Draw();
  canvasPrescale->cd(2);
  hemptyPrescale->Draw();
  ratioHLT15_30->SetLineColor(1);
  ratioHLT15_30->Draw("same");
  TF1 *pol0_1= new TF1("pol0_1","pol0_1",30,50);
  ratioHLT15_30->Fit("pol0_1","","",30,50);
  TLatex *  tex_1 = new TLatex(1.82,1.836,Form("Ratio(HLT15/HLT30)= %f #pm %f",pol0_1->GetParameter(0),pol0_1->GetParError(0)));
  tex_1->SetTextSize(0.04);
  tex_1->Draw();
  canvasPrescale->cd(3);
  hemptyPrescale->Draw();
  ratioHLT30_50->SetLineColor(1);
  ratioHLT30_50->Draw("same");
  TF1 *pol0_2;
  pol0_2= new TF1("pol0_2","pol0_2",20,30);
  ratioHLT30_50->Fit("pol0_2","","",50,80);
  TLatex *  tex_2 = new TLatex(1.82,1.836,Form("Ratio(HLT30/HLT50)= %f #pm %f",pol0_2->GetParameter(0),pol0_2->GetParError(0)));
  tex_2->SetTextSize(0.04);
  tex_2->Draw();
  canvasPrescale->cd(4);
  hemptyPrescale->Draw();
  ratioHLT15_50->SetLineColor(1);
  ratioHLT15_50->Draw("same");
  TF1 *pol0_3;
  pol0_3= new TF1("pol0_3","pol0_3",20,30);
  ratioHLT15_50->Fit("pol0_3","","",50,80);
  TLatex *  tex_3 = new TLatex(1.82,1.836,Form("Ratio(HLT15/HLT50)= %f #pm %f",pol0_3->GetParameter(0),pol0_3->GetParError(0)));
  tex_3->SetTextSize(0.04);
  tex_3->Draw();
  canvasPrescale->SaveAs("canvasPrescaleDataDrivenPP.pdf");


  const int nbinsstudy=3;
  double binsstudy[nbinsstudy+1]={10.,15.,20.,25.};
  double binmedium[nbinsstudy]={12.5,17.5,22.5};
    
  TH1D* hValuesMB = new TH1D("hValuesMB","",nbinsstudy,binsstudy);
  TH1D* hValuesD8 = new TH1D("hValuesD8","",nbinsstudy,binsstudy);
  TH1D* hDcandValuesMB = new TH1D("hDcandValuesMB","",nbinsstudy,binsstudy);
  TH1D* hDcandValuesD8 = new TH1D("hDcandValuesD8","",nbinsstudy,binsstudy);


  for (int i=0;i<nbinsstudy;i++){

    double valueMB=hYieldTriggerCorrected[0]->GetBinContent(hYieldTriggerCorrected[0]->FindBin(binmedium[i]));
    double errvalueMB=hYieldTriggerCorrected[0]->GetBinError(hYieldTriggerCorrected[0]->FindBin(binmedium[i]));
    double valueD8=hYieldTriggerCorrected[1]->GetBinContent(hYieldTriggerCorrected[1]->FindBin(binmedium[i]));
    double errvalueD8=hYieldTriggerCorrected[1]->GetBinError(hYieldTriggerCorrected[1]->FindBin(binmedium[i]));
    
    double DcandvalueMB=hDcandidatesTriggerCorrectedFONLLnorm[0]->GetBinContent(hDcandidatesTriggerCorrectedFONLLnorm[0]->FindBin(binmedium[i]));
    double DcanderrvalueMB=hDcandidatesTriggerCorrectedFONLLnorm[0]->GetBinError(hDcandidatesTriggerCorrectedFONLLnorm[0]->FindBin(binmedium[i]));
    double DcandvalueD8=hDcandidatesTriggerCorrectedFONLLnorm[1]->GetBinContent(hDcandidatesTriggerCorrectedFONLLnorm[1]->FindBin(binmedium[i]));
    double DcanderrvalueD8=hDcandidatesTriggerCorrectedFONLLnorm[1]->GetBinError(hDcandidatesTriggerCorrectedFONLLnorm[1]->FindBin(binmedium[i]));

    hValuesMB->SetBinContent(i+1,valueMB);
    hValuesMB->SetBinError(i+1,errvalueMB);
    hValuesD8->SetBinContent(i+1,valueD8);
    hValuesD8->SetBinError(i+1,errvalueD8);
    
    hDcandValuesMB->SetBinContent(i+1,DcandvalueMB);
    hDcandValuesMB->SetBinError(i+1,DcanderrvalueMB);
    hDcandValuesD8->SetBinContent(i+1,DcandvalueD8);
    hDcandValuesD8->SetBinError(i+1,DcanderrvalueD8);
    
  }
  
  hValuesD8->Sumw2();
  hValuesMB->Sumw2();
  
  TH1D* hRatioMBOverTriggered = (TH1D*)hValuesMB->Clone("hRatioMBOverTriggered");
  hRatioMBOverTriggered->Divide(hValuesD8);
  hRatioMBOverTriggered->Scale(25.8);  
  
  TH1D* hRatioMBOverTriggeredDcand = (TH1D*)hDcandValuesMB->Clone("hRatioMBOverTriggeredDcand");
  hRatioMBOverTriggeredDcand->Divide(hDcandValuesD8);
  hRatioMBOverTriggeredDcand->Scale(25.8);  

  
  for (int i=1;i<nbinsstudy+1;i++) cout<<"luminosity="<<hRatioMBOverTriggered->GetBinContent(i)<<"with error="<<hRatioMBOverTriggered->GetBinError(i)<<endl;
  for (int i=1;i<nbinsstudy+1;i++) cout<<"luminosity D cand="<<hRatioMBOverTriggeredDcand->GetBinContent(i)<<"with error="<<hRatioMBOverTriggeredDcand->GetBinError(i)<<endl;

  TCanvas*canvasLumi=new TCanvas("canvasLumi","canvasLumi",1000,500);
  canvasLumi->Divide(2,1);
  canvasLumi->cd(1);
  TH2F* hemptyLumi=new TH2F("hemptyLumi","",50,5,30,10.,0,0.10); 
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
  hRatioMBOverTriggered->Draw("same");
  hRatioMBOverTriggered->Fit("pol0","","",10,25);
  TF1 *pol0_yield = hRatioMBOverTriggered->GetFunction("pol0");
  TLatex *  tex_yield = new TLatex(10.82,0.07,Form("Lumi= %f #pm %f",pol0_yield->GetParameter(0),pol0_yield->GetParError(0)));
  tex_yield->SetTextSize(0.04);
  tex_yield->Draw();
  canvasLumi->cd(2);
  hemptyLumi->Draw();
  hRatioMBOverTriggeredDcand->Draw("same");
  hRatioMBOverTriggeredDcand->Fit("pol0","","",10,25);
  TF1 *pol0_cand = hRatioMBOverTriggeredDcand->GetFunction("pol0");
  TLatex *  tex_cand = new TLatex(10.82,0.07,Form("Lumi= %f #pm %f",pol0_cand->GetParameter(0),pol0_cand->GetParError(0)));
  tex_cand->SetTextSize(0.04);
  tex_cand->Draw();
  canvasLumi->SaveAs("canvasLumiPP.pdf");

}


void ComparisonTriggerPP()
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

  TH1D* hYieldTriggerCorrectedFONLLnorm[nFiles];
  TH1D* hDcandidatesTriggerCorrectedFONLLnorm[nFiles];
  TFile* files[nFiles];
  TLegendEntry *entry[nFiles];
  
  for (int ifile=0;ifile<nFiles;ifile++){
    files[ifile]=new TFile(myfiles[ifile].Data());  
    hYieldTriggerCorrectedFONLLnorm[ifile] = (TH1D*)files[ifile]->Get("hYieldTriggerCorrectedFONLLnorm");
    hDcandidatesTriggerCorrectedFONLLnorm[ifile] = (TH1D*)files[ifile]->Get("hDcandidatesTriggerCorrectedFONLLnorm");
    if(ifile==0) {
      hYieldTriggerCorrectedFONLLnorm[ifile]->Scale(1/lumiPPMB);
      hDcandidatesTriggerCorrectedFONLLnorm[ifile]->Scale(1/lumiPPMB);
    }
    if(ifile>0) {
      hYieldTriggerCorrectedFONLLnorm[ifile]->Scale(1/lumiPP);
      hDcandidatesTriggerCorrectedFONLLnorm[ifile]->Scale(1/lumiPP);
    }
  }

  const int binstotal=9;
  double ptBinsTotal[binstotal+1] = {10.,15.,20.,25,30.,40.,50.,60.,80,100};
  double ptBinsTotalCenter[binstotal] = {12.5,17.5,22.5,27.5,35.,45.,55.,70.,90};
  
  int assignment[binstotal]={0,0,2,2,2,3,3,4,4};
  TH1D* hDcandidates=new TH1D("hDcandidates","hDcandidates",binstotal,ptBinsTotal);
  TH1D* hYieldTrigger=new TH1D("hYieldTrigger","hYieldTrigger",binstotal,ptBinsTotal);
  
  for (int i=0;i<binstotal;i++){
    hDcandidates->SetBinContent(i+1,hDcandidatesTriggerCorrectedFONLLnorm[assignment[i]]->GetBinContent(hDcandidatesTriggerCorrectedFONLLnorm[assignment[i]]->FindBin(ptBinsTotalCenter[i])));
    hYieldTrigger->SetBinContent(i+1,hYieldTriggerCorrectedFONLLnorm[assignment[i]]->GetBinContent(hYieldTriggerCorrectedFONLLnorm[assignment[i]]->FindBin(ptBinsTotalCenter[i])));
    hDcandidates->SetBinError(i+1,hDcandidatesTriggerCorrectedFONLLnorm[assignment[i]]->GetBinError(hDcandidatesTriggerCorrectedFONLLnorm[assignment[i]]->FindBin(ptBinsTotalCenter[i])));
    hYieldTrigger->SetBinError(i+1,hYieldTriggerCorrectedFONLLnorm[assignment[i]]->GetBinError(hYieldTriggerCorrectedFONLLnorm[assignment[i]]->FindBin(ptBinsTotalCenter[i])));
  }
  
  
  for (int ifile=0;ifile<nFiles;ifile++){
     hYieldTriggerCorrectedFONLLnorm[ifile]->Divide(hYieldTrigger);
     hDcandidatesTriggerCorrectedFONLLnorm[ifile]->Divide(hDcandidates);
  }
  
  
  TLine *line20 = new TLine(20,0,20,2);
  TLine *line40 = new TLine(40,0,40,2);
  TLine *line60 = new TLine(60,0,60,2);
  line20->SetLineWidth(3);
  line40->SetLineWidth(3);
  line60->SetLineWidth(3);
  
  line20->SetLineStyle(2);
  line40->SetLineStyle(2);
  line60->SetLineStyle(2);
  
  TLegend *legendSigma=new TLegend(0.311747,0.6945694,0.6401439,0.8740055,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  legendSigma->SetTextSize(0.045);

      
  for (int ifile=0;ifile<nFiles;ifile++){
    hYieldTriggerCorrectedFONLLnorm[ifile] ->SetLineColor(colors[ifile]);
    hYieldTriggerCorrectedFONLLnorm[ifile] ->SetLineWidth(3);
    hYieldTriggerCorrectedFONLLnorm[ifile] ->SetMarkerColor(colors[ifile]);
    hYieldTriggerCorrectedFONLLnorm[ifile] ->Draw("same");  
    entry[ifile]=legendSigma->AddEntry(hYieldTriggerCorrectedFONLLnorm[ifile],label[ifile].Data(),"f");
    entry[ifile]->SetTextFont(42);
    entry[ifile]->SetLineColor(colors[ifile]);
    entry[ifile]->SetMarkerColor(colors[ifile]);
  }


  TCanvas* cSigma = new TCanvas("cSigma","",1000,500);
  cSigma->Divide(2,1);
  cSigma->cd(1);
  gPad->SetLogx();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,3,100.,10.,0.,3);
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
  
  line20->Draw();
  line40->Draw();
  line60->Draw();
  
  
  legendSigma->Draw("same");

  cSigma->cd(2);
  gPad->SetLogx();
  TH2F* hemptyRatioCounting=new TH2F("hemptyRatioCounting","",50,3,100.,10.,0.,3);
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
  line20->Draw();
  line40->Draw();
  line60->Draw();
  cSigma->SaveAs("TriggerCrossSectionRatioPbPb.pdf");

}
