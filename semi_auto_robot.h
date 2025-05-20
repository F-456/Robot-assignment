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

#ifndef SEMI_AUTO_ROBOT_H
#define SEMI_AUTO_ROBOT_H

#include "robot.h"
#include "reentry.h"
#include <fstream>
#include <random>
#include <chrono>

class SemiAutoBot : public ShootingRobot
{
private:
    string robotName;
    int x;
    int y;
    int killCount;
    int lives;
    bool fired;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;

public:
    SemiAutoBot(const string &name, int xPos, int yPos) : robotName(name), x(xPos), y(yPos), killCount(0), lives(3), fired(false),
                                                          rng(std::chrono::system_clock::now().time_since_epoch().count()),
                                                          dist(0.0, 1.0) {}

    string getType() const override
    {
        return "S";
    }

    string getRobotName() const override
    {
        return robotName;
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

    void increaseKillCount(Grid &grid) override
    {
        ++killCount;
    }

    int getLives() const override
    {
        return lives;
    }

    void decreaseLives(Grid &grid, ReentryQueue &reentryQueue, ofstream &outputFile) override
    {
        if (lives > 0)
        {
            --lives;
            if (lives > 0)
            {
                reentryQueue.queue(this);
                grid.at(x, y) = nullptr;
                cout << robotName << " lost a life and will re-enter battlefield. lives left: " << lives << endl;
                outputFile << robotName << " lost a life and will re-enter battlefield. lives left: " << lives << endl;
            }
            else
            {
                cout << robotName << " has no lives left and is permanently destroyed." << endl;
                outputFile << robotName << " has no lives left and is permanently destroyed." << endl;
            }
        }
    }

    void increaseLives(Grid &grid) override
    {
        if (lives < 3)
        {
            lives = 3;
        }
    }

    bool isAlive() const override
    {
        return lives > 0;
    }

    void fire(Grid &grid, ReentryQueue &reentryQueue, ofstream &outputFile) override
    {
        if (fired)
            return;

        static const int directions[8][2] = {
            {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

        bool hitAny = false;

        // Check adjacent positions (Manhattan distance = 1)
        for (int i = 0; i < 8; ++i)
        {
            int fireX = x + directions[i][0];
            int fireY = y + directions[i][1];

            if (!grid.isValidPosition(fireX, fireY))
                continue;

            Robot *target = grid.at(fireX, fireY);
            if (target == nullptr)
                continue;

            cout << robotName << " (S) firing 3 shots at (" << fireX << ", " << fireY << ")" << endl;
            outputFile << robotName << " (S) firing 3 shots at (" << fireX << ", " << fireY << ")" << endl;
            hitAny = true;

            // Fire 3 shots with 70% hit probability each
            for (int shot = 1; shot <= 3; ++shot)
            {
                if (dist(rng) <= 0.7)
                { // 70% chance to hit
                    cout << "  Shot " << shot << ": HIT!" << endl;
                    outputFile << "  Shot " << shot << ": HIT!" << endl;

                    target->decreaseLives(grid, reentryQueue, outputFile);
                    increaseKillCount(grid);

                    if (!target->isAlive())
                    {
                        grid.at(fireX, fireY) = nullptr;
                        cout << "Robot " << target->getRobotName() << " (" << target->getType()
                             << ") has been destroyed." << endl;
                        outputFile << "Robot " << target->getRobotName() << " (" << target->getType()
                                   << ") has been destroyed." << endl;
                        break; // Stop shooting if target destroyed
                    }
                }
                else
                {
                    cout << "  Shot " << shot << ": Missed!" << endl;
                    outputFile << "  Shot " << shot << ": Missed!" << endl;
                }
            }
            break; // Only fire at first valid target found
        }

        fired = true;
        if (!hitAny)
        {
            cout << robotName << " (S) fired but found no valid targets." << endl;
            outputFile << robotName << " (S) fired but found no valid targets." << endl;
        }
    }

    bool hasFired() const override
    {
        return fired;
    }

    void setFired(bool fired) override
    {
        this->fired = fired;
    }
};

#endif