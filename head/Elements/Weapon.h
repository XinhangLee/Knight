//
// Created by lixh1 on 25-2-6.
//

#ifndef WEAPON_H
#define WEAPON_H

#include <common.h>
#include <Elements/Bullet.h>
#include <Elements/Wall.h>


class Weapon{
protected:
    mutable Direction dir_weapon;
    Position pos_weapon;
    SDL_Point center_weapon;
    SDL_Point launch_point;
    SDL_Texture *texture;
    const s_bullets *bullet_type;
    std::vector<Bullet *> &bullets;
public:
    explicit Weapon(const s_weapons &);
    virtual ~Weapon();
    void UpdateDir(const double x, const double y) const {dir_weapon = {x - pos_weapon.x, y - pos_weapon.y};}
    void UpdatePos(const double x, const double y) {pos_weapon.x = x;pos_weapon.y = y;}

    [[nodiscard]] double get_dx() const{return dir_weapon.dx;}
    [[nodiscard]] double get_dy() const{return dir_weapon.dy;}
    const s_bullets *getBullet() const {return bullet_type;}
    virtual void render(Position MousePos) const {}
    virtual void Attack() const {}
};

class Weapon_type_1 final :public Weapon{//法杖类武器
public:
    explicit Weapon_type_1(const s_weapons &);
    ~Weapon_type_1() override= default;
    void render(Position MousePos) const override;
    void Attack() const override {bullets.push_back(new Bullet(*bullet_type,
            {pos_weapon.x - center_weapon.x + launch_point.x,
                        pos_weapon.y - center_weapon.y + launch_point.y},dir_weapon));}
};



#endif //WEAPON_H
