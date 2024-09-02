#ifndef _VIEW_H_
#define _VIEW_H_
//символи стінки
#define WALL "\xe2\x96\x88\xe2\x96\x88"
//символи шляху
#define PATH "\xe2\x96\x91\xe2\x96\x91"
#include <iostream>
#include "Maze.h"
//enum кольорів
enum Color { RESET, RED };
//вивід лабіринту
void printMaze(const Maze *maze);
//переміщення курсора в консолі
void gotoXY(const int x, const int y);
//ввід шляху до файлу
void inputPath(string &path);
//очищення консолі
void clearDisplay();
//зміна кольору виводу
void color(const Color cl);
//ввід лабіринту
int inputMaze(Maze &maze);
//очищення потоку вводу
void resetInput();

#endif