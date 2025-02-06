//
// Created by lixh1 on 25-2-6.
//

#ifndef WEAPON_H
#define WEAPON_H

#include <common.h>

class Weapon{
    int AttackPower;
    int EnergyConsumed;
    double AttackSpeed;
    Direction Dir;
public:
    // Weapon();
    // ~Weapon();
    // Direction UpdateDir();
    [[nodiscard]] double get_dx() const{return Dir.dx;}
    [[nodiscard]] double get_dy() const{return Dir.dy;}
};

#endif //WEAPON_H
