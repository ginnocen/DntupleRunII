#!/bin/bash
#source clean.sh

VariableOption=$1
System=$2
Type=$3

#INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_prompt_D0pt30p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt0tkPt0p5_D0Dstar.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_nonprompt_D0pt30p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160122_dPt0tkPt0p5_D0Dstar.root"
#INPUTDATAPP="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root"
#INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_nonprompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"

if [ $System == "pp" ]; then
#INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_nonprompt_D0_dPt0tkPt0p5_pthatweight.root"

if [ $Type == "HF" ]; then
INPUTDATAPP="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skimmed.root"
fi
if [ $Type == "MB" ]; then
INPUTDATAPP="/data/dmeson2015/DataDntuple/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016_skimmed.root"
fi
fi

if [ $System == "PbPb" ]; then
#INPUTMCPP="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_promptNnonprompt_D0_dPt1tkPt1_pthatweight.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_promptNnonprompt_D0_dPt1tkPt1_pthatweight.root"
INPUTMCPP="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"
INPUTMCNPPP="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_nonprompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_nonprompt_D0_dPt1tkPt1_pthatweight.root"

if [ $Type == "HF" ]; then
INPUTDATAPP="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2_skimmed.root"
fi
if [ $Type == "MB" ]; then
INPUTDATAPP="/data/dmeson2015/DataDntuple/Dntuple_crab_PbPb_HIMinimumBias3_ForestAOD_D0_tkpt0p7eta1p5_goldenjson_01292016_skim.root"
fi
fi

ISDOWEIGHTPP=1
WEIGHTINGFACTOR="pow(10,-0.168499*Dgenpt+3.872855+Dgenpt*Dgenpt*0.000556)+pow(10,-0.068599*Dgenpt+2.512265+Dgenpt*Dgenpt*0.000331)"

if [ $VariableOption -eq 0 ]; then      
cp config/parametersVariablesDecay.h parameters.h 
VARIABLE="DsvpvDistance/DsvpvDisErr";
VARIABLEPLOT="d_{xy}/#sigma(d_{xy})"
VARIABLENAME="decay"
LABELPPPromptMC="MCPromptDecay"
OUTPUTFILEPPVariablePromptMC="MCCutVariablePromptDecay.root"
LABELPPNonPromptMC="MCNonPromptDecay"
OUTPUTFILEPPVariableNonPromptMC="MCCutVariableNonPromptDecay.root"
OUTPUTFILEPPVariableData="DataCutVariableDecay.root"
LABELPPData="DataDecay"
#LIMITLOW=3
#LIMITHIGH=18
LIMITLOW=4
LIMITHIGH=15
OUTPUTFILEPLOT="outputPlotDecay.root"
fi

if [ $VariableOption -eq 1 ]; then      
cp config/parametersVariablesDy.h parameters.h 
VARIABLE="Dy";
VARIABLEPLOT="D rapidity"
VARIABLENAME="Drapidity"
LABELPPPromptMC="MCPromptRapidity"
OUTPUTFILEPPVariablePromptMC="MCCutVariablePromptRapidity.root"
LABELPPNonPromptMC="MCNonPromptRapidity"
OUTPUTFILEPPVariableNonPromptMC="MCCutVariableNonPromptRapidity.root"
OUTPUTFILEPPVariableData="DataCutVariableRapidity.root"
LABELPPData="DataRapidity"
#LIMITLOW=-2
#LIMITHIGH=2
LIMITLOW=-1
LIMITHIGH=1
OUTPUTFILEPLOT="outputPlotRapidity.root"
fi

if [ $VariableOption -eq 2 ]; then      
cp config/parametersVariablesDpt.h parameters.h 
VARIABLE="Dpt";
VARIABLEPLOT="D p_{T}"
VARIABLENAME="Dpt"
LABELPPPromptMC="MCPromptPt"
OUTPUTFILEPPVariablePromptMC="MCCutVariablePromptPt.root"
LABELPPNonPromptMC="MCNonPromptPt"
OUTPUTFILEPPVariableNonPromptMC="MCCutVariableNonPromptPt.root"
OUTPUTFILEPPVariableData="DataCutVariablePt.root"
LABELPPData="DataPt"
#LIMITLOW=20
#LIMITHIGH=50
LIMITLOW=20
LIMITHIGH=40
OUTPUTFILEPLOT="outputPlotPt.root"
if [ $System == "PbPb" ]; then
cp config/parametersVariablesDpt_PbPb.h parameters.h
fi
if [ $Type == "MB" ]; then
cp config/parametersVariablesDpt_MB.h parameters.h
fi
fi

if [ $VariableOption -eq 3 ]; then      
cp config/parametersVariablesChi2.h parameters.h 
VARIABLE="Dchi2cl";
VARIABLEPLOT="vertex #chi^{2}"
VARIABLENAME="Dchi2cl"
LABELPPPromptMC="MCPromptChi2"
OUTPUTFILEPPVariablePromptMC="MCCutVariablePromptChi2.root"
LABELPPNonPromptMC="MCNonPromptChi2"
OUTPUTFILEPPVariableNonPromptMC="MCCutVariableNonPromptChi2.root"
OUTPUTFILEPPVariableData="DataCutVariableChi2.root"
LABELPPData="DataChi2"
#LIMITLOW=0
#LIMITHIGH=1.1
LIMITLOW=0.05
LIMITHIGH=1.0
OUTPUTFILEPLOT="outputPlotChi2.root"
fi

if [ $VariableOption -eq 4 ]; then      
cp config/parametersVariablesDalpha.h parameters.h 
VARIABLE="Dalpha";
VARIABLEPLOT="#alpha"
VARIABLENAME="Dalpha"
LABELPPPromptMC="MCPromptDalpha"
OUTPUTFILEPPVariablePromptMC="MCCutVariablePromptDalpha.root"
LABELPPNonPromptMC="MCNonPromptDalpha"
OUTPUTFILEPPVariableNonPromptMC="MCCutVariableNonPromptDalpha.root"
OUTPUTFILEPPVariableData="DataCutVariableDalpha.root"
LABELPPData="DataDalpha"
#LIMITLOW=0.
#LIMITHIGH=0.05
LIMITLOW=0.00
LIMITHIGH=0.12
OUTPUTFILEPLOT="outputPlotDalpha.root"
fi


LUMIPP=1
ISMCPP=1
ISMCPPData=0
SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
#CUTPP="Dpt>35&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
TRGPPMC="(1)"
#TRGPPData="HLT_DmesonPPTrackingGlobal_Dpt30_v1"

if [ $System == "pp" ]; then
if [ $Type == "HF" ]; then
CUTPP="Dpt>20&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
TRGPPData="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
fi
if [ $Type == "MB" ]; then
CUTPP="Dpt<20&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12"
TRGPPData="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
fi
fi

if [ $System == "PbPb" ]; then
if [ $Type == "HF" ]; then
CUTPP="Dpt>20&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPPData="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<45)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>45&&Dpt<70)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>70))"
fi

if [ $Type == "MB" ]; then
CUTPP="Dpt<20&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPPData="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
fi
fi

g++ fitDVariable.C $(root-config --cflags --libs) -g -o fitDVariable.exe 
./fitDVariable.exe "$VARIABLE" "$VARIABLEPLOT" "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMC" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   "$LUMIPP"   "$ISDOWEIGHTPP"   "$LABELPPPromptMC"  "$OUTPUTFILEPPVariablePromptMC" "$WEIGHTINGFACTOR"
./fitDVariable.exe "$VARIABLE" "$VARIABLEPLOT" "$INPUTMCNPPP"  "$INPUTMCNPPP"  "$TRGPPMC" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   "$LUMIPP"   "$ISDOWEIGHTPP"   "$LABELPPNonPromptMC"  "$OUTPUTFILEPPVariableNonPromptMC" "$WEIGHTINGFACTOR"
./fitDVariable.exe "$VARIABLE" "$VARIABLEPLOT" "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPPData" "$CUTPP"   "$SELGENPP"   "$ISMCPPData"   "$LUMIPP"   "$ISDOWEIGHTPP"   "$LABELPPData"  "$OUTPUTFILEPPVariableData" "$WEIGHTINGFACTOR"

g++ compareMCdataVariables.C $(root-config --cflags --libs) -g -o compareMCdataVariables.exe 
./compareMCdataVariables.exe "$OUTPUTFILEPPVariablePromptMC" "$OUTPUTFILEPPVariableNonPromptMC" "$OUTPUTFILEPPVariableData" "$VARIABLEPLOT" "$VARIABLENAME" "$LIMITLOW" "$LIMITHIGH" "$OUTPUTFILEPLOT"
mv $OUTPUTFILEPPVariablePromptMC $OUTPUTFILEPPVariableNonPromptMC $OUTPUTFILEPPVariableData $OUTPUTFILEPLOT OutPuts/
