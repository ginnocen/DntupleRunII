void projectPPMBMC()
{
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
  gStyle->SetOptFit(1111);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(0);

  TFile* infMCP = new TFile("/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_prompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root");
  TFile* infMCNP = new TFile("/data/HeavyFlavourRun2/MC2015/Dntuple/pp/ntD_EvtBase_20160513_DfinderMC_pp_20160502_dPt0tkPt0p5_D0Dstar_nonprompt_Dpt2Dy1p1tkPt0p7tkEta2Decay2p9Dalpha0p14Skim_pthatweight.root");
  
  TTree* tMCP = (TTree*)infMCP->Get("ntDkpi");
  TTree* tMCNP = (TTree*)infMCNP->Get("ntDkpi");
  TTree* tMCPHI = (TTree*)infMCP->Get("ntHi");
  TTree* tMCNPHI = (TTree*)infMCNP->Get("ntHi");
  TTree* tMCPSkim = (TTree*)infMCP->Get("ntSkim");
  TTree* tMCNPSkim = (TTree*)infMCNP->Get("ntSkim");
  tMCP->AddFriend(tMCPHI);
  tMCNP->AddFriend(tMCNPHI);
  tMCP->AddFriend(tMCPSkim);
  tMCNP->AddFriend(tMCNPSkim);
  
  TFile* outf = new TFile("bFeedDownPPMBMC.hist.root","recreate");
  
  TCut cutPPMb ="pBeamScrapingFilter&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12";

  TCut cutmc = "(Dgen==23333||Dgen==23344)&&pthat>(1.5*Dpt)";
  TCut cutmcSignal = "Dgen==23333&&pthat>(1.5*Dpt)";
  TCut cutmcSwapped = "Dgen==23344&&pthat>(1.5*Dpt)";
  TCut cutpt = "Dpt<20";
  TCut cutSignal = "abs(Dmass-1.8649)<0.025";
  TCut cutSideband = "abs(Dmass-1.8649)>0.075&&abs(Dmass-1.8649)<0.1";
  TCut cutPrompt = "DgenBAncestorpt<=0";
  TCut cutNonPrompt ="DgenBAncestorpt>0";
  TCut weightfunctionreco = "pthatweight";

  const int nBinX = 14;
  Float_t binsX[nBinX+1] = {2.,3.,4.,5.,6.,8.,10.,12.5,15.0,20.,25.,30.,40.,60.,100};

  const int nBinY = 20;
  Float_t binsY[nBinY+1];
  float firstBinYWidth = 0.001;
  float binYWidthRatio = 1.27;
  binsY[0]=0;
  for(int i=1; i<=nBinY; i++)
    binsY[i] = binsY[i-1]+firstBinYWidth*pow(binYWidthRatio,i-1);
  cout<<"last y bin: "<<binsY[nBinY]<<endl;

  const int nBinZ = 20;
  Float_t binsZ[nBinZ+1];
  float firstBinZ = 3.5;
  float binWidthZ = 5;
  for(int i=0; i<=nBinZ; i++)
    binsZ[i] = firstBinZ+binWidthZ*i;
  
  const int nBinM = 60;
  Float_t binsM[nBinM];
  float minMassBin = 1.7;
  float massBinWidth = 0.005;
  for(int i=0; i<=nBinM; i++)
    binsM[i] = minMassBin + massBinWidth*i;

  TH3D* hMCPSignal = new TH3D("hMCPSignal",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hMCNPSignal = new TH3D("hMCNPSignal",";p_{T} (GeV/c};D0 DCA (cm);flight distance significance",nBinX,binsX,nBinY,binsY,nBinZ,binsZ);
  TH3D* hPtMD0DcaMCPSignal = new TH3D("hPtMD0DcaMCPSignal",";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
  TH3D* hPtMD0DcaMCPSwapped = new TH3D("hPtMD0DcaMCPSwapped",";p_{T} (GeV/c);m (GeV/c^{2});D^{0} DCA (cm)",nBinX,binsX,nBinM,binsM,nBinY,binsY);
  
  hMCPSignal->Sumw2();
  hMCNPSignal->Sumw2();
  hPtMD0DcaMCPSignal->Sumw2();
  hPtMD0DcaMCPSwapped->Sumw2();
  
  tMCP->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hMCPSignal",weightfunctionreco*(cutpt&&cutPPMb&&cutSignal&&cutmc&&cutPrompt));
  tMCNP->Draw("DsvpvDistance/DsvpvDisErr:DsvpvDistance*sin(Dalpha):Dpt>>hMCNPSignal",weightfunctionreco*(cutpt&&cutPPMb&&cutSignal&&cutmc&&cutNonPrompt));
  tMCP->Draw("DsvpvDistance*sin(Dalpha):Dmass:Dpt>>hPtMD0DcaMCPSignal",weightfunctionreco*(cutpt&&cutPPMb&&cutmcSignal&&cutPrompt));
  tMCP->Draw("DsvpvDistance*sin(Dalpha):Dmass:Dpt>>hPtMD0DcaMCPSwapped",weightfunctionreco*(cutpt&&cutPPMb&&cutmcSwapped&&cutPrompt));
  
  outf->Write();
}

