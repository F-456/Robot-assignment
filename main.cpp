#include <iostream>
#include <fstream>
#include <sstream>
#include "Robot function.h"
#include "Frame.h"

using namespace std;

int main()
{

    string file_name = "Robot_config.cfg";
    Frame obj;
    obj.reading_from_file(file_name);
    obj.frame_loop();
    obj.check_robot_data();

    return 0;
}