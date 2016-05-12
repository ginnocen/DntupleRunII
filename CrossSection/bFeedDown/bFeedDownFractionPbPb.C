// Yen-Jie: extraction of the feed-down fraction

#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TCut.h>
#include <TTree.h>
#include <TLegend.h>
#include <TNtuple.h>

void normalize(TH1D *h,int color)
{
   h->Sumw2();
   for (int i=1;i<=h->GetNbinsX();i++)
   {
      double val=h->GetBinContent(i);
      double valErr=h->GetBinError(i);
      if (val==0) valErr=1;
      h->SetBinContent(i,val/h->GetBinWidth(i));
      h->SetBinError(i,valErr/h->GetBinWidth(i));
   }
   h->Scale(1./h->Integral(0,100));
   h->SetLineColor(color);
   h->SetMarkerColor(color);
}

TF1 *bFeedDownFractionPbPb(double ptMin=20,double ptMax=25, bool isInclusive = 1)
{


   TFile *infMCP = new TFile("/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root");
   TFile *infMCNP = new TFile("/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_nonprompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_nonprompt_D0_dPt1tkPt1_pthatweight.root");
//   TFile *infData = new TFile("/data/dmeson2015/DataDntuple/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_skimmed.root");   //MB
   TFile *infData =   new TFile("/data/jisun/PbPb2015/HF2and_tk1p0_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root");
   
   TTree *tMCP = (TTree*)infMCP->Get("ntDkpi");
   TTree *tMCNP = (TTree*)infMCNP->Get("ntDkpi");
   TTree *tMCPHI = (TTree*)infMCP->Get("ntHi");
   TTree *tMCNPHI = (TTree*)infMCNP->Get("ntHi");
   TTree *tData = (TTree*)infData->Get("ntDkpi");
   TTree *tDataHi = (TTree*)infData->Get("ntHi");
   tData->AddFriend(tDataHi);
   tMCP->AddFriend(tMCPHI);
   tMCNP->AddFriend(tMCNPHI);
   
   
   TFile *outf = new TFile(Form("outputPbPb-%.0f-%.0f.root",ptMin,ptMax),"recreate");
   TNtuple *nt = new TNtuple("nt","","ptMin:ptMax:Frac:FracErr");
   TCanvas *cSideband = new TCanvas("cSideband","Data Sideband",1200,1200);
   cSideband->Divide(2,2);
   cSideband->cd(1);


   // high pT
   TCut cutPbPb;
   if (isInclusive == 1) {
      cutPbPb = "hiBin<200&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3";
   } else {
      cutPbPb = "hiBin<20&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3";
   }
   
   // mb
//   TCut cutPbPb = "Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))";

   //"Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)";
   TCut cutmc="(Dgen==23333||Dgen==23344)";
   TCut cutpt=Form("Dpt>%f&&Dpt<%f",ptMin,ptMax);
   TCut cutSignal = "abs(Dmass-1.8649)<0.025";
   TCut cutSideband = "abs(Dmass-1.8649)>0.075&&abs(Dmass-1.8649)<0.1";
 //  TCut weightfuncFtionreco="((TMath::Erf((log(DsvpvDisErr))*(Dgenpt*Dgenpt*(-0.001)+0.1021*Dgenpt+1.247)+(Dgenpt*Dgenpt*(-0.0032)+0.2912*Dgenpt+6.8275))+1))*(pow(10,-0.168499*Dgenpt+3.872855+Dgenpt*Dgenpt*0.000556)+pow(10,-0.068599*Dgenpt+2.512265+Dgenpt*Dgenpt*0.000331))";
 //  TCut weightfunctionreco = "pthatweight";
  TCut weightfunctionreco ="(0.104044-0.00155184*hiBin+7.42445e-6*hiBin*hiBin-1.10964e-8*hiBin*hiBin*hiBin)*exp(0.5106+9.972*Dpt-0.2284*Dpt*Dpt+0.001111*Dpt*Dpt*Dpt)";
   int nBin=20;
   double binL=3.5;
   double binH=103.5;
   double fitRangeL=3.5;
   double fitRangeH=100.5;

   if (ptMax<=6) {
      fitRangeH=103.5;
      binH=103.5;
   }

   float bins[6+1]={3.5,5.5,8.5,10.5,20.5,30.5,50.5};
   
   TH1D *hSideband = new TH1D("hSideband","Sideband",nBin,binL,binH);
   TH1D *hData = new TH1D("hData","Data",nBin,binL,binH);
   TH1D *hMCPSignal = new TH1D("hMCPSignal","Prompt",nBin,binL,binH);
   TH1D *hMCNPSignal = new TH1D("hMCNPSignal","Non-prompt",nBin,binL,binH);
   TH1D *hMCPSideband = new TH1D("hMCPSideband","",nBin,binL,binH);
   TH1D *hMCNPSideband = new TH1D("hMCNPSideband","",nBin,binL,binH);
   hSideband->Sumw2();
   hData->Sumw2();
   hMCPSignal->Sumw2();
   hMCNPSignal->Sumw2();

   
   tData->Draw("(DsvpvDistance/DsvpvDisErr)>>hSideband",cutpt&&cutPbPb&&cutSideband);
   tData->Draw("(DsvpvDistance/DsvpvDisErr)>>hData",cutpt&&cutPbPb&&cutSignal);
   tMCP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCPSignal",weightfunctionreco*(cutpt&&cutPbPb&&cutSignal&&cutmc));
   //tMCP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCPSideband",cutpt&&cutPbPb&&cutSideband);
   tMCNP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCNPSignal",weightfunctionreco*(cutpt&&cutPbPb&&cutSignal&&cutmc));
   //tMCNP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCNPSideband",cutpt&&cutPbPb&&cutSideband);
   
   hSideband->Scale(1./1.);
   hData->Add(hSideband,-1);
   normalize(hData,1);
   normalize(hMCPSignal,2);
   normalize(hMCNPSignal,4);
   normalize(hSideband,kGreen+2);
   
   
   
   TF1 *fSideband = new TF1("fSideband","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");     
   TF1 *fMCPSignal = new TF1("fMCPSignal","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");
   TF1 *fMCNPSignal = new TF1("fMCNPSignal","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");
   
   fSideband->SetParameters(0,-0.1,0.2,-0,-2,0.006,-0.01,-0.11,-0.04,0,0.001);
   fMCNPSignal->SetParameters(0,-0.1,0.1,-0,-0.02,0.006,-0.01,-0.11,-0.04,0,0.001);
   fMCPSignal->SetParameters(0,-0.1,0.1,-0,-0.02,0.006,-0.01,-0.11,-0.04,0,0.001);
//   fMCNPSignal->FixParameter(3,0);
//   fMCPSignal->FixParameter(3,0);
   fMCPSignal->SetParLimits(1,-100,0);   
   fMCPSignal->SetParLimits(4,-100,0);   
   fMCPSignal->SetParLimits(7,-100,0);   
   fMCNPSignal->SetParLimits(1,-100,0);   
   fMCNPSignal->SetParLimits(4,-100,0);   
   fMCNPSignal->SetParLimits(7,-100,0);   
   fMCPSignal->SetParLimits(0,0,1e10);   
   fMCPSignal->SetParLimits(3,0,1e10);   
   fMCPSignal->SetParLimits(6,0,1e10);   
   fMCNPSignal->SetParLimits(0,0,1e10);   
   fMCNPSignal->SetParLimits(3,0,1e10);   
   fMCNPSignal->SetParLimits(6,0,1e10);   

   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   
   
   hSideband->Fit("fSideband","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","LL q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","m q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","m q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband","m q","",fitRangeL,fitRangeH);
   hSideband->Fit("fSideband"," q","",fitRangeL,fitRangeH);
   double normSideband = hSideband->Integral(0,0.12);
   
   cSideband->cd(2);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","LL q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","m q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","m q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal","m q","",fitRangeL,fitRangeH);
   hMCPSignal->Fit("fMCPSignal"," m q","",fitRangeL,fitRangeH);
   double normMCPSignal = hMCPSignal->Integral(0,0.12);

   cSideband->cd(3);
   hMCNPSignal->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal"," q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal"," q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","LL q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal"," q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal"," q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","m q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","m q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","m q","",fitRangeL,fitRangeH);
   hMCNPSignal->Fit("fMCNPSignal","m q","",fitRangeL,fitRangeH);
   
   double normMCNPSignal = hMCNPSignal->Integral(0,0.12);
   
   
   string sSideband = Form("(%e)*(exp((%e)*(x*[3])+(%e))+(%e)*exp((%e)*(x*[3])+(%e))+(%e)*exp((%e)*(x*[3])+(%e)))",fSideband->GetParameter(0),fSideband->GetParameter(1),fSideband->GetParameter(2),fSideband->GetParameter(3),fSideband->GetParameter(4),fSideband->GetParameter(5),fSideband->GetParameter(6),fSideband->GetParameter(7),fSideband->GetParameter(8));
   string sMCPSignal = Form("(%e)*(exp((%e)*(x*[3])+(%e))+(%e)*exp((%e)*(x*[3])+(%e))+(%e)*exp((%e)*(x*[3])+(%e)))",fMCPSignal->GetParameter(0),fMCPSignal->GetParameter(1),fMCPSignal->GetParameter(2),fMCPSignal->GetParameter(3),fMCPSignal->GetParameter(4),fMCPSignal->GetParameter(5),fMCPSignal->GetParameter(6),fMCPSignal->GetParameter(7),fMCPSignal->GetParameter(8));
   
   string sMCNPSignal = Form("(%e)*(exp((%e)*(x*[3])+(%e))+(%e)*exp((%e)*(x*[3])+(%e))+(%e)*exp((%e)*(x*[3])+(%e)))",fMCNPSignal->GetParameter(0),fMCNPSignal->GetParameter(1),fMCNPSignal->GetParameter(2),fMCNPSignal->GetParameter(3),fMCNPSignal->GetParameter(4),fMCNPSignal->GetParameter(5),fMCNPSignal->GetParameter(6),fMCNPSignal->GetParameter(7),fMCNPSignal->GetParameter(8));
   
   
   string function;
   function="0*("+sSideband+")+[1]*([2]*"+sMCPSignal+"+(1-[2])*("+sMCNPSignal+"))";
   string functionNP;
   functionNP="0*("+sSideband+")+[1]*(0*"+sMCPSignal+"+(1-[2])*("+sMCNPSignal+"))";
   
    
   TCanvas *cFit = new TCanvas("cFit","Fit",600,600);
   TF1 *f = new TF1("f",function.c_str());
   f->SetParameters(1,0.1,0.9,0,0.1);
   f->SetParLimits(0,0,1000);
   f->SetParLimits(2,-1,2);
   f->SetLineColor(2);
   f->SetFillColor(2);
   f->SetFillStyle(3001);
   f->Draw("same");   
   hData->SetAxisRange(fitRangeL,fitRangeH,"X");
   hData->Fit("f","LL");
   hData->Fit("f","LL");
   hData->Fit("f","LL");
   hData->Fit("f","LL");
   hData->Fit("f","m");
   hData->SetXTitle("Flight Distance Significance");
   hData->SetYTitle("Event Fraction");
   
   TF1 *fNP = new TF1("fNP",functionNP.c_str());
   fNP->SetParameters(f->GetParameter(0),f->GetParameter(1),f->GetParameter(2));
   fNP->SetRange(fitRangeL,fitRangeH*2);
   fNP->SetLineColor(4);
   fNP->SetFillStyle(3001);
   fNP->SetFillColor(4);
   hData->SetStats(0);
   hData->Draw("same");
   fNP->Draw("same");  

   cout <<fNP->Integral(3.5,60)/f->Integral(3.5,60)<<endl;

   TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->AddEntry(hData,"PbPb data","pl");
   leg->AddEntry(f,Form("Prompt Fraction %.1f #pm %.1f %%",100*f->GetParameter(2),100*f->GetParError(2)),""); 
   leg->AddEntry(f,"Prompt D^{0}","f");
   leg->AddEntry(fNP,"Non-Prompt D^{0}","f");
   
   leg->Draw();
   
   cSideband->cd(4);
   hMCPSignal->Draw("hist");
   hSideband->Draw("hist same");
   hMCNPSignal->Draw("hist same");
   hData->Draw("same");
   nt->Fill(ptMin,ptMax,f->GetParameter(2),f->GetParError(2));
   nt->Write();
   outf->Write();
//   outf->Close();	
   return f;
}

void scan()
{
   TFile *outf = new TFile("result.root","recreate");

   TH1D *h = new TH1D("h","",6,20,50);
   int bin=1;
   for (int i=20;i<50;i+=5)
   {
      TF1 *f = bFeedDownFractionPbPb(i,i+5);
      h->SetBinContent(bin,f->GetParameter(2));
      h->SetBinError(bin,f->GetParError(2));
      bin++;
   }
   
   TCanvas *cResult = new TCanvas("cResult","",600,600);
   h->SetXTitle("D^{0} p_{T} (GeV/c)");
   h->SetYTitle("Prompt Fraction");
   h->Draw("e");
}

