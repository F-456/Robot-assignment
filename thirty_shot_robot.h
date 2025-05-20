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

#ifndef THIRTY_SHOT_ROBOT_H
#define THIRTY_SHOT_ROBOT_H

#include "robot.h"
#include "reentry.h"
#include <chrono>
#include <random>
#include <fstream>

class ThirtyShotBot : public ShootingRobot
{
private:
    std::string robotName;
    int x;
    int y;
    int killCount;
    int lives;
    int shellsRemaining;
    bool fired;
    std::mt19937 rng;
    std::uniform_real_distribution<double> dist;

public:
    ThirtyShotBot(const std::string &name, int xPos, int yPos)
        : robotName(name), x(xPos), y(yPos), killCount(0), lives(3), shellsRemaining(30),
          rng(std::chrono::system_clock::now().time_since_epoch().count()),
          dist(0.0, 1.0) {}

    std::string getType() const override { return "T"; }
    std::string getRobotName() const override { return robotName; }
    int getX() const override { return x; }
    int getY() const override { return y; }
    int getKillCount() const override { return killCount; }
    void increaseKillCount(Grid &grid) override { ++killCount; }
    int getLives() const override { return lives; }

    void decreaseLives(Grid &grid, ReentryQueue &reentryQueue, std::ofstream &outputFile) override
    {
        if (lives > 0)
        {
            --lives;
            if (lives > 0)
            {
                reentryQueue.queue(this);
                grid.at(x, y) = nullptr;
                std::cout << robotName << " lost a life and will re-enter battlefield. Lives left: " << lives << std::endl;
                outputFile << robotName << " lost a life and will re-enter battlefield. Lives left: " << lives << std::endl;
            }
            else
            {
                std::cout << robotName << " has no lives left and is permanently destroyed." << std::endl;
                outputFile << robotName << " has no lives left and is permanently destroyed." << std::endl;
            }
        }
    }

    void increaseLives(Grid &grid) override
    {
        if (lives < 3)
        {
            lives = 3;
        }
        shellsRemaining = 30; // Refill ammo when lives are restored
        std::cout << robotName << " (T) lives restored to 3 and ammo refilled to 30 shells." << std::endl;
    }

    bool isAlive() const override { return lives > 0; }

    void fire(Grid &grid, ReentryQueue &reentryQueue, std::ofstream &outputFile) override
    {
        if (shellsRemaining <= 0)
        {
            std::cout << robotName << " (T) is out of ammo!" << std::endl;
            outputFile << robotName << " (T) is out of ammo!" << std::endl;
            fired = true;
            return;
        }

        static const int directions[8][2] = {
            {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};

        bool hitAny = false;

        // Fire at first valid adjacent target
        for (int i = 0; i < 8; ++i)
        {
            int fireX = x + directions[i][0];
            int fireY = y + directions[i][1];

            if (!grid.isValidPosition(fireX, fireY))
                continue;

            Robot *target = grid.at(fireX, fireY);
            if (target != nullptr)
            {
                --shellsRemaining;
                hitAny = true;

                std::cout << robotName << " (T) fired at (" << fireX << ", " << fireY
                          << "). Shells remaining: " << shellsRemaining << std::endl;
                outputFile << robotName << " (T) fired at (" << fireX << ", " << fireY
                           << "). Shells remaining: " << shellsRemaining << std::endl;

                // 100% hit chance
                target->decreaseLives(grid, reentryQueue, outputFile);
                increaseKillCount(grid);

                if (!target->isAlive())
                {
                    grid.at(fireX, fireY) = nullptr;
                    std::cout << "Robot " << target->getRobotName() << " (" << target->getType()
                              << ") has been destroyed." << std::endl;
                    outputFile << "Robot " << target->getRobotName() << " (" << target->getType()
                               << ") has been destroyed." << std::endl;
                }
                break;
            }
        }

        if (!hitAny)
        {
            std::cout << robotName << " (T) found no valid targets. Shells remaining: "
                      << shellsRemaining << std::endl;
            outputFile << robotName << " (T) found no valid targets. Shells remaining: "
                       << shellsRemaining << std::endl;
        }
        fired = true;
    }

    bool hasFired() const override
    {
        return fired || shellsRemaining <= 0;
    }

    void setFired(bool fired) override
    {
        this->fired = fired;
    }

    // Additional helper function
    int getShellsRemaining() const { return shellsRemaining; }
};

#endif