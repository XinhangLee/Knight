//
// Created by lixh1 on 25-2-6.
//
#include <Elements/Monster.h>

Monster_type2 *monster_1;

Monster::Monster(const int HP, const int attack_power, const int range, const double speed_monster,
    const Position pos_monster, const SDL_Point center_monster):HP(HP), speed_monster(speed_monster),
attack_power(attack_power), range(range), center_monster(center_monster), dir_monster(0.0,0.0) ,pos_monster(pos_monster){
    int angle = dis(gen);
    angle = angle % 360 - 180;
    dir_monster.dx = cos(angle);
    dir_monster.dy = sin(angle);
}
Monster::~Monster() = default;
void Monster::UpdateDir(const Hero &hero) {
    if (Distance(pos_monster, hero.getPos()) <= range) {
        dir_monster = {hero.getX() - pos_monster.x, hero.getY() - pos_monster.y};
    }
}
void Monster::Hurt(const int attack) {
    if (HP >= 0) {
        if (HP - attack >= 0)
            HP -= attack;
        else
            HP = 0;
    }
}


Monster_type2::Monster_type2(const int HP, const int attack_power, const int range, const double speed_monster,
    const Position pos_monster, const SDL_Point center_monster, const std::string &Path , const s_weapons &w):
    Monster(HP, attack_power, range, speed_monster, pos_monster, center_monster),Timer(w.time_gap),
    Collider(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y,49,81),
    texture(nullptr), frame_num(7), current_frame(0), weapon(w, bullets_monster), alive(true) {
    LoadImage(texture, Path);
}
Monster_type2::~Monster_type2() {
    SDL_DestroyTexture(texture);
}
void Monster_type2::Move(const Hero &h) {
    UpdateDir(h);
    if (Distance(pos_monster, h.getPos()) >= 200.0) {
        if (const double len = sqrt(pow(dir_monster.dx, 2) + pow(dir_monster.dy, 2)); len != 0.0) {
            pos_monster.x += dir_monster.dx / len * speed_monster;
            pos_monster.y += dir_monster.dy / len * speed_monster;
        }
    }
    else {
        weapon.setDir(dir_monster.dx, dir_monster.dy);
        attack();
    }
    setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
}

void Monster_type2::Die() {
    alive = false;
}
void Monster_type2::Render() const {
    if (texture) {
        const SDL_Rect srcrect = {current_frame * 49, 0, 49, 81};
        SDL_RenderCopy(app.renderer, texture, &srcrect, getCollider());
    }
    weapon.UpdatePos(pos_monster.x + 2 , pos_monster.y + 16);
    weapon.render();
}




// 暂时失败
Monster_type1::Monster_type1(const int HP, const int attack_power, const int range, const double speed_monster,
    const Position pos_monster, const SDL_Point center_monster, const std::string &Path):
    Monster(HP, attack_power, range, speed_monster, pos_monster, center_monster),
    Collider(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y, 150, 150),
    texture(nullptr),frame_num(5), current_frame(0), row(0), alive(true) {
    LoadImage(texture, Path);
}
Monster_type1::~Monster_type1() {
    SDL_DestroyTexture(texture);
}
void Monster_type1::Move(const Hero &hero) {
    UpdateDir(hero);
    int a = 0;
    if (Distance(pos_monster, hero.getPos()) <= 10.0) {
        setSpeed(2);
        a = 1;
    }
    if (std::abs(dir_monster.dx) > std::abs(dir_monster.dy)) {
        if (dir_monster.dx <= 0) {
            row = a * 4 + 0;
        }
        else {
            row = a * 4 + 1;
        }
    }
    else {
        if (dir_monster.dy <= 0) {
            row = a * 4 + 2;
        }
        else {
            row = a * 4 + 3;
        }
    }
    if (const double len = sqrt(std::pow(dir_monster.dx, 2) + std::pow(dir_monster.dy, 2)); len != 0.0) {
        pos_monster.x += dir_monster.dx / len * speed_monster;
        pos_monster.y += dir_monster.dy / len * speed_monster;
    }
    setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
    current_frame = (current_frame + 1) % frame_num;
}
void Monster_type1::Die() {
    alive = false;
    current_frame = 0;
    if (std::abs(dir_monster.dx) > std::abs(dir_monster.dy)) {
        if (dir_monster.dx <= 0) {
            row = 8;
        }
        else {
            row = 9;
        }
    }
    else {
        if (dir_monster.dy <= 0) {
            row = 10;
        }
        else {
            row = 11;
        }
    }
}
void Monster_type1::Render() const {
    const SDL_Rect srcrect = {current_frame * 40, row * 40, 40, 40};
    SDL_RenderCopy(app.renderer, texture, &srcrect, getCollider());
    if (!alive && current_frame == frame_num) {
        delete this;
    }
}
