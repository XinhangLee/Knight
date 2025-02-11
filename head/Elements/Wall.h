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
int isColliding(const T& other) {
    int code = 0;
    if (std::abs(walls[0].getCollider()->x + walls[0].getCollider()->w / 2 - other.getCollider()->x - other.getCollider()->w / 2) <
            std::min(walls[0].getCollider()->w / 2, other.getCollider()->w / 2))
        {code |= 1;}
    if (std::abs(walls[2].getCollider()->x + walls[2].getCollider()->w / 2 - other.getCollider()->x - other.getCollider()->w / 2) <
            std::min(walls[2].getCollider()->w / 2, other.getCollider()->w / 2))
        {code |= 4;}
    if (std::abs(walls[1].getCollider()->y + walls[1].getCollider()->h / 2 - other.getCollider()->y - other.getCollider()->h / 2) <
            std::min(walls[1].getCollider()->h / 2, other.getCollider()->h / 2))
        {code |= 2;}
    if (std::abs(walls[3].getCollider()->y + walls[3].getCollider()->h / 2 - other.getCollider()->y - other.getCollider()->h / 2) <
            std::min(walls[3].getCollider()->h / 2, other.getCollider()->h / 2))
        {code |= 8;}
    return code;
}

#endif //WALL_H
