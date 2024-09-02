#ifndef _QUEUE_H
#define _QUEUE_H

#include <iostream>
#include <new>
#include "Point.h"
using namespace std;

class Queue {
    //змінна для зберігання точок
    Point *queue;
    //фронт черги
    int front;
    //тил черги
    int rear;
    //вмістимість черги
    int capacity;
public:
    Queue(const int n);
    ~Queue();
    //додати в чергу
    void enqueue(const Point &p);
    //витягнути з черги
    Point dequeue();
    //перевірка чи пуста черга
    bool isEmpty() const;
};

#endif
