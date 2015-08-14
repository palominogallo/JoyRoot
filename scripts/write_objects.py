import write_tool

def write_class( filepath, filename ):

    write_tool.write_top_file( filepath, filename, "cc" )
    fileclass = open(filepath+filename+".cc", 'a')
    fileclass.write( "%s::%s(){\n}\n\n" % (filename,filename) )
    fileclass.write( "%s::~%s(){\n}\n\n" % (filename,filename) )
    fileclass.close()

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
    fileclass.write( "};\n\n" )
    fileclass.write( "#endif\n" )
    fileclass.close()

def write_rootclass( filepath, filename ):

    write_tool.write_top_file( filepath, filename, "cc" )
    fileclass = open(filepath+filename+".cc", 'a')
    write_tool.write_function_comment( fileclass, "Constructor" )
    fileclass.write( "%s::%s( TTree *tree )\n{\n" % (filename,filename) )
    fileclass.write( "\tmTree = tree;\n\n" )
    fileclass.write( "\tmTree->SetBranchAddress(\" \", , );\n\n" )
    fileclass.write( "\tmNevents = mTree->GetEntries();\n}\n\n" )
    write_tool.write_function_comment( fileclass, "Destructor" )
    fileclass.write( "%s::~%s()\n{\n\tdelete mTree->GetCurrentFile();\n}\n\n" % (filename,filename) )
    write_tool.write_function_comment( fileclass, "GetEntry" )
    fileclass.write( "%s::GetEntry( Long64_t entry )\n{\n" % filename )
    fileclass.write( "\treturn mTree->GetEntry( entry );\n}\n\n" )
    fileclass.close()

def write_rootheader( filepath, filename ):

    write_tool.write_top_file( filepath, filename, "hh" )
    fileclass = open(filepath+filename+".hh", 'a')
    fileclass.write( "class %s\n{\n\n \tpublic:\n\n" % filename )
    fileclass.write( "\t\t//! Default Constructor\n" )
    fileclass.write( "\t\t%s();\n\n" % filename )
    fileclass.write( "\t\t//! Destructor\n" )
    fileclass.write( "\t\tvirtual ~%s();\n\n" % filename )
    fileclass.write( "\tpublic:\n\n" )
    fileclass.write( "\t\tTTree\t\t*mTree;\n" )
    fileclass.write( "\t\tLong64_t\t\tmNevents;\n\n" )
    fileclass.write( "\t\t// Declaration of leaf types\n\n" )
    fileclass.write( "\t\t// List of branches\n\n" )
    fileclass.write( "\t\tInt_t GetEntry( Long64_t entry );\n" )
    fileclass.write( "\t\tinline Long64_t GetEntries(){ return mNevents; };\n" )
    fileclass.write( "};\n\n" )
    fileclass.write( "#endif\n" )
    fileclass.close()

def write_histos( filepath, classname, filename ):

    write_tool.write_top_file( filepath, filename+"Histos", "cc" )
    filehistos = open( filepath+filename+"Histos.cc", "a" )
    filehistos.write("#include \"%s.hh\"\n\n" % classname )
    write_tool.write_mainfunction_comment( filehistos, "%sHistos" % filename )
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

