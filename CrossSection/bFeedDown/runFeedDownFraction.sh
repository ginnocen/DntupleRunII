#!/bin/bash

##

DOSAVEHIST_PP=1
DOPLOTFIT_PP=1
DOSAVEHIST_PPMB=1
DOPLOTFIT_PPMB=1
DOSAVEHIST_PbPb=1
DOPLOTFIT_PbPb=1
DOSAVEHIST_PbPbMB=1
DOPLOTFIT_PbPbMB=1

#

PTMIN_PP=(15 20 25 35 50)
PTMAX_PP=(20 25 35 50 100)
PTMIN_PPMB=(2 6 8 10)
PTMAX_PPMB=(6 8 10 15)
PTMIN_PbPb=(20 40 50)
PTMAX_PbPb=(40 50 100)
PTMIN_PbPbMB=(6 10 15)
PTMAX_PbPbMB=(10 15 20)

#

COLL_PP=PP
COLL_PPMB=PPMB
COLL_PbPb=PbPb
COLL_PbPbMB=PbPbMB

##

count_PP=0
for ptmin_PP in ${PTMIN_PP[@]}
do
    echo "Processing - $COLL_PP - ptbin: (${ptmin_PP}, ${PTMAX_PP[$count_PP]}) ..."
    if [ $DOSAVEHIST_PP -eq 1 ]; then
        g++ bFeedDownFractionPP.C $(root-config --cflags --libs) -g -o bFeedDownFractionPP.exe
        ./bFeedDownFractionPP.exe ${ptmin_PP} ${PTMAX_PP[$count_PP]}
        rm bFeedDownFractionPP.exe
    fi
    if [ $DOPLOTFIT_PP -eq 1 ]; then
        g++ plotFits.C $(root-config --cflags --libs) -g -o plotFits.exe
        ./plotFits.exe ${ptmin_PP} ${PTMAX_PP[$count_PP]} ${COLL_PP}
        rm plotFits.exe
    fi
    count_PP=$((count_PP+1))
done


count_PPMB=0
for ptmin_PPMB in ${PTMIN_PPMB[@]}
do
    echo "Processing - $COLL_PPMB - ptbin: (${ptmin_PPMB}, ${PTMAX_PPMB[$count_PPMB]}) ..."
    if [ $DOSAVEHIST_PPMB -eq 1 ]; then
        g++ bFeedDownFractionPPMB.C $(root-config --cflags --libs) -g -o bFeedDownFractionPPMB.exe
        ./bFeedDownFractionPPMB.exe ${ptmin_PPMB} ${PTMAX_PPMB[$count_PPMB]}
        rm bFeedDownFractionPPMB.exe
    fi
    if [ $DOPLOTFIT_PPMB -eq 1 ]; then
        g++ plotFits.C $(root-config --cflags --libs) -g -o plotFits.exe
        ./plotFits.exe ${ptmin_PPMB} ${PTMAX_PPMB[$count_PPMB]} ${COLL_PPMB}
        rm plotFits.exe
    fi
    count_PPMB=$((count_PPMB+1))
done


count_PbPb=0
for ptmin_PbPb in ${PTMIN_PbPb[@]}
do
    echo "Processing - $COLL_PbPb - ptbin: (${ptmin_PbPb}, ${PTMAX_PbPb[$count_PbPb]}) ..."
    if [ $DOSAVEHIST_PbPb -eq 1 ]; then
        g++ bFeedDownFractionPbPb.C $(root-config --cflags --libs) -g -o bFeedDownFractionPbPb.exe
        ./bFeedDownFractionPbPb.exe ${ptmin_PbPb} ${PTMAX_PbPb[$count_PbPb]}
        rm bFeedDownFractionPbPb.exe
    fi
    if [ $DOPLOTFIT_PbPb -eq 1 ]; then
        g++ plotFits.C $(root-config --cflags --libs) -g -o plotFits.exe
        ./plotFits.exe ${ptmin_PbPb} ${PTMAX_PbPb[$count_PbPb]} ${COLL_PbPb}
        rm plotFits.exe
    fi
    count_PbPb=$((count_PbPb+1))
done


count_PbPbMB=0
for ptmin_PbPbMB in ${PTMIN_PbPbMB[@]}
do
    echo "Processing - $COLL_PbPbMB - ptbin: (${ptmin_PbPbMB}, ${PTMAX_PbPbMB[$count_PbPbMB]}) ..."
    if [ $DOSAVEHIST_PbPbMB -eq 1 ]; then
        g++ bFeedDownFractionPbPbMB.C $(root-config --cflags --libs) -g -o bFeedDownFractionPbPbMB.exe
        ./bFeedDownFractionPbPbMB.exe ${ptmin_PbPbMB} ${PTMAX_PbPbMB[$count_PbPbMB]}
        rm bFeedDownFractionPbPbMB.exe
    fi
    if [ $DOPLOTFIT_PbPbMB -eq 1 ]; then
        g++ plotFits.C $(root-config --cflags --libs) -g -o plotFits.exe
        ./plotFits.exe ${ptmin_PbPbMB} ${PTMAX_PbPbMB[$count_PbPbMB]} ${COLL_PbPbMB}
        rm plotFits.exe
    fi
    count_PbPbMB=$((count_PbPbMB+1))
done


##