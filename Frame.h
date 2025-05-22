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
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Robot.h"
using namespace std;

MovingRobot Robot;
class Frame
{
private:
    int current_line = 0;
    int size_line = 1;
    int step_line = 2;
    int robots_numbers_line = 3;

public:
    int step = 5;
    int x_value = 0;
    int y_value = 0;
    int robot_numbers = 0;
    int Row_number = 0, Column_number = 0;

    vector<string> robot_namelist, robot_genre; // two vector to store the robot namelist and the robot genre
    vector<int> robot_x_pos, robot_y_pos;

    void reading_from_file(string file_name)
    {
        string information;
        ifstream file_in;
        file_in.open(file_name);

        if (!file_in.is_open())
        {
            cout << "file opening error please check your file name again" << endl;
        }

        while (getline(file_in, information)) // while getting line read the information from the config file into the program
        {

            current_line++;
            if (current_line == size_line)
            {
                read_size_information(information);
            }
            else if (current_line == step_line)
            {
                read_step(information);
            }
            else if (current_line == robots_numbers_line)
            {
                read_robot_numbers(information);
            }
            else
            {
                read_robot_info(information);
            }
        }
    }

    void read_size_information(string s)
    {
        stringstream ss;
        ss << s;
        string temp;
        int loop_times = 0;

        int found;
        while (!ss.eof()) // make sure the string stream doesn't read beyond the the data
        {
            ss >> temp;
            if (stringstream(temp) >> found)
            {
                if (loop_times == 1) // using loop times to decide whether it's the first integer to read or second
                                     // use to determine x and y axis
                {
                    Column_number = found;
                    // cout << "Column number = " << Column_number << endl;
                }
                else
                {
                    Row_number = found;
                    // cout << "Row number = " << Row_number << endl;
                }
                loop_times++;
            }

            temp = "";
        }
    };

    void read_step(string s)
    {
        stringstream ss;
        ss << s;
        string temp;
        int found;
        while (!ss.eof())
        {
            ss >> temp;
            if (stringstream(temp) >> found)
            {
                step = found;
                cout << "Steps = " << step << endl;
            }
        }
    }

    void read_robot_numbers(string s)
    {
        stringstream ss;
        ss << s;
        string temp;
        int found;
        while (!ss.eof())
        {
            ss >> temp;
            if (stringstream(temp) >> found)
            {
                robot_numbers = found;
                cout << "Robot numbers = " << robot_numbers << endl;
            }
        }
    }

    void read_robot_info(string s)
    {
        stringstream ss;
        ss << s;
        string temp;
        vector<string> temps;
        while (!ss.eof())
        {
            ss >> temp;
            temps.push_back(temp);
        }
        // debug loop for the vector string
        // necessary for iterate througha a string vector
        for (int i = 0; i < temps.size(); i++)
        {
            cout << temps[i] << endl;
            if (i == 0)
            {
                robot_genre.push_back(temps[i]);
            }
            else if (i == 1)
            {
                robot_namelist.push_back(temps[i]);
            }
            else if (i == 2)
            {
                int temp2 = stoi(temps[i]); // converting string into i to be push back
                robot_x_pos.push_back(temp2);
            }
            else
            {
                int temp2 = stoi(temps[i]);
                robot_y_pos.push_back(temp2);
            }
            // cout << "loop" << i << endl;
        }
    }

    void check_robot_data() // debug functionf for checking the program data including all the robot info
    {
        for (int i = 0; i < robot_numbers; i++)
        {
            cout << "robot type = " << robot_genre[i] << ", ";
            cout << "robot name = " << robot_namelist[i] << ", ";
            cout << "robot x position = " << robot_x_pos[i] << ", ";
            cout << "robot y position = " << robot_y_pos[i] << " " << endl;
        }
    }

    void debug()
    {
        cout << "debugging " << endl;
        cout << Column_number << Row_number << endl;
    }
};

class display_class : public Frame // derived display class from the frame
{
public:
    void frame_loop() // main frame loop for the program
    {
        for (int i = 0; i < step; i++)
        {
            for (int x = 0; x < robot_numbers + 1; x++)
            {
                cout << " now is " << x << " turns" << endl;
                cout << "Press Enter to Continue";
                cin.ignore();
                if (x == 1)
                {
                    Robot.move(robot_x_pos[x - 1], robot_y_pos[x - 1], Column_number, Row_number);
                    cout << "Robot now are " << robot_x_pos[x - 1] << "and" << robot_x_pos[x] << endl;
                }
                y_value = 0;
            }
            cout << "Remaining step = :" << step << endl;
            displayBattlefield();
        };
    }
    void displayBattlefield()
    {
        int row = Row_number;
        int column = Column_number;

        cout << "row" << row << endl;
        for (int y = 0; y <= column * 2; ++y)
        {
            if (y % 2 != 0)
            {
                y_value++;
                x_value = 0; // resetting x value in each row
            }

            for (int x = 0; x <= row * 2; ++x)
            {

                if (y == 0 && x % 2 != 0)
                {
                    cout << " " << (x / 2) + 1 << " ";
                }
                else if (y % 2 == 0) // if the y axis is even nujmber
                {
                    if (x % 2 == 0 && y != 0)
                        cout << "+";
                    else if (y != 0)
                    {
                        cout << "--";
                    }
                }
                else // if the y axis is odd number
                {
                    if (x % 2 == 0)
                    {
                        if (x == 0)
                            cout << y_value;

                        else
                        {
                            cout << "|";
                            x_value++;
                            // cout << " x_value = " << x_value;
                        }
                    }

                    else
                        check_robot_position();
                }
            }
            cout << endl;
        }
    }

    void check_robot_position() // function to check if the robot is in the slot
    {
        if (check_robot_y())
        {
        }
        else
            cout << "  "; // a slot for holding the robot places
    }
    bool check_robot_y()
    {
        for (int i = 0; i < Row_number; i++)
        {
            if (y_value == robot_y_pos[i])
            {
                check_robot_x(i);
            }
        }
        return false;
    }
    bool check_robot_x(int i) // passing the i value from the previous function as a parameter
                              //  for faster navigating and more straight forward solution
    {
        if (robot_x_pos[i] - 1 == x_value) // a robot is found on the position
        {
            x_value++;
            print_robot_name(i);
            return true;
        }
        return false;
    }

    void print_robot_name(int i)
    {
        cout << robot_namelist[i];
    }
};