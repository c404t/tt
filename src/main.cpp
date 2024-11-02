#include <stdlib.h>
#include <cstring>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: tt [command] <arguments>" << std::endl;
        return -1;
    }
    else 
    {
        if (strcmp(argv[1], "add") == 0)
        {
            system("ls -l");
        }
        else 
        {
            std::cout << "Invalid command. " << std::endl;
            std::cout << "Try 'tt --help' for more information." << std::endl;
            return -1;
        }
    }

    return 0;
}
