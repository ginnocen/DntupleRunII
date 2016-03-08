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

// =============================================================================================================
// RAA systematics
// =============================================================================================================
float systematicsForRAA(double pt, double HLT=0)
{
   double sys=0;
   sys+=ppLumiUncertainty*ppLumiUncertainty;
   //sys+=ppSignalExtraction*ppSignalExtraction;
   sys+=ppDMesonSelection*ppDMesonSelection;
   sys+=ppBFeedDownCorrection*ppBFeedDownCorrection;
   sys+=ppMCPtSpectra*ppMCPtSpectra;
   
   if (pt<20) sys+=PbPbNMBUncertainty*PbPbNMBUncertainty;
   	else  sys+=PbPbLumiUncertainty*PbPbLumiUncertainty;
   
   sys+=TAAUncertainty0to100*TAAUncertainty0to100;
   //sys+=PbPbSignalExtraction*PbPbSignalExtraction;
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
   return 0.2;

}


// =============================================================================================================
// cross-section systematics for pp
// =============================================================================================================
float systematicsPP(double pt, double HLT=0)
{
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

