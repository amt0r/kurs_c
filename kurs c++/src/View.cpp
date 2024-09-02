#include "View.h"

void printMaze(const Maze *maze) {
    //перевірка чи існує масив лабіринту
    if(!maze->getMaze()){ return; }
    //кольоровий вивід символа в залежності від числа в клітинці
    //0-стіна, 1-прохід, 2-шлях
    for(int i=0; i<maze->rows; i++){
        for(int j=0; j<maze->columns; j++){
            switch (maze->getMaze()[i][j]){
            case 0:
                cout<<WALL;
                break;
            case 1:
                cout<<"  ";
                break;
            case 2:
                color(RED);
                cout<<PATH;
                color(RESET);
                break;
            default:
                break;
            } 
        }
        cout<<endl;
    }
    return;
}
//переміщення курсора в консолі
void gotoXY(const int x, const int y){
    cout << "\033[" << y << ";" << x << "H";
}
//ввід шляху до файлу
void inputPath(string &path){
    cout<<"Введіть шлях до файлу з лабіринтом: ";
    cin>>path;
    resetInput();
}
//очищення консолі
void clearDisplay(){ cout<<"\x1B[2J"; }
//зміна кольору виводу
void color(const Color cl){
    switch (cl){
    case RESET:
        cout << "\033[0m";
        break;
    case RED:
        cout << "\033[31m";
        break;
    default:
        cout << "\033[0m";
        break;
    }
}

int inputMaze(Maze &maze){
    //ввід кількості рядків та стовпців
    cout << "Введіть кількість рядків в лабіринті: ";
    while (!(cin >> maze.rows) || maze.rows <= 0) {
        cout << "Неправильний ввід. Введіть позитивне число: ";
        resetInput();
    }
    resetInput();
    cout << "Введіть кількість стовпців в лабіринті: ";
    while (!(cin >> maze.columns) || maze.columns <= 0) {
        cout << "Неправильний ввід. Введіть позитивне число: ";
        resetInput();
    }
    resetInput();
    //виділення пам'яті
    int** newMaze;
    try{
        newMaze = new int*[maze.rows];
        for (int i = 0; i < maze.rows; i++) {
            newMaze[i] = new int[maze.columns];
        }
    }catch(const bad_alloc &e){
        cerr<<"Помилка виділення пам'яті: " << e.what() << endl;
        //очищення виділеної пам'яті в разі помилки
        if (newMaze) {
            for (int k = 0; k < maze.rows; k++) {
                if (newMaze[k]) {
                    delete[] newMaze[k];
                }
            }
            delete[] newMaze;
        }
        return 1;
    }
    //перевірка на ввід некориктних символів
    cout << "Введіть лабіринт (1 прохід, 0 стіна):" << endl;
    for (int i = 0; i < maze.rows; i++) {
        for (int j = 0; j < maze.columns; j++) {
            while (!(cin >> newMaze[i][j]) || (newMaze[i][j] != 0 && newMaze[i][j] != 1)) {
                cout << "Неправильний ввід. Введіть 0 або 1: ";
                resetInput();
            }
        }
    }
    //збереження лабіринту
    maze.setMaze(newMaze);
    resetInput();
    return 0;
}

void resetInput(){
    //очищення помилок
    cin.clear();
    //ігнорування зайвих символів
    cin.ignore(10000, '\n');
}