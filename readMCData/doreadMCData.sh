#!/bin/bash

###
i=${1:-0}
COLLSYST=("pp_MB" "pp_HF" "PbPb_MB" "PbPb_HF")
BINNING=('const int nbins=9; double ptBins[nbins+1]={2,3,4,5,6,8,10,12.5,15,20};'
    'const int nbins=4; double ptBins[nbins+1]={20,25,30,35,40};'
    'const int nbins=9; double ptBins[nbins+1]={2,3,4,5,6,8,10,12.5,15,20};'
    'const int nbins=4; double ptBins[nbins+1]={20,25,30,35,40};')
YMIN=(0.4 0.4 0.4 0.4)
YMAX=(2.52 1.52 2.626 2.031)
VARS=("Dpt")


sed "1i${BINNING[i]}" readMCData.C > readMCData_tmp.C

###

g++ readMCData_tmp.C $(root-config --cflags --libs) -g -o readMCData_tmp.exe 
./readMCData_tmp.exe ${VARS[0]} ${COLLSYST[i]} ${YMIN[i]} ${YMAX[i]}
rm readMCData_tmp.exe
rm readMCData_tmp.C
