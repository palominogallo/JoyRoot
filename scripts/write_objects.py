import write_tool

def write_class( filepath, filename ):

    write_tool.write_top_file( filepath, filename, "cc" )
    fileclass = open(filepath+filename+".cc", 'a')
    fileclass.write( "%s::%s(){\n}\n\n" % (filename,filename) )
    fileclass.write( "%s::~%s(){\n}\n\n" % (filename,filename) )
    fileclass.close()
    write_tool.write_bottom_file( filepath, filename, "cc" )

def write_header( filepath, filename ):

    write_tool.write_top_file( filepath, filename, "hh" )
    fileclass = open(filepath+filename+".hh", 'a')
    fileclass.write( "class %s\n{\n\n \tpublic:\n\n" % filename )
    fileclass.write( "\t\t//! Default Constructor\n" )
    fileclass.write( "\t\t%s();\n\n" % filename )
    fileclass.write( "\t\t//! Destructor\n" )
    fileclass.write( "\t\tvirtual ~%s();\n\n" % filename )
    fileclass.write( "\tpublic:\n\n" )
    fileclass.write( "\t\t// Write members here\n\n" )
    fileclass.close()
    write_tool.write_bottom_file( filepath, filename, "hh" )

def write_histos( filepath, classname, filename ):

    write_tool.write_top_file( filepath, filename+"Histos", "cc" )
    filehistos = open( filepath+filename+"Histos.cc", "a" )
    filehistos.write("#include \"%s.hh\"\n\n" % classname )
    filehistos.write( "//=================================================================\n" )
    filehistos.write( "// %sHistos\n" % filename )
    filehistos.write( "//\n" )
    filehistos.write( "//=================================================================\n" )
    filehistos.write( "int %sHistos( TString dPDFin, TString dPDFout )\n{\n" % filename )
    filehistos.write( "\t// Create file to store histograms\n" )
    filehistos.write( "\tTFile *rootfile = new TFile( dPDFout+\"rootfiles/out_name.root\",\"RECREATE\");\n" )
    filehistos.write( "\tTH1F *htest = Plot1::bookTH1F( \"htest\", \"title;xtitle;ytitle;units\", nbins, xmin, xmax, true);\n\n" )
    filehistos.write( "\t// TChain to retrieve data\n" )
    filehistos.write( "\tTChain *c%s = new TChain(\"tree_name\");\n" % classname.lower() )
    filehistos.write( "\tc%s->Add(dPDFin+\"/file_name\");\n" % classname.lower() )
    filehistos.write( "\t%s *%s = new %s( c%s );\n" % (classname, classname.lower(), classname, classname.lower()) )
    filehistos.write( "\tLong64_t nevents = %s->GetEntries();\n\n" % classname.lower() )
    filehistos.write( "\t// Loop\n" )
    filehistos.write( "\tfor ( Int_t index = 0; index < nevents; index++)\n\t{\n" )
    filehistos.write( "\t\t%s->GetEntry(index);\n\n\t}\n\n" % classname.lower() )
    filehistos.write( "\trootfile->Write();\n")
    filehistos.write( "\trootfile->Close();\n\n")
    filehistos.write( "\treturn 0;\n\n}\n\n")
    filehistos.close()
    write_tool.write_help( filepath, filename+"Histos" )
    write_tool.write_main( filepath, filename+"Histos" )

