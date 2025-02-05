//
// Created by lixh1 on 25-2-5.
//
#include <tools\Quit.h>

void quit_app(){
    SDL_DestroyRenderer(app.renderer);
    SDL_DestroyWindow(app.window);
    SDL_Quit();
    LOG("SDL Quit Successfully!");
    IMG_Quit();
    LOG("IMG Quit Successfully!");
}