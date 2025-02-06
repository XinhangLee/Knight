//
// Created by lixh1 on 25-2-6.
//

#include <Elements/Hero.h>

Hero::Hero(SDL_Renderer *renderer,
    const std::string &imagePath): HP(5),
                                   shield(5),
                                   energy(200),
                                   speed(2.0),
                                   pos{WINDOW_WIDTH / 2.0, WINDOW_HEIGHT / 2.0},
                                   texture(nullptr) {
    //加载图像

    LoadImage(this->texture, renderer, imagePath, "Hero");
}

Hero::~Hero() {
    SDL_DestroyTexture(texture);
    LOG("Hero Destroyed Successfully!");
}
void Hero::render(SDL_Renderer* renderer) const {
    if (texture) {
        const SDL_Rect rect = { static_cast<int>(pos.x), static_cast<int>(pos.y), 64, 64 };
        SDL_RenderCopy(renderer, texture, nullptr, &rect);
    }
}
void Hero::Move(const double dx, const double dy) {
    pos.x += dx;
    pos.y += dy;
}
// void Hero::Attack() {
//
// }




