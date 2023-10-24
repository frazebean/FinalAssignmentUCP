#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game_initialisation.h"
#include "map_struct.h"
#include "game_display.h"
#include "constants.h"
#include "terminal.h"
#include "game_movement.h"

int main(int argc, char** argv)
{
    FILE* file = fopen(argv[1], "r");
    
    int fileIOErrors = 0;  /* This variable keeps track the number of errors in file IO. */
    int gameInProgress = TRUE;
    char userInput;

    /* Declare the 'Map' struct. This stores a map 'object' in a sense. */
    Map* map = (Map*)malloc(sizeof(Map));
    map->emptySpace = (EmptySpace*)malloc(sizeof(EmptySpace));
    map->path = (Path*)malloc(sizeof(Path));
    map->car = (Car*)malloc(sizeof(Car));
    map->player = (Player*)malloc(sizeof(Player));
    map->goal = (Goal*)malloc(sizeof(Goal));

    /* NOTE: The code within the borders below are all responsible for file IO. */
    /* ---------------------------------------------------------------------------------------------- */
    /* First check if the number of command line arguments is correct. */
    if(argc != 2)
    {
        printf("Usage: ./traffic <map_file_name>\n");
        fileIOErrors++;
    }
    /* If two command line arguments are supplied, we then check if we can read from the file. */
    else
    {
        /* Give error if there is no source file to read from. */
        if(file == NULL)
        {
            perror("Error opening source file");
            fileIOErrors++;
        }
        else
        {
            /* We read the first two integers, which denotes the map row and column. */
            if(fscanf(file, "%d %d", &map->mapRow, &map->mapCol) != 2)
            {
                perror("Error reading data");
                fileIOErrors++;
            }
            else
            {
                /* Malloc a 2D map array WITH INTEGERS read from the file. */
                mallocIntMap(map);

                /* Read remaining data in the file. */
                readRemainingData(file, map);

                /* Malloc the actual map: Integers converted to characters. */
                mallocCharMap(map);

                /* Initialise the map with correct characters. */
                initialiseMap(map);
            }

            /* This error checking goes at the very bottom. */
            if(ferror(file))
            {
                perror("Error reading from source file\n");
                fileIOErrors++;
            }
            fclose(file);
        }
    }
    /* ---------------------------------------------------------------------------------------------- */

    /* NOTE: The code within the borders below are responsible for the main game. */
    /* ---------------------------------------------------------------------------------------------- */
    /* The game only starts when the number of errors in the file reading is zero. */
    while((gameInProgress) && (fileIOErrors == 0))
    {
        /* Clear the terminal. */
        system("clear");

        displayMap(map);

        /* Automatically accepts user input without needing to press 'Enter'. */
        disableBuffer();
        scanf(" %c", &userInput);
        enableBuffer();

        if(userInput == 'w' || userInput == 's' || userInput == 'a' || userInput == 'd')
        {
            updateMap(map);
            moveCar(map);
        }

        if(userInput == 'w')
        {
            movePlayerUp(map);
        }
        if(userInput == 's')
        {
            movePlayerDown(map);
        }
        if(userInput == 'a')
        {
            movePlayerLeft(map);
        }
        if(userInput == 'd')
        {
            movePlayerRight(map);
        }
    }

    return 0;
}