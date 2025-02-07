//
// Created by lixh1 on 25-2-6.
//

#ifndef HERO_H
#define HERO_H

#include <common.h>
#include <Elements/Weapon.h>

class Hero {
    /*  []:
     *     0 : 总量
     *     1 : 余量
     */
    int HP[2];
    int shield[2];
    int energy[2];
    double speed;
    Weapon *weapon;
    Position pos;
    SDL_Texture *texture[5];
public:
    Hero(SDL_Renderer *renderer, const std::string &imagePath);
    ~Hero();
    void render(SDL_Renderer *renderer);
    void Move(double dx, double dy);
//    void Attack();

    [[nodiscard]] int getHP() const{return HP[1];}
    [[nodiscard]] int getShield() const{return shield[1];}
    [[nodiscard]] int getEnergy() const{return energy[1];}
    [[nodiscard]] double getX() const{return pos.x;}
    [[nodiscard]] double getY() const{return pos.y;}
    [[nodiscard]] double getSpeed() const{return speed;}
    [[nodiscard]] Weapon *getWeapon() const{return weapon;}
    void setWeapon(Weapon *w){weapon = w;}
};

extern Hero *hero;


#endif //HERO_H
