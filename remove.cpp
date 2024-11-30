#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace::std;
using nlohmann::json;

int main(int argc, char* argv[])
{
    const string path = "tasks.json";
    json data;
    ifstream read_file;
    read_file.open(path);
    data = json::parse(read_file);
    //cout << data << endl;

    for(auto task = data["tasks"].begin(); task != data["tasks"].end(); )
    {
        if(task->contains("id") && task->at("id") == atoi(argv[1]))
        {
            task = data["tasks"].erase(task);
            cout << "wow" << endl;
            break;
        }
        else
        {
            ++task;
        }
    }

    ofstream write_file;                                                                        
    write_file.open(path, ofstream::trunc);

    write_file << data.dump(4);

    return 0;
}
