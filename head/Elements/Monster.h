//
// Created by lixh1 on 25-2-6.
//

#ifndef MONSTER_H
#define MONSTER_H

#include <common.h>
#include <Elements/Weapon.h>

#include "Hero.h"

inline std::random_device rd;
inline std::mt19937 gen(rd());
inline std::uniform_int_distribution dis(0, 360);

class Monster {
protected:
    int HP;
    double speed_monster;
    int attack_power;
    int range;
    SDL_Point center_monster;
    Direction dir_monster;
    Position pos_monster;
public:
    Monster(int, int, int, double, Position, SDL_Point);
    virtual ~Monster();
    void UpdateDir(const Hero &);
    void Hurt(int);
    void setSpeed(const int a){speed_monster *= a;}
};
// 碰撞型
class Monster_type1 final : public Monster, public Collider {
    SDL_Texture *texture;
    int frame_num;
    int current_frame;
    int row;
    bool alive;
    public:
    Monster_type1(int, int, int, double, Position, SDL_Point, const std::string &Path);
    ~Monster_type1() override;
    void Move(const Hero &);
    void Die();
    void Render() const;
};
extern Monster_type1 *monster_1;

#endif //MONSTER_H
