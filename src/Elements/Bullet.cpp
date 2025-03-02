//
// Created by lixh1 on 25-2-11.
//
#include <Elements/Bullet.h>

std::vector<Bullet*> bullets_hero;
std::vector<Bullet*> bullets_monster;

Bullet::Bullet(const s_bullets &bullet, const Position pos_bullet, const Direction dir_bullet):
        Collider(static_cast<int>(pos_bullet.x),static_cast<int>(pos_bullet.y), 16,16),
        attack_power(bullet.attack_power),energy_consumed(bullet.energy_consumed), pos_bullet(pos_bullet),
        center_bullet(bullet.center_bullet), dir_bullet(dir_bullet), speed_bullet(bullet.speed_bullet),
        frame_current(0), frame_num(bullet.frame_num),texture(nullptr),is_first(true)
{
    Load_Image(this->texture, bullet.path);
}
Bullet::~Bullet() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}
void Bullet::Update() {
    const double len = sqrt(pow(dir_bullet.dx, 2) + pow(dir_bullet.dy, 2));
    pos_bullet.x += dir_bullet.dx / len * speed_bullet;
    pos_bullet.y += dir_bullet.dy / len * speed_bullet;

    frame_current = (frame_current + 1) % frame_num;
}
void Bullet::render() {
    is_first = false;
    setColliderPosition(static_cast<int>(pos_bullet.x) - center_bullet.x,
                        static_cast<int>(pos_bullet.y) - center_bullet.y);
    const SDL_Rect src_rect = {16 * frame_current, 0, 16, 16};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (dir_bullet.dx < 0)
        flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(app.renderer, texture, &src_rect, getCollider(),
                getDegree(dir_bullet), &center_bullet, flip);
}
