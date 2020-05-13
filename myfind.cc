#include <stdio.h> // it says "std" it's probably good to have
#include <stdlib.h> // it says "std" it's probably good to have
#include <sys/wait.h> // wait(), for use with fork()
#include <iostream> // kout & zin
//#include <fstream> // read or write files
#include <assert.h> // alias sanitycheck.h
//#include <mutex> // for managing shared resources among threads
#include <chrono> // useful for performance eval
#include <vector>
// nooo you can't just use vectors whenever you're too lazy to make dynamic arrays!! The overheadudelidoo nooooo
// haha vector go push_brrr
#include <unistd.h> // getopt() & friends
#include <cctype> // tolower()
#include <filesystem> // exactly what it says
namespace fs = std::filesystem;

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
|   The actual file search
|
*/

std::string to_lowercase( std::string s )
{
    for(char & c : s )
    {
        c = std::tolower(c);
    }
    return s;
}


void find_filepath( std::string path, std::string target, bool recursive, bool ignorecase )
{
    if( ignorecase ) target = to_lowercase( target );

    for (const auto & entry : fs::directory_iterator(path) )
    {
        if( entry.is_regular_file() )
        {
            std::string entryname = entry.path().filename();
            if( ignorecase ) entryname = to_lowercase( entryname );
            if( entryname == target )
                std::cout << getpid() << ": " << target << ": " << fs::absolute(entry.path()) << std::endl;
        }
        else if( entry.is_directory() && recursive )
        {
            find_filepath( entry.path().string(), target, recursive, ignorecase );
        }
    }
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

    //pid_t children[] = new pid_t[ targets.size() ];
    std::vector <pid_t> children;

    for( int i = 0; i < targets.size(); ++i )
    {
	    pid_t pid = fork();

        switch( pid )
        {
            case -1:
                std::cout << "Childprozess #" << i << " could not be started." << std::endl;
	            //exit(EXIT_FAILURE);
                break;
            case 0: //child
                try
                {
                    // Run a search for this file...
                    find_filepath( path, targets[i], flag_recursive, flag_ignorecase );
                    // ...then hand control back to parent.
                    exit(0);
                }
                catch(fs::filesystem_error except)
                {
                    std::cout << "Childprocess #" << i << " had an error:" << std::endl << '\t' << except.what() << std::endl;
                    exit(1);
                }
                break;
            default: //parent
                std::cout << "Childprocess #" << i << " with PID: " << pid << " started." << std::endl;
                //children[i] = pid;
                children.push_back( pid );
        }
    }

    while( children.size() > 0 )
    {
        int status = 0;
        pid_t pid = wait( &status );

        std::cout << "Childprocess with PID: " << pid << " ended with " << WEXITSTATUS(status) << std::endl;

        for( int i = 0; i < children.size(); ++i )
        {
            if( children[i] == pid )
            {
                children.erase( children.begin() + i );
                break;
            }
        }
    }

    exit(EXIT_SUCCESS);
    return 0;
}
