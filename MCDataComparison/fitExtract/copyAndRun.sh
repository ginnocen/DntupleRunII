#!/bin/bash

mkdir test$1$2$3$4/
cp -r doAnalysisVariable.sh compareMCdataVariables.C fitDVariable.C uti.h config test$1$2$3$4
cd test$1$2$3$4
mkdir FitsVariables OutPuts
./doAnalysisVariable.sh $1 $2 $3 $4
cp FitsVariables/* ../FitsVariables_$2$3$4/
cp OutPuts/* ../OutPuts_$2$3$4/
cd ../
