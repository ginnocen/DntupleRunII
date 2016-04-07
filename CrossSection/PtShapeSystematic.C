#include "uti.h"
#include "TString.h"
#include "TLegendEntry.h"


void doplot(TString noweight="ROOTfiles/MCstudiesPPMB.root",TString weight="ROOTfiles/MCstudiesPPMBPPMBptreweighted.root",TString label="PPMB"){
  TFile *filenoweight=new TFile(noweight.Data());
  TFile *fileweight=new TFile(weight.Data());
  TH1F*hEffNoWeight=(TH1F*)filenoweight->Get("hEff");
  TH1F*hEffWeight=(TH1F*)fileweight->Get("hEff");

  hEffWeight->Divide(hEffNoWeight);
  hEffWeight->Draw();

  TCanvas*canvas=new TCanvas("canvas","canvas",500.,500);
  canvas->cd();
  hEffWeight->GetXaxis()->CenterTitle();
  hEffWeight->GetYaxis()->CenterTitle();
  hEffWeight->GetXaxis()->SetTitleOffset(1.0);
  hEffWeight->GetYaxis()->SetTitleOffset(1.15);
  hEffWeight->GetXaxis()->SetTitleSize(0.04);
  hEffWeight->GetYaxis()->SetTitleSize(0.04);
  hEffWeight->GetXaxis()->SetTitleFont(42);
  hEffWeight->GetYaxis()->SetTitleFont(42);
  hEffWeight->GetXaxis()->SetLabelFont(42);
  hEffWeight->GetYaxis()->SetLabelFont(42);
  hEffWeight->GetXaxis()->SetLabelSize(0.035);
  hEffWeight->GetYaxis()->SetLabelSize(0.035);  
  hEffWeight->SetMinimum(0.8);
  hEffWeight->SetMaximum(1.2);
  hEffWeight->SetXTitle("Gen p_{T}");
  hEffWeight->SetYTitle("Efficiency p_{T} weight/no weight");
  hEffWeight->Draw();
  
  TF1 *fPbPbSignalExtractionSig = new TF1("fPbPbSignalExtractionSig","[0]+[1]/(x)+[2]/x/x+[3]*x");
  hEffWeight->Fit("fPbPbSignalExtractionSig","L q","",2,100);
    
  std::cout<<"parameter 0="<<fPbPbSignalExtractionSig->GetParameter(0)<<endl;
  std::cout<<"parameter 1="<<fPbPbSignalExtractionSig->GetParameter(1)<<endl;
  std::cout<<"parameter 2="<<fPbPbSignalExtractionSig->GetParameter(2)<<endl;
  std::cout<<"parameter 3="<<fPbPbSignalExtractionSig->GetParameter(3)<<endl;
  canvas->SaveAs(Form("canvasPtreweightedComparison%s.pdf",label.Data()));

}


void PtShapeSystematic(int isPbPb=0){

 void doplot(TString,TString,TString);
 if (isPbPb==0) doplot("ROOTfiles/pthatallPP.root","ROOTfiles/pthatallPPptreweighted.root","PP");
 if (isPbPb==1) doplot("ROOTfiles/pthatallPbPb.root","ROOTfiles/pthatallPbPbptreweighted.root","PbPb");
 
}


int main(int argc, char *argv[])
{
  PtShapeSystematic();
  return 1;
}
