//
// Created by lixh1 on 25-2-8.
//

#ifndef GAME_H
#define GAME_H

#include <Elements/Hero.h>

void game();

void Render_background();
void Render_fps(int);
void display();
void do_keydown(const SDL_Event &);
void do_mouse_down(const SDL_Event &);
void do_mouse_motion(const SDL_Event &);
void bi_control();

#endif //GAME_H
