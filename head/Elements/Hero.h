//
// Created by lixh1 on 25-2-6.
//

#ifndef HERO_H
#define HERO_H

#include <common.h>
#include <Elements/Weapon.h>


class Hero {
    int HP;
    int shield;
    int energy;
    double speed;
//    Weapon weapon;
    Position pos;
    SDL_Texture* texture;
public:
    Hero(SDL_Renderer *renderer, const std::string &imagePath);
    ~Hero();
    void render(SDL_Renderer *renderer) const;
    void Move(double dx, double dy);
//    void Attack();

    int getHP() const{return HP;}
    int getShield() const{return shield;}
    int getEnergy() const{return energy;}
    double getX() const{return pos.x;}
    double getY() const{return pos.y;}
};



#endif //HERO_H
