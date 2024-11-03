#include <stdlib.h>
#include <cstring>
#include <string>
#include <fmt/format.h>
#include <iostream>

void command(std::string cmd, int argc, char* argv[])
{
    if (argc < 3)
    {
        std::string command = cmd;
        system(command.c_str());
    }
    else
    {
        std::string task = argv[2];
        std::string send = fmt::format("./{} {}", cmd, task);
        system(send.c_str());
    }
}

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
            command("add", argc, argv);
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
