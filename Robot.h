/**********|**********|**********|
Program: robot.h
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
#include <fstream>

using namespace std;

class Robot
{
public:
    void Random_action()
    {
    }
};
class ThinkingRobot : public Robot
{
public:
    void Thinking()
    {
    }
};

class MovingRobot : public Robot
{
protected:
    bool moved = false;

public:
    void move(int &x, int &y, int maxX, int maxY)
    {
        int direction = rand() % 4; // 0: up, 1: down, 2: left, 3: right
        cout << "Random direction = " << direction << endl;

        switch (direction)
        {
        case 0:
            cout << "Moving up\n";
            if (y > 0)
                y--;
            break;
        case 1:
            cout << "Moving down\n";
            if (y < maxY - 1)
                y++;
            break;
        case 2:
            cout << "Moving left\n";
            if (x > 0)
                x--;
            break;
        case 3:
            cout << "Moving right\n";
            if (x < maxX - 1)
                x++;
            break;
        }
    }
};

class ShootingRobot : public Robot
{
protected:
    bool fired = false;

public:
    virtual void fire()
    {
    }

    virtual bool hasFired()
    {
        return fired;
    }
};

class SeeingRobot : public Robot
{
public:
    virtual void look(int &targetX, int &targetY, bool &targetFound)
    {
        // Default behavior: no target found
        targetFound = false;
        targetX = -1;
        targetY = -1;
    }
};

#endif