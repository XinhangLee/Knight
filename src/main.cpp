#include <main.h>
#include <menu.h>


APP app;
Menu menu;

#undef main


int main() {
    init_app();

    menu.menu();

    atexit(&quit_app);
    return 0;
}




void init_app() {
    // SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG_ERROR("SDL Init");
    }

    // IMG
    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
        LOG_ERROR("IMG Init");
    }

    // TTF
    if (TTF_Init() == -1) {
        LOG_ERROR("TTF Init");
    }

    // MIXER
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        LOG_ERROR("Mix OpenAudio");
    }

    Create_Window_Renderer();
}

void quit_app(){
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_CloseAudio();
}

void Create_Window_Renderer() {
    app.window = SDL_CreateWindow("S_Knight",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN
                                    // | SDL_WINDOW_MOUSE_GRABBED
                                    // | SDL_WINDOW_BORDERLESS
                                    // | SDL_WINDOW_ALWAYS_ON_TOP
                                    // | SDL_WINDOW_FULLSCREEN_DESKTOP
                                    | SDL_WINDOW_ALLOW_HIGHDPI
                                    | SDL_WINDOW_RESIZABLE
                                    );
    if (app.window == nullptr) {
        LOG_ERROR("Window Create");
    }
    // SDL_SetWindowMinimumSize(app.window, WINDOW_WIDTH, WINDOW_HEIGHT);
    // SDL_SetWindowMaximumSize(app.window, WINDOW_WIDTH, WINDOW_HEIGHT);
    app.renderer = SDL_CreateRenderer(app.window,-1, 0);
    if (app.renderer == nullptr) {
        LOG_ERROR("Renderer Create");
    }
}
