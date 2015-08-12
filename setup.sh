#!/bin/bash

if [ -z "$JOYROOTROOT" ]; then
	echo " setting PlotUtils!! "
	echo " "
	export JOYROOTROOT=$HOME/Work/JoyRoot
	export DYLD_LIBRARY_PATH=$JOYROOTROOT/lib:$DYLD_LIBRARY_PATH #MAC OSX
	#export LD_LIBRARY_PATH=$JOYROOTROOT/lib:$LD_LIBRARY_PATH
else
  echo " PlotUtils is already setup!!"
  echo " "
fi
