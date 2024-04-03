// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "ghost.h"
#include "map.h"

char sees_pacman(int pacman_y, int pacman_x, int ghost_y, int ghost_x) {
    int diff = 0;
    if (pacman_y == ghost_y){ //If it is on the same y level
        diff = pacman_x - ghost_x; //Determining the distance between the two if it's left or right
        if (diff > 0){ //If the ghost is to the right of pacman
            for (int i = diff; i > 0; i++){
               if(is_wall(pacman_y, ghost_x+diff)==1){ //Checking if there's a wall in between them
                   return SEES_NOTHING;
               }
            }
            return LEFT; // Direction of travel for the ghost
        }
        else{
            for (int i = 0; i > diff; i++){
                if(is_wall(pacman_y, ghost_x+diff)==1){ //Checking if there's a wall in between them
                    return SEES_NOTHING;
                }
            }
            return RIGHT; // Direction of travel for the ghost
        }
    }
    else if (pacman_x == ghost_y){
        diff = pacman_x - ghost_x; //Determining the distance between the two is up or down
        if (diff > 0){ //If the ghost is to the below pacman
            for (int i = diff; i > 0; i++){
                if(is_wall(pacman_y+diff, ghost_x)==1){ //Checking if there's a wall in between them
                    return SEES_NOTHING;
                }
            }
            return DOWN; // Direction of travel for the ghost
        }
        else{
            for (int i = 0; i > diff; i++){ //Ghost is below
                if(is_wall(pacman_y+diff, ghost_x)==1){ //Checking if there's a wall in between them
                    return SEES_NOTHING;
                }
            }
            return UP; // Direction of travel for the ghost
        }
    }

    return SEES_NOTHING;
}
