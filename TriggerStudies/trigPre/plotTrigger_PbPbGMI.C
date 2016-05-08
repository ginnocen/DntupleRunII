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
   TCut triggerHLTsel = "(HLT_HIPuAK4CaloJet40_Eta5p1_v1||HLT_HIPuAK4CaloJet60_Eta5p1_v1||HLT_HIPuAK4CaloJet80_Eta5p1_v1)";

   TFile *inf = new TFile("/data/wangj/Data2015/Dntuple/PbPb/ntD_EvtBase_20160405_HIHardProbes_DfinderData_PbPb_20160402_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_jettriggerskim.root");
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
   const int nBin = 15;
   Float_t bins[nBin+1]={0,5,10,15,18,20,25,30,35,40,45,55,60,65,70,80};
 
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

