#ifndef MAP_STRUCT_H
#define MAP_STRUCT_H

typedef struct EmptySpace
{
    char symbol;

} EmptySpace;

typedef struct Path
{
    char symbol;

} Path;

typedef struct Player
{
    char symbol;
    int rowPos;
    int colPos;

} Player;

typedef struct Car
{
    char symbol;
    int rowPos;
    int colPos;
    
    /* The two variables below denote the row and column position in front of the car.
       Example, if car is facing East '>' and its position is rowPos = 0, colPos = 0, then
       frontRowPos = 0 and frontColPos = 1. */
    int frontRowPos;
    int frontColPos;

} Car;

typedef struct Goal
{
    char symbol;
    
} Goal;

typedef struct Map
{
    int** intMapArray;
    char** charMapArray;
    int mapRow;
    int mapCol;

    /* These are the characters in the map. */
    EmptySpace* emptySpace;
    Path* path;
    Car* car;
    Player* player;
    Goal* goal;

} Map;

#endif