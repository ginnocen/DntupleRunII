#include <TH1D.h>
#include <TTree.h>
#include <TLegend.h>
#include <TCut.h>
#include <TFile.h>
#include <TCanvas.h>  
#include <TGraphAsymmErrors.h>
#include "CMS_lumi.C"



// Take a tree, a variable and calculate the efficiency
TGraphAsymmErrors* getEfficiency(TTree *t, char *variable, TCut preselection, TCut cut, int nBin, Float_t *bins)
{
   static int count = 0;
   count++;
   TH1D *hPass = new TH1D (Form("hPass%d",count),"",nBin,bins);
   TH1D *hAll = new TH1D (Form("hAll%d",count),"",nBin,bins);
   t->Draw(Form("%s>>hAll%d",variable,count),preselection);
   t->Draw(Form("%s>>hPass%d",variable,count),preselection&&cut);

   TGraphAsymmErrors *g = new TGraphAsymmErrors;
   g->BayesDivide(hPass,hAll);
   return g;
}
//void plotTriggerForTDR(char *infname="/data/yjlee/dmeson/2015/trigger/mb.root")
void plotTrigger(char *infname="/data/jisun/ppMB2015fullstats/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016.root")
{  
   // ============== Open file and basic settings ===============   
   // Open Dntuple file
   TFile *inf = new TFile(infname);

   TTree *ntDkpi = (TTree*)inf->Get("ntDkpi");
   TTree *ntHlt = (TTree*)inf->Get("ntHlt");
   TTree *ntSkim = (TTree*)inf->Get("ntSkim");
   ntDkpi->AddFriend(ntHlt);
   ntDkpi->AddFriend(ntSkim);   

   // Define bin size and bin width for trigger turnon curve histograms
   const int nBin = 7;
   Float_t bins[nBin+1]={0,6,8,10,15,20,30,50};
   //const int nBin = 12;
   //Float_t bins[nBin+1]={0,5,6,8,10,12,15,20,25,30,35,40,70};

 
   // Templates for plotting  
   TH1D *hTmp2 = new TH1D ("hTmp2","",nBin,bins);
   
   // ============== Selection Criteria ===============

   // This MB sample has all pp MB 
   TCut mbCut = "(HLT_L1MinimumBiasHF1OR_part0_v1||  \
                             HLT_L1MinimumBiasHF1OR_part1_v1||  \
                             HLT_L1MinimumBiasHF1OR_part2_v1||  \
                             HLT_L1MinimumBiasHF1OR_part3_v1||  \
                             HLT_L1MinimumBiasHF1OR_part4_v1||  \
                             HLT_L1MinimumBiasHF1OR_part5_v1||  \
                             HLT_L1MinimumBiasHF1OR_part6_v1||  \
                             HLT_L1MinimumBiasHF1OR_part7_v1||  \
                             HLT_L1MinimumBiasHF1OR_part8_v1||  \
                             HLT_L1MinimumBiasHF1OR_part9_v1||  \
                             HLT_L1MinimumBiasHF1OR_part10_v1||  \
                             HLT_L1MinimumBiasHF1OR_part11_v1||  \
                             HLT_L1MinimumBiasHF1OR_part12_v1||  \
                             HLT_L1MinimumBiasHF1OR_part13_v1|| \
                             HLT_L1MinimumBiasHF1OR_part14_v1|| \
                             HLT_L1MinimumBiasHF1OR_part15_v1|| \
                             HLT_L1MinimumBiasHF1OR_part16_v1|| \
                             HLT_L1MinimumBiasHF1OR_part17_v1|| \
                             HLT_L1MinimumBiasHF1OR_part18_v1|| \
                             HLT_L1MinimumBiasHF1OR_part19_v1)";
   
   // L1 trigger thresholds
   TCut l1Cut16 = "L1_SingleJet16_BptxAND==1";
   TCut l1Cut24 = "L1_SingleJet24_BptxAND==1";
   TCut l1Cut28 = "L1_SingleJet28_BptxAND==1";
   TCut l1Cut40 = "L1_SingleJet40_BptxAND==1";

   // D meson selection
   TCut DmassCut             = "(abs(Dmass-1.8696)<0.03)";
   TCut DmesonCut            = "Dy>-1.&&Dy<1&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.0&&Dchi2cl>0.05&&Dalpha<0.12";
   TCut DmesonDaughterTrkCut = "Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)";


   // Final selection for D candidates for trigger turnon studies
   TCut DAnaCut = DmassCut && DmesonCut && DmesonDaughterTrkCut;

   // HLT trigger thresholds
   TCut HLTCut8  = "HLT_DmesonPPTrackingGlobal_Dpt8_v1";
   TCut HLTCut15 = "HLT_DmesonPPTrackingGlobal_Dpt15_v1";
   TCut HLTCut20 = "HLT_DmesonPPTrackingGlobal_Dpt20_v1";
   TCut HLTCut30 = "HLT_DmesonPPTrackingGlobal_Dpt30_v1";

   // ============== L1 trigger efficiency study ===============
   
  int W = 600;
  int H = 600;

  int H_ref = 600; 
  int W_ref = 600; 

  // references for T, B, L, R
  float T = 0.08*H_ref;
  float B = 0.14*H_ref; 
  float L = 0.14*W_ref;
  float R = 0.08*W_ref;


  TString canvName = "TRDFigure_Centrality";
  TCanvas* c = new TCanvas(canvName,canvName,50,50,W,H);
  c->cd();
  c->SetFillColor(0);
  c->SetBorderMode(0);
  c->SetFrameFillStyle(0);
  c->SetFrameBorderMode(0);
  c->SetLeftMargin( L/W );
  c->SetRightMargin( R/W );
  c->SetTopMargin( T/H );
  c->SetBottomMargin( B/H );
  
  
    TH2D *hTmp = new TH2D ("hTmp","",100,0,60,100,0,1.4);
    hTmp->GetXaxis()->SetTitle("p_{T} (D^{0}) (GeV)");  
    hTmp->GetYaxis()->SetTitleOffset(1.15);
    hTmp->GetXaxis()->SetTitleOffset(0.95);
    hTmp->GetYaxis()->SetTitle("Efficiency");  
    hTmp->GetYaxis()->CenterTitle();
    hTmp->GetXaxis()->CenterTitle();
    hTmp->SetMaximum(1.4);
    hTmp->GetXaxis()->SetTitleFont(42);
    hTmp->GetXaxis()->SetLabelFont(42);
    hTmp->GetXaxis()->SetTitleSize(0.06);
    hTmp->GetXaxis()->SetLabelSize(0.05);
    hTmp->GetYaxis()->SetTitleFont(42);
    hTmp->GetYaxis()->SetLabelFont(42);
    hTmp->GetYaxis()->SetTitleSize(0.06);
    hTmp->GetYaxis()->SetLabelSize(0.05);
       

   TGraphAsymmErrors* g8  = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&mbCut&&l1Cut16), HLTCut8, nBin, bins);
   TGraphAsymmErrors* g15 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&mbCut&&l1Cut24), HLTCut15, nBin, bins);
   TGraphAsymmErrors* g20 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&mbCut&&l1Cut28), HLTCut20, nBin, bins);
   TGraphAsymmErrors* g30 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&mbCut&&l1Cut40), HLTCut30, nBin, bins);

/*
   TGraphAsymmErrors* g8  = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&l1Cut16), HLTCut8, nBin, bins);
   TGraphAsymmErrors* g15 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&l1Cut24), HLTCut15, nBin, bins);
   TGraphAsymmErrors* g20 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&l1Cut28), HLTCut20, nBin, bins);
   TGraphAsymmErrors* g30 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&l1Cut40), HLTCut30, nBin, bins);
*/
    hTmp->Draw();

   g8->SetLineColor(1);
   g8->SetMarkerColor(1);
   g8->Draw("p same");
   
   g15->SetLineColor(2);
   g15->SetMarkerColor(2);
   g15->Draw("p same");

   g20->SetLineColor(4);
   g20->SetMarkerColor(4);
   g20->Draw("p same");
   
   g30->SetLineColor(kGreen+2);
   g30->SetMarkerColor(kGreen+2);
   //g30->Draw("p same");
   
 TLegend *legend=new TLegend(0.4579866,0.2472028,0.8389262,0.4342657,"");
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.04);

  TLegendEntry *ent_g8=legend->AddEntry(g8,"HLT D meson p_{T} #geq 8","pl");
  ent_g8->SetTextFont(42);
  ent_g8->SetLineColor(1);
  ent_g8->SetMarkerColor(1);
  TLegendEntry *ent_g15=legend->AddEntry(g15,"HLT D meson p_{T} #geq15","pl");
  ent_g15->SetTextFont(42);
  ent_g15->SetLineColor(1);
  ent_g15->SetMarkerColor(1);
  TLegendEntry *ent_g20=legend->AddEntry(g20,"HLT D meson p_{T} #geq 20","pl");
  ent_g20->SetTextFont(42);
  ent_g20->SetLineColor(1);
  ent_g20->SetMarkerColor(1);
  //TLegendEntry *ent_g30=legend->AddEntry(g30,"HLT D meson p_{T} #geq 30","pl");
  //ent_g30->SetTextFont(42);
  //ent_g30->SetLineColor(1);
  //ent_g30->SetMarkerColor(1);
  legend->Draw("same");
   
   CMS_lumi( c, 1, 11 );
   
   
  TLatex * tlatexeff=new TLatex(0.2079866,0.70,"HLT efficiency with respect to L1 seed");
  tlatexeff->SetNDC();
  tlatexeff->SetTextColor(1);
  tlatexeff->SetTextFont(42);
  tlatexeff->SetTextSize(0.040);
 // tlatexeff->Draw("same");

   

   c->SaveAs("result/Dmeson-HLTriggerEfficiency.pdf");
   c->SaveAs("result/Dmeson-HLTriggerEfficiency.png");
   c->SaveAs("result/Dmeson-HLTriggerEfficiency.C");

   
   // ============== HLT trigger efficiency study ===============
   TCanvas *c2 = new TCanvas("c2","",600,600);
   
   TGraphAsymmErrors* gL16 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&mbCut&&"L1_SingleJet16_BptxAND_Prescl==1"), l1Cut16, nBin, bins);
   TGraphAsymmErrors* gL24 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&mbCut&&"L1_SingleJet24_BptxAND_Prescl==1"), l1Cut24, nBin, bins);
   TGraphAsymmErrors* gL28 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&mbCut&&"L1_SingleJet28_BptxAND_Prescl==1"), l1Cut28, nBin, bins);
   TGraphAsymmErrors* gL40 = getEfficiency(ntDkpi,Form("Max$(Dpt*(%s))",DAnaCut.GetTitle()), TCut(DAnaCut&&mbCut&&"L1_SingleJet40_BptxAND_Prescl==1"), l1Cut40, nBin, bins);
   
   hTmp2->Draw();
   hTmp2->SetXTitle("p_{T}  (D^{0})(GeV/c)");
   hTmp2->SetYTitle("L1 Trigger Efficiency");
   
   gL16->SetMarkerColor(1);
   gL16->SetLineColor(1);
   gL16->Draw("p same");

   gL24->SetMarkerColor(2);
   gL24->SetLineColor(2);
   gL24->Draw("p same");

   gL28->SetMarkerColor(4);
   gL28->SetLineColor(4);
   gL28->Draw("p same");

   gL40->SetMarkerColor(kGreen+2);
   gL40->SetLineColor(kGreen+2);
   gL40->Draw("p same");

   TLegend *leg2 = new TLegend(0.4916107,0.3059441,0.8322148,0.4912587);
   leg2->SetBorderSize(0);
   leg2->SetFillStyle(0); 
   leg2->AddEntry(gL16,"pp #sqrt{s} = 5.02 TeV","");
   leg2->AddEntry(gL16,"Level 1 Jet 16","pl");
   leg2->AddEntry(gL24,"Level 1 Jet 24","pl");
   leg2->AddEntry(gL28,"Level 1 Jet 28","pl");
   leg2->AddEntry(gL40,"Level 1 Jet 40","pl");
   leg2->Draw();

   c2->SaveAs("result/Dmeson-L1TriggerEfficiency.pdf");
   c2->SaveAs("result/Dmeson-L1TriggerEfficiency.png");
   c2->SaveAs("result/Dmeson-L1TriggerEfficiency.C");
   
   
   // ============== Plot an example D mass distribution ===============
   TCanvas *c3 = new TCanvas("c3","",600,600);
   ntDkpi->Draw("Dmass>>h(100,1.7696,1.9696)",DmesonCut&&DmesonDaughterTrkCut&&mbCut&&l1Cut16);
   
   // ..done 
}

