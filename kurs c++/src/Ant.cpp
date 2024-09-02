#include "Ant.h"

Ant::Ant(Maze &maze) : Solver(maze) {}

int Ant::solve(){
    //перевірка на ініціалізацію
    if(!maze) { return 1; }
    //вивід лабіринту
    printMaze(maze);
    //всі можливі напрями руху
    const int moveX[4] = {-1, 0, 1, 0};
    const int moveY[4] = {0, 1, 0, -1};
    int x = 1;
    int y = 1;
    //початковий напрям
    int direction = 1;
    gotoXY(1+y*2, 5+x);
    color(RED);
    cout<<PATH;
    color(RESET);
    int counter=MAX_VISITED_STEPS;
    //цикл, доки лабіринт не буде пройдений або counter не зменшиться до нуля
    while (result[maze->rows-2][maze->columns-2] != 2 && counter>0) {
        //затримка для покрокового виводу
        Sleep(SLEEP_TIME);
        //спробувати повернути наліво
        int newDirection = (direction + 3) % 4;
        if (result[x+moveX[newDirection]][y+moveY[newDirection]] != 0) {
            direction = newDirection;
            //збільшуємо кількість кроків на одиницю
            stepsCounter++;
            x += moveX[direction];
            y += moveY[direction];
        //якщо рух неможливий то крок прямо
        } else if (result[x+moveX[direction]][y + moveY[direction]] != 0) {
            //збільшуємо кількість кроків на одиницю
            stepsCounter++;
            x += moveX[direction];
            y += moveY[direction];
        //якщо і попереду стінка, то поворот направо
        } else {
            direction = (direction + 1) % 4;
        }
        //якщо клітинка під мурахою вже була пройдена, то conter зменшується на одиницю
        if(result[x][y]==2) counter--;
        //позначення клітинки, як відвіданої
        result[x][y]=2;
        //вивід відвіданої клітинки
        gotoXY(1+y*2, 5+x);
        color(RED);
        cout<<PATH;
        color(RESET);
    }
    //якщо counter зменшився до нуля, то алгоритм не знайшов шлях за обмежену кількість кроків по відвіданих клітинках
    if(counter==0){
        gotoXY(0,3);
        cout<<"Не знайшов рішення за обмежену кількість кроків по відвіданих клітинках."<<endl;
    }
    return 0;
}