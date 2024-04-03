// APSC 142 Pacman code
// Created by John Calder 20392298 and Aslan Lauzon ####

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "ghost.h"



// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map = NULL, *dot_map = NULL;
// width and height store the width and height of map, NOT counting outer walls
int width = 9, height = 9, dotCount;




/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PACMAN when no pacman is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    int *pHeight =  &width;
    int *pWidth = &height;
    char input;
    int dots;
    int result;

    //tracking variables
    int  pacman_x, pacman_y;
    pacman_x = 4;
    pacman_y = 4;
    char direction;

    int pacman[2] = {4,4};

    int ghosts_y[NUM_GHOSTS] = {0,8};
    int ghosts_x[NUM_GHOSTS] = {0,8};



    map = load_map("map.txt", pHeight, pWidth);
    dot_map = load_dotMap(pHeight, pWidth);
    dotCount = initalDotCount(pHeight, pWidth);

    if (map == NULL) //If the map is not findable
        return ERR_NO_MAP;
    setbuf(stdout, NULL);
    //Creating the dot map


    //change to loss condition


    do{
        if (check_win(pacman_y,pacman_x,ghosts_y,ghosts_x)){
            break;
        }
        printMap(pHeight, pWidth);
        input = getch();
        printf("\nPACMAN CORDS: (%d,%d)", pacman_x,pacman_y);


        int mveactrresult = move_actor(&pacman_y,&pacman_x,input,1);
//        printf("\nWall Result: %d", mveactrresult);
//        printf("\nGLOBAL PACMAN CORDS: (%d,%d)", pacman_x,pacman_y);
//        printf("LOSS CONDITION RETURNS:%d", check_loss(pacman_y,pacman_x,ghosts_y,ghosts_x));
        printf("\nGHOST LOCATION\nGHOST ONE (%d,%d) GHOST TWO (%d,%d)", ghosts_y[0], ghosts_x[1],ghosts_x[1], ghosts_y[1]);
        printf("\nDOTCOUNT: %d", dotCount);



        direction = moveGhost(pacman_y,pacman_x,ghosts_y[1], ghosts_x[1]);
        printf("\ndirection: %c", direction);
        result = move_actor(&ghosts_y[1], &ghosts_x[1], direction, 0);

        direction = moveGhost(pacman_y,pacman_x,ghosts_y[0], ghosts_x[0]);
        printf("\ndirection: %c", direction);
        result = move_actor(&ghosts_y[0], &ghosts_x[0], direction, 0);

        printf("MOVE ACTOR RESULT: %d", result);
        printf("\n\n\n\n");


        //check win condition





    }while (!check_loss(pacman_y,pacman_x,ghosts_y,ghosts_x));

    return NO_ERROR;
}
