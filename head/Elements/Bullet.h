//
// Created by lixh1 on 25-2-11.
//

#ifndef BULLET_H
#define BULLET_H

#include <common.h>
#include <Stash.h>

class Bullet {
    Position pos_bullet;
    SDL_Point center_bullet;
    Direction dir_bullet;
    double speed_bullet;
    int frame_current;
    int frame_num;
    SDL_Texture *texture;
    mutable SDL_Rect dstrect_bullet;
    mutable bool is_first;
public:
    Bullet(const s_bullets &bullet, Position pos_bullet, Direction dir_bullet);
    ~Bullet();
    void Update();
    void render() const;
    SDL_Rect &GetRect() const{return dstrect_bullet;}
    bool isFirst() const{return is_first;}
};

extern std::vector<Bullet*> initial_bullets;

#endif //BULLET_H
