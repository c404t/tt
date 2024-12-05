#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <unordered_set>
#include <ctime>
#include <sstream>
#include <vector>
#include <random>

#include <nlohmann/json.hpp>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::count;

using std::ofstream;
using std::ifstream;
using std::istringstream;
using std::vector;
using std::unordered_set;

using std::exception;
using std::string;
using std::getenv;
using std::setw;

using nlohmann::json;

void usage(char* argv)
{
    cout << "Usage: " 
        << "(add <task> " << endl
        << "       (remove) <id> " << endl
        << "       (update) <id> \"new tasks description\"" << endl
        << "       (list | listw | listd) <id> " << endl
        << "       (markd | markw) <id> " << endl
        << "       (clear) " << endl;
}

string home()
{
    char* home = getenv("HOME");
    return home ? string(home) : "";
}

int gen_id(const json& data)
{
    if (!data.contains("tasks") || !data["tasks"].is_array())
    {
        cerr << "There was something wrong with tasks data. " << endl;

        return -1;
    }

    unordered_set<int> ids;

    for(const auto& it : data["tasks"])
    {
        try
        {
            if (it.contains("id") && it["id"].is_number_integer()) 
            {
                ids.insert(it["id"].get<int>());
            } 
            else 
            {
                std::cerr << "Warning: Task element missing 'id' key or 'id' is not an integer." << std::endl;
            }
        }
        catch(const exception& e)
        {
            cerr << "Error: " << e.what() << endl;

            return -1;
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1000, 9999);

    int id;
    do
    {
        id = distrib(gen);
    }
    while(ids.count(id));

    return id;
}

int add(int argc, char* argv[], const string path, string time)
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

        json new_task;
        new_task["id"] = gen_id(data);
        new_task["description"] = string(argv[2]);
        new_task["status"] = "todo";
        new_task["created"] = time;
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
                    cout << "New task was added successfully!" << endl
                        << "Task id: "
                        << new_task["id"]
                        << endl;

                    return 0;
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

int remove(int argc, char* argv[], const string path)
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

        bool removed = false;

        for(auto task = data["tasks"].begin(); task != data["tasks"].end(); )
        {
            if(task->contains("id") && task->at("id") == atoi(argv[2]))
            {
                try
                {
                    task = data["tasks"].erase(task);
                    removed = true;
                    cout << "Task was removed successfully!" << endl;
                    break;
                }
                catch(const exception& e)
                {
                    cerr << "Something went wrong!" << endl;

                    return -1;
                }
            }
            else
            {
                ++task;
            }
        }

        if(!removed)
        {
            cerr << "Could not remove task with provided id!" << endl
                << "The id you provided is likely not a valid id or integer."
                << endl;

            return -1;
        }

        ofstream write_file;
        write_file.open(path, ofstream::trunc);

        if(write_file)
        {
            if(!data["tasks"].is_null())
            {
                try
                {
                    write_file << data.dump(4);
                    write_file.close();

                    return 0;
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

int markdw(int argc, char* argv[], const string path, string time)
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

        bool updated = false;

        for(auto task = data["tasks"].begin(); task != data["tasks"].end(); )
        {
            if(task->contains("id") && task->at("id") == atoi(argv[2]))
            {
                if(task->contains("status"))
                {
                    if(string(argv[1]) == "markw")
                    {
                        try
                        {
                            cout << "Marking: "<< task->at("description") << endl;
                            task->at("status") = "wip";
                            task->at ("updated") = time;
                            updated = true;
                            cout << "Task was marked as wip!" << endl;
                            break;
                        }
                        catch(const exception& e)
                        {
                            cerr << "Something went wrong!" << endl;

                            return -1;
                        }
                    }
                    if(string(argv[1]) == "markd")
                    {
                        try
                        {
                            cout << "Marking: "<< task->at("description") << endl;
                            task->at("status") = "done";
                            task->at ("updated") = time;
                            updated = true;
                            cout << "Task was marked as done!" << endl;
                            break;
                        }
                        catch(const exception& e)
                        {
                            cerr << "Something went wrong!" << endl;

                            return -1;
                        }

                    }
                }
                else
                {
                    cerr << "There was something wrong with the tasks data" << endl;

                    return -1;
                }
            }
            else
            {
                ++task;
            }
        }

        if(!updated)
        {
            cerr << "Could not update task with provided id!" << endl
                << "The id you provided is likely not a valid id or integer."
                << endl;

            return -1;
        }

        ofstream write_file;
        write_file.open(path, ofstream::trunc);

        if(write_file)
        {
            if(!data["tasks"].is_null())
            {
                try
                {
                    write_file << data.dump(4);
                    write_file.close();

                    return 0;
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
        cerr << argv[1] << " take exactly 2 argument but "
            << (argc - 2)
            << " was provided." << endl;

        return -1;
    }
}

int update(int argc, char* argv[], const string path, string time)
{
    if(argc == 4) 
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

        bool updated = false;

        for(auto task = data["tasks"].begin(); task != data["tasks"].end(); )
        {
            if(task->contains("id") && task->at("id") == atoi(argv[2]))
            {
                if(task->contains("description"))
                {
                    try
                    {
                        cout << "Updating: "<< task->at("description") << endl;
                        task->at("description") = string(argv[3]);
                        task->at ("updated") = time;
                        updated = true;
                        cout << "Task was updated successfully!" << endl;
                        break;
                    }
                    catch(const exception& e)
                    {
                        cerr << "Something went wrong!" << endl;

                        return -1;
                    }
                }
                else
                {
                    cerr << "There was something wrong with the tasks data" << endl;

                    return -1;
                }
            }
            else
            {
                ++task;
            }
        }

        if(!updated)
        {
            cerr << "Could not update task with provided id!" << endl
                << "The id you provided is likely not a valid id or integer."
                << endl;

            return -1;
        }

        ofstream write_file;
        write_file.open(path, ofstream::trunc);

        if(write_file)
        {
            if(!data["tasks"].is_null())
            {
                try
                {
                    write_file << data.dump(4);
                    write_file.close();

                    return 0;
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
        cerr << "update takes exactly two argument but "
            << (argc - 2)
            << " was provided." << endl;

        return -1;
    }
}

int reset(int argc, char* argv[], const string path)
{
    if(argc == 2) 
    {
        string choice;
        cout << "reset all the tasks? (yes/no) ";
        cin >> choice;

        if(string(choice) == "yes" ||
                string(choice) == "Yes" ||
                string(choice) == "y" ||
                string(choice) == "Y")
        {
            cout << "resetting tasks data at: " 
                << path << endl;
        }
        else
        {
            cout << "no changes were made since last run. " << endl;

            return 0;
        }


        ofstream write_file;
        write_file.open(path, ofstream::trunc);

        if(write_file)
        {
            try
            {
                json data;
                data = {{"tasks", json::array()}};

                write_file << data.dump(4);
                write_file.close();

                return 0;
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
            cerr << "Unable to open tasks data at " 
                << path << endl;

            return -1;
        }
    }
    else
    {
        cerr << "reset takes no argument." << endl;

        return -1;
    }
}

int main(int argc, char* argv[])
{
    //before everything check if file exist or found
    //if not make one and warn the user

    if(argc < 2)
    {
        cerr << "Error: expected more arguments." << endl;
        usage(argv[0]);
        return -1;
    }
    unordered_set<string> commands =
    {
        "add",      //done
        "remove",   //done
        "update",   //done

        "markd",    //done
        "markw",    //done

        "list",
        "listw",
        "listd",

        "reset"
    };

    if(commands.count(argv[1]) > 0)
    {
        std::string cmd = argv[1];
        const string path = home() + "/tasktracker/tasks.json";

        time_t timestamp;
        time(&timestamp);
        string time = ctime(&timestamp);
        time.pop_back();

        if(cmd == "add")
        {
            add(argc, argv, path, time);
        }
        else if(cmd == "remove")
        {
            remove(argc, argv, path);
        }
        else if(cmd == "update")
        {
            update(argc, argv, path, time);
        }
        else if(cmd == "reset")
        {
            reset(argc, argv, path);
        }
        else if(cmd == "markd" || (argv[1]) == "markw")
        {
            markdw(argc, argv, path, time);
        }
        else
        {}
    }
    else
    {
        cerr << "Error: Invalid command." << endl;
        usage(argv[0]);
        return -1;
    }

    return 0;
}
