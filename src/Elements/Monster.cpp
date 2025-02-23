//
// Created by lixh1 on 25-2-6.
//
#include <Elements/Monster.h>

#include <utility>

std::vector<Monster *> monster;

Monster::Monster(const int HP, const int range, const double speed_monster,
    const Position pos_monster, const SDL_Point center_monster): Collider(0,0,0,0), Timer(0),
                                                                 HP(HP),
                                                                 speed_monster(speed_monster),
                                                                 range(range), center_monster(center_monster),
                                                                 dir_monster(0.0, 0.0), pos_monster(pos_monster),
                                                                 alive(true), to_delete(false) {
    UpdateDirRandom();
}

Monster::~Monster() = default;
void Monster::UpdateDir(const Hero &hero) {
    if (Distance(pos_monster, hero.getPos()) <= range) {
        dir_monster = {hero.getX() - pos_monster.x, hero.getY() - pos_monster.y};
    }
}
void Monster::Hurt(const int attack) {
    if (HP >= 0) {
        if (HP - attack >= 0)
            HP -= attack;
        else {
            HP = 0;
            Die();
        }
    }
}
void Monster::UpdateDirRandom() {
    int angle = dis(gen);
    angle = angle % 360 - 180;
    dir_monster.dx = cos(angle);
    dir_monster.dy = sin(angle);
}
void Monster::Die() {
    alive = false;
    to_delete = true;
}






Monster_type2::Monster_type2(const int HP, const int range, const double speed_monster, const SDL_Point staff_point,
    const Position pos_monster, const SDL_Point center_monster, const std::string &Path , const s_weapons &w):
    Monster(HP, range, speed_monster, pos_monster, center_monster),texture(nullptr),
    frame_num(8), current_frame(-1), staff_point(staff_point), weapon(w, bullets_monster){
    setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
    setColliderSize(48,48);
    Reset(w.bullet_type->time_gap);
    Load_Image(texture, Path);
}
Monster_type2::~Monster_type2() {
    SDL_DestroyTexture(texture);
}
void Monster_type2::Move(const Hero &h) {
    UpdateDir(h);
    if (isColliding(*this)) {
        UpdateDirRandom();
        int pos[4] = {};
        const int code = isColliding(*this);
        for (int i = 0; i < 4; i++) {
            pos[i] = code & static_cast<int>(pow(2, i)) ? 1 : 0;
        }
        if (pos[0] && dir_monster.dx < 0) {
            dir_monster.dx = 0.0;
        }
        if (pos[1] && dir_monster.dy < 0) {
            dir_monster.dy = 0.0;
        }
        if (pos[2] && dir_monster.dx > 0) {
            dir_monster.dx = 0.0;
        }
        if (pos[3] && dir_monster.dy > 0) {
            dir_monster.dy = 0.0;
        }
    }
    if (Distance(pos_monster, h.getPos()) >= 200.0) {
        if (const double len = sqrt(pow(dir_monster.dx, 2) + pow(dir_monster.dy, 2)); len != 0.0) {
            pos_monster.x += dir_monster.dx / len * speed_monster;
            pos_monster.y += dir_monster.dy / len * speed_monster;
        }
    }
    else {
        weapon.setDir(dir_monster.dx, dir_monster.dy);
        attack();
    }
    setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
    current_frame = (current_frame + 1) % frame_num;
}
void Monster_type2::Render(){
    if (texture) {
        const SDL_Rect srcrect = {current_frame * 16, 0, 16, 16};
        SDL_RenderCopy(app.renderer, texture, &srcrect, getCollider());
    }
    weapon.UpdatePos(pos_monster.x - center_monster.x + staff_point.x * 3, pos_monster.y - center_monster.y + staff_point.y * 3);
    weapon.render();
}













Monster_type3::Monster_type3(const int HP, const int range, const double speed_monster,
    const Position pos_monster, const SDL_Point center_monster, const std::string &Path , const s_bullets &b):
    Monster(HP, range, speed_monster, pos_monster, center_monster),
    texture(nullptr), frame_num{4,8,6}, current_frame{-1,-1,-1}, row(0), mode_attack(false), bullet(b)
    {
    setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
    setColliderSize(81,71);
    Reset(b.time_gap);
    Load_Image(texture, Path);
}
Monster_type3::~Monster_type3() {
    SDL_DestroyTexture(texture);
}
void Monster_type3::Render() {
    if (texture) {
        if (alive) {
            if (mode_attack) {
                render_attack();
            }
            else {
                render_move();
            }
        }
        else {
            render_death();
        }
    }
}
void Monster_type3::Move(const Hero &h) {
    if (alive){
        if (isColliding(*this)) {
            UpdateDirRandom();
            int pos[4] = {};
            const int code = isColliding(*this);
            for (int i = 0; i < 4; i++) {
                pos[i] = code & static_cast<int>(pow(2, i)) ? 1 : 0;
            }
            if (pos[0] && dir_monster.dx < 0) {
                dir_monster.dx = 0.0;
            }
            if (pos[1] && dir_monster.dy < 0) {
                dir_monster.dy = 0.0;
            }
            if (pos[2] && dir_monster.dx > 0) {
                dir_monster.dx = 0.0;
            }
            if (pos[3] && dir_monster.dy > 0) {
                dir_monster.dy = 0.0;
            }
        }
        UpdateDir(h);
        if (Distance(pos_monster, h.getPos()) >= 200.0) {
            if (const double len = sqrt(pow(dir_monster.dx, 2) + pow(dir_monster.dy, 2)); len != 0.0) {
                pos_monster.x += dir_monster.dx / len * speed_monster;
                pos_monster.y += dir_monster.dy / len * speed_monster;
            }
        }
        else {
            mode_attack = true;
            row = 1;
            attack();
        }
        setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
    }
    current_frame[row] = (current_frame[row] + 1) % frame_num[row];
}
void Monster_type3::render_attack() {
    const SDL_Rect srcrect = {current_frame[row] * 81, row * 71, 81, 71};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (dir_monster.dx > 0)
        flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(app.renderer, texture, &srcrect, getCollider(), 0.0, &center_monster, flip);
    if (current_frame[row] == 7) {
        row = 0;
        mode_attack = false;
    }
}
void Monster_type3::render_move() const {
    const SDL_Rect srcrect = {current_frame[row] * 81, row * 71, 81, 71};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (dir_monster.dx > 0)
        flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(app.renderer, texture, &srcrect, getCollider(), 0.0, &center_monster, flip);
}
void Monster_type3::render_death() {
    row = 2;
    const SDL_Rect srcrect = {current_frame[row] * 81, row * 71, 81, 71};
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (dir_monster.dx > 0)
        flip = SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(app.renderer, texture, &srcrect, getCollider(), 0.0, &center_monster, flip);
    if (current_frame[row] == 5) {
        to_delete = true;
    }
}
void Monster_type3::attack() const {
    if (current_frame[row] == 4) {
        if (Time_out()) {
            if (dir_monster.dx <= 0)
                bullets_monster.push_back(new Bullet(bullet, {pos_monster.x - center_monster.x + 20, pos_monster.y - center_monster.y + 53}, dir_monster));
            else
                bullets_monster.push_back(new Bullet(bullet, {pos_monster.x - center_monster.x + 62, pos_monster.y - center_monster.y + 53}, dir_monster));
        }
    }
}
void Monster_type3::Die() {
    alive = false;
    row = 2;
}





Monster_type4::Monster_type4(const int HP, const int range, const double speed_monster,
    const Position pos_monster, const SDL_Point center_monster):
    Monster(HP, range, speed_monster, pos_monster, center_monster), HP_total(HP), texture(nullptr),
    row{-1,-1}, current_frame{-1,-1,-1,-1}, bullet(bullet_4), mode{false, false, false}, times(3){
    setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
    setColliderSize(222,246);
    Load_Image(texture[0], "../rsc/monster/covid-19-Idle-1.png");
    Load_Image(texture[1], "../rsc/monster/covid-19-Death-1.png");
    Load_Image(texture[2], "../rsc/monster/covid-19-Idle-2.png");
    Load_Image(texture[3], "../rsc/monster/covid-19-Death-2.png");
    Load_Image(texture[4], "../rsc/monster/covid-19-blood.png");
    Reset(1000);
}
Monster_type4::~Monster_type4() {
    SDL_DestroyTexture(texture[0]);
    SDL_DestroyTexture(texture[1]);
    SDL_DestroyTexture(texture[2]);
    SDL_DestroyTexture(texture[3]);
    SDL_DestroyTexture(texture[4]);
    SDL_DestroyTexture(texture[5]);
}
void Monster_type4::Move(const Hero &h) {
    if (alive){
        if (isColliding(*this)) {
            UpdateDirRandom();
            int pos[4] = {};
            const int code = isColliding(*this);
            for (int i = 0; i < 4; i++) {
                pos[i] = code & static_cast<int>(pow(2, i)) ? 1 : 0;
            }
            if (pos[0] && dir_monster.dx < 0) {
                dir_monster.dx = 0.0;
            }
            if (pos[1] && dir_monster.dy < 0) {
                dir_monster.dy = 0.0;
            }
            if (pos[2] && dir_monster.dx > 0) {
                dir_monster.dx = 0.0;
            }
            if (pos[3] && dir_monster.dy > 0) {
                dir_monster.dy = 0.0;
            }
        }
            if (const double len = sqrt(pow(dir_monster.dx, 2) + pow(dir_monster.dy, 2)); len != 0.0) {
                pos_monster.x += dir_monster.dx / len * speed_monster;
                pos_monster.y += dir_monster.dy / len * speed_monster;
            }
        setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
    }
    UpdateAnimation();
    if (Time_out()) {
        if (checkCollision(h)) {
            h.Hurt(2);
        }
    }
}
void Monster_type4::UpdateAnimation() {
    if (HP > HP_total / 2) {
        current_frame[0] = (current_frame[0] + 1) % 8;
        if (current_frame[0] == 0) {
            row[0] = (row[0] + 1) % 4;
        }
    }
    else if (HP <= HP_total / 2 && !mode[1]) {
        mode[0] = true;
        current_frame[1] = (current_frame[1] + 1) % 9;
    }
    else if (HP <= HP_total / 2 && HP > 0) {
        current_frame[2] = (current_frame[2] + 1) % 8;
        if (current_frame[2] == 0) {
            row[1] = (row[1] + 1) % 4;
        }
    }
    else if (HP <= 0){
        Die();
        mode[2] = true;
        current_frame[3] = (current_frame[3] + 1) % 9;
    }
    attack();
}
void Monster_type4::Render() {
    if (!mode[0]) {
        const SDL_Rect srcrect = {222 * current_frame[0], 246 * row[0], 222, 246};
        SDL_RenderCopy(app.renderer, texture[0], &srcrect, getCollider());
    }
    else if (!mode[1]) {
        const SDL_Rect srcrect = {222 * current_frame[1], 0, 222, 246};
        SDL_RenderCopy(app.renderer, texture[1], &srcrect, getCollider());
        if (current_frame[1] == 8) {
            if (times == 0) {
                mode[1] = true;
                hero->Sub_energy(-150);
                setSpeed(2);
                setColliderSize(222,279);
            } else {
                times--;
            }
        }
    }
    else if (!mode[2]) {
        const SDL_Rect srcrect = {222 * current_frame[2], 279 * row[1], 222, 279};
        SDL_RenderCopy(app.renderer, texture[2], &srcrect, getCollider());
    }
    else {
        const SDL_Rect srcrect = {222 * current_frame[3], 0, 222, 279};
        SDL_RenderCopy(app.renderer, texture[3], &srcrect, getCollider());
        if (current_frame[3] == 8) {
            to_delete = true;
        }
    }
    // 加载血条
    constexpr SDL_Rect srcrect = {0,0,600,100};
    SDL_Rect dstrect = {450,50,600,100};
    SDL_RenderCopy(app.renderer, texture[4], &srcrect, &dstrect);

    const int length = HP * 524 / HP_total;
    dstrect = {450 + 37, 50 + 30, length, 36};
    SDL_SetRenderDrawColor(app.renderer, 99,199,77, 0);
    SDL_RenderFillRect(app.renderer, &dstrect);
    // 名字
    TTF_Font *font = TTF_OpenFont("../rsc/font/svgafix.fon", 0);
    if (font == nullptr) {
        LOG_ERROR("Font Open");
    }
    Load_Text(this->texture[5], font, "COVID-19", RED);
    dstrect = {650,68,200,64};
    SDL_RenderCopy(app.renderer, texture[5], nullptr, &dstrect);
}
void Monster_type4::attack() const {
    if (!mode[0]) {
        if ((current_frame[0] == 2 && row[0] == 0) || (current_frame[0] == 2 && row[0] == 2)) {
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x, pos_monster.y - 106}, {0.0,-1.0}));
        }
        if ((current_frame[0] == 7 && row[0] == 0) || (current_frame[0] == 7 && row[0] == 2)) {
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x - 120, pos_monster.y + 11}, {-1.0,0.0}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x + 120, pos_monster.y + 11}, {1.0,0.0}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x, pos_monster.y + 130}, {0.0,1.0}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x - 105, pos_monster.y + 83}, {-10,6}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x + 105, pos_monster.y + 83}, {10,6}));
        }
    }
    else if (!mode[2]) {
        if ((current_frame[2] == 2 && row[1] == 0) || (current_frame[2] == 2 && row[1] == 2)) {
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x, pos_monster.y - 106}, {0.0,-1.0}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x - 105, pos_monster.y -18}, {-10,-2}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x + 105, pos_monster.y -18}, {10,-2}));
        }
        if ((current_frame[2] == 7 && row[1] == 0) || (current_frame[2] == 7 && row[1] == 2)) {
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x - 120, pos_monster.y + 11}, {-1.0,0.0}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x + 120, pos_monster.y + 11}, {1.0,0.0}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x, pos_monster.y + 130}, {0.0,1.0}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x - 105, pos_monster.y + 83}, {-10,6}));
            bullets_monster.push_back(new Bullet(bullet, {pos_monster.x + 105, pos_monster.y + 83}, {10,6}));
        }
    }
}




// // 暂时失败
// Monster_type1::Monster_type1(const int HP, const int range, const double speed_monster,
//     const Position pos_monster, const SDL_Point center_monster, const std::string &Path):
//     Monster(HP, attack_power, range, speed_monster, pos_monster, center_monster),
//     Collider(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y, 150, 150),
//     texture(nullptr),frame_num(5), current_frame(0), row(0), alive(true) {
//     Load_Image(texture, Path);
// }
// Monster_type1::~Monster_type1() {
//     SDL_DestroyTexture(texture);
// }
// void Monster_type1::Move(const Hero &hero) {
//     UpdateDir(hero);
//     int a = 0;
//     if (Distance(pos_monster, hero.getPos()) <= 10.0) {
//         setSpeed(2);
//         a = 1;
//     }
//     if (std::abs(dir_monster.dx) > std::abs(dir_monster.dy)) {
//         if (dir_monster.dx <= 0) {
//             row = a * 4 + 0;
//         }
//         else {
//             row = a * 4 + 1;
//         }
//     }
//     else {
//         if (dir_monster.dy <= 0) {
//             row = a * 4 + 2;
//         }
//         else {
//             row = a * 4 + 3;
//         }
//     }
//     if (const double len = sqrt(std::pow(dir_monster.dx, 2) + std::pow(dir_monster.dy, 2)); len != 0.0) {
//         pos_monster.x += dir_monster.dx / len * speed_monster;
//         pos_monster.y += dir_monster.dy / len * speed_monster;
//     }
//     setColliderPosition(static_cast<int>(pos_monster.x) - center_monster.x, static_cast<int>(pos_monster.y) - center_monster.y);
//     current_frame = (current_frame + 1) % frame_num;
// }
// void Monster_type1::Die() {
//     alive = false;
//     current_frame = 0;
//     if (std::abs(dir_monster.dx) > std::abs(dir_monster.dy)) {
//         if (dir_monster.dx <= 0) {
//             row = 8;
//         }
//         else {
//             row = 9;
//         }
//     }
//     else {
//         if (dir_monster.dy <= 0) {
//             row = 10;
//         }
//         else {
//             row = 11;
//         }
//     }
// }
// void Monster_type1::Render() const {
//     const SDL_Rect srcrect = {current_frame * 40, row * 40, 40, 40};
//     SDL_RenderCopy(app.renderer, texture, &srcrect, getCollider());
//     if (!alive && current_frame == frame_num) {
//         delete this;
//     }
// }







