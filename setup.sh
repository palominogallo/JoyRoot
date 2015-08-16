#!/bin/bash

if [ -z "$JOYROOTROOT" ]; then
	echo " setting JOYROOT!! "
	echo " "
	export JOYROOTROOT=
	export DYLD_LIBRARY_PATH=$JOYROOTROOT/lib:$DYLD_LIBRARY_PATH #MAC OSX
	#export LD_LIBRARY_PATH=$JOYROOTROOT/lib:$LD_LIBRARY_PATH
else
  echo " JOYROOT is already setup!!"
  echo " "
fi
