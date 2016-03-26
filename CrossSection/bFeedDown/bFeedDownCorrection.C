	#include <TF1.h>

// Yen-Jie: B feeddown fraction

float bFeedDownCorrection(double pt, bool isPbPb)
{
   double val=-1.0; // place holder
   double errval=-1.0;
   
   if (!isPbPb) { // pp
      if (pt>1&&pt<2) {
	 val = 0.766;
      } else if (pt>2&&pt<6) {
	 val = 0.766;
      } else if (pt>6&&pt<10) {
	 val =0.896 ;
      }else if (pt>10&&pt<20) {
	 val =0.913 ;
      } else if (pt>20&&pt<50) {
     val =0.898;
      } else if (pt>50&&pt<100) { 
      val =0.972;
      }
   } else {
     // PbPb
     if (pt>1&&pt<2) {
	 val = 0.703;
     } else if (pt>2&&pt<6) {
	 val = 0.703;
      } else if (pt>6&&pt<10) {
	 val =0.703 ;
      }else if (pt>10&&pt<20) {
	 val =0.880 ;
      } else if (pt>20&&pt<50) {
     val =0.940;
      } else if (pt>50&&pt<100) { 
      val =0.920;
      }
   }
   return val;
}
