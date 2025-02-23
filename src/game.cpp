//
// Created by lixh1 on 25-2-8.
//
#include <game.h>

Game *newgame;


Game::~Game() {
    delete hero;
    hero = nullptr;
    for (const auto & it : bullets_hero) {
        delete it;
    }
    bullets_hero.clear(); // 清空容器
    bullets_hero.shrink_to_fit();

    // 删除 bullets_monster 中的所有子弹
    for (const auto & it : bullets_monster) {
        delete it;
    }
    bullets_monster.clear(); // 清空容器
    bullets_monster.shrink_to_fit();

    // 删除 monster 中的所有怪物
    for (const auto & it : monster) {
        delete it;
    }
    monster.clear(); // 清空容器
    monster.shrink_to_fit();
    delete level;
    level = nullptr;
    SDL_DestroyTexture(render_target);
}

void Game::game() {
    tick = SDL_GetTicks();
    for (auto & i : walls_1) {
        walls.emplace_back(i[0], i[1], i[2], i[3]);
    }
    while (!IsQuit) {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0) {
            switch (event.type) {
                case SDL_QUIT:
                    Mix_FreeMusic(music);
                    IsQuit = true;
                    exit(0);
                case SDL_KEYDOWN:
                    do_keydown(event);
                break;
                case SDL_MOUSEBUTTONDOWN:
                    do_mouse_down(event);
                break;
                case SDL_MOUSEMOTION:
                    do_mouse_motion(event);
                break;
                case SDL_WINDOWEVENT:
                    do_window_event(event);
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
        level_control();

        display();
        SDL_Delay(1000 / FPS);
        if (hero && hero->getHP() == 0){
            Mix_FreeMusic(music);
            showSystemMessageBox("Game Over!", "INFO");
            IsQuit = true;
        }
    }
    IsQuit = false;
}




void Game::do_keydown(const SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
            Mix_FreeMusic(music);
            IsQuit = true;
            break;
        case SDL_SCANCODE_SPACE:
            CreateHero();
        break;
        case SDL_SCANCODE_RETURN:
            CreateHero();
        break;
        case SDL_SCANCODE_J:
            Fire();
        break;
        case SDL_SCANCODE_Z :
            if (hero) {
                monster.push_back(new Monster_type3(10,500,3.5,{900,600},{41,36},"../rsc/monster/Demon bat.png", bullet_2));
            }
        break;
        case SDL_SCANCODE_X:
            if (hero) {
                monster.push_back(new Monster_type2(10,500,3.5,{8,12},{700,500},{24,24},"../rsc/monster/ghost.png",weapon_2));
            }
        break;
        case SDL_SCANCODE_C:
            if (hero) {
                monster.push_back(new Monster_type4(200,500,6.5,{700,500},{111,123}));
            }
        default:
            break;
    }
}
void Game::do_mouse_down(const SDL_Event &event) const {
    if (event.button.button == SDL_BUTTON_LEFT) {
        Fire();
    }
}
void Game::do_mouse_motion(const SDL_Event &event) {
    MousePos.x = event.motion.x;
    MousePos.y = event.motion.y;
}
void Game::do_window_event(const SDL_Event &event) {
    if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        screenWidth[0] = event.window.data1;
        screenHeight[0] = event.window.data2;
        if (screenWidth[0] / 3 >= screenHeight[0] / 2) {
            screenWidth[1] = screenHeight[0] / 2 * 3;
            screenHeight[1] = screenHeight[0];
        }
        else {
            screenWidth[1] = screenWidth[0];
            screenHeight[1] = screenWidth[0] / 3 * 2;
        }
    }
}

void Game::display() {
    SDL_SetRenderTarget(app.renderer, render_target);
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    // 加载背景、帧率
    Render_ground_game();
    Render_background();
    SDL_DestroyTexture(background_texture);
    Render_Elements();
    const Uint32 duration = SDL_GetTicks() - tick;
    fps = 1000 / static_cast<int>(duration);
    tick = SDL_GetTicks();
    Render_fps(fps);
    SDL_DestroyTexture(fps_texture);
    SDL_SetRenderTarget(app.renderer, nullptr); // 重置渲染目标为默认（屏幕）
    const SDL_Rect screenDstRect = {(screenWidth[0] - screenWidth[1]) / 2, (screenHeight[0] - screenHeight[1]) / 2, screenWidth[1], screenHeight[1]};
    SDL_RenderCopy(app.renderer, render_target, nullptr, &screenDstRect);
    Present();
}



void Game::Render_ground_game() {
    SDL_Texture *texture = nullptr;
    Load_Image(texture, "../rsc/sundry/mystery-forest.png");
    constexpr SDL_Rect groundRect = {-180, 0, 1500, 1000};
    constexpr SDL_Rect groundRect2 = {200, 0, 1500, 1000};
    SDL_RenderCopy(app.renderer, texture, nullptr, &groundRect);
    SDL_RenderCopy(app.renderer, texture, nullptr, &groundRect2);
    SDL_DestroyTexture(texture);
}
void Game::Render_background() {
    Load_Image(background_texture, "../rsc/sundry/background.png");
    constexpr SDL_Rect backgroundRect = {307, 60, 885, 880};
    SDL_RenderCopy(app.renderer, background_texture, nullptr, &backgroundRect);
}
void Game::Render_fps(const int fps) {
    TTF_Font *font = TTF_OpenFont("../rsc/font/svgafix.fon", 30);
    Load_Text(fps_texture, font, "FPS: " + std::to_string(fps), WHITE);
    constexpr SDL_Rect fpsRect = {0, WINDOW_HEIGHT - 30, 80, 30};
    SDL_RenderCopy(app.renderer, fps_texture, nullptr, &fpsRect);
    TTF_CloseFont(font);
}
void Game::Render_Elements() const {
    // 加载人物、武器、子弹、怪物
    if (hero) {
        hero->render(MousePos);
        if (hero->getWeapon()) {
            hero->getWeapon()->UpdatePos(hero->getWeaponPoint().x + hero->getX(), hero->getWeaponPoint().y + hero->getY());
            hero->getWeapon()->render(hero->get_DirAttack(), hero->get_Dir());
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
            hero->Sub_energy(-5);
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
void Game::Fire() const {
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
void Game::CreateHero() {
    Mix_Chunk *chunk;
    Load_Chunk(chunk, "../rsc/mixer/Create Hero.wav");
    SDL_Delay(500);
    Mix_FreeChunk(chunk);
    if (!hero)
        hero = new Hero(hero_1);
    if (hero && !hero->getWeapon()) {
        hero->setWeapon(new Weapon_type_1(weapon_1, bullets_hero));
    }
    if (!level)
        level = new Level1();
}
void Game::level_control() {
    if (level) {
        if (!level->getRunning(0))
            level->run();
        else if (monster.empty() && !level->getPass(0)) {
            level->setPass(0);
            if (!level->getRunning(1)) {
                level->run();
            }
        }
        else if (monster.empty() && !level->getPass(1)) {
            level->setPass(1);
            if (!level->getRunning(2)) {
                level->run();
            }
        }
        else if (monster.empty() && !level->getPass(2)) {
            level->setPass(2);
            delete level;
            level = nullptr;
            Mix_FreeMusic(music);
            showSystemMessageBox("You Win!", "INFO");
            IsQuit = true;
        }
    }
}
