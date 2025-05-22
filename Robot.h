/**********|**********|**********|
Program: robot.h
Course: Data Structures and Algorithms
Trimester: 2410
Name: Frank Carrano
ID: 1071001234
Lecture Section: TC101
Tutorial Section: TT1L
Email: abc123@yourmail.com
Phone: 018-1234567
**********|**********|**********/

#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

class Robot // abstract base class
            // doesn't exist until to be derived
{

public:
    int turn = 0;
    int random_number = 0;
    virtual void think(string robot_name) const = 0;
    virtual void move(string robot_name, int x, int y) const = 0;
    virtual void shoot(string robot_name) const = 0;
    virtual void see(string robot_name) const = 0;
    virtual ~Robot() {}; // virtual destructor
};
class ThinkingRobot : public Robot
{
public:
    virtual void think(string robot_name) const
    {
        cout << robot_name << " is thinking what to do next" << endl;
    }
    virtual void move(string robot_name, int x, int y) const {};
    virtual void shoot(string robot_name) const {};
    virtual void see(string robot_name) const {};
};

class MovingRobot : public Robot
{

public:
    virtual void move(string robot_name, int x, int y) const
    {
        cout << robot_name << " is moving now" << endl;
    }
    virtual void think(string robot_name) const {};
    virtual void shoot(string robot_name) const {};
    virtual void see(string robot_name) const {};
};

class ShootingRobot : public Robot
{

public:
    virtual void shoot(string robot_name) const
    {
        cout << robot_name << " is shooting " << endl;
    }
    virtual void move(string robot_name, int x, int y) const {};
    virtual void think(string robot_name) const {};
    virtual void see(string robot_name) const {};
};

class SeeingRobot : public Robot
{
public:
    virtual void see(string robot_name) const
    {
        cout << robot_name << " is seeing now " << endl;
    }
    virtual void move(string robot_name, int x, int y) const {};
    virtual void shoot(string robot_name) const {};
    virtual void think(string robot_name) const {};
};

// multiple inheritance of a robot type to do all the action
class GenericBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{

public:
};
class HideBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
};
class JumpBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
};
class LongShotBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
};
class SemiAutoBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
};
class ThirtyShotBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
};
class ScoutBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
};

class TrackBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
};