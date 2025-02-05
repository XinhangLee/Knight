//
// Created by lixh1 on 25-2-5.
//

#ifndef COMMON_H
#define COMMON_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>

#define LOG(x) SDL_Log(x)
#define LOG_ERROR(msg) SDL_Log(msg " Failed: %s", SDL_GetError());\
        exit(EXIT_FAILURE);


constexpr int WINDOW_WIDTH = 1000;
constexpr int WINDOW_HEIGHT = 1000;

typedef struct App {
    SDL_Window* window;
    SDL_Renderer* renderer;
} APP;

extern APP app;

#endif //COMMON_H
