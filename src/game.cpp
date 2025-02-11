//
// Created by lixh1 on 25-2-8.
//
#include <game.h>

Position MousePos = { 750.0, 500.0 };
int fps = 0;
Uint32 tick;
Hero *hero = nullptr;
bool IsQuit = false;



void game() {

    tick = SDL_GetTicks();
    constexpr int wall_num = std::size(walls_1);
    for (int i = 0; i < wall_num; i++) {
        walls.emplace_back(walls_1[i][0], walls_1[i][1], walls_1[i][2], walls_1[i][3]);
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
            bi_control();
        }

        if (hero){hero->Move(MousePos);}

        display();

        SDL_Delay(1000 / FPS);
    }
    IsQuit = false;
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
            hero->getWeapon()->UpdatePos(hero->getX(), hero->getY() - 20);
            hero->getWeapon()->render(MousePos);
        }
    }

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
void do_keydown(const SDL_Event &event) {
    switch (event.key.keysym.scancode) {
        case SDL_SCANCODE_ESCAPE:
            LOG("Escape Key Pressed");
        IsQuit = true;
        break;
        case SDL_SCANCODE_SPACE:
            LOG("Space Key Pressed");
        if (!hero)
            hero = new Hero(hero_1);
        break;
        case SDL_SCANCODE_RETURN:
            LOG("Return Key Pressed");
        if (hero && !hero->getWeapon()) {
            hero->setWeapon(new Weapon(weapon_1));
        }
        break;
        // case SDL_SCANCODE_UP:
        // case SDL_SCANCODE_W:
        //     LOG("Up Key Pressed");
        // if (hero != nullptr)
        //     hero->Move(0.0, -hero->getSpeed());
        // break;
        // case SDL_SCANCODE_DOWN:
        // case SDL_SCANCODE_S:
        //     LOG("Down Key Pressed");
        // if (hero != nullptr)
        //     hero->Move(0.0, hero->getSpeed());
        // break;
        // case SDL_SCANCODE_LEFT:
        // case SDL_SCANCODE_A:
        //     LOG("Left Key Pressed");
        // if (hero != nullptr)
        //     hero->Move(-hero->getSpeed(), 0.0);
        // break;
        // case SDL_SCANCODE_RIGHT:
        // case SDL_SCANCODE_D:
        //     LOG("Right Key Pressed");
        // if (hero != nullptr)
        //     hero->Move(hero->getSpeed(), 0.0);
        // break;
        default:
            break;
    }
}
void do_mouse_down(const SDL_Event &event) {
    if (event.button.button == SDL_BUTTON_LEFT) {
        MousePos.x = event.button.x;
        MousePos.y = event.button.y;
        if (hero != nullptr){
            if (Weapon *w = hero->getWeapon(); w != nullptr){
                w->UpdatePos(hero->getX(), hero->getY() - 20);
                w->UpdateDir(MousePos.x, MousePos.y);
                if (hero->getEnergy() - hero->getWeapon()->get_EnergyConsumed() >= 0){
                    w->Attack();
                    hero->Sub_energy(hero->getWeapon()->get_EnergyConsumed());
                }
            }
        }
    }
}
void do_mouse_motion(const SDL_Event &event) {
    MousePos.x = event.motion.x;
    MousePos.y = event.motion.y;
}
void bi_control() {
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    if ((keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_D])
        || (keyState[SDL_SCANCODE_UP] && keyState[SDL_SCANCODE_RIGHT])) {
        LOG("Up and Right Key Pressed");
        if (hero != nullptr)
            hero->Move(hero->getSpeed() / Root_2, -hero->getSpeed() / Root_2);
    }
    if ((keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_A])
        || (keyState[SDL_SCANCODE_DOWN] && keyState[SDL_SCANCODE_LEFT])) {
        LOG("Down and Left Key Pressed");
        if (hero != nullptr)
            hero->Move(-hero->getSpeed() / Root_2, hero->getSpeed() / Root_2);
    }
    if ((keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_A])
        || (keyState[SDL_SCANCODE_UP] && keyState[SDL_SCANCODE_LEFT])) {
        LOG("Up and Left Key Pressed");
        if (hero != nullptr)
            hero->Move(-hero->getSpeed() / Root_2, -hero->getSpeed() / Root_2);
    }
    if ((keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_D])
        || (keyState[SDL_SCANCODE_DOWN] && keyState[SDL_SCANCODE_RIGHT])) {
        LOG("Down and Right Key Pressed");
        if (hero != nullptr)
            hero->Move(hero->getSpeed() / Root_2, hero->getSpeed() / Root_2);
    }
    if (keyState[SDL_SCANCODE_UP] || keyState[SDL_SCANCODE_W]) {
        if (hero != nullptr) {
            hero->Move(0.0, -hero->getSpeed());
        }
    }
    if (keyState[SDL_SCANCODE_DOWN] || keyState[SDL_SCANCODE_S]) {
        if (hero != nullptr) {
            hero->Move(0.0, hero->getSpeed());
        }
    }
    if (keyState[SDL_SCANCODE_LEFT] || keyState[SDL_SCANCODE_A]) {
        if (hero != nullptr) {
            hero->Move(-hero->getSpeed(), 0.0);
        }
    }
    if (keyState[SDL_SCANCODE_RIGHT] || keyState[SDL_SCANCODE_D]) {
        if (hero != nullptr) {
            hero->Move(hero->getSpeed(), 0.0);
        }
    }
}