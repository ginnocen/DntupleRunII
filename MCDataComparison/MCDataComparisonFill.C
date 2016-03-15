#include "uti.h"
#include "Dntuple.h"
#include "format.h"
using namespace std;

TString weight = "1";
TString seldata;
TString selmc;
TString collisionsystem;

//float signalWidth = 0.02;
float signalWidth = 0.03;
float sidebandLow = 0.06;
float sidebandHigh = 0.12;
//float wfactor = 1/3.;
float wfactor = signalWidth/(sidebandHigh-sidebandLow);

enum varType{
	_Dpt,
	_Dmass,
	_Ddtheta,
	_DlxyBS_DlxyBSErr,
	_Dy,
	_Dalpha,
	_Dchi2cl,
	_DsvpvDistance_DsvpvDisErr,
	_fine_Dy,
	_fine_Dalpha,
	_fine_Dchi2cl,
	_fine_DsvpvDistance_DsvpvDisErr,
	_varSize
};

struct varStruct{
	string var;
	string title;
	int nBin;
	double xMin;
	double xMax;
	int nBinSep;
	double* binSep;
	int binOpt;
	string plotName;
	string xtitle;
	string rfile;
	bool pthatWeight;
};

double _binPtpp[5] = {20, 25, 30, 35, 40};
double _binPtPbPb[5] = {20, 25, 30, 35, 40};
double _binChi[6] = {0.05,0.2,0.4,0.6,0.8,1.0};
double _binAlpha[6] = {0.00,0.005,0.01,0.02,0.03,0.12};
double _binDecay[7] = {4.,5.,6.,7.,8.,10,15};
double _binY[7] = {-1.,-0.6,-0.3,0.,0.3,0.6,1.};
double _dummy[1] = {0};

struct varStruct myVars[_varSize] = {
	{"Dpt",                       "Dpt",                             16, 20,   100.,  4, _binPtpp,   0, "Dpt",                            "GeV", "outputPlotPt.root",        true },
	{"Dmass",                     "Dmass",                           20, 1.7,  2.,    1, _dummy,     0, "Dmass",                          "GeV", "",                         false},
	{"Ddtheta",                   "Ddtheta",                         20, 0.,   0.2,   1, _dummy,     0, "Ddtheta",                        "",    "",                         false},
	{"DlxyBS/DlxyBSErr",          "DlxyBS_DlxyBSErr",                20, 0.,   1000., 1, _dummy,     0, "DlxyBS_DlxyBSErr",               "",    "",                         false},
	{"Dy",                        "Dy",                              20, -1,   1.,    6, _binY,      1, "Dy",                             "",    "outputPlotRapidity.root",  false},
	{"Dalpha",                    "Dalpha",                          20, 0.,   0.04,  5, _binAlpha,  1, "Dalpha",                         "",    "outputPlotDalpha.root",    false},
	{"Dchi2cl",                   "Dchi2cl",                         20, 0.05, 1.,    5, _binChi,    1, "Dchi2cl",                        "",    "outputPlotChi2.root",      false},
	{"DsvpvDistance/DsvpvDisErr", "DsvpvDistance_DsvpvDisErr",       20, 4.,   15.,   6, _binDecay,  1, "DsvpvDistance_DsvpvDisErr_fine", "",    "outputPlotDecay.root",     false},
	{"Dy",                        "_fine_Dy",                        20, -1,   1.,    1, _dummy,     0, "Dy_fine",                        "",    "outputPlotRapidity.root",  false},
	{"Dalpha",                    "_fine_Dalpha",                    20, 0.,   0.12,  1, _dummy,     0, "Dalpha_fine",                    "",    "outputPlotDalpha.root",    false},
	{"Dchi2cl",                   "_fine_Dchi2cl",                   20, 0.05, 1.,    1, _dummy,     0, "Dchi2cl_fine",                   "",    "outputPlotChi2.root",      false},
	{"DsvpvDistance/DsvpvDisErr", "_fine_DsvpvDistance_DsvpvDisErr", 20, 4.,   15.,   1, _dummy,     0, "DsvpvDistance_DsvpvDisErr_fine", "",    "outputPlotDecay.root",     false}
};

class HLTBranches
{
    public:
        int HLT_DmesonPPTrackingGlobal_Dpt15_v1;
        int HLT_DmesonPPTrackingGlobal_Dpt30_v1;
        int HLT_DmesonPPTrackingGlobal_Dpt50_v1;
		int HLT_HIDmesonHITrackingGlobal_Dpt20_v1;
		int HLT_HIDmesonHITrackingGlobal_Dpt40_v1;
		int HLT_HIDmesonHITrackingGlobal_Dpt60_v1;
		int HLT_L1MinimumBiasHF1OR_part1_v1;
		int HLT_L1MinimumBiasHF1OR_part2_v1;
		int HLT_L1MinimumBiasHF1OR_part3_v1;
		int HLT_L1MinimumBiasHF1OR_part4_v1;
		int HLT_L1MinimumBiasHF1OR_part5_v1;
		int HLT_L1MinimumBiasHF1OR_part6_v1;
		int HLT_L1MinimumBiasHF1OR_part7_v1;
		int HLT_L1MinimumBiasHF1OR_part8_v1;
		int HLT_L1MinimumBiasHF1OR_part9_v1;
		int HLT_L1MinimumBiasHF1OR_part10_v1;
		int HLT_L1MinimumBiasHF1OR_part11_v1;
		int HLT_L1MinimumBiasHF1OR_part12_v1;
		int HLT_L1MinimumBiasHF1OR_part13_v1;
		int HLT_L1MinimumBiasHF1OR_part14_v1;
		int HLT_L1MinimumBiasHF1OR_part15_v1;
		int HLT_L1MinimumBiasHF1OR_part16_v1;
		int HLT_L1MinimumBiasHF1OR_part17_v1;
		int HLT_L1MinimumBiasHF1OR_part18_v1;
		int HLT_L1MinimumBiasHF1OR_part19_v1;
		int HLT_HIL1MinimumBiasHF2AND_part1_v1;
		int HLT_HIL1MinimumBiasHF2AND_part2_v1;
		int HLT_HIL1MinimumBiasHF2AND_part3_v1;
        void setHLTBranches(TTree* t1, string ){
			if(dataNtype == "ppHF"){
        	    t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt15_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt15_v1);
    	        t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt30_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt30_v1);
	            t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt50_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt50_v1);
			}
            if(dataNtype == "PbPBHF"){
				t1->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt20_v1", &HLT_HIDmesonHITrackingGlobal_Dpt20_v1);
				t1->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt40_v1", &HLT_HIDmesonHITrackingGlobal_Dpt40_v1);
				t1->SetBranchAddress("HLT_HIDmesonHITrackingGlobal_Dpt60_v1", &HLT_HIDmesonHITrackingGlobal_Dpt60_v1);
			}
            if(dataNtype == "ppMB"){
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part1_v1", &HLT_L1MinimumBiasHF1OR_part1_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part2_v1", &HLT_L1MinimumBiasHF1OR_part2_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part3_v1", &HLT_L1MinimumBiasHF1OR_part3_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part4_v1", &HLT_L1MinimumBiasHF1OR_part4_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part5_v1", &HLT_L1MinimumBiasHF1OR_part5_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part6_v1", &HLT_L1MinimumBiasHF1OR_part6_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part7_v1", &HLT_L1MinimumBiasHF1OR_part7_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part8_v1", &HLT_L1MinimumBiasHF1OR_part8_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part9_v1", &HLT_L1MinimumBiasHF1OR_part9_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part10_v1", &HLT_L1MinimumBiasHF1OR_part10_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part11_v1", &HLT_L1MinimumBiasHF1OR_part11_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part12_v1", &HLT_L1MinimumBiasHF1OR_part12_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part13_v1", &HLT_L1MinimumBiasHF1OR_part13_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part14_v1", &HLT_L1MinimumBiasHF1OR_part14_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part15_v1", &HLT_L1MinimumBiasHF1OR_part15_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part16_v1", &HLT_L1MinimumBiasHF1OR_part16_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part17_v1", &HLT_L1MinimumBiasHF1OR_part17_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part18_v1", &HLT_L1MinimumBiasHF1OR_part18_v1);
				t1->SetBranchAddress("HLT_L1MinimumBiasHF1OR_part19_v1", &HLT_L1MinimumBiasHF1OR_part19_v1);
			}
            if(dataNtype == "PbPbMB"){
				t1->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part1_v1", &HLT_HIL1MinimumBiasHF2AND_part1_v1);
				t1->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part2_v1", &HLT_HIL1MinimumBiasHF2AND_part2_v1);
				t1->SetBranchAddress("HLT_HIL1MinimumBiasHF2AND_part3_v1", &HLT_HIL1MinimumBiasHF2AND_part3_v1);
			}
        };
};

//
//const int nBins=3; 
//float ptBinspp[nBins+1]={20, 40, 60, 100};
//float pa0[nBins] = {1, 1, 1};	
//float pa1[nBins] = {0, 0, 0};	
//float pa2[nBins] = {0, 0, 0};	
//float ptBinsPbPb[nBins+1]={20, 45, 70, 100};
const int nBins=1; 
float ptBinspp[nBins+1]={20, 40};
float pa0[nBins] = {1};	
float pa1[nBins] = {0};	
float pa2[nBins] = {0};	
float ptBinsPbPb[nBins+1]={20, 45};
float *ptBins;

void overlapTH1(TCanvas* c, TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, string xTitle, TH1D* hRatio, string rfile, int customize = -1, bool isPbPb = false);
void setBranches(TTree* t1, DntupleBranches &Dntuple);
void setGenBranches(TTree* t1, DntupleBranches &Dntuple);

void DoAnalysis(TFile* inf, TFile* infMC, TString outputfile, bool DoPtWeight, string dataNtype)
{

	if(!isPbPb) {
		ptBins = ptBinspp;
	}
	if(isPbPb) {
		ptBins = ptBinsPbPb;
		myVars[_Dpt].binSep = _binPtPbPb;
	}
	
	string wPrefix = "";
	if(!DoPtWeight){	
		wPrefix = "UnWeighted";
	}
	
	gStyle->SetTextSize(0.05);
	gStyle->SetTextFont(42);
	gStyle->SetPadRightMargin(0.043);
	gStyle->SetPadLeftMargin(0.18);
	gStyle->SetPadTopMargin(0.1);
	gStyle->SetPadBottomMargin(0.145);
	gStyle->SetTitleX(.0f);

	TTree* nt = (TTree*) inf->Get("ntDkpi");
	TTree* HltTree = (TTree*) inf->Get("ntHlt");
	
	TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
	TTree* ntGen = (TTree*)infMC->Get("ntGen");
	TTree* ntHi = (TTree*)infMC->Get("ntHi");
	//TTree* MCHltTree;
	//MCHltTree= (TTree*)infMC->Get("ntHlt");
	
	TCanvas *c[_varSize][nBins];
	TH1D *h1[_varSize][nBins];
	TH1D *h2[_varSize][nBins];
	TH1D *h3[_varSize][nBins];
	TH1D *h4[_varSize][nBins];
	TH1D *h11[_varSize][nBins];
	TH1D *h12[_varSize][nBins];
	TH1D *h13[_varSize][nBins];
	TH1D *h14[_varSize][nBins];
	TH1D *h21[_varSize][nBins];
	TH1D *h22[_varSize][nBins];
	TH1D *h23[_varSize][nBins];
	TH1D *hRatio[_varSize][nBins];
	TH1D *ptR[nBins];

	for (int p = 0; p < nBins; p++){
		//ptR[p] =  new TH1D((myVars[_Dpt].title+"Ratio"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[_Dpt].title.c_str(), myVars[_Dpt].nBin, myVars[_Dpt].xMin, myVars[_Dpt].xMax);
		ptR[p] =  new TH1D((myVars[_Dpt].title+"Ratio"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[_Dpt].title.c_str(), myVars[_Dpt].nBinSep, myVars[_Dpt].binSep);
		for (int i = 0 ; i < _varSize; i++){
			c[i][p] =  new TCanvas(("c"+myVars[i].title+Form("%d%s", p, wPrefix.c_str())).c_str(),"",600,600);
			if(myVars[i].binOpt==0){
				h1[i][p] =  new TH1D((myVars[i].title+"1"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h2[i][p] =  new TH1D((myVars[i].title+"2"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h3[i][p] =  new TH1D((myVars[i].title+"3"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h4[i][p] =  new TH1D((myVars[i].title+"4"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h11[i][p] = new TH1D((myVars[i].title+"11"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h12[i][p] = new TH1D((myVars[i].title+"12"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h13[i][p] = new TH1D((myVars[i].title+"13"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h14[i][p] = new TH1D((myVars[i].title+"14"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h21[i][p] = new TH1D((myVars[i].title+"21"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h22[i][p] = new TH1D((myVars[i].title+"22"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				h23[i][p] = new TH1D((myVars[i].title+"23"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
				hRatio[i][p] = new TH1D((myVars[i].title+"_ratio"+Form("%d%s", p, wPrefix.c_str())).c_str(), (myVars[i].title+"_ratio").c_str(), myVars[i].nBin, myVars[i].xMin, myVars[i].xMax);
			}
            if(myVars[i].binOpt==1){
				h1[i][p] =  new TH1D((myVars[i].title+"1"+Form("%d%s",  p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h2[i][p] =  new TH1D((myVars[i].title+"2"+Form("%d%s",  p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h3[i][p] =  new TH1D((myVars[i].title+"3"+Form("%d%s",  p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h4[i][p] =  new TH1D((myVars[i].title+"4"+Form("%d%s",  p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h11[i][p] = new TH1D((myVars[i].title+"11"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h12[i][p] = new TH1D((myVars[i].title+"12"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h13[i][p] = new TH1D((myVars[i].title+"13"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h14[i][p] = new TH1D((myVars[i].title+"14"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h21[i][p] = new TH1D((myVars[i].title+"21"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h22[i][p] = new TH1D((myVars[i].title+"22"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h23[i][p] = new TH1D((myVars[i].title+"23"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				hRatio[i][p] = new TH1D((myVars[i].title+"_ratio"+Form("%d%s", p, wPrefix.c_str())).c_str(), (myVars[i].title+"_ratio").c_str(), myVars[i].nBinSep, myVars[i].binSep);
			}
		}
	}
	TH1D *hMCMass =    new TH1D(Form("MCDmass%s", wPrefix.c_str()), "MCDmass", 100, 1.7, 2);
	TH1D *hMCMassGM =  new TH1D(Form("MCDmassGM%s", wPrefix.c_str()), "MCDmassGM", 100, 1.7, 2);
	TH1D *hMCMassGMW = new TH1D(Form("MCDmassGMW%s", wPrefix.c_str()), "MCDmassGMW", 100, 1.7, 2);
	TH1D *hDataMass =  new TH1D(Form("DataDmass%s", wPrefix.c_str()), "DataDmass", 100, 1.7, 2);
	TH1D *hMassRatio = new TH1D(Form("DmassRatio%s", wPrefix.c_str()), "DmassRatio", 100, 1.7, 2);
	TH1D *hempty =     new TH1D(Form("empty%s", wPrefix.c_str()), "empty", 100, 1.7, 2);
    TCanvas* cMass =   new TCanvas(Form("cMass%s", wPrefix.c_str()),"",600,600);

	DntupleBranches Dntuple;
	HLTBranches HLTBh;

	setBranches(ntMC, Dntuple);
    ntMC->SetBranchAddress("Dgen" ,Dntuple.Dgen);

	float pthatweight;
	ntHi->SetBranchAddress("pthatweight" ,&pthatweight);
	float ptWeight = 1;
	int nEntries = ntMC->GetEntries();
//	nEntries = 1000000;
	for(int i=0;i<nEntries;i++){
		ntMC->GetEntry(i);
		ntHi->GetEntry(i);
		//cout<<Dntuple.Dsize<<endl;
		//cout<<HLTBh.HLT_DmesonPPTrackingGlobal_Dpt15_v1<<endl;
		for (int s = 0; s < Dntuple.Dsize; s++){
			//cout<<Dntuple.Dmass[s]<<endl;
			//printf("%f, %f\n", Dntuple.Dtrk1Pt[s], Dntuple.Dtrk2Pt[s]);
			bool boolCut = false;
			bool boolGenCut = false;
			bool boolHLTCut = false;
			bool boolSignalRG = false;
			bool boolSidebandRG = false;
			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>2.0&&Dntuple.Dtrk2Pt[s]>2.0
				&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.5&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>2.5
				&&Dntuple.Dchi2cl[s]>0.05&&Dntuple.Dalpha[s]<0.12
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.1&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.1
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&Dntuple.Dtrk1Algo[s]>3&&Dntuple.Dtrk1Algo[s]<8&&Dntuple.Dtrk2Algo[s]>3&&Dntuple.Dtrk2Algo[s]<8
				&&(Dntuple.Dtrk1PixelHit[s]+Dntuple.Dtrk1StripHit[s])>=11
				&&(Dntuple.Dtrk2PixelHit[s]+Dntuple.Dtrk2StripHit[s])>=11
				&&(Dntuple.Dtrk1Chi2ndf[s]/(Dntuple.Dtrk1nStripLayer[s]+Dntuple.Dtrk1nPixelLayer[s])<0.15)&&(Dntuple.Dtrk2Chi2ndf[s]/(Dntuple.Dtrk2nStripLayer[s]+Dntuple.Dtrk2nPixelLayer[s])<0.15)
				&&(dataNtype == "ppHF")
			){
				boolCut = true;
			}
			if (&&Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>8.5&&Dntuple.Dtrk2Pt[s]>8.5
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.1&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.1
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&(Dntuple.Dtrk1PixelHit[s]+Dntuple.Dtrk1StripHit[s])>=11
				&&(Dntuple.Dtrk2PixelHit[s]+Dntuple.Dtrk2StripHit[s])>=11
				&&(Dntuple.Dtrk1Chi2ndf[s]/(Dntuple.Dtrk1nStripLayer[s]+Dntuple.Dtrk1nPixelLayer[s])<0.15)&&(Dntuple.Dtrk2Chi2ndf[s]/(Dntuple.Dtrk2nStripLayer[s]+Dntuple.Dtrk2nPixelLayer[s])<0.15)
				&&((Dntuple.Dpt[s]>2 &&Dntuple.Dpt[s]<4 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.86&&Dntuple.Dchi2cl[s]>0.224)
				 ||(Dntuple.Dpt[s]>4 &&Dntuple.Dpt[s]<5 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.46&&Dntuple.Dchi2cl[s]>0.196)
				 ||(Dntuple.Dpt[s]>5 &&Dntuple.Dpt[s]<6 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.86&&Dntuple.Dchi2cl[s]>0.170)
				 ||(Dntuple.Dpt[s]>6 &&Dntuple.Dpt[s]<8 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.54&&Dntuple.Dchi2cl[s]>0.125)
				 ||(Dntuple.Dpt[s]>8 &&Dntuple.Dpt[s]<10&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.42&&Dntuple.Dchi2cl[s]>0.091)
				 ||(Dntuple.Dpt[s]>10&&Dntuple.Dpt[s]<15&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.06&&Dntuple.Dchi2cl[s]>0.069)
				 ||(Dntuple.Dpt[s]>15&&Dntuple.Dpt[s]<20&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.71&&Dntuple.Dchi2cl[s]>0.056)
				 ||(Dntuple.Dpt[s]>20&&Dntuple.Dpt[s]<25&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.25&&Dntuple.Dchi2cl[s]>0.054)
				 ||(Dntuple.Dpt[s]>25                   &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>2.97&&Dntuple.Dchi2cl[s]>0.050))
				&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5&&Dntuple.Dalpha[s]<0.12
				&&(dataNtype == "PbPbHF")
			){
				boolCut = true;
			}

			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>1.0&&Dntuple.Dtrk2Pt[s]>1.0
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.3&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.3
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.5&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5&&Dntuple.Dchi2cl[s]>0.05&&Dntuple.Dalpha[s]<0.12
				&&(dataNtype == "ppMB")
			){
				boolCut = true;
			}

			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>1.0&&Dntuple.Dtrk2Pt[s]>1.0
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.3&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.3
				&&abs(Dntuple.Dtrk1Eta[s])<1.5&&abs(Dntuple.Dtrk2Eta[s])<1.5
				&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5&&Dntuple.Dalpha[s]<0.12
				&&((Dntuple.Dpt[s]>2 &&Dntuple.Dpt[s]<4 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.86 &&Dntuple.Dchi2cl[s]>0.224)
				 ||(Dntuple.Dpt[s]>4 &&Dntuple.Dpt[s]<5 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.46 &&Dntuple.Dchi2cl[s]>0.196)
				 ||(Dntuple.Dpt[s]>5 &&Dntuple.Dpt[s]<6 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.86 &&Dntuple.Dchi2cl[s]>0.170)
				 ||(Dntuple.Dpt[s]>6 &&Dntuple.Dpt[s]<8 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.54 &&Dntuple.Dchi2cl[s]>0.125)
				 ||(Dntuple.Dpt[s]>8 &&Dntuple.Dpt[s]<10&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.42 &&Dntuple.Dchi2cl[s]>0.091)
				 ||(Dntuple.Dpt[s]>10&&Dntuple.Dpt[s]<15&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.06 &&Dntuple.Dchi2cl[s]>0.069)
				 ||(Dntuple.Dpt[s]>15&&Dntuple.Dpt[s]<20&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.71 &&Dntuple.Dchi2cl[s]>0.056)
				 ||(Dntuple.Dpt[s]>20&&Dntuple.Dpt[s]<25&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.25 &&Dntuple.Dchi2cl[s]>0.054)
				 ||(Dntuple.Dpt[s]>25&&                   (Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>2.97 &&Dntuple.Dchi2cl[s]>0.050))
				&&(dataNtype == "PbPbMB")
			){
				boolCut = true;
			}

			if (!boolCut) continue;

			if (Dntuple.Dgen[s]==23333){
				boolGenCut = true;
			}
			if (fabs(Dntuple.Dmass[s]-1.8648)<signalWidth){
  	          boolSignalRG = true;
			}
			if (fabs(Dntuple.Dmass[s]-1.8648)>sidebandLow&fabs(Dntuple.Dmass[s]-1.8648)<sidebandHigh){
            	boolSidebandRG = true;
			}
		
			if(Dntuple.Dpt[s] > 15 && Dntuple.Dpt[s] < 40){
				hMCMass->Fill(Dntuple.Dmass[s]);
				if(boolGenCut){
					hMCMassGM->Fill(Dntuple.Dmass[s]);
					hMCMassGMW->Fill(Dntuple.Dmass[s], pthatweight);
				}
			}
			for (int p = 0; p < nBins; p++){
				ptWeight = pa0[p] + pa1[p]*Dntuple.Dpt[s] + pa2[p]*Dntuple.Dpt[s]*Dntuple.Dpt[s];
				if(Dntuple.Dpt[s]>ptBins[p]&&Dntuple.Dpt[s]<ptBins[p+1]){
					if(boolSignalRG){
						h1 [_Dpt][p]->Fill(Dntuple.Dpt[s], ptWeight);
						h11[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
						h1 [_Dmass][p]->Fill(Dntuple.Dmass[s], ptWeight);
						h11[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
						h1 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], ptWeight);
						h11[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
						h1 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], ptWeight);
						h11[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
						h1 [_Dy][p]->Fill(Dntuple.Dy[s], ptWeight);
						h11[_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
						h1 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
						h11[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h1 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
						h11[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h1 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
						h11[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						h1 [_fine_Dy][p]->Fill(Dntuple.Dy[s], ptWeight);
						h11[_fine_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
						h1 [_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
						h11[_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h1 [_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
						h11[_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h1 [_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
						h11[_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						if(boolGenCut){
							h4 [_Dpt][p]->Fill(Dntuple.Dpt[s], ptWeight);
							h14[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
							h4 [_Dmass][p]->Fill(Dntuple.Dmass[s], ptWeight);
							h14[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
							h4 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], ptWeight);
							h14[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
							h4 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], ptWeight);
							h14[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
							h4 [_Dy][p]->Fill(Dntuple.Dy[s], ptWeight);
							h14[_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
							h4 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
							h14[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
							h4 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
							h14[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
							h4 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
							h14[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
							h4 [_fine_Dy][p]->Fill(Dntuple.Dy[s], ptWeight);
							h14[_fine_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
							h4 [_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
							h14[_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
							h4 [_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
							h14[_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
							h4 [_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
							h14[_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						}
					}
					if(boolSidebandRG){
						h2 [_Dpt][p]->Fill(Dntuple.Dpt[s], ptWeight);
						h12[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
						h2 [_Dmass][p]->Fill(Dntuple.Dmass[s], ptWeight);
						h12[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
						h2 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], ptWeight);
						h12[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
						h2 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], ptWeight);
						h12[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
						h2 [_Dy][p]->Fill(Dntuple.Dy[s], ptWeight);
						h12[_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
						h2 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
						h12[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h2 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
						h12[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h2 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
						h12[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						h2 [_fine_Dy][p]->Fill(Dntuple.Dy[s], ptWeight);
						h12[_fine_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
						h2 [_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], ptWeight);
						h12[_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h2 [_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], ptWeight);
						h12[_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h2 [_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], ptWeight);
						h12[_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
					}
				}
			}
		}
	}

	setBranches(nt, Dntuple);
	HLTBh.setHLTBranches(HltTree, dataNtype);
	ptWeight = 1;
	nEntries = nt->GetEntries();
//	nEntries = 100000;
	for(int i=0;i<nEntries;i++){
		nt->GetEntry(i);
		HltTree->GetEntry(i);
		for (int s = 0; s < Dntuple.Dsize; s++){
			bool boolCut = false;
			bool boolGenCut = false;
			bool boolHLTCut = false;
			bool boolSignalRG = false;
			bool boolSidebandRG = false;
			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>2.0&&Dntuple.Dtrk2Pt[s]>2.0
				&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.5&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>2.5
				&&Dntuple.Dchi2cl[s]>0.05&&Dntuple.Dalpha[s]<0.12
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.1&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.1
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&Dntuple.Dtrk1Algo[s]>3&&Dntuple.Dtrk1Algo[s]<8&&Dntuple.Dtrk2Algo[s]>3&&Dntuple.Dtrk2Algo[s]<8
				&&(Dntuple.Dtrk1PixelHit[s]+Dntuple.Dtrk1StripHit[s])>=11
				&&(Dntuple.Dtrk2PixelHit[s]+Dntuple.Dtrk2StripHit[s])>=11
				&&(Dntuple.Dtrk1Chi2ndf[s]/(Dntuple.Dtrk1nStripLayer[s]+Dntuple.Dtrk1nPixelLayer[s])<0.15)&&(Dntuple.Dtrk2Chi2ndf[s]/(Dntuple.Dtrk2nStripLayer[s]+Dntuple.Dtrk2nPixelLayer[s])<0.15)
				&&(dataNtype == "ppHF")
			){
				boolCut = true;
			}
			if (&&Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>8.5&&Dntuple.Dtrk2Pt[s]>8.5
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.1&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.1
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&(Dntuple.Dtrk1PixelHit[s]+Dntuple.Dtrk1StripHit[s])>=11
				&&(Dntuple.Dtrk2PixelHit[s]+Dntuple.Dtrk2StripHit[s])>=11
				&&(Dntuple.Dtrk1Chi2ndf[s]/(Dntuple.Dtrk1nStripLayer[s]+Dntuple.Dtrk1nPixelLayer[s])<0.15)&&(Dntuple.Dtrk2Chi2ndf[s]/(Dntuple.Dtrk2nStripLayer[s]+Dntuple.Dtrk2nPixelLayer[s])<0.15)
				&&((Dntuple.Dpt[s]>2 &&Dntuple.Dpt[s]<4 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.86&&Dntuple.Dchi2cl[s]>0.224)
				 ||(Dntuple.Dpt[s]>4 &&Dntuple.Dpt[s]<5 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.46&&Dntuple.Dchi2cl[s]>0.196)
				 ||(Dntuple.Dpt[s]>5 &&Dntuple.Dpt[s]<6 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.86&&Dntuple.Dchi2cl[s]>0.170)
				 ||(Dntuple.Dpt[s]>6 &&Dntuple.Dpt[s]<8 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.54&&Dntuple.Dchi2cl[s]>0.125)
				 ||(Dntuple.Dpt[s]>8 &&Dntuple.Dpt[s]<10&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.42&&Dntuple.Dchi2cl[s]>0.091)
				 ||(Dntuple.Dpt[s]>10&&Dntuple.Dpt[s]<15&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.06&&Dntuple.Dchi2cl[s]>0.069)
				 ||(Dntuple.Dpt[s]>15&&Dntuple.Dpt[s]<20&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.71&&Dntuple.Dchi2cl[s]>0.056)
				 ||(Dntuple.Dpt[s]>20&&Dntuple.Dpt[s]<25&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.25&&Dntuple.Dchi2cl[s]>0.054)
				 ||(Dntuple.Dpt[s]>25                   &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>2.97&&Dntuple.Dchi2cl[s]>0.050))
				&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5&&Dntuple.Dalpha[s]<0.12
				&&(dataNtype == "PbPbHF")
			){
				boolCut = true;
			}

			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>1.0&&Dntuple.Dtrk2Pt[s]>1.0
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.3&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.3
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.5&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5&&Dntuple.Dchi2cl[s]>0.05&&Dntuple.Dalpha[s]<0.12
				&&(dataNtype == "ppMB")
			){
				boolCut = true;
			}

			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>1.0&&Dntuple.Dtrk2Pt[s]>1.0
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.3&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.3
				&&abs(Dntuple.Dtrk1Eta[s])<1.5&&abs(Dntuple.Dtrk2Eta[s])<1.5
				&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5&&Dntuple.Dalpha[s]<0.12
				&&((Dntuple.Dpt[s]>2 &&Dntuple.Dpt[s]<4 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.86 &&Dntuple.Dchi2cl[s]>0.224)
				 ||(Dntuple.Dpt[s]>4 &&Dntuple.Dpt[s]<5 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.46 &&Dntuple.Dchi2cl[s]>0.196)
				 ||(Dntuple.Dpt[s]>5 &&Dntuple.Dpt[s]<6 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.86 &&Dntuple.Dchi2cl[s]>0.170)
				 ||(Dntuple.Dpt[s]>6 &&Dntuple.Dpt[s]<8 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.54 &&Dntuple.Dchi2cl[s]>0.125)
				 ||(Dntuple.Dpt[s]>8 &&Dntuple.Dpt[s]<10&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.42 &&Dntuple.Dchi2cl[s]>0.091)
				 ||(Dntuple.Dpt[s]>10&&Dntuple.Dpt[s]<15&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>4.06 &&Dntuple.Dchi2cl[s]>0.069)
				 ||(Dntuple.Dpt[s]>15&&Dntuple.Dpt[s]<20&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.71 &&Dntuple.Dchi2cl[s]>0.056)
				 ||(Dntuple.Dpt[s]>20&&Dntuple.Dpt[s]<25&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.25 &&Dntuple.Dchi2cl[s]>0.054)
				 ||(Dntuple.Dpt[s]>25&&                   (Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>2.97 &&Dntuple.Dchi2cl[s]>0.050))
				&&(dataNtype == "PbPbMB")
			){
				boolCut = true;
			}
			if (!boolCut) continue;

			if (((HLTBh.HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dntuple.Dpt[s]>15&&Dntuple.Dpt[s]<40)
				||(HLTBh.HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dntuple.Dpt[s]>40&&Dntuple.Dpt[s]<60)
				||(HLTBh.HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dntuple.Dpt[s]>60))
				&&(dataNtype == "ppHF")
			){
				boolHLTCut = true;
			}
			if(((HLTBh.HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dntuple.Dpt[s]>20&&Dntuple.Dpt[s]<45)
				||(HLTBh.HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dntuple.Dpt[s]>45&&Dntuple.Dpt[s]<70)
				||(HLTBh.HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dntuple.Dpt[s]>70))
				&&(dataNtype == "PbPbHF")
			){
				boolHLTCut = true;
			}
			if((HLTBh.HLT_L1MinimumBiasHF1OR_part1_v1
				||HLTBh.HLT_L1MinimumBiasHF1OR_part2_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part3_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part4_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part5_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part6_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part7_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part8_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part9_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part10_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part11_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part12_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part13_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part14_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part15_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part16_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part17_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part18_v1
			 	||HLTBh.HLT_L1MinimumBiasHF1OR_part19_v1)
				&&(dataNtype == "ppMB")
			){
				boolHLTCut = true;
			}

			if ((HLTBh.HLT_HIL1MinimumBiasHF2AND_part1_v1
				||HLTBh.HLT_HIL1MinimumBiasHF2AND_part2_v1
				||HLTBh.HLT_HIL1MinimumBiasHF2AND_part3_v1)
				&&(dataNtype == "ppMB")
			){
				boolHLTCut = true;
			}
			
			if (!boolHLTCut) continue;

			if (fabs(Dntuple.Dmass[s]-1.8648)<signalWidth){
  	          boolSignalRG = true;
			}
			if (fabs(Dntuple.Dmass[s]-1.8648)>sidebandLow&fabs(Dntuple.Dmass[s]-1.8648)<sidebandHigh){
            	boolSidebandRG = true;
			}
			hDataMass->Fill(Dntuple.Dmass[s]);
			for (int p = 0; p < nBins; p++){
				if(Dntuple.Dpt[s]>ptBins[p]&&Dntuple.Dpt[s]<ptBins[p+1]){
					if(boolSignalRG){
						h21 [_Dpt][p]->Fill(Dntuple.Dpt[s]);
						h21 [_Dmass][p]->Fill(Dntuple.Dmass[s]);
						h21 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s]);
						h21 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s]);
						h21 [_Dy][p]->Fill(Dntuple.Dy[s]);
						h21 [_Dalpha][p]->Fill(Dntuple.Dalpha[s]);
						h21 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s]);
						h21 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s]);
						h21 [_fine_Dy][p]->Fill(Dntuple.Dy[s]);
						h21 [_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s]);
						h21 [_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s]);
						h21 [_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s]);
					}
					if(boolSidebandRG){
						h22 [_Dpt][p]->Fill(Dntuple.Dpt[s]);
						h22 [_Dmass][p]->Fill(Dntuple.Dmass[s]);
						h22 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s]);
						h22 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s]);
						h22 [_Dy][p]->Fill(Dntuple.Dy[s]);
						h22 [_Dalpha][p]->Fill(Dntuple.Dalpha[s]);
						h22 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s]);
						h22 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s]);
						h22 [_fine_Dy][p]->Fill(Dntuple.Dy[s]);
						h22 [_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s]);
						h22 [_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s]);
						h22 [_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s]);
					}
				}
			}
		}
	}

    for (int i = 0 ; i < _varSize; i++){
	for (int p = 0 ; p < nBins; p++){
		for(int bin = 1; bin < h1[i][p]->GetNbinsX()+1; bin++){
			h1[i][p]  ->SetBinContent(bin, h1[i][p] ->GetBinContent(bin)/h1[i][p] ->GetBinWidth(bin));
			h2[i][p]  ->SetBinContent(bin, h2[i][p] ->GetBinContent(bin)/h2[i][p] ->GetBinWidth(bin));
			h3[i][p]  ->SetBinContent(bin, h3[i][p] ->GetBinContent(bin)/h3[i][p] ->GetBinWidth(bin));
			h4[i][p]  ->SetBinContent(bin, h4[i][p] ->GetBinContent(bin)/h4[i][p] ->GetBinWidth(bin));
			h11[i][p] ->SetBinContent(bin, h11[i][p]->GetBinContent(bin)/h11[i][p]->GetBinWidth(bin));
			h12[i][p] ->SetBinContent(bin, h12[i][p]->GetBinContent(bin)/h12[i][p]->GetBinWidth(bin));
			h13[i][p] ->SetBinContent(bin, h13[i][p]->GetBinContent(bin)/h13[i][p]->GetBinWidth(bin));
			h14[i][p] ->SetBinContent(bin, h14[i][p]->GetBinContent(bin)/h14[i][p]->GetBinWidth(bin));
			h21[i][p] ->SetBinContent(bin, h21[i][p]->GetBinContent(bin)/h21[i][p]->GetBinWidth(bin));
			h22[i][p] ->SetBinContent(bin, h22[i][p]->GetBinContent(bin)/h22[i][p]->GetBinWidth(bin));
			h23[i][p] ->SetBinContent(bin, h23[i][p]->GetBinContent(bin)/h23[i][p]->GetBinWidth(bin));
		}
		h3[i][p] = (TH1D*)h1[i][p]->Clone();
		h3[i][p]->Add(h2[i][p],-wfactor);

		h13[i][p] = (TH1D*)h11[i][p]->Clone();
		h13[i][p]->Add(h12[i][p],-wfactor);

		h23[i][p] = (TH1D*)h21[i][p]->Clone();
		h23[i][p]->Add(h22[i][p],-wfactor);
		if(myVars[i].pthatWeight == false){
			overlapTH1(c[i][p], h4[i][p],  h3[i][p],  h23[i][p], h21[i][p], myVars[i].xtitle, hRatio[i][p], myVars[i].rfile, -1, isPbPb);
		}
		else{
			overlapTH1(c[i][p], h14[i][p], h13[i][p], h23[i][p], h21[i][p], myVars[i].xtitle, hRatio[i][p], myVars[i].rfile, -1, isPbPb);
		}
		if(!isPbPb){
			c[i][p]->SaveAs(("plotsFill_pp/"+myVars[i].plotName+Form("ptBin%d%s", p, wPrefix.c_str())+".pdf").c_str());
		}
		if(isPbPb){
			c[i][p]->SaveAs(("plotsFill_PbPb/"+myVars[i].plotName+Form("ptBin%d%s", p, wPrefix.c_str())+".pdf").c_str());
		}
		c[i][p]->SaveAs(("temp/"+myVars[i].plotName+Form("ptBin%d%s", p, wPrefix.c_str())+".C").c_str());
	}}
	if (DoPtWeight){
	    overlapTH1(cMass, hMCMassGM, hMCMassGMW, hMCMass, hDataMass, "Dmass", hMassRatio, "", 1, isPbPb);
		if(!isPbPb)	cMass->SaveAs("plotsFill_pp/mass.pdf");
		if(isPbPb)	cMass->SaveAs("plotsFill_PbPb/mass.pdf");
	}

	if (!DoPtWeight){
		for (int p = 0; p < nBins; p++){
			h23[_Dpt][p]->Sumw2();
			h13[_Dpt][p]->Sumw2();
			h23[_Dpt][p]->Scale(1/h23[_Dpt][p]->Integral());
			h13[_Dpt][p]->Scale(1/h13[_Dpt][p]->Integral());
			ptR[p] = (TH1D*)h23[_Dpt][p]->Clone();
			ptR[p]->Divide(h13[_Dpt][p]);
			TCanvas* cptR =  new TCanvas(Form("cptR%d", p),"",600,600);
	  		TF1* f = new TF1(Form("f%d", p),"[0]+[1]*x+[2]*x*x", ptBins[p], ptBins[p+1]);
			f->SetParameter(0,ptR[p]->GetMaximum()*0.8);
			f->SetParLimits(0,0,ptR[p]->GetMaximum());
			f->SetParameter(1,0.1);
			f->SetParLimits(1,-10,10);
			f->SetParameter(2,0.1);
			f->SetParLimits(1,-10,10);
			ptR[p]->Fit(Form("f%d",p),"Lq","",ptBins[p], ptBins[p+1]);
			ptR[p]->Fit(Form("f%d",p),"Lq","",ptBins[p], ptBins[p+1]);
			f->SetLineColor(kRed);
			f->SetLineWidth(3);
			ptR[p]->Draw("p");
			f->Draw("l same ");
			if(!isPbPb) cptR->SaveAs(Form("plotsFill_pp/ptRptBin%d.pdf",p));
			if(isPbPb) cptR->SaveAs(Form("plotsFill_PbPb/ptRptBin%d.pdf",p));
			pa0[p] = f->GetParameter(0);
			pa1[p] = f->GetParameter(1);
			pa2[p] = f->GetParameter(2);
			std::cout<<f->GetParameter(0)<<endl;
			std::cout<<f->GetParameter(1)<<endl;
			std::cout<<f->GetParameter(2)<<endl;
		}
	}

}

void MCDataComparisonFill(TString inputdata="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root", TString inputmc="/afs/cern.ch/work/w/wangj/public/Dmeson/ntD_20151110_DfinderMC_20151110_EvtMatching_Pythia_D0pt15p0_Pthat15_TuneZ2_5020GeV_GENSIM_75x_1015_20151110_ppGlobaTrackingPPmenuHFlowpuv11_MBseed_twang-Pythia_1107.root", TString outputfile="mytest.root"){
	//inputmc  ="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root";
	inputmc  ="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root";
	inputdata="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skimmed.root";

	TFile* infMC  = new TFile(inputmc.Data());
	TFile* inf    = new TFile(inputdata.Data());
	
	DoAnalysis(inf, infMC, outputfile, false, "ppHF");
	DoAnalysis(inf, infMC, outputfile, true, "ppHF");

	//PbPb
	//inputmc = "/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root";
	inputmc = "/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_promptNnonprompt_D0_dPt1tkPt1_pthatweight.root";
	inputdata="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2_skimmed.root";
	inf = new TFile(inputdata.Data());
	infMC = new TFile(inputmc.Data());
//	DoAnalysis(inf, infMC, outputfile, false, "PbPbHF");
//	DoAnalysis(inf, infMC, outputfile, true, "PbPbHF");
}
	
void overlapTH1(TCanvas* c, TH1D* h1, TH1D* h2, TH1D*h3, TH1D* h4, string xTitle, TH1D* hRatio, string rfile, int customize, bool isPbPb){
	c->cd();
	h1->GetXaxis()->SetTitle(xTitle.c_str());
	h1->Sumw2();
	h2->Sumw2();
	h3->Sumw2();
	h4->Sumw2();
	h1->Scale(1/h1->Integral());
	h2->Scale(1/h2->Integral());
	h3->Scale(1/h3->Integral());
	h4->Scale(1/h4->Integral());
//	h1->Scale(1/h1->GetEntries());
//	h2->Scale(1/h2->GetEntries());
//	h3->Scale(1/h3->GetEntries());
//	h4->Scale(1/h4->GetEntries());
	h1->SetMaximum(max(h1->GetMaximum(), max(h2->GetMaximum(), max(h3->GetMaximum(), h4->GetMaximum())))*1.8);
//	h1->SetMaximum(max(h1->GetMaximum(), max(h3->GetMaximum(), h4->GetMaximum()))*1.2);
//	h1->SetMinimum(h3->GetMinimum()*1.2);
	h1->SetMinimum(0);
	h1->SetMarkerSize(2);
	h2->SetMarkerSize(0.8);
	h3->SetMarkerSize(0.8);
	h1->SetMarkerColor(2);
	h1->SetMarkerStyle(21);
	h2->SetMarkerColor(kGreen-4);
	h3->SetMarkerColor(kAzure+8);
	h4->SetMarkerColor(kMagenta+3);
	h1->SetLineWidth(3);
	h2->SetLineWidth(3);
	h3->SetLineWidth(3);
	h4->SetLineWidth(3);
	h1->SetLineColor(2);
	h2->SetLineColor(kGreen-4);
	h3->SetLineColor(kAzure+8);
	h4->SetLineColor(kMagenta+3);
	if (customize == 1){
		h1->Draw("Hist e");
		h2->Draw("same pe");
		h3->Draw("same pe");
		h4->Draw("same pe");
		TLegend* leg = myLegend(0.5, 0.65, 0.86, 0.86);
  		leg->SetTextFont(42);
  		leg->SetTextSize(0.045);
		leg->AddEntry(h1, "MC gen matched", "l");
		leg->AddEntry(h2, "MC gen matched weighted", "p");
		leg->AddEntry(h3, "MC no gen matched", "p");
		leg->AddEntry(h4, "data", "p");
		leg->Draw();
	}
	else{
    	hRatio = (TH1D*)h3->Clone();
		hRatio->Divide(h2);
		hRatio->GetXaxis()->SetTitle(xTitle.c_str());
		hRatio->GetYaxis()->SetTitle("Data/MC");
		hRatio->SetMaximum(2.5);
		hRatio->SetMinimum(0.2);
		TPad* pad1;
		static int pcount = 0;
        pad1 = new TPad(Form("p%d", pcount), Form("p%d", pcount), 0.01, 0.35, 0.99, 0.99); pcount++;
		pad1->Draw();
		pad1->cd();
		h1->Draw("pe");
//		h2->Draw("same pe");
//		h3->Draw("same pe");
//		h4->Draw("same pe");
		h2->Draw("same hist e");
		h3->Draw("same hist e");
		TLegend* leg = myLegend(0.5, 0.65, 0.86, 0.86);
  		leg->SetTextFont(42);
  		leg->SetTextSize(0.045);
		leg->AddEntry(h1, "MC gen matched", "p");
		leg->AddEntry(h2, "MC sideband sub.", "l");
		leg->AddEntry(h3, "data sideband sub.", "l");
//		leg->AddEntry(h4, "data signal region", "p");
		leg->Draw();
		TPad* pad2;
        pad2 = new TPad(Form("p%d", pcount), Form("p%d", pcount), 0.01, 0.01, 0.99, 0.35);
	    c->cd();
		pad2->Draw();
		pad2->cd();
		hRatio->Draw("hist e");
		TFile* rfin;
		TH1D* dataIn;
		TH1D* MCIn;
		TH1D* ratioIn;
		if(rfile!=""){
			if(!isPbPb) rfin = new TFile(("fitExtract_pp/"+rfile).c_str());
			if(isPbPb) rfin = new TFile(("fitExtract_PbPb/"+rfile).c_str());
			dataIn = (TH1D*)rfin->Get("hPt");
			MCIn = (TH1D*)rfin->Get("hPtMCTot");
			TH1D* ratioIn = (TH1D*)rfin->Get("hRatio");
	        pad1->cd();
			dataIn->SetMarkerSize(2);
			MCIn->SetMarkerSize(2);
			dataIn->SetLineWidth(0);
			MCIn->SetLineWidth(0);
			dataIn->SetMarkerStyle(34);
			MCIn->SetMarkerStyle(34);
			//dataIn->SetMarkerStyle(29);
			//MCIn->SetMarkerStyle(29);
			MCIn->SetMarkerColor(kGreen-2);
			MCIn->SetLineColor(kGreen-2);
			dataIn->SetMarkerColor(kBlue-4);
			dataIn->SetLineColor(kBlue-4);
			MCIn->Draw("same pe");
			dataIn->Draw("same pe");
			if(!isPbPb){
		        leg->AddEntry(MCIn, Form("MC fit Dpt=%.0f~%.0f", ptBinspp[0], ptBinspp[1]), "p");
	    	    leg->AddEntry(dataIn, Form("data fit Dpt=%.0f~%.0f", ptBinspp[0], ptBinspp[1]), "p");
			}
			if(isPbPb){
		        leg->AddEntry(MCIn, Form("MC fit Dpt=%.0f~%.0f", ptBinsPbPb[0], ptBinsPbPb[1]), "p");
	    	    leg->AddEntry(dataIn, Form("data fit Dpt=%.0f~%.0f", ptBinsPbPb[0], ptBinsPbPb[1]), "p");
			}
			leg->Draw();
	        pad2->cd();
			ratioIn->SetLineWidth(0);
            ratioIn->SetMarkerStyle(34);
			ratioIn->SetMarkerSize(2);
			//ratioIn->Draw("same pe");
			ratioIn->Draw("same pe");
			TLegend* leg2 = myLegend(0.5, 0.65, 0.86, 0.86);
  			leg2->SetTextFont(42);
  			leg2->SetTextSize(0.085);
			leg2->AddEntry(hRatio, "ratio sideband", "p");
			leg2->AddEntry(ratioIn, "ratio fit", "p");
			leg2->Draw();
		}
	}
}

void clean0(TH1D* h){
  for (int i=1;i<=h->GetNbinsX();i++)
    {
      if(h->GetBinContent(i)==0) h->SetBinError(i,1);
    }
}

int main(int argc, char *argv[])
{
  if((argc != 4))
  {
    std::cout << "Wrong number of inputs" << std::endl;
    return 1;
  }

  if(argc == 4)
    MCDataComparisonFill(argv[1], argv[2], argv[3]);
  return 0;
}

void setBranches(TTree* t1, DntupleBranches &Dntuple){
    t1->SetBranchAddress("Dsize" ,&Dntuple.Dsize);
    t1->SetBranchAddress("Dpt" ,Dntuple.Dpt);
    t1->SetBranchAddress("Dmass" ,Dntuple.Dmass);
    t1->SetBranchAddress("Ddtheta" ,Dntuple.Ddtheta);
    t1->SetBranchAddress("Dalpha" ,Dntuple.Dalpha);
    t1->SetBranchAddress("Dchi2cl" ,Dntuple.Dchi2cl);
    t1->SetBranchAddress("DsvpvDistance" ,Dntuple.DsvpvDistance);
    t1->SetBranchAddress("DsvpvDisErr" ,Dntuple.DsvpvDisErr);
    t1->SetBranchAddress("DlxyBS" ,Dntuple.DlxyBS);
    t1->SetBranchAddress("DlxyBSErr" ,Dntuple.DlxyBSErr);
    t1->SetBranchAddress("Dy" ,Dntuple.Dy);
    t1->SetBranchAddress("Dtrk1highPurity" ,Dntuple.Dtrk1highPurity);
    t1->SetBranchAddress("Dtrk2highPurity" ,Dntuple.Dtrk2highPurity);
    t1->SetBranchAddress("Dtrk1Pt" ,Dntuple.Dtrk1Pt);
    t1->SetBranchAddress("Dtrk1PtErr" ,Dntuple.Dtrk1PtErr);
    t1->SetBranchAddress("Dtrk2Pt" ,Dntuple.Dtrk2Pt);
    t1->SetBranchAddress("Dtrk2PtErr" ,Dntuple.Dtrk2PtErr);
    t1->SetBranchAddress("Dtrk1Eta" ,Dntuple.Dtrk1Eta);
    t1->SetBranchAddress("Dtrk2Eta" ,Dntuple.Dtrk2Eta);
    t1->SetBranchAddress("Dtrk1Algo" ,Dntuple.Dtrk1Algo);
    t1->SetBranchAddress("Dtrk2Algo" ,Dntuple.Dtrk2Algo);
    t1->SetBranchAddress("Dtrk1PixelHit" ,Dntuple.Dtrk1PixelHit);
    t1->SetBranchAddress("Dtrk1StripHit" ,Dntuple.Dtrk1StripHit);
    t1->SetBranchAddress("Dtrk2PixelHit" ,Dntuple.Dtrk2PixelHit);
    t1->SetBranchAddress("Dtrk2StripHit" ,Dntuple.Dtrk2StripHit);
    t1->SetBranchAddress("Dtrk1Chi2ndf" ,Dntuple.Dtrk1Chi2ndf);
    t1->SetBranchAddress("Dtrk2Chi2ndf" ,Dntuple.Dtrk2Chi2ndf);
    t1->SetBranchAddress("Dtrk1nStripLayer" ,Dntuple.Dtrk1nStripLayer);
    t1->SetBranchAddress("Dtrk1nPixelLayer" ,Dntuple.Dtrk1nPixelLayer);
    t1->SetBranchAddress("Dtrk2nStripLayer" ,Dntuple.Dtrk2nStripLayer);
    t1->SetBranchAddress("Dtrk2nPixelLayer" ,Dntuple.Dtrk2nPixelLayer);
    //t1->SetBranchAddress("" ,Dntuple.);
    t1->SetBranchAddress("Dtrk1MassHypo" ,Dntuple.Dtrk1MassHypo);
    t1->SetBranchAddress("Dtrk2MassHypo" ,Dntuple.Dtrk2MassHypo);
}
void setGenBranches(TTree* t1, DntupleBranches &Dntuple){
    t1->SetBranchAddress("GisSignal" ,Dntuple.GisSignal);
    t1->SetBranchAddress("Gy" ,Dntuple.Gy);
}
