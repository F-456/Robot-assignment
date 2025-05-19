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

#include "long_shot_robot.h"
#include <fstream>
using namespace std;

LongShotBot::LongShotBot(const string &name, int xPos, int yPos) : robotName(name), x(xPos), y(yPos), killCount(0), lives(3), fired(false) {}

string LongShotBot::getType() const
{
    return "L";
}

string LongShotBot::getRobotName() const
{
    return robotName;
}

int LongShotBot::getX() const
{
    return x;
}

int LongShotBot::getY() const
{
    return y;
}

int LongShotBot::getKillCount() const
{
    return killCount;
}

void LongShotBot::increaseKillCount(Grid &grid)
{
    ++killCount;
}

int LongShotBot::getLives() const
{
    return lives;
}

void LongShotBot::decreaseLives(Grid &grid, ReentryQueue &reentryQueue, ofstream &outputFile)
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

void LongShotBot::increaseLives(Grid &grid)
{
    if (lives < 3)
    {
        lives = 3;
    }
}

bool LongShotBot::isAlive() const
{
    return lives > 0;
}

void LongShotBot::fire(Grid &grid, ReentryQueue &reentryQueue, ofstream &outputFile)
{
    if (fired)
        return;

    bool hitAny = false;

    // Check all positions within Manhattan distance ≤ 3
    for (int dx = -3; dx <= 3; ++dx)
    {
        int max_dy = 3 - abs(dx); // Optimize dy range based on current dx
        for (int dy = -max_dy; dy <= max_dy; ++dy)
        {
            if (dx == 0 && dy == 0)
                continue; // Skip own position

            int fireX = x + dx;
            int fireY = y + dy;

            if (grid.isValidPosition(fireX, fireY))
            {
                Robot *target = grid.at(fireX, fireY);
                if (target != nullptr)
                {
                    // Log the firing action
                    cout << "Robot " << robotName << " (L) fired at (" << fireX << ", " << fireY << ")" << endl;
                    outputFile << "Robot " << robotName << " (L) fired at (" << fireX << ", " << fireY << ")" << endl;

                    // Handle the hit
                    target->decreaseLives(grid, reentryQueue, outputFile);
                    increaseKillCount(grid);

                    // Check if target was destroyed
                    if (!target->isAlive())
                    {
                        grid.at(fireX, fireY) = nullptr;
                        cout << "Robot " << target->getRobotName() << " (" << target->getType()
                             << ") has been destroyed." << endl;
                        outputFile << "Robot " << target->getRobotName() << " (" << target->getType()
                                   << ") has been destroyed." << endl;
                    }
                    hitAny = true;
                }
            }
        }
    }

    fired = true;
    if (!hitAny)
    {
        cout << robotName << " (L) fired but hit nothing." << endl;
        outputFile << robotName << " (L) fired but hit nothing." << endl;
    }
}
bool LongShotBot::hasFired() const
{
    return fired;
}

void LongShotBot::setFired(bool fired)
{
    this->fired = fired;
}
