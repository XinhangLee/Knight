//
// Created by lixh1 on 25-2-11.
//

#ifndef WALL_H
#define WALL_H

#include <common.h>

class Wall : public Collider {
public:
    Wall(const int x, const int y, const int w, const int h) : Collider(x, y, w, h){}
};

inline std::vector<Wall> walls;
template <typename T>
int isColliding(const T& other) {//密码锁
    int code = 0;
    if (walls[0].getCollider()->x + walls[0].getCollider()->w > other.getCollider()->x)
        {code |= 1;}
    if (walls[1].getCollider()->y + walls[1].getCollider()->h > other.getCollider()->y + other.getCollider()->h / 2)
    {code |= 2;}
    if (walls[2].getCollider()->x < other.getCollider()->x + other.getCollider()->w)
        {code |= 4;}
    if (walls[3].getCollider()->y < other.getCollider()->y + other.getCollider()->h)
        {code |= 8;}
    return code;
}

#endif //WALL_H
