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

    for(auto it = data["tasks"].begin(); it != data["tasks"].end(); ++it)
    {
        cout << it["id"] << endl;
        if(it["id"] == argv[1])
        {
            cout << "wow";
        }
    }

    return 0;
}
