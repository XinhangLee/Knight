//
// Created by lixh1 on 25-2-8.
//
#include <game.h>

Position MousePos = { 750.0, 460.0 };
int fps = 0;
Uint32 tick;
Hero *hero = nullptr;
bool IsQuit = false;



void game() {
    tick = SDL_GetTicks();
    for (auto & i : walls_1) {
        walls.emplace_back(i[0], i[1], i[2], i[3]);
    }
    while (!IsQuit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    IsQuit = true;
                break;
                case SDL_KEYDOWN:
                    do_keydown(event);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    do_mouse_down(event);
                    break;
                case SDL_MOUSEMOTION:
                    do_mouse_motion(event);
                    break;
                default:
                    break;
            }
        }
        if (hero) {
            hero->Move(MousePos);
            if (!monster.empty()) {
                for (const auto & i : monster) {
                    i->Move(*hero);
                }
            }
        }

        display();
        SDL_Delay(1000 / FPS);
    }
    IsQuit = false;
}




void do_keydown(const SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
            break;
        case SDL_SCANCODE_SPACE:
            IsQuit = true;
        break;
        case SDL_SCANCODE_RETURN:
            CreateHero();
        break;
        case SDL_SCANCODE_J:
            Fire();
        break;
        case SDL_SCANCODE_Z :
            if (hero) {
                monster.push_back(new Monster_type3(5,200,3.5,{900,600},{41,36},"../rsc/Demon bat.png", bullet_2));
            }
        break;
        case SDL_SCANCODE_X:
            if (hero) {
                monster.push_back(new Monster_type2(5,200,3.5,{700,500},{24,24},"../rsc/ghost.png",weapon_1));
            }
        break;
        case SDL_SCANCODE_C:
            if (hero) {
                monster.push_back(new Monster_type4(20,200,0.5,{700,500},{111,123}));
            }
        default:
            break;
    }
}
void do_mouse_down(const SDL_Event &event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        Fire();
    }
}
void do_mouse_motion(const SDL_Event &event) {
    MousePos.x = event.motion.x;
    MousePos.y = event.motion.y;
}
void display() {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    // 加载背景、帧率
    Render_ground_game();
    Render_background();
    SDL_DestroyTexture(background_texture);
    const Uint32 duration = SDL_GetTicks() - tick;
    fps = 1000 / static_cast<int>(duration);
    tick = SDL_GetTicks();
    Render_fps(fps);
    SDL_DestroyTexture(fps_texture);
    Render_Elements();
    Present();
}



void Render_ground_game() {
    SDL_Texture *texture = nullptr;
    LoadImage(texture, "../rsc/mystery-forest.png");
    constexpr SDL_Rect groundRect = {-180, 0, 1500, 1000};
    constexpr SDL_Rect groundRect2 = {200, 0, 1500, 1000};
    SDL_RenderCopy(app.renderer, texture, nullptr, &groundRect);
    SDL_RenderCopy(app.renderer, texture, nullptr, &groundRect2);
    SDL_DestroyTexture(texture);
}
void Render_background() {
    LoadImage(background_texture, "../rsc/background.png");
    constexpr SDL_Rect backgroundRect = {307, 60, 885, 880};
    SDL_RenderCopy(app.renderer, background_texture, nullptr, &backgroundRect);
}
void Render_fps(const int fps) {
    TTF_Font *font = TTF_OpenFont("../rsc/svgafix.fon", 30);
    LoadText(fps_texture, font, "FPS: " + std::to_string(fps), WHITE);
    constexpr SDL_Rect fpsRect = {0, WINDOW_HEIGHT - 30, 80, 30};
    SDL_RenderCopy(app.renderer, fps_texture, nullptr, &fpsRect);
    TTF_CloseFont(font);
}
void Render_Elements() {
    // 加载人物、武器、子弹、怪物
    if (hero) {
        hero->render(MousePos);
        if (hero->getWeapon()) {
            hero->getWeapon()->UpdatePos(hero->getWeaponPoint().x + hero->getX(), hero->getWeaponPoint().y + hero->getY());
            hero->getWeapon()->render(hero->get_DirAttack());
        }
    }
    // 检测英雄子弹并渲染
    if (!bullets_hero.empty()) {
        for (auto it_bullet = bullets_hero.begin(); it_bullet != bullets_hero.end();) {
            auto bullet = *it_bullet;
            if (isColliding(*bullet)) {
                delete bullet;
                it_bullet = bullets_hero.erase(it_bullet);
                bullet = nullptr;
            }
            else if (!monster.empty()) {
                for (const auto m : monster) {
                    if (bullet->checkCollision(*m)) {
                        m->Hurt(bullet->get_attack_power());
                        delete bullet;
                        it_bullet = bullets_hero.erase(it_bullet);
                        bullet = nullptr;
                        break;
                    }
                }
            }
            if (bullet != nullptr){
                if (bullet->isFirst())
                    bullet->render();
                else {
                    bullet->Update();
                    bullet->render();
                }
                ++it_bullet;
            }
        }
    }
    // 杀死怪物
    for (auto it_monster = monster.begin(); it_monster != monster.end();) {
        if (const auto m = *it_monster; m->getDelete()) {
            delete m;
            it_monster = monster.erase(it_monster);
        }
        else {
            ++it_monster;
        }
    }
    // 渲染怪物
    if (!monster.empty()) {
        for (const auto monster : monster) {
            monster->Render();
        }
    }
    // 检测怪物子弹并渲染
    if (!bullets_monster.empty()) {
        for (auto it_bullet = bullets_monster.begin(); it_bullet != bullets_monster.end();) {
            if (const auto bullet = *it_bullet; isColliding(*bullet)) {
                delete bullet;
                it_bullet = bullets_monster.erase(it_bullet);
            }
            else if (bullet->checkCollision(*hero)) {
                hero->Hurt(bullet->get_attack_power());
                delete bullet;
                it_bullet = bullets_monster.erase(it_bullet);
            }
            else {
                if (bullet->isFirst())
                    bullet->render();
                else {
                    bullet->Update();
                    bullet->render();
                }
                ++it_bullet;
            }
        }
    }
}
void Fire() {
    if (hero != nullptr){
        if (const Weapon *w = hero->getWeapon(); w != nullptr){
            w->UpdatePos(hero->getWeaponPoint().x + hero->getX(), hero->getWeaponPoint().y + hero->getY());
            w->UpdateDir(MousePos.x, MousePos.y);
            if (hero->getEnergy() - hero->getWeapon()->getBullet()->energy_consumed >= 0){
                hero->attack();
                hero->Sub_energy(hero->getWeapon()->getBullet()->energy_consumed);
            }
        }
    }
}
void CreateHero() {
    if (!hero)
        hero = new Hero(hero_1);
    if (hero && !hero->getWeapon()) {
        hero->setWeapon(new Weapon_type_1(weapon_1, bullets_hero));
    }
}
