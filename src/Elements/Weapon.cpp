//
// Created by lixh1 on 25-2-6.
//
#include <Elements/Weapon.h>

std::vector<Bullet*> initial_bullets;

Weapon::Weapon(const std::string &imagePath): AttackPower(3),
                                              EnergyConsumed(20.0),
                                              Dir{1.0, 0.0},
                                              Pos{0.0, 0.0},
                                              texture(nullptr),
                                              bullets(initial_bullets){
    LoadImage(this->texture, imagePath);
}

Weapon::~Weapon() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Weapon::render(const Position MousePos) const {
    const SDL_Rect rect = {static_cast<int>(Pos.x) + 7, static_cast<int>(Pos.y) + 37, 48, 12 };
    constexpr SDL_Point center = {24,4};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (MousePos.x - Pos.x > 0)
        flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(app.renderer, texture, nullptr, &rect, getDegree(Dir), &center, flip);

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





Bullet::Bullet(const std::string &imagePath, const double speed, const Direction Dir, const Position Pos, const int FrameCount, const double degree):
        Pos(Pos), Dir(Dir), speed(speed), texture(nullptr), currentFrame(0), FrameCount(FrameCount), degree(degree), rect(static_cast<int>(Pos.x), static_cast<int>(Pos.y), 16,16), is_first(true){
    LoadImage(this->texture, imagePath);
}
Bullet::~Bullet() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Bullet::Update() {
    const double len = sqrt(pow(Dir.dx, 2) + pow(Dir.dy, 2));
    Pos.x += Dir.dx / len * speed;
    Pos.y += Dir.dy / len * speed;

    currentFrame = (currentFrame + 1) % FrameCount;
}
void Bullet::render() const {
    is_first = false;
    rect = {static_cast<int>(Pos.x), static_cast<int>(Pos.y), 16,16};
    const SDL_Rect src_rect = {16 * currentFrame, 0, 16, 16};
    SDL_RenderCopyEx(app.renderer, texture, &src_rect, &rect, degree, nullptr, SDL_FLIP_NONE);
}



