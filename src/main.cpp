#include <main.h>
#include <Elements/Hero.h>
#include <tools/Init.h>
#include <tools/Quit.h>

APP app;
Hero *hero = nullptr;

int main(int argc, char* argv[]) {
    init_app();

    app.window = SDL_CreateWindow("SDL2 Window",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN);
    if (app.window == nullptr) {
        LOG_ERROR("Window Create");
    }
    LOG("Window Created Successfully!");
    app.renderer = SDL_CreateRenderer(app.window,-1, 0);
    if (app.renderer == nullptr) {
        LOG_ERROR("Renderer Create");
    }
    LOG("Renderer Created Successfully!");
    SDL_Texture* background_texture;
    LoadImage(background_texture, app.renderer, "../rsc/background.png", "Background");


    bool IsQuit = false;
    while (!IsQuit) {
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
                        case SDL_SCANCODE_UP:
                        case SDL_SCANCODE_W:
                            LOG("Up Key Down");
                            if (hero != nullptr)
                                hero->Move(0.0, -5.0);
                        break;
                        case SDL_SCANCODE_DOWN:
                        case SDL_SCANCODE_S:
                            LOG("Down Key Down");
                            if (hero != nullptr)
                                hero->Move(0.0, 5.0);
                        break;
                        case SDL_SCANCODE_LEFT:
                        case SDL_SCANCODE_A:
                            LOG("Left Key Down");
                            if (hero != nullptr)
                                hero->Move(-5.0, 0.0);
                        break;
                        case SDL_SCANCODE_RIGHT:
                        case SDL_SCANCODE_D:
                            LOG("Right Key Down");
                            if (hero != nullptr)
                                hero->Move(5.0, 0.0);
                        break;
                        default:
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    break;
                case SDL_MOUSEBUTTONUP:
                    break;
                case SDL_MOUSEMOTION:
                    break;
                default:
                    break;
            }
            const Uint8* keyState = SDL_GetKeyboardState(nullptr);

            if (keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_D]) {
                LOG("Up and Right Key Down");
                if (hero != nullptr)
                    hero->Move(5.0, -5.0);
            }
            if (keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_A]) {
                LOG("Down and Left Key Down");
                if (hero != nullptr)
                    hero->Move(-5.0, 5.0);
            }
            if (keyState[SDL_SCANCODE_W] && keyState[SDL_SCANCODE_A]) {
                LOG("Up and Left Key Down");
                if (hero != nullptr)
                    hero->Move(-5.0, -5.0);
            }
            if (keyState[SDL_SCANCODE_S] && keyState[SDL_SCANCODE_D]) {
                LOG("Down and Right Key Down");
                if (hero != nullptr)
                    hero->Move(5.0, 5.0);
            }
            SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
            SDL_RenderClear(app.renderer);

            SDL_RenderCopy(app.renderer, background_texture, nullptr, nullptr);
            if (hero) {
                hero->render(app.renderer);
            }

            Present();
        }
    }

    delete hero;
    SDL_DestroyTexture(background_texture);
    LOG("Background_Texture Destroyed!");
    atexit(&quit_app);

    return 0;
}