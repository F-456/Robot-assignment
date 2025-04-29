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
    int robots_line = 3;

public:
    int step = 5;
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
            cout << information << endl;
            if (current_line == size_line)
            {
                read_size_information(information);
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
                if (loop_times == 1)
                {
                    cout << "Y-axis = " << found << endl;
                    Y_axis = found;
                    cout << Y_axis << endl;
                }
                else
                {

                    cout << "X-axis = " << found << endl;
                    X_axis = found;
                    cout << X_axis << endl;
                }
                loop_times++;
            }

            temp = "";
        }
    };

    void frame_loop()
    {
        for (int i = 0; i < step; i++)
        {
            cout << "Remaining step = :" << step << endl;
            displayBattlefield(10, 10);
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