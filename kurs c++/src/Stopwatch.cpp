#include "Stopwatch.h"

Stopwatch::Stopwatch(){
    sec = 0; 
    running = 0;
}
//запустити секундомір
void Stopwatch::start(){
    if (!running) {
        startTime = time(NULL);
        running = 1;
    } else {
        cout << "Секундомір вже запущений." << endl;
    }
}
//зупинити секундомір
int Stopwatch::stop(){  
    if (running) {
        sec = time(nullptr)-startTime;
        running = 0;
        return sec;
    } else {
        cout << "Секундомір не запущений." << endl;
        return 0;
    }
}
