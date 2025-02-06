//
// Created by lixh1 on 25-2-6.
//

#ifndef MONSTER_H
#define MONSTER_H

#include <common.h>
#include <Elements/Weapon.h>

class Monster {
    int HP;
    double Speed;
    // Weapon weapon;
    Position pos;
public:
    Monster();
    ~Monster();
    // void Move();
    // void Attack();
};

#endif //MONSTER_H
