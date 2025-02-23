//
// Created by lixh1 on 25-2-11.
//
#include <Stash.h>


s_bullets const bullet_1 = {
    3,
    2,
    200,
    {8,8},
    8.0,
    6,
    "../rsc/bullet/Fireball.png"
};
s_bullets const bullet_2 = {
    3,
    0,
    500,
    {18,9},
    8.0,
    1,
    "../rsc/bullet/projectile.png"
};
s_bullets const bullet_3 = {
    3,
    0,
    500,
    {8,8},
    8.0,
    6,
    "../rsc/bullet/Darkness Bolt.png"
};
s_bullets const bullet_4 = {
    1,
    4,
    500,
    {8,8},
    8.0,
    6,
    "../rsc/bullet/Magic Orb.png"
};
s_weapons const weapon_1 = {
    {16,16},
    {27,4},
    &bullet_1,
    "../rsc/weapon/staff1.png"
};
s_weapons const weapon_2{
    {16,16},
    {27,4},
    &bullet_3,
    "../rsc/weapon/staff2.png"
};
s_heroes const hero_1 = {
    {100,100},
    {8,8},
    {200,200},
    6.0,
    {750,460},
    {25,41},
    {27,57},
    &weapon_1,
    7,
    "../rsc/hero/hero_Idle_1.png",
    "../rsc/hero/hero_Walk_1.png"
};
s_heroes const hero_2 = {
    {100,100},
    {8,8},
    {250,250},
    5.0,
    {750,460},
    {25,41},
    {27,57},
    &weapon_1,
    7,
    "../rsc/hero/hero_Idle_2.png",
    "../rsc/hero/hero_Walk_2.png"
};
int walls_1[4][4] = {
    {307, 60, 61, 880},//left
    {307, 60, 885, 62},//up
    {1132, 60, 61, 880},//right
    {307, 880, 885, 60}//down
};