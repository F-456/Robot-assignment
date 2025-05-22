#include <iostream>
#include <fstream>
#include <sstream>
#include "Frame.h"

using namespace std;

int main()
{

    string file_name = "Robot_config.cfg";
    display_class display;

    display.reading_from_file(file_name);
    // display.debug();
    display.value_initialize(); // initializing all the required data for the robot

    // main loop for the program
    display.frame_loop();
    // for debug purposes only
    // obj.check_robot_data();

    return 0;
}