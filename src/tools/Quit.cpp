//
// Created by lixh1 on 25-2-5.
//
#include <tools\Quit.h>

void quit_app(){
    delete hero;
    SDL_DestroyTexture(background_texture);
    LOG("Background_Texture Destroyed!");
    SDL_DestroyRenderer(app.renderer);
    LOG("Renderer Destroyed!");
    SDL_DestroyWindow(app.window);
    LOG("Window Destroyed!");
    SDL_Quit();
    LOG("SDL Quit Successfully!");
    IMG_Quit();
    LOG("IMG Quit Successfully!");
    TTF_Quit();
    LOG("TTF Quit Successfully!");
}