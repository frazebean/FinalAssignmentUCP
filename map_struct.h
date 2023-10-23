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
    int xPos;  /* The x-axis (horizontal) position of the player. */
    int yPos;  /* The y-axis (vertical) position of the player. */

} Player;

typedef struct Car
{
    char symbol;
    int xPos;  /* The x-axis (horizontal) position of the car. */
    int yPos;  /* The y-axis (vertical) position of the car. */

} Car;

typedef struct Goal
{
    char symbol;
    int xPos;  /* The x-axis (horizontal) position of the goal. */
    int yPos;  /* The y-axis (vertical) position of the goal. */
    
} Goal;

typedef struct Map
{
    int** intMapArray;
    char** charMapArray;
    int mapRow;
    int mapColumn;

    /* These are the characters in the map. */
    EmptySpace emptySpace;
    Path path;
    Car car;
    Player player;
    Goal goal;

} Map;

#endif