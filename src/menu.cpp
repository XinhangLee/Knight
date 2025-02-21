//
// Created by lixh1 on 25-2-8.
//
#include <menu.h>

static Widget *widgets;
static int selection = 0;

void menu() {
    bool IsQuit = false;
    SDL_Event event;
    init_widget();
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

        }
        menu_render();
    }
    quit_widget();
}
void menu_render() {
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 255);
    SDL_RenderClear(app.renderer);
    Render_ground_menu();

    Render_Title();

    Render_Widgets();

    Present();
}
void init_widget() {
    widgets = new Widget[WIDGET_NUM];
    widgets[0] = (Widget){"Start", WIDGET_POS_X, WIDGET_POS_Y_TOP, start_action};
    widgets[1] = (Widget){"Exit", WIDGET_POS_X, WIDGET_POS_Y_TOP + WIDGET_POS_Y_GAP, exit_action};
}
void quit_widget() {
    delete[] widgets;
}
void prev_widget() {
    selection = (selection - 1 + WIDGET_NUM) % WIDGET_NUM;
}
void next_widget() {
    selection = (selection + 1) % WIDGET_NUM;
}
void act_widget() {
    if (const Action action = widgets[selection].action) {
        action();
    }
}
void start_action() {
    LOG("Start");
    newgame = new Game();
    if (newgame){
        newgame->game();
        delete newgame;
        newgame = nullptr;
    }
    exit(0);
}
void exit_action() {
    LOG("Exit");
    exit(0);
}
void Render_Widgets() {
    TTF_Font *font = TTF_OpenFont("../rsc/svgafix.fon", 80);
    for (int i = 0; i < WIDGET_NUM; i++) {
        SDL_Texture *texture = nullptr;
        LoadText(texture, font, widgets[i].text, i == selection ? GRAY : WHITE);
        const int w = i == selection ? WIDGET_W * 0.8: WIDGET_W;
        const int h = i == selection ? WIDGET_H * 0.8: WIDGET_H;
        const double x = i == selection ? widgets[i].x + WIDGET_W * 0.1 : widgets[i].x;
        const double y = i == selection ? widgets[i].y + WIDGET_H * 0.1 : widgets[i].y;
        SDL_Rect rect = {static_cast<int>(x), static_cast<int>(y), w, h};
        SDL_RenderCopy(app.renderer, texture, nullptr, &rect);
        SDL_DestroyTexture(texture);
    }
    TTF_CloseFont(font);
}
void Render_Title() {
    TTF_Font *font = TTF_OpenFont("../rsc/svgafix.fon", 100);
    SDL_Texture *texture = nullptr;
    LoadText(texture, font, "KNIGHT", RED);
    constexpr SDL_Rect rect = {TITLE_X, TITLE_Y, TITLE_W, TITLE_H};
    SDL_RenderCopy(app.renderer, texture, nullptr, &rect);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
}
void Render_ground_menu() {
    SDL_Texture *texture = nullptr;
    LoadImage(texture, "../rsc/mystery-forest.png");
    constexpr SDL_Rect groundRect = {0, 0, 1500, 1000};
    SDL_RenderCopy(app.renderer, texture, nullptr, &groundRect);
    SDL_DestroyTexture(texture);
}