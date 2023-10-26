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

    LinkedList* playerRowPosList = createLinkedList();
    LinkedList* playerColPosList = createLinkedList();
    LinkedList* carRowPosList = createLinkedList();
    LinkedList* carColPosList = createLinkedList();
    LinkedList* carSymbolList = createLinkedList();
    LinkedList* carFrontRowPosList = createLinkedList();
    LinkedList* carFrontColPosList = createLinkedList();

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
    updateCarRowPos(map, carRowPosList);
    updateCarColPos(map, carColPosList);
    updateCarSymbol(map, carSymbolList);
    updateCarFrontRowPos(map, carFrontRowPosList);
    updateCarFrontColPos(map, carFrontColPosList);

    updatePlayerRowPos(map, playerRowPosList);
    updatePlayerColPos(map, playerColPosList);

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

            updateCarRowPos(map, carRowPosList);
            updateCarColPos(map, carColPosList);
            updateCarSymbol(map, carSymbolList);
            updateCarFrontRowPos(map, carFrontRowPosList);
            updateCarFrontColPos(map, carFrontColPosList);
        }

        if(userInput == 'w')
        {
            movePlayerUp(map);

            updatePlayerRowPos(map, playerRowPosList);
            updatePlayerColPos(map, playerColPosList);
        }
        else if(userInput == 's')
        {
            movePlayerDown(map);

            updatePlayerRowPos(map, playerRowPosList);
            updatePlayerColPos(map, playerColPosList);
        }
        else if(userInput == 'a')
        {
            movePlayerLeft(map);

            updatePlayerRowPos(map, playerRowPosList);
            updatePlayerColPos(map, playerColPosList);
        }
        else if(userInput == 'd')
        {
            movePlayerRight(map);

            updatePlayerRowPos(map, playerRowPosList);
            updatePlayerColPos(map, playerColPosList);
        }
        else if(userInput == 'u')
        {
            /* Before undoing, we must check that all linked list length are not 1. (This is
               because players are not allowed to undo at the beginning state of the game.) */
            /* Every time a player undos, the current map is removed, reverting to the previous map. */
            if(length(playerRowPosList) != 1 && length(playerColPosList) != 1 && length(carRowPosList) != 1
            && length(carColPosList) != 1 && length(carSymbolList) != 1 && length(carFrontRowPosList) != 1
            && length(carFrontColPosList) != 1) 
            {
                removeFirst(playerRowPosList);
                map->player->rowPos = *((int*)playerRowPosList->head->data);

                removeFirst(playerColPosList);
                map->player->colPos = *((int*)playerColPosList->head->data);

                removeFirst(carRowPosList);
                map->car->rowPos = *((int*)carRowPosList->head->data);

                removeFirst(carColPosList);
                map->car->colPos = *((int*)carColPosList->head->data);

                removeFirst(carSymbolList);
                map->car->symbol = *((char*)carSymbolList->head->data);

                removeFirst(carFrontRowPosList);
                map->car->frontRowPos = *((int*)carFrontRowPosList->head->data);

                removeFirst(carFrontColPosList);
                map->car->frontColPos = *((int*)carFrontColPosList->head->data);

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

    /* Free the linked lists. */
    freeLinkedList(playerRowPosList, &freeInt);
    freeLinkedList(playerColPosList, &freeInt);
    freeLinkedList(carRowPosList, &freeInt);
    freeLinkedList(carColPosList, &freeInt);
    freeLinkedList(carSymbolList, &freeChar);
    freeLinkedList(carFrontRowPosList, &freeInt);
    freeLinkedList(carFrontColPosList, &freeInt);

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