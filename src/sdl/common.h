#pragma once

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "../entity.h"

typedef struct AppState{
    SDL_Window* window;
    SDL_Renderer* renderer;
    float last_tick;
    float current_tick;
    float delta_time;
} AppState;