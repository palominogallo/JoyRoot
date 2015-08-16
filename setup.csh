#! /bin/tcsh 

if ( ! $?JOYROOTROOT ) then
  setenv JOYROOTROOT 
  setenv LD_LIBRARY_PATH /usr/local/lib:$ROOTSYS/lib:$JOYROOTROOT/lib:$LD_LIBRARY_PATH
else
  echo " JOYROOTROOT is already setup"
  echo " "
endif

