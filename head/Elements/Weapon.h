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
    Position Pos;
    SDL_Texture *texture;
public:
    Weapon(SDL_Renderer *renderer, const std::string &imagePath);
    ~Weapon();
    double UpdateDir(double, double) const;
    void UpdatePos(double, double);
    void render(SDL_Renderer *renderer, Position MousePos) const;
    [[nodiscard]] double get_dx() const{return Dir.dx;}
    [[nodiscard]] double get_dy() const{return Dir.dy;}
};

#endif //WEAPON_H
