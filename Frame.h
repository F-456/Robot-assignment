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

class Frame
{

private:
    int current_line = 0;
    int size_line = 1;
    int step_line = 2;
    int robots_numbers_line = 3;

public:
    int step = 0;
    float x_value = 0;
    int y_value = 0;
    int robot_numbers = 0;
    int remaining_step = 0;
    int slot_occupied = 0;
    int Row_number = 0, Column_number = 0;
    int remaining_round = 0;

    vector<string> robot_namelist, robot_genre; // two vector to store the robot namelist and the robot genre
    vector<int> robot_x_pos, robot_y_pos;

    void fetching_data() // fetching data to the robot header file
    {
        cout << "fetching data ... " << endl;
        for (int i = 0; i < robot_numbers; i++)
        {
            robot_fetching_data(Row_number, Column_number, robot_numbers, robot_namelist[i], robot_genre[i], robot_x_pos[i], robot_y_pos[i]);
        }
    }
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
                    Row_number = found;
                    cout << "Row number = " << Row_number << endl;
                }
                else
                {
                    Column_number = found;
                    cout << "Column number = " << Column_number << endl;
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
                remaining_round = found - 1;
                cout << "Steps = " << step << endl;
                remaining_step = found;
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
            // cout << temps[i] << endl;
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
        }
    }

    void check_robot_data() // debug function for checking the program data including all the robot info
    {
        for (int i = 0; i < robot_numbers; i++)
        {
            cout << "robot type = " << robot_genre[i] << ", ";
            cout << "robot name = " << robot_namelist[i] << ", ";
            cout << "robot x position = " << robot_x_pos[i] << ", ";
            cout << "robot y position = " << robot_y_pos[i] << " " << endl;
        }
        robot_data_debug();
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
    void dice(int turn)
    {
        GenericBot normal_robot;
        HideBot hide_robot;

        // int random_number = 4;
        int random_number = (rand() % 4);
        if (robot_genre[turn] == "GenericRobot")
        {
            if (random_number == 0)
            {
                normal_robot.think(turn);
            }
            else if (random_number == 1)
            {
                normal_robot.move(turn, robot_x_pos[turn], robot_y_pos[turn]);
            }
            else if (random_number == 2)
            {
                normal_robot.shoot(turn);
            }
            else
            {
                normal_robot.see(turn);
            }
        }
    }
    void frame_loop() // main frame loop for the program
    {

        displayBattlefield();
        for (int i = 0; i < step; i++)
        {
            for (int x = 0; x < robot_numbers; x++)
            {
                cout << " now is turn " << x << endl
                     << endl;
                cout << "PRESS ENTER TO CONTINUE";
                cin.ignore();
                dice(x);
                y_value = 0;
            }

            remaining_step--;
            cout << "Remaining step = :" << remaining_step << endl;
            displayBattlefield();
            cout << endl;
        };
    }
    void type_checker(int x)
    {
    }
    void value_initialize()
    {
        for (int i = 0; i < robot_numbers; i++)
        {
            // value in robot header
            robot_looked.push_back(0);
            robot_ammo_left.push_back(10);
            robot_lives.push_back(3);
            robot_destroyed.push_back(0);
            robot_upgraded.push_back(0);
            Hidebot.push_back(0);
            Jumpbot.push_back(0);
            long_shot_bot.push_back(0);
            semiauto_bot.push_back(0);
            thirtyshot_bot.push_back(0);
            scoutbot.push_back(0);
            trackbot.push_back(0);
        }

        cout << "data initialize completely " << endl;
    }

    void displayBattlefield()
    {
        int row = Row_number;
        int column = Column_number;

        for (int y = 0; y <= row * 2; ++y)
        {
            if (y % 2 != 0)
            {
                y_value++;
                x_value = 0; // resetting x value in each row
            }

            for (int x = 0; x <= column * 2; ++x)
            {

                if (y == 0 && x % 2 != 0)
                {
                    cout << " " << (x / 2) + 1 << " ";
                }
                else if (y % 2 == 0) // if the y axis is even number
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
                        x_value++;
                        if (x == 0)
                        {
                            cout << y_value;
                        }
                        else
                        {
                            cout << "|";
                            slot_occupied = 0;
                        }
                    }

                    else
                    {
                        check_robot_position();
                    }
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
        else if (slot_occupied == 0) // the slot does not have any robot
            cout << "  ";            // slot for holding the robot places
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
        if (x_value == robot_x_pos[i]) // a robot is found on the position
        {
            slot_occupied = 1;
            print_robot_name(i);

            return true;
        }
        else
        {
            return false;
        }
    }
    void print_robot_name(int i)
    {
        if (robot_namelist[i].length() >= 2) // print only the first two character of the robot name
        {
            cout << robot_namelist[i].substr(0, 2);
        }
    }
};