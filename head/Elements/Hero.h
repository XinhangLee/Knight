//
// Created by lixh1 on 25-2-6.
//

#ifndef HERO_H
#define HERO_H

#include <common.h>
#include <Elements/Weapon.h>

inline Uint32 time1 = 0;
inline Uint32 time2 = 0;

class Hero final : public Collider, public Timer{
    /*  []:
     *     0 : 总量
     *     1 : 余量
     */
    mutable int HP[2];
    mutable int shield[2];
    int energy[2];
    double speed;
    Position pos_hero;
    SDL_Point center_hero;        //英雄坐标记录点
    SDL_Point weapon_point;       //武器中心重合点
    mutable Direction dir_hero;
    mutable Direction dir_attack;
    int frame_num;
    int currentframe;
    Weapon *weapon;
    s_weapons weapon_type;
    SDL_Texture *texture[4];
public:
    explicit Hero(const s_heroes &);
    ~Hero() override;
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
    void Sub_energy(int x);
    void Hurt(int x) const;
    void UpdateDir(Position p) const;
    const s_weapons *getWeaponType() const {return &weapon_type;}
    SDL_Point getWeaponPoint() const {return {weapon_point.x - center_hero.x, weapon_point.y - center_hero.y};}
    Position getPos() const {return pos_hero;}
    void attack() const;
    Direction get_DirAttack() const {return  dir_attack;}
    Direction get_Dir() const {return dir_hero;}
};

extern Hero *hero;


#endif //HERO_H
