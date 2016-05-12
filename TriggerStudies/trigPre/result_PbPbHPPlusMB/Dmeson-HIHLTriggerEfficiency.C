void Dmeson-HIHLTriggerEfficiency()
{
//=========Macro generated from canvas: c/
//=========  (Thu May 12 01:45:38 2016) by ROOT version6.02/10
   TCanvas *c = new TCanvas("c", "",240,1222,600,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c->Range(-22.66667,-0.196875,110.6667,1.115625);
   c->SetFillColor(0);
   c->SetBorderMode(0);
   c->SetBorderSize(0);
   c->SetTickx(1);
   c->SetTicky(1);
   c->SetLeftMargin(0.17);
   c->SetRightMargin(0.08);
   c->SetTopMargin(0.05);
   c->SetBottomMargin(0.15);
   c->SetFrameLineColor(0);
   c->SetFrameBorderMode(0);
   c->SetFrameLineColor(0);
   c->SetFrameBorderMode(0);
   Double_t xAxis1[18] = {0, 5, 10, 15, 18, 20, 25, 30, 35, 40, 45, 55, 60, 65, 70, 80, 90, 100}; 
   
   TH1D *hTmp1 = new TH1D("hTmp1","",17, xAxis1);
   hTmp1->SetLineStyle(0);
   hTmp1->SetMarkerStyle(20);
   hTmp1->GetXaxis()->SetTitle("D Meson p_{T} (GeV/c)");
   hTmp1->GetXaxis()->SetLabelFont(42);
   hTmp1->GetXaxis()->SetLabelOffset(0.01);
   hTmp1->GetXaxis()->SetLabelSize(0.045);
   hTmp1->GetXaxis()->SetTitleSize(0.055);
   hTmp1->GetXaxis()->SetTitleFont(42);
   hTmp1->GetYaxis()->SetTitle("D Meson HLT Efficiency");
   hTmp1->GetYaxis()->SetLabelFont(42);
   hTmp1->GetYaxis()->SetLabelOffset(0.01);
   hTmp1->GetYaxis()->SetLabelSize(0.045);
   hTmp1->GetYaxis()->SetTitleSize(0.055);
   hTmp1->GetYaxis()->SetTitleOffset(1.3);
   hTmp1->GetYaxis()->SetTitleFont(42);
   hTmp1->GetZaxis()->SetLabelFont(42);
   hTmp1->GetZaxis()->SetLabelSize(0.045);
   hTmp1->GetZaxis()->SetTitleSize(0.035);
   hTmp1->GetZaxis()->SetTitleFont(42);
   hTmp1->Draw("");
   
   Double_t _fx3001[14] = {
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
   75,
   85,
   95};
   Double_t _fy3001[14] = {
   0,
   0.05504587,
   0.9002494,
   0.9061033,
   0.8922156,
   0.9072165,
   0.8888889,
   0.9449541,
   1,
   0.9,
   1,
   1,
   1,
   1};
   Double_t _felx3001[14] = {
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
   5,
   5,
   5};
   Double_t _fely3001[14] = {
   0,
   0.01926017,
   0.01563173,
   0.02125523,
   0.02553162,
   0.03222741,
   0.04046567,
   0.0247386,
   0.04020013,
   0.07943508,
   0.08458096,
   0.05323778,
   0.119839,
   0.2052842};
   Double_t _fehx3001[14] = {
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
   5,
   5,
   5};
   Double_t _fehy3001[14] = {
   0.05088055,
   0.0247386,
   0.01430147,
   0.01871687,
   0.02241105,
   0.02665508,
   0.03333727,
   0.01926017,
   0,
   0.05357914,
   0,
   0,
   0,
   0};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(14,_fx3001,_fy3001,_felx3001,_fehx3001,_fely3001,_fehy3001);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3001 = new TH1F("Graph_Graph3001","",100,6.5,108.5);
   Graph_Graph3001->SetMinimum(0);
   Graph_Graph3001->SetMaximum(1.1);
   Graph_Graph3001->SetDirectory(0);
   Graph_Graph3001->SetStats(0);
   Graph_Graph3001->SetLineStyle(0);
   Graph_Graph3001->SetMarkerStyle(20);
   Graph_Graph3001->GetXaxis()->SetLabelFont(42);
   Graph_Graph3001->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph3001->GetXaxis()->SetLabelSize(0.045);
   Graph_Graph3001->GetXaxis()->SetTitleSize(0.055);
   Graph_Graph3001->GetXaxis()->SetTitleFont(42);
   Graph_Graph3001->GetYaxis()->SetLabelFont(42);
   Graph_Graph3001->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph3001->GetYaxis()->SetLabelSize(0.045);
   Graph_Graph3001->GetYaxis()->SetTitleSize(0.055);
   Graph_Graph3001->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph3001->GetYaxis()->SetTitleFont(42);
   Graph_Graph3001->GetZaxis()->SetLabelFont(42);
   Graph_Graph3001->GetZaxis()->SetLabelSize(0.045);
   Graph_Graph3001->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3001->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3001);
   
   grae->Draw("pl ");
   
   Double_t _fx3002[14] = {
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
   75,
   85,
   95};
   Double_t _fy3002[14] = {
   0.0625,
   0.04455446,
   0.01872659,
   0.04038997,
   0.04552846,
   0.03780718,
   0.9229075,
   0.9244992,
   0.928934,
   0.9433962,
   0.9266055,
   0.9259259,
   0.987013,
   0.9777778};
   Double_t _felx3002[14] = {
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
   5,
   5,
   5};
   Double_t _fely3002[14] = {
   0.0342453,
   0.0130963,
   0.004416323,
   0.006938267,
   0.007932358,
   0.00773798,
   0.01315144,
   0.01081618,
   0.0197931,
   0.02027921,
   0.02764881,
   0.02468838,
   0.0188924,
   0.03160774};
   Double_t _fehx3002[14] = {
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
   5,
   5,
   5};
   Double_t _fehy3002[14] = {
   0.05263088,
   0.01612477,
   0.005224526,
   0.00779476,
   0.008920782,
   0.008908512,
   0.01190847,
   0.009943209,
   0.01688716,
   0.01654465,
   0.02242973,
   0.02048088,
   0.00942238,
   0.01601984};
   grae = new TGraphAsymmErrors(14,_fx3002,_fy3002,_felx3002,_fehx3002,_fely3002,_fehy3002);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(2);
   grae->SetMarkerColor(2);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3002 = new TH1F("Graph_Graph3002","",100,6.5,108.5);
   Graph_Graph3002->SetMinimum(0);
   Graph_Graph3002->SetMaximum(1.094648);
   Graph_Graph3002->SetDirectory(0);
   Graph_Graph3002->SetStats(0);
   Graph_Graph3002->SetLineStyle(0);
   Graph_Graph3002->SetMarkerStyle(20);
   Graph_Graph3002->GetXaxis()->SetLabelFont(42);
   Graph_Graph3002->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph3002->GetXaxis()->SetLabelSize(0.045);
   Graph_Graph3002->GetXaxis()->SetTitleSize(0.055);
   Graph_Graph3002->GetXaxis()->SetTitleFont(42);
   Graph_Graph3002->GetYaxis()->SetLabelFont(42);
   Graph_Graph3002->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph3002->GetYaxis()->SetLabelSize(0.045);
   Graph_Graph3002->GetYaxis()->SetTitleSize(0.055);
   Graph_Graph3002->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph3002->GetYaxis()->SetTitleFont(42);
   Graph_Graph3002->GetZaxis()->SetLabelFont(42);
   Graph_Graph3002->GetZaxis()->SetLabelSize(0.045);
   Graph_Graph3002->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3002->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3002);
   
   grae->Draw("pl ");
   
   Double_t _fx3003[14] = {
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
   75,
   85,
   95};
   Double_t _fy3003[14] = {
   0,
   0.02678571,
   0.001136364,
   0.005555556,
   0.01441678,
   0.007183908,
   0.008169935,
   0.02123142,
   0.06369427,
   0.9395161,
   0.9277108,
   0.9288889,
   0.9663866,
   0.9850746};
   Double_t _felx3003[14] = {
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
   5,
   5,
   5};
   Double_t _fely3003[14] = {
   0,
   0.00949916,
   0.0008312045,
   0.00215404,
   0.003924861,
   0.002783251,
   0.003163787,
   0.004378278,
   0.01288069,
   0.01636287,
   0.02185771,
   0.01843543,
   0.01947802,
   0.02160958};
   Double_t _fehx3003[14] = {
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
   5,
   5,
   5};
   Double_t _fehy3003[14] = {
   0.03757113,
   0.01236415,
   0.001701916,
   0.002908539,
   0.004784006,
   0.003754972,
   0.004266183,
   0.005060459,
   0.01473686,
   0.01399381,
   0.01841987,
   0.01589132,
   0.01414196,
   0.0108142};
   grae = new TGraphAsymmErrors(14,_fx3003,_fy3003,_felx3003,_fehx3003,_fely3003,_fehy3003);
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
   
   TH1F *Graph_Graph3003 = new TH1F("Graph_Graph3003","",100,6.5,108.5);
   Graph_Graph3003->SetMinimum(0);
   Graph_Graph3003->SetMaximum(1.095478);
   Graph_Graph3003->SetDirectory(0);
   Graph_Graph3003->SetStats(0);
   Graph_Graph3003->SetLineStyle(0);
   Graph_Graph3003->SetMarkerStyle(20);
   Graph_Graph3003->GetXaxis()->SetLabelFont(42);
   Graph_Graph3003->GetXaxis()->SetLabelOffset(0.01);
   Graph_Graph3003->GetXaxis()->SetLabelSize(0.045);
   Graph_Graph3003->GetXaxis()->SetTitleSize(0.055);
   Graph_Graph3003->GetXaxis()->SetTitleFont(42);
   Graph_Graph3003->GetYaxis()->SetLabelFont(42);
   Graph_Graph3003->GetYaxis()->SetLabelOffset(0.01);
   Graph_Graph3003->GetYaxis()->SetLabelSize(0.045);
   Graph_Graph3003->GetYaxis()->SetTitleSize(0.055);
   Graph_Graph3003->GetYaxis()->SetTitleOffset(1.3);
   Graph_Graph3003->GetYaxis()->SetTitleFont(42);
   Graph_Graph3003->GetZaxis()->SetLabelFont(42);
   Graph_Graph3003->GetZaxis()->SetLabelSize(0.045);
   Graph_Graph3003->GetZaxis()->SetTitleSize(0.035);
   Graph_Graph3003->GetZaxis()->SetTitleFont(42);
   grae->SetHistogram(Graph_Graph3003);
   
   grae->Draw("pl ");
   
   TLegend *leg = new TLegend(0.53,0.2,0.93,0.6,NULL,"brNDC");
   leg->SetBorderSize(0);
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
   entry->SetTextFont(42);
   entry=leg->AddEntry("","HLT D meson 20","pl");
   entry->SetLineColor(1);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","HLT D meson 40","pl");
   entry->SetLineColor(2);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","HLT D meson 60","pl");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   c->Modified();
   c->cd();
   c->SetSelected(c);
}
