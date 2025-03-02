//
// Created by lixh1 on 25-2-11.
//

#ifndef STASH_H
#define STASH_H

#include <common.h>

typedef struct s_heroes s_heroes;
typedef struct s_weapons s_weapons;
typedef struct s_bullets s_bullets;

// extern s_weapons const weapon_1;
// extern s_weapons const weapon_2;

// extern s_heroes const hero_1;
// extern s_heroes const hero_2;

extern int walls_1[4][4];

struct s_bullets{
    int attack_power;
    int energy_consumed;
    Uint32 time_gap;
    SDL_Point center_bullet;
    double speed_bullet;
    int frame_num;
    std::string path;
};
struct  s_weapons{
    SDL_Point center_weapon;
    SDL_Point launch_point;
    s_bullets bullet_type;
    std::string path;
};
struct s_heroes{
    int HP[2];
    int shield[2];
    int energy[2];
    double speed;
    Position pos_hero;
    SDL_Point center_hero;
    SDL_Point weapon_point;
    s_weapons weapon_type;
    int frame_num;
    std::string StablePath;
    std::string WalkPath;
};

s_bullets init_bullets(const std::string& type);
s_weapons init_weapons(const std::string& type);
s_heroes init_heroes(const std::string& type);
#endif //STASH_H
