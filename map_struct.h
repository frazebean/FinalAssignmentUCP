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
    int mapColumn;

    /* These are the characters in the map. */
    EmptySpace* emptySpace;
    Path* path;
    Car* car;
    Player* player;
    Goal* goal;

} Map;

#endif