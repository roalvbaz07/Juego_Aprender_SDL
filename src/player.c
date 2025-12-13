#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "entity.h"

SDL_Texture* player_texture;


SDL_FRect sprite_portion = {18,16,13,16};
SDL_FRect player_position = {250,250,13,16};

void quit(){

}
void handle_events(){

}

void update(){

}

void render(SDL_Renderer* renderer){

    SDL_SetTextureScaleMode(player_texture,SDL_SCALEMODE_NEAREST);
    SDL_RenderTexture(renderer,player_texture,&sprite_portion,&player_position);
}

Entity init_player(SDL_Renderer* renderer){

    const char path[] ="./char_spritesheet.png";
    player_texture= IMG_LoadTexture(renderer,path);

    Entity player ={
        .quit = quit, 
        .handle_events = handle_events,
        .render = render,
        .update = update
    };

    return player;
}