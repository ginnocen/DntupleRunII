	#include <TF1.h>

// Yen-Jie: B feeddown fraction

float bFeedDownFraction(double pt, double HLT, bool isPbPb)
{
   double val=0.23; // place holder
   if (!isPbPb) { // pp
      if(pt>20&&pt<30) { 
         // 77.0+- 1.7%
         val = 1-0.77;
      } else if (pt>30&&pt<40) {  
         // 75.3 +- 1.6%
	 val = 1-0.75;
      } else if (pt>40&&pt<50) {
         // 83.3% +- 3.5%
	 val = 1-0.833;
      } else if (pt>50) {
         // 82.4% +- 3.1%
	 val = 1-0.824;
      }
   } else {
     // PbPb
      val = 0.15; // place holder
   }
   return val;
}
