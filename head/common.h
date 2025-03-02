//
// Created by lixh1 on 25-2-5.
//

#ifndef COMMON_H
#define COMMON_H


#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <complex>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <fstream>
#include <iostream>
#include <json.hpp>
#include <memory>
#include <random>
#include <vector>
#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

#define LOG(x) SDL_Log(x)
#define LOG_ERROR(msg) SDL_Log(msg " Failed: %s", SDL_GetError());\
        exit(EXIT_FAILURE);


constexpr int WINDOW_WIDTH = 1500;
constexpr int WINDOW_HEIGHT = 1000;
constexpr int FUNCTION_WIDTH = 269;
constexpr int FUNCTION_HEIGHT = 134;
constexpr double Root_2 = sqrt(2);
constexpr int FPS = 30;                     //帧率


constexpr SDL_Color WHITE = {255,255,255,255};
constexpr SDL_Color BLACK = {0,0,0,0};
constexpr SDL_Color RED = {255,0,0,0};
constexpr SDL_Color GREEN = {0,255,0,0};
constexpr SDL_Color BLUE = {0,0,255,0};
constexpr SDL_Color YELLOW = {255,255,0,0};
constexpr SDL_Color MAGENTA = {255,0,255,0};
constexpr SDL_Color CYAN = {0,255,0,255};
constexpr SDL_Color GRAY = {200,200,200,255};
constexpr SDL_Color Green2 = {99,199,77,0};


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


class Collider {
protected:
    SDL_Rect collider{};
public:
    Collider(int x, int y, int width, int height);
    [[nodiscard]] bool checkCollision(const Collider& other) const {return SDL_HasIntersection(&collider, &other.collider);}
    [[nodiscard]] const SDL_Rect *getCollider() const {return &collider;}
    void setColliderPosition(const int x, const int y) {collider.x = x;collider.y = y;}
    void setColliderSize(const int width, const int height) {collider.w = width;collider.h = height;}
};
class Timer {
protected:
    mutable Uint32 last_time;
    mutable Uint32 current_time;
    Uint32 time_gap;
public:
    virtual ~Timer() = default;

    explicit Timer(const Uint32 time_gap):last_time(0), current_time(0), time_gap(time_gap){}
    [[nodiscard]] bool Time_out() const;
    void Reset(Uint32 x);
    void set_LastTime(const Uint32 x) const {last_time = x;}
};


extern APP app;
inline SDL_Texture* background_texture = nullptr;
inline SDL_Texture* fps_texture = nullptr;
inline Mix_Music *music;

inline void Present(){
    SDL_RenderPresent(app.renderer);
}
inline double getDegree(const Direction dir) {
    const double radians = atan(dir.dy / dir.dx);
    const double degree = radians * (180.0f / M_PI);
    return degree;
}
inline void Load_Image(SDL_Texture *&texture, const std::string &imagePath) {
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
inline void Load_Text(SDL_Texture *&texture, TTF_Font *font, const std::string& text, const SDL_Color color) {
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
inline void Load_Music(Mix_Music *&music, const std::string& musicPath) {
    music = Mix_LoadMUS(musicPath.c_str());
    if (music == nullptr) {
        LOG_ERROR("Music Load");
    }
    if (Mix_PlayMusic(music, -1) == -1) {
        LOG_ERROR("Music Play");
    }
    Mix_VolumeMusic(8);
}
inline void Load_Chunk(Mix_Chunk *&chunk, const std::string& chunkPath) {
    chunk = Mix_LoadWAV(chunkPath.c_str());
    if (chunk == nullptr) {
        LOG_ERROR("Chunk Load");
    }
    if (Mix_PlayChannel(-1, chunk, 0) == -1) {
        LOG_ERROR("Chunk Play");
    }
    Mix_VolumeChunk(chunk, 8);
}
inline double Distance(const Position p1, const Position p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

inline void showSystemMessageBox(const char* message, const char* title) {
#ifdef _WIN32
    // Windows 系统使用 MessageBox
    MessageBox(nullptr, message, title, MB_OK | MB_ICONEXCLAMATION);
#else
    // 其他系统使用系统命令调用对话框工具
    std::string command = "zenity --error --title=\"" + std::string(title) + "\" --text=\"" + std::string(message) + "\"";
    system(command.c_str());
#endif
}
#endif //COMMON_H
