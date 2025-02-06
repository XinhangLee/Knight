#include <main.h>
#include <Elements/Hero.h>
#include <tools/Control.h>
#include <tools/Init.h>
#include <tools/Quit.h>

APP app;
Hero *hero = nullptr;

void Create_Window_Renderer();


int main(int argc, char* argv[]) {
    init_app();

    Create_Window_Renderer();

    control();

    atexit(&quit_app);

    return 0;
}


void Create_Window_Renderer() {
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
}
