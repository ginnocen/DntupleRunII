#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"


void BuildNormalisationPP(double pt=17.5,double lumiPP=25.8 )
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  TString fileMB="ROOTfiles/CrossSectionFONLLPPMBNorm.root"; 
  TString file="ROOTfiles/CrossSectionFONLLPPNorm.root";
  
  TFile* filePPMB = new TFile(fileMB.Data());  
  TH1D* hSigmaPPStatMB = (TH1D*)filePPMB->Get("hPtSigma");

  TFile* filePP = new TFile(file.Data());  
  TH1D* hTriggerEfficiencyPtBins = (TH1D*)filePP->Get("hTriggerEfficiencyPtBins");
  TH1D* hSigmaPPStat = (TH1D*)filePP->Get("hPtSigma");
    
  hSigmaPPStat->Sumw2();
  hSigmaPPStatMB->Sumw2();
  
  TH1D* hRatioMBOverTriggered = (TH1D*)hSigmaPPStatMB->Clone("hRatioMBOverTriggered");
  hRatioMBOverTriggered->Divide(hSigmaPPStat);

  hRatioMBOverTriggered->Scale(lumiPP);  
  for (int i=1;i<4;i++) cout<<"luminosity="<<hRatioMBOverTriggered->GetBinContent(i)<<"with error="<<hRatioMBOverTriggered->GetBinError(i)<<endl;

  TCanvas*canvas=new TCanvas("canvas","canvas",1000,500);
  canvas->Divide(2,1);
  canvas->cd(1);
  TH2F* hemptyLumi=new TH2F("hemptyLumi","",50,5,30,10.,0,0.05); 
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
  canvas->cd(2);
  TH2F* hemptyEff=new TH2F("hemptyEff","",50,5,30,10.,0,1.5); 
  hemptyEff->GetXaxis()->CenterTitle();
  hemptyEff->GetYaxis()->CenterTitle();
  hemptyEff->GetYaxis()->SetTitle("Trigger efficiency");
  hemptyEff->GetXaxis()->SetTitle("p_{T} (GeV/c)");
  hemptyEff->GetXaxis()->SetTitleOffset(0.95);//0.9
  hemptyEff->GetYaxis()->SetTitleOffset(1.30);//1.
  hemptyEff->GetXaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetYaxis()->SetTitleSize(0.060);//0.045
  hemptyEff->GetXaxis()->SetTitleFont(42);
  hemptyEff->GetYaxis()->SetTitleFont(42);
  hemptyEff->GetXaxis()->SetLabelFont(42);
  hemptyEff->GetYaxis()->SetLabelFont(42);
  hemptyEff->GetXaxis()->SetLabelSize(0.050);//0.035
  hemptyEff->GetYaxis()->SetLabelSize(0.050);//0.035  
  hemptyEff->GetXaxis()->SetLabelOffset(0.01);
  hemptyEff->Draw();
  hTriggerEfficiencyPtBins->Draw("same");


  }
  
  void BuildNormalisationPbPbInclusive(TString cut="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)")
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  double TAA=0.;
  TString selection;
  
    TAA=392.4/(70.*1e9);
    selection="1";

  TString inputfilePbPbMB="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root";
  TFile* filePbPbMBraw = new TFile(inputfilePbPbMB.Data());  
  TTree* HltTreePbPbMB= (TTree*) filePbPbMBraw->Get("ntHlt");
  TH1D*hcountsMBPbPb=new TH1D("hcountsMBPbPb","hcountsMBPbPb",2,-200,200);
  HltTreePbPbMB->Draw("1>>hcountsMBPbPb",Form("%s&&%s",cut.Data(),selection.Data()));
  double ncountsMBPbPb=hcountsMBPbPb->GetEntries();
  
  double lumiPbPbMB=ncountsMBPbPb*TAA;
  cout<<"luminosity MB="<<lumiPbPbMB<<endl;

 // cout<<"nevents MB PbPb="<<ncountsMBPbPb<<endl;
 // cout<<"1/lumiPbPb MB="<<lumiPbPbMB/(208*208)<<endl;
  
  TString fileMB="ROOTfiles/CrossSectionFONLLPbPbMBNorm.root"; 
  TString file="ROOTfiles/CrossSectionFONLLPbPbNorm.root";
  
  TFile* filePbPbMB = new TFile(fileMB.Data());  
  TH1D* hSigmaPbPbStatMB = (TH1D*)filePbPbMB->Get("hPtSigma");

  TFile* filePbPb = new TFile(file.Data());  
  TH1D* hSigmaPbPbStat = (TH1D*)filePbPb->Get("hPtSigma");
  
  double ratio=hSigmaPbPbStat->GetBinContent(hSigmaPbPbStat->FindBin(22.5))/hSigmaPbPbStatMB->GetBinContent(hSigmaPbPbStatMB->FindBin(22.5));
  cout<<"ratio="<<ratio<<endl;
  double lumiHighPt=ratio*lumiPbPbMB;
  cout<<"luminosity high pt="<<lumiHighPt<<endl;

  }
  
void BuildNormalisationPbPbCen10(TString cut="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)")
{
  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);
  
  double TAA=0.;
  TString selection;
  
  TAA=(23.2/1e9);
  selection="hiBin<20";

  TString inputfilePbPbMB="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root";
  TFile* filePbPbMBraw = new TFile(inputfilePbPbMB.Data());  
  TTree* HltTreePbPbMB= (TTree*) filePbPbMBraw->Get("ntHlt");
  TTree* HltHiPbPbMB= (TTree*) filePbPbMBraw->Get("ntHi");
  TH1D*hcountsMBPbPb=new TH1D("hcountsMBPbPb","hcountsMBPbPb",2,-200,200);
  HltTreePbPbMB->AddFriend(HltHiPbPbMB);
  
  HltTreePbPbMB->Draw("1>>hcountsMBPbPb",Form("%s&&%s",cut.Data(),selection.Data()));
  double ncountsMBPbPb=hcountsMBPbPb->GetEntries();
  
  double lumiPbPbMB=ncountsMBPbPb*TAA;
  cout<<"luminosity MB="<<lumiPbPbMB<<endl;

 // cout<<"nevents MB PbPb="<<ncountsMBPbPb<<endl;
 // cout<<"1/lumiPbPb MB="<<lumiPbPbMB/(208*208)<<endl;
  
  TString fileMB="ROOTfiles/CrossSectionFONLLPbPbMBNorm_Cent10.root"; 
  TString file="ROOTfiles/CrossSectionFONLLPbPbNorm_Cent10.root";
  
  TFile* filePbPbMB = new TFile(fileMB.Data());  
  TH1D* hSigmaPbPbStatMB = (TH1D*)filePbPbMB->Get("hPtSigma");

  TFile* filePbPb = new TFile(file.Data());  
  TH1D* hSigmaPbPbStat = (TH1D*)filePbPb->Get("hPtSigma");
  
  double ratio=hSigmaPbPbStat->GetBinContent(hSigmaPbPbStat->FindBin(22.5))/hSigmaPbPbStatMB->GetBinContent(hSigmaPbPbStatMB->FindBin(22.5));
  cout<<"ratio="<<ratio<<endl;
  double lumiHighPt=ratio*lumiPbPbMB;
  cout<<"luminosity high pt="<<lumiHighPt<<endl;

  }