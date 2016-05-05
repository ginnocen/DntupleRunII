void Dmeson-HLTriggerEfficiency()
{
//=========Macro generated from canvas: TRDFigure_Centrality/TRDFigure_Centrality
//=========  (Thu May  5 07:57:02 2016) by ROOT version6.02/10
   TCanvas *TRDFigure_Centrality = new TCanvas("TRDFigure_Centrality", "TRDFigure_Centrality",0,0,600,600);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   TRDFigure_Centrality->Range(-10.76923,-0.251282,66.15385,1.54359);
   TRDFigure_Centrality->SetFillColor(0);
   TRDFigure_Centrality->SetBorderMode(0);
   TRDFigure_Centrality->SetBorderSize(2);
   TRDFigure_Centrality->SetTickx(1);
   TRDFigure_Centrality->SetTicky(1);
   TRDFigure_Centrality->SetLeftMargin(0.14);
   TRDFigure_Centrality->SetRightMargin(0.08);
   TRDFigure_Centrality->SetTopMargin(0.08);
   TRDFigure_Centrality->SetBottomMargin(0.14);
   TRDFigure_Centrality->SetFrameFillStyle(0);
   TRDFigure_Centrality->SetFrameBorderMode(0);
   TRDFigure_Centrality->SetFrameFillStyle(0);
   TRDFigure_Centrality->SetFrameBorderMode(0);
   
   TH2D *hTmp1 = new TH2D("hTmp1","",100,0,60,100,0,1.4);
   hTmp1->SetMaximum(1.4);
   hTmp1->SetLineStyle(0);
   hTmp1->SetMarkerStyle(20);
   hTmp1->GetXaxis()->SetTitle("p_{T} (D^{0}) (GeV)");
   hTmp1->GetXaxis()->CenterTitle(true);
   hTmp1->GetXaxis()->SetLabelFont(42);
   hTmp1->GetXaxis()->SetLabelOffset(0.007);
   hTmp1->GetXaxis()->SetLabelSize(0.05);
   hTmp1->GetXaxis()->SetTitleSize(0.06);
   hTmp1->GetXaxis()->SetTitleOffset(0.95);
   hTmp1->GetXaxis()->SetTitleFont(42);
   hTmp1->GetYaxis()->SetTitle("HLT Efficiency");
   hTmp1->GetYaxis()->CenterTitle(true);
   hTmp1->GetYaxis()->SetLabelFont(42);
   hTmp1->GetYaxis()->SetLabelOffset(0.007);
   hTmp1->GetYaxis()->SetLabelSize(0.05);
   hTmp1->GetYaxis()->SetTitleSize(0.06);
   hTmp1->GetYaxis()->SetTitleOffset(1.15);
   hTmp1->GetYaxis()->SetTitleFont(42);
   hTmp1->GetZaxis()->SetLabelFont(42);
   hTmp1->GetZaxis()->SetLabelOffset(0.007);
   hTmp1->GetZaxis()->SetLabelSize(0.05);
   hTmp1->GetZaxis()->SetTitleSize(0.06);
   hTmp1->GetZaxis()->SetTitleFont(42);
   hTmp1->Draw("");
   
   Double_t _fx3001[8] = {
   3,
   7,
   9,
   12.5,
   17.5,
   25,
   40,
   65};
   Double_t _fy3001[8] = {
   0,
   0.1666667,
   0.8571429,
   0.1428571,
   0.4545455,
   1,
   1,
   1};
   Double_t _felx3001[8] = {
   3,
   1,
   1,
   2.5,
   2.5,
   5,
   10,
   15};
   Double_t _fely3001[8] = {
   0,
   0.1081155,
   0.1533797,
   0.09435654,
   0.1357564,
   0.119839,
   0.09129775,
   0.1742602};
   Double_t _fehx3001[8] = {
   3,
   1,
   1,
   2.5,
   2.5,
   5,
   10,
   15};
   Double_t _fehy3001[8] = {
   0.4369725,
   0.1696671,
   0.09435654,
   0.1533797,
   0.1404935,
   0,
   0,
   0};
   TGraphAsymmErrors *grae = new TGraphAsymmErrors(8,_fx3001,_fy3001,_felx3001,_fehx3001,_fely3001,_fehy3001);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(1);
   grae->SetLineColor(4);
   grae->SetMarkerColor(4);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3001 = new TH1F("Graph_Graph3001","",100,0,88);
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
   
   Double_t _fx3002[8] = {
   3,
   7,
   9,
   12.5,
   17.5,
   25,
   40,
   65};
   Double_t _fy3002[8] = {
   0,
   0.2,
   0.125,
   0.1,
   0.1428571,
   0,
   1,
   0.8571429};
   Double_t _felx3002[8] = {
   3,
   1,
   1,
   2.5,
   2.5,
   5,
   10,
   15};
   Double_t _fely3002[8] = {
   0,
   0.1264582,
   0.08367334,
   0.0681878,
   0.09435654,
   0,
   0.07373067,
   0.1533797};
   Double_t _fehx3002[8] = {
   3,
   1,
   1,
   2.5,
   2.5,
   5,
   10,
   15};
   Double_t _fehy3002[8] = {
   0.3181538,
   0.1891604,
   0.1397325,
   0.1183613,
   0.1533797,
   0.09129775,
   0,
   0.09435654};
   grae = new TGraphAsymmErrors(8,_fx3002,_fy3002,_felx3002,_fehx3002,_fely3002,_fehy3002);
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
   
   TH1F *Graph_Graph3002 = new TH1F("Graph_Graph3002","",100,0,88);
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
   
   Double_t _fx3003[8] = {
   3,
   7,
   9,
   12.5,
   17.5,
   25,
   40,
   65};
   Double_t _fy3003[8] = {
   0,
   0,
   0,
   0,
   0.05263158,
   0,
   0.09375,
   0.875};
   Double_t _felx3003[8] = {
   3,
   1,
   1,
   2.5,
   2.5,
   5,
   10,
   15};
   Double_t _fely3003[8] = {
   0,
   0,
   0,
   0,
   0.03713847,
   0,
   0.04303954,
   0.1397325};
   Double_t _fehx3003[8] = {
   3,
   1,
   1,
   2.5,
   2.5,
   5,
   10,
   15};
   Double_t _fehy3003[8] = {
   0.3181538,
   0.0787842,
   0.06928609,
   0.05323778,
   0.06958997,
   0.03229151,
   0.05969556,
   0.08367334};
   grae = new TGraphAsymmErrors(8,_fx3003,_fy3003,_felx3003,_fehx3003,_fely3003,_fehy3003);
   grae->SetName("");
   grae->SetTitle("");
   grae->SetFillColor(1);

   ci = TColor::GetColor("#ffcc00");
   grae->SetLineColor(ci);

   ci = TColor::GetColor("#ffcc00");
   grae->SetMarkerColor(ci);
   grae->SetMarkerStyle(20);
   
   TH1F *Graph_Graph3003 = new TH1F("Graph_Graph3003","",100,0,88);
   Graph_Graph3003->SetMinimum(0);
   Graph_Graph3003->SetMaximum(1.054541);
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
   
   TLegend *leg = new TLegend(0.4579866,0.2472028,0.8389262,0.4342657,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextSize(0.04);
   leg->SetLineColor(0);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(1001);
   TLegendEntry *entry=leg->AddEntry("","HLT D meson p_{T} #geq 20","pl");
   entry->SetLineColor(4);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(4);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","HLT D meson p_{T} #geq 30","pl");

   ci = TColor::GetColor("#009900");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#009900");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   entry=leg->AddEntry("","HLT D meson p_{T} #geq 50","pl");

   ci = TColor::GetColor("#ffcc00");
   entry->SetLineColor(ci);
   entry->SetLineStyle(1);
   entry->SetLineWidth(1);

   ci = TColor::GetColor("#ffcc00");
   entry->SetMarkerColor(ci);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(1);
   entry->SetTextFont(42);
   leg->Draw();
   TLatex *   tex = new TLatex(0.92,0.936," pp, #sqrt{s}= 5.02 TeV ");
tex->SetNDC();
   tex->SetTextAlign(31);
   tex->SetTextFont(42);
   tex->SetTextSize(0.048);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.1751,0.8927,"CMS");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(61);
   tex->SetTextSize(0.06);
   tex->SetLineWidth(2);
   tex->Draw();
      tex = new TLatex(0.1751,0.8207,"Preliminary");
tex->SetNDC();
   tex->SetTextAlign(13);
   tex->SetTextFont(52);
   tex->SetTextSize(0.0456);
   tex->SetLineWidth(2);
   tex->Draw();
   TRDFigure_Centrality->Modified();
   TRDFigure_Centrality->cd();
   TRDFigure_Centrality->SetSelected(TRDFigure_Centrality);
}
