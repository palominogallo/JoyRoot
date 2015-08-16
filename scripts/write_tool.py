def write_top_file( filepath, filename, extension ):
    filet = open(filepath+filename+"."+extension, 'w')
    isclass =  "Histos" not in filename and "Plots" not in filename
    if isclass:
        filet.write("#ifndef %s_%s\n" % ( filename.upper(), extension.upper() ) )
        filet.write("#define %s_%s\n\n" % ( filename.upper(), extension.upper() ) )
    if extension == 'hh':
        filet.write("#include <Plot1.hh>\n")
        filet.write("#include <Utils1.hh>\n\n")
    if extension == 'cc' and isclass:
        filet.write("#include \"%s.hh\"\n\n" % filename)
    filet.close()

def write_function_comment( filename, function_name ):
    filename.write( "//=================================================================\n" )
    filename.write( "// %s\n" % function_name )
    filename.write( "//=================================================================\n" )

def write_mainfunction_comment( filename, function_name ):
    filename.write( "//=================================================================\n" )
    filename.write( "// %s\n" % function_name )
    filename.write( "//\n" )
    filename.write( "//=================================================================\n" )

def write_help( filepath, filename ):
    fileh = open( filepath+filename+".cc", "a")
    write_function_comment( fileh, "showHelp" )
    fileh.write( "void showHelp( TString program_name )\n{\n" )
    fileh.write( "\tcout<<\"Usage:\t\t\"<< program_name <<\" [-option] [argument]\" << endl;\n" )
    fileh.write( "\tcout<<\"option:\t\t\"<<\"-i input directory \" << endl;\n")
    fileh.write( "\tcout<<\"option:\t\t\"<<\"-o output directory \"<< endl;\n")
    fileh.write( "\tcout<<\"example:\t\t\"<< program_name ")
    fileh.write( "<<\"-i <PDF input directory> -o <PDF plot output directoy >\" <<endl;\n")
    fileh.write( "\texit(-1);\n}\n\n")
    fileh.close()

def write_main( filepath, filename ):
    filem = open( filepath+filename+".cc", "a")
    write_mainfunction_comment( filem, "main" )
    filem.write( "int main(int argc, char **argv)\n{\n")
    filem.write( "\tTString dPDFin;\n" )
    filem.write( "\tTString dPDFout;\n\n" )
    filem.write( "\tif ( argc == 1 ) showHelp( TString(argv[0]) );\n" )
    filem.write( "\tint opt;\n" )
    filem.write( "\twhile ( ( opt = getopt( argc, argv, \"i:o:\") ) != -1 )\n\t{\n" )
    filem.write( "\t\tswitch(opt)\n\t\t{\n ")
    filem.write( "\t\t\tcase \'i\': dPDFin = TString(optarg); break;\n")
    filem.write( "\t\t\tcase \'o\': dPDFout = TString(optarg); break;\n")
    filem.write( "\t\t\tdefault  : showHelp(argv[0]);\n\t\t}\n\t}\n")
    filem.write( "\treturn %s(dPDFin, dPDFout);\n}" % filename )
    filem.close()


