//
// Created by lixh1 on 25-2-6.
//

#ifndef WEAPON_H
#define WEAPON_H

#include <common.h>

class Bullet {
    Position Pos;
    Direction Dir;
    double speed;
    SDL_Texture *texture;
    int currentFrame;
    int FrameCount;
    double degree;
    mutable SDL_Rect rect;
    mutable bool is_first;
public:
    Bullet(const std::string &imagePath, double speed, Direction Dir, Position Pos,
            int FrameCount, double degree);
    ~Bullet();
    void Update();
    void render() const;
    SDL_Rect &GetRect() const{return rect;}
    bool isFirst() const{return is_first;}
};

extern std::vector<Bullet*> initial_bullets;

class Weapon{
    int AttackPower;
    int EnergyConsumed;
    Direction Dir;
    Position Pos;
    SDL_Texture *texture;
    std::vector<Bullet *> &bullets;
public:
    explicit Weapon(const std::string &imagePath);
    ~Weapon();
    void UpdateDir(const double x, const double y){Dir = {x - Pos.x, y - Pos.y};}
    void UpdatePos(const double x, const double y) {Pos.x = x;Pos.y = y;}
    void render(Position MousePos) const;
    [[nodiscard]] double get_dx() const{return Dir.dx;}
    [[nodiscard]] double get_dy() const{return Dir.dy;}
    void Attack() const {
        bullets.push_back(new Bullet("../rsc/Fireball.png", 8.0, Dir, {Pos.x + 25, Pos.y + 40}, 6, getDegree(Dir)));}
    [[nodiscard]] int get_EnergyConsumed() const{return EnergyConsumed;}
};



#endif //WEAPON_H
