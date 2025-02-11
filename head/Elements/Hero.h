//
// Created by lixh1 on 25-2-6.
//

#ifndef HERO_H
#define HERO_H

#include <common.h>
#include <Elements/Weapon.h>
#include <Stash.h>

class Hero : public Collider{
    /*  []:
     *     0 : 总量
     *     1 : 余量
     */
    int HP[2];
    int shield[2];
    int energy[2];
    double speed;
    Position pos_hero;
    SDL_Point center_hero;
    mutable Direction dir_hero;
    int frame_num;
    int currentframe;
    Weapon *weapon;
    const s_weapons *weapon_type;
    SDL_Texture *texture[4];
public:
    explicit Hero(const s_heroes &);
    ~Hero();
    void render(Position);
    void Move(double, double);
    void Move(Position);
    [[nodiscard]] int getHP() const{return HP[1];}
    [[nodiscard]] int getShield() const{return shield[1];}
    [[nodiscard]] int getEnergy() const{return energy[1];}
    [[nodiscard]] double getX() const{return pos_hero.x;}
    [[nodiscard]] double getY() const{return pos_hero.y;}
    [[nodiscard]] double getSpeed() const{return speed;}
    [[nodiscard]] Weapon *getWeapon() const{return weapon;}
    void setWeapon(Weapon *w){weapon = w;}
    void Sub_energy(const int dx){energy[1] -= dx;}
    void UpdateDir(const Position p) const {dir_hero = {p.x - pos_hero.x,p.y - pos_hero.y };}
    const s_weapons *getWeaponType() const {return weapon_type;}
};

extern Hero *hero;


#endif //HERO_H
