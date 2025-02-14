//
// Created by lixh1 on 25-2-6.
//

#include <Elements/Weapon.h>


Weapon::Weapon(const s_weapons &w): dir_weapon{1.0, 0.0},pos_weapon{0.0, 0.0},
    center_weapon(w.center_weapon), launch_point(w.launch_point), texture(nullptr), bullet_type(w.bullet_type), bullets(hero_bullets){
    LoadImage(this->texture, w.Path);
}
Weapon::~Weapon(){
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

Weapon_type_1::Weapon_type_1(const s_weapons &w): Weapon(w) {}
void Weapon_type_1::render(const Position MousePos) const{
    UpdateDir(MousePos.x, MousePos.y);
    const SDL_Rect rect = {static_cast<int>(pos_weapon.x) - center_weapon.x, static_cast<int>(pos_weapon.y) - center_weapon.y, 32, 32 };
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (MousePos.x - pos_weapon.x < 0)
        flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(app.renderer, texture, nullptr, &rect, 0.0, nullptr, flip);
}
