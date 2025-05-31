/**********|**********|**********|
Program: main.cpp / Frame.h/ Robot.h
Course: Data Structures and Algorithms
Trimester: 2410
Lecture Class: TC3L
Tutorial Class: TT5L
Trimester: 2430
Member_1: 242UC244DD | TIEW FU SIANG | TIEW.FU.SIANG@student.mmu.edu.my |010-3706933
Member_2: 242UC244PP | Nicholas Beh Zhi Yang | NICHOLAS.BEH.ZHI@student.mmu.edu.my | 011-65215166
Member_3: 242UC24551 | LOW ZHENG HAO | LOW.ZHENG.HAO@student.mmu.edu.my | 013-8888444
**********|**********|**********/

#include <iostream>
#include <fstream>
#include <sstream>
#include "Frame.h"
#include <ctime>

using namespace std;

#include <streambuf>

// Custom buffer stream that writes to two streambufs
class TeeBuf : public streambuf
{
public:
    // teebuf is a custom stream buffer
    TeeBuf(streambuf *sb1, streambuf *sb2) : sb1(sb1), sb2(sb2) {}

protected:
    virtual int overflow(int c) override
    {
        if (c == EOF)
            return !EOF;
        if (sb1->sputc(c) == EOF)
            return EOF;
        if (sb2->sputc(c) == EOF)
            return EOF;
        return c;
    }

    // handle flushing
    virtual int sync() override
    {
        int r1 = sb1->pubsync();
        int r2 = sb2->pubsync();
        return (r1 == 0 && r2 == 0) ? 0 : -1;
    }

private:
    streambuf *sb1;
    streambuf *sb2;
};
int main()
{

    srand(time(0));
    string file_name = "Robot_config.cfg";
    display_class display;
    ofstream out("Log.txt");
    if (!out.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return 1;
    }

    TeeBuf teebuf(cout.rdbuf(), out.rdbuf()); // changing the cout to custom stream and output in both log file and terminal
    ostream tee_stream(&teebuf);

    // Replace std::cout with the tee stream
    streambuf *old_cout_buf = cout.rdbuf();
    cout.rdbuf(&teebuf);

    display.reading_from_file(file_name);

    display.value_initialize(); // initializing all the required data for the robot
    display.fetching_data();    // fetch data to the robot.h file
    // display.debug();
    //  main loop for the program
    display.frame_loop();
    // for debug purposes only
    // display.check_robot_data();

    return 0;
}