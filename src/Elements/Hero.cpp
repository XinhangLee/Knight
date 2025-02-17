//
// Created by lixh1 on 25-2-6.
//

#include <Elements/Hero.h>
#include <Elements/Monster.h>

Hero::Hero(const s_heroes &hero):Collider(static_cast<int>(hero.pos_hero.x), static_cast<int>(hero.pos_hero.y),49,81),Timer(hero.weapon_type->time_gap),
                                 HP{hero.HP[0],hero.HP[1]}, shield{hero.shield[0], hero.shield[1]},energy{hero.energy[0], hero.energy[1]}, speed(hero.speed), pos_hero(hero.pos_hero),center_hero(hero.center_hero),
                                 weapon_point(hero.weapon_point),dir_hero(0.0,0.0),dir_attack(0.0,0.0), frame_num(hero.frame_num), currentframe(0), weapon(nullptr),weapon_type(hero.weapon_type),
                                 texture{nullptr, nullptr, nullptr, nullptr}{
    //加载图像
    //人物静止
    LoadImage(this->texture[0], hero.StablePath);
    //人物运动
    LoadImage(this->texture[1], hero.WalkPath);
    //功能性界面
    LoadImage(this->texture[2], "../rsc/Func.png");
}

Hero::~Hero() {
    delete weapon;
    for (const auto & i : texture) {
        if (i != nullptr) {
            SDL_DestroyTexture(i);
        }
    }
}
void Hero::Move(const double dx, const double dy) {
    pos_hero.x += dx;
    pos_hero.y += dy;
    currentframe = (currentframe + 1) % frame_num;
    setColliderPosition(static_cast<int>(pos_hero.x) - center_hero.x, static_cast<int>(pos_hero.y) - center_hero.y);
}
void Hero::Move(const Position MousePos) {
    UpdateDir(MousePos);
    int pos[4] = {};
    const int code = isColliding(*this);
    for (int i = 0; i < 4; i++) {
        pos[i] = code & static_cast<int>(pow(2, i)) ? 1 : 0;
    }
    if (pos[0] && dir_hero.dx < 0) {
        dir_hero.dx = 0.0;
    }
    if (pos[1] && dir_hero.dy < 0) {
        dir_hero.dy = 0.0;
    }
    if (pos[2] && dir_hero.dx > 0) {
        dir_hero.dx = 0.0;
    }
    if (pos[3] && dir_hero.dy > 0) {
        dir_hero.dy = 0.0;
    }
    if (pos_hero.x > MousePos.x + 50.0 || pos_hero.x < MousePos.x - 50.0
        || pos_hero.y > MousePos.y + 50.0 || pos_hero.y < MousePos.y - 50.0) {
        if (const double len = sqrt(pow(dir_hero.dx, 2) + pow(dir_hero.dy, 2)); len != 0.0) {
            pos_hero.x += dir_hero.dx / len * speed;
            pos_hero.y += dir_hero.dy / len * speed;
        }
        currentframe = (currentframe + 1) % frame_num;
        }
    setColliderPosition(static_cast<int>(pos_hero.x) - center_hero.x, static_cast<int>(pos_hero.y) - center_hero.y);
}
void Hero::UpdateDir(const Position p) const {
    dir_hero = {p.x - pos_hero.x,p.y - pos_hero.y };
    bool update = false;
    if (!monster_1.empty()) {
        auto min = DBL_MAX;
        for (const auto & monster : monster_1) {
            if (Distance(pos_hero, monster->getPos()) <= 500) {
                if (Distance(pos_hero, monster->getPos()) < min) {
                    min = Distance(pos_hero, monster->getPos());
                    dir_attack = {monster->getPos().x - pos_hero.x, monster->getPos().y - pos_hero.y};
                    update = true;
                }
            }
        }
    }
    if (!update) {
        dir_attack = {dir_hero.dx, dir_hero.dy};
    }
}

void Hero::render(const Position MousePos) {
    if (shield[1] < shield[0]) {
        time2 = SDL_GetTicks();
        if (time2 - time1 > 2000) {
            shield[1]++;
            time1 = time2;
        }
    }
    if (pos_hero.x <= MousePos.x + 50.0 && pos_hero.x >= MousePos.x - 50.0
        && pos_hero.y <= MousePos.y + 50.0 && pos_hero.y >= MousePos.y - 50.0) {
        if (texture[0]) {
            constexpr SDL_Rect srcrect = {0, 0, 49, 81};
            SDL_RenderCopy(app.renderer, texture[0], &srcrect, getCollider());
        }
    }
    else {
        if (texture[1]) {
            const SDL_Rect srcrect = {49 * currentframe, 0, 49, 81};
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            if (MousePos.x - pos_hero.x < 0)
                flip = SDL_FLIP_HORIZONTAL;
            SDL_RenderCopyEx(app.renderer, texture[1], &srcrect, getCollider(), 0.0f, nullptr, flip);
        }
    }
    if (texture[2]) {
        constexpr SDL_Rect rect1 = { 25, 20, FUNCTION_WIDTH, FUNCTION_HEIGHT};
        SDL_RenderCopy(app.renderer, texture[2], nullptr, &rect1);
    }
    const int HP_Length = HP[1] * 180 / HP[0]; // 条的总长度为180像素
    const int energy_Length = energy[1] * 180 / energy[0];
    const int shield_Length = shield[1] * 180 / shield[0];
    const SDL_Rect healthRect = {87, 38, HP_Length, 12}; // 12是条的高度
    SDL_SetRenderDrawColor(app.renderer, 255, 0, 0, 255); // 红色表示血量
    SDL_RenderFillRect(app.renderer, &healthRect);
    const SDL_Rect manaRect = {87, 78, energy_Length, 12};
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 255, 255); // 蓝色表示魔法值
    SDL_RenderFillRect(app.renderer, &manaRect);
    const SDL_Rect shieldRect = {87, 120, shield_Length, 12};
    SDL_SetRenderDrawColor(app.renderer, 200, 200, 200, 255); // 灰色表示护盾值
    SDL_RenderFillRect(app.renderer, &shieldRect);

    const std::string HP_Text = std::to_string(HP[1]) + " / " + std::to_string(HP[0]);
    const std::string energy_Text = std::to_string(energy[1]) + " / " + std::to_string(energy[0]);
    const std::string shield_Text = std::to_string(shield[1]) + " / " + std::to_string(shield[0]);

    TTF_Font *font = TTF_OpenFont("../rsc/svgafix.fon", 0);
    if (font == nullptr) {
        LOG_ERROR("Font Open");
    }
    LoadText(this->texture[3], font, HP_Text, WHITE);
    constexpr SDL_Rect HP_Text_Rect = { 87 + 65, 36, 40, 17 };
    SDL_RenderCopy(app.renderer, texture[3], nullptr, &HP_Text_Rect);
    SDL_DestroyTexture(texture[3]);
    LoadText(this->texture[3], font, energy_Text, WHITE);
    constexpr SDL_Rect energy_Text_Rect = { 87 + 50, 76, 80, 17 };
    SDL_RenderCopy(app.renderer, texture[3], nullptr, &energy_Text_Rect);
    SDL_DestroyTexture(texture[3]);
    LoadText(this->texture[3], font, shield_Text, WHITE);
    constexpr SDL_Rect shield_Text_Rect = { 87 + 65, 118, 40, 17 };
    SDL_RenderCopy(app.renderer, texture[3], nullptr, &shield_Text_Rect);
    SDL_DestroyTexture(texture[3]);

    TTF_CloseFont(font);
}
void Hero::attack() const {
    if (Time_out())
    weapon->Attack(dir_attack);
}
void Hero::Hurt(const int x) {
    if (shield[1] != 0 ){
        if (shield[1] - x >= 0)
            shield[1] -= x;
        else {
            int extra = 0;
            extra = x - shield[1];
            shield[1] = 0;
            if (HP[1] != 0) {
                if (HP[1] - extra >= 0) {
                    HP[1] -= extra;
                }
                else {
                    HP[1] = 0;
                }
            }
        }
    }
    else {
        if (HP[1] - x >= 0)
            HP[1] -= x;
        else {
            HP[1] = 0;
        }
    }
}



