#!/bin/bash

# Find the root of the building area.
___joyroot_root() {
    COUNT=10
    while true; do
			if [ -e ./include/JoyRoot -a -d ./include/JoyRoot -a -e ./include/JoyRoot/Plot1.hh ]; then
				echo ${PWD}
				return
			fi
			COUNT=$(expr ${COUNT} - 1)
			if [ ${COUNT} -lt 1 ]; then
				echo invalid-directory
				return
			fi
			cd ..
    done
}

export JOYROOT_ROOT
JOYROOT_ROOT=$(___joyroot_root)
unset -f ___joyroot_root

if [ ${JOYROOT_ROOT} = "invalid-directory" ]; then
    echo JOYROOT setup.sh must be sourced in your installation directory.
    return
fi

if [ "$(uname)" == "Darwin" ]; then
    export DYLD_LIBRARY_PATH=$JOYROOT_ROOT/lib:${DYLD_LIBRARY_PATH}
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
    export LD_LIBRARY_PATH=$JOYROOT_ROOT/lib:${LD_LIBRARY_PATH}
fi
