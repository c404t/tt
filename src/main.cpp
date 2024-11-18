#include <iostream>
#include <string>
#include <unordered_set>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

void
usage(char* argv)
{
    cout << "Usage: " 
         << "(add | remove | update) <task> " << endl
         << "       (list | listw | listd) <id> " << endl
         << "       (markd | markw) <id> " << endl
         << "       (clear | reset) " << endl;
}

int
main(int argc, char* argv[])
{
    if(argc < 2)
    {
        cerr << "Error: expected more arguments." << endl;
        usage(argv[0]);
        return -1;
    }
    
    std::unordered_set<std::string> commands =
    {
        "add",
        "remove",
        "update",
        
        "list",
        "listw",
        "listd",

        "markd",
        "markw",

        "clear",
        "reset"
    };

    if(commands.count(argv[1]) > 0)
    {
        cout << "good to go!" << endl;
        if(std::string(argv[1]) == "add")
        {
            cout << "add found" << endl;
        }
    }
    else
    {
        cout << "Error: Invalid command." << endl;
        usage(argv[0]);
        return -1;
    }

    return 0;
}
