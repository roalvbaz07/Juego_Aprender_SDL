//Librerias y archivos
#include "player.h"

//Definiciones de SDL
static SDL_Texture* player_texture;
static SDL_FRect sprite_portion = {16,15,16,17};
static SDL_FRect player_position = {250,250,16,17};

// Funcion para salir de las entidades
static void quit(){

}

static void handle_events(SDL_Event *event){

}

static void update(){

}

static void render(SDL_Renderer* renderer){
    // Dibujar el personaje
    SDL_SetTextureScaleMode(player_texture,SDL_SCALEMODE_NEAREST);
    SDL_RenderTexture(renderer,player_texture,&sprite_portion,&player_position);

}

Entity init_player(SDL_Renderer* renderer){
    const char path[] ="./char_spritesheet.png";
    player_texture= IMG_LoadTexture(renderer,path);
    
    Entity player ={
        .quit=quit,
        .handle_events=handle_events,
        .update=update,
        .render=render
    };

    return player;
}