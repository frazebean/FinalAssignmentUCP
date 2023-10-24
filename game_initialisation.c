#include <stdio.h>
#include <stdlib.h>
#include "game_initialisation.h"
#include "map_struct.h"

/* This function is only used in the beginning for storing the integer values read from the file. */
void mallocIntMap(Map* map)
{
    int r;

    /* Mallocs rows first for the 2D array. */
    map->intMapArray = (int**)malloc(sizeof(int*) * map->mapRow);
    for(r = 0; r < map->mapRow; r++)
    {
        /* Mallocs columns in each row of the 2D array. */
        map->intMapArray[r] = (int*)malloc(sizeof(int) * map->mapColumn);
    }
}

void readRemainingData(FILE* file, Map* map)
{
    int r, c;
    for(r = 0; r < map->mapRow; r++)
    {
        for(c = 0; c < map->mapColumn; c++)
        {
            /* Stores every integer from the file into the 2D array. */
            if(fscanf(file, "%d", &map->intMapArray[r][c]) != 1)
            {
                perror("Error reading data");
            }
        }
    }
}

/* This function is used to malloc the actual map, which stores characters instead of integers. */
void mallocCharMap(Map* map)
{
    int r;

    /* Mallocs rows first for the 2D array. */
    map->charMapArray = (char**)malloc(sizeof(char*) * map->mapRow);
    for(r = 0; r < map->mapRow; r++)
    {
        /* Mallocs columns in each row of the 2D array. */
        map->charMapArray[r] = (char*)malloc(sizeof(char) * map->mapColumn);
    }
}

/* Initialise the actual map with characters. */
void initialiseMap(Map* map)
{
    int r, c;
    for(r = 0; r < map->mapRow; r++)
    {
        for(c = 0; c < map->mapColumn; c++)
        {
            /* The value '0' denotes an empty space: ' ' */
            if(map->intMapArray[r][c] == 0)
            {
                map->emptySpace->symbol = ' ';
                map->charMapArray[r][c] = map->emptySpace->symbol;
            }
            /* The value '1' denotes a path: '.' */
            else if(map->intMapArray[r][c] == 1)
            {
                map->path->symbol = '.';
                map->charMapArray[r][c] = map->path->symbol;
            }
            /* The value '2' denotes the car: '>' */
            else if(map->intMapArray[r][c] == 2)
            {
                map->car->symbol = '>';
                map->charMapArray[r][c] = map->car->symbol;
            }
            /* The value '3' denotes the player: 'P' */
            else if(map->intMapArray[r][c] == 3)
            {
                map->player->symbol = 'P';
                map->charMapArray[r][c] = map->player->symbol;
                map->player->rowPos = r;
                map->player->colPos = c;
            }
            /* The value '4' denotes the goal: 'G' */
            else if(map->intMapArray[r][c] == 4)
            {
                map->goal->symbol = 'G';
                map->charMapArray[r][c] = map->goal->symbol;
            }
        }
    }
}