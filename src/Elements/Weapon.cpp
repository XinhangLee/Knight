//
// Created by lixh1 on 25-2-6.
//
#include <Elements/Weapon.h>

std::vector<Bullet*> initial_bullets;

Weapon::Weapon(const s_weapons &w): attack_power(w.attack_power), energy_consumed(w.energy_consumed), dir_weapon{1.0, 0.0},pos_weapon{0.0, 0.0},
    center_weapon(w.center_weapon), launch_point(w.launch_point), texture(nullptr), bullet_type(w.bullet_type), bullets(initial_bullets)
{
    LoadImage(this->texture, w.Path);
}

Weapon::~Weapon()
{
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Weapon::render(const Position MousePos) const
{
    UpdateDir(MousePos.x, MousePos.y);
    const SDL_Rect rect = {static_cast<int>(pos_weapon.x) - center_weapon.x, static_cast<int>(pos_weapon.y) - center_weapon.y, 32, 32 };
    // constexpr SDL_Point center = {12, 8};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (MousePos.x - pos_weapon.x < 0)
        flip = SDL_FLIP_HORIZONTAL;
    // SDL_RenderCopyEx(app.renderer, texture, nullptr, &rect, getDegree(Dir), &center, flip);
    SDL_RenderCopyEx(app.renderer, texture, nullptr, &rect, 0.0, nullptr, flip);
    if (!bullets.empty()) {
        for (auto it = bullets.begin(); it != bullets.end();) {
            if (const auto bullet = *it; bullet->GetRect().x >= 1237 || bullet->GetRect().x <= 246 || bullet->GetRect().y >= 984 || bullet->GetRect().y <= 0) {
                delete bullet;
                it = bullets.erase(it);
            }
            else {
                if (bullet->isFirst())
                    bullet->render();
                else {
                    bullet->Update();
                    bullet->render();
                }
                ++it;
            }
        }
    }
}
