#include "robot.h"
#include <iostream>

Robot::Robot(std::string name, int x, int y)
    : name(name), posX(x), posY(y), lives(3) {}

void Robot::move(int dx, int dy)
{
    posX += dx;
    posY += dy;
}

void Robot::displayStatus() const
{
    std::cout << "Robot " << name << " at (" << posX << ", " << posY << "), Lives: " << lives << std::endl;
}