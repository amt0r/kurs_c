#ifndef _ANT_H_
#define _ANT_H_

//макрозміна обмеження, на випадок неможливості пройти лабіринт
#define MAX_VISITED_STEPS 40
#include "Solver.h"

class Ant: public Solver{
    //напрям руху
    int direction;
public:
    Ant(Maze &Maze);
    //перевизначення наслідуваної функції
    int solve() override;
};

#endif