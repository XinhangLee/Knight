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
            if (monster_1)
            monster_1->Move(*hero);
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
                // monster_1 = new Monster_type1(5,0,200,0.5,{0.0,0.0},{700,500},{20,20},"../rsc/Crow.png");
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
    // 加载人物、武器、子弹
    if (hero) {
        hero->render(MousePos);
        if (hero->getWeapon()) {
            hero->getWeapon()->UpdatePos(hero->getWeaponPoint().x + hero->getX(), hero->getWeaponPoint().y + hero->getY());
            hero->getWeapon()->render(MousePos);
            if (!hero_bullets.empty()) {
                for (auto it = hero_bullets.begin(); it != hero_bullets.end();) {
                    if (const auto bullet = *it; isColliding(*bullet)) {
                        delete bullet;
                        it = hero_bullets.erase(it);
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
    }
    if (monster_1)
        monster_1->Render();
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
void Fire() {
    if (hero != nullptr){
        if (Weapon *w = hero->getWeapon(); w != nullptr){
            w->UpdatePos(hero->getWeaponPoint().x + hero->getX(), hero->getWeaponPoint().y + hero->getY());
            w->UpdateDir(MousePos.x, MousePos.y);
            if (hero->getEnergy() - hero->getWeapon()->getBullet()->energy_consumed >= 0){
                w->Attack();
                hero->Sub_energy(hero->getWeapon()->getBullet()->energy_consumed);
            }
        }
    }
}
void CreateHero() {
    if (!hero)
        hero = new Hero(hero_1);
    if (hero && !hero->getWeapon()) {
        hero->setWeapon(new Weapon_type_1(weapon_1));
    }
}
