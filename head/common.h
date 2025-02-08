//
// Created by lixh1 on 25-2-5.
//

#ifndef COMMON_H
#define COMMON_H


#include <SDL2/SDL.h>
// #include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

#define LOG(x) SDL_Log(x)
#define LOG_ERROR(msg) SDL_Log(msg " Failed: %s", SDL_GetError());\
        exit(EXIT_FAILURE);


constexpr int WINDOW_WIDTH = 1500;
constexpr int WINDOW_HEIGHT = 1000;
constexpr double Root_2 = sqrt(2);
constexpr int FPS = 60;                     //帧率


constexpr SDL_Color WHITE = {255,255,255,255};
constexpr SDL_Color BLACK = {0,0,0,0};
constexpr SDL_Color RED = {255,0,0,0};
constexpr SDL_Color GREEN = {0,255,0,0};
constexpr SDL_Color BLUE = {0,0,255,0};
constexpr SDL_Color YELLOW = {255,255,0,0};


typedef struct App {
    SDL_Window* window;
    SDL_Renderer* renderer;
} APP;
typedef struct POSITION {
    double x;
    double y;
} Position;
typedef struct DIRECTION {
    double dx;
    double dy;
} Direction;


extern APP app;
inline SDL_Texture* background_texture = nullptr;
inline SDL_Texture* fps_texture = nullptr;



inline void Present(){
    SDL_RenderPresent(app.renderer);
}
inline double getDegree(const Direction dir) {
    const double radians = atan(dir.dy / dir.dx);
    const double degree = radians * (180.0f / M_PI);
    return degree;
}
inline void LoadImage(SDL_Texture *&texture, const std::string &imagePath) {
    SDL_Surface* surface = IMG_Load(imagePath.c_str());
    if (surface == nullptr) {
        LOG_ERROR("Image Load");
    }
    texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        LOG_ERROR("Texture Create");
    }
}
inline void LoadText(SDL_Texture *&texture, TTF_Font *font, const std::string& text, const SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
    if (surface == nullptr) {
        LOG_ERROR("Text Render");
    }
    texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) {
        LOG_ERROR("Texture Create");
    }
}

#endif //COMMON_H
