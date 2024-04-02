// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdlib.h>
#include <stdio.h>

#include "defines.h"
#include "colours.h"
#include "map.h"


extern char *map, *dot_map;
extern int width, height;

int cordIdxCvt (int x,int y){

    return (y * 11 + (x - 1));
}

int move_actor(int * y, int * x, char direction, int eat_dots){

    //declearing variables, includes converted x and y cords into an idx and the direction vector and the new cords after movement
    int actorIdx = cordIdxCvt((int) x, (int) y);
    int dirVector;
    int newActorCords;
    int tempX;
    int tempY;

    //converting direction to int values
    switch (direction) {
        case UP:
            dirVector = -11;
            tempY = (int) (y) -1;
            tempX = (int) x;
            break;
        case DOWN:
            dirVector = 11;
            tempX = (int) x;
            tempY = (int) (y) +1;
            break;
        case RIGHT:
            dirVector = 1;
            tempY = (int) y;
            tempX = (int) x +1;
            break;
        case LEFT:
            dirVector = -1;
            tempY = (int) y;
            tempX = (int) x -11;
            break;
        default:
            //  Handle any unexpected direction values
            break;
    }

    //checks if new position is a wall
    if (is_wall(tempX,tempY)){
        return MOVED_WALL;
    }

        //if it is a valid position (contains no walls) then it moves the actor and updates all the corresponding variables.
    else {
        if (eat_dots == 1 && dot_map[actorIdx] == '.') {
            dot_map[actorIdx] = ' ';


        }
        map[actorIdx] = dot_map[actorIdx];
        newActorCords = cordIdxCvt(tempX, tempY);

        if (eat_dots == 1)
            map[newActorCords] = 'P';
        else if (eat_dots == 0)
            map[newActorCords] = 'G';

        y = &tempY;
        x = &tempX;

        return MOVED_OKAY;
    }
}


int is_wall(int y, int x) {

    int index = y * 11 + (x - 1);


    if (map[index] == 'W') {
        return 1;
    } else {
        return 0;
    }
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

int printMap(int *map_height, int *map_width, int getDots){
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


        if (getDots == 1 && map[i] == '.')
            dots++;

    }
    return dots;
}