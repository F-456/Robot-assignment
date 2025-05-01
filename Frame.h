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
#include "Robot function.h"
using namespace std;

class Frame
{
private:
    int current_line = 0;
    int size_line = 1;
    int step_line = 2;
    int robots_numbers_line = 3;

public:
    int step = 5;
    int robot_numbers = 0;
    int Y_axis, X_axis = 0;
    Robot Obj;

    void reading_from_file(string file_name)
    {
        string information;
        ifstream file_in;
        file_in.open(file_name);

        if (!file_in.is_open())
        {
            cout << "file opening error please check your file name again" << endl;
        }

        while (getline(file_in, information))
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
                    Y_axis = found;
                    cout << "Y-axis = " << Y_axis << endl;
                }
                else
                {
                    X_axis = found;
                    cout << "X-axis = " << X_axis << endl;
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

    void frame_loop()
    {
        for (int i = 0; i < step; i++)
        {
            cout << "Remaining step = :" << step << endl;
            displayBattlefield(X_axis, Y_axis);
        };
    }
    void displayBattlefield(int row, int column)
    {

        for (int i = 0; i <= row * 2; ++i)
        {
            for (int j = 0; j <= column * 2; ++j)
            {
                if (i % 2 == 0)
                {
                    if (j % 2 == 0)
                        cout << "+";
                    else
                        cout << "--";
                }
                else
                {
                    if (j % 2 == 0)
                        cout << "|";
                    else
                        cout << "  ";
                }
            }
            cout << endl;
        }
    }
};