#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "entity.h"

static SDL_Texture* player_texture;
static SDL_FRect sprite_portion = {18,16,13,16};
static SDL_FRect player_position = {250,250,13,16};

static void quit(){

}
 static void handle_events(SDL_Event* event){

}

static void update(){

}

static void render(SDL_Renderer* renderer){

    SDL_SetTextureScaleMode(player_texture,SDL_SCALEMODE_NEAREST);
    SDL_RenderTexture(renderer,player_texture,&sprite_portion,&player_position);
}

Entity init_player(SDL_Renderer* renderer){

    const char path[] ="./char_spritesheet.png";
    player_texture= IMG_LoadTexture(renderer,path);

    Entity player ={quit,handle_events,update,render};

    return player;
}