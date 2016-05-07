#include "uti.h"

Double_t setparam0=100.;
Double_t setparam1=1.865;
Double_t setparam2=0.03;
Double_t setparam10=0.005;
Double_t setparam8=0.1;
Double_t setparam9=0.1;
Double_t fixparam1=1.865;
Double_t minhisto=1.7;
Double_t maxhisto=2.0;
Double_t nbinsmasshisto=60;
Double_t binwidthmass=(maxhisto-minhisto)/nbinsmasshisto;

TString mvatk = "(Dtrk1highPurity&&Dtrk2highPurity)";
TString mbtrg = "L1_SingleS1Jet28_BptxAND==1&&(HLT_HIPuAK4CaloJet40_Eta5p1_v1||HLT_HIPuAK4CaloJet60_Eta5p1_v1||HLT_HIPuAK4CaloJet80_Eta5p1_v1)";
TString prefilter = Form("Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&(DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050&&%s&&%s",mvatk.Data(),mbtrg.Data());
TString prefilterMC = Form("Dgen==23333&&Dy>-1.&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&(DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050&&%s",mvatk.Data());
TString prefilterSW = Form("Dgen==23344&&Dy>-1.&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&(DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050&&%s",mvatk.Data());
bool isPbPb=false;


void triggerturnondataPbPb(TString trigger="HLT_HIDmesonHITrackingGlobal_Dpt40_v1")
{
  TH1D* getYield(TTree* nt, TTree* ntMC, TString triggerpass, TString triggername, TString prescale, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="");
  void plotTurnOn(TH1D* hnominator, TH1D* hdenominator, TString triggerlegend, TString triggername, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX);

  TString infnameMC,infname;
  infnameMC ="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root";
  infname = "/data/wangj/Data2015/Dntuple/PbPb/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_jettriggerskim.root";
  TFile* infile = new TFile(infname);
  TTree* root = (TTree*)infile->Get("ntDkpi");
  root->AddFriend("ntHlt");
  TFile* infileMC = new TFile(infnameMC);
  TTree* rootMC = (TTree*)infileMC->Get("ntDkpi");
  rootMC->AddFriend("ntHlt");
  rootMC->AddFriend("ntGen");

  if(!isPbPb)
  {
    TH1D* hpp_pt = getYield(root,rootMC,"","","","Dpt","pt","p_{T} (GeV/c)",3,40,100);
    TH1D* hpp_pt_Hlt = getYield(root,rootMC,Form("&&%s",trigger.Data()),Form("_%s",trigger.Data()),Form("*%s_Prescl",trigger.Data()),"Dpt","pt","p_{T} (GeV/c)",3,40,100);
    plotTurnOn(hpp_pt_Hlt,hpp_pt,trigger,Form("_%s",trigger.Data()),"pt","p_{T} (GeV/c)",3,40,100);
  }
}

TH1D* getYield(TTree* nt, TTree* ntMC, TString triggerpass, TString triggername, TString prescale, TString variable, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX, TString addcut="")
{
  TH1D* hDistrib = new TH1D(Form("h%s_Distrib_%s",triggername.Data(),varname.Data()),"",BIN_NUM,BIN_MIN,BIN_MAX);
  for(float ivar=0;ivar<BIN_NUM;ivar++)
  {
    TCanvas* c = new TCanvas(Form("c%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"",500,500);
    TH1D* h = new TH1D(Form("h%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),";D^{0} mass (GeV/c^{2});Candidates",60,1.7,2.0);
    TH1D* hMC = new TH1D(Form("hMC%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"",60,1.75,1.95);
    TH1D* hSW = new TH1D(Form("hSW%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"",60,1.75,1.95);
    Float_t varmin = BIN_MIN+ivar*((BIN_MAX-BIN_MIN)/BIN_NUM);
    Float_t varmax = BIN_MIN+(ivar+1)*((BIN_MAX-BIN_MIN)/BIN_NUM);
    nt->Project(Form("h%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),Form("Dmass%s",prescale.Data()),Form("%s%s&&(%s>%f&&%s<%f)%s",prefilter.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,triggerpass.Data()));
    ntMC->Project(Form("hMC%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)%s",prefilterMC.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,"&&1"));
    ntMC->Project(Form("hSW%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"Dmass",Form("%s%s&&(%s>%f&&%s<%f)%s",prefilterSW.Data(),addcut.Data(),variable.Data(),varmin,variable.Data(),varmax,"&&1"));
    h->SetMaximum(h->GetMaximum()*1.20);
    h->Draw();

    TF1* f = new TF1(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]*([7]*([9]*Gaus(x,[1],[2]*(1+[11]))/(sqrt(2*3.14159)*[2]*(1+[11]))+(1-[9])*Gaus(x,[1],[10]*(1+[11]))/(sqrt(2*3.14159)*[10]*(1+[11])))+(1-[7])*Gaus(x,[1],[8]*(1+[11]))/(sqrt(2*3.14159)*[8]*(1+[11])))+[3]+[4]*x+[5]*x*x+[6]*x*x*x", 1.7, 2.0);
    f->SetParLimits(4,-1000,1000);
    f->SetParLimits(10,0.001,0.05);
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
    h->GetEntries();

    hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"q","",1.7,2.0);
    hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"q","",1.7,2.0);
    f->ReleaseParameter(1);
    hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
    hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
    hMC->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L m","",1.7,2.0);

    f->FixParameter(1,f->GetParameter(1));
    f->FixParameter(2,f->GetParameter(2));
    f->FixParameter(10,f->GetParameter(10));
    f->FixParameter(9,f->GetParameter(9));
    f->FixParameter(7,0);
    f->ReleaseParameter(8);
    f->SetParameter(8,setparam8);

    hSW->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
    hSW->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
    hSW->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
    hSW->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L m","",1.7,2.0);

    f->FixParameter(7,hMC->Integral(0,1000)/(hSW->Integral(0,1000)+hMC->Integral(0,1000)));
    f->FixParameter(8,f->GetParameter(8));
    f->ReleaseParameter(3);
    f->ReleaseParameter(4);
    f->ReleaseParameter(5);
    f->ReleaseParameter(6);

    f->SetLineColor(kRed);

    h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"q","",1.7,2.0);
    h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"q","",1.7,2.0);
    f->ReleaseParameter(1);
    f->SetParLimits(1,1.86,1.87);
    f->ReleaseParameter(11);
    f->SetParLimits(11,-1.,1.);
    h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
    h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
    h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L q","",1.7,2.0);
    h->Fit(Form("f%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"L m","",1.7,2.0);
    h->SetMarkerSize(0.8);
    h->SetMarkerStyle(20);

    TF1* background = new TF1(Form("background%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]+[1]*x+[2]*x*x+[3]*x*x*x");
    background->SetParameter(0,f->GetParameter(3));
    background->SetParameter(1,f->GetParameter(4));
    background->SetParameter(2,f->GetParameter(5));
    background->SetParameter(3,f->GetParameter(6));
    background->SetLineColor(4);
    background->SetRange(1.7,2.0);
    background->SetLineStyle(2);

    TF1* mass = new TF1(Form("fmass%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]*([3]*([4]*Gaus(x,[1],[2]*(1+[6]))/(sqrt(2*3.14159)*[2]*(1+[6]))+(1-[4])*Gaus(x,[1],[5]*(1+[6]))/(sqrt(2*3.14159)*[5]*(1+[6]))))");
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

    TF1* massSwap = new TF1(Form("fmassSwap%s_Fit_%s_%.0f",triggername.Data(),varname.Data(),ivar),"[0]*(1-[2])*Gaus(x,[1],[3]*(1+[4]))/(sqrt(2*3.14159)*[3]*(1+[4]))");
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

    h->SetXTitle("m_{#piK} (GeV/c^{2})");
    h->SetYTitle("Entries / (5 MeV/c^{2})");
    h->GetXaxis()->CenterTitle();
    h->GetYaxis()->CenterTitle();
    h->SetAxisRange(0,h->GetMaximum()*1.4*1.2,"Y");
    h->GetXaxis()->SetTitleOffset(1.3);
    h->GetYaxis()->SetTitleOffset(1.8);
    h->GetXaxis()->SetLabelOffset(0.007);
    h->GetYaxis()->SetLabelOffset(0.007);
    h->GetXaxis()->SetTitleSize(0.045);
    h->GetYaxis()->SetTitleSize(0.045);
    h->GetXaxis()->SetTitleFont(42);
    h->GetYaxis()->SetTitleFont(42);
    h->GetXaxis()->SetLabelFont(42);
    h->GetYaxis()->SetLabelFont(42);
    h->GetXaxis()->SetLabelSize(0.04);
    h->GetYaxis()->SetLabelSize(0.04);
    h->SetMarkerSize(0.8);
    h->SetMarkerStyle(20);
    h->SetStats(0);
    h->Draw("e");

    background->Draw("same");   
    mass->SetRange(1.7,2.0);	
    mass->Draw("same");
    massSwap->SetRange(1.7,2.0);
    massSwap->Draw("same");
    f->Draw("same");

    Double_t yield = mass->Integral(1.7,2.0)/0.005;
    Double_t yieldErr = (mass->Integral(1.7,2.0)/0.005)*(mass->GetParError(0)/mass->GetParameter(0));
    std::cout<<"YIELD="<<yield<<std::endl;

    // Draw the legend:)   
    TLegend* leg = myLegend(0.20,0.60,0.53,0.94);
    leg->SetFillColor(0);
    leg->SetBorderSize(0);
    leg->AddEntry((TObject*)0,"CMS Preliminary","");
    if(isPbPb) leg->AddEntry((TObject*)0,"PbPb #sqrt{s_{NN}}= 5.02 TeV","");
    else leg->AddEntry((TObject*)0,"pp #sqrt{s_{NN}}= 5.02 TeV","");
    leg->AddEntry((TObject*)0,Form("%.1f<%s<%.1f",varmin,varlatex.Data(),varmax),"");
    leg->AddEntry(h,"Data","pl");
    leg->AddEntry(f,"Fit","l");
    leg->AddEntry(mass,"Signal","f");
    leg->AddEntry(massSwap,"K-#pi swapped","f");
    leg->AddEntry(background,"Combinatorial Background","l");
    leg->Draw();
    TLegend* leg2 = myLegend(0.45,0.80,0.90,0.94);
    leg2->SetFillColor(0);
    leg2->SetBorderSize(0);
    leg2->AddEntry(h,"D meson","");
    leg2->AddEntry(h,Form("M_{D}=%.2f #pm %.2f MeV/c^{2}",mass->GetParameter(1)*1000.,mass->GetParError(1)*1000.),"");
    leg2->AddEntry(h,Form("N_{D}=%.0f #pm %.0f", yield, yieldErr),"");
    leg2->Draw();

    hDistrib->SetBinContent(ivar+1,yield);
    hDistrib->SetBinError(ivar+1,yieldErr);

    if(isPbPb) c->SaveAs(Form("triggerturnonPlots/data/pbpb/c%s_Fit_%s_%.0f.pdf",triggername.Data(),varname.Data(),ivar));
    else c->SaveAs(Form("triggerturnonPlots/data/pp/c%s_Fit_%s_%.0f.pdf",triggername.Data(),varname.Data(),ivar));
  }
  TCanvas* cDistrib = new TCanvas(Form("c%s_Distrib_%s",triggername.Data(),varname.Data()),"",500,500);
  hDistrib->Draw();
  hDistrib->SetStats(0);
  if(isPbPb) cDistrib->SaveAs(Form("triggerturnonPlots/data/pbpb/c%s_Distrib_%s.pdf",triggername.Data(),varname.Data()));
  else cDistrib->SaveAs(Form("triggerturnonPlots/data/pp/c%s_Distrib_%s.pdf",triggername.Data(),varname.Data()));

  return hDistrib;
}

void plotTurnOn(TH1D* hnominator, TH1D* hdenominator, TString triggerlegend, TString triggername, TString varname, TString varlatex, Int_t BIN_NUM, Double_t BIN_MIN, Double_t BIN_MAX)
{
  TEfficiency* pEff = new TEfficiency(*hnominator,*hdenominator);
  TCanvas* cEff = new TCanvas(Form("c%s_Eff_%s",triggername.Data(),varname.Data()),"",500,500);
  TH2D* hempty = new TH2D(Form("hempty_%s_Eff_%s",triggername.Data(),varname.Data()),Form(";D^{0} %s;Pass efficiency",varlatex.Data()),BIN_NUM,BIN_MIN,BIN_MAX,10,0,1.2);
  hempty->SetStats(0);
  hempty->Draw();
  pEff->Draw("PSAME");
  TLatex* tex = new TLatex(0.18,0.96,triggerlegend);
  tex->SetNDC();
  tex->SetTextFont(42);
  tex->SetTextSize(0.04);
  tex->Draw();
  if(isPbPb) cEff->SaveAs(Form("triggerturnonPlots/data/pbpb/c%s_Eff_%s.pdf",triggername.Data(),varname.Data()));
  else cEff->SaveAs(Form("triggerturnonPlots/data/pp/c%s_Eff_%s.pdf",triggername.Data(),varname.Data()));
}
