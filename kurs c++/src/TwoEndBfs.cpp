#include "TwoEndBfs.h"

TwoEndBfs::TwoEndBfs(Maze &maze) : Solver(maze) {
    //перевірка на ініціалізацію
    if(!maze.getMaze()) {
        distances=nullptr;
        distancesEnd=nullptr;
        visited=nullptr; 
    } else {
        //виділення пам'яті
        try{
            distances=new int*[maze.rows];
            distancesEnd=new int*[maze.rows];
            visited=new int*[maze.rows];
            for(int i=0; i<maze.rows; i++){
                distances[i]=new int[maze.columns]();
                distancesEnd[i]=new int[maze.columns]();
                visited[i]=new int[maze.columns]();
                for(int j=0; j<maze.columns; j++){
                    distances[i][j]=INFINITY;
                    distancesEnd[i][j]=INFINITY;
                    visited[i][j]=false;
                }
            }
        } catch(const bad_alloc &e){
            cerr<<"Помилка виділення пам'яті: " << e.what() << endl;
            //очищення виділеної пам'яті в разі помилки
            deleteArray(&distances);
            deleteArray(&distancesEnd);
            deleteArray(&visited);
        }
    }
}

TwoEndBfs::~TwoEndBfs(){
    deleteArray(&distances);
    deleteArray(&distancesEnd);
    deleteArray(&visited);
}

void TwoEndBfs::deleteArray(int*** array){
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

int TwoEndBfs::solve(){
    //перевірка на ініціалізацію
    if(!maze) { return 1; }
    //вивід лабіринту
    printMaze(maze);
    //створення черги
    Queue queue(maze->rows * maze->columns);
    //початкова точка
    Point src(1, 1);
    //кінцева точка точка
    Point dst(maze->rows-2, maze->columns-2);
    //додавання початкової точки в чергу
    queue.enqueue(src);
    //додавання кінцевої точки в чергу
    queue.enqueue(dst);
    //призначення 0 як відстані до початкової та кінцевої точок
    //позначення їх як відвіданих, 1 для точок, що почалися з початку, 2 для точок, що почалися з кінця
    distances[src.getX()][src.getY()] = 0;
    visited[src.getX()][src.getY()] = 1;
    gotoXY(1 + src.getY() * 2, 5 + src.getX());
    cout << distances[src.getX()][src.getY()];

    distancesEnd[dst.getX()][dst.getY()] = 0;
    visited[dst.getX()][dst.getY()] = 2;
    gotoXY(1 + dst.getY() * 2, 5 + dst.getX());
    cout << distancesEnd[dst.getX()][dst.getY()];

    int intersection = 0;
    int currentX, currentY, currentEndX, currentEndY;
    //цикл, доки черга не пуста або bfs не перетнуться
    while (!queue.isEmpty() && !intersection) {
        //береться точка з черги
        Point current = queue.dequeue();
        //вибір масивів і позначень відвідуваності в залежності від bfs початку чи кінця
        int **currentDistances = (visited[current.getX()][current.getY()] == 1) ? distances : distancesEnd;
        int flag = (visited[current.getX()][current.getY()] == 1) ? 1 : 2;
        int otherFlag = (visited[current.getX()][current.getY()] == 1) ? 2 : 1;
        //цикл для всіх сусідніх клітинок
        for (int i = 0; i < 4; i++) {
            int newX = current.getX() + moveX[i];
            int newY = current.getY() + moveY[i];
            //перевірка чи можливий рух в сусідню клітинку та чи не була вона відвідана
            if (maze->getMaze()[newX][newY] == 1) {
                //якщо точка була відвідана іншим bfs, то bfs перетнулися
                if (visited[newX][newY] != otherFlag) {
                    if (visited[newX][newY] == 0) {
                        //затримка
                        Sleep(SLEEP_TIME);
                        //збільшуємо кількість кроків на одиницю
                        stepsCounter++;
                        //для сусідньої клітинки відстань збільшуємо на одиницю
                        currentDistances[newX][newY] = currentDistances[current.getX()][current.getY()] + 1;
                        //позначаємо як відвідану
                        visited[newX][newY] = flag;
                        //виводимо відстань
                        gotoXY(1 + newY * 2, 5 + newX);
                        cout << currentDistances[newX][newY];
                        //додаємо точку в чергу
                        queue.enqueue(Point(newX, newY));
                    }
                } else {
                    //запам'ятовування точки перетину
                    currentX=newX;
                    currentY=newY;
                    currentEndX=newX;
                    currentEndY=newY;
                    intersection=1;
                }
            }
        }
    }
    //якщо не пертнулися, а черга порожня, то рішення не існує
    if(!intersection) {
        gotoXY(0, 3);
        cout<<"Рішення не існує."<<endl;    
        return 1;
    }
    //вивід шляху
    drawPath(distances, currentX, currentY);
    drawPath(distancesEnd, currentEndX, currentEndY);

    return 0;
}

void TwoEndBfs::drawPath(int **dist, int curX, int curY) const{
    result[curX][curY]=2;
    gotoXY(1+curY*2, 5+curX);
    color(RED);
    cout<<PATH;
    color(RESET);
    //допоки не дійшли до стартової точки для bfs, відстань до якої 0
    while(dist[curX][curY]!=0){
        //цикл для всіх сусідніх клітинок
        for(int i=0; i<4; i++){
            int newX=curX+moveX[i];
            int newY=curY+moveY[i];
            //перевірка чи відстань до сусідньої клітинки менша
            if(dist[newX][newY]<dist[curX][curY]){
                //позначаємо та виводимо шлях
                result[newX][newY]=2;
                curX=newX;
                curY=newY;
                gotoXY(1+curY*2, 5+curX);
                color(RED);
                cout<<PATH;
                color(RESET);
                //затримка для покрокового виводу
                Sleep(SLEEP_TIME);
            }
        }
    }
}