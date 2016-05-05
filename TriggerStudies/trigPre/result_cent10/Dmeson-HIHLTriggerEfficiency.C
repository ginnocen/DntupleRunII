void Dmeson-HIHLTriggerEfficiency()
{
//=========Macro generated from canvas: c/
//=========  (Thu May  5 01:01:57 2016) by ROOT version6.02/10
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
   
   Double_t _fx3001[11] = {
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
   75};
   Double_t _fy3001[11] = {
   0,
   0.06896552,
   0.8761062,
   0.98,
   1,
   1,
   0.7777778,
   1,
   1,
   1,
   1};
   Double_t _felx3001[11] = {
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
   5};
   Double_t _fely3001[11] = {
   0,
   0.03764367,
   0.03310196,
   0.02860099,
   0.04165758,
   0.06928609,
   0.1035062,
   0.05582399,
   0.2496484,
   0.2496484,
   0.2496484};
   Double_t _fehx3001[11] = {
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
   5};
   Double_t _fehy3001[11] = {
   0.3181538,
   0.05749455,
   0.02869668,
   0.01444014,
   0,
   0,
   0.08449391,
   0,
   0,
   0,
   0};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(11,_fx3001,_fy3001,_felx3001,_fehx3001,_fely3001,_fehy3001);
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
   
   Double_t _fx3002[9] = {
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   50,
   62.5,
   75};
   Double_t _fy3002[9] = {
   0.1111111,
   0,
   0,
   0,
   0,
   0.6923077,
   0.9,
   1,
   1};
   Double_t _felx3002[9] = {
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   5};
   Double_t _fely3002[9] = {
   0.05913286,
   0,
   0,
   0,
   0,
   0.1286012,
   0.1183613,
   0.2496484,
   0.3181538};
   Double_t _fehx3002[9] = {
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   5};
   Double_t _fehy3002[9] = {
   0.08674482,
   0.01540516,
   0.03322531,
   0.05088055,
   0.0787842,
   0.1111246,
   0.0681878,
   0,
   0};
   grae = new TGraphAsymmErrors(9,_fx3002,_fy3002,_felx3002,_fehx3002,_fely3002,_fehy3002);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3002 = new TH1F("Graph_Graph3002","",100,11.8,86.2);
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
   
   Double_t _fx3003[10] = {
   19,
   22.5,
   27.5,
   32.5,
   37.5,
   42.5,
   50,
   57.5,
   62.5,
   75};
   Double_t _fy3003[10] = {
   0.1333333,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   1,
   1};
   Double_t _felx3003[10] = {
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   2.5,
   5};
   Double_t _fely3003[10] = {
   0.07000057,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0.2496484,
   0.2496484};
   Double_t _fehx3003[10] = {
   1,
   2.5,
   2.5,
   2.5,
   2.5,
   2.5,
   5,
   2.5,
   2.5,
   5};
   Double_t _fehy3003[10] = {
   0.1005408,
   0.02030624,
   0.03421472,
   0.06183102,
   0.07373067,
   0.06183102,
   0.0586742,
   0.2496484,
   0,
   0};
   grae = new TGraphAsymmErrors(10,_fx3003,_fy3003,_felx3003,_fehx3003,_fely3003,_fehy3003);
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
   
   TH1F *Graph_Graph3003 = new TH1F("Graph_Graph3003","",100,11.8,86.2);
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
