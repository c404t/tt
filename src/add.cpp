#include <stdlib.h>
#include <cstring>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: tt add <task>" << std::endl;
        std::cerr << "Example: tt add \"feed the cat\"" << std::endl;
        return -1;
    }
    else
    {
        //generate new task from argv[2] using json
        system("ls -la | grep tasks.json");
        std::cout << "Task "<< argv[1] << " was added."<< std::endl;
    }

    return 0;
}
