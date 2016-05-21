#include <TH1.h>
#include <TH2.h>
#include <TTree.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TCut.h>
#include <TFile.h>
#include <TCanvas.h>
#include <TGraphAsymmErrors.h>


// Take a tree, a variable and calculate the efficiency
TGraphAsymmErrors* getEfficiency(TTree *t, char *variable, TCut preselection, TCut cut, int nBin, Float_t *bins)
{
   static int count = 0;
   count++;
   TH1D *hPass = new TH1D (Form("hPass%d",count),"",nBin,bins);
   TH1D *hAll = new TH1D (Form("hAll%d",count),"",nBin,bins);
   t->Draw(Form("%s>>hAll%d",variable,count),preselection);
   t->Draw(Form("%s>>hPass%d",variable,count),preselection&&cut);
   
   hAll->Draw();
   cout<<"ici"<<endl;
   
   TGraphAsymmErrors *g = new TGraphAsymmErrors;
   g->BayesDivide(hPass,hAll);
   return g;
}

TGraphAsymmErrors* getEfficiencySum(TTree *t,TTree *t2, char *variable, TCut preselection,TCut preselection2, TCut cut, int nBin, Float_t *bins)
{
   static int count = 0;
   count++;
   TH1D *hPass = new TH1D (Form("hPass%d",count),"",nBin,bins);
   TH1D *hAll = new TH1D (Form("hAll%d",count),"",nBin,bins);
   t->Draw(Form("%s>>hAll%d",variable,count),preselection);
   t->Draw(Form("%s>>hPass%d",variable,count),preselection&&cut);

   TH1D *hPass2 = new TH1D (Form("hPass2%d",count),"",nBin,bins);
   TH1D *hAll2 = new TH1D (Form("hAll2%d",count),"",nBin,bins);
   t2->Draw(Form("%s>>hAll2%d",variable,count),preselection2);
   t2->Draw(Form("%s>>hPass2%d",variable,count),preselection2&&cut);
      
   TH1D *hPassTot = (TH1D*)hPass->Clone("hPassTot");
   TH1D *hAllTot = (TH1D*)hAll->Clone("hAllTot");

   hPassTot->Add(hPass2);
   hAllTot->Add(hAll2);
   
   TFile*f=new TFile(Form("test%d.root",count),"recreate");
   f->cd();
   hPass->Write();
   hAll->Write();
   hPass2->Write();
   hAll2->Write();
   hAllTot->Write();
   hPassTot->Write();
   f->Close();

   TGraphAsymmErrors *g = new TGraphAsymmErrors;
   g->BayesDivide(hPassTot,hAllTot);
   return g;
}


void plotTrigger_PbPbGMI(TString sample="JetTriggeredPlusMB")
{
   bool sideband = false;
   bool cent = false;   
   TString outf,infname;
   int isSample;
   
   if (sample=="MB"){
     TString outf = "result";
     isSample=1;
   }
   
   if (sample=="MBsideband"){
     TString outf = "result_sideband";
     sideband = true;
     isSample=1;
   }

   if (sample=="MB010"){
     TString outf = "result_cent10";
     cent = true;
     isSample=1;
   }
   
   if(sample=="JetTriggered"){
     outf = "result_PbPbHP";
     isSample=0;
   }  
   
   if(sample=="JetTriggeredPlusMB"){
     outf = "result_PbPbHPPlusMB";
     cout<<"QUIII"<<endl;
     isSample=2;
   }  
   
   // ============== Open file and basic settings ===============   
   // Open Dntuple file
   
      // L1 trigger thresholds
   TCut l1CutMBHF2And = "L1_MinimumBiasHF2_AND==1";
   TCut l1Cut28 = "L1_SingleS1Jet28_BptxAND==1&&L1_SingleJet44_BptxAND==1";
   TCut l1Cut44 = "L1_SingleJet44_BptxAND==1";
   
   TCut l1CutMBHF2AndMB = "L1_MinimumBiasHF2_AND==1";
   TCut l1Cut28MB = "L1_SingleS1Jet28_BptxAND==1";
   TCut l1Cut44MB = "L1_SingleJet44_BptxAND==1";

   TCut triggerHLTselMB = "(HLT_HIL1MinimumBiasHF2AND_part1_v1 || HLT_HIL1MinimumBiasHF2AND_part2_v1 || HLT_HIL1MinimumBiasHF2AND_part3_v1)";
   TCut triggerHLTsel = "(HLT_HIPuAK4CaloJet40_Eta5p1_v1||HLT_HIPuAK4CaloJet60_Eta5p1_v1||HLT_HIPuAK4CaloJet80_Eta5p1_v1||HLT_HIPuAK4CaloJet100_Eta5p1_v1)";

   TFile *inf = new TFile("/data/HeavyFlavourRun2/Data2015/Dntuple/PbPb/ntD_EvtBase_20160511_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_skimhltbranches.root");
   //TFile *inf = new TFile("/data/dmeson2015/DataDntuple/checktriggered.root");
   TTree *ntDkpi = (TTree*)inf->Get("ntDkpi");
   TTree *ntHlt = (TTree*)inf->Get("ntHlt");
   TTree *ntSkim = (TTree*)inf->Get("ntSkim");
   
   ntDkpi->AddFriend(ntHlt);
   ntDkpi->AddFriend(ntSkim);   

   if(cent){
      TTree *ntHi = (TTree*)inf->Get("ntHi");
      ntDkpi->AddFriend(ntHi);
   }
   
   TFile *infMB = new TFile("/data/jisun/PbPb2015/Dntuple_crab_PbPb_HIMinimumBias3_ForestAOD_D0_tkpt0p7eta1p5_goldenjson_01292016.root");
   //TFile *infMB = new TFile("/data/dmeson2015/DataDntuple/smalltest.root");
   TTree *ntDkpiMB = (TTree*)infMB->Get("ntDkpi");
   TTree *ntHltMB = (TTree*)infMB->Get("ntHlt");
   TTree *ntSkimMB = (TTree*)infMB->Get("ntSkim");

   ntDkpiMB->SetName("ntDkpiMB");
   ntHltMB->SetName("ntHltMB");
   ntSkimMB->SetName("ntSkimMB");
   
   ntDkpiMB->AddFriend(ntHltMB);
   ntDkpiMB->AddFriend(ntSkimMB);   

   if(cent){
      TTree *ntHiMB = (TTree*)infMB->Get("ntHiMB");
      ntHiMB->SetName("ntHiMB");
      ntDkpiMB->AddFriend(ntHiMB);
   }

   // Define bin size and bin width for trigger turnon curve histograms

   const int nBin = 17;
   Float_t bins[nBin+1]={0,5,10,15,18,20,25,30,35,40,45,55,60,65,70,80,90,100};
   
   // Templates for plotting  
   TH1D *hTmp = new TH1D ("hTmp","",nBin,bins);
   TH1D *hTmp2 = new TH1D ("hTmp2","",nBin,bins);
      
   // D meson selection
   TCut DmassCut             = "(abs(Dmass-1.8696)<0.025)";
   TCut DmesonCut            = "(DsvpvDistance/DsvpvDisErr)>3.5&&Dchi2cl>0.10&&Dalpha<0.12";
   TCut DmesonDaughterTrkCut="Dtrk1highPurity&&Dtrk1Pt>8.5&&abs(Dtrk1Eta)<2.0&&Dtrk2highPurity&&Dtrk2Pt>8.5&&abs(Dtrk2Eta)<2.0";
   if (sideband) DmassCut = "(abs(Dmass-1.8696)>0.06 && abs(Dmass-1.8696)>0.12)";
   TCut CentCut = "hiBin<=20";

   // Final selection for D candidates for trigger turnon studies
   TCut DAnaCut = DmassCut && DmesonCut && DmesonDaughterTrkCut;
   if(cent) DAnaCut = DmassCut && DmesonCut && DmesonDaughterTrkCut && CentCut;	

   // HLT trigger thresholds
   //TCut HLTCut20 = "HLT_HIDmesonHITrackingGlobal_Dpt20_v1";
   TCut HLTCut20 = "HLT_HIDmesonHITrackingGlobal_Dpt20_v2";
   TCut HLTCut40 = "HLT_HIDmesonHITrackingGlobal_Dpt40_v1";
   TCut HLTCut60 = "HLT_HIDmesonHITrackingGlobal_Dpt60_v1";

   // ============== L1 trigger efficiency study ===============
   TCanvas *c = new TCanvas("c","",600,600);
   
   TGraphAsymmErrors* g20;
   TGraphAsymmErrors* g40;
   TGraphAsymmErrors* g60;
   //TTree *t,TTree *t2, char *variable, TCut preselection,TCut preselection2, TCut cut, int nBin, Float_t *bins
   
   if(isSample==1){
     g20  = getEfficiency(ntDkpiMB,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTselMB&&l1CutMBHF2AndMB), HLTCut20, nBin, bins);
     g40 = getEfficiency(ntDkpiMB,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTselMB&&l1Cut28MB), HLTCut40, nBin, bins);
     g60 = getEfficiency(ntDkpiMB,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTselMB&&l1Cut44MB), HLTCut60, nBin, bins);
   }

   if(isSample==0){
     g20  = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTsel&&l1CutMBHF2And), HLTCut20, nBin, bins);
     g40 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTsel&&l1Cut28), HLTCut40, nBin, bins);
     g60 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTsel&&l1Cut44), HLTCut60, nBin, bins);
   }
   if(isSample==2){
     g20  = getEfficiencySum(ntDkpi,ntDkpiMB,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTsel&&l1CutMBHF2And),TCut(DAnaCut&&triggerHLTselMB&&l1CutMBHF2AndMB), HLTCut20, nBin, bins);
     g40 = getEfficiencySum(ntDkpi,ntDkpiMB,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTsel&&l1Cut28),TCut(DAnaCut&&triggerHLTselMB&&l1Cut28MB), HLTCut40, nBin, bins);
     g60 = getEfficiencySum(ntDkpi,ntDkpiMB,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&triggerHLTsel&&l1Cut44),TCut(DAnaCut&&triggerHLTselMB&&l1Cut44MB), HLTCut60, nBin, bins);
   }


   hTmp->Draw();
   hTmp->SetXTitle("D Meson p_{T} (GeV/c)");
   hTmp->SetYTitle("D Meson HLT Efficiency");
   g20->SetLineColor(1);
   g20->SetMarkerColor(1);
   g20->Draw("pl same");

   g40->SetLineColor(2);
   g40->SetMarkerColor(2);
   g40->Draw("pl same");

   g60->SetLineColor(kGreen+2);
   g60->SetMarkerColor(kGreen+2);
   g60->Draw("pl same");

   TLegend *leg = new TLegend(0.53,0.2,0.93,0.6);
   leg->SetBorderSize(0);
   leg->SetFillStyle(0);
   leg->AddEntry(g20,"PbPb #sqrt{s} = 5.02 TeV","");
   leg->AddEntry(g20,"HLT D meson 20","pl");
   leg->AddEntry(g40,"HLT D meson 40","pl");
   leg->AddEntry(g60,"HLT D meson 60","pl");
   leg->Draw();

   c->SaveAs(outf+"/Dmeson-HIHLTriggerEfficiency.pdf");
   c->SaveAs(outf+"/Dmeson-HIHLTriggerEfficiency.png");
   c->SaveAs(outf+"/Dmeson-HIHLTriggerEfficiency.C");
   TFile *fouput=new TFile(outf+"/fefficiency.root","recreate");
   fouput->cd();
   g20->SetName("g20");
   g40->SetName("g40");
   g60->SetName("g60");
   g20->Write();
   g40->Write();
   g60->Write();
   fouput->Close();
}


void plotturnon(){
   

   const int nfiles=3;

   TFile *fouput=new TFile("result_PbPbHPPlusMB/fefficiency.root");
   TGraphAsymmErrors *g[nfiles];
   g[0]=(TGraphAsymmErrors*)fouput->Get("g20");
   g[1]=(TGraphAsymmErrors*)fouput->Get("g40");
   g[2]=(TGraphAsymmErrors*)fouput->Get("g60");

  TLegendEntry *entry[nfiles];
  TString label[nfiles] = {"D^{0} trigger p_{T}> 20", "D^{0} trigger p_{T}> 40", "D^{0} trigger p_{T}> 60"};
  const int nBin = 17;
  int colors[nfiles]={1,2,4};

  for (int m=0;m<nBin;m++){
      Double_t x,y;
      g[0]->GetPoint(m,x,y);  
      if (x>40){
      g[0]->SetPoint(m,0.,0.);
      g[0]->SetPointEYlow(m,0);
      g[0]->SetPointEYhigh(m,0);
      }
  }

  int whichthreshold[nBin]={0,0,0,0,0,0,1,1,1,2,2,2,2};

  double yvalue[nBin];
  double yvaluehigh[nBin];
  double yvaluelow[nBin];
  double xvalue[nBin];
  double xvaluehigh[nBin];
  double xvaluelow[nBin];


  for (int m=0;m<nBin;m++){
    int mybin=whichthreshold[m];

    Double_t x,y;
    g[mybin]->GetPoint(m,x,y);  

    yvalue[m]=y;
    yvaluehigh[m]=g[mybin]->GetErrorYhigh(m);
    yvaluelow[m]=g[mybin]->GetErrorYlow(m);
    
    xvalue[m]=x;
    xvaluehigh[m]=g[mybin]->GetErrorXhigh(m);
    xvaluelow[m]=g[mybin]->GetErrorXlow(m);
    
    cout<<xvalue[m]<<","<<xvaluelow[m]<<","<<xvaluehigh[m]<<","<<yvalue[m]<<","<<yvaluelow[m]<<","<<yvaluehigh[m]<<endl;

  }

  TGraphAsymmErrors* gaeTrigger = new TGraphAsymmErrors(nBin,xvalue,yvalue,xvaluelow,xvaluehigh,yvaluelow,yvaluehigh);
  gaeTrigger->SetName("gaeTrigger");
  gaeTrigger->SetMarkerStyle(20);
  gaeTrigger->SetMarkerSize(0.8);

  TH2F* hemptyRatio=new TH2F("hemptyRatio","",50,10,100.,10.,0.0,1.5);
  hemptyRatio->GetXaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->CenterTitle();
  hemptyRatio->GetYaxis()->SetTitle("HLT D meson trigger efficiency");
  hemptyRatio->GetXaxis()->SetTitle("D^{0} p_{T} (GeV/c)");
  hemptyRatio->GetXaxis()->SetTitleOffset(1.20);
  hemptyRatio->GetYaxis()->SetTitleOffset(1.14);//1.3
  hemptyRatio->GetXaxis()->SetTitleSize(0.055);
  hemptyRatio->GetYaxis()->SetTitleSize(0.055);
  hemptyRatio->GetXaxis()->SetTitleFont(42);
  hemptyRatio->GetYaxis()->SetTitleFont(42);
  hemptyRatio->GetXaxis()->SetLabelFont(42);
  hemptyRatio->GetYaxis()->SetLabelFont(42);
  hemptyRatio->GetXaxis()->SetLabelSize(0.045);
  hemptyRatio->GetYaxis()->SetLabelSize(0.045);  
  hemptyRatio->Draw();
  
  //TLegend *legendSigma=new TLegend(0.4714765,0.3496503,0.8003356,0.5244755,"");//0.5100806,0.5868644,0.8084677,0.7605932
  TLegend *legendSigma=new TLegend(0.50,0.30,0.80,0.52,"");//0.5100806,0.5868644,0.8084677,0.7605932
  legendSigma->SetBorderSize(0);
  legendSigma->SetLineColor(0);
  legendSigma->SetFillColor(0);
  legendSigma->SetFillStyle(1001);
  legendSigma->SetTextFont(42);
  //legendSigma->SetTextSize(0.045);
  legendSigma->SetTextSize(0.060);

   TCanvas *cFit = new TCanvas("c","",1200,600);
   hemptyRatio->Draw();
   gPad->SetLogx();
   TF1 *f= new TF1("f","[0]+[1]*x",20,100);
   gaeTrigger->Fit(f,"","",20,100);
   gStyle->SetOptFit(0);

   TF1 *fup= new TF1("f","[0]+[1]*x",20,100);
   TF1 *flow= new TF1("f","[0]+[1]*x",20,100);
    fup->SetParameter(1,f->GetParameter(1));
    flow->SetParameter(1,f->GetParameter(1));
    fup->SetParameter(0,f->GetParameter(0)+f->GetParError(0));
    flow->SetParameter(0,f->GetParameter(0)-f->GetParError(0));
    fup->Draw("same");
    flow->Draw("same");
    gaeTrigger->SetLineColor(1);
    gaeTrigger->SetMarkerColor(1);
    gaeTrigger->SetLineWidth(2);
    gaeTrigger->SetFillStyle(0); 
    gaeTrigger->Draw("epsame"); 
    cFit->SaveAs("result_PbPbHPPlusMB/Dmeson-HLTfinaltriggerefficiency.pdf");



   TCanvas *c = new TCanvas("c","",600,600);
   hemptyRatio->Draw();

  for (int ifile=0;ifile<nfiles;ifile++){
    g[ifile]->SetLineColor(colors[ifile]);
    g[ifile]->SetMarkerColor(colors[ifile]);
    g[ifile]->SetLineWidth(2);
    g[ifile]->SetFillStyle(0); 
    g[ifile]->Draw("epsame");  
    entry[ifile]=legendSigma->AddEntry(g[ifile],label[ifile].Data(),"f");
    entry[ifile]->SetTextFont(42);
    entry[ifile]->SetTextSize(0.045);
    entry[ifile]->SetLineColor(colors[ifile]);
    entry[ifile]->SetMarkerColor(colors[ifile]);
    
  }

  legendSigma->Draw("same");
  TLatex* texlumi = new TLatex(0.42,0.865,"404 #mub^{-1} (5.02 TeV PbPb)");
  texlumi->SetNDC();
  texlumi->SetTextFont(42);
  texlumi->SetTextSize(0.044);
  texlumi->SetLineWidth(2);
  texlumi->Draw();
  TLatex* texcms = new TLatex(0.22,0.90,"CMS");
  texcms->SetNDC();
  texcms->SetTextAlign(13);
  texcms->SetTextFont(62);//61
  texcms->SetTextSize(0.06);
  texcms->SetLineWidth(2);
  texcms->Draw();
  TLatex* texpre = new TLatex(0.22,0.84,"Performance");
  texpre->SetNDC();
  texpre->SetTextAlign(13);
  texpre->SetTextFont(52);
  texpre->SetTextSize(0.04);
  texpre->SetLineWidth(2);
  texpre->Draw();
  c->SaveAs("HLTDmesonEfficiency.pdf");


}

