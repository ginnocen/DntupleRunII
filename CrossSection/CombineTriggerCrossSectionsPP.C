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
  gPad->SetLogy();
  gPad->SetLogx();
  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,3,100.,10.,0.001,5);
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
  TH2F* hemptyRatioCounting=new TH2F("hemptyRatioCounting","",50,3,100.,10.,0.001,5);
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
  ratioHLT30_50->SetMaximum(100);

  TH1D* ratioHLT15_30=(TH1D*)hDcandidatesTriggerCorrectedFONLLnorm[2]->Clone("ratioHLT15_30");
  ratioHLT15_30->Divide(hDcandidatesTriggerCorrectedFONLLnorm[3]);
  ratioHLT15_30->SetMaximum(100);

  TH1D* ratioHLT8_15=(TH1D*)hDcandidatesTriggerCorrectedFONLLnorm[1]->Clone("ratioHLT8_15");
  ratioHLT8_15->Divide(hDcandidatesTriggerCorrectedFONLLnorm[2]);
  ratioHLT8_15->SetMaximum(100);
  
  TCanvas*canvasPrescale=new TCanvas("canvasPrescale","canvasPrescale",1500,500);
  canvasPrescale->Divide(3,1);
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
  TLatex *  tex_0 = new TLatex(1.82,1.836,Form("Ratio= %f #pm %f",pol0_0->GetParameter(0),pol0_0->GetParError(0)));
  tex_0->Draw();
  canvasPrescale->cd(2);
  hemptyPrescale->Draw();
  ratioHLT15_30->SetLineColor(1);
  ratioHLT15_30->Draw("same");
  TF1 *pol0_1= new TF1("pol0_1","pol0_1",30,50);
  ratioHLT15_30->Fit("pol0_1","","",30,50);
  TLatex *  tex_1 = new TLatex(1.82,1.836,Form("Ratio= %f #pm %f",pol0_1->GetParameter(0),pol0_1->GetParError(0)));
  tex_1->Draw();
  canvasPrescale->cd(3);
  hemptyPrescale->Draw();
  ratioHLT30_50->SetLineColor(1);
  ratioHLT30_50->Draw("same");
  TF1 *pol0_2;
  pol0_2= new TF1("pol0_2","pol0_2",20,30);
  ratioHLT30_50->Fit("pol0_2","","",50,80);
  TLatex *  tex_2 = new TLatex(1.82,1.836,Form("Ratio= %f #pm %f",pol0_2->GetParameter(0),pol0_2->GetParError(0)));
  tex_2->Draw();
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
  canvasLumi->cd(2);
  hemptyLumi->Draw();
  hRatioMBOverTriggeredDcand->Draw("same");
  hRatioMBOverTriggeredDcand->Fit("pol0","","",10,25);
  canvasLumi->SaveAs("canvasLumiPP.pdf");

}
