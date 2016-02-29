#!/bin/bash
#source clean.sh

cp config/parametersMCreweight.h parameters.h 

SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"

g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 


INPUTMCPP="/data/wangj/MC2015/Dntuple/backup/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_prompt_D0_dPt0tkPt0p5_noweight.root"
LABELPP="PPALL"
FILEOUT="PPALL.root"
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELPP" "$FILEOUT"
