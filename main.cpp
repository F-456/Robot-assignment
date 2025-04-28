/**********|**********|**********|
Program: YOUR_FILENAME.cpp / YOUR_FILENAME.h
Course: Data Structures and Algorithms
Trimester: 2410
Name: Frank Carrano
ID: 1071001234
Lecture Section: TC101
Tutorial Section: TT1L
Email: abc123@yourmail.com
Phone: 018-1234567
**********|**********|**********/
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
#include "function.h"

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