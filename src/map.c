#define CUTE_TILED_IMPLEMENTATION  
#include "map.h"

static cute_tiled_map_t* map;
static cute_tiled_layer_t* layer;
static cute_tiled_tileset_t* tileset;
static Texture* texture;

static void render(SDL_Renderer* renderer){

    cute_tiled_layer_t* temp_layer = layer;

    while(temp_layer){
        //Pasar a la siguiente si no hay data
        if(!temp_layer->data){
            temp_layer = temp_layer -> next;
        }
        //Eje Y
        for(int i = 0; i < map->height; i++){
            
            //Eje X
            for(int j = 0; i < map -> width; j++){
                
                int tile_id = temp_layer -> data[i*map ->width + j];
                
                if(tile_id == 0) continue;

                Texture* temp_texture = texture;
                Texture* texture_to_use = NULL;

                while(temp_texture){
                    if(tile_id >= temp_texture -> firstgid && tile_id <= temp_texture -> firstgid + temp_texture -> tilecount -1 ){
                        texture_to_use = temp_texture;
                        break;
                    }

                    temp_texture = temp_texture -> next; 
                }

                if(!texture_to_use) continue;

                int tileset_collums = texture_to_use -> tileset_width / map -> tilewidth;

                SDL_FRect src= {
                    (tile_id - texture_to_use -> firstgid) % tileset_collums * map -> tilewidth,
                    (tile_id - texture_to_use -> firstgid) % tileset_collums * map -> tileheight,
                    map ->tilewidth,
                    map ->tileheight
                };

                SDL_FRect dest = {
                    j * map-> tilewidth,
                    i * map -> tileheight,
                    map -> tilewidth,
                    map -> tileheight
                };
                
                SDL_RenderTexture(renderer,texture_to_use -> texture,&src,&dest);
                
            }
        }

        temp_layer = temp_layer -> next;
    }
}

Entity init_map(SDL_Renderer* renderer){
    const char map_path[]="./tiled/map.json";
    map = cute_tiled_load_map_from_file(map_path,NULL);

    // Logear error en caso del mismo
    if(!map){
        SDL_Log("Error cargando el mapa");
    }
    
    // Asignar datos de mapa
    layer = map ->layers;
    tileset = map-> tilesets;

    texture = SDL_malloc(sizeof(Texture));

    Texture* current_texture = texture;

    while(tileset){
        current_texture -> texture = IMG_LoadTexture(renderer, tileset ->  image.ptr);

        if(!current_texture -> texture){
            SDL_Log("Error cargando la textura para el tileset");
        }
        else{
            SDL_Log("Textura cargada correctamente");
        }

        current_texture -> firstgid = tileset -> firstgid;
        current_texture -> tilecount = tileset -> tilecount;
        current_texture -> tileset_width = tileset -> imagewidth;
        current_texture -> tileset_height= tileset -> imageheight;

        tileset = tileset -> next;

        if(tileset){
            current_texture->next = SDL_malloc(sizeof(Texture));
            current_texture = current_texture -> next;
        } else{
            current_texture -> next = NULL;
        }
    }
    
    Entity map_e = {
        .render = render
    };

    return map_e;

}