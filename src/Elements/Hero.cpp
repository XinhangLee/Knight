//
// Created by lixh1 on 25-2-6.
//

#include <Elements/Hero.h>

Hero::Hero(SDL_Renderer *renderer,
    const std::string &imagePath,
    const std::string &imagePath_w): HP{5,5},
                                   shield{5,5},
                                   energy{200,200},
                                   speed(5.0),
                                   pos{WINDOW_WIDTH / 2.0 - 28, WINDOW_HEIGHT / 2.0},
                                   texture{nullptr},
                                   weapon(renderer, imagePath_w){
    //加载图像
    //人物
    LoadImage(this->texture[0], renderer, imagePath, "Hero");
    //功能性界面
    LoadImage(this->texture[1], renderer, "../rsc/Func.png", "Func");
}

Hero::~Hero() {
    SDL_DestroyTexture(texture[0]);
    SDL_DestroyTexture(texture[1]);
    SDL_DestroyTexture(texture[2]);
    SDL_DestroyTexture(texture[3]);
    SDL_DestroyTexture(texture[4]);
    LOG("Hero Destroyed Successfully!");
}
void Hero::render(SDL_Renderer* renderer, Position MousePos) {
    if (texture[0]) {
        const SDL_Rect rect = { static_cast<int>(pos.x), static_cast<int>(pos.y), 64, 64 };
        SDL_RenderCopy(renderer, texture[0], nullptr, &rect);
    }
    if (texture[1]) {
        constexpr SDL_Rect rect1 = { 25, 20, 269, 134 };
        SDL_RenderCopy(renderer, texture[1], nullptr, &rect1);
    }
    const int HP_Length = HP[1] * 180 / HP[0]; // 条的总长度为180像素
    const int energy_Length = energy[1] * 180 / energy[0];
    const int shield_Length = shield[1] * 180 / shield[0];
    const SDL_Rect healthRect = {87, 38, HP_Length, 12}; // 12是条的高度
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // 红色表示血量
    SDL_RenderFillRect(renderer, &healthRect);
    const SDL_Rect manaRect = {87, 78, energy_Length, 12};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // 蓝色表示魔法值
    SDL_RenderFillRect(renderer, &manaRect);
    const SDL_Rect shieldRect = {87, 120, shield_Length, 12};
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // 灰色表示护盾值
    SDL_RenderFillRect(renderer, &shieldRect);

    const std::string HP_Text = std::to_string(HP[1]) + " / " + std::to_string(HP[0]);
    const std::string energy_Text = std::to_string(energy[1]) + " / " + std::to_string(energy[0]);
    std::string shield_Text = std::to_string(shield[1]) + " / " + std::to_string(shield[0]);

    TTF_Font *font = TTF_OpenFont("../rsc/svgafix.fon", 0);
    if (font == nullptr) {
        LOG_ERROR("Font Open");
    }
    LOG("Font Open Successfully!");
    LoadText(this->texture[2], renderer, font, HP_Text, WHITE);
    constexpr SDL_Rect HP_Text_Rect = { 87 + 65, 36, 40, 17 };
    SDL_RenderCopy(renderer, texture[2], nullptr, &HP_Text_Rect);
    LoadText(this->texture[3], renderer, font, energy_Text, WHITE);
    constexpr SDL_Rect energy_Text_Rect = { 87 + 50, 76, 80, 17 };
    SDL_RenderCopy(renderer, texture[3], nullptr, &energy_Text_Rect);
    LoadText(this->texture[4], renderer, font, shield_Text, WHITE);
    constexpr SDL_Rect shield_Text_Rect = { 87 + 65, 118, 40, 17 };
    SDL_RenderCopy(renderer, texture[4], nullptr, &shield_Text_Rect);

    TTF_CloseFont(font);
    LOG("Font Close Successfully!");

    // 渲染武器
    weapon.UpdatePos(pos.x, pos.y);
    weapon.render(renderer, MousePos);
}
void Hero::Move(const double dx, const double dy) {
    pos.x += dx;
    pos.y += dy;
}
// void Hero::Attack() {
//
// }




