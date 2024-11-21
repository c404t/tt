#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <unordered_set>

#include <nlohmann/json.hpp>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

using std::fstream;

using std::exception;
using std::string;
using std::getenv;
using std::setw;

using nlohmann::json;

    void
usage(char* argv)
{
    cout << "Usage: " 
        << "(add | remove | update) <task> " << endl
        << "       (list | listw | listd) <id> " << endl
        << "       (markd | markw) <id> " << endl
        << "       (clear | reset) " << endl;
}

    string
home()
{
    char* home = getenv("HOME");
    return home ? string(home) : "";
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

    std::unordered_set<string> commands =
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
        const string path = home() + "/tasktracker/tasks.json";

        //add

        if(string(argv[1]) == "add")
        {
            if(argc == 3) 
            {
                fstream file;

                file.open(path, 
                        std::ios_base::in |
                        std::ios_base::out | 
                        std::ios_base::app);

                json data = json::parse(file);
                
                json new_task;
                new_task["id"] = 3;
                new_task["description"] = string(argv[2]);
                new_task["status"] = "todo";
                new_task["created"] = "";
                new_task["updated"] = "";

                if(file.is_open())
                {
                    try
                    {
                        file << data["tasks"].emplace_back(new_task); 
                        file << data.dump(4);
                        file.close();
                        cout << "New task was added successfully!" << endl;
                    }
                    catch (const exception& e)
                    {
                        cout << "Error writting data to: "
                            << path << endl;
                        cout << e.what() << endl;
                    }
                }
                else
                {
                    cerr << "Unable to open tasks data at " 
                        << path << endl;
                    return -1;
                }
            }
            else
            {
                cerr << "add takes exactly one argument but "
                    << (argc - 2)
                    << " was provided." << endl;

                return -1;
            }
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
