#include <iostream>
#include <fstream>
#include <sstream>
#include "Frame.h"

using namespace std;

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

<<<<<<< HEAD
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
=======
    string file_name = "Robot_config.cfg";
    display_class display;

    display.reading_from_file(file_name);
    // display.debug();
    display.value_initialize(); // initializing all the required data for the robot
    display.fetching_data();    // fetch data to the robot.h file
    // main loop for the program
    display.frame_loop();
    // for debug purposes only
    // display.check_robot_data();
>>>>>>> main

    return 0;
}
