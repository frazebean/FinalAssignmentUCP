#include <stdio.h>
#include <stdlib.h>
#include "game_initialisation.h"
#include "map_struct.h"

/* This function is only used in the beginning for storing the integer values read from the file. */
int** mallocIntMap(Map map)
{
    int r;

    /* Mallocs rows first for the 2D array. */
    map.intMapArray = (int**)malloc(sizeof(int*) * map.mapRow);
    for(r = 0; r < map.mapRow; r++)
    {
        /* Mallocs columns in each row of the 2D array. */
        map.intMapArray[r] = (int*)malloc(sizeof(int) * map.mapColumn);
    }

    return map.intMapArray;
}

void readRemainingData(FILE* file, Map map)
{
    int r, c;
    for(r = 0; r < map.mapRow; r++)
    {
        for(c = 0; c < map.mapColumn; c++)
        {
            /* Stores every integer from the file into the 2D array. */
            if(fscanf(file, "%d", &map.intMapArray[r][c]) != 1)
            {
                perror("Error reading data");
            }
        }
    }
}

/* This function is used to malloc the actual map, which stores characters instead of integers. */
char** mallocCharMap(Map map)
{
    int r;

    /* Mallocs rows first for the 2D array. */
    map.charMapArray = (char**)malloc(sizeof(char*) * map.mapRow);
    for(r = 0; r < map.mapRow; r++)
    {
        /* Mallocs columns in each row of the 2D array. */
        map.charMapArray[r] = (char*)malloc(sizeof(char) * map.mapColumn);
    }

    return map.charMapArray;
}

/* Initialise the actual map with characters. */
void initialiseMap(Map map)
{
    int r, c;
    for(r = 0; r < map.mapRow; r++)
    {
        for(c = 0; c < map.mapColumn; c++)
        {
            /* The value '0' is an empty space: ' ' */
            if(map.intMapArray[r][c] == 0)
            {
                map.charMapArray[r][c] = ' ';
            }
            else if(map.intMapArray[r][c] == 1)
            {
                map.charMapArray[r][c] = '.';
            }
            else if(map.intMapArray[r][c] == 2)
            {
                map.charMapArray[r][c] = '>';
            }
            else if(map.intMapArray[r][c] == 3)
            {
                map.charMapArray[r][c] = 'P';
            }
            else if(map.intMapArray[r][c] == 4)
            {
                map.charMapArray[r][c] = 'G';
            }
        }
    }
}