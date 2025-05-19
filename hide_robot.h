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

#ifndef HIDE_ROBOT_H
#define HIDE_ROBOT_H

#include "robot.h"
#include "frame.h"
#include "reentry.h"

class HideBot : public MovingRobot
{
private:
    string robotName;
    int x;
    int y;
    int killCount;
    int lives;
    bool moved;
    bool fired;

public:
    HideBot(const string &name, int xPos, int yPos);

    string getType() const override;
    string getRobotName() const override;
    int getX() const override;
    int getY() const override;
    int getKillCount() const override;
    void increaseKillCount(Grid &grid) override;
    int getLives() const override;
    void decreaseLives(Grid &grid, ReentryQueue &reentryQueue, ofstream &outputFile) override;
    void increaseLives(Grid &grid) override;
    bool isAlive() const override;
    void fire(Grid &grid, ReentryQueue &reentryQueue, ofstream &outputFile) override;
    bool hasFired() const override;
    void setFired(bool fired) override;
    void setPosition(int newX, int newY) override;
    bool hasMoved() const override;
    void setMoved(bool moved) override;
};

#endif