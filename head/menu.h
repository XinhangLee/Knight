//
// Created by lixh1 on 25-2-8.
//

#ifndef MENU_H
#define MENU_H

#include <common.h>
#include <game.h>

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

void menu();
void menu_render();
void init_widget();
void quit_widget();
void prev_widget();
void next_widget();
void act_widget();
void start_action();
void exit_action();
void Render_Widgets();
void Render_Title();
void Render_ground_menu();

#endif //MENU_H
