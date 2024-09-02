#include "Maze.h"

Maze::Maze(){
    maze=nullptr;
    rows=0;
    columns=0;
}

Maze::~Maze(){
    if(maze){
        deleteMaze();
    }
}
//гетер
int **Maze::getMaze() const { return maze; }
//сетер з видаленням попереднього лабіринту якщо він існує
void Maze::setMaze(int ** const array){ 
    if(maze){
        for(int i=0; i<rows; i++) {
            delete[] maze[i];
        }
        delete[] maze;
    }
    maze=array; 
}

int Maze::readMaze(const string &fileName){
    ifstream file;
    //відкриття файлу
    file.open(fileName);
    //перевірка чи відкрився файл
    if(!file.is_open()){
        cerr<<"Помилка відкриття файлу."<<endl;
        return 1;
    }
    
    string line;
    //зчитування полінійно файлу для підрахунку рядків та перевірка на недопустимі символи
    while(getline(file, line)){
        for (char c : line) {
            if (c != '0' && c != '1') {
                cerr << "Помилка файл містить неприпустимі символи." << endl;
                file.close();
                return 1;
            }
        }
        rows++;
        columns=line.size();
    }
    //виділення пам'яті для лабіринту
    try{
        maze=new int*[rows];
        for(int i=0; i<rows; i++){
            maze[i]=new int[columns];
        }
    }catch(const bad_alloc &e){
        cerr<<"Помилка виділення пам'яті: " << e.what() << endl;
        if (maze) {
            for (int k = 0; k < rows; k++) {
                if (maze[k]) {
                    delete[] maze[k];
                }
            }
            delete[] maze;
        }
        file.close();
        return 1;
    }
    //зчитування лабіринту з початку файлу в масив
    file.clear();
    file.seekg(0, ios::beg);
    rows=0;
    
    while(getline(file, line)){
        for(int i=0; i<columns; i++){
            maze[rows][i]=line[i]-'0';
        }
        rows++;
    }
    
    file.close();

    return 0;
}

void Maze::deleteMaze(){
    for (int k = 0; k < rows; k++) {
        delete[] maze[k];
    }
    delete[] maze;
    maze=nullptr;
}
