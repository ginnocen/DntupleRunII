void getFeedDownCorrectionCode()
{
  //  TFile* f1 = new TFile("bFeedDownResultPP.root");
  TFile* f1 = new TFile("bFeedDownResultPbPb.root");
  TGraphErrors* grPromptFraction = (TGraphErrors*)f1->Get("grPromptFraction");
  const int nBinX = 14;
  Float_t binsX[nBinX+1] = {2.,3.,4.,5.,6.,8.,10.,12.5,15.0,20.,25.,30.,40.,60.,100};
  for(int i=0; i<nBinX; i++)
    {
      if(i==0)
	cout<<"if (pt>"<<binsX[i]<<"&&pt<"<<binsX[i+1]<<") {"<<endl;
      else
	cout<<"} else if (pt>"<<binsX[i]<<"&&pt<"<<binsX[i+1]<<") {"<<endl;
      cout<<"val = "<<grPromptFraction->GetY()[i]<<";"<<endl;
    }

}

