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
    bool alive;
public:
    Monster(int, int, int, double, Position, SDL_Point);
    virtual ~Monster();
    void UpdateDir(const Hero &);
    void UpdateDirRandom();
    void Hurt(int);
    void setSpeed(const int a){speed_monster *= a;}
    [[nodiscard]] bool getAlive() const{return alive;}
    [[nodiscard]] Position getPos() const{return pos_monster;}
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


// 法杖类怪物
class Monster_type2 final : public Monster, public Collider ,public Timer{
    SDL_Texture *texture;
    int frame_num;
    int current_frame;
    Weapon_type_1 weapon;
public:
    Monster_type2(int, int, int, double, Position, SDL_Point, const std::string &, const s_weapons &);
    ~Monster_type2() override;
    void Move(const Hero &);
    void Die();
    void Render() const;
    void attack() const {if (Time_out())weapon.Attack();}
};
extern std::vector<Monster_type2 *> monster_1;

#endif //MONSTER_H
