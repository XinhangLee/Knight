//
// Created by lixh1 on 25-2-5.
//
#include <tools/Init.h>

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
}