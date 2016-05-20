void D0DcaM()
{
  TFile* f1 = new TFile("bFeedDownPbPbMB.hist.root");
  TH3D* hPtMD0Dca = (TH3D*)f1->Get("hPtMD0Dca");
  hPtMD0Dca->GetXaxis()->SetRange(1,1);
  hPtMD0Dca->GetYaxis()->SetRangeUser(1.765,1.79);
  TH1D* hD0Dca1 = hPtMD0Dca->Project3D("z")->Clone("hD0Dca1");
  hPtMD0Dca->GetYaxis()->SetRangeUser(1.94,1.965);
  TH1D* hD0Dca2 = hPtMD0Dca->Project3D("z")->Clone("hD0Dca2");

  TCanvas* c1 = new TCanvas();
  c1->SetLogy();
  hD0Dca1->SetMarkerStyle(20);
  hD0Dca2->SetMarkerStyle(20);
  hD0Dca2->SetMarkerColor(2);
  hD0Dca2->SetLineColor(2);
  hD0Dca1->Draw();
  hD0Dca2->Draw("same");
}
