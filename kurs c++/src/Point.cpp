#include "Point.h"

Point::Point(){
    x=-1; 
    y=-1;
}

Point::Point(const int i, const int j){
    x=i; 
    y=j;
}
//гетери
int Point::getX() const { return x; }
int Point::getY() const { return y; }