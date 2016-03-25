#!/bin/bash

mkdir test$1$2$3/
cp -r doAnalysisVariable.sh compareMCdataVariables.C fitDVariable.C uti.h config test$1$2$3
cd test$1$2$3
mkdir FitsVariables OutPuts
./doAnalysisVariable.sh $1 $2 $3
cp FitsVariables/* ../FitsVariables_$2$3/
cp OutPuts/* ../OutPuts_$2$3/
cd ../
