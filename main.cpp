#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "robot.h"
#include "Frame.h"

using namespace std;

int main()
{

    string file_name = "Robot_config.cfg";
    display_class display;

    display.reading_from_file(file_name);
    display.debug();
    display.frame_loop();
    // for debug purposes only
    display.check_robot_data();

    srand(static_cast<unsigned>(time(0)));

    return 0;
}