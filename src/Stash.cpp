//
// Created by lixh1 on 25-2-11.
//
#include <Stash.h>


s_bullets const bullet_1 = {
    3,
    2,
    {8,8},
    10.0,
    6,
    "../rsc/Fireball.png"
};
s_weapons const weapon_1 = {
    200,
    {16,16},
    {16,6},
    &bullet_1,
    "../rsc/Aqua Staff.png"
};
s_heroes const hero_1 = {
    {5,5},
    {5,5},
    {1000,1000},
    6.0,
    {750,460},
    {25,41},
    {27,57},
    &weapon_1,
    7,
    "../rsc/hero_Idle_1.png",
    "../rsc/hero_Walk_1.png"
};
s_heroes const hero_2 = {
    {5,5},
    {5,5},
    {250,250},
    3.0,
    {750,460},
    {25,41},
    {27,57},
    &weapon_1,
    7,
    "../rsc/hero_Idle_2.png",
    "../rsc/hero_Walk_2.png"
};
int walls_1[4][4] = {
    {307, 60, 61, 880},//left
    {307, 60, 885, 62},//up
    {1132, 60, 61, 880},//right
    {307, 880, 885, 60}//down
};