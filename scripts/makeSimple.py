#!/bin/python
# to just plot histograms already defined in rootfiles

import sys, os
import write_objects

def make_plot():
    workpath = sys.argv[1]
    dirname = sys.argv[2]
    os.system("mkdir -p %s/%s/{make_plots,rootfiles,plots}" % (workpath, dirname) )
    write_objects.write_plots( workpath+"/"+dirname+"/make_plots/", "", "Basic" )
    write_objects.write_makefile2( workpath, dirname )

    joypath0 = sys.argv[0].split("/")
    joypath0.remove("makeSimple.py")
    joypath0.remove("scripts")
    joypath = "/".join(joypath0)
    write_objects.write_setup(joypath, workpath, dirname )

def showHelp():
    print "usage: python %s <work path> <directory name> " % sys.argv[0]
    exit(-1)

if len(sys.argv) == 3:
    make_plot()
else:
    showHelp()



