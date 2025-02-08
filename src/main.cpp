#include <main.h>
#include <game.h>


APP app;




int main(int argc, char* argv[]) {
    init_app();

    game();

    atexit(&quit_app);
    return 0;
}




void init_app() {
    // SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG_ERROR("SDL Init");
    }
    LOG("SDL Init Successfully!");

    // IMG
    if (!(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG)) {
        LOG_ERROR("IMG Init");
    }
    LOG("IMG Init Successfully!");

    // TTF
    if (TTF_Init() == -1) {
        LOG_ERROR("TTF Init");
    }
    LOG("TTF Init Successfully!");

    Create_Window_Renderer();
}

void quit_app(){
    delete hero;
    SDL_DestroyTexture(background_texture);
    SDL_DestroyTexture(fps_texture);
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
}

void Create_Window_Renderer() {
    app.window = SDL_CreateWindow("S_Knight",
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGHT,
                                    SDL_WINDOW_SHOWN | SDL_WINDOW_MOUSE_FOCUS);
    if (app.window == nullptr) {
        LOG_ERROR("Window Create");
    }
    app.renderer = SDL_CreateRenderer(app.window,-1, 0);
    if (app.renderer == nullptr) {
        LOG_ERROR("Renderer Create");
    }
}
