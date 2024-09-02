#ifndef _SOLVER_H_
#define _SOLVER_H_
//макрозміна нескінченої відстані
#define INFINITY 2147483647
//макрозміна затримки
#define SLEEP_TIME 300
#include <thread>
#include <chrono>
#include "Maze.h"
#include "View.h"

class Solver{
protected:
    //посилання на лабіринт
    Maze *maze;
    //лабіринт зі шляхом
    int **result;
    //змінна для підрахунку кількості ходів
    int stepsCounter;
    //функція для затримки
    void Sleep(const int millisec) const;
public:
    Solver(Maze &maze);
    //віртуальний деструктор
    virtual ~Solver();
    //гетер
    int getStepsCounter();
    //повністю віртуальна функція вирішення
    virtual int solve()=0;
};

#endif