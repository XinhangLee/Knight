//
// Created by lixh1 on 25-2-11.
//

#ifndef BULLET_H
#define BULLET_H

#include <common.h>
#include <Stash.h>

class Bullet :public Collider{
    int attack_power;
    int energy_consumed;
    Position pos_bullet;
    SDL_Point center_bullet;
    Direction dir_bullet;
    double speed_bullet;
    int frame_current;
    int frame_num;
    SDL_Texture *texture;
    mutable bool is_first;
public:
    Bullet(const s_bullets &bullet, Position pos_bullet, Direction dir_bullet);
    ~Bullet();
    void Update();
    void render();
    bool isFirst() const{return is_first;}
    Position GetPos() const{return pos_bullet;}
};

extern std::vector<Bullet*> bullets_hero;
extern std::vector<Bullet*> bullets_monster;

#endif //BULLET_H
