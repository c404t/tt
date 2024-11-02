#include <stdlib.h>
#include <cstring>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: tt [command] <arguments>" << std::endl;
        return -1;
    }
    else 
    {
        if (strcmp(argv[1], "add") == 0)
        {
            if (argc < 3)
            {
                system("./add");
            }
            else 
            {
                std::string task = argv[2];
                std::string send = "./add \"" + task + "\"";
                system(send.c_str());
            }
        }
        else 
        {
            std::cerr << "Invalid command. " << std::endl;
            std::cerr << "Try 'tt --help' for more information." << std::endl;
            return -1;
        }
    }

    return 0;
}
