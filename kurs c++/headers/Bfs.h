#ifndef _BFS_H_
#define _BFS_H_
    
#include "Solver.h"
#include "Queue.h"

class Bfs: public Solver{
    //відстані
    int **distances;
    //відвідуваність
    int **visited;
    //всі можливі напрями руху
    int moveX[4]={0, 0, -1, 1};
    int moveY[4]={-1, 1, 0, 0};
    //функція для очищення динамічно виділеної пам'яті
    void deleteArray(int*** array);
    //функція для виводу знайденого шляху
    void drawPath() const;
public:
    Bfs(Maze &maze);
    ~Bfs();
    //перевизначення наслідуваної функції
    int solve() override;
};

#endif