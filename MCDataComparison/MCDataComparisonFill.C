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
	_Dmass,
	_Ddtheta,
	_DlxyBS_DlxyBSErr,
	_Dpt,
	_Dy,
	_Dalpha,
	_Dchi2cl,
	_DsvpvDistance_DsvpvDisErr,
	_fine_Dpt,
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

const int _nbinPtpp    = 4; 
const int _nbinPtPbPb  = 4;
const int _nbinPtMB    = 8;
const int _nbinChi     = 7;
const int _nbinAlpha   = 7;
const int _nbinDecay   = 6;
const int _nbinY       = 6;
const int _ndummy      = 0;

double _binPtpp[_nbinPtpp+1] = {20, 25, 30, 35, 40};
double _binPtPbPb[_nbinPtPbPb+1] = {20, 25, 30, 35, 40};
double _binPtMB[_nbinPtMB+1] = {1.,3.,4.,5.,6.,8.,10.,15.,20.};
double _binChi[_nbinChi+1] = {0.05,0.1,0.2,0.3,0.4,0.6,0.8,1.0};
double _binAlpha[_nbinAlpha+1] = {0.00,0.003,0.006,0.009,0.014,0.02,0.03,0.12};
double _binDecay[_nbinDecay+1] = {4.,5.,6.,7.,8.,10,15};
double _binY[_nbinY+1] = {-1.,-0.6,-0.3,0.,0.3,0.6,1.};
double _dummy[_ndummy+1] = {0};

struct varStruct myVars[_varSize] = {
	{"Dmass",                     "Dmass",                           50, 1.7,  2.,    _ndummy,     _dummy,     0, "Dmass",                          "GeV", "",                         true },
	{"Ddtheta",                   "Ddtheta",                         20, 0.,   0.1,   _ndummy,     _dummy,     0, "Ddtheta",                        "",    "",                         true },
	{"DlxyBS/DlxyBSErr",          "DlxyBS_DlxyBSErr",                20, 0.,   1000., _ndummy,     _dummy,     0, "DlxyBS_DlxyBSErr",               "",    "",                         true },
	{"Dpt",                       "Dpt",                             20, 0,    100.,  _nbinPtpp,   _binPtpp,   1, "Dpt",                            "GeV", "outputPlotPt.root",        true },
	{"Dy",                        "Dy",                              20, -1,   1.,    _nbinY,      _binY,      1, "Dy",                             "",    "outputPlotRapidity.root",  true },
	{"Dalpha",                    "Dalpha",                          20, 0.,   0.04,  _nbinAlpha,  _binAlpha,  1, "Dalpha",                         "",    "outputPlotDalpha.root",    true },
	{"Dchi2cl",                   "Dchi2cl",                         20, 0.05, 1.,    _nbinChi,    _binChi,    1, "Dchi2cl",                        "",    "outputPlotChi2.root",      true },
	{"DsvpvDistance/DsvpvDisErr", "DsvpvDistance_DsvpvDisErr",       20, 4.,   15.,   _nbinDecay,  _binDecay,  1, "DsvpvDistance_DsvpvDisErr",      "",    "outputPlotDecay.root",     true },
	{"Dpt",                       "_fine_Dpt",                       20, 0,    100.,  _ndummy,     _dummy,     0, "Dpt_fine",                       "GeV", "",                         true },
	{"Dy",                        "_fine_Dy",                        20, -1,   1.,    _ndummy,     _dummy,     0, "Dy_fine",                        "",    "",                         true },
	{"Dalpha",                    "_fine_Dalpha",                    20, 0.,   0.12,  _ndummy,     _dummy,     0, "Dalpha_fine",                    "",    "",                         true },
	{"Dchi2cl",                   "_fine_Dchi2cl",                   20, 0.05, 1.,    _ndummy,     _dummy,     0, "Dchi2cl_fine",                   "",    "",                         true },
	{"DsvpvDistance/DsvpvDisErr", "_fine_DsvpvDistance_DsvpvDisErr", 20, 4.,   15.,   _ndummy,     _dummy,     0, "DsvpvDistance_DsvpvDisErr_fine", "",    "",                         true }
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
        void setHLTBranches(TTree* t1, string dataNtype){
			if(dataNtype == "ppHF"){
        	    t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt15_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt15_v1);
    	        t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt30_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt30_v1);
	            t1->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt50_v1" ,&HLT_DmesonPPTrackingGlobal_Dpt50_v1);
			}
            if(dataNtype == "PbPbHF"){
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
const int paraBins = 15;
float pa0[paraBins] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};	
float pa1[paraBins] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
float pa2[paraBins] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};	
const int nBinsppHF=7; 
float ptBinsppHF[nBinsppHF+1]={20, 40, -1, 20, 25, 30, 35, 40 };
const int nBinsPbPbHF=7; 
float ptBinsPbPbHF[nBinsPbPbHF+1]={20, 45, -1, 20, 25, 30, 35, 45};
const int nBinsppMB=11; 
float ptBinsppMB[nBinsppMB+1]={1, 20, -1, 1., 3.,4.,5.,6.,8.,10.,15.,20.};
int nBins; 
float *ptBins;

void overlapTH1(TCanvas* c, TH1D* h1, TH1D* h2, TH1D* h3, TH1D* h4, string xTitle, TH1D* hRatio, string rfile, int customize, string dataNtype, int _bin);
void setBranches(TTree* t1, DntupleBranches &Dntuple);
void setGenBranches(TTree* t1, DntupleBranches &Dntuple);

void DoAnalysis(TFile* inf, TFile* infMC, TString outputfile, bool DoPtWeight, string dataNtype)
{

	if(dataNtype == "ppHF") {
		nBins = nBinsppHF;
		ptBins = ptBinsppHF;
	}
	if(dataNtype == "PbPbHF") {
		nBins = nBinsPbPbHF;
		ptBins = ptBinsPbPbHF;
		myVars[_Dpt].binSep = _binPtPbPb;
		myVars[_Dpt].nBinSep = _nbinPtPbPb;
	}
	if(dataNtype == "ppMB" || dataNtype == "PbPbMB") {
		nBins = nBinsppMB;
		ptBins = ptBinsppMB;
		myVars[_Dpt].binSep = _binPtMB;
		myVars[_Dpt].nBinSep = _nbinPtMB;
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
	//gStyle->SetErrorX(0.);

	TTree* nt = (TTree*) inf->Get("ntDkpi");
	TTree* HltTree = (TTree*) inf->Get("ntHlt");
	
	TTree* ntMC = (TTree*)infMC->Get("ntDkpi");
	TTree* ntGen = (TTree*)infMC->Get("ntGen");
	TTree* ntHi = (TTree*)infMC->Get("ntHi");
	//TTree* MCHltTree;
	//MCHltTree= (TTree*)infMC->Get("ntHlt");
	
	TCanvas *c0[_varSize][nBins];
	TCanvas *c1[_varSize][nBins];
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
		ptR[p] =  new TH1D((myVars[_Dpt].title+"Ratio"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[_Dpt].title.c_str(), myVars[_Dpt].nBinSep, myVars[_Dpt].binSep);
		ptR[p]->SetDefaultSumw2();
		for (int i = 0 ; i < _varSize; i++){
			c0[i][p] =  new TCanvas(("c0"+myVars[i].title+Form("_%d%s", p, wPrefix.c_str())).c_str(),"",600,600);
			c1[i][p] =  new TCanvas(("c1"+myVars[i].title+Form("_%d%s", p, wPrefix.c_str())).c_str(),"",600,600);
			float _xMin = myVars[i].xMin;
			float _xMax = myVars[i].xMax;
			if(myVars[i].binOpt==0){
				if(i == _fine_Dpt && ptBins[p] != -1 && ptBins[p+1] != -1){
					_xMin = ptBins[p];
					_xMax = ptBins[p+1];
				}
				h1[i][p] =   new TH1D((myVars[i].title+"1"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h2[i][p] =   new TH1D((myVars[i].title+"2"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h3[i][p] =   new TH1D((myVars[i].title+"3"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h4[i][p] =   new TH1D((myVars[i].title+"4"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h11[i][p] = new TH1D((myVars[i].title+"11"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h12[i][p] = new TH1D((myVars[i].title+"12"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h13[i][p] = new TH1D((myVars[i].title+"13"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h14[i][p] = new TH1D((myVars[i].title+"14"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h21[i][p] = new TH1D((myVars[i].title+"21"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h22[i][p] = new TH1D((myVars[i].title+"22"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				h23[i][p] = new TH1D((myVars[i].title+"23"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBin, _xMin, _xMax);
				hRatio[i][p] = new TH1D((myVars[i].title+"_ratio"+Form("_%d%s", p, wPrefix.c_str())).c_str(), (myVars[i].title+"_ratio").c_str(), myVars[i].nBin, _xMin, _xMax);
			}
            if(myVars[i].binOpt==1){
				h1[i][p] =  new TH1D((myVars[i].title+"1"+Form("_%d%s",  p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h2[i][p] =  new TH1D((myVars[i].title+"2"+Form("_%d%s",  p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h3[i][p] =  new TH1D((myVars[i].title+"3"+Form("_%d%s",  p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h4[i][p] =  new TH1D((myVars[i].title+"4"+Form("_%d%s",  p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h11[i][p] = new TH1D((myVars[i].title+"11"+Form("%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h12[i][p] = new TH1D((myVars[i].title+"12"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h13[i][p] = new TH1D((myVars[i].title+"13"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h14[i][p] = new TH1D((myVars[i].title+"14"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h21[i][p] = new TH1D((myVars[i].title+"21"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h22[i][p] = new TH1D((myVars[i].title+"22"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				h23[i][p] = new TH1D((myVars[i].title+"23"+Form("_%d%s", p, wPrefix.c_str())).c_str(), myVars[i].title.c_str(), myVars[i].nBinSep, myVars[i].binSep);
				hRatio[i][p] = new TH1D((myVars[i].title+"_ratio"+Form("_%d%s", p, wPrefix.c_str())).c_str(), (myVars[i].title+"_ratio").c_str(), myVars[i].nBinSep, myVars[i].binSep);
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
	int isPrompt;
	ntHi->SetBranchAddress("pthatweight" ,&pthatweight);
	ntHi->SetBranchAddress("isPrompt" ,&isPrompt);
	float ptWeight = 1;
	float additionWeight = 1;
	float totalWeight = 1;
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
			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
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
				&&Dntuple.Dtrk1Pt[s]>0.7&&Dntuple.Dtrk2Pt[s]>0.7
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.3&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.3
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.5&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>2.5&&Dntuple.Dchi2cl[s]>0.05&&Dntuple.Dalpha[s]<0.12
				&&(dataNtype == "ppMB")
			){
				boolCut = true;
			}

			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>0.7&&Dntuple.Dtrk2Pt[s]>0.7
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.3&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.3
				&&abs(Dntuple.Dtrk1Eta[s])<1.5&&abs(Dntuple.Dtrk2Eta[s])<1.5
				&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5&&Dntuple.Dalpha[s]<0.12
				&&(
				   (Dntuple.Dpt[s]>1 &&Dntuple.Dpt[s]<2 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>6.0  &&Dntuple.Dchi2cl[s]>0.25)
				 ||(Dntuple.Dpt[s]>2 &&Dntuple.Dpt[s]<4 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.86 &&Dntuple.Dchi2cl[s]>0.224)
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
				if(ptBins[p] == -1 || ptBins[p+1] == -1) continue;
				ptWeight = pa0[p] + pa1[p]*Dntuple.Dpt[s] + pa2[p]*Dntuple.Dpt[s]*Dntuple.Dpt[s];
				if(isPrompt) additionWeight = 1;
				else additionWeight = 0.15;
				totalWeight = ptWeight*additionWeight;
				//totalWeight = 1;
				//totalWeight = 0.15;
				if(Dntuple.Dpt[s]>ptBins[p]&&Dntuple.Dpt[s]<ptBins[p+1]){
					if(boolSignalRG){
						h1 [_Dpt][p]->Fill(Dntuple.Dpt[s], totalWeight);
						h11[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
						h1 [_Dmass][p]->Fill(Dntuple.Dmass[s], totalWeight);
						h11[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
						h1 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], totalWeight);
						h11[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
						h1 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], totalWeight);
						h11[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
						h1 [_Dy][p]->Fill(Dntuple.Dy[s], totalWeight);
						h11[_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
						h1 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], totalWeight);
						h11[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h1 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], totalWeight);
						h11[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h1 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], totalWeight);
						h11[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						h1 [_fine_Dpt][p]->Fill(Dntuple.Dpt[s], totalWeight);
						h11[_fine_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
						h1 [_fine_Dy][p]->Fill(Dntuple.Dy[s], totalWeight);
						h11[_fine_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
						h1 [_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], totalWeight);
						h11[_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h1 [_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], totalWeight);
						h11[_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h1 [_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], totalWeight);
						h11[_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						if(boolGenCut){
							h4 [_Dpt][p]->Fill(Dntuple.Dpt[s], totalWeight);
							h14[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
							h4 [_Dmass][p]->Fill(Dntuple.Dmass[s], totalWeight);
							h14[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
							h4 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], totalWeight);
							h14[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
							h4 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], totalWeight);
							h14[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
							h4 [_Dy][p]->Fill(Dntuple.Dy[s], totalWeight);
							h14[_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
							h4 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], totalWeight);
							h14[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
							h4 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], totalWeight);
							h14[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
							h4 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], totalWeight);
							h14[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
							h4 [_fine_Dpt][p]->Fill(Dntuple.Dpt[s], totalWeight);
							h14[_fine_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
							h4 [_fine_Dy][p]->Fill(Dntuple.Dy[s], totalWeight);
							h14[_fine_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
							h4 [_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], totalWeight);
							h14[_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
							h4 [_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], totalWeight);
							h14[_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
							h4 [_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], totalWeight);
							h14[_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						}
					}
					if(boolSidebandRG){
						h2 [_Dpt][p]->Fill(Dntuple.Dpt[s], totalWeight);
						h12[_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
						h2 [_Dmass][p]->Fill(Dntuple.Dmass[s], totalWeight);
						h12[_Dmass][p]->Fill(Dntuple.Dmass[s], pthatweight*ptWeight);
						h2 [_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], totalWeight);
						h12[_Ddtheta][p]->Fill(Dntuple.Ddtheta[s], pthatweight*ptWeight);
						h2 [_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], totalWeight);
						h12[_DlxyBS_DlxyBSErr][p]->Fill(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s], pthatweight*ptWeight);
						h2 [_fine_Dpt][p]->Fill(Dntuple.Dpt[s], totalWeight);
						h12[_fine_Dpt][p]->Fill(Dntuple.Dpt[s], pthatweight*ptWeight);
						h2 [_Dy][p]->Fill(Dntuple.Dy[s], totalWeight);
						h12[_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
						h2 [_Dalpha][p]->Fill(Dntuple.Dalpha[s], totalWeight);
						h12[_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h2 [_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], totalWeight);
						h12[_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h2 [_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], totalWeight);
						h12[_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], pthatweight*ptWeight);
						h2 [_fine_Dy][p]->Fill(Dntuple.Dy[s], totalWeight);
						h12[_fine_Dy][p]->Fill(Dntuple.Dy[s], pthatweight*ptWeight);
						h2 [_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], totalWeight);
						h12[_fine_Dalpha][p]->Fill(Dntuple.Dalpha[s], pthatweight*ptWeight);
						h2 [_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], totalWeight);
						h12[_fine_Dchi2cl][p]->Fill(Dntuple.Dchi2cl[s], pthatweight*ptWeight);
						h2 [_fine_DsvpvDistance_DsvpvDisErr][p]->Fill(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s], totalWeight);
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
			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
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
				&&Dntuple.Dtrk1Pt[s]>0.7&&Dntuple.Dtrk2Pt[s]>0.7
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.3&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.3
				&&abs(Dntuple.Dtrk1Eta[s])<2.0&&abs(Dntuple.Dtrk2Eta[s])<2.0
				&&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>3.5&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>2.5&&Dntuple.Dchi2cl[s]>0.05&&Dntuple.Dalpha[s]<0.12
				&&(dataNtype == "ppMB")
			){
				boolCut = true;
			}

			if (Dntuple.Dy[s]>-1.&&Dntuple.Dy[s]<1.
				&&Dntuple.Dtrk1highPurity[s]&&Dntuple.Dtrk2highPurity[s]
				&&Dntuple.Dtrk1Pt[s]>0.7&&Dntuple.Dtrk2Pt[s]>0.7
				&&Dntuple.Dtrk1PtErr[s]/Dntuple.Dtrk1Pt[s]<0.3&&Dntuple.Dtrk2PtErr[s]/Dntuple.Dtrk2Pt[s]<0.3
				&&abs(Dntuple.Dtrk1Eta[s])<1.5&&abs(Dntuple.Dtrk2Eta[s])<1.5
				&&(Dntuple.DlxyBS[s]/Dntuple.DlxyBSErr[s])>1.5&&Dntuple.Dalpha[s]<0.12
				&&(
				   (Dntuple.Dpt[s]>1 &&Dntuple.Dpt[s]<2 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>6.0  &&Dntuple.Dchi2cl[s]>0.25)
				 ||(Dntuple.Dpt[s]>2 &&Dntuple.Dpt[s]<4 &&(Dntuple.DsvpvDistance[s]/Dntuple.DsvpvDisErr[s])>5.86 &&Dntuple.Dchi2cl[s]>0.224)
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
				&&(dataNtype == "PbPbMB")
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
				if(ptBins[p] == -1 || ptBins[p+1] == -1) continue;
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
						h21 [_fine_Dpt][p]->Fill(Dntuple.Dpt[s]);
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
						h22 [_fine_Dpt][p]->Fill(Dntuple.Dpt[s]);
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
		if(ptBins[p] == -1 || ptBins[p+1] == -1) continue;
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

			h1[i][p]  ->SetBinError(bin, h1[i][p] ->GetBinError(bin)/h1[i][p] ->GetBinWidth(bin));
			h2[i][p]  ->SetBinError(bin, h2[i][p] ->GetBinError(bin)/h2[i][p] ->GetBinWidth(bin));
			h3[i][p]  ->SetBinError(bin, h3[i][p] ->GetBinError(bin)/h3[i][p] ->GetBinWidth(bin));
			h4[i][p]  ->SetBinError(bin, h4[i][p] ->GetBinError(bin)/h4[i][p] ->GetBinWidth(bin));
			h11[i][p] ->SetBinError(bin, h11[i][p]->GetBinError(bin)/h11[i][p]->GetBinWidth(bin));
			h12[i][p] ->SetBinError(bin, h12[i][p]->GetBinError(bin)/h12[i][p]->GetBinWidth(bin));
			h13[i][p] ->SetBinError(bin, h13[i][p]->GetBinError(bin)/h13[i][p]->GetBinWidth(bin));
			h14[i][p] ->SetBinError(bin, h14[i][p]->GetBinError(bin)/h14[i][p]->GetBinWidth(bin));
			h21[i][p] ->SetBinError(bin, h21[i][p]->GetBinError(bin)/h21[i][p]->GetBinWidth(bin));
			h22[i][p] ->SetBinError(bin, h22[i][p]->GetBinError(bin)/h22[i][p]->GetBinWidth(bin));
			h23[i][p] ->SetBinError(bin, h23[i][p]->GetBinError(bin)/h23[i][p]->GetBinWidth(bin));
		}
		h3[i][p] = (TH1D*)h1[i][p]->Clone();
		h3[i][p]->Add(h2[i][p],-wfactor);

		h13[i][p] = (TH1D*)h11[i][p]->Clone();
		h13[i][p]->Add(h12[i][p],-wfactor);

		h23[i][p] = (TH1D*)h21[i][p]->Clone();
		h23[i][p]->Add(h22[i][p],-wfactor);

//		if(myVars[i].pthatWeight == false){
		if(1){
			if(p==0 && myVars[i].rfile != ""){
				overlapTH1(c0[i][p], h4[i][p],  h3[i][p],  h23[i][p], h21[i][p], myVars[i].xtitle, hRatio[i][p], "fitExtract/OutPuts_"+dataNtype+"0/"+myVars[i].rfile, -1, dataNtype, p);
				overlapTH1(c1[i][p], h14[i][p], h13[i][p], h23[i][p], h21[i][p], myVars[i].xtitle, hRatio[i][p], "fitExtract/OutPuts_"+dataNtype+"1/"+myVars[i].rfile, -1, dataNtype, p);
			}
			else{
				overlapTH1(c0[i][p], h4[i][p],  h3[i][p],  h23[i][p], h21[i][p], myVars[i].xtitle, hRatio[i][p], "", -1, dataNtype, p);
				overlapTH1(c1[i][p], h14[i][p], h13[i][p], h23[i][p], h21[i][p], myVars[i].xtitle, hRatio[i][p], "", -1, dataNtype, p);
			}
		}
		c0[i][p]->SaveAs(("plotsFill_"+dataNtype+"0/"+myVars[i].plotName+Form("ptBin%d%s", p, wPrefix.c_str())+".pdf").c_str());
		c1[i][p]->SaveAs(("plotsFill_"+dataNtype+"1/"+myVars[i].plotName+Form("ptBin%d%s", p, wPrefix.c_str())+".pdf").c_str());
	}}
	if (DoPtWeight){
	    overlapTH1(cMass, hMCMassGM, hMCMassGMW, hMCMass, hDataMass, "Dmass", hMassRatio, "", 1, dataNtype, -1);
		cMass->SaveAs(("plotsFill_"+dataNtype+"1/mass.pdf").c_str());
	}

	if (!DoPtWeight){
		for (int p = 0; p < nBins; p++){
			if(ptBins[p] == -1 || ptBins[p+1] == -1) continue;
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
			cptR->SaveAs(Form("plotsFill_%s/ptRptBin%d.pdf", dataNtype.c_str(), p));
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
//	DoAnalysis(inf, infMC, outputfile, false, "ppHF");
//	DoAnalysis(inf, infMC, outputfile, true, "ppHF");

    inputdata = "/data/dmeson2015/DataDntuple/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016_skimmedPt1.root";
	inf    = new TFile(inputdata.Data());
//	DoAnalysis(inf, infMC, outputfile, false, "ppHF");
//	DoAnalysis(inf, infMC, outputfile, true, "ppMB");

	//PbPb
	//inputmc = "/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root";
	inputmc = "/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_promptNnonprompt_D0_dPt1tkPt1_pthatweight.root";
	inputdata="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2_skimmed.root";
	inf = new TFile(inputdata.Data());
	infMC = new TFile(inputmc.Data());
//	DoAnalysis(inf, infMC, outputfile, false, "PbPbHF");
//	DoAnalysis(inf, infMC, outputfile, true, "PbPbHF");

	inputdata = "/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root";
	inf = new TFile(inputdata.Data());
//	DoAnalysis(inf, infMC, outputfile, false, "PbPbMB");
	DoAnalysis(inf, infMC, outputfile, true, "PbPbMB");
		
}
	
void overlapTH1(TCanvas* c, TH1D* h1, TH1D* h2, TH1D*h3, TH1D* h4, string xTitle, TH1D* hRatio, string rfile, int customize, string dataNtype, int _bin){
	c->cd();
	h1->GetXaxis()->SetTitle(xTitle.c_str());
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
	h1->SetMarkerSize(0.);
	h2->SetMarkerSize(0.5);
	h3->SetMarkerSize(0.5);
	h1->SetMarkerStyle(21);
	h1->SetMarkerColor(2);
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
//		hRatio->SetMaximum(2.5);
//		hRatio->SetMinimum(0.2);
		hRatio->SetMaximum(1.6);
		hRatio->SetMinimum(0.4);
		TPad* pad1;
		static int pcount = 0;
        pad1 = new TPad(Form("p%d", pcount), Form("p%d", pcount), 0.01, 0.35, 0.99, 0.99); pcount++;
		pad1->Draw();
		pad1->cd();
		h1->Draw("hist e");
//		h2->Draw("same pe");
//		h3->Draw("same pe");
//		h4->Draw("same pe");
		h2->Draw("same hist e");
		h3->Draw("same hist e");
		TLegend* leg = myLegend(0.5, 0.65, 0.86, 0.86);
  		leg->SetTextFont(42);
  		leg->SetTextSize(0.045);
		leg->AddEntry(h1, Form("MC gen matched Dpt=%.0f~%.0f", ptBins[_bin], ptBins[_bin+1]), "l");
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
			rfin = new TFile((rfile).c_str());
			dataIn = (TH1D*)rfin->Get("hPt");
			MCIn = (TH1D*)rfin->Get("hPtMCTot");
			TH1D* ratioIn = (TH1D*)rfin->Get("hRatio");
	        pad1->cd();
			dataIn->SetMarkerSize(0);
			MCIn->SetMarkerSize(0);
			//dataIn->SetLineWidth(0);
			//MCIn->SetLineWidth(0);
			dataIn->SetMarkerStyle(34);
			MCIn->SetMarkerStyle(34);
			//dataIn->SetMarkerStyle(29);
			//MCIn->SetMarkerStyle(29);
			MCIn->SetFillStyle(3001);
			MCIn->SetFillColor(kGreen-2);
			MCIn->SetMarkerColor(kGreen-2);
			MCIn->SetLineColor(kGreen-2);
			dataIn->SetFillStyle(3001);
			dataIn->SetFillColor(kBlue-4);
			dataIn->SetMarkerColor(kBlue-4);
			dataIn->SetLineColor(kBlue-4);
			MCIn->Draw("same E2");
			dataIn->Draw("same E2");
		    leg->AddEntry(MCIn, Form("MC fit Dpt=%.0f~%.0f", ptBins[0], ptBins[1]), "f");
	    	leg->AddEntry(dataIn, Form("data fit"), "f");
			leg->Draw();
	        pad2->cd();
			ratioIn->SetLineWidth(0);
            ratioIn->SetMarkerStyle(34);
			ratioIn->SetFillColor(2);
			ratioIn->SetFillStyle(3001);
			ratioIn->SetLineColor(2);
			ratioIn->SetMarkerColor(2);
			ratioIn->SetMarkerSize(0);
			//ratioIn->Draw("same pe");
			ratioIn->Draw("same E2");
			TLegend* leg2 = myLegend(0.5, 0.65, 0.86, 0.86);
  			leg2->SetTextFont(42);
  			leg2->SetTextSize(0.085);
			leg2->AddEntry(hRatio, "ratio sideband", "l");
			leg2->AddEntry(ratioIn, "ratio fit", "f");
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
