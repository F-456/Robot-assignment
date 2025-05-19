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

#ifndef REENTRY_QUEUE_H
#define REENTRY_QUEUE_H

// forward declaration for Robot
class Robot;

class ReentryQueue
{
private:
    struct Node
    {
        Robot *robot;
        Node *next;
        Node(Robot *r) : robot(r), next(nullptr) {}
    };
    Node *front;
    Node *rear;
    int size;

public:
    ReentryQueue();
    ~ReentryQueue();

    bool isEmpty() const;
    void queue(Robot *robot);
    Robot *dequeue();
    int getSize() const;
};

#endif
