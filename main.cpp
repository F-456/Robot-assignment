#include <iostream>
#include <fstream>
#include <sstream>
#include "Frame.h"
#include <ctime>

using namespace std;

int main()
{
    srand(time(0));
    string file_name = "Robot_config.cfg";
    display_class display;

    display.reading_from_file(file_name);

    display.value_initialize(); // initializing all the required data for the robot
    display.fetching_data();    // fetch data to the robot.h file
    // display.debug();
    //  main loop for the program
    display.frame_loop();
    // for debug purposes only
    // display.check_robot_data();

    return 0;
}