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

class Monster :public Collider ,public Timer{
protected:
    int HP;
    double speed_monster;
    int range;
    SDL_Point center_monster;
    Direction dir_monster;
    Position pos_monster;
    bool alive;
    bool to_delete;
public:
    Monster(int, int, double, Position, SDL_Point);
    ~Monster() override;
    virtual void Move(const Hero&){}
    void UpdateDir(const Hero &);
    void UpdateDirRandom();
    void Hurt(int);
    virtual void Die();
    virtual void Render(){}
    void setSpeed(const int a){speed_monster *= a;}
    bool getDelete() const{return to_delete;}
    [[nodiscard]] Position getPos() const{return pos_monster;}
};




// 法杖类怪物
class Monster_type2 final : public Monster{
    SDL_Texture *texture;
    int frame_num;
    int current_frame;
    SDL_Point staff_point;
    Weapon_type_1 weapon;
public:
    Monster_type2(int, int, double,SDL_Point, Position, SDL_Point, const std::string &, const s_weapons &);
    ~Monster_type2() override;
    void Move(const Hero &) override;
    void Render() override;
    void attack() const {if (Time_out())weapon.Attack();}
};

// 恶魔蝙蝠
class Monster_type3 final : public Monster{
    SDL_Texture *texture;
    int frame_num[3];
    int current_frame[3];
    int row;
    bool mode_attack;
    s_bullets bullet;
public:
    Monster_type3(int, int, double, Position, SDL_Point, const std::string &, const s_bullets &);
    ~Monster_type3() override;
    void Move(const Hero &) override;
    void Render() override;
    void render_move() const;
    void render_attack();
    void render_death();
    void attack() const;
    void Die() override;
};

// Boss: COVID-19
class Monster_type4 final : public Monster {
    int HP_total;
    SDL_Texture *texture[6];
    int row[2];
    int current_frame[4];
    s_bullets bullet;
    bool mode[3];// 记录该模式是否结束。
    int times;
public:
    Monster_type4(int, int, double, Position, SDL_Point);
    ~Monster_type4() override;
    void Move(const Hero &) override;
    void Render() override;
    void attack() const;
    void Die() override {alive = false;}
    void UpdateAnimation();
};


extern std::vector<Monster *> monster;


// // 碰撞型
// class Monster_type1 final : public Monster, public Collider {
//     SDL_Texture *texture;
//     int frame_num;
//     int current_frame;
//     int row;
//     bool alive;
//     public:
//     Monster_type1(int, int, int, double, Position, SDL_Point, const std::string &Path);
//     ~Monster_type1() override;
//     void Move(const Hero &);
//     void Die();
//     void Render() const;
// };

#endif //MONSTER_H
