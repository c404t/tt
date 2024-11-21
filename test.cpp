#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>

using namespace std;
using nlohmann::json;

int main()
{
    std::string path= "/home/noob/tasktracker/newfile.json";

    std::ifstream ifs(path);
    json data = json::parse("{ \"tasks\" : [] }");

    ifs >> data;

    cout << data["tasks"] << endl;

    json new_task = {{"id", 2}, {"name", "eg"}};

    data["tasks"].push_back(new_task);
    try                                                         
    {                                                           
        std::ofstream file("./newfile.json", ios::trunc);
        file << data.dump(4);
        file.close();                                           
        cout << "New task was added successfully!" << endl;     
    }                                                           
    catch (const exception& e)                                  
    {                                                           
        cout << "Error writting data to!" << endl;
        cout << e.what() << endl;                               
    } 
    return 0;
}
