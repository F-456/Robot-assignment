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
#include <limits>
#include <cmath>

using namespace std;
int row_number, column_number = 0;
int robot_num = 0;
int scout_use = 3;
int teleport_x_pos, teleport_y_pos;
vector<string> robot_name, robot_genre; // two vector to store the robot namelist and the robot genre
vector<int> robot_x, robot_y, robot_looked, robot_lives, robot_destroyed, robot_ammo_left;
vector<int> robot_upgraded;
vector<int> jump_left, hide_left;
vector<int> robot_tracked_target; // which single robot-index each bot is tracking, or -1 if none yet
vector<bool> tank_shield_used;    // false by default, same index as robot
vector<int> repel_left;

// fetching data from frame h and load it to this file

void robot_fetching_data(int bot_number, int x_pos, int y_pos)

{
    cout << "data loading ..." << endl;

    robot_num = bot_number;
    robot_x.push_back(x_pos);
    robot_y.push_back(y_pos);
}

void random_teleport()
{

    bool teleport_done = false;
    cout << " teleporting" << endl;
    while (!teleport_done) // while not finding the choosen coordinate keep looping
    {
        bool found_collision = false;
        teleport_x_pos = rand() % column_number + 1; // random x coordinate
        teleport_y_pos = rand() % row_number + 1;
        cout << "x = " << teleport_x_pos << endl;
        cout << "y = " << teleport_y_pos << endl;
        for (int i = 0; i < robot_num; i++) // checking if the choose number has already a existing one in the list
        {

            if (teleport_x_pos == robot_x[i] && teleport_y_pos == robot_y[i])
            {
                found_collision = true; // added another boolean to make sure every pair of coordinate is check
            }
        }
        if (found_collision == true) // if collision happen continue to loop it
        {
            teleport_done = false;
        }
        else
            teleport_done = true;
    }
    cout << " The choosen teleportation coordinate = " << teleport_x_pos << " , " << teleport_y_pos << endl;
}

void robot_name_debug()
{
    for (int i = 0; i < robot_num; i++)
    {
        cout << robot_name[i] << ",";
    }
}
void robot_data_debug()
{
    cout << "debugging robot data" << endl;
    for (int i = 0; i < robot_num; i++)
    {
        cout << "robot ammo left are " << robot_ammo_left[i] << endl;
    }
}

string search_loop(int x, int y) // search looping to be use in the algorithm
{
    bool found;
    string target = "";
    for (int i = 0; i < robot_num; i++) // search loop
    {
        // cout << " searching " << x << "and " << y << endl;
        if (robot_x[i] == x && robot_y[i] == y)
        {

            string target = robot_name[i];
            cout << "robot " << robot_name[i] << " is found" << endl;
            found = true;
            return target;
        }
    }
    if (!found)
    {
        return "";
    }
}
string search_for_robot(int x0, int y0)
{
    const int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1}; // using const array to fix the search movement
    const int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};

    string target;
    for (int direction = 0; direction < 8; ++direction)
    {
        int x = x0 + dx[direction];
        int y = y0 + dy[direction];
        target = search_loop(x, y);
        if (!target.empty())
        {
            break; // exit the loop if a target is found, target holds the name
        }
    }

    if (target.empty())
        cout << "No target is found in the range\n";
    else
        cout << "target found: " << target << endl;

    return target;
}

string long_range_search(int x, int y, int range)
{
    for (int dx = -range; dx <= range; dx++)
    {
        for (int dy = -range; dy <= range; dy++)
        {
            if (dx == 0 && dy == 0)
                continue; // Skip itself

            int longx = x + dx;
            int longy = y + dy;

            if (longx < 0 || longy < 0 || longx >= 10 || longy >= 7)
                continue;

            string target = search_loop(longx, longy);
            // cout << longx << "," << longy << endl;

            if (!target.empty())
            {
                cout << "Target found: " << target << endl;
                return target;
            }
        }
    }

    cout << "No target is found in the range\n";
    return "";
}
void scout_skill(int turn)
{
    // for (int scout_use = 3; scout_use >=0; scout_use--)
    // {
    //     if (scout_use >0)
    //     {
    //         cout << "Remaining scout: " << scout_use << endl;

    //         cout << robot_namelist[turn] << " is scouting the entire battlefield" << endl;

    //         for(int i = 0; i < robot_number; i++)
    //             {
    //                 if(i == turn) continue; //skip itself
    //                 cout << "Detected enemy: " << robot_namelist[i] << " [" << robot_x_pos[i] << ", " << robot_y_pos[i] << "]" << endl;
    //             }

    //     }
    //     else
    //     {
    //         cout << robot_namelist[turn] << " has use all the scout chance" << endl;
    //         return;
    //     }
    // }
    // int scout_use = 3;
    if (scout_use <= 0)
    {
        cout << robot_name[turn] << " has use all the scout chance" << endl;
        return;
    }
    // int x = robot_x_pos[turn];
    // int y = robot_y_pos[turn];
    // int full_range = 8;

    cout << robot_name[turn] << " is scouting the entire battlefield" << endl;

    for (int i = 0; i < robot_num; i++)
    {
        if (i == turn)
            continue; // skip itself
        cout << "Detected enemy: " << robot_name[i] << " [" << robot_x[i] << ", " << robot_y[i] << "]" << endl;
    }

    scout_use--;
    cout << "Remaining scout: " << scout_use << endl;
    // string found = long_range_search(x, y, full_range);
}

bool move_robot_search(int x, int y)
{
    for (int i = 0; i < robot_num; i++)
    {
        // cout << robot_x[i] << "| " << x << endl;
        // cout << robot_y[i] << "| " << y << endl;
        if (robot_x[i] == x && robot_y[i] == y)

        {
            return true;
        }
    }
    return false;
}

int search_hit_target(string name) // a function to find the position of target using the target name
{
    for (int i = 0; i < robot_num; i++)
    {

        if (robot_name[i] == name)
        {
            return i;
        }
    }
}

void upgrade_robot(int turn)
{
    if (robot_upgraded[turn] == 0)
    { // the robot haven't upgraded
        int dice_number = rand() % 9;
        robot_upgraded[turn]++;
        switch (dice_number)
        {
        case 0:
            robot_genre[turn] = "HideBot";
            break;
        case 1:
            robot_genre[turn] = "JumpBot";
            break;
        case 2:
            robot_genre[turn] = "LongShotBot";
            break;
        case 3:
            robot_genre[turn] = "SemiAutoBot";
            break;
        case 4:
            robot_genre[turn] = "ThirtyShotBot";
            cout << robot_name[turn] << " receives a fresh load of 30 shells.\n"; // Nicholas
            robot_ammo_left[turn] = 30;
            break;
        case 5:
            robot_genre[turn] = "ScoutBot";
            break;
        case 6:
            robot_genre[turn] = "TrackBot";
            {
                void track();
            }
            break;
        case 7:
            robot_genre[turn] = "RepelBot";
            repel_left[turn]++;
            break;
        case 8:
            robot_genre[turn] = "DoubleBot";
            break;
        case 9:
            robot_genre[turn] = "TankBot";
            {
                robot_genre[turn] = "TankBot";
                robot_lives[turn]++;
                tank_shield_used[turn] = false;
            }
            break;
        }
        cout << robot_name[turn] << " is upgrading into a " << robot_genre[turn] << endl;
    }
    else // if the robot is not valid for upgrading
        cout << " The robot has already upgraded " << endl;
}

void check_robot_dead(int target_position, int turn)
{

    int dead_index = target_position;

    if (robot_lives[target_position] == 0)
    {
        cout << robot_name[dead_index] << " is dead " << endl;
        robot_name.erase(robot_name.begin() + dead_index);
        cout << "deleted x and y are " << robot_x[dead_index] << ", " << robot_y[dead_index] << endl;
        robot_x.erase(robot_x.begin() + dead_index);
        robot_y.erase(robot_y.begin() + dead_index);
        robot_lives.erase(robot_lives.begin() + dead_index);
        robot_destroyed.erase(robot_destroyed.begin() + dead_index);
        robot_ammo_left.erase(robot_ammo_left.begin() + dead_index);
        robot_upgraded.erase(robot_upgraded.begin() + dead_index);
        jump_left.erase(jump_left.begin() + dead_index);
        hide_left.erase(hide_left.begin() + dead_index);
        robot_tracked_target.erase(robot_tracked_target.begin() + dead_index);
        robot_num--;
    }
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
        cout << robot_name[turn] << " is thinking what to do next" << endl;
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

            int random_number = (rand() % 8) + 1;
            switch (random_number)
            {
            case 1:
                if (move_robot_search(x, y - 1))
                {
                    // cout << robot_name[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_y[turn] - 1 > 0)
                {

                    cout << robot_name[turn] << " is moving up " << endl;
                    moved = true;
                    robot_y[turn]--;
                    y--;
                    break;
                }
                else
                {
                    // cout << robot_name[turn] << " is moving up but hit the wall " << endl;
                }
                break;

            case 2:
                if (move_robot_search(x, y + 1))
                {
                    // cout << robot_name[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_y[turn] + 1 <= row_number)
                {

                    cout << robot_name[turn] << " is moving down " << endl;
                    moved = true;
                    robot_y[turn]++;
                    y++;
                    break;
                }
                else
                {
                    // cout << robot_name[turn] << " is moving down but hit the wall " << endl;
                }
                break;
            case 3:
                if (move_robot_search(x - 1, y))
                {
                    // cout << robot_name[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_x[turn] - 1 > 0)
                {

                    cout << robot_name[turn] << " is moving left " << endl;
                    moved = true;
                    robot_x[turn]--;
                    x--;
                    break;
                }
                else
                {
                    // cout << robot_name[turn] << " is moving left but hit the wall " << endl;
                }
                break;
            case 4:
                if (move_robot_search(x + 1, y))
                {
                    // cout << robot_name[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_x[turn] + 1 <= column_number)
                {

                    cout << robot_name[turn] << " is moving right " << endl;
                    moved = true;
                    robot_x[turn]++;
                    x++;
                    break;
                }
                else
                {
                    // cout << robot_name[turn] << " is moving right but hit the wall " << endl;
                }
                break;
            case 5:
                if (move_robot_search(x + 1, y - 1))
                {
                    // cout << robot_name[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_x[turn] + 1 <= column_number && robot_y[turn] - 1 > 0)
                {

                    cout << robot_name[turn] << " is moving up right " << endl;
                    moved = true;
                    robot_x[turn]++;
                    robot_y[turn]--;
                    x++;
                    y--;
                    break;
                }
                else
                {
                    // cout << robot_name[turn] << " is moving up right but hit the wall " << endl;
                }
                break;
            case 6:

                if (move_robot_search(x - 1, y - 1))
                {
                    // cout << robot_name[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_x[turn] - 1 > 0 && robot_y[turn] - 1 > 0)
                {

                    cout << robot_name[turn] << " is moving up left " << endl;
                    moved = true;
                    robot_x[turn]--;
                    robot_y[turn]--;
                    x--;
                    y--;
                    break;
                }
                else
                {
                    // cout << robot_name[turn] << " is moving up left but hit the wall " << endl;
                }
                break;
            case 7:
                if (move_robot_search(x - 1, y + 1))
                {
                    // cout << robot_name[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_x[turn] - 1 > 0 && robot_y[turn] + 1 <= row_number)
                {

                    cout << robot_name[turn] << " is moving down left " << endl;
                    moved = true;
                    robot_x[turn]--;
                    robot_y[turn]++;
                    x--;
                    y++;
                    break;
                }
                else
                {
                    // cout << robot_name[turn] << " is moving down left but hit the wall " << endl;
                }
                break;
            case 8:
                if (move_robot_search(x + 1, y + 1))
                {
                    // cout << robot_name[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_x[turn] + 1 <= column_number && robot_y[turn] + 1 <= row_number)
                {

                    cout << robot_name[turn] << " is moving down right " << endl;
                    moved = true;
                    robot_x[turn]++;
                    robot_y[turn]++;
                    x++;
                    y++;
                    break;
                }
                else
                {
                    // cout << robot_name[turn] << " is moving down right but hit the wall " << endl;
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

        int list_position = 0;

        int random_number = rand() % 10;
        cout << robot_name[turn] << " is trying to shoot " << endl;
        int x = robot_x[turn];
        int y = robot_y[turn];
        // shoot algorithm for the robot
        string target = search_for_robot(x, y);
        list_position = search_hit_target(target);
        if (!target.empty()) // shoot successfully
        {
            if (robot_genre[list_position] == "HideBot" && hide_left[list_position] > 0)
            {
                cout << "Target " << robot_name[list_position] << " is hiding from the shoot" << endl;
                hide_left[list_position]--;
                cout << robot_name[list_position] << " have " << hide_left[list_position] << " times of hide left" << endl;
            }
            else if (repel_left[list_position] == 1)
            {
                cout << "Target " << robot_name[list_position] << " active a repel shot" << endl;
                cout << robot_name[turn] << " is shoot by itself " << endl;
                robot_lives[turn]--;
                robot_ammo_left[turn]--;
                repel_left[list_position]--;
                cout << "Robot " << robot_name[turn] << " now have " << robot_lives[turn] << " lives left\n";
                cout << " ammo left: " << robot_ammo_left[turn] << endl;
            }
            else if (random_number < 7) // 70 % will hit
            {
                robot_ammo_left[turn]--;
                cout << target << " is being shoot by " << robot_name[turn] << endl;
                cout << " ammo left: " << robot_ammo_left[turn] << endl;
                robot_lives[list_position]--;
                check_robot_dead(list_position, turn);
                cout << target << " is destroyed " << endl;
                cout << "Robot " << target << " now have " << robot_lives[list_position] << " lives left\n";
                robot_destroyed[list_position] = 1;
                upgrade_robot(turn);
            }
            else
            {
                cout << robot_name[turn] << " miss the shot " << endl;
                cout << " ammo left: " << robot_ammo_left[turn] - 1 << endl;
            }
        }
        else
        {
            cout << robot_name[turn] << " did not find someone to shoot " << endl;
        }
    }
};

class SeeingRobot : virtual public Robot
{
public:
    void see(int turn) const override
    {
        cout << robot_name[turn] << " is seeing now " << endl;
        int x = robot_x[turn];
        int y = robot_y[turn];
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
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {
        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
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
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {

        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    }
};
class JumpBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{

public:
    void think(int turn) const override
    {

        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {
        if (jump_left[turn] != 0)
        {

            cout << robot_name[turn] << " is using the jump ability " << endl;
            random_teleport();
            robot_x[turn] = teleport_x_pos;
            x = teleport_x_pos;
            robot_y[turn] = teleport_y_pos;
            y = teleport_y_pos;
            jump_left[turn]--;
            cout << " Robot " << robot_name[turn] << " has jumped to " << teleport_x_pos << " and " << teleport_y_pos << endl;
            cout << jump_left[turn] << "jump are left" << endl;
        }
        else

            MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    };
};

// zh part
class LongShotBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        cout << robot_name[turn] << " is thinking" << endl;
    }
    void move(int turn, int &x, int &y) const override
    {

        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {

        int list_position = 0;

        int random_number = rand() % 10;
        cout << robot_name[turn] << " is using longshot ability" << endl;
        int x = robot_x[turn];
        int y = robot_y[turn];
        // shoot algorithm for the robot
        string target = long_range_search(x, y, 3);
        if (!target.empty()) // shoot successfully
        {
            if (robot_genre[list_position] == "HideBot" && hide_left[list_position] > 0)
            {
                cout << "Target " << robot_name[list_position] << " is hiding from the shoot" << endl;
                hide_left[list_position]--;
                cout << robot_name[list_position] << " have " << hide_left[list_position] << " times of hide left" << endl;
            }
            else if (repel_left[list_position] == 1)
            {
                cout << "Target " << robot_name[list_position] << " active a repel shot" << endl;
                cout << robot_name[turn] << " is shoot by itself " << endl;
                robot_lives[turn]--;
                robot_ammo_left[turn]--;
                repel_left[list_position]--;
                cout << "Robot " << robot_name[turn] << " now have " << robot_lives[turn] << " lives left\n";
                cout << " ammo left: " << robot_ammo_left[turn] << endl;
            }
            else if (random_number < 7)
            {
                cout << target << " is being shoot by " << robot_name[turn] << endl;
                robot_ammo_left[turn]--;
                cout << " ammo left: " << robot_ammo_left[turn] << endl;
                list_position = search_hit_target(target);
                robot_lives[list_position]--;
                cout << target << " is destroyed " << endl;
                cout << "Robot " << target << " now have " << robot_lives[list_position] << " lives left\n";
                robot_destroyed[list_position] = 1;
                upgrade_robot(turn);
            }
            else
            {
                cout << robot_name[turn] << " miss the long range shot " << endl;
            }
        }
        else
        {
            cout << robot_name[turn] << " did not find someone to shoot " << endl;
        }
    }

    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    }
};
// Nicholas start
class SemiAutoBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {

        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    }
};
// Nicholas
class ThirtyShotBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {
        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    }
};

// zh part
class ScoutBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {

        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        scout_skill(turn);
    }
};
// Nicholas
class TrackBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {

        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        // Then handle tracking: if none yet, plant on nearest
        int &tracked = robot_tracked_target[turn];
        if (tracked == -1)
        {
            double bestDist = numeric_limits<double>::infinity();
            int bestIdx = -1;
            int x0 = robot_x[turn], y0 = robot_y[turn];
            for (int i = 0; i < robot_num; ++i)
            {
                if (i == turn)
                    continue;
                double dx = robot_x[i] - x0;
                double dy = robot_y[i] - y0;
                double d = sqrt(dx * dx + dy * dy);
                if (d < bestDist)
                {
                    bestDist = d;
                    bestIdx = i;
                }
            }
            if (bestIdx != -1)
            {
                tracked = bestIdx;
                cout << robot_name[turn] << " plants tracker on '" << robot_name[bestIdx] << "' at (" << robot_x[bestIdx] << "," << robot_y[bestIdx] << ")" << std::endl;
            }
        }
        // If already tracking, report coordinates
        if (tracked != -1)
        {
            cout << robot_name[turn]
                 << " tracking '" << robot_name[tracked]
                 << "' at (" << robot_x[tracked]
                 << "," << robot_y[tracked] << ")" << std::endl;
        }
    }
    void track(int turn)
    {
        // Find nearest
        double bestDist = numeric_limits<double>::infinity();
        int bestIdx = -1;
        int x0 = robot_x[turn], y0 = robot_y[turn];
        for (int i = 0; i < robot_num; ++i)
        {
            if (i == turn)
                continue;
            double dx = robot_x[i] - x0;
            double dy = robot_y[i] - y0;
            double d = sqrt(dx * dx + dy * dy);
            if (d < bestDist)
            {
                bestDist = d;
                bestIdx = i;
            }
        }
        if (bestIdx != -1)
        {
            cout << robot_name[turn] << " is upgraded to TrackBot and plants a tracker on '" << robot_name[bestIdx] << "' at (" << robot_x[bestIdx] << "," << robot_y[bestIdx] << ")\n";
            robot_tracked_target[turn] = bestIdx;
        }
    }
};

class TankBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {
        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    }
    void take_damage(int turn)
    {
        if (robot_genre[turn] == "TankBot")
        {
            if (!tank_shield_used[turn])
            {
                cout << robot_name[turn] << "'s shield absorbed the damage!" << endl;
                tank_shield_used[turn] = true;
            }
            else
            {
                robot_lives[turn]--;
                cout << robot_name[turn] << " took damage and now has " << robot_lives[turn] << " lives left." << endl;

                if (robot_lives[turn] <= 0)
                {
                    cout << robot_name[turn] << " is destroyed!" << endl;
                    robot_destroyed[turn] = 1;
                }
                else
                {
                    tank_shield_used[turn] = false; // reset shield for next life cycle if you want
                }
            }
        }
        else
        {
            // Default damage behavior for non-TankBot robots
            robot_lives[turn]--;
            cout << robot_name[turn] << " took damage and now has " << robot_lives[turn] << " lives left." << endl;
            if (robot_lives[turn] <= 0)
            {
                cout << robot_name[turn] << " is destroyed!" << endl;
                robot_destroyed[turn] = 1;
            }
        }
    }
};
class RepelBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {
        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    }
};

class DoubleBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {
        MovingRobot::move(turn, x, y);
        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        SeeingRobot::see(turn);
    }
};
