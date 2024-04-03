// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include <stdlib.h>
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

//Moving the ghost
char moveGhost (int pacman_y, int pacman_x, int ghost_y, int ghost_x){
    char dirns [] = {UP, DOWN, LEFT, RIGHT}; //Array of possible directions
    char* validDirns; //Array for the final valid directions
    char motion = sees_pacman(pacman_y, pacman_x, ghost_y, ghost_x); //If the motion is already decided by seeing packman
    int direction; //Will hold the random direction
    int count = 0; //Number of allowable directions
    if (motion == 0){
        for (int i = 0; i < 4; i++){
            if (validMovement(ghost_y, ghost_x, dirns[i])==0){ //If the direction is valid
                count++;
                //Adding it to the valid directions
                validDirns = realloc(validDirns, count * sizeof(int));
                validDirns[count-1] = dirns[i];
            }
        }
        //Taking a random number between 0 and the max amount of valid directions
        direction = rand() % count;
        return validDirns[direction];
    }
    return motion;
}
