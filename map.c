// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "colours.h"
#include "map.h"


extern char *map, *dot_map;
extern int width, height, dotCount;

int validMovement (int x, int y, char direction){
    switch (direction){ //Changing the coordinate depending on the type of movement require3d
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
    }
    if (x >= 0 && x < 9 && y < 9 && y >= 0) //motion is valid
        return 0;
    return 1; // The motion is invalid
}

int cordIdxCvt (int x,int y){

    return (y * 9 + (x));
}

int move_actor(int *y, int *x, char direction, int eat_dots){

    //declaring variables, includes converted x and y cords into an idx and the direction vector and the new cords after movement
    int actorIdx = cordIdxCvt(*x, *y);
    printf("\nORIGINAL IDX:%d", actorIdx);
    int newActorCords;
    int tempX;
    int tempY;

    //converting direction to int values
    switch(direction) {
        case UP:
            // Move up means decrement the Y value
            tempY = *y - 1;
            tempX = *x;
            break;
        case DOWN:
            // Move down means increment the Y value
            tempY = *y + 1;
            tempX = *x;
            break;
        case RIGHT:
            // Move right means increment the X value
            tempX = *x + 1;
            tempY = *y;
            break;
        case LEFT:
            // Move left means decrement the X value
            tempX = *x - 1;
            tempY = *y;
            break;
        default:
            //  Handle any unexpected direction values
            return MOVED_INVALID_DIRECTION;
    }


    if (eat_dots == 0) {
        printf("\nTEMP VALUES %d %d\nWALL VALUE:%d\n", tempX, tempY,is_wall(tempX,tempY));

    }
    fflush(stdout);
    //checks if new position is a wall
    if (is_wall(tempX,tempY)){
        return MOVED_WALL;
    }

        //if it is a valid position (contains no walls) then it moves the actor and updates all the corresponding variables.

    if (eat_dots == 1 && dot_map[actorIdx] == '.') {
        dot_map[actorIdx] = ' ';
        dotCount--;

    }
    map[actorIdx] = dot_map[actorIdx];
    printf("\nNEW CORDS (%d, %d) IDX: %d", tempX, tempY,cordIdxCvt(tempX, tempY));
    newActorCords = cordIdxCvt(tempX, tempY);

    if (eat_dots == 1)
        map[newActorCords] = 'P';
    else if (eat_dots == 0)
        map[newActorCords] = 'G';

    *y = tempY;
    *x = tempX;

    return MOVED_OKAY;

}


int is_wall(int x, int y) {

    int validMove;
    int idx = cordIdxCvt(x,y);
    if (x >= 0 && x < 9 && y < 9 && y >= 0)
        validMove = 1;
    else
        validMove = 0;

    if (map[cordIdxCvt(x,y)] == 'W'|| validMove == 0) {
        return 1;


    } else
        return 0;

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
    char * pMap = (char*) malloc((*map_width)*(*map_height)*sizeof(char*));
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
//    for (int i = 0; i < *map_width+2; i++){
//        pMap[i]='W';
//        //index++;
//        pMap[(*map_width+1)*(*map_height+2)+i]='W';
//        //printf("%c ", pMap[i]); //test
//    }
   //printf("\n"); //test
   //printf("%d!\n", index); //Index testing

    //Getting the real map
    for (int i = 0; i < (*map_height); i++){
        //Loading the map
//        pMap[(i-1)*(*map_height+2)+*map_height+2]= 'W'; //Creating the left most wall
        //printf("%d? ", ((i-1)*(*map_height+2)+*map_height+2)); //Index testing
      //printf("%c ", pMap[i*(*map_height)]); //test
        for (int j = 0; j < *map_width; j++){
            fscanf(fMap, "%c", &pHold[0]); // Getting the value from the with a holding value
            if (pHold[0]== '\n'){
                fscanf(fMap, "%c", &pMap[i*(*map_height)+j]); //The next value will be valid and can be taken
            }
            else if (pHold[0]==' '){
                fscanf(fMap, "%c", &pHold[0]); //Spaces will be in twos therefor second must be taken
                fscanf(fMap, "%c", &pMap[i*(*map_height)+j]); //This will be valid
            }
            else{
                pMap[i*(*map_height)+j] = pHold[0]; //If the hold passes the condition, pMap can be made that
            }

           // printf("%d* ", (i*(*map_height+2)+j)); //Index test

           //printf("%c ", pMap[i*(*map_height)+j]); //test
        } //Goes through 9 reps
//        pMap[i*(*map_height+2)+*map_width+1]= 'W'; //Adding the right most wall

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
    for (int i = 0; i < (height)*(width);i++){
        if (map[i] == 'P' || map[i] == 'G')
            pMap[i] = ' ';
        else
            pMap[i]=map[i];
    }
    return pMap;
}


void printMap(int *map_height, int *map_width){
    int dots = 0;
    int level = -1;
    for (int i = 0; i < (*map_height+2)*(*map_width+2); i++){
        if (i < *map_width+1 || (*map_width+2)*(*map_height+1)< i)
            printf("W ");
        else if ((i+1)%11==0){
            printf("W\n");
            level++;
        }
        else if (i % (*map_width+2)==0)
            printf("W ");
        else{
            printf("%c ", map[i-(width+3)-2*level]);
        }
    }
}

int initalDotCount (int *map_height, int *map_width){
    int count = 0;

    for (int x = 0; x < *map_height**map_width; x++)

        if (dot_map[x] == '.'){
            count++;
        }
    //printf("COUINT %d", count);
    return  count;
}