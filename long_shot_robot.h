#ifndef LONG_SHOT_ROBOT_H
#define LONG_SHOT_ROBOT_H

#include "robot.h"
#include "reentry_queue.h"
#include <string>
#include <fstream>
using namespace std;

class LongShotBot : public ShootingRobot
{
private:
    string name;
    int x, y;
    int killCount;
    int lives;
    bool fired;

public:
    LongShotBot(string name, int x, int y)
        : name(name), x(x), y(y), killCount(0), lives(3), fired(false) {}

    string getType() const override
    {
        return "LongShotBot";
    }

    string getRobotName() const override
    {
        return name;
    }

    int getX() const override
    {
        return x;
    }

    int getY() const override
    {
        return y;
    }

    int getKillCount() const override
    {
        return killCount;
    }

    void increaseKillCount() override
    {
        killCount++;
    }

    int getLives() const override
    {
        return lives;
    }

    void increaseLives() override
    {
        lives++;
    }

    void decreaseLives(ReentryQueue &reentryQueue, ofstream &outputFile) override
    {
        lives--;
        outputFile << name << " lost a life! Remaining lives: " << lives << endl;
        if (lives > 0)
        {
            reentryQueue.queue(this); // this is now valid since we inherit Robot
        }
    }

    bool isAlive() const override
    {
        return lives > 0;
    }

    void fire(ReentryQueue &reentryQueue, ofstream &outputFile) override
    {
        fired = true;
        outputFile << name << " fired a long-range shot!" << endl;
    }

    bool hasFired() const override
    {
        return fired;
    }

    void setFired(bool f) override
    {
        fired = f;
    }
};

#endif
