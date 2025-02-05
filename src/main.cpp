#include <main.h>
#include <tools/Init.h>
#include <tools/Quit.h>

APP app;

int main(int argc, char* argv[]) {
    init_app();

    app.window = SDL_CreateWindow("SDL2 Window",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS);
    if (app.window == nullptr) {
        LOG_ERROR("Window Create");
    }
    LOG("Window Created Successfully!");
    app.renderer = SDL_CreateRenderer(app.window,-1, 0);
    if (app.renderer == nullptr) {
        LOG_ERROR("Renderer Create");
    }
    LOG("Renderer Created Successfully!");
    SDL_Surface* background_surface = IMG_Load("../rsc/background.png");
    if (background_surface == nullptr) {
        LOG_ERROR("Background Load");
    }
    LOG("Background Loaded Successfully!");
    SDL_Texture* background_texture = SDL_CreateTextureFromSurface(app.renderer, background_surface);
    if (background_texture == nullptr) {
        LOG_ERROR("Background Texture Create");
    }
    LOG("Background Texture Created Successfully!");
    SDL_FreeSurface(background_surface);


    bool IsQuit = false;
    while (!IsQuit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    IsQuit = true;
                break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        IsQuit = true;
                    break;
                case SDL_KEYUP:
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
            SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
            SDL_RenderClear(app.renderer);

            // 渲染背景
            SDL_RenderCopy(app.renderer, background_texture, nullptr, nullptr);

            // 呈现内容
            SDL_RenderPresent(app.renderer);
        }
    }

    SDL_DestroyTexture(background_texture);
    atexit(&quit_app);

    return 0;
}