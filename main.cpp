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

void diaplayBattlefield(int row, int column){
    for(int i = 0; i<= row * 2; ++i){
        for(int j = 0; j<= column * 2; ++j){
            if (i % 2 == 0){
                if (j % 2 == 0) cout << "+";
                else cout << "---";
            }
            else{
                if (j % 2 == 0) cout << "|";
                else cout << "   ";
                }
        }
        cout << endl;
    }
}

class Robot
{
private:
public:
    string file_name = "Robot_config.cfg";
    string config_info = "";
};

class movingRobot : public Robot
{
};

class shootingRobot : public Robot
{
};

class SeeingRobot : public Robot
{
};
class ThinkingRobot : public Robot
{
};
int main()
{
    system("cd");
    string information;
    Robot Obj;
    ifstream file_in;
    ofstream file_out("example");
    file_in.open(Obj.file_name);

    int m = 80;
    int n = 50;

    diaplayBattlefield(m,n);

    if (!file_in.is_open())
    {
        cout << "file opening error please check your file name again" << endl;
    }
    else
        cout << "config file opened" << endl;

    while (getline(file_in, information))
    {
        cout << information << endl;
    }

    file_in.close();
    return 0;
}
