using namespace std;
#include "uti.h"

TH1D* hD0DcaMCPSignal;
TH1D* hD0DcaMCNPSignal;

Double_t funMix(Double_t* x_, Double_t* para);
Double_t funNonPrompt(Double_t* x_, Double_t* para);
void RandomSmear(TH1D* h0, TH1D* h);
void normalize(TH1D* h);
void setColorTitleLabel(TH1* h, int color=1);
TF1* fitMass(TH1D* hData, TH1D* hMCSignal, TH1D* hMCSwapped);

void bFeedDownFraction()
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.04);
  gStyle->SetPadLeftMargin(0.14);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.14);
  gStyle->SetTitleX(.0f);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TCanvas* c4 = new TCanvas("c4","",800,600);
  c4->Divide(2,2);
   
  TCanvas* c2 = new TCanvas("c2","",400,600);
  c2->Divide(1,2);

  TCanvas* c1 = new TCanvas();

  TCanvas* c15 = new TCanvas("c15","",810,1000);
  c15->Divide(3,5);

  TFile* fPbPb = new TFile("bFeedDownPbPb.hist.root");
  TFile* fPbPbMB = new TFile("bFeedDownPbPbMB.hist.root");
  TFile* fPbPbMC = new TFile("bFeedDownPbPbMC.hist.root");
  TFile* fPbPbMBMC = new TFile("bFeedDownPbPbMBMC.hist.root");

  TH3D* hDataPbPb = (TH3D*)fPbPb->Get("hData");
  TH3D* hSidebandPbPb = (TH3D*)fPbPb->Get("hSideband");
  TH3D* hDataPbPbMB = (TH3D*)fPbPbMB->Get("hData");
  TH3D* hSidebandPbPbMB = (TH3D*)fPbPbMB->Get("hSideband");
  TH3D* hPtMD0DcaPbPb = (TH3D*)fPbPb->Get("hPtMD0Dca");
  TH3D* hPtMD0DcaPbPbMB = (TH3D*)fPbPbMB->Get("hPtMD0Dca");

  TH3D* hMCPSignalPbPb = (TH3D*)fPbPbMC->Get("hMCPSignal");
  TH3D* hMCNPSignalPbPb = (TH3D*)fPbPbMC->Get("hMCNPSignal");
  TH3D* hMCPSignalPbPbMB = (TH3D*)fPbPbMBMC->Get("hMCPSignal");
  TH3D* hMCNPSignalPbPbMB = (TH3D*)fPbPbMBMC->Get("hMCNPSignal");
  TH3D* hPtMD0DcaMCPSignalPbPb = (TH3D*)fPbPbMC->Get("hPtMD0DcaMCPSignal");
  TH3D* hPtMD0DcaMCPSwappedPbPb = (TH3D*)fPbPbMC->Get("hPtMD0DcaMCPSwapped");
  TH3D* hPtMD0DcaMCPSignalPbPbMB =(TH3D*)fPbPbMBMC->Get("hPtMD0DcaMCPSignal");
  TH3D* hPtMD0DcaMCPSwappedPbPbMB = (TH3D*)fPbPbMBMC->Get("hPtMD0DcaMCPSwapped");

  TH3D* hData = (TH3D*)hDataPbPb->Clone("hData");
  hData->Sumw2();
  hData->Add(hDataPbPbMB);

  TH3D* hSideband = (TH3D*)hSidebandPbPb->Clone("hSideband");
  hSideband->Sumw2();
  hSideband->Add(hSidebandPbPbMB);

  TH3D* hPtMD0Dca = (TH3D*)hPtMD0DcaPbPb->Clone("hPtMD0Dca");
  hPtMD0Dca->Sumw2();
  hPtMD0Dca->Add(hPtMD0DcaPbPbMB);

  TH3D* hMCPSignal = (TH3D*)hMCPSignalPbPb->Clone("hMCPSignal");
  hMCPSignal->Sumw2();
  hMCPSignal->Add(hMCPSignalPbPbMB);

  TH3D* hMCNPSignal = (TH3D*)hMCNPSignalPbPb->Clone("hMCNPSignal");
  hMCNPSignal->Sumw2();
  hMCNPSignal->Add(hMCNPSignalPbPbMB);

  TH3D* hPtMD0DcaMCPSignal = (TH3D*)hPtMD0DcaMCPSignalPbPb->Clone("hPtMD0DcaMCPSignal");
  hPtMD0DcaMCPSignal->Sumw2();
  hPtMD0DcaMCPSignal->Add(hPtMD0DcaMCPSignalPbPbMB);

  TH3D* hPtMD0DcaMCPSwapped =(TH3D*)hPtMD0DcaMCPSwappedPbPb->Clone("hPtMD0DcaMCPSwapped");
  hPtMD0DcaMCPSwapped->Sumw2();
  hPtMD0DcaMCPSwapped->Add(hPtMD0DcaMCPSwappedPbPbMB);

  TLatex* texCms = new TLatex(0.18,0.93, "#scale[1.25]{CMS} Preliminary");
  texCms->SetNDC();
  texCms->SetTextAlign(12);
  texCms->SetTextSize(0.06);
  texCms->SetTextFont(42);

  TLatex* texCol = new TLatex(0.96,0.93, "PbPb #sqrt{s_{NN}} = 5.02 TeV");
  texCol->SetNDC();
  texCol->SetTextAlign(32);
  texCol->SetTextSize(0.06);
  texCol->SetTextFont(42);

  const int nPtBins = 13;
  float ptBins[nPtBins+1] = {2.,4.,5.,6.,8.,10.,12.5,15.0,20.,25.,30.,40.,60.,100};

  float pts[nPtBins];
  float promptFraction[nPtBins];
  float promptFractionError[nPtBins];
  float promptFractionErrorDataOnly[nPtBins];
  float totalYield[nPtBins];
  float totalYieldError[nPtBins];
  float bToDYield[nPtBins];
  float bToDYieldError[nPtBins];

  const int nBinY = 14;
  Float_t binsY[nBinY+1];
  float firstBinYWidth = 0.001;
  float binYWidthRatio = 1.27;
  binsY[0]=0;
  for(int i=1; i<=nBinY; i++)
    binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
  cout<<"last y bin: "<<binsY[nBinY]<<endl;


  for(int i=1; i<=nPtBins; i++)
    {
      pts[i-1] = 0.5*(ptBins[i-1]+ptBins[i]);
      float ptLow = ptBins[i-1];
      float ptHigh = ptBins[i];
      cout<<endl<<"======================================="<<endl;
      cout<<"pT range: "<<ptLow<<" "<<ptHigh<<endl;

      TLatex* texPtY = new TLatex(0.32,0.82,Form("%.1f < p_{T} < %.1f GeV/c      |y| < 1.0",ptLow,ptHigh));
      texPtY->SetNDC();
      texPtY->SetTextFont(42);
      texPtY->SetTextSize(0.06);
      texPtY->SetLineWidth(2);

      TLatex* texPt = new TLatex(0.18,0.82,Form("%.1f < p_{T} < %.1f GeV/c",ptLow,ptHigh));
      texPt->SetNDC();
      texPt->SetTextFont(42);
      texPt->SetTextSize(0.06);
      texPt->SetLineWidth(2);

      TLatex* texY = new TLatex(0.18,0.74,Form("|y| < 1.0"));
      texY->SetNDC();
      texY->SetTextFont(42);
      texY->SetTextSize(0.06);
      texY->SetLineWidth(2);

      c2->cd(1);

      hPtMD0Dca->GetZaxis()->SetRange(1,100);
      hPtMD0Dca->GetXaxis()->SetRangeUser(ptLow+0.001,ptHigh-0.001);
      hPtMD0DcaMCPSignal->GetXaxis()->SetRangeUser(ptLow+0.001,ptHigh-0.001);
      hPtMD0DcaMCPSwapped->GetXaxis()->SetRangeUser(ptLow+0.001,ptHigh-0.001);
      TH1D* hMData = (TH1D*)hPtMD0Dca->Project3D("y")->Clone(Form("hM_%1.1f_%1.1f", ptLow, ptHigh));
      TH1D* hMMCSignal = (TH1D*)hPtMD0DcaMCPSignal->Project3D("y");
      TH1D* hMMCSwapped = (TH1D*)hPtMD0DcaMCPSwapped->Project3D("y");

      setColorTitleLabel(hMData);
      TF1* fMass = fitMass(hMData, hMMCSignal, hMMCSwapped);

      texCms->Draw();
      texCol->Draw();
      texPt->Draw();
      texY->Draw();
      
      TF1* background = new TF1("fBackground","[0]+[1]*x+[2]*x*x+[3]*x*x*x");
      background->SetParameter(0,fMass->GetParameter(3));
      background->SetParameter(1,fMass->GetParameter(4));
      background->SetParameter(2,fMass->GetParameter(5));
      background->SetParameter(3,fMass->GetParameter(6));

      float massD = 1.8649;
      float massSignal1 = massD-0.025;
      float massSignal2 = massD+0.025;
      float massSideBand1 = massD-0.1;
      float massSideBand2 = massD-0.075;
      float massSideBand3 = massD+0.075;
      float massSideBand4 = massD+0.1;

      float scaleSideBand = background->Integral(massSignal1, massSignal2)/(background->Integral(massSideBand1, massSideBand2)+background->Integral(massSideBand3, massSideBand4));
      cout<<"scaleSideBand: "<<scaleSideBand<<endl;

      TLatex* texScale = new TLatex(0.18,0.66,Form("side band scale: %1.3f", scaleSideBand));
      texScale->SetNDC();
      texScale->SetTextFont(42);
      texScale->SetTextSize(0.06);
      texScale->SetLineWidth(2);
      texScale->Draw();

      TLine* lineSignal1 = new TLine(massSignal1, 0, massSignal1, hMData->GetMaximum()*0.5);
      TLine* lineSignal2 = new TLine(massSignal2, 0, massSignal2, hMData->GetMaximum()*0.5);
      TLine* lineSideBand1 = new TLine(massSideBand1, 0, massSideBand1, hMData->GetMaximum()*0.5);
      TLine* lineSideBand2 = new TLine(massSideBand2, 0, massSideBand2, hMData->GetMaximum()*0.5);
      TLine* lineSideBand3 = new TLine(massSideBand3, 0, massSideBand3, hMData->GetMaximum()*0.5);
      TLine* lineSideBand4 = new TLine(massSideBand4, 0, massSideBand4, hMData->GetMaximum()*0.5);
      lineSignal1->Draw();
      lineSignal2->Draw();
      lineSideBand1->Draw();
      lineSideBand2->Draw();
      lineSideBand3->Draw();
      lineSideBand4->Draw();

      c2->cd(2);
      gPad->SetLogy();

      hData->GetXaxis()->SetRangeUser(ptLow+0.001,ptHigh-0.001);
      hSideband->GetXaxis()->SetRangeUser(ptLow+0.001,ptHigh-0.001);
      hMCPSignal->GetXaxis()->SetRangeUser(ptLow+0.001,ptHigh-0.001);
      hMCNPSignal->GetXaxis()->SetRangeUser(ptLow+0.001,ptHigh-0.001);

      TH1D* hD0DcaData0 = (TH1D*)hData->Project3D("y")->Clone("hD0DcaData0");
      TH1D* hD0DcaSideband = (TH1D*)hSideband->Project3D("y")->Clone("hD0DcaSideband");
      TH1D* hD0DcaMCPSignal0 = (TH1D*)hMCPSignal->Project3D("y")->Clone("hD0DcaMCPSignal0");
      TH1D* hD0DcaMCNPSignal0 = (TH1D*)hMCNPSignal->Project3D("y")->Clone("hD0DcaMCNPSignal0");

      hD0DcaMCPSignal = hD0DcaMCPSignal0;
      hD0DcaMCNPSignal = hD0DcaMCNPSignal0;

      divideBinWidth(hD0DcaData0);
      divideBinWidth(hD0DcaSideband);
      setColorTitleLabel(hD0DcaData0, 1);
      hD0DcaData0->GetXaxis()->SetRangeUser(0,0.1);
      hD0DcaData0->GetYaxis()->SetTitle("counts per cm");

      TH1D* hD0DcaSideband0 = (TH1D*)hD0DcaSideband->Clone("hD0DcaSideband0");
      hD0DcaSideband->Scale(scaleSideBand);

      TH1D* hD0DcaDataSubSideBand = (TH1D*)hD0DcaData0->Clone("hD0DcaDataSubSideBand");
      hD0DcaDataSubSideBand->Add(hD0DcaSideband,-1);

      hD0DcaData0->SetMarkerSize(0.6);
      hD0DcaData0->Draw();
      hD0DcaSideband->Draw("hsame");
      hD0DcaSideband0->SetLineStyle(2);
      hD0DcaSideband0->Draw("hsame");

      TLegend* leg1 = new TLegend(0.44,0.6,0.90,0.76,NULL,"brNDC");
      leg1->SetBorderSize(0);
      leg1->SetTextSize(0.06);
      leg1->SetTextFont(42);
      leg1->SetFillStyle(0);
      leg1->AddEntry(hD0DcaData0,"D^{0} candidate","pl");
      leg1->AddEntry(hD0DcaSideband,"side band","l");
      leg1->AddEntry(hD0DcaSideband0,"side band unscaled","l");
      leg1->Draw("same");

      texCms->Draw();
      texCol->Draw();
      texPtY->Draw();

      c2->SaveAs(Form("plots/PbPb_%.0f_%.0f_sideBand.pdf",ptLow,ptHigh));

      c15->cd(1);
      
      fitMass(hMData, hMMCSignal, hMMCSwapped);

      texPt->Draw();
      texY->Draw();

      TH1D* hD0DcaDataFit = new TH1D("hD0DcaDataFit", ";D^{0} DCA (cm);yield per cm", nBinY, binsY);

      for(int j=1; j<=14; j++)
	{
	  c15->cd(j+1);
	  hPtMD0Dca->GetZaxis()->SetRange(j,j);
          float D0DcaLow = hPtMD0Dca->GetZaxis()->GetBinLowEdge(j);
	  float D0DcaHigh = hPtMD0Dca->GetZaxis()->GetBinUpEdge(j);
	  TH1D* hMData_D0Dca = (TH1D*)hPtMD0Dca->Project3D("y")->Clone(Form("hM_pt_%1.1f_%1.1f_D0Dca_%1.4f_%1.4f", ptLow, ptHigh, D0DcaLow, D0DcaHigh));
	  setColorTitleLabel(hMData_D0Dca);
	  fMass = fitMass(hMData_D0Dca, hMMCSignal, hMMCSwapped);

	  float yield = fMass->GetParameter(0)*fMass->GetParameter(7)/hMData_D0Dca->GetBinWidth(1);
	  float yieldError = fMass->GetParError(0)*fMass->GetParameter(7)/hMData_D0Dca->GetBinWidth(1);

	  hD0DcaDataFit->SetBinContent(j, yield);
	  hD0DcaDataFit->SetBinError(j, yieldError);

	  TLatex* texD0Dca = new TLatex(0.18,0.82,Form("D^{0} DCA: %1.4f - %1.4f",D0DcaLow,D0DcaHigh));
	  texD0Dca->SetNDC();
	  texD0Dca->SetTextFont(42);
	  texD0Dca->SetTextSize(0.06);
	  texD0Dca->SetLineWidth(2);
	  texD0Dca->Draw();

          TLatex* texYield = new TLatex(0.18,0.74,Form("D^{0} yield: %1.0f #pm %1.0f",yield,yieldError));
          texYield->SetNDC();
          texYield->SetTextFont(42);
          texYield->SetTextSize(0.06);
          texYield->SetLineWidth(2);
          texYield->Draw();

	}

      c15->SaveAs(Form("plots/PbPb_%.0f_%.0f_invMassFit.pdf",ptLow,ptHigh));

      divideBinWidth(hD0DcaDataFit);

      c4->cd(1);
      gPad->SetLogy();
 
      normalize(hD0DcaMCPSignal);
      setColorTitleLabel(hD0DcaMCPSignal, 2);
      hD0DcaMCPSignal->GetXaxis()->SetRangeUser(0,0.1);
      hD0DcaMCPSignal->GetYaxis()->SetTitle("normalized counts per cm");
   
      normalize(hD0DcaMCNPSignal);
      setColorTitleLabel(hD0DcaMCNPSignal, 4);
      hD0DcaMCNPSignal->GetXaxis()->SetRangeUser(0,0.1);
      hD0DcaMCNPSignal->GetYaxis()->SetTitle("normalized counts per cm");
      hD0DcaMCNPSignal->SetMaximum(hD0DcaMCPSignal->GetMaximum()*3.);

      hD0DcaMCNPSignal->Draw("");
      hD0DcaMCPSignal->Draw("same");

      TLegend* leg2 = new TLegend(0.54,0.72,0.90,0.88,NULL,"brNDC");
      leg2->SetBorderSize(0);
      leg2->SetTextSize(0.06);
      leg2->SetTextFont(42);
      leg2->SetFillStyle(0);
      leg2->AddEntry(hD0DcaMCPSignal,"MC Prompt D^{0}","pl");
      leg2->AddEntry(hD0DcaMCNPSignal,"MC Non-prompt D^{0}","pl");
      leg2->Draw("same");

      c4->cd(2);
      gPad->SetLogy();
      
      TH1D* hD0DcaData = hD0DcaDataFit;
      if(pts[i-1]>20) hD0DcaData = hD0DcaDataSubSideBand;

      setColorTitleLabel(hD0DcaData, 1);

      double integralTotalYield = hD0DcaData->Integral(1,hD0DcaData->GetXaxis()->GetNbins(),"width");
      cout<<"integralTotalYield: "<<integralTotalYield<<endl;

      TF1* fMix = new TF1("fMix",&funMix, 0., 0.5, 2);
      fMix->SetParameters(integralTotalYield,0.9);
      fMix->SetParLimits(0,0,2*integralTotalYield);
      fMix->SetParLimits(1,0,1);

      fMix->SetLineColor(2);
      fMix->SetFillColor(2);
      fMix->SetFillStyle(3001);
      
      float fitRangeL = 0;
      float fitRangeH = 0.08;
      
      hD0DcaData->GetXaxis()->SetRangeUser(0,0.1);
      hD0DcaData->Draw();
      int fitStatus = 1;
      TFitResultPtr fitResult;
      double fitPrecision = 1.e-6;
      while(fitStatus)
	{
	  TFitter::SetPrecision(fitPrecision);
	  fMix->SetParameters(integralTotalYield,0.9);
	  fMix->SetParError(0,0.1*integralTotalYield);
	  fMix->SetParError(1,0.1);
	  fitResult = hD0DcaData->Fit("fMix","E SNQ0", "", fitRangeL, fitRangeH);
	  fitStatus = fitResult->Status();
	  cout<<"fit precision: "<<TFitter::GetPrecision()<<"   status: "<<fitStatus<<endl;
	  if(fitStatus)
	    fitPrecision *= 10;
	}
      cout<<"============== do main fit ============"<<endl;
      fMix->SetParameters(integralTotalYield,0.9);
      fMix->SetParError(0,0.1*integralTotalYield);
      fMix->SetParError(1,0.1);
      fitResult = hD0DcaData->Fit("fMix","E S0", "", fitRangeL, fitRangeH);
      hD0DcaData->GetFunction("fMix")->Draw("flsame");
      fitStatus = fitResult->Status();
      cout<<"fit precision: "<<TFitter::GetPrecision()<<"   status: "<<fitStatus<<endl;

      TF1* fNP = new TF1("fNP",&funNonPrompt, 0., 0.5, 2);
      fNP->SetParameters(fMix->GetParameter(0),fMix->GetParameter(1));
      fNP->SetRange(fitRangeL,fitRangeH);
      fNP->SetLineColor(4);
      fNP->SetFillStyle(3001);
      fNP->SetFillColor(4);
      fNP->Draw("same");  
   
      hD0DcaData->Draw("same");

      //      cout<<"NP integral fraction: "<<fNP->Integral(fitRangeL,fitRangeH,1.e-7)/fMix->Integral(fitRangeL,fitRangeH,1.e-7)<<endl;
      cout<<"NP integral fraction: "<<fNP->Integral(fitRangeL,fitRangeH,fNP->GetParameters(),1.e-7)/fMix->Integral(fitRangeL,fitRangeH,fNP->GetParameters(),1.e-7)<<endl;
      cout<<"prompt fraction (real data statistic error only): "<<fMix->GetParameter(1)<<" +- "<<fMix->GetParError(1)<<endl;
      cout<<"chi2 / NDF: "<<fitResult->Chi2()<<" / "<<fitResult->Ndf()<<endl;
      cout<<"total yield: "<<integralTotalYield<<" (integral) vs. "<<fMix->GetParameter(0)<<" +- "<<fMix->GetParError(0)<<" (fit)"<<endl;

      promptFraction[i-1] = fMix->GetParameter(1);
      promptFractionErrorDataOnly[i-1] = fMix->GetParError(1);
      totalYield[i-1] = fMix->GetParameter(0);
      totalYieldError[i-1] = fMix->GetParError(0);

      texCms->Draw();
      texCol->Draw();
      texPtY->Draw();

      TLatex* texRatio = new TLatex(0.47,0.73,Form("Prompt frac. = %.1f #pm %.1f %%",100*fMix->GetParameter(1),100*fMix->GetParError(1)));
      texRatio->SetNDC();
      texRatio->SetTextFont(42);
      texRatio->SetTextSize(0.06);
      texRatio->SetLineWidth(2);
      texRatio->Draw();
      
      TLegend* leg4 = new TLegend(0.56,0.46,0.90,0.7);
      leg4->SetBorderSize(0);
      leg4->SetTextSize(0.06);
      leg4->SetTextFont(42);
      leg4->SetFillStyle(0);
      leg4->AddEntry(hD0DcaData,"Data","pl");
      leg4->AddEntry(fMix,"Prompt D^{0}","f");
      leg4->AddEntry(fNP,"Non-Prompt D^{0}","f");
      leg4->Draw("same");

      //smear MC smaple with the error, to simulate the MC statistic error effect.
      c4->cd(3);
      gPad->SetLogy();

      hD0DcaMCPSignal = (TH1D*)hD0DcaMCPSignal0->Clone("hMCPSignal");
      hD0DcaMCNPSignal = (TH1D*)hD0DcaMCNPSignal0->Clone("hMCNPSignal");
      
      TH1D* hPromptRatio = new TH1D("hPromptRatio", "hPromptRatio", 100, 0, 1);
      setColorTitleLabel(hPromptRatio, 1);

      int nSmear = 1000;

      for(int j=0; j<nSmear; j++)
	{
	  RandomSmear(hD0DcaMCPSignal0, hD0DcaMCPSignal);
	  RandomSmear(hD0DcaMCNPSignal0, hD0DcaMCNPSignal);
	  
	  hD0DcaData->Fit("fMix","E QN0");
	  
	  hPromptRatio->Fill(fMix->GetParameter(1));
	}
      
      hPromptRatio->GetXaxis()->SetTitle("prompt ratio");
      hPromptRatio->GetYaxis()->SetTitle("counts");
      hPromptRatio->SetMarkerStyle(20);
      hPromptRatio->SetStats(0);
      hPromptRatio->Draw("e");
      hPromptRatio->Fit("gaus");
      
      TLatex* texGaussMean = new TLatex(0.27,0.83,Form("#mu: %.3f",hPromptRatio->GetFunction("gaus")->GetParameter(1)));
      texGaussMean->SetNDC();
      texGaussMean->SetTextFont(42);
      texGaussMean->SetTextSize(0.06);
      texGaussMean->SetLineWidth(2);
      texGaussMean->Draw();
      
      TLatex* texGaussSigma = new TLatex(0.27,0.73,Form("#sigma: %.3f",hPromptRatio->GetFunction("gaus")->GetParameter(2)));
      texGaussSigma->SetNDC();
      texGaussSigma->SetTextFont(42);
      texGaussSigma->SetTextSize(0.06);
      texGaussSigma->SetLineWidth(2);
      texGaussSigma->Draw();
      
      float promptFractionErrorMc = hPromptRatio->GetFunction("gaus")->GetParameter(2);
      promptFractionError[i-1] = sqrt(pow(promptFractionErrorDataOnly[i-1],2)+pow(promptFractionErrorMc,2));
      cout<<"prompt fraction: "<<promptFraction[i-1]<<" +- "<<promptFractionError[i-1]<<" (+- "<<promptFractionErrorDataOnly[i-1]<<" +- "<<promptFractionErrorMc<<" )"<<endl;

      bToDYield[i-1] = totalYield[i-1]*(1-promptFraction[i-1]);
      bToDYieldError[i-1] = bToDYield[i-1]*sqrt(pow(promptFractionError[i-1]/(1-promptFraction[i-1]),2) + pow(totalYieldError[i-1]/totalYield[i-1],2));
      cout<<"B to D yield: "<<bToDYield[i-1]<<" +- "<<bToDYieldError[i-1]<<endl;

      //restore original unsmeared histograms before saving plots
      delete hD0DcaMCPSignal;
      delete hD0DcaMCNPSignal;
      hD0DcaMCPSignal = hD0DcaMCPSignal0;
      hD0DcaMCNPSignal = hD0DcaMCNPSignal0;
      hD0DcaData->Fit("fMix","E QN0");

      c4->cd(4);

      TH1D* hD0DcaDataOverFit = (TH1D*)hD0DcaData->Clone("hD0DcaDataOverFit");
      hD0DcaDataOverFit->Divide(fMix);
      hD0DcaDataOverFit->GetYaxis()->SetTitle("data / fit");
      hD0DcaDataOverFit->GetYaxis()->SetRangeUser(0,5);
      hD0DcaDataOverFit->GetXaxis()->SetRangeUser(0,0.1);
      setColorTitleLabel(hD0DcaDataOverFit, 1);
      hD0DcaDataOverFit->Draw("e");
      
      TF1* fLine1 = new TF1("fLine1", "1", 0,1);
      fLine1->Draw("same");
      hD0DcaDataOverFit->Draw("esame");
      
      c4->SaveAs(Form("plots/PbPb_%.0f_%.0f_fit.pdf",ptLow,ptHigh));

      delete hD0DcaMCPSignal;
      delete hD0DcaMCNPSignal;

    }
  c1->cd();

  TH1D* hStupidJie = new TH1D("hStupidJie", "", 100, 0, 100);
  hStupidJie->GetYaxis()->SetRangeUser(0,1);
  hStupidJie->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hStupidJie->GetYaxis()->SetTitle("prompt fraction");
  hStupidJie->SetStats(0);
  hStupidJie->Draw();
  TGraphErrors* grFraction = new TGraphErrors(nPtBins, pts, promptFraction, 0, promptFractionError);
  grFraction->SetName("grPromptFraction");
  grFraction->SetMarkerStyle(20);
  grFraction->Draw("psame");

  TGraphErrors* grFraction2 = new TGraphErrors(nPtBins, pts, promptFraction, 0, promptFractionErrorDataOnly);
  grFraction2->SetName("grPromptFractionErrorFromRealDataOnly");
  grFraction2->SetMarkerStyle(20);
  grFraction2->SetMarkerColor(4);
  grFraction2->SetLineColor(4);
  grFraction2->Draw("psame");

  TLegend* leg = new TLegend(0.2, 0.3, 0.9, 0.5);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.04);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(grFraction, "statistic error from both real data and MC", "l");
  leg->AddEntry(grFraction2, "statistic error from real data only", "l");
  leg->Draw();

  c1->SaveAs("promptFraction.pdf");

  c1->SetLogy();

  TH1D* hBtoDRawYield = new TH1D("hBtoDRawYield", ";p_{T} (GeV/c);counts per GeV/c", nPtBins, ptBins);
  for(int i=1; i<=nPtBins; i++)
    {
      if(bToDYield[i-1] <= 0) continue;
      hBtoDRawYield->SetBinContent(i, bToDYield[i-1]);
      hBtoDRawYield->SetBinError(i, bToDYieldError[i-1]);
    }
  divideBinWidth(hBtoDRawYield);
  setColorTitleLabel(hBtoDRawYield, 1);
  c1->SetBottomMargin(0.14);
  hBtoDRawYield->Draw("p");
  
  c1->SaveAs("BtoD.pdf");

  TFile* fOut = new TFile("bFeedDownResult.root", "recreate");
  fOut->WriteTObject(grFraction);
  fOut->WriteTObject(grFraction2);
  fOut->WriteTObject(hBtoDRawYield);
  fOut->Write();
  fOut->Close();
}

Double_t funMix(Double_t* x_, Double_t* para)
{
  float x = x_[0];
  float A = para[0];
  float R = para[1];
  float promptYield = 0;
  float nonPromptYield = 0;

  promptYield = hD0DcaMCPSignal->GetBinContent(hD0DcaMCPSignal->GetXaxis()->FindBin(x));
  nonPromptYield = hD0DcaMCNPSignal->GetBinContent(hD0DcaMCNPSignal->GetXaxis()->FindBin(x));

  return A*(R*promptYield+(1-R)*nonPromptYield);
}

Double_t funNonPrompt(Double_t* x_, Double_t* para)
{
  float x = x_[0];
  float A = para[0];
  float R = para[1];
  float nonPromptYield = 0;
  nonPromptYield = hD0DcaMCNPSignal->GetBinContent(hD0DcaMCNPSignal->GetXaxis()->FindBin(x));
  return A*(1-R)*nonPromptYield;
}

void RandomSmear(TH1D* h0, TH1D* h)
{
  for(int i=1; i<h0->GetXaxis()->GetNbins(); i++)
    {
      h->SetBinContent(i, gRandom->Gaus(h0->GetBinContent(i), h0->GetBinError(i)));
    }
}

void normalize(TH1D* h)
{
  h->Sumw2();
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      Float_t val=h->GetBinContent(i);
      Float_t valErr=h->GetBinError(i);
      if (val==0) valErr=1;
      h->SetBinContent(i,val/h->GetBinWidth(i));
      h->SetBinError(i,valErr/h->GetBinWidth(i));
    }
  h->Scale(1./h->Integral(0,100,"width"));
}

void setColorTitleLabel(TH1* h, int color)
{
  h->SetLineColor(color);
  h->SetMarkerColor(color);
  h->SetMarkerStyle(20);
  h->SetStats(0);
  h->GetXaxis()->CenterTitle();
  h->GetYaxis()->CenterTitle();
  h->GetXaxis()->SetTitleOffset(1.);
  h->GetYaxis()->SetTitleOffset(1.2);
  h->GetXaxis()->SetLabelOffset(0.007);
  h->GetYaxis()->SetLabelOffset(0.007);
  h->GetXaxis()->SetTitleSize(0.06);
  h->GetYaxis()->SetTitleSize(0.06);
  h->GetXaxis()->SetLabelSize(0.06);
  h->GetYaxis()->SetLabelSize(0.06);
}

TF1* fitMass(TH1D* hData, TH1D* hMCSignal, TH1D* hMCSwapped)
{
  Double_t setparam0=100.;
  Double_t setparam1=1.865;
  Double_t setparam2=0.03;
  Double_t setparam10=0.005;
  Double_t setparam8=0.1;
  Double_t setparam9=0.1;
  Double_t fixparam1=1.865;
  Double_t minhisto=1.7;
  Double_t maxhisto=2.0;

  TF1* f = new TF1("fMass","[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);
  f->SetParLimits(4,-1000,1000);
  f->SetParLimits(10,0.005,0.05);
  f->SetParLimits(2,0.01,0.1);
  f->SetParLimits(8,0.02,0.2);
  f->SetParLimits(7,0,1);
  f->SetParLimits(9,0,1);

  f->SetParameter(0,setparam0);
  f->SetParameter(1,setparam1);
  f->SetParameter(2,setparam2);
  f->SetParameter(10,setparam10);
  f->SetParameter(9,setparam9);

  f->FixParameter(8,setparam8);
  f->FixParameter(7,1);
  f->FixParameter(1,fixparam1);
  f->FixParameter(3,0);
  f->FixParameter(4,0);
  f->FixParameter(5,0);
  f->FixParameter(6,0);
  f->FixParameter(11,0);

  hMCSignal->Fit("fMass","q","",minhisto,maxhisto);
  hMCSignal->Fit("fMass","q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  hMCSignal->Fit("fMass","L q","",minhisto,maxhisto);
  hMCSignal->Fit("fMass","L q","",minhisto,maxhisto);
  hMCSignal->Fit("fMass","L m","",minhisto,maxhisto);

  f->FixParameter(1,f->GetParameter(1));
  f->FixParameter(2,f->GetParameter(2));
  f->FixParameter(10,f->GetParameter(10));
  f->FixParameter(9,f->GetParameter(9));
  f->FixParameter(7,0);
  f->ReleaseParameter(8);
  f->SetParameter(8,setparam8);

  hMCSwapped->Fit("fMass","L q","",minhisto,maxhisto);
  hMCSwapped->Fit("fMass","L q","",minhisto,maxhisto);
  hMCSwapped->Fit("fMass","L q","",minhisto,maxhisto);
  hMCSwapped->Fit("fMass","L m","",minhisto,maxhisto);

  f->FixParameter(7,hMCSignal->Integral(0,1000)/(hMCSwapped->Integral(0,1000)+hMCSignal->Integral(0,1000)));
  f->FixParameter(8,f->GetParameter(8));
  f->ReleaseParameter(3);
  f->ReleaseParameter(4);
  f->ReleaseParameter(5);
  f->ReleaseParameter(6);

  f->SetLineColor(kRed);

  hData->Fit("fMass","q","",minhisto,maxhisto);
  hData->Fit("fMass","q","",minhisto,maxhisto);
  f->ReleaseParameter(1);
  f->SetParLimits(1,1.86,1.87);
  f->ReleaseParameter(11);
  f->SetParLimits(11,-0.2,0.2);
  hData->Fit("fMass","L q","",minhisto,maxhisto);
  hData->Fit("fMass","L q","",minhisto,maxhisto);
  hData->Fit("fMass","L q","",minhisto,maxhisto);
  hData->Fit("fMass","L m","",minhisto,maxhisto);

  TF1* background = new TF1("fBackground","[0]+[1]*x+[2]*x*x+[3]*x*x*x");
  background->SetParameter(0,f->GetParameter(3));
  background->SetParameter(1,f->GetParameter(4));
  background->SetParameter(2,f->GetParameter(5));
  background->SetParameter(3,f->GetParameter(6));
  background->SetLineColor(4);
  background->SetRange(minhisto,maxhisto);
  background->SetLineStyle(2);

  TF1* mass = new TF1("fSignal","[0]*([3]*([4]*Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
  mass->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2),f->GetParameter(7),f->GetParameter(9),f->GetParameter(10),f->GetParameter(11));
  mass->SetParError(0,f->GetParError(0));
  mass->SetParError(1,f->GetParError(1));
  mass->SetParError(2,f->GetParError(2));
  mass->SetParError(3,f->GetParError(7));
  mass->SetParError(4,f->GetParError(9));
  mass->SetParError(5,f->GetParError(10));
  mass->SetFillColor(kOrange-3);
  mass->SetFillStyle(3002);
  mass->SetLineColor(kOrange-3);
  mass->SetLineWidth(3);
  mass->SetLineStyle(2);

  TF1* massSwap = new TF1("fBackground","[0]*(1-[2])*Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
  massSwap->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(7),f->GetParameter(8),f->GetParameter(11));
  massSwap->SetParError(0,f->GetParError(0));
  massSwap->SetParError(1,f->GetParError(1));
  massSwap->SetParError(2,f->GetParError(7));
  massSwap->SetParError(3,f->GetParError(8));
  massSwap->SetFillColor(kGreen+4);
  massSwap->SetFillStyle(3005);
  massSwap->SetLineColor(kGreen+4);
  massSwap->SetLineWidth(3);
  massSwap->SetLineStyle(1);

  hData->SetXTitle("m_{#piK} (GeV/c^{2})");
  hData->SetYTitle("Entries / (5 MeV/c^{2})");
  hData->SetAxisRange(0,hData->GetBinContent(hData->GetMaximumBin())*1.4*1.2,"Y");
  hData->SetMarkerSize(0.3);
  hData->Draw("e");

  cout<<"hData->GetMaximum(): "<<hData->GetMaximum()<<endl;

  background->Draw("same");
  mass->SetRange(minhisto,maxhisto);
  mass->Draw("same");
  massSwap->SetRange(minhisto,maxhisto);
  massSwap->Draw("same");
  f->Draw("same");

  Double_t yield = mass->Integral(minhisto,maxhisto)/hData->GetBinWidth(1);
  Double_t yieldErr = mass->Integral(minhisto,maxhisto)/hData->GetBinWidth(1)*mass->GetParError(0)/mass->GetParameter(0);

  std::cout<<"integral function yield: "<<yield<<"    fit yield: "<<f->GetParameter(0)*f->GetParameter(7)/hData->GetBinWidth(1)<<" +- "<<f->GetParError(0)*f->GetParameter(7)/hData->GetBinWidth(1)<<std::endl;

  TLegend* leg = new TLegend(0.65,0.5,0.82,0.88,NULL,"brNDC");
  leg->SetBorderSize(0);
  leg->SetTextSize(0.06);
  leg->SetTextFont(42);
  leg->SetFillStyle(0);
  leg->AddEntry(hData,"Data","pl");
  leg->AddEntry(f,"Fit","l");
  leg->AddEntry(mass,"D^{0}+#bar{D^{#lower[0.2]{0}}} Signal","f");
  leg->AddEntry(massSwap,"K-#pi swapped","f");
  leg->AddEntry(background,"Combinatorial","l");
  leg->Draw("same");

  hData->GetFunction("fMass")->Delete();
  TH1D* hDataNoFitFun = (TH1D*) hData->Clone("hDataNoFitFun");
  hDataNoFitFun->Draw("esame");

  return f;
}
