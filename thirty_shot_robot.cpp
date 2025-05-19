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

// thirty_shot_bot.cpp
#include "thirty_shot_bot.h"
#include <chrono>
#include <fstream>

ThirtyShotBot::ThirtyShotBot(const std::string &name, int xPos, int yPos)
    : robotName(name), x(xPos), y(yPos), killCount(0), lives(3),
      shellsRemaining(30), // Starts with 30 shells
      rng(std::chrono::system_clock::now().time_since_epoch().count()),
      dist(0.0, 1.0)
{
}

std::string ThirtyShotBot::getType() const { return "T"; }

std::string ThirtyShotBot::getRobotName() const { return robotName; }

int ThirtyShotBot::getX() const { return x; }

int ThirtyShotBot::getY() const { return y; }

int ThirtyShotBot::getKillCount() const { return killCount; }

void ThirtyShotBot::increaseKillCount(Grid &grid) { ++killCount; }

int ThirtyShotBot::getLives() const { return lives; }

void ThirtyShotBot::decreaseLives(Grid &grid, ReentryQueue &reentryQueue, std::ofstream &outputFile)
{
    if (lives > 0)
    {
        --lives;
        if (lives > 0)
        {
            reentryQueue.queue(this);
            grid.at(x, y) = nullptr;
            std::cout << robotName << " lost a life and will re-enter battlefield. lives left: " << lives << std::endl;
            outputFile << robotName << " lost a life and will re-enter battlefield. lives left: " << lives << std::endl;
        }
        else
        {
            std::cout << robotName << " has no lives left and is permanently destroyed." << std::endl;
            outputFile << robotName << " has no lives left and is permanently destroyed." << std::endl;
        }
    }
}

bool ThirtyShotBot::isAlive() const { return lives > 0; }

void ThirtyShotBot::fire(Grid &grid, ReentryQueue &reentryQueue, std::ofstream &outputFile)
{
    if (shellsRemaining <= 0)
    {
        std::cout << robotName << " (T) is out of ammo!" << std::endl;
        outputFile << robotName << " (T) is out of ammo!" << std::endl;
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
            --shellsRemaining; // Use one shell
            hitAny = true;

            std::cout << robotName << " (T) fired at (" << fireX << ", " << fireY
                      << "). Shells remaining: " << shellsRemaining << std::endl;
            outputFile << robotName << " (T) fired at (" << fireX << ", " << fireY
                       << "). Shells remaining: " << shellsRemaining << std::endl;

            // 100% hit chance for ThirtyShotBot
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
}

bool ThirtyShotBot::hasFired() const
{
    // Considered "fired" if out of ammo to prevent infinite tries
    return shellsRemaining <= 0;
}

void ThirtyShotBot::setFired(bool fired)
{
    // No-op since we track ammo instead
}

int ThirtyShotBot::getShellsRemaining() const
{
    return shellsRemaining;
}

void ThirtyShotBot::upgrade(Grid &grid, std::ofstream &outputFile)
{
    if (killCount >= 3)
    {
        // Upgrade logic here
    }
}

void ThirtyShotBot::increaseLives(Grid &grid)
{
    if (lives < 3)
    {
        lives = 3;
    }
    // Consider refilling ammo when lives are restored
    shellsRemaining = 30;
}