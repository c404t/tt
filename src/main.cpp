#include <stdlib.h>
#include <cstring>
#include <string>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <iostream>

void
show_help()
{
    std::cout << "tt | command line tasktracker"              << std::endl << std::endl
              << "tt add \"new task\""                        << std::endl
              << "tt update <task id> \"redefine task\""      << std::endl
              << "tt remove <task id>"                        << std::endl << std::endl
              << "tt done <task id>"                          << std::endl
              << "tt wip <task id>"                           << std::endl
              << "tt list [wip | done | notdone]"             << std::endl
              ;
}

void 
add(char* argv[]) 
{
    std::cout << "good to go!" << std::endl;
    std::cout << argv[2] << std::endl;
}

bool
is_command(std::string cmd, char* argv[])
{
    if(strcmp(argv[1], cmd.c_str()) == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}

int 
main(int argc, char* argv[])
{
    if (argc < 3)
    {
        std::cerr << "Usage: tt [command] <arguments>" << std::endl;
        std::cerr << "Try 'tt --help' for more information." << std::endl;
        return -1;
    }
    else 
    {
        if(is_command("add", argv))
        {
            add(argv);
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
