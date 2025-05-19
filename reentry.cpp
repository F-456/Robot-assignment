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

#include "reentry_queue.h"

ReentryQueue::ReentryQueue() : front(nullptr), rear(nullptr), size(0) {}

ReentryQueue::~ReentryQueue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

bool ReentryQueue::isEmpty() const
{
    return front == nullptr;
}

void ReentryQueue::queue(Robot *robot)
{
    Node *newNode = new Node(robot);
    if (rear)
    {
        rear->next = newNode;
    }
    else
    {
        front = newNode;
    }
    rear = newNode;
    ++size;
}

Robot *ReentryQueue::dequeue()
{
    if (isEmpty())
    {
        return nullptr;
    }
    Node *temp = front;
    Robot *robot = front->robot;
    front = front->next;
    if (front == nullptr)
    {
        rear = nullptr;
    }
    delete temp;
    --size;
    return robot;
}

int ReentryQueue::getSize() const
{
    return size;
}