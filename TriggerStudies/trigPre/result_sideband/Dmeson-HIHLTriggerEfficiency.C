void Dmeson-HIHLTriggerEfficiency()
{
//=========Macro generated from canvas: c/
//=========  (Thu May  5 00:54:59 2016) by ROOT version6.02/10
   TCanvas *c = new TCanvas("c", "",0,0,600,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c->Range(-12.68293,-0.1664634,84.87805,1.114024);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(2);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.13);
   c->SetRightMargin(0.05);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.13);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   c->SetFrameFillStyle(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[16] = {0, 5, 10, 15, 18, 20, 25, 30, 35, 40, 45, 55, 60, 65, 70, 80}; 
   
   TH1D *hTmp1 = new TH1D("hTmp1","",15, xAxis1);
   hTmp1->SetLineStyle(0);
   hTmp1->SetMarkerStyle(20);
   hTmp1->GetXaxis()->SetTitle("D Meson p_{T} (GeV/c)");
   hTmp1->GetXaxis()->SetLabelFont(42);
   hTmp1->GetXaxis()->SetLabelOffset(0.007);
   hTmp1->GetXaxis()->SetLabelSize(0.05);
   hTmp1->GetXaxis()->SetTitleSize(0.06);
   hTmp1->GetXaxis()->SetTitleOffset(0.9);
   hTmp1->GetXaxis()->SetTitleFont(42);
   hTmp1->GetYaxis()->SetTitle("D Meson HLT Efficiency");
   hTmp1->GetYaxis()->SetLabelFont(42);
   hTmp1->GetYaxis()->SetLabelOffset(0.007);
   hTmp1->GetYaxis()->SetLabelSize(0.05);
   hTmp1->GetYaxis()->SetTitleSize(0.06);
   hTmp1->GetYaxis()->SetTitleOffset(1.05);
   hTmp1->GetYaxis()->SetTitleFont(42);
   hTmp1->GetZaxis()->SetLabelFont(42);
   hTmp1->GetZaxis()->SetLabelOffset(0.007);
   hTmp1->GetZaxis()->SetLabelSize(0.05);
   hTmp1->GetZaxis()->SetTitleSize(0.06);
   hTmp1->GetZaxis()->SetTitleFont(42);
   hTmp1->Draw("");
   
   Double_t _fx3001[12] = {
   16.5,
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   50,
   57.5,
   62.5,
   67.5,
   75};
   Double_t _fy3001[12] = {
   0,
   0.07017544,
   0.9342105,
   0.9457364,
   0.915493,
   0.9482759,
   0.9565217,
   0.94,
   0.9090909,
   1,
   1,
   1};
   Double_t _felx3001[12] = {
   1.5,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   2.5,
   2.5,
   5};
   Double_t _fely3001[12] = {
   0,
   0.02898372,
   0.01772732,
   0.02238829,
   0.03691587,
   0.03474246,
   0.05875471,
   0.03988195,
   0.1098839,
   0.2496484,
   0.3181538,
   0.1513615};
   Double_t _fehx3001[12] = {
   1.5,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   2.5,
   2.5,
   5};
   Double_t _fehy3001[12] = {
   0.04322466,
   0.03904648,
   0.01518357,
   0.0177534,
   0.0291466,
   0.02429136,
   0.03087939,
   0.02805368,
   0.06240274,
   0,
   0,
   0};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(12,_fx3001,_fy3001,_felx3001,_fehx3001,_fely3001,_fehy3001);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3001 = new TH1F("Graph_Graph3001","",100,8.5,86.5);
   Graph_Graph3001->SetMinimum(0);
   Graph_Graph3001->SetMaximum(1.1);
   Graph_Graph3001->SetDirectory(0);
   Graph_Graph3001->SetStats(0);
   Graph_Graph3001->SetLineStyle(0);
   Graph_Graph3001->SetMarkerStyle(20);
   Graph_Graph3001->GetXaxis()->SetLabelFont(42);
   Graph_Graph3001->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph3001->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph3001->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph3001->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph3001->GetXaxis()->SetTitleFont(42);
   Graph_Graph3001->GetYaxis()->SetLabelFont(42);
   Graph_Graph3001->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph3001->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph3001->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph3001->GetYaxis()->SetTitleOffset(1.05);
   Graph_Graph3001->GetYaxis()->SetTitleFont(42);
   Graph_Graph3001->GetZaxis()->SetLabelFont(42);
   Graph_Graph3001->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph3001->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph3001->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3001);
   
   grae->Draw("pl ");
   
   Double_t _fx3002[12] = {
   16.5,
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   50,
   57.5,
   62.5,
   67.5,
   75};
   Double_t _fy3002[12] = {
   0,
   0.1052632,
   0.01724138,
   0.02666667,
   0,
   0.02941176,
   0.9166667,
   0.95,
   1,
   1,
   1,
   1};
   Double_t _felx3002[12] = {
   1.5,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   2.5,
   2.5,
   5};
   Double_t _fely3002[12] = {
   0,
   0.05621981,
   0.009699312,
   0.01492036,
   0,
   0.02109664,
   0.1025138,
   0.0429307,
   0.1742602,
   0.4369725,
   0.3181538,
   0.3181538};
   Double_t _fehx3002[12] = {
   1.5,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   2.5,
   2.5,
   5};
   Double_t _fehy3002[12] = {
   0.08458096,
   0.0829325,
   0.01557656,
   0.02374158,
   0.02185107,
   0.04111185,
   0.05751889,
   0.02759841,
   0,
   0,
   0,
   0};
   grae = new TGraphAsymmErrors(12,_fx3002,_fy3002,_felx3002,_fehx3002,_fely3002,_fehy3002);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3002 = new TH1F("Graph_Graph3002","",100,8.5,86.5);
   Graph_Graph3002->SetMinimum(0);
   Graph_Graph3002->SetMaximum(1.1);
   Graph_Graph3002->SetDirectory(0);
   Graph_Graph3002->SetStats(0);
   Graph_Graph3002->SetLineStyle(0);
   Graph_Graph3002->SetMarkerStyle(20);
   Graph_Graph3002->GetXaxis()->SetLabelFont(42);
   Graph_Graph3002->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph3002->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph3002->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph3002->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph3002->GetXaxis()->SetTitleFont(42);
   Graph_Graph3002->GetYaxis()->SetLabelFont(42);
   Graph_Graph3002->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph3002->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph3002->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph3002->GetYaxis()->SetTitleOffset(1.05);
   Graph_Graph3002->GetYaxis()->SetTitleFont(42);
   Graph_Graph3002->GetZaxis()->SetLabelFont(42);
   Graph_Graph3002->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph3002->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph3002->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3002);
   
   grae->Draw("pl ");
   
   Double_t _fx3003[12] = {
   16.5,
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   50,
   57.5,
   62.5,
   67.5,
   75};
   Double_t _fy3003[12] = {
   0,
   0,
   0,
   0.01470588,
   0,
   0,
   0.0952381,
   0.02222222,
   0,
   1,
   1,
   1};
   Double_t _felx3003[12] = {
   1.5,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   2.5,
   2.5,
   5};
   Double_t _fely3003[12] = {
   0,
   0,
   0,
   0.01065679,
   0,
   0,
   0.05117451,
   0.01601984,
   0,
   0.2496484,
   0.3181538,
   0.1513615};
   Double_t _fehx3003[12] = {
   1.5,
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   2.5,
   2.5,
   5};
   Double_t _fehy3003[12] = {
   0.1513615,
   0.09129775,
   0.01480942,
   0.0213032,
   0.02271511,
   0.02636377,
   0.07621597,
   0.03160774,
   0.09917226,
   0,
   0,
   0};
   grae = new TGraphAsymmErrors(12,_fx3003,_fy3003,_felx3003,_fehx3003,_fely3003,_fehy3003);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(1);

   Int_t ci;      // for color index setting
   TColor *color; // for color definition with alpha
   ci = TColor::GetColor("#009900");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#009900");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3003 = new TH1F("Graph_Graph3003","",100,8.5,86.5);
   Graph_Graph3003->SetMinimum(0);
   Graph_Graph3003->SetMaximum(1.1);
   Graph_Graph3003->SetDirectory(0);
   Graph_Graph3003->SetStats(0);
   Graph_Graph3003->SetLineStyle(0);
   Graph_Graph3003->SetMarkerStyle(20);
   Graph_Graph3003->GetXaxis()->SetLabelFont(42);
   Graph_Graph3003->GetXaxis()->SetLabelOffset(0.007);
   Graph_Graph3003->GetXaxis()->SetLabelSize(0.05);
   Graph_Graph3003->GetXaxis()->SetTitleSize(0.06);
   Graph_Graph3003->GetXaxis()->SetTitleOffset(0.9);
   Graph_Graph3003->GetXaxis()->SetTitleFont(42);
   Graph_Graph3003->GetYaxis()->SetLabelFont(42);
   Graph_Graph3003->GetYaxis()->SetLabelOffset(0.007);
   Graph_Graph3003->GetYaxis()->SetLabelSize(0.05);
   Graph_Graph3003->GetYaxis()->SetTitleSize(0.06);
   Graph_Graph3003->GetYaxis()->SetTitleOffset(1.05);
   Graph_Graph3003->GetYaxis()->SetTitleFont(42);
   Graph_Graph3003->GetZaxis()->SetLabelFont(42);
   Graph_Graph3003->GetZaxis()->SetLabelOffset(0.007);
   Graph_Graph3003->GetZaxis()->SetLabelSize(0.05);
   Graph_Graph3003->GetZaxis()->SetTitleSize(0.06);
   Graph_Graph3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3003);
   
   grae->Draw("pl ");
   
   TLegend *leg = new TLegend(0.53,0.2,0.93,0.6,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);
   TLegendEntry *entry=leg->AddEntry("","PbPb #sqrt{s} = 5.02 TeV","");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(21);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","HLT D meson 20","pl");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","HLT D meson 40","pl");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   entry=leg->AddEntry("","HLT D meson 60","pl");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(62);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
