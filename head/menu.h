//
// Created by lixh1 on 25-2-8.
//

#ifndef MENU_H
#define MENU_H

#include <common.h>

constexpr int TITLE_X = 500;
constexpr int TITLE_Y = 200;
constexpr int TITLE_W = 500;
constexpr int TITLE_H = 200;
constexpr int WIDGET_NUM = 2;
constexpr int WIDGET_POS_X = 650;
constexpr int WIDGET_POS_Y_TOP = 600;
constexpr int WIDGET_POS_Y_GAP = 80;
constexpr int WIDGET_W = 200;
constexpr int WIDGET_H = 100;

typedef void (*Action)();

typedef struct {
    char const *text;
    int x, y;
    Action action;
} Widget;

class Menu {
    Widget *widgets;
    int selection;
    static int screenWidth[2];
    static int screenHeight[2];
    SDL_Texture *render_target;
public:
    Menu(): widgets(nullptr), selection(0), render_target(nullptr) {}
    ~Menu();
    void menu();
    void menu_render() const;
    void init_widget();
    void quit_widget() const;
    void prev_widget();
    void next_widget();
    void act_widget() const;
    static void start_action();
    static void exit_action();
    void Render_Widgets() const;
    static void Render_Title();
    static void Render_ground_menu();
};


#endif //MENU_H
