	#include <TF1.h>

// Yen-Jie: B feeddown fraction

float bFeedDownCorrection(double pt, bool isPbPb, bool isDCA=0)
{
 double val=-1.0; // place holder
 double errval=-1.0;

 if (isDCA) {   
   if (!isPbPb) { // pp
      if (pt>2&&pt<6) {
	 val = 0.925; // 10.2%
      } else if (pt>6&&pt<8) {
	 val = 0.852; // 0.9%
      } else if (pt>8&&pt<10) {
	 val = 0.879; // 1.7%
      }else if (pt>10&&pt<15) {
	 val = 0.849; // 2.8%
      } else if (pt>15&&pt<20) {
        val = 0.779; // 2.0%
      } else if (pt>20&&pt<25) {
        val = 0.771; // 2.0%
      } else if (pt>25&&pt<35) {
        val = 0.824; // 1.6%
      } else if (pt>35&&pt<=50) {
        val = 0.824; // 3.6%
      } else if (pt>50&&pt<100) {
        val = 0.814; // 3.1%
      } 
   } 
   else{
     // PbPb
      if (pt>2&&pt<6) {
	 val = 0.824; // 10.2%
      } else if (pt>6&&pt<8) {
	 val = 0.729; // 0.9%
      } else if (pt>8&&pt<10) {
	 val = 0.774; // 1.7%
      }else if (pt>10&&pt<20) {
	 val = 0.803; // 2.8%
      } else if (pt>20&&pt<25) {
        val = 0.775; // 2.0%
      } else if (pt>25&&pt<35) {
        val = 0.783; // 1.6%
      } else if (pt>35&&pt<=50) {
        val = 0.824; // 3.6%
      } else if (pt>50&&pt<100) {
        val = 1.0; // 3.1%
      } 
   }
 } else {
   if (!isPbPb) { // pp
      if (pt>1&&pt<2) {
	 val = 0.626; // 10.2%
      } else if (pt>2&&pt<6) {
	 val = 0.827; // 0.9%
      } else if (pt>6&&pt<10) {
	 val = 0.890; // 1.7%
      }else if (pt>10&&pt<20) {
	 val = 0.871; // 2.8%
      } else if (pt>20&&pt<30) {
        val = 0.848; // 2.0%
      } else if (pt>30&&pt<40) {
        val = 0.87; // 1.6%
      } else if (pt>40&&pt<=50) {
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
       val = 0.828;
     } else if (pt>6&&pt<10) {
       val = 0.771;
     }else if (pt>10&&pt<20) {
       val = 0.803; // 1.3%
      } else if (pt>20&&pt<=50) {
        val = 0.955; // 0.8%
      } else if (pt>50&&pt<100) {
        val = 0.92; // 3.4%
      }
   }

 }
 return val;
}
