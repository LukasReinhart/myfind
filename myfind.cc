#include <iostream>
#include <fstream>
#include <mutex>
#include <chrono>

int main(int argc, char *argv[], char *envp[])
{
    std::cout << "Hello, world!" << std::endl;

    for(int i = 0; i < argc; ++i)
    {
        std::cout << argv[i] << std::endl;
    }

    return 0;
}
