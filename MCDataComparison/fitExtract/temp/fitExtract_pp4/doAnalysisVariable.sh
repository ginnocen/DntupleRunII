#!/bin/bash
#source clean.sh

VariableOption=$1

#INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_prompt_D0pt30p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20151212_dPt0tkPt0p5_D0Dstar.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160203_Dfinder_20160201_pp_Pythia8_nonprompt_D0pt30p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160122_dPt0tkPt0p5_D0Dstar.root"
#INPUTDATAPP="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root"
#INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_nonprompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160229_Dfinder_20160215_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
#INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_promptNnonprompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTDATAPP="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skimmed.root"


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
ISDOWEIGHTPP=0
SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
#CUTPP="Dpt>35&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPP="Dpt>20&&Dpt<40&&Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>1.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
TRGPPMC="(1)"
#TRGPPData="HLT_DmesonPPTrackingGlobal_Dpt30_v1"
TRGPPData="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"


g++ fitDVariable.C $(root-config --cflags --libs) -g -o fitDVariable.exe 
./fitDVariable.exe "$VARIABLE" "$VARIABLEPLOT" "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMC" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   "$LUMIPP"   "$ISDOWEIGHTPP"   "$LABELPPPromptMC"  "$OUTPUTFILEPPVariablePromptMC"
./fitDVariable.exe "$VARIABLE" "$VARIABLEPLOT" "$INPUTMCNPPP"  "$INPUTMCNPPP"  "$TRGPPMC" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   "$LUMIPP"   "$ISDOWEIGHTPP"   "$LABELPPNonPromptMC"  "$OUTPUTFILEPPVariableNonPromptMC"
./fitDVariable.exe "$VARIABLE" "$VARIABLEPLOT" "$INPUTDATAPP"  "$INPUTMCPP"  "$TRGPPData" "$CUTPP"   "$SELGENPP"   "$ISMCPPData"   "$LUMIPP"   "$ISDOWEIGHTPP"   "$LABELPPData"  "$OUTPUTFILEPPVariableData"

g++ compareMCdataVariables.C $(root-config --cflags --libs) -g -o compareMCdataVariables.exe 
./compareMCdataVariables.exe "$OUTPUTFILEPPVariablePromptMC" "$OUTPUTFILEPPVariableNonPromptMC" "$OUTPUTFILEPPVariableData" "$VARIABLEPLOT" "$VARIABLENAME" "$LIMITLOW" "$LIMITHIGH" "$OUTPUTFILEPLOT"

#cp *root *pdf ../../fitExtract_pp/
#cp FitsVariables/* ../../fitExtract_pp/FitsVariables/
