/**********|**********|**********|
Program: reentry.h
Course: Data Structures and Algorithms
Trimester: 2410
Name: Frank Carrano
ID: 1071001234
Lecture Section: TC101
Tutorial Section: TT1L
Email: abc123@yourmail.com
Phone: 018-1234567
**********|**********|**********/

#ifndef REENTRY_H
#define REENTRY_H

// Forward declaration
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

    // Prevent copy construction and assignment
    ReentryQueue(const ReentryQueue &) = delete;
    ReentryQueue &operator=(const ReentryQueue &) = delete;

public:
    ReentryQueue() : front(nullptr), rear(nullptr), size(0) {}

    ~ReentryQueue()
    {
        while (!isEmpty())
        {
            dequeue();
        }
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    void queue(Robot *robot)
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

    Robot *dequeue()
    {
        if (isEmpty())
        {
            return nullptr;
        }

        Node *temp = front;
        Robot *robot = temp->robot;
        front = front->next;

        if (!front)
        {
            rear = nullptr;
        }

        delete temp;
        --size;

        return robot;
    }

    int getSize() const
    {
        return size;
    }
};

#endif
