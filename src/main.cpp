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

using std::ofstream;
using std::ifstream;

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
                json data;
                ifstream read_file;
                read_file.open(path);

                if(read_file)
                {
                    try
                    {
                        data = json::parse(read_file); 
                    }
                    catch(const exception& e)
                    {

                        cout << "Error parsing data at: " 
                            << path << endl;

                        return -1;
                    }
                }
                else 
                {
                    cerr << "Unable to open tasks data at " 
                        << path << endl;

                    return -1;
                }

                cout << data["tasks"];

                json new_task;
                new_task["id"] = 3;
                new_task["description"] = string(argv[2]);
                new_task["status"] = "todo";
                new_task["created"] = "";
                new_task["updated"] = "";


                ofstream write_file;
                write_file.open(path, ofstream::trunc);

                if(write_file)
                {
                    if(!data["tasks"].is_null())
                    {
                        try
                        {
                            data["tasks"].push_back(new_task); 
                            write_file << data.dump(4);
                            write_file.close();
                            cout << "New task was added successfully!" << endl;
                        }
                        catch (const exception& e)
                        {
                            cerr << "Error writting data to: "
                                << path << endl;
                            cerr << e.what() << endl;

                            return -1;
                        }
                    }
                    else
                    {
                        cerr << "There was something wrong with tasks data. " << endl 
                            << "You can either try correcting the file at "
                            << path
                            << " (not recommended) " << endl
                            << "or regenerating tasks data using "
                            << argv[0]
                            << " reset";

                        return -1;
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
        cerr << "Error: Invalid command." << endl;
        usage(argv[0]);
        return -1;
    }

    return 0;
}
