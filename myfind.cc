#include <iostream>
#include <fstream>
#include <mutex>
#include <chrono>
#include <vector>

void showhelp()
{
    std::cout << "Usage: myfind [-R] [-i] searchpath filename1 [filename 2] [...filename n]" << std::endl;
    std::cout << "\t-R = recursively search subdirectories" << std:endl;
    std::cout << "\t-i = ignore uppercase/lowercase" << std:endl;
}

int main(int argc, char *argv[], char *envp[])
{
    bool flag_recursive = false;
    bool flag_ignorecase = false;
    std::string path = "";
    std::vector <std::string> targets;

    // read the arguments
    // i=0 is the call to this program
    for(int i = 1; i < argc; ++i)
    {
        std::string arg = std::string(argv[i]);

        if( arg == "-R" ) flag_recursive = true;
        else if( arg == "-i" ) flag_ignorecase = true;
        else if( path == "" ) path = arg;
        else targets.push_back( arg );
    }

    // DEBUG output what you understood
    std::cout << "Recursive: " << flag_recursive << "; IgnoreCase: " << flag_ignorecase << "; Path: " << path << "; Targets:" << std::endl;
    for (std::vector<std::string>::iterator it = targets.begin() ; it != targets.end(); ++it)
        std::cout << *it << std::endl;

    return 0;
}
