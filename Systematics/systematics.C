#include <TF1.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TLine.h>
#include <TLegend.h>

// Yen-Jie: systematics table for D meson
// Unit: In percentage

// =============================================================================================================
// D meson decay
// =============================================================================================================
double DKpiBRUncertainty	= 1.29;			// from PDG

// =============================================================================================================
// pp uncertainty
// =============================================================================================================

double ppTrackingEfficiency 	= 4;   			// single track systematics from D* studies
double ppLumiUncertainty 	= 10;			// 10% for the moment, to be updated (from Daniel)
double ppSignalExtraction	= 7;			// TODO: old number from 2011, to be updated
double ppDMesonSelection	= 11.4;			// TODO: old number from 2011, to be updated
double ppBFeedDownCorrection	= 0;			// TODO
double ppMCPtSpectra		= 0;			// TODO

TF1 *fppSignalExtractionSig = new TF1("fppSignalExtractionSig","[0]+[1]/(x)+[2]/x/x+[3]*x");
TF1 *fppSignalExtractionBkg = new TF1("fppSignalExtractionBkg","[0]+[1]/(x)+[2]/x/x+[3]*x");


// =============================================================================================================
// PbPb uncertainty
// =============================================================================================================
double PbPbNMBUncertainty	= 2;			// uncertainty associated with minbias events, 
							// used in RAA for pT < 20 GeV
double PbPbLumiUncertainty	= 10;			// 10% for the moment, to be updated (from Daniel)
double PbPbTrigger		= 0.6;			// Statistical uncertainty of the eff plateau (92.8+-0.6%)

double TAAUncertainty0to100	= 5.7;			// TODO: old number from 2011, to be updated to the latest table
double PbPbSignalExtraction	= 7;			// TODO: old number from 2011, to be updated
double PbPbDMesonSelection	= 11.4;			// TODO: old number from 2011, to be updated
double PbPbBFeedDownCorrection	= 0;			// TODO
double PbPbMCPtSpectra		= 0;			// TODO

TF1 *fPbPbSignalExtractionSig = new TF1("fPbPbSignalExtractionSig","[0]+[1]/(x)+[2]/x/x+[3]*x");
TF1 *fPbPbSignalExtractionBkg = new TF1("fPbPbSignalExtractionBkg","[0]+[1]/(x)+[2]/x/x+[3]*x");

bool initialized = 0;

void initialization()
{
   fppSignalExtractionSig->SetParameters(-2.783,58.6,-161.6,0.1142);
   fppSignalExtractionBkg->SetParameters(-6.024,122,-314.1,0.1775);
   fPbPbSignalExtractionSig->SetParameters(-6.024,122,-314.1,0.1775);  
   fPbPbSignalExtractionBkg->SetParameters(6.741,-45.35,337,-0.04263);
}

// =============================================================================================================
// RAA systematics
// =============================================================================================================
float systematicsForRAA(double pt, double HLT=0, int stage=0)
{
   if (!initialized) initialization();
   double sys=0;
   sys+=ppLumiUncertainty*ppLumiUncertainty;
   
   if (pt<20) sys+=PbPbNMBUncertainty*PbPbNMBUncertainty;
   	else  sys+=PbPbLumiUncertainty*PbPbLumiUncertainty;
   
   sys+=TAAUncertainty0to100*TAAUncertainty0to100;

   if (stage==1) return sqrt(sys);
   
   sys+=(fPbPbSignalExtractionSig->Eval(pt)-fppSignalExtractionSig->Eval(pt))*
        (fPbPbSignalExtractionSig->Eval(pt)-fppSignalExtractionSig->Eval(pt));
   sys+=(fPbPbSignalExtractionBkg->Eval(pt)-fppSignalExtractionBkg->Eval(pt))*
   	(fPbPbSignalExtractionBkg->Eval(pt)-fppSignalExtractionBkg->Eval(pt));

   if (stage==2) return sqrt(sys);
   
   sys+=ppDMesonSelection*ppDMesonSelection;
   sys+=ppBFeedDownCorrection*ppBFeedDownCorrection;
   sys+=ppMCPtSpectra*ppMCPtSpectra;
   sys+=PbPbDMesonSelection*PbPbDMesonSelection;
   sys+=PbPbBFeedDownCorrection*PbPbBFeedDownCorrection;
   sys+=PbPbMCPtSpectra*PbPbMCPtSpectra;
    
   return sqrt(sys);
}

// =============================================================================================================
// RCP systematics
// =============================================================================================================
float systematicsForRCP(double pt, double HLT=0)
{
   if (!initialized) initialization();
   return 0.2;

}


// =============================================================================================================
// cross-section systematics for pp
// =============================================================================================================
float systematicsPP(double pt, double HLT=0)
{
   if (!initialized) initialization();
   double sys=0;
   sys+=(ppTrackingEfficiency*2)*(ppTrackingEfficiency*2);
   sys+=ppLumiUncertainty*ppLumiUncertainty;
   sys+=ppDMesonSelection*ppDMesonSelection;
   sys+=ppBFeedDownCorrection*ppBFeedDownCorrection;
   sys+=ppMCPtSpectra*ppMCPtSpectra;
   sys+=(fppSignalExtractionSig->Eval(pt))*(fppSignalExtractionSig->Eval(pt));
   
   return sqrt(sys);
}

// =============================================================================================================
// cross-section systematics for PbPb
// =============================================================================================================
float systematicsPbPb(double pt, double HLT=0)
{
   if (!initialized) initialization();
   double sys=0;
   
   // pp tracking eff uncertainty used for the moment
   sys+=(ppTrackingEfficiency*2)*(ppTrackingEfficiency*2);
   if (pt<20) sys+=PbPbNMBUncertainty*PbPbNMBUncertainty;
   	else  sys+=PbPbLumiUncertainty*PbPbLumiUncertainty;
   
   sys+=TAAUncertainty0to100*TAAUncertainty0to100;
   sys+=PbPbDMesonSelection*PbPbDMesonSelection;
   sys+=PbPbBFeedDownCorrection*PbPbBFeedDownCorrection;
   sys+=PbPbMCPtSpectra*PbPbMCPtSpectra;
   sys+=(fPbPbSignalExtractionSig->Eval(pt))*(fPbPbSignalExtractionSig->Eval(pt));
    
   return sqrt(sys);

}


// =============================================================================================================
// Drawer
// =============================================================================================================
void drawSys(double x1,double y1, double x2,double y2, int color = 1)
{
   TLine *l1 = new TLine(x1,y1/100.,x2,y2/100.);
   TLine *l2 = new TLine(x1,-y1/100.,x2,-y2/100.);
   l1->SetLineWidth(2);
   l2->SetLineWidth(2);
   l1->SetLineColor(color);
   l2->SetLineColor(color);
   l1->Draw();
   l2->Draw();
 
}

// =============================================================================================================
// Plot systematics for RAA
// =============================================================================================================
void plotSystematicsRAA()
{
   TH1D *htmp = new TH1D("htmp","",1000,3,102);
   htmp->SetAxisRange(-0.5,0.8,"Y");
   htmp->SetXTitle("D meson p_{T} (GeV/c)");
   htmp->SetYTitle("Systematical Uncertainty");
   TCanvas *c = new TCanvas("c","",600,600);
   c->SetLogx();
   htmp->Draw();
   for (double i=3;i<100;i+=0.1)
   {      
      drawSys(i,systematicsForRAA(i), i+0.1,systematicsForRAA(i+0.1),1);
      drawSys(i,systematicsForRAA(i,0,1), i+0.1,systematicsForRAA(i+0.1,0,1),2);
      drawSys(i,sqrt((systematicsForRAA(i,0,2)*systematicsForRAA(i,0,2))-(systematicsForRAA(i,0,1)*systematicsForRAA(i,0,1))),
              i+0.1,sqrt((systematicsForRAA(i+0.1,0,2)*systematicsForRAA(i+0.1,0,2))-(systematicsForRAA(i+0.1,0,1)*systematicsForRAA(i+0.1,0,1))),4);
      drawSys(i,sqrt((systematicsForRAA(i,0,0)*systematicsForRAA(i,0,0))-(systematicsForRAA(i,0,2)*systematicsForRAA(i,0,2))),
              i+0.1,sqrt((systematicsForRAA(i+0.1,0,0)*systematicsForRAA(i+0.1,0,0))-(systematicsForRAA(i+0.1,0,2)*systematicsForRAA(i+0.1,0,2))),kGreen+2);
   }

   TH1D *h1 = new TH1D("h1","",100,0,1);
   h1->SetLineWidth(2); h1->SetLineColor(1);
   TH1D *h2 = new TH1D("h2","",100,0,1);
   h2->SetLineWidth(2); h2->SetLineColor(2);
   TH1D *h4 = new TH1D("h4","",100,0,1);
   h4->SetLineWidth(2); h4->SetLineColor(4);
   TH1D *h5 = new TH1D("h5","",100,0,1);
   h5->SetLineWidth(2); h5->SetLineColor(kGreen+2);
 
   TLegend *leg = new TLegend(0.2,0.7,0.9,0.9);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->AddEntry(h1,"Total Systematics","l");
   leg->AddEntry(h2,"Overall Normalization (N_{MB}, Lumi)","l");
   leg->AddEntry(h4,"Signal Extraction","l");
   leg->AddEntry(h5,"D Meson Selection and Correction","l");
   leg->Draw();
}
