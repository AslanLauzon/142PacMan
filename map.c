// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "colours.h"
#include "map.h"


extern char *map, *dot_map;
extern int width, height;

int move_actor(int * y, int * x, char direction, int eat_dots) {
    return MOVED_OKAY;
}

int is_wall(int y, int x) {
    return NOT_WALL;
}

char * load_map(char * filename, int *map_height, int *map_width) {
    int dotIndex = 0; //used for testing
    FILE *fMap = NULL;
    fMap = fopen(filename, "r");
    if (fMap == NULL) { //If the map file is not available
        printf("File not found.\n");

        //closing the file
        fclose(fMap);
        return NULL; //Non-zero return to show error has occurred
    }

    //Creating the holding and map points
    char * pMap = (char*) malloc((*map_width+2)*(*map_height+2)*sizeof(char*));
    char * pHold = (char*) malloc(sizeof(char*));
    if (pMap == NULL || pHold == NULL) { //If there is no memory to allocate them to
        //message to the user
        printf("Memory is not available");
        //Closing the file and free the space
        fclose(fMap);
        free(pMap);
        free(pHold);
        return NULL; //indicating error has occured
    }
    //Creating the top and bottom row of the map
    for (int i = 0; i < *map_width+2; i++){
        pMap[i]='W';
        //index++;
        pMap[(*map_width+1)*(*map_height+2)+i]='W';
        //printf("%c ", pMap[i]); //test
    }
   //printf("\n"); //test
   //printf("%d!\n", index); //Index testing

    //Getting the real map
    for (int i = 1; i < (*map_height+1); i++){
        //Loading the map
        pMap[(i-1)*(*map_height+2)+*map_height+2]= 'W'; //Creating the left most wall
        //printf("%d? ", ((i-1)*(*map_height+2)+*map_height+2)); //Index testing
      //printf("%c ", pMap[i*(*map_height)]); //test
        for (int j = 1; j < *map_width+1; j++){
            fscanf(fMap, "%c", &pHold[0]); // Getting the value from the with a holding value
            if (pHold[0]== '\n'){
                fscanf(fMap, "%c", &pMap[i*(*map_height+2)+j]); //The next value will be valid and can be taken
            }
            else if (pHold[0]==' '){
                fscanf(fMap, "%c", &pHold[0]); //Spaces will be in twos therefor second must be taken
                fscanf(fMap, "%c", &pMap[i*(*map_height+2)+j]); //This will be valid
            }
            else{
                pMap[i*(*map_height+2)+j] = pHold[0]; //If the hold passes the condition, pMap can be made that
            }

           // printf("%d* ", (i*(*map_height+2)+j)); //Index test

           //printf("%c ", pMap[i*(*map_height)+j]); //test
        } //Goes through 9 reps
        pMap[i*(*map_height+2)+*map_width+1]= 'W'; //Adding the right most wall

    }

    return pMap;
}
char * load_dotMap(int *map_height, int *map_width){
    char * pMap = (char*) malloc((*map_width+2)*(*map_height+2)*sizeof(char*));
    if (pMap == NULL) { //If there is no memory to allocate them to
        //message to the user
        printf("Memory is not available");
        //Closing the file and free the space
        free(pMap);
        return NULL; //indicating error has occured
    }
    for (int i = 0; i < (height+2)*(width+2);i++){
        if (map[i] == 'P' || map[i] == 'G')
            pMap[i] = ' ';
        else
            pMap[i]=map[i];
    }
    return pMap;
}