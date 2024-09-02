#include "Queue.h"

Queue::Queue(const int n){
    front=0;
    rear=0;
    capacity=n;
    try{
        queue=new Point[n];
    } catch(const bad_alloc &e){
        cerr<<"Помилка виділення пам'яті: " << e.what() << endl;
        throw;
    }
}

Queue::~Queue(){
    delete[] queue;
    queue = nullptr;
}
//додати в чергу
void Queue::enqueue(const Point &p){
    if (rear < capacity) {
        queue[rear++] = p;
    } else {
        cerr<<"Черга переповнена.";
    }
}
//витягнути з черги
Point Queue::dequeue() {
    if (!isEmpty()) {
        return queue[front++];
    }
    cerr<<"Черга порожня.";
    return Point(0,0);
}
//перевірка чи пуста черга
bool Queue::isEmpty() const {
    return front == rear;
}
