//
// Created by lixh1 on 25-2-6.
//
#include <Elements/Weapon.h>

Weapon::Weapon(SDL_Renderer * renderer, const std::string &imagePath): AttackPower(3),
                    EnergyConsumed(2),
                    AttackSpeed(4.5),
                    Dir{1.0,0.0},
                    Pos{0.0,0.0},
                    texture(nullptr) {
    LoadImage(this->texture, renderer, imagePath, "Weapon");
}
Weapon::~Weapon() {
    SDL_DestroyTexture(texture);
}

// 返回值是一个角度，用角度制，如45
double Weapon::UpdateDir(const double x, const double y) const {
    const Position dir = {x - Pos.x, y - Pos.y};
    const double radians = atan(dir.y / dir.x);
    const double degree = radians * (180.0f / M_PI);
    return degree;
}


void Weapon::render(SDL_Renderer *renderer, const Position MousePos) const {
    const SDL_Rect rect = {static_cast<int>(Pos.x) + 7, static_cast<int>(Pos.y) + 37, 48, 12 };
    constexpr SDL_Point center = {24,4};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (MousePos.x - Pos.x > 0)
        flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, UpdateDir(MousePos.x, MousePos.y), &center, flip);
}


