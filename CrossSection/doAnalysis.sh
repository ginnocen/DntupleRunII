#!/bin/bash
#source clean.sh

#Central point of the analysis

DOFONLL=0
DOTRGCOMBINATION=0
DOFEEDDOWN=0
DOFITSPP=0
DOFITSPPMCClosure=0
DOFITSPbPbMCClosure=0
DOFITSPbPb=0
DOCrossSectionPP=0
DOCrossSectionPbPb=0
DORAA=0

DOFONLLMB=0
DOFEEDDOWNMB=0
DOFITSPPMB=0
DOFITSPbPbMB=0
DOCrossSectionPPMB=0
DOCrossSectionPbPbMB=0
DORAAMB=0

DOCombineCrossSection=0
DOCombineRAA=

#Efficiency studies

DOMCstudyPP=0
DOMCstudyNPPP=0
DOMCstudyPbPb=0
DOMCstudyPPMB=0
DOMCstudyPbPbMB=0

#reweight systematic

DOMCstudyPPReweight=0
DOMCstudyPbPbReweight=0
DOMCstudyPPMBReweight=0
DOMCstudyPbPbMBReweight=0
DOsystematicPtshape=0

DOsystematicPthatstudyPP=0

UNITY=1
NULL=0

MINIMUMFIT=2
MAXIMUMFIT=100

FONLLDATINPUT="pp_d0meson_5TeV_y1"
FONLLDATINPUTBtoD="pp_Btod0meson_5TeV_y1"
FONLLDATINPUTB="pp_Bmeson_5TeV_y1"

NTUPLAPYTHIA="/data/HeavyFlavourRun2/BtoDPythia/treefile_ptall_11january2016.root"
INPUTMCPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0_dPt0tkPt0p5_pthatweight.root"  
INPUTMCPPMB="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"  
INPUTMCNPPP="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_nonprompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_nonprompt_D0_dPt0tkPt0p5_pthatweight.root"
INPUTDATAPPSKIMMED="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2_skimmed.root"
INPUTDATAPPUNSKIMMED="/data/dmeson2015/DataDntuple/nt_20160112_DfinderData_pp_20160111_dPt0tkPt1_D0Dstar3p5p_DCSJSON_v2.root"
INPUTMCPbPb="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0_dPt1tkPt1_pthatweight.root"
INPUTMCPbPbMB="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"
INPUTDATAPbPbSKIMMED="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2_skimmed.root"
INPUTDATAPbPbUNSKIMMED="/data/dmeson2015/DataDntuple/nt_skimmed_DfinderData_PbPb_20160126_dPt0tkPt2p5_D0Dstar3p5p_FINALJSON_v6_partialstats_v2.root"

INPUTMCPPPthat10="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"
INPUTMCPPPthat30="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"
INPUTMCPPPthat50="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"
INPUTMCPPPthat70="/data/wangj/MC2015/Dntuple/pp/revised/ntD_pp_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_pp_Pythia8_prompt_D0pt0p0_Pthat70_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt0tkPt0p5_D0Dstar.root"

INPUTMCPbPbPthat10="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat10_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"
INPUTMCPbPbPthat30="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat30_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"
INPUTMCPbPbPthat50="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat50_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"
INPUTMCPbPbPthat70="/data/wangj/MC2015/Dntuple/PbPb/revised/ntD_PbPb_Dzero_kpi_prompt/ntD_EvtBase_20160303_Dfinder_20160302_PbPb_Pythia8_prompt_D0pt0p0_Pthat70_TuneCUETP8M1_5020GeV_evtgen130_GEN_SIM_20160229_dPt1tkPt1_D0Ds.root"

INPUTDATAPPMBUNSKIMMED="/data/jisun/ppMB2015fullstats/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016.root"
INPUTDATAPPMBSKIMMED="/data/dmeson2015/DataDntuple/skim_ncand_D0Dntuple_crab_pp_ALLMinimumBias_AOD_D0_tkpt0p5_Ds_01212016_skimmed.root"
INPUTDATAPbPbMBUNSKIMMED="/data/jisun/PbPb2015/HF2and_skim_MB1to7_highpuritytk_D0_tkpt0p7eta1p5_goldenjson_02222016.root"
INPUTDATAPbPbMBSKIMMED=""

FONLLOUTPUTFILE="ROOTfiles/output_pp_d0meson_5TeV_y1.root"
FONLLOUTPUTFILEBtoD="ROOTfiles/output_pp_Btod0meson_5TeV_y1.root"
FONLLOUTPUTFILEInclusiveD="ROOTfiles/output_inclusiveDd0meson_5TeV_y1.root"
FONLLOUTPUTFILEB="ROOTfiles/output_pp_Bmeson_5TeV_y1.root"
OUTPUTFILEPP="ROOTfiles/hPtSpectrumDzeroPP.root"
OUTPUTFILEPPMCClosure="ROOTfiles/hPtSpectrumDzeroPPMCClosure.root"
OUTPUTFILEPbPbMCClosure="ROOTfiles/hPtSpectrumDzeroPbPbMCClosure.root"
OUTPUTFILEPlotPP="ROOTfiles/CrossSectionFONLLPP.root"
OUTPUTFILEPbPb="ROOTfiles/hPtSpectrumDzeroPbPb.root"
OUTPUTFILEPlotPbPb="ROOTfiles/CrossSectionFONLLPbPb.root"
OUTPUTFILERAA="ROOTfiles/outputRAA.root"
OUTPUTFILEMCSTUDYPP="ROOTfiles/MCstudiesPP"
OUTPUTFILEMCSTUDYNPPP="ROOTfiles/MCstudiesNPPP"
OUTPUTFILEMCSTUDYPbPb="ROOTfiles/MCstudiesPbPb"

LUMIPP=26.31
ISMCPP=0
ISDOWEIGHTPP=0
SELGENPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPP="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPP="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>2.0&&Dtrk2Pt>2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&Dtrk1Algo>3&&Dtrk1Algo<8&&Dtrk2Algo>3&&Dtrk2Algo<8&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
TRGPP="((HLT_DmesonPPTrackingGlobal_Dpt15_v1&&Dpt>20&&Dpt<40)||(HLT_DmesonPPTrackingGlobal_Dpt30_v1&&Dpt>40&&Dpt<60)||(HLT_DmesonPPTrackingGlobal_Dpt50_v1&&Dpt>60))"
LABELPP="PP"
LABELNPPP="NPPP"
USEPRESCALEPP=1
CUTFORTRIGGERPRESCALEPP=0

LUMIPPMCClosure=1
ISMCPPMCClosure=1
ISDOWEIGHTPPMCClosure=0
TRGPPMCClosure="1"
LABELPPMCClosure="PPMCClosure"

LUMIPbPbMCClosure=1
ISMCPbPbMCClosure=1
ISDOWEIGHTPbPbMCClosure=0
TRGPbPbMCClosure="1"
LABELPbPbMCClosure="PbPbMCClosure"
                                         
LUMIPbPb=0.000404 #404*0.001*0.001
ISMCPbPb=0
ISDOWEIGHTPbPb=0
SELGENPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENPPACCPbPb="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>2.0&&Gtk2pt>2.0"
RECOONLYPbPb="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)"
CUTPbPb="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>8.5&&Dtrk2Pt>8.5&&Dtrk1PtErr/Dtrk1Pt<0.1&&Dtrk2PtErr/Dtrk2Pt<0.1&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(Dtrk1PixelHit+Dtrk1StripHit)>=11&&(Dtrk2PixelHit+Dtrk2StripHit)>=11&&(Dtrk1Chi2ndf/(Dtrk1nStripLayer+Dtrk1nPixelLayer)<0.15)&&(Dtrk2Chi2ndf/(Dtrk2nStripLayer+Dtrk2nPixelLayer)<0.15)&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPb="((HLT_HIDmesonHITrackingGlobal_Dpt20_v1&&Dpt>20&&Dpt<45)||(HLT_HIDmesonHITrackingGlobal_Dpt40_v1&&Dpt>45&&Dpt<70)||(HLT_HIDmesonHITrackingGlobal_Dpt60_v1&&Dpt>70))"
LABELPbPb="PbPb"
USEPRESCALEPbPb=1
CUTFORTRIGGERPRESCALEPbPb=0

OUTPUTPrescalePP="prescalePP.root"
OUTPUTPrescalePbPb="prescalePbPb.root"

cp config/parametersHighpt.h parameters.h

if [ $DOFONLL -eq 1 ]; then      

g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILE" "$LABELPP"
./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoD" "$LABELPP"

g++ BplusAlldsigmadpt.cc $(root-config --cflags --libs) -g -o BplusAlldsigmadpt.exe 
./BplusAlldsigmadpt.exe "$FONLLDATINPUTB"  "$FONLLOUTPUTFILEB" "$LABELPP"
fi 

if [ $DOFEEDDOWN -eq 1 ]; then      

g++ RatioFeedDown.cc $(root-config --cflags --libs) -g -o RatioFeedDown.exe 
./RatioFeedDown.exe "$FONLLOUTPUTFILE"  "$FONLLOUTPUTFILEBtoD" "$FONLLOUTPUTFILEInclusiveD" "$LABELPP"

g++ plotFeedDown.C $(root-config --cflags --libs) -g -o plotFeedDown.exe 
./plotFeedDown.exe "$FONLLOUTPUTFILE"  "$FONLLOUTPUTFILEB" "$NTUPLAPYTHIA" 1 0 100 

fi

if [ $DOTRGCOMBINATION -eq 1 ]; then      

g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe 
./triggercombination.exe "$LABELPP"  "$INPUTDATAPPUNSKIMMED" "$INPUTDATAPPMBUNSKIMMED" "$CUTFORTRIGGERPRESCALEPP" "$OUTPUTPrescalePP"

g++ triggercombination.cc $(root-config --cflags --libs) -g -o triggercombination.exe 
./triggercombination.exe "$LABELPbPb"  "$INPUTDATAPbPbUNSKIMMED" "$INPUTDATAPbPbMBUNSKIMMED" "$CUTFORTRIGGERPRESCALEPbPb" "$OUTPUTPrescalePbPb"
fi

if [ $DOFITSPP -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPPSKIMMED"  "$INPUTMCPP"  "$TRGPP" "$CUTPP"   "$SELGENPP"   "$ISMCPP"   "$LUMIPP"   "$ISDOWEIGHTPP"   "$LABELPP"  "$OUTPUTFILEPP"
fi

if [ $DOFITSPbPb -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPbPbSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPb" "$CUTPbPb"   "$SELGENPbPb"   "$ISMCPbPb"   "$LUMIPbPb"   "$ISDOWEIGHTPbPb"  "$LABELPbPb"  "$OUTPUTFILEPbPb"
fi

if [ $DOMCstudyPP -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$ISDOWEIGHTPP" "$MINIMUMFIT" "$MAXIMUMFIT"
fi

if [ $DOMCstudyPPReweight -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELPP" "$OUTPUTFILEMCSTUDYPP" "$UNITY" "$MINIMUMFIT" "$MAXIMUMFIT"
fi


if [ $DOMCstudyNPPP -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCNPPP"  "$SELGENPP" "$SELGENPPACCPP"  "$RECOONLYPP" "$CUTPP"  "$LABELNPPP" "$OUTPUTFILEMCSTUDYNPPP" "$ISDOWEIGHTPP" "$MINIMUMFIT" "$MAXIMUMFIT"
fi


if [ $DOMCstudyPbPbReweight -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPPACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$UNITY" "$MINIMUMFIT" "$MAXIMUMFIT"
fi

if [ $DOMCstudyPbPb -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPb" "$SELGENPPACCPbPb"  "$RECOONLYPbPb" "$CUTPbPb"  "$LABELPbPb" "$OUTPUTFILEMCSTUDYPbPb" "$ISDOWEIGHTPbPb" "$MINIMUMFIT" "$MAXIMUMFIT"
fi


if [ $DOCrossSectionPP -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEInclusiveD"  "$OUTPUTFILEPP" "$OUTPUTPrescalePP" "$USEPRESCALEPP" "$OUTPUTFILEPlotPP" "$LABELPP"
fi

if [ $DOCrossSectionPbPb -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEInclusiveD"  "$OUTPUTFILEPbPb" "$OUTPUTPrescalePbPb" "$USEPRESCALEPbPb" "$OUTPUTFILEPlotPbPb" "$LABELPbPb"
fi

if [ $DORAA -eq 1 ]; then      
g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe 
./NuclearModificationFactor.exe "$OUTPUTFILEPlotPP" "$OUTPUTFILEPlotPbPb"  "$LABELPbPb" "$OUTPUTFILERAA" 
fi


FONLLOUTPUTFILEMB="ROOTfiles/output_pp_d0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEBtoDMB="ROOTfiles/output_pp_Btod0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEInclusiveDMB="ROOTfiles/output_inclusiveDd0meson_5TeV_y1MB.root"
FONLLOUTPUTFILEBMB="ROOTfiles/output_pp_Bmeson_5TeV_y1MB.root"
OUTPUTFILEPPMB="ROOTfiles/hPtSpectrumDzeroPPMB.root"
OUTPUTFILEPPMCClosureMB="ROOTfiles/hPtSpectrumDzeroPPMCClosureMB.root"
OUTPUTFILEPlotPPMB="ROOTfiles/CrossSectionFONLLPPMB.root"
OUTPUTFILEPbPbMB="ROOTfiles/hPtSpectrumDzeroPbPbMB.root"
OUTPUTFILEPlotPbPbMB="ROOTfiles/CrossSectionFONLLPbPbMB.root"
OUTPUTFILERAAMB="ROOTfiles/outputRAAMB.root"
OUTPUTFILEMCSTUDYPPMB="ROOTfiles/MCstudiesPPMB"
OUTPUTFILEMCSTUDYPbPbMB="ROOTfiles/MCstudiesPbPbMB"


#LUMIPPMB=0.0351        #assuming sigma=70mb, Nevents=2213 millions, estimated MB efficiency=0.9  Lumi=2.213*10^9/(70*0.85*10^9pb)=2.213/(70*0.9)=0.0351
LUMIPPMB=0.028245
ISMCPPMB=0
ISDOWEIGHTPPMB=0
SELGENPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPPMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<2.0&&abs(Gtk2eta)<2.0&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0"
CUTPPMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<2.0&&abs(Dtrk2Eta)<2.0&&(DsvpvDistance/DsvpvDisErr)>3.5&&(DlxyBS/DlxyBSErr)>2.5&&Dchi2cl>0.05&&Dalpha<0.12"
TRGPPMB="(HLT_L1MinimumBiasHF1OR_part1_v1||HLT_L1MinimumBiasHF1OR_part2_v1||HLT_L1MinimumBiasHF1OR_part3_v1||HLT_L1MinimumBiasHF1OR_part4_v1||HLT_L1MinimumBiasHF1OR_part5_v1||HLT_L1MinimumBiasHF1OR_part6_v1||HLT_L1MinimumBiasHF1OR_part7_v1||HLT_L1MinimumBiasHF1OR_part8_v1||HLT_L1MinimumBiasHF1OR_part9_v1||HLT_L1MinimumBiasHF1OR_part10_v1||HLT_L1MinimumBiasHF1OR_part11_v1||HLT_L1MinimumBiasHF1OR_part12_v1||HLT_L1MinimumBiasHF1OR_part13_v1||HLT_L1MinimumBiasHF1OR_part14_v1||HLT_L1MinimumBiasHF1OR_part15_v1||HLT_L1MinimumBiasHF1OR_part16_v1||HLT_L1MinimumBiasHF1OR_part17_v1||HLT_L1MinimumBiasHF1OR_part18_v1||HLT_L1MinimumBiasHF1OR_part19_v1)"
LABELPPMB="PPMB"
USEPRESCALEPPMB=0


#LUMIPbPbMB=0.0000072        #assuming sigma=7750 mb, Nevents=50.283009 millions, estimated MB efficiency=0.9  Lumi=0.05028*10^9/(7750*0.90*10^9pb)=0.05028/(7750*0.9)=7.20*1e-6
LUMIPbPbMB=0.000023353         # 0.0578064*0.000404
ISMCPbPbMB=0
ISDOWEIGHTPbPbMB=0
SELGENPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))"
SELGENACCPbPbMB="((GisSignal==1||GisSignal==2)&&(Gy>-1&&Gy<1))&&abs(Gtk1eta)<1.5&&abs(Gtk2eta)<1.5&&Gtk1pt>1.0&&Gtk2pt>1.0"
RECOONLYPbPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5"
CUTPbPbMB="Dy>-1.&&Dy<1.&&Dtrk1highPurity&&Dtrk2highPurity&&Dtrk1Pt>1.0&&Dtrk2Pt>1.0&&Dtrk1PtErr/Dtrk1Pt<0.3&&Dtrk2PtErr/Dtrk2Pt<0.3&&abs(Dtrk1Eta)<1.5&&abs(Dtrk2Eta)<1.5&&((DlxyBS/DlxyBSErr)>1.5&&Dalpha<0.12&&((Dpt>1&&Dpt<2&&(DsvpvDistance/DsvpvDisErr)>6.0&&Dchi2cl>0.25)||(Dpt>2&&Dpt<4&&(DsvpvDistance/DsvpvDisErr)>5.86&&Dchi2cl>0.224)||(Dpt>4&&Dpt<5&&(DsvpvDistance/DsvpvDisErr)>5.46&&Dchi2cl>0.196)||(Dpt>5&&Dpt<6&&(DsvpvDistance/DsvpvDisErr)>4.86&&Dchi2cl>0.170)||(Dpt>6&&Dpt<8&&(DsvpvDistance/DsvpvDisErr)>4.54&&Dchi2cl>0.125)||(Dpt>8&&Dpt<10&&(DsvpvDistance/DsvpvDisErr)>4.42&&Dchi2cl>0.091)||(Dpt>10&&Dpt<15&&(DsvpvDistance/DsvpvDisErr)>4.06&&Dchi2cl>0.069)||(Dpt>15&&Dpt<20&&(DsvpvDistance/DsvpvDisErr)>3.71&&Dchi2cl>0.056)||(Dpt>20&&Dpt<25&&(DsvpvDistance/DsvpvDisErr)>3.25&&Dchi2cl>0.054)||(Dpt>25&&(DsvpvDistance/DsvpvDisErr)>2.97&&Dchi2cl>0.050)))"
TRGPbPbMB="(HLT_HIL1MinimumBiasHF2AND_part1_v1||HLT_HIL1MinimumBiasHF2AND_part2_v1||HLT_HIL1MinimumBiasHF2AND_part3_v1)"
LABELPbPbMB="PbPbMB"
USEPRESCALEPbPbMB=0

cp config/parametersLowpt.h parameters.h

if [ $DOFONLLMB -eq 1 ]; then      

g++ Dzerodsigmadpt.cc $(root-config --cflags --libs) -g -o Dzerodsigmadpt.exe 
./Dzerodsigmadpt.exe "$FONLLDATINPUT"  "$FONLLOUTPUTFILEMB" "$LABELPPMB"
./Dzerodsigmadpt.exe "$FONLLDATINPUTBtoD"  "$FONLLOUTPUTFILEBtoDMB" "$LABELPPMB"

g++ BplusAlldsigmadpt.cc $(root-config --cflags --libs) -g -o BplusAlldsigmadpt.exe 
./BplusAlldsigmadpt.exe "$FONLLDATINPUTB"  "$FONLLOUTPUTFILEBMB" "$LABELPPMB"
fi 

if [ $DOFEEDDOWNMB -eq 1 ]; then      

g++ RatioFeedDown.cc $(root-config --cflags --libs) -g -o RatioFeedDown.exe 
./RatioFeedDown.exe "$FONLLOUTPUTFILEMB"  "$FONLLOUTPUTFILEBtoDMB" "$FONLLOUTPUTFILEInclusiveDMB" "$LABELPPMB"

g++ plotFeedDown.C $(root-config --cflags --libs) -g -o plotFeedDown.exe 
./plotFeedDown.exe "$FONLLOUTPUTFILEMB"  "$FONLLOUTPUTFILEBMB" "$NTUPLAPYTHIA" 1 0 100 

fi

if [ $DOFITSPPMB -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPPMBUNSKIMMED"  "$INPUTMCPP"  "$TRGPPMB" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMB"   "$LUMIPPMB"   "$ISDOWEIGHTPPMB"   "$LABELPPMB"  "$OUTPUTFILEPPMB"
fi

if [ $DOFITSPbPbMB -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTDATAPbPbMBUNSKIMMED"  "$INPUTMCPbPb"  "$TRGPbPbMB" "$CUTPbPbMB"   "$SELGENPbPbMB"   "$ISMCPbPbMB"   "$LUMIPbPbMB"   "$ISDOWEIGHTPbPbMB"   "$LABELPbPbMB"  "$OUTPUTFILEPbPbMB"
fi

if [ $DOMCstudyPPMB -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" "$ISDOWEIGHTPPMB" "$MINIMUMFIT" "$MAXIMUMFIT"
fi

if [ $DOMCstudyPPMBReweight -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPPMB" "$OUTPUTFILEMCSTUDYPPMB" "$UNITY" "$MINIMUMFIT" "$MAXIMUMFIT"
fi

if [ $DOMCstudyPbPbMB -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$ISDOWEIGHTPbPbMB" "$MINIMUMFIT" "$MAXIMUMFIT"
fi

if [ $DOMCstudyPbPbMBReweight -eq 1 ]; then      
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 
./MCefficiency.exe "$INPUTMCPbPb"  "$SELGENPbPbMB" "$SELGENACCPbPbMB"  "$RECOONLYPbPbMB" "$CUTPbPbMB"  "$LABELPbPbMB" "$OUTPUTFILEMCSTUDYPbPbMB" "$UNITY" "$MINIMUMFIT" "$MAXIMUMFIT"
fi


if [ $DOCrossSectionPPMB -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEInclusiveDMB"  "$OUTPUTFILEPPMB" "$OUTPUTPrescalePP" "$USEPRESCALEPPMB" "$OUTPUTFILEPlotPPMB" "$LABELPPMB"
fi

if [ $DOCrossSectionPbPbMB -eq 1 ]; then      
g++ CrossSectionRatio.C $(root-config --cflags --libs) -g -o CrossSectionRatio.exe 
./CrossSectionRatio.exe "$FONLLOUTPUTFILEInclusiveDMB"  "$OUTPUTFILEPbPbMB" "$OUTPUTPrescalePP" "$USEPRESCALEPbPbMB" "$OUTPUTFILEPlotPbPbMB" "$LABELPbPbMB"
fi

if [ $DORAAMB -eq 1 ]; then      
g++ NuclearModificationFactor.C $(root-config --cflags --libs) -g -o NuclearModificationFactor.exe 
./NuclearModificationFactor.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPbPbMB" "$LABELPbPbMB" "$OUTPUTFILERAAMB"
fi

if [ $DOCombineCrossSection -eq 1 ]; then      
g++ CombineCrossSections.C $(root-config --cflags --libs) -g -o CombineCrossSections.exe 
./CombineCrossSections.exe "$OUTPUTFILEPlotPPMB" "$OUTPUTFILEPlotPP" 
fi

CHARGEDHADRON="/afs/cern.ch/work/g/ginnocen/public/PlotRAA.root" 

if [ $DOCombineRAA -eq 1 ]; then      
g++ CombineRAA.C $(root-config --cflags --libs) -g -o CombineRAA.exe 
./CombineRAA.exe "$OUTPUTFILERAAMB" "$OUTPUTFILERAA" "$CHARGEDHADRON"
fi


if [ $DOsystematicPtshape -eq 1 ]; then      
g++ PtShapeSystematic.C $(root-config --cflags --libs) -g -o PtShapeSystematic.exe 
./PtShapeSystematic.exe 
fi

cp config/parametersAllpt.h parameters.h

if [ $DOsystematicPthatstudyPP -eq 1 ]; then   
g++ MCefficiency.C $(root-config --cflags --libs) -g -o MCefficiency.exe 

LABELPTHATALL="pthatallPP"
FILEOUTPTHATALL="ROOTfiles/pthatallPP.root" 
LABELPTHAT10="pthat10PP"
FILEOUTPTHAT10="ROOTfiles/pthat10PP.root"
LABELPTHAT30="pthat30PP"
FILEOUTPTHAT30="ROOTfiles/pthat30PP.root"
LABELPTHAT50="pthat50PP"
FILEOUTPTHAT50="ROOTfiles/pthat50PP.root"

./MCefficiency.exe "$INPUTMCPP"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHATALL" "$FILEOUTPTHATALL" "$UNITY"  2 100
./MCefficiency.exe "$INPUTMCPPPthat10"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHAT10" "$FILEOUTPTHAT10" "$UNITY"  2 30
./MCefficiency.exe "$INPUTMCPPPthat30"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHAT30" "$FILEOUTPTHAT30" "$UNITY"  2 70
./MCefficiency.exe "$INPUTMCPPPthat50"  "$SELGENPPMB" "$SELGENACCPPMB"  "$RECOONLYPPMB" "$CUTPPMB"  "$LABELPTHAT50" "$FILEOUTPTHAT50" "$UNITY"  2 100
g++ compareMC.C $(root-config --cflags --libs) -g -o compareMC.exe 
./compareMC.exe "$FILEOUTPTHAT10" "$FILEOUTPTHAT30" "$FILEOUTPTHAT50" "$FILEOUTPTHATALL"
fi

if [ $DOFITSPPMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTMCPP"  "$INPUTMCPP"  "$TRGPPMCClosure" "$CUTPPMB"   "$SELGENPPMB"   "$ISMCPPMCClosure"   "$LUMIPPMCClosure"   "$ISDOWEIGHTPPMCClosure"   "$LABELPPMCClosure"  "$OUTPUTFILEPPMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPPMCClosure" "$LABELPP"
fi

if [ $DOFITSPbPbMCClosure -eq 1 ]; then      
g++ fitD.C $(root-config --cflags --libs) -g -o fitD.exe 
./fitD.exe "$INPUTMCPbPb"  "$INPUTMCPbPb"  "$TRGPbPbMCClosure" "$CUTPbPbMB"   "$SELGENPbPb"   "$ISMCPbPbMCClosure"   "$LUMIPbPbMCClosure"   "$ISDOWEIGHTPbPbMCClosure"   "$LABELPbPbMCClosure"  "$OUTPUTFILEPbPbMCClosure"
g++ ClosureTest.C $(root-config --cflags --libs) -g -o ClosureTest.exe 
./ClosureTest.exe "$OUTPUTFILEPbPbMCClosure" "$LABELPbPb"
fi



