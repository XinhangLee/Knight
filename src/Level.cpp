//
// Created by lixh1 on 25-2-21.
//
#include <Level.h>

Level *level = nullptr;

Level::Level() : Timer(2000), pass(false), running(false){
    last_time = SDL_GetTicks();
}
Level::~Level() = default;

void Level1::run() {
    if (!pass[0]) {
        if (Time_out()){
            monster.push_back(new Monster_type3(1,200,3.5,{400,150},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{600,800},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{700,300},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{900,400},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1000,200},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1100,600},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            running[0] = true;
        }
    }
    else if (!pass[1]) {
        if (Time_out()) {
            Mix_FreeMusic(music);
            Load_Music(music, "../rsc/mixer/Final Solitaire.wav");
            monster.push_back(new Monster_type3(1,200,3.5,{400,150},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{600,800},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{700,300},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{900,400},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1000,200},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1100,600},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{500,186},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{649,582},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{826,672},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{462,852},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1059,496},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1000,300},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            running[1] = true;
        }
    }
    else if (!pass[2]) {
        if (Time_out()) {
            Mix_FreeMusic(music);
            Load_Music(music, "../rsc/mixer/Dragon Dance.wav");
            monster.push_back(new Monster_type3(1,200,3.5,{400,150},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{600,800},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{700,300},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{900,400},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1000,200},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1100,600},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{500,186},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{649,582},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type3(1,200,3.5,{826,672},{41,36},"../rsc/monster/Demon bat.png", init_bullets("bullet_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{462,852},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1059,496},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type2(1,200,3.5,{12,12},{1000,300},{24,24},"../rsc/monster/ghost.png",init_weapons("weapon_2")));
            monster.push_back(new Monster_type4(100,200,6.0,{750,500},{111,123}));
            running[2] = true;
        }
    }
}

