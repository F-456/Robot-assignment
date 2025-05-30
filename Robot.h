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
#include <limits> // Nicholas
#include <cmath>  // Nicholas

using namespace std;

int row_number, column_number = 0;
int robot_number = 0;
vector<string> robot_namelist, robot_genre; // two vector to store the robot namelist and the robot genre
vector<int> robot_x_pos, robot_y_pos, robot_looked, robot_lives, robot_destroyed, robot_ammo_left;
vector<int> robot_upgraded;
vector<int> robot_tracked_target; // which single robot-index each bot is tracking, or -1 if none yet // Nicholas
int autorepair_used[100] = {0};   // array to track how many times each robot repaired (initialize to 0)

// fetching data from frame h and load it to this file

void random_telepor()
{
}
void robot_fetching_data(int row, int column, int bot_number, string name, string genre, int x_pos, int y_pos)

{
    cout << "data loading ..." << endl;
    row_number = row;
    column_number = column;
    robot_number = bot_number;
    robot_namelist.push_back(name);
    robot_genre.push_back(genre);
    robot_x_pos.push_back(x_pos);
    robot_y_pos.push_back(y_pos);
    robot_tracked_target.push_back(-1); // -1 means “no tracker planted yet”  // Nicholas
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
    bool found;
    string target = "";
    for (int i = 0; i < robot_number; i++) // search loop
    {
        // cout << " searching " << x << "and " << y << endl;
        if (robot_x_pos[i] == x && robot_y_pos[i] == y)
        {

            string target = robot_namelist[i];
            cout << "robot " << robot_namelist[i] << " is found" << endl;
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

int search_hit_target(string name) // a function to find the position of target using the target name
{
    for (int i = 0; i < robot_number; i++)
    {

        if (robot_namelist[i] == name)
        {
            return i;
        }
    }
    return 0;
}

void upgrade_robot(int turn)
{
    if (robot_upgraded[turn] == 0)
    { // the robot haven't upgraded
        // int dice_number = rand() % 5;
        // switch (dice_number)
        {
            // case 0:
            //     robot_genre[turn] = "HideBot";
            //     break;
            // case 1:
            //     robot_genre[turn] = "JumpBot";
            //     break;
            // case 2:
            //     robot_genre[turn] = "LongShotBot";
            //     break;
            // case 3:
            //     robot_genre[turn] = "SemiAutoBot";
            //     break;
            // case 4:
            //     robot_genre[turn] = "ThirtyShotBot";                                      // Nicholas
            //     cout << robot_namelist[turn] << " receives a fresh load of 30 shells.\n"; // Nicholas
            //     robot_ammo_left[turn] = 30;                                               // Nicholas
            //     break;
            // case 5:
            //     robot_genre[turn] = "ScoutBot";
            //     break;
            // // Nicholas Start
            // case 6:
            //     robot_genre[turn] = "TrackBot";
            //     {
            //         void track();
            //     }
            //     break;
            // case 7:
            robot_genre[turn] = "AutoRepairBot";
            {
                robot_genre[turn] = "AutoRepairBot";
                // break;
            }
        }
        cout << robot_namelist[turn] << " is upgrading into a " << robot_genre[turn] << endl;
    }
    else // if the robot is not valid for upgrading
        cout << " The robot has already upgraded " << endl;
};

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

            int random_number = (rand() % 8) + 1;
            switch (random_number)
            {
            case 1:
                if (move_robot_search(x, y - 1))
                {
                    // cout << robot_namelist[turn] << " is trying to move into an occupied slot" << endl;
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
                    // cout << robot_namelist[turn] << " is moving up but hit the wall " << endl;
                }
                break;

            case 2:
                if (move_robot_search(x, y + 1))
                {
                    // cout << robot_namelist[turn] << " is trying to move into an occupied slot" << endl;
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
                    // cout << robot_namelist[turn] << " is moving down but hit the wall " << endl;
                }
                break;
            case 3:
                if (move_robot_search(x - 1, y))
                {
                    // cout << robot_namelist[turn] << " is trying to move into an occupied slot" << endl;
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
                    // cout << robot_namelist[turn] << " is moving left but hit the wall " << endl;
                }
                break;
            case 4:
                if (move_robot_search(x + 1, y))
                {
                    // cout << robot_namelist[turn] << " is trying to move into an occupied slot" << endl;
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
                    // cout << robot_namelist[turn] << " is moving right but hit the wall " << endl;
                }
                break;
            case 5:
                if (move_robot_search(x + 1, y - 1))
                {
                    // cout << robot_namelist[turn] << " is trying to move into an occupied slot" << endl;
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
                    // cout << robot_namelist[turn] << " is moving up right but hit the wall " << endl;
                }
                break;
            case 6:

                if (move_robot_search(x - 1, y - 1))
                {
                    // cout << robot_namelist[turn] << " is trying to move into an occupied slot" << endl;
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
                    // cout << robot_namelist[turn] << " is moving up left but hit the wall " << endl;
                }
                break;
            case 7:
                if (move_robot_search(x - 1, y + 1))
                {
                    // cout << robot_namelist[turn] << " is trying to move into an occupied slot" << endl;
                }
                else if (robot_x_pos[turn] - 1 > 0 && robot_y_pos[turn] + 1 <= row_number)
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
                    // cout << robot_namelist[turn] << " is moving down left but hit the wall " << endl;
                }
                break;
            case 8:
                if (move_robot_search(x + 1, y + 1))
                {
                    // cout << robot_namelist[turn] << " is trying to move into an occupied slot" << endl;
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
                    // cout << robot_namelist[turn] << " is moving down right but hit the wall " << endl;
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
        cout << robot_namelist[turn] << " is trying to shoot " << endl;
        int x = robot_x_pos[turn];
        int y = robot_y_pos[turn];
        // shoot algorithm for the robot
        string target = search_for_robot(x, y);
        if (!target.empty()) // shoot successfully
        {
            if (random_number < 7) // 70 % will hit
            {
                cout << target << " is being shoot by " << robot_namelist[turn] << endl;
                cout << " ammo left: " << robot_ammo_left[turn] - 1 << endl;
                list_position = search_hit_target(target);
                robot_lives[list_position]--;
                cout << target << " is destroyed " << endl;
                cout << "Robot " << target << " now have " << robot_lives[list_position] << " lives left\n";
                robot_destroyed[list_position] = 1;
                upgrade_robot(turn);
            }
            else
            {
                cout << robot_namelist[turn] << " miss the shot " << endl;
            }
        }
        else
        {
            cout << robot_namelist[turn] << " did not find someone to shoot " << endl;
        }
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
    }
    void see(int turn) const override
    {
        cout << "seeing now " << endl;
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
        SeeingRobot::see(turn);
    }
};
// Nicholas Start
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
        SeeingRobot::see(turn);
        // Then handle tracking: if none yet, plant on nearest
        int &tracked = robot_tracked_target[turn];
        if (tracked == -1)
        {
            double bestDist = numeric_limits<double>::infinity();
            int bestIdx = -1;
            int x0 = robot_x_pos[turn], y0 = robot_y_pos[turn];
            for (int i = 0; i < robot_number; ++i)
            {
                if (i == turn)
                    continue;
                double dx = robot_x_pos[i] - x0;
                double dy = robot_y_pos[i] - y0;
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
                cout << robot_namelist[turn] << " plants tracker on '" << robot_namelist[bestIdx] << "' at (" << robot_x_pos[bestIdx] << "," << robot_y_pos[bestIdx] << ")" << std::endl;
            }
        }
        // If already tracking, report coordinates
        if (tracked != -1)
        {
            cout << robot_namelist[turn]
                 << " tracking '" << robot_namelist[tracked]
                 << "' at (" << robot_x_pos[tracked]
                 << "," << robot_y_pos[tracked] << ")" << std::endl;
        }
    }
    void track(int turn)
    {
        // Find nearest
        double bestDist = numeric_limits<double>::infinity();
        int bestIdx = -1;
        int x0 = robot_x_pos[turn], y0 = robot_y_pos[turn];
        for (int i = 0; i < robot_number; ++i)
        {
            if (i == turn)
                continue;
            double dx = robot_x_pos[i] - x0;
            double dy = robot_y_pos[i] - y0;
            double d = sqrt(dx * dx + dy * dy);
            if (d < bestDist)
            {
                bestDist = d;
                bestIdx = i;
            }
        }
        if (bestIdx != -1)
        {
            cout << robot_namelist[turn] << " is upgraded to TrackBot and plants a tracker on '" << robot_namelist[bestIdx] << "' at (" << robot_x_pos[bestIdx] << "," << robot_y_pos[bestIdx] << ")\n";
            robot_tracked_target[turn] = bestIdx;
        }
    }
};

class AutoRepairBot : public ThinkingRobot, public MovingRobot, public ShootingRobot, public SeeingRobot
{
public:
    void think(int turn) const override
    {
        const_cast<AutoRepairBot *>(this)->regenerate(turn);
        ThinkingRobot::think(turn);
    }
    void move(int turn, int &x, int &y) const override
    {
        const_cast<AutoRepairBot *>(this)->regenerate(turn);
        MovingRobot::move(turn, x, y);
    }
    void shoot(int turn) const override
    {
        const_cast<AutoRepairBot *>(this)->regenerate(turn);
        ShootingRobot::shoot(turn);
    }
    void see(int turn) const override
    {
        const_cast<AutoRepairBot *>(this)->regenerate(turn);
        SeeingRobot::see(turn);
    }
    void regenerate(int turn)
    {
        if (robot_genre[turn] == "AutoRepairBot")
        {
            if (autorepair_used[turn] < 3) // max 3 repairs allowed
            {
                autorepair_used[turn]++;
                robot_lives[turn]++;
                cout << robot_namelist[turn] << " repaired 1 life point automatically. Total repairs used: " << autorepair_used[turn] << ". Current lives: " << robot_lives[turn] << endl;
            }
            else
            {
                cout << robot_namelist[turn] << " has used all 3 auto repairs." << endl;
            }
        }
    }
};
// Nicholas End