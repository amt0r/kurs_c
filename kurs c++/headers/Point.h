#ifndef _POINT_H_
#define _POINT_H_

class Point{
    //координати
    int x;
    int y;
public:
    Point();
    Point(const int i, const int j);
    //гетери
    int getX() const;
    int getY() const;
};
 
#endif