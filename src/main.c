//Incluir librerias y archivos
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_main.h>
#include "entity.h"
#include "player.h"

//Zona de definiciones
#define renderEntities(entites,entities_count,renderer)\
    for(int i=0;i<entities_count;i++){\
        entities[i].render(renderer);\
    }

#define updateEntities(entites,entities_count)\
    for(int i=0;i<entities_count;i++){\
        entities[i].update();\
    }

#define quitEntities(entites,entities_count)\
    for(int i=0;i<entities_count;i++){\
        entities[i].quit();\
    }

#define handleEventsEntities(entites,entities_count,event) \
    for(int i=0;i<entities_count;i++){\
        entities[i].handle_events(event);\
    }


//declarar cosas del SDL
SDL_Window* window;
SDL_Renderer* renderer;
Entity entities[MAX_ENTITIES];
int entities_count=0; 

//Funcion para salir del SDl
void SDL_AppQuit(void *appstate, SDL_AppResult result){
    quitEntities(entities,entities_count);
    SDL_DestroyRenderer(renderer);
    renderer=NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

//Funcion para acciones dentro del SDL
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event){
    if(event -> type == SDL_EVENT_QUIT){
        return SDL_APP_SUCCESS;
    }
    return SDL_APP_CONTINUE;
}

//Funcion para actualizar
void update(){
    updateEntities(entities,entities_count);
}

//Funcion para renderizar
void render(){

    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    //Renderizar el personaje

    renderEntities(entitiesn,entities_count,renderer);

    SDL_RenderPresent(renderer);

}

//Funcion par interar 
SDL_AppResult SDL_AppIterate(void *appstate){
    update();
    render();
    return SDL_APP_CONTINUE;
}

//Funcion que se activa al inicio del programa
SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv){
    if(!SDL_Init(SDL_INIT_VIDEO)){
        SDL_Log("Error initializing SDL: %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

    window = SDL_CreateWindow(
        "SLD3 Game",
        800,
        600,
        0
    );

    if(!window){
        SDL_Log("Error creating window: %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

    renderer = SDL_CreateRenderer(window,NULL);

    if(!renderer){
        SDL_Log("Error creating renderer: %s",SDL_GetError());
        return SDL_APP_FAILURE;
    }

    //Iniciar personajes

    entities[entities_count++]=init_player(renderer);

    return SDL_APP_CONTINUE;

}

