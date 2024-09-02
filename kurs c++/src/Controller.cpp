#include "Controller.h"
//змінна вибору пункта меню
unsigned int counter = 0;

void start(){
    //масиви пунктів меню
    string menu[] = {"1.Ввести лабіринт", "2.Стандартний лабіринт", "3.Ввести шлях до файлу з лабіринтом", "4.Вихід"};
    string algMenu[] = {"1.BFS", "2.TwoEndBFS", "3.Ant algorithm", "4.Вирішити власноруч", "5.Назад"};
    
    unsigned int algExit = 0,
    //розміри меню
    sizeMenu = sizeof(menu) / sizeof(menu[0]), 
    sizeAlgMenu = sizeof(algMenu) / sizeof(algMenu[0]);
    
    char key;
    
    while(true){
        
        clearDisplay();
        //вивід головного меню
        printMenu(menu, sizeMenu);

        key = getch();
        //вибір пункта
        if(key == KEY_UP && counter>0){ counter--; }

        if(key == KEY_DOWN && counter <sizeMenu-1){ counter++; }

        if(key == ENTER){
            
            clearDisplay();
            
            Maze maze;
            string path = STD_PATH;
            
            gotoXY(0, 5);
            switch (counter){
            case 0:
                //ввід та перевірка лабіринту
                if(inputMaze(maze) || !isValidMaze(maze)){
                    pressAnyKeyPrompt();
                    continue;
                }
                break;
            case 1:
                //зчитування та перевірка лабіринту зі стандартного файлу
                if(maze.readMaze(path) || !isValidMaze(maze)){
                    pressAnyKeyPrompt();
                    continue;
                }
                break;
            case 2:
                //зчитування та первірка лабіринту
                inputPath(path);
                if(!isValidPath(path)){
                    cout<<"Некоректний шлях до файлу."<<endl;
                    pressAnyKeyPrompt();
                    continue;
                }
            
                if(maze.readMaze(path) || !isValidMaze(maze)){
                    pressAnyKeyPrompt();
                    continue;
                }
                break;
            case 3:
                //вихід
                color(RESET);
                return;
            default:
                break;
            }

            counter=0;
            algExit=0;
            
            while(!algExit){
                
                clearDisplay();
                //вивід меню алгоритмів    
                printMenu(algMenu, sizeAlgMenu);
                
                key = getch();
                //вибір пункта
                if(key == KEY_UP && counter>0){ counter--; }

                if(key == KEY_DOWN && counter<sizeAlgMenu-1){ counter++; }
                
                if(key == ENTER){
                    //створення вказівника батьківського класу, для використання динамічного поліморфізму
                    Solver *solv=nullptr;
                    
                    clearDisplay();

                    gotoXY(0, 5);
                    //створення об'єкта класу наслідника
                    switch (counter){
                    case 0:
                        solv = new Bfs(maze);
                        break;
                    case 1:
                        solv = new TwoEndBfs(maze);
                        break;
                    case 2:
                        solv = new Ant(maze);
                        break;
                    case 3:
                        solv = new UserSolve(maze);
                        break;
                    case 4:
                        counter=0;
                        algExit=1;
                        continue;
                    default:
                        break;
                    }
                    Stopwatch stopwatch;
                    //запуск секундоміра
                    stopwatch.start();
                    //виклик перевантаженої функції
                    solv->solve();
                    //зупинка секундоміра та вивід часу
                    gotoXY(0,1);
                    cout<<"Час від початку рішення: ";
                    cout<<stopwatch.stop();
                    cout<<" секунд"<<endl;
                    //вивід кількості кроків
                    cout<<"Кількість кроків: ";
                    cout<<solv->getStepsCounter()<<endl;
                    //видалення об'єкта
                    delete solv;
                    
                    gotoXY(0, 4);
                    pressAnyKeyPrompt();
                }
            }
        }
    }
}

void printMenu(const string menu[], const unsigned int size){
    //якщо номер пункту збігається з counter то він виводиться червоним
    for(unsigned int i=0; i<size; i++){
            gotoXY(10, 5+i);
            if(counter==i){
                color(RED);
            }else color(RESET);
            cout<<menu[i];
    }
}

void pressAnyKeyPrompt(){
    cout<<"Натисніть будь-яку клавішу..."<<endl;
    getch();
}

int isValidPath(const string &path){
    //патерн шляху до файлу на відновс
    regex pattern(R"(^([a-zA-Z]:\\)?(\\?[a-zA-Z0-9_.-]+)+\\?$)");
    return regex_match(path, pattern);
}

int isValidMaze(Maze &maze){
    //перевірка крайніх стовпців
    for (int i = 0; i < maze.rows; i++) {
        if (maze.getMaze()[i][0] != 0 || maze.getMaze()[i][maze.columns - 1] != 0) {
            cout << "Перший і останній стовпець мають бути заповнені 0." << endl;
            maze.deleteMaze();
            return 0;
        }
    }
    //перевірка крайніх рядків
    for (int j = 0; j < maze.columns; ++j) {
        if (maze.getMaze()[0][j] != 0 || maze.getMaze()[maze.rows - 1][j] != 0) {
            cout << "Перший і останній рядок мають бути заповнені 0." << endl;
            maze.deleteMaze();
            return 0;
        }
    }
    //перевірка початкової клітинки
    if (maze.getMaze()[1][1] != 1) {
            cout << "На початку (1, 1) лабіринту має бути 1." << endl;
            maze.deleteMaze();
            return 0;
    }
    return 1;
}