#include "entity.h"

Entity entities[MAX_ENTITIES];
int entities_count = 0;

void create_entity(Entity entity){

    if(entities_count < MAX_ENTITIES){
        entities[entities_count] = entity;
        entities_count++;
    }
    else{
        SDL_Log("Has llegado al limite de entidades\n");
    }
}

void delete_entity(int entityIndex){

    if(entityIndex < 0 || entityIndex >=MAX_ENTITIES){
        SDL_Log("El index proporionado no es valido: %d\n",entityIndex);
        return;
    }

    entities[entityIndex].cleanup();

    for(int i = entityIndex; i < MAX_ENTITIES-1; i++){
        entities[i]= entities[i+1];
    }

    entities_count --;
}

void swap_entities(int index1, int index2){
   
    if(index1 < 0 || index1 >=MAX_ENTITIES|| index2 < 0 || index2 >=MAX_ENTITIES){
        SDL_Log("Los index porporcionados no son validos:: %d y %d\n",index1,index2);
        return;
    } 

    Entity tmp = entities[index1];
    entities[index1] = entities[index2];
    entities[index2] = tmp;


}