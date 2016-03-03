#!/bin/bash
#source clean.sh

cp config/parametersLowpt.h parameters.h

DOFONLL=1
DOFEEDDOWN=1
DOFITSPPMB=1
DOFITSPbPbMB=1
DOMCstudyPPMB=1
DOMCstudyPbPbMB=1
DOCrossSectionPPMB=1
DOCrossSectionPbPbMB=1
DORAAMB=1

FONLLDATINPUT="pp_d0meson_5TeV_y1"
FONLLDATINPUTBtoD="pp_Btod0meson_5TeV_y1"
FONLLDATINPUTB="pp_Bmeson_5TeV_y1"

FONLLOUTPUTFILE="ROOTfiles/output_pp_d0meson_5TeV_y1LowPt.root"
FONLLOUTPUTFILEBtoD="ROOTfiles/output_pp_Btod0meson_5TeV_y1LowPt.root"
FONLLOUTPUTFILEInclusiveD="ROOTfiles/output_inclusiveDd0meson_5TeV_y1LowPt.root"
FONLLOUTPUTFILEB="ROOTfiles/output_pp_Bmeson_5TeV_y1LowPt.root"
OUTPUTFILEPPMB="ROOTfiles/hPtSpectrumDzeroPPMB.root"
OUTPUTFILEPlotPPMB="ROOTfiles/CrossSectionFONLLPPMB.root"
OUTPUTFILEPbPbMB="ROOTfiles/hPtSpectrumDzeroPbPbMB.root"
OUTPUTFILEPlotPbPbMB="ROOTfiles/CrossSectionFONLLPbPbMB.root"
OUTPUTFILERAAMB="ROOTfiles/outputRAAMB.root"

OUTPUTFILEMCSTUDYPPMB="ROOTfiles/MCstudiesPPMB.root"
OUTPUTFILEMCSTUDYPbPbMB="ROOTfiles/MCstudiesPbPbMB.root"


NTUPLAPYTHIA="/data/HeavyFlavourRun2/BtoDPythia/treefile_ptall_11january2016.root"
INPUTMCPPMB="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160216_Dfinder_20160201_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCPbPbMB="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160216_Dfinder_20160201_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTMCPbPbMB="/data/wangj/MC2015/Dntuple/PbPb/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160215_Dfinder_20151229_Pythia8_prompt_D0_pthatweight.root"
INPUTDATAPPMB="/data/jisun/ppMB2015fullstats/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016.root"
INPUTDATAPbPbMB="/data/jisun/PbPb2015/Dntuple_crab_PbPb_HIMinimumBias3_ForestAOD_D0_tkpt0p7eta1p5_goldenjson_01292016.root"
                                         
LUMIPPMB=0.0351        #assuming sigma=70mb, Nevents=2213 millions, estimated MB efficiency=0.9  Lumi=2.213*10^9/(70*0.85*10^9pb)=2.213/(70*0.9)=0.0351
ISMCPPMB=0
ISDOWEIGHTPPMB=1
SELGENPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0"
CUTPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"
USEPRESCALEPPMB=0

LUMIPbPbMB=7.20*1e-6        #assuming sigma=7750 mb, Nevents=50.283009 millions, estimated MB efficiency=0.9  Lumi=0.05028*10^9/(7750*0.90*10^9pb)=0.05028/(7750*0.9)=7.20*1e-6
ISMCPbPbMB=0
ISDOWEIGHTPbPbMB=1
SELGENPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<1.5&&abs(Gtk2eta)<1.5&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPbPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5"
CUTPbPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&(DsvpvDistance/DsvpvDisErr)>5.0&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12"
TRGPbPbMB="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
LABELPbPbMB="PbPbMB"
USEPRESCALEPbPbMB=0

if [ $DOFONLL -eq 1 ]; then      

g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" 
./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoD" 

g++ BplusAlldsigmadpt.cc $(root-config --cflags --libs) -g -o BplusAlldsigmadpt.exe 
./BplusAlldsigmadpt.exe "$FONLLDATINPUTB"  "$FONLLOUTPUTFILEB" 
fi 

if [ $DOFEEDDOWN -eq 1 ]; then      

g++ RatioFeedDown.cc $(root-config --cflags --libs) -g -o RatioFeedDown.exe 
./RatioFeedDown.exe "$FONLLOUTPUTFILE"  "$FONLLOUTPUTFILEBtoD" "$FONLLOUTPUTFILEInclusiveD"

g++ plotFeedDown.C $(root-config --cflags --libs) -g -o plotFeedDown.exe 
./plotFeedDown.exe "$FONLLOUTPUTFILE"  "$FONLLOUTPUTFILEB" "$NTUPLAPYTHIA" 1 0 100 

fi

if [ $DOFITSPPMB -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPPMB"  "$INPUTMCPPMB"  "$TRGPPMB" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMB"   "$LUMIPPMB"   "$ISDOWEIGHTPPMB"   "$LABELPPMB"  "$OUTPUTFILEPPMB"
fi

if [ $DOFITSPbPbMB -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPbPbMB"  "$INPUTMCPbPbMB"  "$TRGPbPbMB" "$CUTPbPbMB"   "$SELGENPbPbMB"   "$ISMCPbPbMB"   "$LUMIPbPbMB"   "$ISDOWEIGHTPbPbMB"   "$LABELPbPbMB"  "$OUTPUTFILEPbPbMB"
fi

if [ $DOMCstudyPPMB -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPPMB"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB"
fi

if [ $DOMCstudyPbPbMB -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPbPbMB"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB"
fi


if [ $DOCrossSectionPPMB -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEInclusiveD"  "$OUTPUTFILEPPMB" "$OUTPUTPrescalePP" "$USEPRESCALEPPMB" "$OUTPUTFILEPlotPPMB" "$LABELPPMB"
fi

if [ $DOCrossSectionPbPbMB -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEInclusiveD"  "$OUTPUTFILEPbPbMB" "$OUTPUTPrescalePP" "$USEPRESCALEPbPbMB" "$OUTPUTFILEPlotPbPbMB" "$LABELPbPbMB"
fi

if [ $DORAAMB -eq 1 ]; then      
g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe 
./NuclearModificationFactor.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPbPbMB" "$LABELPbPbMB" "$OUTPUTFILERAAMB"
fi

