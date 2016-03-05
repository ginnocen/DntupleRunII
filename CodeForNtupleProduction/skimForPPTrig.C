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
void skimForPPTrig(TString infname="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root",TString outfname="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skimmed.root")
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
   
   // define an output file
   TFile *outf = new TFile(outfname.Data(),"recreate");

   AddCloneTree(cloneForest,outf,ntDkpi,"ntDkpi");
   AddCloneTree(cloneForest,outf,ntHlt,"ntHlt");
   AddCloneTree(cloneForest,outf,ntSkim,"ntSkim");
   AddCloneTree(cloneForest,outf,ntGen,"ntGen");
   
   // You only need the branches which can help you decide if you want to keep the event
   int Dsize;   
   float Dpt[15000];
   float Dy[15000];
   float Dtrk1Pt[15000];
   float Dtrk2Pt[15000];
   float DsvpvDistance[15000];
   float DsvpvDisErr[15000];
   int HLT_DmesonPPTrackingGlobal_Dpt15_v1;
   int HLT_DmesonPPTrackingGlobal_Dpt30_v1;
   int HLT_DmesonPPTrackingGlobal_Dpt50_v1;
   
   ntDkpi->SetBranchAddress("Dsize",&Dsize);
   ntDkpi->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt15_v1",&HLT_DmesonPPTrackingGlobal_Dpt15_v1);
   ntDkpi->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt30_v1",&HLT_DmesonPPTrackingGlobal_Dpt30_v1);
   ntDkpi->SetBranchAddress("HLT_DmesonPPTrackingGlobal_Dpt50_v1",&HLT_DmesonPPTrackingGlobal_Dpt50_v1);
   ntDkpi->SetBranchAddress("Dpt",Dpt);
   ntDkpi->SetBranchAddress("Dy",Dy);
   ntDkpi->SetBranchAddress("Dtrk1Pt",Dtrk1Pt);
   ntDkpi->SetBranchAddress("Dtrk2Pt",Dtrk2Pt);
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
	      if (Dpt[j]>19.&&Dtrk1Pt[j]>2.&&Dtrk2Pt[j]>2.&&Dy[j]>-1.1&&Dy[j]<1.1&&DsvpvDistance[j]/DsvpvDisErr[j]>3.) {
	         ncand++;
		 break;
	      }
	   }
          if (ncand>0&&(HLT_DmesonPPTrackingGlobal_Dpt15_v1||HLT_DmesonPPTrackingGlobal_Dpt30_v1||HLT_DmesonPPTrackingGlobal_Dpt50_v1)) {
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



