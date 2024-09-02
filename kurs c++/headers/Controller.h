#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

//макрозміні
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ENTER '\r'
//шлях до файлу стандартного лабіринту
#define STD_PATH "mazes\\maze1.txt"
#include <conio.h>
#include <regex>
#include "Maze.h"
#include "View.h"
#include "Stopwatch.h"
#include "Solver.h"
#include "Bfs.h"
#include "TwoEndBfs.h"
#include "Ant.h"
#include "UserSolve.h"

void start();
//вивід меню
void printMenu(const string menu[], const unsigned int size);
//запит натиснути будь-яку клавішу
void pressAnyKeyPrompt();
//перевірка шляху до файлу на правильність
int isValidPath(const string &path);
//перевірка лабіринту на правильність
int isValidMaze(Maze &maze);
    
#endif