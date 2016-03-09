#include <TF1.h>

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
float systematicsForRAA(double pt, double HLT=0)
{
   if (!initialized) initialization();
   double sys=0;
   sys+=ppLumiUncertainty*ppLumiUncertainty;
   sys+=ppDMesonSelection*ppDMesonSelection;
   sys+=ppBFeedDownCorrection*ppBFeedDownCorrection;
   sys+=ppMCPtSpectra*ppMCPtSpectra;
   
   if (pt<20) sys+=PbPbNMBUncertainty*PbPbNMBUncertainty;
   	else  sys+=PbPbLumiUncertainty*PbPbLumiUncertainty;
   
   sys+=TAAUncertainty0to100*TAAUncertainty0to100;


   sys+=(fPbPbSignalExtractionSig->Eval(pt)-fppSignalExtractionSig->Eval(pt))*
        (fPbPbSignalExtractionSig->Eval(pt)-fppSignalExtractionSig->Eval(pt));
   sys+=(fPbPbSignalExtractionBkg->Eval(pt)-fppSignalExtractionBkg->Eval(pt))*
   	(fPbPbSignalExtractionBkg->Eval(pt)-fppSignalExtractionBkg->Eval(pt));

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
   //sys+=ppSignalExtraction*ppSignalExtraction;
   sys+=ppDMesonSelection*ppDMesonSelection;
   sys+=ppBFeedDownCorrection*ppBFeedDownCorrection;
   sys+=ppMCPtSpectra*ppMCPtSpectra;
   
   return sqrt(sys);
}

// =============================================================================================================
// cross-section systematics for PbPb
// =============================================================================================================
float systematicsPbPb(double pt, double HLT=0)
{
   if (!initialized) initialization();
   double sys=0;
   sys+=(ppTrackingEfficiency*2)*(ppTrackingEfficiency*2);
   if (pt<20) sys+=PbPbNMBUncertainty*PbPbNMBUncertainty;
   	else  sys+=PbPbLumiUncertainty*PbPbLumiUncertainty;
   
   sys+=TAAUncertainty0to100*TAAUncertainty0to100;
   //sys+=PbPbSignalExtraction*PbPbSignalExtraction;
   sys+=PbPbDMesonSelection*PbPbDMesonSelection;
   sys+=PbPbBFeedDownCorrection*PbPbBFeedDownCorrection;
   sys+=PbPbMCPtSpectra*PbPbMCPtSpectra;
    
   return sqrt(sys);

}

