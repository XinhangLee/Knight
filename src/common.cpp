//
// Created by lixh1 on 25-2-14.
//
#include <common.h>

Collider::Collider(const int x, const int y, const int width, const int height) {
    collider.x = x;
    collider.y = y;
    collider.w = width;
    collider.h = height;
}
bool Timer::Time_out() const {
    current_time = SDL_GetTicks();
    if (current_time - last_time > time_gap) {
        last_time = current_time;
        return true;
    }
    return false;
}