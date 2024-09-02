#include "Solver.h"
//функція для затримки
void Solver::Sleep(const int millisec) const {
    this_thread::sleep_for(chrono::milliseconds(millisec));
}

Solver::Solver(Maze &maze){
    //починаємо з нуля кроків
    stepsCounter=0;
    //перевірка на ініціалізацію
    if(!maze.getMaze()) {
        cerr<<"Лабіринт не ініціалізовано."<<endl;
        this->maze=nullptr;
        result=nullptr;
    } else {
        //запис посилання на лабіринт
        this->maze=&maze;
        //виділення пам'яті
        try{
            result=new int*[maze.rows];
            for(int i=0; i<maze.rows; i++){
                result[i]=new int[maze.columns]();
                for(int j=0; j<maze.columns; j++){
                    result[i][j]=maze.getMaze()[i][j];
                }
            }
        } catch(const bad_alloc &e){
            cerr<<"Помилка виділення пам'яті: " << e.what() << endl;
            //очищення виділеної пам'яті в разі помилки
            if (result) {
                for (int k = 0; k < maze.rows; k++) {
                    if (result[k]) {
                        delete[] result[k];
                    }
                }
                delete[] result;
                result=nullptr;
            }
        }
    }
}

Solver::~Solver(){
    if(result){
        for (int i = 0; i < maze->rows; i++) {
            delete[] result[i];
        }
        delete[] result;
        result = nullptr;
    }
}

int Solver::getStepsCounter(){
    return stepsCounter;
}
