#!/bin/python
#python 3

import sys, os
import write_objects

def make_skeleton():
	workpath = sys.argv[1]	
	dirname = sys.argv[2]
	classname = sys.argv[3]
	os.system('mkdir -p {0}/{1}/{{src,include,make_histos,make_plots,rootfiles,plots}}'.format(workpath, dirname) )
	write_objects.write_rootclass( workpath+"/"+dirname+"/src/", classname )
	write_objects.write_rootheader( workpath+"/"+dirname+"/include/", classname )
	write_objects.write_histos( workpath+"/"+dirname+"/make_histos/", classname, "Basic" )
	write_objects.write_plots( workpath+"/"+dirname+"/make_plots/", classname, "Basic" )
	write_objects.write_makefile(workpath, dirname, classname )

	joypath0 = sys.argv[0].split("/")
	joypath0.remove("makeAnaSkeleton.py")
	joypath0.remove("scripts_python3")	
	joypath = "/".join(joypath0)	
	print ("Joy dir: %s " % joypath)
	write_objects.write_setup(joypath, workpath, dirname )

def showHelp():
	print( "usage: python %s <work path> <directory name> <classname>" .format( sys.argv[0]) )
	exit(-1)

if len(sys.argv) == 4:
	make_skeleton()
else:
	showHelp()



