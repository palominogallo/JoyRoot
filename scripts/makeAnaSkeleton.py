#!/bin/python

import sys, os
import write_objects

def make_skeleton():
    workpath = sys.argv[1]
    dirname = sys.argv[2]
    classname = sys.argv[3]
    os.system("mkdir -p %s/%s" % (workpath, dirname) )
    os.system("mkdir -p %s/%s/src" % (workpath, dirname) )
    os.system("mkdir -p %s/%s/include" % (workpath, dirname) )
    os.system("mkdir -p %s/%s/make_histos" % (workpath, dirname) )
    os.system("mkdir -p %s/%s/make_plots" % (workpath, dirname) )
    os.system("mkdir -p %s/%s/rootfiles" % (workpath, dirname) )
    os.system("mkdir -p %s/%s/plots" % (workpath, dirname) )
    write_objects.write_rootclass( workpath+"/"+dirname+"/src/", classname )
    write_objects.write_rootheader( workpath+"/"+dirname+"/include/", classname )
    write_objects.write_histos( workpath+"/"+dirname+"/make_histos/", classname, "Basic" )
    write_objects.write_plots( workpath+"/"+dirname+"/make_plots/", classname, "Basic" )
    write_objects.write_makefile(workpath, dirname, classname )

    joypath0 = sys.argv[0].split("/")
    joypath0.remove("makeAnaSkeleton.py")
    joypath0.remove("scripts")
    joypath = "/".join(joypath0)
    write_objects.write_setup(joypath, workpath, dirname, classname )

def showHelp():
    print "usage: python %s <work path> <directory name> <classname>" % sys.argv[0]
    exit(-1)

if len(sys.argv) == 4:
    make_skeleton()
else:
    showHelp()



