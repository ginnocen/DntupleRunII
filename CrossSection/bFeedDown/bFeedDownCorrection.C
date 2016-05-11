	#include <TF1.h>

// Yen-Jie: B feeddown fraction

float bFeedDownCorrection(double pt, bool isPbPb)
{
   double val=-1.0; // place holder
   double errval=-1.0;
   

   if (!isPbPb) { // pp
      if (pt>1&&pt<2) {
	 val = 0.626; // 10.2%
      } else if (pt>2&&pt<6) {
	 val = 0.827; // 0.9%
      } else if (pt>6&&pt<10) {
	 val = 0.890; // 1.7%
      }else if (pt>10&&pt<20) {
	 val = 0.87.1; // 2.8%
      } else if (pt>20&&pt<30) {
        val = 0.848; // 2.0%
      } else if (pt>30&&pt<40) {
        val = 0.87; // 1.6%
      } else if (pt>40&&pt<50) {
        val = 0.856; // 3.6%
      } else if (pt>50&&pt<60) {
        val = 0.781; // 3.1%
      } else if (pt>60&&pt<100) { 
        val = 0.784; // 4.3%
      }
   } 
   else{
     // PbPb
     if (pt>1&&pt<2) {
       val = 1.000;
     } else if (pt>2&&pt<6) {
       val = 1.000;
     } else if (pt>6&&pt<10) {
       val = 0.946;
     }else if (pt>10&&pt<20) {
       val = 0.960;
     } else if (pt>20&&pt<50) {
       val = 1.000;
     } else if (pt>50&&pt<100) { 
       val = 0.976;
     }
   }
   return val;
}
