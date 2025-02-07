#include <tools/Control.h>

void control() {
    Uint64 lastCounter = SDL_GetPerformanceCounter();
    const Uint64 counterFreq = SDL_GetPerformanceFrequency();
    bool IsQuit = false;
    Position MousePos = { 0.0, 0.0 };
    while (!IsQuit) {
        const Uint64 currentCounter = SDL_GetPerformanceCounter();
        const double deltaTime = static_cast<double>(currentCounter - lastCounter) / static_cast<double>(counterFreq);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    IsQuit = true;
                break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.scancode) {
                        case SDL_SCANCODE_ESCAPE:
                            LOG("Escape Key Down");
                            IsQuit = true;
                        break;
                        case SDL_SCANCODE_SPACE:
                            LOG("Space Key Down");
                            if (!hero)
                                hero = new Hero(app.renderer, "../rsc/Hero.png");
                        break;
                        case SDL_SCANCODE_RETURN:
                            LOG("Return Key Down");
                            if (hero && !hero->getWeapon()) {
                                hero->setWeapon(new Weapon(app.renderer, "../rsc/Shotgun.png"));
                            }
                        case SDL_SCANCODE_UP:
                        case SDL_SCANCODE_W:
                            LOG("Up Key Down");
                            if (hero != nullptr)
                                hero->Move(0.0, -hero->getSpeed());
                        break;
                        case SDL_SCANCODE_DOWN:
                        case SDL_SCANCODE_S:
                            LOG("Down Key Down");
                            if (hero != nullptr)
                                hero->Move(0.0, hero->getSpeed());
                        break;
                        case SDL_SCANCODE_LEFT:
                        case SDL_SCANCODE_A:
                            LOG("Left Key Down");
                            if (hero != nullptr)
                                hero->Move(-hero->getSpeed(), 0.0);
                        break;
                        case SDL_SCANCODE_RIGHT:
                        case SDL_SCANCODE_D:
                            LOG("Right Key Down");
                            if (hero != nullptr)
                                hero->Move(hero->getSpeed(), 0.0);
                        break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        MousePos.x = event.button.x;
                        MousePos.y = event.button.y;
                        if (hero != nullptr){
                            Weapon *w = hero->getWeapon();
                            if (w != nullptr){
                                w->UpdatePos(hero->getX(), hero->getY());
                                w->UpdateDir(MousePos.x, MousePos.y);
                                w->Attack(app.renderer);
                            }
                        }
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
                case SDL_MOUSEMOTION:
                    MousePos.x = event.motion.x;
                    MousePos.y = event.motion.y;
                    break;
                default:;
                    break;
            }
            const Uint8* keyState = SDL_GetKeyboardState(nullptr);

            if ((keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_D])
                || (keyState[SDL_SCANCODE_UP] && keyState[SDL_SCANCODE_RIGHT])) {
                LOG("Up and Right Key Down");
                if (hero != nullptr)
                    hero->Move(hero->getSpeed() / Root_2, -hero->getSpeed() / Root_2);
            }
            if ((keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_A])
                || (keyState[SDL_SCANCODE_DOWN] && keyState[SDL_SCANCODE_LEFT])){
                LOG("Down and Left Key Down");
                if (hero != nullptr)
                    hero->Move(-hero->getSpeed() / Root_2, hero->getSpeed() / Root_2);
            }
            if ((keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_A])
                || (keyState[SDL_SCANCODE_UP] && keyState[SDL_SCANCODE_LEFT])){
                LOG("Up and Left Key Down");
                if (hero != nullptr)
                    hero->Move(-hero->getSpeed() / Root_2, -hero->getSpeed() / Root_2);
            }
            if ((keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_D])
                || (keyState[SDL_SCANCODE_DOWN] && keyState[SDL_SCANCODE_RIGHT])){
                LOG("Down and Right Key Down");
                if (hero != nullptr)
                    hero->Move(hero->getSpeed() / Root_2, hero->getSpeed() / Root_2);
            }
            SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
            SDL_RenderClear(app.renderer);

            Render_background();

            if (hero) {
                hero->render(app.renderer);
                if (hero->getWeapon()) {
                    hero->getWeapon()->UpdatePos(hero->getX(), hero->getY());
                    hero->getWeapon()->UpdateDir(MousePos.x, MousePos.y);
                    hero->getWeapon()->render(app.renderer, MousePos);
                }
            }

            Present();
            if (const double delayTime = frameTime - deltaTime; delayTime > 0) {
                SDL_Delay(static_cast<Uint32>(delayTime * 1000));
            }
            lastCounter = currentCounter;
        }
    }
}

void Render_background() {
    LoadImage(background_texture, app.renderer, "../rsc/background.png", "Background");
    constexpr SDL_Rect backgroundRect = {250, 0, 1007, 1000};
    SDL_RenderCopy(app.renderer, background_texture, nullptr, &backgroundRect);
}