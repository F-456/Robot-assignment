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

#include "heart.h"

Heart::Heart(int xPos, int yPos) : x(xPos), y(yPos) {}

int Heart::getX() const
{
    return x;
}

int Heart::getY() const
{
    return y;
}

bool Heart::isAtPosition(int xPos, int yPos) const
{
    return x == xPos && y == yPos;
}
