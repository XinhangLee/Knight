//
// Created by lixh1 on 25-2-8.
//

#ifndef GAME_H
#define GAME_H

#include <Level.h>


class Game {
    Position MousePos;
    int fps;
    Uint32 tick;
    bool IsQuit;
    bool Stop;
    int screenWidth[2];
    int screenHeight[2];
    SDL_Texture *render_target;
public:
    Game(const int x1, const int x2, const int y1, const int y2):MousePos({750.0,460.0}), fps(0), tick(0) , IsQuit(false), Stop(false),screenWidth{x1, x2},screenHeight{y1, y2},render_target(nullptr) {
        render_target = SDL_CreateTexture(app.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 1500,1000);
        Load_Music(music, "../rsc/mixer/Lotus Pond.wav");
    }
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
    void do_window_event(const SDL_Event &);
    void Fire() const;
    static void CreateHero();
    void level_control();
};

extern Game *newgame;


#endif //GAME_H
