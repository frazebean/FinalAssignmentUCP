#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "game_initialisation.h"
#include "map_struct.h"
#include "game_display.h"
#include "constants.h"
#include "terminal.h"
#include "game_movement.h"
#include "game_outcome.h"
#include "linked_list.h"

int main(int argc, char** argv)
{
    FILE* file = fopen(argv[1], "r");
    
    int fileIOErrors = 0;  /* This variable keeps track the number of errors in file IO. */
    int gameInProgress = TRUE;
    char userInput;

    /* Stores a list of the updated game state. */
    LinkedList* gameStateList = createLinkedList();

    void* removedGameState;

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
    updateGameState(map, gameStateList);  /* Initial game state is stored in linked list. */

    while((gameInProgress) && (fileIOErrors == 0))
    {
        /* Clear the terminal. */
        system("clear");

        displayMap(map);

        /* Automatically accepts user input without needing to press 'Enter'. */
        disableBuffer();
        scanf(" %c", &userInput);
        enableBuffer();

        /* Player and car movement code. */
        /* ------------------------------------------------------------------------------ */
        if(userInput == 'w' || userInput == 's' || userInput == 'a' || userInput == 'd')
        {
            updateMap(map);
            moveCar(map);
        }

        if(userInput == 'w')
        {
            movePlayerUp(map);
            updateGameState(map, gameStateList);  /* Game state is updated by storing in linked list. */
        }
        else if(userInput == 's')
        {
            movePlayerDown(map);
            updateGameState(map, gameStateList);  /* Game state is updated by storing in linked list. */
        }
        else if(userInput == 'a')
        {
            movePlayerLeft(map);
            updateGameState(map, gameStateList);  /* Game state is updated by storing in linked list. */
        }
        else if(userInput == 'd')
        {
            movePlayerRight(map);
            updateGameState(map, gameStateList);  /* Game state is updated by storing in linked list. */
        } 
        else if(userInput == 'u')
        {
            /* Before undoing, we check that the linked list is not size 1 (beginning of the game) */
            if(length(gameStateList) != 1) 
            {
                /* Most recent game state removed is stored in a variable so it can be freed. */
                removedGameState = removeFirst(gameStateList);
                free(removedGameState);

                map->player->rowPos = ((GameState*)gameStateList->head->data)->playerRowPos;
                map->player->colPos = ((GameState*)gameStateList->head->data)->playerColPos;
                map->car->rowPos = ((GameState*)gameStateList->head->data)->carRowPos;
                map->car->colPos = ((GameState*)gameStateList->head->data)->carColPos;
                map->car->symbol = ((GameState*)gameStateList->head->data)->carSymbol;
                map->car->frontRowPos = ((GameState*)gameStateList->head->data)->carFrontRowPos;
                map->car->frontColPos = ((GameState*)gameStateList->head->data)->carFrontColPos;

                revertMap(map);
            }
        }
        /* ------------------------------------------------------------------------------ */

        /* Game outcome code. */
        if(playerWins(map) == TRUE)
        {
            system("clear");
            displayMap(map);

            printf("You win!\n");
            gameInProgress = FALSE;
        }
        else if(playerLoses(map) == TRUE)
        {
            system("clear");
            displayMap(map);

            printf("You lose!\n");
            gameInProgress = FALSE;
        }
    }

    /* Free the linked list. */
    freeLinkedList(gameStateList, &freeGameState);

    /* Free everything else. */
    freeIntMap(map);
    freeCharMap(map);
    free(map->emptySpace);
    free(map->path);
    free(map->car);
    free(map->player);
    free(map->goal);
    free(map);

    return 0;
}