MYPWD=${PWD}

rm -rf analysisNote
svn co -N svn+ssh://svn.cern.ch/reps/tdr2 analysisNote
cd analysisNote
svn update utils
svn update -N notes
svn update notes/AN-15-308
eval `./notes/tdr runtime -sh`
cd notes/AN-15-308/trunk

cp "$MYPWD"/plotFits/Fits/DMassP*.pdf Plots/plotFits/Fits/.
cp "$MYPWD"/plotFits/FitsCent10/DMassP*.pdf Plots/plotFits/FitsCent10/.

cp "$MYPWD"/plotEff/*PnNP*.pdf Plots/Efficiency/.
cp "$MYPWD"/plotCrossSection/*.pdf Plots/plotCrossSection/.
cp "$MYPWD"/plotRAA/*.pdf Plots/plotRAA/.

cp "$MYPWD"/canvasPtreweightedComparisonPP.pdf Plots/SystPtShape/.
cp "$MYPWD"/canvasPtreweightedComparisonPPMB.pdf Plots/SystPtShape/.
cp "$MYPWD"/canvasPtreweightedComparisonPbPb.pdf Plots/SystPtShape/.
cp "$MYPWD"/canvasPtreweightedComparisonPbPbMB.pdf Plots/SystPtShape/.
cp "$MYPWD"/canvasPtReweightPPptreweighted.pdf Plots/SystPtShape/.

cp "$MYPWD"/canvasTotAccEfficiencyPtHatWeight_isPbPb0.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasTotAccEfficiencyPtHatWeight_isPbPb1.pdf Plots/Efficiency/.

cp "$MYPWD"/canvasClosurePP.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasClosurePbPb.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasClosurePPMB.pdf Plots/Efficiency/.
cp "$MYPWD"/canvasClosurePbPbMB.pdf Plots/Efficiency/.

#tdr --style=an b AN-15-308 

svn add Plots/*/*
svn commit -m "update of plots" Plots
cd "$MYPWD"


