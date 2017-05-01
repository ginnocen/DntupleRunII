
using namespace std;
#include "uti.h"

void readMCData(TString tvariable="Dpt", TString tcollsyst="pp_MB", Double_t ymin=0.4, Double_t ymax=2.52)
{
  TString inputname = Form("%s_%s",tvariable.Data(),tcollsyst.Data());
  TH1D* h1 = new TH1D("h1","",nbins,ptBins);
  TH1D* h2 = new TH1D("h2","",nbins,ptBins);
  ifstream readdata(Form("dats/%s.dat",inputname.Data()));
  for(int i=0;i<nbins;i++)
    {
      Double_t tem,y1,ye1,y2,ye2;
      readdata>>tem>>y1>>tem>>ye1>>tem>>y2>>tem>>ye2;
      h1->SetBinContent(i+1,y1);
      h1->SetBinError(i+1,abs(y1-ye1));
      h2->SetBinContent(i+1,y2);
      h2->SetBinError(i+1,abs(y2-ye2));      
    }
  TImage* img = TImage::Open(Form("pngs/%s.png",inputname.Data()));
  TCanvas* cMCData = new TCanvas("cMCData","",1200,1200);
  img->Draw("x");
  gStyle->SetTextSize(0.05);
  gStyle->SetTextFont(42);
  gStyle->SetPadRightMargin(0.043);
  gStyle->SetPadLeftMargin(0.18);
  gStyle->SetPadTopMargin(0.1);
  gStyle->SetPadBottomMargin(0.145);
  gStyle->SetTitleX(.0f);
  TPad* pad2 = new TPad("pad2","", 0.01, 0.01, 0.99, 0.35);
  pad2->SetFrameLineColor(0);
  pad2->SetFillStyle(4000);
  pad2->SetFrameFillStyle(4000);
  pad2->Draw();
  pad2->cd();

  TH1D* hRatio = (TH1D*)h1->Clone("hRatio");
  hRatio->SetStats(0);
  hRatio->Divide(h2);
  hRatio->SetMaximum(ymax);
  hRatio->SetMinimum(ymin);
  hRatio->SetLineColor(kGreen-4);
  hRatio->SetLineWidth(3);
  hRatio->SetMarkerColor(kGreen-4);
  hRatio->SetMarkerStyle(21);
  hRatio->SetMarkerSize(1.0);
  //hRatio->Draw("hist e");
  hRatio->Draw("ah hist e");
  cMCData->SaveAs(Form("plots/%s.eps",inputname.Data()));

}

int main(int argc, char* argv[])
{
  if(argc==5)
    {
      readMCData(argv[1], argv[2], atof(argv[3]), atof(argv[4]));
      return 0;
    }
  else
    {
      cout<<"  Error: Invalid argument number."<<endl;
      return 1;
    }
}
