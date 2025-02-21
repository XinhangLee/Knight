//
// Created by lixh1 on 25-2-8.
//

#ifndef GAME_H
#define GAME_H

#include <Elements/Hero.h>
#include <Level.h>


class Game {
    Position MousePos;
    int fps;
    Uint32 tick;
    bool IsQuit;
    bool Stop;
public:
    Game():MousePos({750.0,460.0}), fps(0), tick(0) , IsQuit(false), Stop(false){}
    ~Game();
    void game();
    static void Render_ground_game();
    static void Render_background();
    static void Render_fps(int);
    void Render_Elements() const;
    void display();
    void do_keydown(const SDL_Event &);
    void do_mouse_down(const SDL_Event &) const;
    void do_mouse_motion(const SDL_Event &);
    void Fire() const;
    static void CreateHero();
    void level_control();
};

extern Game *newgame;


#endif //GAME_H
