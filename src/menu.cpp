//
// Created by lixh1 on 25-2-8.
//
#include <menu.h>
#include <game.h>


int Menu::screenWidth[2] = {WINDOW_WIDTH, WINDOW_WIDTH};
int Menu::screenHeight[2] = {WINDOW_HEIGHT, WINDOW_HEIGHT};

Mix_Music *menu_music;

Menu::~Menu() {
    SDL_DestroyTexture(render_target);
}


void Menu::menu() {
    Load_Music(menu_music, "../rsc/mixer/Mr.Cat - Bit Piano Music.mp3");
    bool IsQuit = false;
    SDL_Event event;
    init_widget();
    render_target = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1500,1000);
    while (!IsQuit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                IsQuit = true;
            }
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.scancode) {
                    case SDL_SCANCODE_ESCAPE:
                        IsQuit = true;
                        LOG("Esc Pressed");
                        break;
                    case SDL_SCANCODE_UP:
                    case SDL_SCANCODE_LEFT:
                        prev_widget();
                        LOG("Last");
                        break;
                    case SDL_SCANCODE_DOWN:
                    case SDL_SCANCODE_RIGHT:
                        next_widget();
                        LOG("Next");
                        break;
                    case SDL_SCANCODE_SPACE:
                    case SDL_SCANCODE_RETURN:
                        act_widget();
                    default:
                        break;
                }
            }
            if (event.type == SDL_WINDOWEVENT) {
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

        }
        menu_render();
    }
    quit_widget();
    SDL_DestroyTexture(render_target);
}
void Menu::menu_render() const {
    SDL_SetRenderTarget(app.renderer, render_target);
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    Render_ground_menu();

    Render_Title();

    Render_Widgets();
    SDL_SetRenderTarget(app.renderer, nullptr); // 重置渲染目标为默认（屏幕）
    const SDL_Rect screenDstRect = {(screenWidth[0] - screenWidth[1]) / 2, (screenHeight[0] - screenHeight[1]) / 2, screenWidth[1], screenHeight[1]};
    SDL_RenderCopy(app.renderer, render_target, nullptr, &screenDstRect);
    Present();
}
void Menu::init_widget() {
    widgets = new Widget[WIDGET_NUM];
    widgets[0] = (Widget){"Start", WIDGET_POS_X, WIDGET_POS_Y_TOP, start_action};
    widgets[1] = (Widget){"Exit", WIDGET_POS_X, WIDGET_POS_Y_TOP + WIDGET_POS_Y_GAP, exit_action};
}
void Menu::quit_widget() const {
    delete[] widgets;
}
void Menu::prev_widget() {
    Mix_Chunk *chunk;
    Load_Chunk(chunk, "../rsc/mixer/Change.wav");
    SDL_Delay(50);
    selection = (selection - 1 + WIDGET_NUM) % WIDGET_NUM;
    Mix_FreeChunk(chunk);
}
void Menu::next_widget() {
    Mix_Chunk *chunk;
    Load_Chunk(chunk, "../rsc/mixer/Change.wav");
    SDL_Delay(50);
    selection = (selection + 1) % WIDGET_NUM;
    Mix_FreeChunk(chunk);
}
void Menu::act_widget() const {
    if (const Action action = widgets[selection].action) {
        action();
    }
}
void Menu::start_action() {
    Mix_Chunk *chunk;
    Load_Chunk(chunk, "../rsc/mixer/Click.wav");
    SDL_Delay(1000);
    SDL_Log("Start");
    Mix_FreeMusic(menu_music);
    newgame = new Game(screenWidth[0], screenWidth[1], screenHeight[0], screenHeight[1]);
    newgame->game();
    Load_Music(menu_music, "../rsc/mixer/Mr.Cat - Bit Piano Music.mp3");
    delete newgame;
    newgame = nullptr;
    Mix_FreeChunk(chunk);
}
void Menu::exit_action(){
    Mix_Chunk *chunk;
    Load_Chunk(chunk, "../rsc/mixer/Click.wav");
    LOG("Exit");
    SDL_Delay(1000);
    Mix_FreeChunk(chunk);
    Mix_FreeMusic(menu_music);
    exit(0);
}
void Menu::Render_Widgets() const {
    TTF_Font *font = TTF_OpenFont("../rsc/font/svgafix.fon", 80);
    for (int i = 0; i < WIDGET_NUM; i++) {
        SDL_Texture *texture = nullptr;
        Load_Text(texture, font, widgets[i].text, i == selection ? WHITE : GRAY);
        const int w = i == selection ? WIDGET_W : WIDGET_W * 0.8;
        const int h = i == selection ? WIDGET_H : WIDGET_H * 0.8;
        const double x = i == selection ? widgets[i].x : widgets[i].x + WIDGET_W * 0.1 ;
        const double y = i == selection ? widgets[i].y : widgets[i].y + WIDGET_H * 0.1 ;
        SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), w, h};
        SDL_RenderCopy(app.renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
    }
    TTF_CloseFont(font);
}
void Menu::Render_Title() {
    TTF_Font *font = TTF_OpenFont("../rsc/font/Darinia.ttf", 100);
    SDL_Texture *texture = nullptr;
    Load_Text(texture, font, "KNIGHT", RED);
    constexpr SDL_Rect rect = {TITLE_X, TITLE_Y, TITLE_W, TITLE_H};
    SDL_RenderCopy(app.renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
void Menu::Render_ground_menu() {
    SDL_Texture *texture = nullptr;
    Load_Image(texture, "../rsc/sundry/mystery-forest.png");
    constexpr SDL_Rect groundRect = {0, 0, 1500, 1000};
    SDL_RenderCopy(app.renderer, texture, nullptr, &groundRect);
    SDL_DestroyTexture(texture);
}