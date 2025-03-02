//
// Created by lixh1 on 25-2-21.
//
#include <Level.h>

Position ran_pos() {
    Position p;
    std::uniform_int_distribution dis1(walls[0].getCollider()->x + walls[0].getCollider()->w, walls[2].getCollider()->x);
    p.x = dis1(gen);
    std::uniform_int_distribution dis2(walls[1].getCollider()->y + walls[1].getCollider()->h, walls[3].getCollider()->y);
    p.y = dis2(gen);
    return p;
}
int ran_num(const int min, const int max) {
    std::uniform_int_distribution dis(min, max);
    const int num = dis(gen);
    return num;
}

Level *level = nullptr;

Level::Level() : Timer(2000), pass(false), running(false){
    last_time = SDL_GetTicks();
}
Level::~Level() = default;

void Level1::run() {
    if (!pass[0]) {
        if (Time_out()){
            int num1 = ran_num(1,3);
            while (num1--) {
                monster.push_back(new Skull(init_monsters("Skull"), ran_pos()));
            }
            int num2 = ran_num(1,3);
            while (num2--) {
                monster.push_back(new Demon_Bat(init_monsters("Demon_Bat"), ran_pos()));
            }
            running[0] = true;
        }
    }
    else if (!pass[1]) {
        if (Time_out()) {
            Mix_FreeMusic(music);
            Load_Music(music, "../rsc/mixer/Final Solitaire.wav");
            int num1 = ran_num(4,6);
            while (num1--) {
                monster.push_back(new Skull(init_monsters("Skull"), ran_pos()));
            }
            int num2 = ran_num(4,6);
            while (num2--) {
                monster.push_back(new Demon_Bat(init_monsters("Demon_Bat"), ran_pos()));
            }
            running[1] = true;
        }
    }
    else if (!pass[2]) {
        if (Time_out()) {
            Mix_FreeMusic(music);
            Load_Music(music, "../rsc/mixer/Dragon Dance.wav");
            monster.push_back(new COVID_19(init_monsters("COVID_19"),{750,500}));
            int num1 = ran_num(3,5);
            while (num1--) {
                monster.push_back(new Skull(init_monsters("Skull"), ran_pos()));
            }
            int num2 = ran_num(3,5);
            while (num2--) {
                monster.push_back(new Demon_Bat(init_monsters("Demon_Bat"), ran_pos()));
            }
            running[2] = true;
        }
    }
}

