#include "UserSolve.h"

UserSolve::UserSolve(Maze &maze) : Solver(maze) {}

int UserSolve::solve(){
    //перевірка на ініціалізацію
    if(!maze) { return 1; }   
    
    char key;
    //вивід підказок по управлінню
    gotoXY(0, 4);
    cout<<"\u2190 \u2191 \u2192 \u2193, двічі 'е'-вихід"<<endl;
    //вивід лабіринту
    gotoXY(0, 5);
    printMaze(maze);

    int x=1;
    int y=1;
    gotoXY(1+y*2, 5+x);
    color(RED);
    cout<<PATH;
    color(RESET);
    //цикл допоки лабіринт не пройдений
    while(result[maze->rows-2][maze->columns-2] != 2){
        //ігнорування зайвого символу
        getch();
        //зчитування клавіші та переміщення у відповідному напрямку, якщо можливо
        key=getch();
        if(key == 'e'){break;}
        if(key == KEY_UP && result[x-1][y]==1){x--;}
        if(key == KEY_DOWN && result[x+1][y]==1){x++;}
        if(key == KEY_LEFT && result[x][y-1]==1){y--;}
        if(key == KEY_RIGHT && result[x][y+1]==1){y++;}
        //вивід шляху
        result[x][y]=2;
        gotoXY(1+y*2, 5+x);
        color(RED);
        cout<<PATH;
        color(RESET);
        //збільшуємо кількість кроків на одиницю
        stepsCounter++;
    }
    //в разі проходження лабіринту вивід повідомлення
    if(result[maze->rows-2][maze->columns-2] == 2){
        gotoXY(0, 3);
        cout<<"Ви пройшли лабіринт!";
    }

    return 0;
}
