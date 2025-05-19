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
#include <fstream>
#include "frame.h"

// forward dec for Grid and ReentryQueue
class Grid;
class ReentryQueue;

using namespace std;

class Robot
{
public:
    virtual ~Robot() {}
    virtual string getType() const = 0;
    virtual string getRobotName() const = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getKillCount() const = 0;
    virtual void increaseKillCount(Grid &grid) = 0;
    virtual int getLives() const = 0;
    virtual void decreaseLives(Grid &grid, ReentryQueue &reentryQueue, ofstream &outputFile) = 0;
    virtual bool isAlive() const = 0;
    virtual void upgrade(Grid &grid, ofstream &outputFile) = 0;
    virtual void increaseLives(Grid &grid) = 0;
};

class MovingRobot : virtual public Robot
{
public:
    virtual void move(Grid &grid, ofstream &outputFile) = 0;
    virtual void setPosition(int newX, int newY) = 0;
    virtual bool hasMoved() const = 0;
    virtual void setMoved(bool moved) = 0;
};

class ShootingRobot : virtual public Robot
{
public:
    virtual void fire(Grid &grid, ReentryQueue &reentryQueue, ofstream &outputFile) = 0;
    virtual bool hasFired() const = 0;
    virtual void setFired(bool fired) = 0;
};

class SeeingRobot : virtual public Robot
{
public:
    virtual void look(Grid &grid, int &targetX, int &targetY, bool &targetFound) = 0;
};

#endif
