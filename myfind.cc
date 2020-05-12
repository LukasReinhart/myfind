#include <iostream>
#include <fstream>
#include <assert.h> // alias sanitycheck.h
#include <mutex>
#include <chrono>
#include <vector>
#include <unistd.h> // getopt()

/*
|
|   Verbosity & Sanitation
|
*/

std::string program_name = "myfile"; // program_name may change to the exact command used in console.


void print_usage()
{
    std::cout << "Usage: " << program_name << " [options] searchpath filename1 [filename 2] [...filename n]" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  -R \t Recursively search subdirectories" << std::endl;
    std::cout << "  -i \t ignore uppercase/lowercase" << std::endl;
}


void abort_doubleflag(char c)
{
    std::cout << program_name << ": option can only be used once -- '" << c << '\'' << std::endl;
    print_usage();
    exit(1);
}


/*
|
|   Main
|
*/

int main(int argc, char *argv[], char *envp[])
{
    bool flag_recursive = false;
    bool flag_ignorecase = false;
    std::string path = "";
    std::vector <std::string> targets;

    program_name = argv[0];

    // simple approach without getopt or verbosity
    /*
    for(int i = 1; i < argc; ++i)
    {
        std::string arg = std::string(argv[i]);

        if( arg == "-R" ) flag_recursive = true;
        else if( arg == "-i" ) flag_ignorecase = true;
        else if( path == "" ) path = arg;
        else targets.push_back( arg );
    }
    */

    char c;

    opterr = 1; // yells if the user makes mistakes

    while ( (c = getopt( argc, argv, "Ri" )) != EOF ) {
        switch (c) {
            case '?':
                print_usage();
                exit(1);
                break;
            case 'R':
                if( flag_recursive ) abort_doubleflag(c);
                flag_recursive = true;
                break;
            case 'i':
                if( flag_ignorecase ) abort_doubleflag(c);
                flag_ignorecase = true;
                break;
            default:
                assert(0);
        }
    }
    while (optind < argc)
    {
        if( path == "")
            path = argv[optind];
        else
            //TODO make sure this does not contain forbidden symbols (in particular '/')?
            targets.push_back( argv[optind] );
        ++optind;
    }
    if ( path == "" || targets.size() < 1)
    {
        print_usage();
        exit(1);
    }

    // DEBUG output what you understood
    /*
    std::cout << "Recursive: " << flag_recursive << "; IgnoreCase: " << flag_ignorecase << "; Path: " << path << "; Targets:" << std::endl;
    for (std::vector<std::string>::iterator it = targets.begin() ; it != targets.end(); ++it)
        std::cout << *it << std::endl;
    */

    for (std::vector<std::string>::iterator it = targets.begin() ; it != targets.end(); ++it)
    {
        //TODO starte Suchen
    }

    return 0;
}
