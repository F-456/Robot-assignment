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

#ifndef ROBOT_H
#define ROBOT_H

#include <iostream>
#include <string>
using namespace std;
class Robot
{
private:
    int posX, posY;
    int lives;
    string name;

public:
    string file_name = "Robot_config.cfg";
    string config_info = "";
    // Robot_move(string name, int x, int y);
    void move(int dx, int dy);
    void displayStatus() const;
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
#endif
