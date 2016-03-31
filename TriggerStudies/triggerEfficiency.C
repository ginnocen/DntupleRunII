	#include <TF1.h>

// Yen-Jie: correction factors for L1 + HLT trigger efficiency for D meson

float triggerEfficiency(double pt, double HLT, bool isPbPb)
{
   float val=1;
   
   if (isPbPb) {
      // correction factor for PbPb collisions
      val = 1;
      TF1 *fL1 = new TF1("fL1","TMath::Erf(x*[1]+[2])*0.5*(1-[0])+0.5*(1+[0])");
      if (HLT==20) {
         fL1->SetParameters(-4.5400e3,3.09974e-1,2.31049);
      } else if (HLT==40) {
         fL1->SetParameters(-4.05647e3,8.77473e-3,3.1443);
      } else if (HLT==50) {
         fL1->SetParameters(2.01935e-1,7.43858e-2,-2.0107);               
      } else if (HLT==60) {
         fL1->SetParameters(7.0734e-2,6.76907e-2,-2.31850);               
     } else {
         std::cout <<"Oh no, where did you find this HLT path??? I don't remember this value "<<HLT<<". This is a disaster! We need to go to Brocard to buy more cakes..."<<std::endl;
	 return 1e10; 
      }

      // HLT, at high pt things are consistent with 0.9275+-0.0055 for the moment
      if (pt<HLT) {
         val = 1e10; // veto
	 std::cout <<"using D candidate below HLT threshold!!"<<std::endl;
      } else {
         // 
         val = 0.9275;
      }
      
      val *= fL1->Eval(pt);
      
   } else {
      // correction factor for pp collisions
      TF1 *fL1 = new TF1("fL1","TMath::Erf(x*[1]+[2])*0.5*(1-[0])+0.5*(1+[0])");
      if (HLT==8) {
         fL1->SetParameters(1.81837e-1,1.54009e-1,-1.66545);
      } else if (HLT==15) {
         fL1->SetParameters(6.35868e-2,1.32864e-1,-1.90241);
      } else if (HLT==20) {
         fL1->SetParameters(3.95443e-2,1.44985e-1,-2.23026);
      }	else if (HLT==30) {
         fL1->SetParameters(6.19120e-3,1.19415e-1,-2.24150);
      }	else if (HLT==50) {
         fL1->SetParameters(6.19120e-3,1.19415e-1,-2.24150);
      } else {
         std::cout <<"Oh no, where did you find this HLT path??? I don't remember this value "<<HLT<<". This is a disaster! We need to go to Brocard to buy more cakes..."<<std::endl;
	 return 1e10; 
      }
      
      // HLT, at high pt things are consistent with 1, put 1 for the moment
      if (pt<HLT) {
         val = 1e10; // veto
	 std::cout <<"using D candidate below HLT threshold!!"<<std::endl;
      } else {
         // 
         val = 1;
      }
      
      val *= fL1->Eval(pt);
      
   }
   
   return val;
}
