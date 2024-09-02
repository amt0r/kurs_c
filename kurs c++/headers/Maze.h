#ifndef _MAZE_H_
#define _MAZE_H_

#include <iostream>
#include <fstream>
#include <new>
using namespace std;

class Maze{
    //масив для зберігання лабіринту
    int **maze;
public:
    int rows;
    int columns;
    Maze();
    ~Maze();
    int **getMaze() const;
    void setMaze(int ** const array);
    //зчитати лабіринт з файлу
    int readMaze(const string &fileName);
    //видалит масив лабіринт
    void deleteMaze();
};
    
#endif