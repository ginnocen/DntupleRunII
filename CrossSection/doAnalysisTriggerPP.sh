#!/bin/bash
#source clean.sh

DOTriggered=1
DOMB=0

DONORM=1

UNITY=1
NULL=0

## PbPb 

## PbPb MONTE CARLO

NTUPLAPYTHIA="/data/HeavyFlavourRun2/BtoDPythia/treefile_ptall_11january2016.root"
INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"  
INPUTMCPPMB="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"  
INPUTDATAPPSKIMMED="/data/dmeson2015/DataDntuple/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson_skim_myskim.root"
INPUTDATAPPUNSKIMMED="/data/wangj/Data2015/Dntuple/pp/ntD_EvtBase_20160330_HeavyFlavor_DfinderData_pp_20160329_dPt0tkPt1_D0Dstar3p5p_goldenjson.root"
INPUTDATAPPMBUNSKIMMED="/data/jisun/ppMB2015fullstats/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016.root"
INPUTDATAPPMBSKIMMED="/data/dmeson2015/DataDntuple/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016_skimmedPt1.root"

if [ $DOTriggered -eq 1 ]; then      

for VARIABLE in 8 15 30 50

do

FONLLDATINPUT="pp_d0meson_5TeV_y1"
FONLLOUTPUTFILE="ROOTfiles/output_pp_d0meson_5TeV_y1_$VARIABLE.root"
OUTPUTPrescalePP="ROOTfiles/prescalePP_$VARIABLE.root"
OUTPUTFILEMCSTUDYPP="ROOTfiles/MCstudiesPP_$VARIABLE.root"
OUTPUTFILEMCSTUDYNPPP="ROOTfiles/MCstudiesNPPP_$VARIABLE.root"
OUTPUTFILEPP="ROOTfiles/hPtSpectrumDzeroPP_$VARIABLE.root"
OUTPUTFILEPlotPP="ROOTfiles/CrossSectionFONLLPP_$VARIABLE.root"
OUTPUTFILEPPDcandidates="ROOTfiles/hDcandidatesPP_$VARIABLE.root"


ISMCPP=0
ISDOWEIGHTPP=0
SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
LABELPPPLOT="PP_$VARIABLE"
LABELNPPP="NPPP"
USEPRESCALEPP=1
CUTFORTRIGGERPRESCALEPP=0
LUMIPP=25.8

if [ $VARIABLE -eq 8 ]; then      
cp config/parametersHighHLTD8PP.h parameters.h
TRGPP="HLT_DmesonPPTrackingGlobal_Dpt8_v1"
fi 

if [ $VARIABLE -eq 15 ]; then      
cp config/parametersHighHLTD15PP.h parameters.h
TRGPP="HLT_DmesonPPTrackingGlobal_Dpt15_v1"
fi 

if [ $VARIABLE -eq 30 ]; then      
cp config/parametersHighHLTD30PP.h parameters.h
TRGPP="HLT_DmesonPPTrackingGlobal_Dpt30_v1"
fi 

if [ $VARIABLE -eq 50 ]; then      
cp config/parametersHighHLTD50PP.h parameters.h
TRGPP="HLT_DmesonPPTrackingGlobal_Dpt50_v1"
fi 

if [ $DONORM -eq 1 ]; then     
LUMIPP=1
fi 


g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPPPLOT"
 
g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe 
./triggercombination.exe 0 "$INPUTDATAPPUNSKIMMED" "$INPUTDATAPPMBUNSKIMMED" "$CUTFORTRIGGERPRESCALEPP" "$OUTPUTPrescalePP"
rm triggercombination.exe

g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe 0 "$INPUTDATAPPSKIMMED"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   1   "$ISDOWEIGHTPP"   "$LABELPPPLOT"  "$OUTPUTFILEPP"
rm fitD.exe

g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILE"  "$OUTPUTFILEPP" "$OUTPUTPrescalePP" "$USEPRESCALEPP" "$OUTPUTFILEPlotPP" 0 "$LABELPPPLOT" "$LUMIPP" 
rm CrossSectionRatio.exe
done

fi

if [ $DOMB -eq 1 ]; then      

cp config/parametersLowpt_extended.h parameters.h

FONLLDATINPUT="pp_d0meson_5TeV_y1"
FONLLOUTPUTFILEPPMB="ROOTfiles/output_pp_d0meson_5TeV_y1"
OUTPUTPrescalePPMB="ROOTfiles/prescalePPMB_extended.root"
OUTPUTFILEMCSTUDYPPMB="ROOTfiles/MCstudiesPPMB_extended.root"
OUTPUTFILEPPMB="ROOTfiles/hPtSpectrumDzeroPPMB_extended.root"
OUTPUTFILEPlotPPMB="ROOTfiles/CrossSectionFONLLPPMB_extended.root"
OUTPUTFILEPPDcandidatesMB="ROOTfiles/hDcandidatesPP_extended.root"

LUMIPPMB=0.0344167
ISMCPPMB=0
ISDOWEIGHTPPMB=0
SELGENPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
LABELPPPLOT="PPMB_extended"
USEPRESCALEPPMB=0
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"


if [ $DONORM -eq 1 ]; then     
LUMIPPMB=1
fi 

g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEPPMB" "$LABELPPPLOT"


g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
#./fitD.exe 0 "$INPUTDATAPPMBSKIMMED"  "$INPUTMCPP"  "$TRGPPMB" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMB"   1   "$ISDOWEIGHTPPMB"   "$LABELPPPLOT"  "$OUTPUTFILEPPMB" 
rm fitD.exe


g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEPPMB"  "$OUTPUTFILEPPMB" "$OUTPUTPrescalePP" "$USEPRESCALEPPMB" "$OUTPUTFILEPlotPPMB" 0 "$LABELPPPLOT" "$LUMIPPMB" 
rm CrossSectionRatio.exe

fi









