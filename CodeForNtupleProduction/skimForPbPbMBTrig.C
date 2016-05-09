#include <iostream>
#include <vector>
#include <algorithm>

#include <TTree.h>
#include <TFile.h>


// Get entry from the forest
void GetEntry(vector<TTree*> forest, int j)
{
  for (unsigned int i=0; i<forest.size(); i++)
  {
    forest[i]->GetEntry(j);
  }

}

// Fill the output for each tree in the forest
void FillOutput(vector<TTree*> cloneForest)
{
  for (unsigned int i=0; i<cloneForest.size(); i++)
  {
    cloneForest[i]->Fill();
  }
}

// Clone a tree
void AddCloneTree(vector<TTree*> &cloneForest,TFile *outf, TTree* t, const char *treeName)
{
  // Make directory
  outf->cd();
  //outf->mkdir(dirName);
  //outf->cd(dirName);

  // Add a clone tree to the clone forest
  TTree *tClone = t->CloneTree(0);
  tClone->SetMaxTreeSize(40000000000);
  tClone->SetName(treeName);

  cloneForest.push_back(tClone);
  cout <<"size"<<" "<<cloneForest.size();
}

// main routine
//void skimForPbPbMBTrig(TString infname="/data/jisun/PbPb2015/HF2and_ncand_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_D0y1p1_tkpt0p7eta1p5_goldenjson_EvtPlaneCali_03182015.root",TString outfname="/data/dmeson2015/DataDntuple/HF2and_ncand_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_D0y1p1_tkpt0p7eta1p5_goldenjson_EvtPlaneCali_03182015_skim_newfilter.root")
void skimForPbPbMBTrig(TString infname="/data/jisun/PbPb2015/HF2and_ncand_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_D0y1p1_tkpt0p7eta1p5_goldenjson_EvtPlaneCali_03182015.root",TString outfname="/data/dmeson2015/DataDntuple/HF2and_ncand_skim_Dntuple_crab_PbPb_HIMinimumBias1to7_ForestAOD_D0y1p1_tkpt0p7eta1p5_goldenjson_EvtPlaneCali_03182015_skim_newfilterPt2GeV_9may2016_Pttrk1GeV.root")
{
   vector<TTree*> cloneForest;
   vector<TTree*> forest;

   TFile *inf = new TFile(infname.Data());
   
   // take the relevant trees from the file
   TTree *ntDkpi = (TTree*)inf->Get("ntDkpi");
   TTree *ntHlt = (TTree*)inf->Get("ntHlt");
   TTree *ntHi = (TTree*)inf->Get("ntHi");
   TTree *ntSkim = (TTree*)inf->Get("ntSkim");
   TTree *ntGen = (TTree*)inf->Get("ntGen");
   
   ntDkpi->AddFriend(ntHlt);
   
   forest.push_back(ntDkpi);
   forest.push_back(ntHlt);
   forest.push_back(ntSkim);
   forest.push_back(ntGen);
   forest.push_back(ntHi);
   
   // define an output file
   TFile *outf = new TFile(outfname.Data(),"recreate");

   AddCloneTree(cloneForest,outf,ntDkpi,"ntDkpi");
   AddCloneTree(cloneForest,outf,ntHlt,"ntHlt");
   AddCloneTree(cloneForest,outf,ntSkim,"ntSkim");
   AddCloneTree(cloneForest,outf,ntGen,"ntGen");
   AddCloneTree(cloneForest,outf,ntHi,"ntHi");
   
   
   // You only need the branches which can help you decide if you want to keep the event
   int Dsize;   
   float Dpt[15000];
   float Dalpha[15000];
   float Dy[15000];
   float Dtrk1Pt[15000];
   float Dtrk2Pt[15000];
   float Dtrk1Eta[15000];
   float Dtrk2Eta[15000];
   float DsvpvDistance[15000];
   float DsvpvDisErr[15000];
   
   ntDkpi->SetBranchAddress("Dsize",&Dsize);
   ntDkpi->SetBranchAddress("Dpt",Dpt);
   ntDkpi->SetBranchAddress("Dy",Dy);
   ntDkpi->SetBranchAddress("Dalpha",Dalpha);
   ntDkpi->SetBranchAddress("Dtrk1Pt",Dtrk1Pt);
   ntDkpi->SetBranchAddress("Dtrk2Pt",Dtrk2Pt);
   ntDkpi->SetBranchAddress("Dtrk1Eta",Dtrk1Eta);
   ntDkpi->SetBranchAddress("Dtrk2Eta",Dtrk2Eta);
   ntDkpi->SetBranchAddress("DsvpvDistance",DsvpvDistance);
   ntDkpi->SetBranchAddress("DsvpvDisErr",DsvpvDisErr);
   
   // main loop
   for (Long64_t i=0;i<ntDkpi->GetEntries()/1.;i++)
   {
         if (i%10000==0) cout <<ntDkpi->GetEntries()<<"/"<<i<<endl;
	 ntDkpi->GetEntry(i);
	 
	 // if pass the selection -> accept this event
	 if (Dsize>0) {
	   int ncand=0;
	   for (int j=0;j<Dsize;j++) {
	     //for the low pt skim
	      //if (Dalpha[j]<0.12&&Dpt[j]>0.9&&Dy[j]>-1.1&&Dy[j]<1.1&&(((DsvpvDistance[j]/DsvpvDisErr[j])>6.0&&Dpt[j]<=2.0) || ((DsvpvDistance[j]/DsvpvDisErr[j])>5.4&&Dpt[j]>2.0&&Dpt[j]<=5.0) || ((DsvpvDistance[j]/DsvpvDisErr[j])>3.&&Dpt[j]>5.0))) {
	      if (Dalpha[j]<0.12&&Dtrk1Pt[j]>1.0&&Dtrk2Pt[j]>1.0&&Dpt[j]>2.0&&Dy[j]>-1.1&&Dy[j]<1.1&&(((DsvpvDistance[j]/DsvpvDisErr[j])>6.0&&Dpt[j]<=2.0) || ((DsvpvDistance[j]/DsvpvDisErr[j])>5.4&&Dpt[j]>2.0&&Dpt[j]<=5.0) || ((DsvpvDistance[j]/DsvpvDisErr[j])>3.&&Dpt[j]>5.0))) {
	         ncand++;
		 break;
	      }
	   }
          if (ncand>0) {
	      GetEntry(forest,i);
	      FillOutput(cloneForest);
	   }
	 } 
   }
   
   for (unsigned int i=0;i<cloneForest.size();i++)
   {
      cloneForest[i]->AutoSave();
   }
   
   outf->Close();
}



