#include "uti.h"
#include "parameters.h"
#include "TLegendEntry.h"

void compareMC(){

  gStyle->SetOptTitle(0);
  gStyle->SetOptStat(0);
  gStyle->SetEndErrorSize(0);
  gStyle->SetMarkerStyle(20);

  
  int value1=10; int value2=30; int value3=50; bool integratedonly=false;

  TFile *f1=new TFile(Form("ROOTfiles/pthat%d.root",value1));
  TFile *f2=new TFile(Form("ROOTfiles/pthat%d.root",value2));
  TFile *f3=new TFile(Form("ROOTfiles/pthat%d.root",value3));
  TFile *fallnoweight=new TFile("ROOTfiles/pthatall.root");

  TH1D *h1=(TH1D*)f1->Get("hEff");
  TH1D *h2=(TH1D*)f2->Get("hEff");
  TH1D *h3=(TH1D*)f3->Get("hEff");
  TH1D *hallnoweight=(TH1D*)fallnoweight->Get("hEff");
  TH2F* hemptyPthat=new TH2F("hemptyPthat","",50,0,100.,10,0.01,5.);  
  hemptyPthat->GetXaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->SetTitle("Efficiencies");
  hemptyPthat->GetXaxis()->SetTitle("p_{T}");
  hemptyPthat->GetXaxis()->SetTitleOffset(0.9);
  hemptyPthat->GetYaxis()->SetTitleOffset(1.0);
  hemptyPthat->GetXaxis()->SetTitleSize(0.05);
  hemptyPthat->GetYaxis()->SetTitleSize(0.05);
  hemptyPthat->GetXaxis()->SetTitleFont(42);
  hemptyPthat->GetYaxis()->SetTitleFont(42);
  hemptyPthat->GetXaxis()->SetLabelFont(42);
  hemptyPthat->GetYaxis()->SetLabelFont(42);
  hemptyPthat->GetXaxis()->SetLabelSize(0.035);
  hemptyPthat->GetYaxis()->SetLabelSize(0.035);  


  TCanvas*c=new TCanvas("c","c",500,500);
  c->cd();
  gPad->SetLogy();
  gPad->SetLogx();
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  h3->SetLineColor(4);
  hallnoweight->SetLineColor(6);
  h1->SetMarkerColor(1);
  h2->SetMarkerColor(2);
  h3->SetMarkerColor(4);
  hallnoweight->SetMarkerColor(6);
  
  hemptyPthat->Draw();
  if(!integratedonly)h1->Draw("same");
  if(!integratedonly)h2->Draw("same");
  if(!integratedonly)h3->Draw("same");
  hallnoweight->Draw("same");
  TLegend *legend=new TLegend(0.2100806,0.7068644,0.5084677,0.8605932,"");
  legend->SetBorderSize(0);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetTextFont(42);
  legend->SetTextSize(0.045);
  if(!integratedonly){
  TLegendEntry *ent_pthat1=legend->AddEntry(h1,Form("efficiency sample pthat=%d",value1),"pf");
  ent_pthat1->SetTextFont(42);
  ent_pthat1->SetLineColor(1);
  ent_pthat1->SetMarkerColor(1);
  TLegendEntry *ent_pthat2=legend->AddEntry(h2,Form("efficiency sample pthat=%d",value2),"pf");
  ent_pthat2->SetTextFont(42);
  ent_pthat2->SetLineColor(2);
  ent_pthat2->SetMarkerColor(2);
  TLegendEntry *ent_pthat3=legend->AddEntry(h3,Form("efficiency sample pthat=%d",value3),"pf");
  ent_pthat3->SetTextFont(42);
  ent_pthat3->SetLineColor(4);
  ent_pthat3->SetMarkerColor(4);
  }
  TLegendEntry *ent_pthatallnoweigth=legend->AddEntry(hallnoweight,"efficiency sample pthat all","pf");
  ent_pthatallnoweigth->SetTextFont(42);
  ent_pthatallnoweigth->SetLineColor(6);
  ent_pthatallnoweigth->SetMarkerColor(6);
  legend->Draw("same");
  if(!integratedonly) c->SaveAs(Form("canvasEfficiency_phat%d_pthat%d_pthat%d.pdf",value1,value2,value3));
  else c->SaveAs("canvas_phatintegrated.pdf");
}


int main(int argc, char *argv[])
{
  compareMC();
  return 1;
}

