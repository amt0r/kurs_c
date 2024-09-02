#ifndef _STOPWATCH_H_
#define _STOPWATCH_H_

#include <iostream>
#include <ctime>
using namespace std;

class Stopwatch{
    //секунди
    int sec;
    //зберігання стану секундоміра
    int running;
    //зберігання часу запуску секундоміра
    time_t startTime;
public:
    Stopwatch();
    void start();
    int stop();
};
 
#endif