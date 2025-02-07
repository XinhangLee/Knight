//
// Created by lixh1 on 25-2-6.
//
#include <Elements/Weapon.h>

std::vector<Bullet*> initial_bullets;

Weapon::Weapon(SDL_Renderer * renderer, const std::string &imagePath): AttackPower(3),
                                                                       EnergyConsumed(2),
                                                                       Dir{1.0, 0.0},
                                                                       Pos{0.0, 0.0},
                                                                       texture(nullptr), bullets(initial_bullets){
    LoadImage(this->texture, renderer, imagePath, "Weapon");
}

Weapon::~Weapon() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }

}
// 返回值是一个角度，用角度制，如45

void Weapon::render(SDL_Renderer *renderer, const Position MousePos) const {
    const SDL_Rect rect = {static_cast<int>(Pos.x) + 7, static_cast<int>(Pos.y) + 37, 48, 12 };
    constexpr SDL_Point center = {24,4};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (MousePos.x - Pos.x > 0)
        flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, texture, nullptr, &rect, getDegree(Dir), &center, flip);

    if (!bullets.empty()) {
        for (auto it = bullets.begin(); it != bullets.end();) {
            if (const auto bullet = *it; bullet->GetRect().x >= 1237 || bullet->GetRect().x <= 246 || bullet->GetRect().y >= 984 || bullet->GetRect().y <= 0) {
                delete bullet;
                it = bullets.erase(it);
            }
            else {
                if (bullet->isFirst())
                    bullet->render(renderer);
                else {
                    bullet->Update();
                    bullet->render(renderer);
                }
                ++it;
            }
        }
    }
}
// void Weapon::removeBullet(std::vector<Bullet*>& bullets, Bullet* bullet) {
//     const auto it = std::ranges::find_if(bullets, [bullet](const Bullet* b) {
//         return b == bullet;
//     });
//     if (it != bullets.end()) {
//         delete *it;
//         bullets.erase(it);
//     }
// }
void Weapon::Attack(SDL_Renderer *renderer) const {
    bullets.push_back(new Bullet(renderer, "../rsc/Fireball.png", 8.0, Dir, {Pos.x + 25, Pos.y + 40}, 6, getDegree(Dir)));
}




Bullet::Bullet(SDL_Renderer *renderer, const std::string &imagePath, const double speed, const Direction Dir, const Position Pos, const int FrameCount, const double degree):
        Pos(Pos), Dir(Dir), speed(speed), texture(nullptr), currentFrame(0), FrameCount(FrameCount), degree(degree), rect(static_cast<int>(Pos.x), static_cast<int>(Pos.y), 16,16), is_first(true){
    LoadImage(this->texture, renderer, imagePath, "Bullet");
}
void Bullet::Update() {
    const double len = sqrt(pow(Dir.dx, 2) + pow(Dir.dy, 2));
    Pos.x += Dir.dx / len * speed;
    Pos.y += Dir.dy / len * speed;

    currentFrame = (currentFrame + 1) % FrameCount;
}
void Bullet::render(SDL_Renderer *renderer) const {
    is_first = false;
    rect = {static_cast<int>(Pos.x), static_cast<int>(Pos.y), 16,16};
    const SDL_Rect src_rect = {16 * currentFrame, 0, 16, 16};
    SDL_RenderCopyEx(renderer, texture, &src_rect, &rect, degree, nullptr, SDL_FLIP_NONE);
}



