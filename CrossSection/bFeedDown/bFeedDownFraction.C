// Yen-Jie: extraction of the feed-down fraction

#include <TFile.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TF1.h>

void bFeedDownFraction()
{
   TFile *infMCP = new TFile("MCCutVariablePromptDecay.root");
   TFile *infMCNP = new TFile("MCCutVariableNonPromptDecay.root");
   TFile *infData = new TFile("DataCutVariableDecay.root");
   
   TH1D *hMCP = (TH1D*)infMCP->Get("hPt");
   TH1D *hMCNP = (TH1D*)infMCNP->Get("hPt");
   TH1D *hData = (TH1D*)infData->Get("hPt");
   
   TF1 *fP = new TF1("fP","[0]*exp([1]+[2]*x+[3]*x*x)");
   TF1 *fNP = new TF1("fNP","[0]*exp([1]+[2]*x+[3]*x*x)");
   
   TCanvas *c = new TCanvas("c","Prompt MC",600,600);
   hMCP->Fit("fP","","",4,14);
   hMCP->Fit("fP","","",4,14);
   hMCP->SetMarkerStyle(20);
   hMCP->Draw();
   
   
   TCanvas *c2 = new TCanvas("c2","NonPrompt MC",600,600);
   hMCNP->Fit("fNP","","",4,14);
   hMCNP->Fit("fNP","","",4,14);
   hMCNP->SetMarkerStyle(20);
   hMCNP->Draw();
   
   TCanvas *c3 = new TCanvas("c3","Data",600,600);
   TF1 *fData = new TF1("fData","[7]*([0]*[8]*exp([1]+[2]*x+[3]*x*x)+(1-[0])*[9]*exp([4]+[5]*x+[6]*x*x))");
   fData->FixParameter(1,fP->GetParameter(1));
   fData->FixParameter(2,fP->GetParameter(2));
   fData->FixParameter(3,fP->GetParameter(3));
   fData->FixParameter(4,fNP->GetParameter(1));
   fData->FixParameter(5,fNP->GetParameter(2));
   fData->FixParameter(6,fNP->GetParameter(3));
   fData->FixParameter(8,fP->GetParameter(0)/fP->Integral(4,14));
   fData->FixParameter(9,fNP->GetParameter(0)/fNP->Integral(4,14));
   fData->SetParLimits(0,0,2);
   hData->SetMarkerStyle(20);
   hData->Fit("fData","","",4,14);
   hData->Fit("fData","","",4,14);
   hData->Fit("fData","","",4,14);
   /*
   TF1 *fDataNP = (TF1*)fData->Clone("fDataNP");
   fDataNP->SetParameter(7,fData->GetParameter(7)*(1-fData->GetParameter(0)));
   fDataNP->SetParameter(0,0);
   fDataNP->SetRange(4,10);
   fDataNP->Draw("same");
   */
}
