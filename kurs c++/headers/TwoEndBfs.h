#ifndef _TWOENDBFS_H_
#define _TWOENDBFS_H_
    
#include "Solver.h"
#include "Queue.h"

class TwoEndBfs: public Solver{
    //відстані bfs, що починається з початку
    int **distances;
    //відстані bfs, що починається з кінця
    int **distancesEnd;
    //відвідуваність
    int **visited;
    //всі можливі напрями руху
    int moveX[4]={0, 0, -1, 1};
    int moveY[4]={-1, 1, 0, 0};
    //функція для очищення динамічно виділеної пам'яті
    void deleteArray(int*** array);
    //функція для виводу знайденого шляху
    void drawPath(int **dist, int curX, int curY) const;
public:
    TwoEndBfs(Maze &maze);
    ~TwoEndBfs();
    //перевизначення наслідуваної функції
    int solve() override;
};

#endif