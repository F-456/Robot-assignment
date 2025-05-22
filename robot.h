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

// Forward declaration only for ReentryQueue
class Frame;
class ReentryQueue;

class Robot
{
protected:
    string name;
    int x = 0, y = 0;
    int killCount = 0;
    int lives = 3;

public:
    virtual ~Robot() {}
    virtual string getType() const { return "Generic"; }
    virtual string getRobotName() const { return name; }
    virtual int getX() const { return x; }
    virtual int getY() const { return y; }
    virtual int getKillCount() const { return killCount; }
    virtual void increaseKillCount() { killCount++; }
    virtual int getLives() const { return lives; }
    virtual void decreaseLives(ReentryQueue &reentryQueue, ofstream &outputFile)
    {
        lives--;
        outputFile << name << " lost a life! Remaining lives: " << lives << endl;
    }
    virtual bool isAlive() const { return lives > 0; }
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
    virtual void fire(ReentryQueue &reentryQueue, ofstream &outputFile)
    {
        // Default behavior: log firing
        outputFile << name << " fired a basic shot!" << endl;
        fired = true;
    }

    virtual bool hasFired() const
    {
        return fired;
    }

    virtual void setFired(bool f)
    {
        fired = f;
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
