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
#include <vector>

using namespace std;

int row_number, column_number = 0;
int robot_number = 0;
vector<string> robot_namelist, robot_genre; // two vector to store the robot namelist and the robot genre
vector<int> robot_x_pos, robot_y_pos, robot_looked, robot_heart, robot_ammo_left;

void robot_fetching_data(int row, int column, int bot_number, string name, string genre, int x_pos, int y_pos, int robot_look, int robot_hp, int robot_ammo)
{
    cout << "data loading ..." << endl;
    row_number = column;
    column_number = row;
    robot_number = bot_number;
    robot_namelist.push_back(name);
    robot_genre.push_back(genre);
    robot_x_pos.push_back(x_pos);
    robot_y_pos.push_back(y_pos);
    robot_looked.push_back(robot_look);
    robot_heart.push_back(robot_hp);
    robot_ammo_left.push_back(robot_ammo);
}

void robot_data_debug()
{
    cout << "debugging robot data" << endl;
    for (int i = 0; i < robot_number; i++)
    {
        cout << "robot ammo left are " << robot_ammo_left[i] << endl;
    }
}

string search_loop(int x, int y) // search looping to be use in the algorithm
{
    string target = "";
    for (int i = 0; i < robot_number; i++) // search loop
    {
        // cout << " searching " << x << "and " << y << endl;
        if (robot_x_pos[i] == x && robot_y_pos[i] == y)
        {

            string target = robot_namelist[i];
            cout << "robot " << robot_namelist[i] << " is found" << endl;
            return target;
        }
    }
    if (target.empty())
    {
        return "";
    }
}
string search_for_robot(int x, int y) // searching algorithm in look and shooting
{

    string target;
    y--;
    target = search_loop(x, y);
    x++;
    target = search_loop(x, y);
    y++;
    target = search_loop(x, y);
    y++;
    target = search_loop(x, y);
    x--;
    target = search_loop(x, y);
    x--;
    target = search_loop(x, y);
    y--;
    target = search_loop(x, y);
    y--;
    target = search_loop(x, y);
    if (!target.empty())
        cout << "No target is found in the range" << endl;
    return target;
}

bool move_robot_search(int x, int y)
{
    for (int i = 0; i < robot_number; i++)
    {
        // cout << robot_x_pos[i] << "| " << x << endl;
        // cout << robot_y_pos[i] << "| " << y << endl;
        if (robot_x_pos[i] == x && robot_y_pos[i] == y)

        {

            return true;
        }
    }
    return false;
}

class Robot // abstract base class
            // doesn't exist until to be derived
{
public:
    virtual void think(int) const = 0;
    virtual void move(int, int &x, int &y) const = 0;
    virtual void shoot(int) const = 0;
    virtual void see(int) const = 0;
    virtual ~Robot() {}; // virtual destructor
};
class ThinkingRobot : virtual public Robot
{
public:
    void think(int turn) const override
    {
        cout << robot_namelist[turn] << " is thinking what to do next" << endl;
    }
};

class MovingRobot : virtual public Robot
{

public:
    void move(int turn, int &x, int &y) const override
    {
        bool moved = false;

        while (!moved)
        {

            int random_number = rand() % 9;
            switch (random_number)
            {
            case 1:
                if (move_robot_search(x, y - 1))
                {
                    cout << " robot " << robot_namelist[turn] << " try to move to an occupied slot" << endl;
                    break;
                }
                else if (robot_y_pos[turn] - 1 > 0)
                {

                    cout << robot_namelist[turn] << " is moving up " << endl;
                    moved = true;
                    robot_y_pos[turn]--;
                    y--;
                    break;
                }
                else
                {
                    cout << robot_namelist[turn] << " is moving up but hit the wall " << endl;
                    int random_number = (rand() % 8) + 1;
                }
                break;

            case 2:
                if (move_robot_search(x, y + 1))
                {
                    cout << " robot " << robot_namelist[turn] << " try to move to an occupied slot" << endl;
                    break;
                }
                else if (robot_y_pos[turn] + 1 <= row_number)
                {

                    cout << robot_namelist[turn] << " is moving down " << endl;
                    moved = true;
                    robot_y_pos[turn]++;
                    y++;
                    break;
                }
                else
                {
                    cout << robot_namelist[turn] << " is moving down but hit the wall " << endl;
                    int random_number = (rand() % 8) + 1;
                }
                break;
            case 3:
                if (move_robot_search(robot_x_pos[turn] - 1, robot_y_pos[turn]))
                {
                    cout << " robot " << robot_namelist[turn] << " try to move to an occupied slot" << endl;
                    break;
                }
                else if (robot_x_pos[turn] - 1 > 0)
                {

                    cout << robot_namelist[turn] << " is moving left " << endl;
                    moved = true;
                    robot_x_pos[turn]--;
                    x--;
                    break;
                }
                else
                {
                    cout << robot_namelist[turn] << " is moving left but hit the wall " << endl;
                    int random_number = (rand() % 8) + 1;
                }
                break;
            case 4:
                if (move_robot_search(robot_x_pos[turn] + 1, robot_y_pos[turn]))
                {
                    cout << " robot " << robot_namelist[turn] << " try to move to an occupied slot" << endl;
                    break;
                }
                else if (robot_x_pos[turn] + 1 <= column_number)
                {

                    cout << robot_namelist[turn] << " is moving right " << endl;
                    moved = true;
                    robot_x_pos[turn]++;
                    x++;
                    break;
                }
                else
                {
                    cout << robot_namelist[turn] << " is moving right but hit the wall " << endl;
                    int random_number = (rand() % 8) + 1;
                }
                break;
            case 5:
                if (move_robot_search(robot_x_pos[turn] + 1, robot_y_pos[turn] - 1))
                {
                    cout << " robot " << robot_namelist[turn] << " try to move to an occupied slot" << endl;
                    break;
                }
                else if (robot_x_pos[turn] + 1 <= column_number && robot_y_pos[turn] - 1 > 0)
                {

                    cout << robot_namelist[turn] << " is moving up right " << endl;
                    moved = true;
                    robot_x_pos[turn]++;
                    robot_y_pos[turn]--;
                    x++;
                    y--;
                    break;
                }
                else
                {
                    cout << robot_namelist[turn] << " is moving up right but hit the wall " << endl;
                    int random_number = (rand() % 8) + 1;
                }
                break;
            case 6:
                if (move_robot_search(robot_x_pos[turn] - 1, robot_y_pos[turn] - 1))
                {
                    cout << " robot " << robot_namelist[turn] << " try to move to an occupied slot" << endl;
                    break;
                }
                else if (robot_x_pos[turn] - 1 > 0 && robot_y_pos[turn] - 1 > 0)
                {

                    cout << robot_namelist[turn] << " is moving up left " << endl;
                    moved = true;
                    robot_x_pos[turn]--;
                    robot_y_pos[turn]--;
                    x--;
                    y--;
                    break;
                }
                else
                {
                    cout << robot_namelist[turn] << " is moving up left but hit the wall " << endl;
                    int random_number = (rand() % 8) + 1;
                }
                break;
            case 7:
                if (move_robot_search(robot_x_pos[turn] - 1, robot_y_pos[turn] - 1))
                {
                    cout << " robot " << robot_namelist[turn] << " try to move to an occupied slot" << endl;
                    break;
                }
                else if (robot_x_pos[turn] - 1 > 0 && robot_y_pos[turn] + 1 < row_number)
                {

                    cout << robot_namelist[turn] << " is moving down left " << endl;
                    moved = true;
                    robot_x_pos[turn]--;
                    robot_y_pos[turn]++;
                    x--;
                    y++;

                    break;
                }
                else
                {
                    cout << robot_namelist[turn] << " is moving down left but hit the wall " << endl;
                    int random_number = (rand() % 8) + 1;
                }
                break;
            case 8:
                if (move_robot_search(robot_x_pos[turn] + 1, robot_y_pos[turn] + 1))
                {
                    cout << " robot " << robot_namelist[turn] << " try to move to an occupied slot" << endl;
                    break;
                }
                else if (robot_x_pos[turn] + 1 <= column_number && robot_y_pos[turn] + 1 <= row_number)
                {

                    cout << robot_namelist[turn] << " is moving down right " << endl;
                    moved = true;
                    robot_x_pos[turn]++;
                    robot_y_pos[turn]++;
                    x++;
                    y++;

                    break;
                }
                else
                {
                    cout << robot_namelist[turn] << " is moving down right but hit the wall " << endl;
                    int random_number = (rand() % 8) + 1;
                }
                break;
            default:
                cout << "invalid movement " << endl;
                break;
            }
        }
    }
};

class ShootingRobot : virtual public Robot
{

public:
    void shoot(int turn) const override
    {
        cout << robot_namelist[turn] << " is shooting " << endl;
    }
};

class SeeingRobot : virtual public Robot
{
public:
    void see(int turn) const override
    {
        cout << robot_namelist[turn] << " is seeing now " << endl;
        int x = robot_x_pos[turn];
        int y = robot_y_pos[turn];
        search_for_robot(x, y);
    }
};

// multiple inheritance of a robot type to do all the action
class GenericBot : public ThinkingRobot,
                   public MovingRobot,
                   public ShootingRobot,
                   public SeeingRobot
{

public:
    void think(int turn) const override
    {
        cout << robot_namelist[turn] << " is thinking" << endl;
    }
    void move(int turn, int &x, int &y) const override
    {
        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        cout << robot_namelist[turn] << " decides to shoot" << endl;
    }
    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    }
};
class HideBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        cout << robot_namelist[turn] << " is thinking" << endl;
    }
    void move(int turn, int &x, int &y) const override
    {

        cout << "test moving " << endl;
    }
    void shoot(int turn) const override
    {
        cout << robot_namelist[turn] << " decides to shoot" << endl;
    }
    void see(int turn) const override
    {
        cout << "seeing now " << endl;
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
};