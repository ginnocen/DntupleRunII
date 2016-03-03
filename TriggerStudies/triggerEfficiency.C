#include <TF1.h>

// Yen-Jie: correction factors for L1 + HLT trigger efficiency for D meson

float triggerEfficiency(double pt, double HLT, isPbPb)
{
   float val=1;
   
   if (isPbPb) {
      // PbPb collisions
      val = 1;
   } else {
      // pp collisions
      val = 1;
   }
   
   return val;
}
