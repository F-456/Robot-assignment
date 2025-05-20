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

#ifndef TRACK_ROBOT_H
#define TRACK_ROBOT_H

#include "robot.h"
#include "reentry.h"

class TrackBot : public SeeingRobot
{
private:
    string robotName;
    int x;
    int y;
    int killCount;
    int lives;
    bool fired;

public:
    TrackBot(const string &name, int xPos, int yPos);

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
    void look(Grid &grid, int &targetX, int &targetY, bool &targetFound) override;
};

#endif