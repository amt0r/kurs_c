#ifndef _USERSOLVE_H_
#define _USERSOLVE_H_
    
#include "Solver.h"
#include "Controller.h"

class UserSolve: public Solver{
public:
    UserSolve(Maze &maze);
    //перевизначення наслідуваної функції
    int solve() override;
};

#endif