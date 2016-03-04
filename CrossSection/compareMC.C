void compareMC(int value1=30,int value2=50, bool integratedonly=false){

  TFile *f1=new TFile(Form("pthat%d.root",value1));
  TFile *f2=new TFile(Form("pthat%d.root",value2));
  TFile *fall=new TFile("PPALL.root");
  TFile *fallnoweight=new TFile("PPALLnoweight.root");

  TH1D *h1=(TH1D*)f1->Get("hEff");
  TH1D *h2=(TH1D*)f2->Get("hEff");
  TH1D *hall=(TH1D*)fall->Get("hEff");
  TH1D *hallnoweight=(TH1D*)fallnoweight->Get("hEff");
  TH2F* hemptyPthat=new TH2F("hemptyPthat","",50,0,100.,10,0.,2.);  
  hemptyPthat->GetXaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->CenterTitle();
  hemptyPthat->GetYaxis()->SetTitle("Efficiencies");
  hemptyPthat->GetXaxis()->SetTitle("p_{T}");
  hemptyPthat->GetXaxis()->SetTitleOffset(0.9);
  hemptyPthat->GetYaxis()->SetTitleOffset(0.95);
  hemptyPthat->GetXaxis()->SetTitleSize(0.05);
  hemptyPthat->GetYaxis()->SetTitleSize(0.05);
  hemptyPthat->GetXaxis()->SetTitleFont(42);
  hemptyPthat->GetYaxis()->SetTitleFont(42);
  hemptyPthat->GetXaxis()->SetLabelFont(42);
  hemptyPthat->GetYaxis()->SetLabelFont(42);
  hemptyPthat->GetXaxis()->SetLabelSize(0.035);
  hemptyPthat->GetYaxis()->SetLabelSize(0.035);  
  hemptyPthat->SetMaximum(2);
  hemptyPthat->SetMinimum(0.);


  TCanvas*c=new TCanvas("c","c",500,500);
  c->cd();
  h1->SetLineColor(1);
  h2->SetLineColor(2);
  hall->SetLineColor(4);
  hallnoweight->SetLineColor(6);
  h1->SetMarkerColor(1);
  h2->SetMarkerColor(2);
  hall->SetMarkerColor(4);
  hallnoweight->SetMarkerColor(6);
  
  hemptyPthat->Draw();
  if(!integratedonly)h1->Draw("same");
  if(!integratedonly)h2->Draw("same");
  hall->Draw("same");
  hallnoweight->Draw("same");
  TLegend *legend=new TLegend(0.2100806,0.6068644,0.5084677,0.7605932,"");
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
  }
  TLegendEntry *ent_pthatall=legend->AddEntry(hall,"efficiency sample pthat all","pf");
  ent_pthatall->SetTextFont(42);
  ent_pthatall->SetLineColor(4);
  ent_pthatall->SetMarkerColor(4);
  TLegendEntry *ent_pthatallnoweigth=legend->AddEntry(hallnoweight,"efficiency sample pthat all unweigted","pf");
  ent_pthatallnoweigth->SetTextFont(42);
  ent_pthatallnoweigth->SetLineColor(4);
  ent_pthatallnoweigth->SetMarkerColor(4);
  legend->Draw("same");
  if(!integratedonly) c->SaveAs(Form("canvas_phat%d_pthat%d.pdf",value1,value2));
  else c->SaveAs("canvas_phatintegrated.pdf");
}
