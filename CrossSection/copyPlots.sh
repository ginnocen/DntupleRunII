MYPWD=${PWD}

rm -rf analysisNote
svn co -N svn+ssh://svn.cern.ch/reps/tdr2 analysisNote
cd analysisNote
svn update utils
svn update -N notes
svn update notes/AN-15-308
eval `./notes/tdr runtime -sh`
cd notes/AN-15-308/trunk

cp "$MYPWD"/Fits/DMass*.pdf Plots/Fits/.
cp "$MYPWD"/canvasEff*.pdf Plots/Efficiency/.
cp "$MYPWD"/canvas_pp_Btod0meson_5TeV_y1.pdf Plots/FONLL/.
cp "$MYPWD"/canvas_pp_d0meson_5TeV_y1.pdf Plots/FONLL/.
cp "$MYPWD"/canvasSigma*.pdf Plots/Results/.
cp "$MYPWD"/canvasRAA.pdf Plots/Results/.

tdr --style=an b AN-15-308 
svn add Plots/*/*
svn commit -m "update of plots" Plots
cd "$MYPWD"


