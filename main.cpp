
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

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

    if (!file_in.is_open())
    {
        cout << "file opening error please check your file name again" << endl;
    }

    while (getline(file_in, information))
    {
        cout << information;
    }

    file_in.close();
    return 0;
}