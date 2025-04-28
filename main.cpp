#include <iostream>
#include <fstream>
#include <sstream>
#include "function.h"

using namespace std;

int main()
{
    system("cd");
    string information;
    Robot Obj;
    ifstream file_in;
    ofstream file_out("example");
    file_in.open(Obj.file_name);

    if (!file_in.is_open())
    {
        cout << "file opening error please check your file name again" << endl;
    }
    else
        cout << "config file opened" << endl;

    while (getline(file_in, information))
    {
        cout << information;
    }

    file_in.close();
    return 0;
}