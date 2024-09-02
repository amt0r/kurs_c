#include "Bfs.h"

Bfs::Bfs(Maze &maze) : Solver(maze) {
    //перевірка на ініціалізацію
    if(!maze.getMaze()) {
        distances=nullptr;
        visited=nullptr; 
    } else {
        //виділення пам'яті
        try{
            distances=new int*[maze.rows];
            visited=new int*[maze.rows];
            for(int i=0; i<maze.rows; i++){
                distances[i]=new int[maze.columns]();
                visited[i]=new int[maze.columns]();
                for(int j=0; j<maze.columns; j++){
                    distances[i][j]=INFINITY;
                    visited[i][j]=false;
                }
            }
        } catch(const bad_alloc &e){
            cerr<<"Помилка виділення пам'яті: " << e.what() << endl;
            //очищення виділеної пам'яті в разі помилки
            deleteArray(&distances);
            deleteArray(&visited);
        }
    }
}

Bfs::~Bfs() {
    deleteArray(&distances);
    deleteArray(&visited);
}

void Bfs::deleteArray(int*** array){
    if (*array) {
        for (int k = 0; k < maze->rows; k++) {
            if ((*array)[k]) {
                delete[] (*array)[k];
            }
        }
        delete[] *array;
        *array = nullptr;
    }
}

int Bfs::solve() {
    //перевірка на ініціалізацію
    if(!maze) { return 1; }
    //вивід лабіринту
    printMaze(maze);
    //створення черги
    Queue queue(maze->rows * maze->columns);
    //початкова точка
    Point current, src(1, 1);
    //додавання початкової точки в чергу
    queue.enqueue(src);
    //призначення 0 як відстані до початкової точки
    distances[src.getX()][src.getY()]=0;
    //позначення початкової точки як відвіданої
    visited[src.getX()][src.getY()]=true;
    int newX, newY;
    
    gotoXY(1+src.getY()*2, 5+src.getX());
    cout<<distances[src.getX()][src.getY()];
    //цикл, доки черга не пуста або не знайдений шлях
    while(!queue.isEmpty() && distances[maze->rows-2][maze->columns-2]==INFINITY){
        //береться точка з черги
        current=queue.dequeue();
        //цикл для всіх сусідніх клітинок
        for(int i=0; i<4; i++){
            newX=current.getX() + moveX[i];
            newY=current.getY() + moveY[i];
            //перевірка чи можливий рух в сусідню клітинку та чи не була вона відвідана
            if(maze->getMaze()[newX][newY]==1 && !visited[newX][newY]){
                //затримка
                Sleep(SLEEP_TIME);
                //збільшуємо кількість кроків на одиницю
                stepsCounter++;
                //для сусідньої клітинки відстань збільшуємо на одиницю
                distances[newX][newY] = distances[current.getX()][current.getY()]+1;
                //позначаємо як відвідану
                visited[newX][newY] = true;
                //виводимо відстань
                gotoXY(1+newY*2, 5+newX);
                cout<<distances[newX][newY];
                //додаємо точку в чергу
                Point newPoint(newX, newY);
                queue.enqueue(newPoint);
            }
        }        
    }
    //якщо алгоритм не знайшов відстань до кінцевої точки, то шлях не існує
    if(distances[maze->rows-2][maze->columns-2]==INFINITY){
        gotoXY(0,3);
        cout<<"Рішення не існує."<<endl;
        return 1;
    }
    //вивід шлях
    drawPath();
    
    return 0;
}

void Bfs::drawPath() const {
    int newX, newY, currentX=maze->rows-2, currentY=maze->columns-2;
    result[currentX][currentY]=2;
    gotoXY(1+currentY*2, 5+currentX);
    color(RED);
    cout<<PATH;
    color(RESET);
    //допоки не дійшли до стартової точки, відстань до якої 0
    while(distances[currentX][currentY]){
        //цикл для всіх сусідніх клітинок
        for(int i=0; i<4; i++){
            newX=currentX+moveX[i];
            newY=currentY+moveY[i];
            //перевірка чи відстань до сусідньої клітинки менша
            if(distances[newX][newY]<distances[currentX][currentY]){
                //позначаємо та виводимо шлях
                result[newX][newY]=2;
                currentX=newX;
                currentY=newY;
                gotoXY(1+currentY*2, 5+currentX);
                color(RED);
                cout<<PATH;
                color(RESET);
                //затримка для покрокового виводу
                Sleep(SLEEP_TIME);
            }
        }
    }
}