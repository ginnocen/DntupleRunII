// Yen-Jie: extraction of the feed-down fraction

#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TF1.h>
#include <TCut.h>
#include <TTree.h>
#include <TLegend.h>

void normalize(TH1D *h,int color)
{
   h->Sumw2();
   h->Scale(1./h->Integral(0,100));
   h->SetLineColor(color);
   h->SetMarkerColor(color);
}

TF1 *bFeedDownFraction(double ptMin=20,double ptMax=25)
{
   TFile *infMCP = new TFile("miniNtuplePrompt.root");
   TFile *infMCNP = new TFile("miniNtupleNonPrompt.root");
   TFile *infData = new TFile("miniData.root");
  //TFile *infData = new TFile("miniNtupleNonPrompt.root");
   //(DsvpvDistance/DsvpvDisErr)
   
   TTree *tMCP = (TTree*)infMCP->Get("ntDkpi");
   TTree *tMCNP = (TTree*)infMCNP->Get("ntDkpi");
   TTree *tData = (TTree*)infData->Get("ntDkpi");
   
   TFile *outf = new TFile("output.root","recreate");
   TCut cutpp =""; "Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)";
   TCut cutmc="(Dgen==23333||Dgen==23344)";
   TCut cutpt=Form("Dpt>%f&&Dpt<%f",ptMin,ptMax);
   TCut cutSignal = "abs(Dmass-1.8649)<0.025";
   TCut cutSideband = "abs(Dmass-1.8649)>0.050&&abs(Dmass-1.8649)<0.15";
   TCut weightfunctionreco="((TMath::Erf((log(DsvpvDisErr))*(Dgenpt*Dgenpt*(-0.001)+0.1021*Dgenpt+1.247)+(Dgenpt*Dgenpt*(-0.0032)+0.2912*Dgenpt+6.8275))+1))*(pow(10,-0.168499*Dgenpt+3.872855+Dgenpt*Dgenpt*0.000556)+pow(10,-0.068599*Dgenpt+2.512265+Dgenpt*Dgenpt*0.000331))";
   
   int nBin=50;
   double binL=3.5;
   double binH=43.5;
   TH1D *hSideband = new TH1D("hSideband","",nBin,binL,binH);
   TH1D *hData = new TH1D("hData","",nBin,binL,binH);
   TH1D *hMCPSignal = new TH1D("hMCPSignal","",nBin,binL,binH);
   TH1D *hMCNPSignal = new TH1D("hMCNPSignal","",nBin,binL,binH);
   TH1D *hMCPSideband = new TH1D("hMCPSideband","",nBin,binL,binH);
   TH1D *hMCNPSideband = new TH1D("hMCNPSideband","",nBin,binL,binH);
   hSideband->Sumw2();
   hData->Sumw2();
   hMCPSignal->Sumw2();
   hMCNPSignal->Sumw2();

   
   tData->Draw("(DsvpvDistance/DsvpvDisErr)>>hSideband",cutpt&&cutpp&&cutSideband);
   tData->Draw("(DsvpvDistance/DsvpvDisErr)>>hData",cutpt&&cutpp&&cutSignal);
   tMCP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCPSignal",weightfunctionreco*(cutpt&&cutpp&&cutSignal&&cutmc));
   //tMCP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCPSideband",cutpt&&cutpp&&cutSideband);
   tMCNP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCNPSignal",weightfunctionreco*(cutpt&&cutpp&&cutSignal&&cutmc));
   //tMCNP->Draw("(DsvpvDistance/DsvpvDisErr)>>hMCNPSideband",cutpt&&cutpp&&cutSideband);
   
   hSideband->Scale(1./4);
   hData->Add(hSideband,-1);
   normalize(hData,1);
   normalize(hMCPSignal,2);
   normalize(hMCNPSignal,4);
   normalize(hSideband,kGreen+2);
   
   
   
   TF1 *fSideband = new TF1("fSideband","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");     
   TF1 *fMCPSignal = new TF1("fMCPSignal","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");
   TF1 *fMCNPSignal = new TF1("fMCNPSignal","[0]*(exp([1]*x+[2])+[3]*exp([4]*x+[5])+[6]*exp([7]*x+[8]))");
   
   fSideband->SetParameters(0,0,0.2,-0,-0.02,0.006,2.5,-0.11,0.04,0,0.001);
   fMCPSignal->SetParameters(0,0,0.1,-0,-0.02,0.006,2.5,-0.11,0.04,0,0.001);
   fMCNPSignal->SetParameters(0,0,0.2,-0,-0.02,0.006,2.5,-0.11,0.04,0,0.001);

   TCanvas *cSideband = new TCanvas("cSideband","Data Sideband",600,600);
   hSideband->Fit("fSideband","LL q");
   hSideband->Fit("fSideband","LL q");
   hSideband->Fit("fSideband","q");
   hSideband->Fit("fSideband","q");
   hSideband->Fit("fSideband","q");
   hSideband->Fit("fSideband","LL q");
   hSideband->Fit("fSideband","LL q");
   hSideband->Fit("fSideband","LL q");
   hSideband->Fit("fSideband","LL q");
   hSideband->Fit("fSideband","q");
   hSideband->Fit("fSideband","q");
   hSideband->Fit("fSideband","q");
   hSideband->Fit("fSideband","LL q");
   hSideband->Fit("fSideband","LL q");
   double normSideband = hSideband->Integral(0,0.12);
   
   TCanvas *cMCPSignal = new TCanvas("cMCPSignal","Prompt MC",600,600);
   hMCPSignal->Fit("fMCPSignal","LL q");
   hMCPSignal->Fit("fMCPSignal","LL q");
   hMCPSignal->Fit("fMCPSignal","q");
   hMCPSignal->Fit("fMCPSignal","q");
   hMCPSignal->Fit("fMCPSignal","q");
   hMCPSignal->Fit("fMCPSignal","LL q");
   hMCPSignal->Fit("fMCPSignal","LL q");
   hMCPSignal->Fit("fMCPSignal","LL q");
   hMCPSignal->Fit("fMCPSignal","LL q");
   hMCPSignal->Fit("fMCPSignal","q");
   hMCPSignal->Fit("fMCPSignal","q");
   hMCPSignal->Fit("fMCPSignal","q");
   hMCPSignal->Fit("fMCPSignal","LL q");
   hMCPSignal->Fit("fMCPSignal","LL q");
   double normMCPSignal = hMCPSignal->Integral(0,0.12);

   TCanvas *cMCNPSignal = new TCanvas("cMCNPSignal","Prompt MC",600,600);
   hMCNPSignal->Fit("fMCNPSignal","LL q");
   hMCNPSignal->Fit("fMCNPSignal","LL q");
   hMCNPSignal->Fit("fMCNPSignal","q");
   hMCNPSignal->Fit("fMCNPSignal","q");
   hMCNPSignal->Fit("fMCNPSignal","q");
   hMCNPSignal->Fit("fMCNPSignal","LL q");
   hMCNPSignal->Fit("fMCNPSignal","LL q");
   hMCNPSignal->Fit("fMCNPSignal","LL q");
   hMCNPSignal->Fit("fMCNPSignal","LL q");
   hMCNPSignal->Fit("fMCNPSignal","q");
   hMCNPSignal->Fit("fMCNPSignal","q");
   hMCNPSignal->Fit("fMCNPSignal","q");
   hMCNPSignal->Fit("fMCNPSignal","LL q");
   hMCNPSignal->Fit("fMCNPSignal","LL q");
   double normMCNPSignal = hMCNPSignal->Integral(0,0.12);
   
   
   string sSideband = Form("(%f)*(exp((%f)*x+(%f))+(%f)*exp((%f)*x+(%f))+(%f)*exp((%f)*x+(%f)))",fSideband->GetParameter(0),fSideband->GetParameter(1),fSideband->GetParameter(2),fSideband->GetParameter(3),fSideband->GetParameter(4),fSideband->GetParameter(5),fSideband->GetParameter(6),fSideband->GetParameter(7),fSideband->GetParameter(8));
   string sMCPSignal = Form("(%f)*(exp((%f)*x+(%f))+(%f)*exp((%f)*x+(%f))+(%f)*exp((%f)*x+(%f)))",fMCPSignal->GetParameter(0),fMCPSignal->GetParameter(1),fMCPSignal->GetParameter(2),fMCPSignal->GetParameter(3),fMCPSignal->GetParameter(4),fMCPSignal->GetParameter(5),fMCPSignal->GetParameter(6),fMCPSignal->GetParameter(7),fMCPSignal->GetParameter(8));
   
   string sMCNPSignal = Form("(%f)*(exp((%f)*x+(%f))+(%f)*exp((%f)*x+(%f))+(%f)*exp((%f)*x+(%f)))",fMCNPSignal->GetParameter(0),fMCNPSignal->GetParameter(1),fMCNPSignal->GetParameter(2),fMCNPSignal->GetParameter(3),fMCNPSignal->GetParameter(4),fMCNPSignal->GetParameter(5),fMCNPSignal->GetParameter(6),fMCNPSignal->GetParameter(7),fMCNPSignal->GetParameter(8));
   
   
   string function;
   function="[0]*("+sSideband+")+[1]*([2]*"+sMCPSignal+"+(1-[2])*("+sMCNPSignal+"))";
   
    
   TCanvas *cFit = new TCanvas("cFit","Fit",600,600);
   TF1 *f = new TF1("f",function.c_str());
   f->SetParameters(1,0.1,0.9,0,0.1);
   //f->FixParameter(0,0);
   f->SetParLimits(0,0,1000);
   f->SetParLimits(2,-1,2);
   hData->Fit("f","LL");
   hData->Fit("f","LL");
   hData->Fit("f","LL");
   hData->Fit("f","LL");
   hData->Fit("f","m");
   hData->Fit("f","m");
   
   TCanvas *cComparison = new TCanvas("cComparison","Comparison",600,600);
   hMCPSignal->Draw("hist");
   hSideband->Draw("hist same");
   hMCNPSignal->Draw("hist same");
   hData->Draw("same");
      
   
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
      TF1 *f = bFeedDownFraction(i,i+5);
      h->SetBinContent(bin,f->GetParameter(2));
      h->SetBinError(bin,f->GetParError(2));
      bin++;
   }
   
   TCanvas *cResult = new TCanvas("cResult","",600,600);
   h->SetXTitle("D^{0} p_{T} (GeV/c)");
   h->SetYTitle("Prompt Fraction");
   h->Draw("e");
}

