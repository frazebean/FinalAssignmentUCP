#include <stdio.h>
#include <stdlib.h>
#include "map_struct.h"
#include "game_movement.h"
#include "constants.h"
#include "linked_list.h"

/* Updates the map whenever player moves by pressing 'w', 's', 'a' or 'd'. */
void updateMap(Map* map)
{
    int r, c;
    for(r = 0; r < map->mapRow; r++)
    {
        for(c = 0; c < map->mapCol; c++)
        {
            /* The value '0' denotes an empty space: ' ' */
            if(map->intMapArray[r][c] == 0)
            {
                map->charMapArray[r][c] = map->emptySpace->symbol;
            }
            /* The value '1' denotes a path: '.' */
            else if(map->intMapArray[r][c] == 1)
            {
                map->charMapArray[r][c] = map->path->symbol;
            }
            /* The value '2' denotes the car: '>' */
            else if(map->intMapArray[r][c] == 2)
            {
                /* As the car's starting position is always on the path, we set it to be a path
                   first. Then we manually place the car in another location. */
                map->charMapArray[r][c] = map->path->symbol;
            }
            /* The value '3' denotes the player: 'P' */
            else if(map->intMapArray[r][c] == 3)
            {
                /* The player's starting position is always on an empty space. Similar
                   to the previous else-if statement, we update it to be an empty space. */
                map->charMapArray[r][c] = map->emptySpace->symbol;
            }
            /* The value '4' denotes the goal: 'G' */
            else if(map->intMapArray[r][c] == 4)
            {
                map->charMapArray[r][c] = map->goal->symbol;
            }
        }
    }
}
void revertMap(Map* map)
{
    updateMap(map);

    /* Revert the position of the player. */
    map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;

    /* Revert the position of the car. */
    map->charMapArray[map->car->rowPos][map->car->colPos] = map->car->symbol;
}

/* ---------------------------------------------------------------------------------------------- */
void movePlayerUp(Map* map)
{
    /* Player is only allowed to move up if player is not at the top row. */
    if(map->player->rowPos != 0)
    {
        map->player->rowPos = map->player->rowPos - 1;  /* Go one row higher (up) */
        map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;
    }
    else
    {
        /* If row position of player is 0, the player stays in the same location. */
        map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;
    }
}
void movePlayerDown(Map* map)
{
    /* Player is only allowed to move down if player is not at the bottom row. */
    if(map->player->rowPos != (map->mapRow - 1))
    {
        map->player->rowPos = map->player->rowPos + 1;  /* Go one row lower (down) */
        map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;
    }
    else
    {
        /* If row position of player is at the bottom, the player stays in the same location. */
        map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;
    }
}
void movePlayerLeft(Map* map)
{
    /* Player is only allowed to move left if player is not at the leftmost column. */
    if(map->player->colPos != 0)
    {
        map->player->colPos = map->player->colPos - 1;  /* Go one column to the left */
        map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;
    }
    else
    {
        /* If column position of player is leftmost, the player stays in the same location. */
        map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;
    }
}
void movePlayerRight(Map* map)
{
    /* Player is only allowed to move right if player is not at the rightmost column. */
    if(map->player->colPos != (map->mapCol - 1))
    {
        map->player->colPos = map->player->colPos + 1;  /* Go one column to the right */
        map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;
    }
    else
    {
        /* If column position of player is leftmost, the player stays in the same location. */
        map->charMapArray[map->player->rowPos][map->player->colPos] = map->player->symbol;
    }
}
/* ---------------------------------------------------------------------------------------------- */

/* Note, the functions below are different from the 'moveCarUp/Down/Left/Right' functions.
   It is concerned with operations regarding cars pointing in a certain DIRECTION. */
/* ------------------------------------------------------------------------------------------------------- */
void moveCarFacingUp(Map* map)
{
    char frontOfCar = map->charMapArray[map->car->frontRowPos][map->car->frontColPos];
    if(frontOfCar != map->path->symbol)
    {
        if(pathOnRight(map) == TRUE)
        {
            moveCarRight(map);
        }
        else if(pathOnLeft(map) == TRUE)
        {
            moveCarLeft(map);
        }
    }
    /* If the car does not reach a dead end, we continue moving the car up. */
    else
    {
        moveCarUp(map);
    }
}
void moveCarFacingDown(Map* map)
{
    char frontOfCar = map->charMapArray[map->car->frontRowPos][map->car->frontColPos];  
    if(frontOfCar != map->path->symbol)
    {
        if(pathOnRight(map) == TRUE)
        {
            moveCarLeft(map);
        }
        else if(pathOnLeft(map) == TRUE)
        {
            moveCarRight(map);
        }
    }
    else
    {
        moveCarDown(map);
    }
}
void moveCarFacingLeft(Map* map)
{
    char frontOfCar = map->charMapArray[map->car->frontRowPos][map->car->frontColPos];    
    if(frontOfCar != map->path->symbol)
    {
        if(pathOnRight(map) == TRUE)
        {
            moveCarUp(map);
        }
        else if(pathOnLeft(map) == TRUE)
        {
            moveCarDown(map);
        }
    }
    else
    {
        moveCarLeft(map);
    }
}
void moveCarFacingRight(Map* map)
{
    char frontOfCar = map->charMapArray[map->car->frontRowPos][map->car->frontColPos];
    if(frontOfCar != map->path->symbol)
    {
        if(pathOnRight(map) == TRUE)
        {
            moveCarDown(map);
        }
        else if(pathOnLeft(map) == TRUE)
        {
            moveCarUp(map);
        }
    }
    /* If the car does not reach a dead end, we continue moving the car to the right. */
    else
    {
        moveCarRight(map);
    }
}
/* ------------------------------------------------------------------------------------------------------- */

/* NOTE: The functions between the borders below are concerned with MOVING the cars. */
/* --------------------------------------------------------------------------------- */
void moveCarUp(Map* map)
{
    map->car->symbol = '^';

    map->car->rowPos = map->car->rowPos - 1;
    map->charMapArray[map->car->rowPos][map->car->colPos] = map->car->symbol;

    map->car->frontRowPos = map->car->rowPos - 1;
    map->car->frontColPos = map->car->colPos;
}
void moveCarDown(Map* map)
{
    map->car->symbol = 'v';

    map->car->rowPos = map->car->rowPos + 1;
    map->charMapArray[map->car->rowPos][map->car->colPos] = map->car->symbol;

    map->car->frontRowPos = map->car->rowPos + 1;
    map->car->frontColPos = map->car->colPos;
}
void moveCarLeft(Map* map)
{
    map->car->symbol = '<';

    map->car->colPos = map->car->colPos - 1;
    map->charMapArray[map->car->rowPos][map->car->colPos] = map->car->symbol;

    map->car->frontRowPos = map->car->rowPos;
    map->car->frontColPos = map->car->colPos - 1;
}
void moveCarRight(Map* map)
{
    map->car->symbol = '>';

    map->car->colPos = map->car->colPos + 1;
    map->charMapArray[map->car->rowPos][map->car->colPos] = map->car->symbol;

    map->car->frontRowPos = map->car->rowPos;
    map->car->frontColPos = map->car->colPos + 1;
}
/* --------------------------------------------------------------------------------- */

/* A general function that ties in all car moving operations together. */
/* ---------------------------------------- */
void moveCar(Map* map)
{

    if(map->car->symbol == '^')
    {
        moveCarFacingUp(map);
    }
    else if(map->car->symbol == 'v')
    {
        moveCarFacingDown(map);
    }
    else if(map->car->symbol == '<')
    {
        moveCarFacingLeft(map);
    }
    else if(map->car->symbol == '>')
    {
        moveCarFacingRight(map);
    }
}
/* ---------------------------------------- */

/* Functions that return true if there is a path to the right or left of the car. */
/* ----------------------------------------------------------------------------------------------- */
int pathOnRight(Map* map)
{
    int rightPathExists = FALSE;
    if(map->car->symbol == '>')
    {
        if(map->charMapArray[(map->car->rowPos) + 1][map->car->colPos] == map->path->symbol)
        {
            rightPathExists = TRUE;
        }
    }
    else if(map->car->symbol == '^')
    {
        if(map->charMapArray[map->car->rowPos][(map->car->colPos) + 1] == map->path->symbol)
        {
            rightPathExists = TRUE;
        }
    }
    else if(map->car->symbol == '<')
    {
        if(map->charMapArray[(map->car->rowPos) - 1][map->car->colPos] == map->path->symbol)
        {
            rightPathExists = TRUE;
        }
    }
    else if(map->car->symbol == 'v')
    {
        if(map->charMapArray[map->car->rowPos][(map->car->colPos) - 1] == map->path->symbol)
        {
            rightPathExists = TRUE;
        }
    }
    return rightPathExists;
}

/* Function that returns true if there is a path to the left of the car. */
int pathOnLeft(Map* map)
{
    int leftPathExists = FALSE;
    if(map->car->symbol == '>')
    {
        if(map->charMapArray[(map->car->rowPos) - 1][map->car->colPos] == map->path->symbol)
        {
            leftPathExists = TRUE;
        }
    }
    else if(map->car->symbol == '^')
    {
        if(map->charMapArray[map->car->rowPos][(map->car->colPos) -1] == map->path->symbol)
        {
            leftPathExists = TRUE;
        }
    }
    else if(map->car->symbol == '<')
    {
        if(map->charMapArray[(map->car->rowPos) + 1][map->car->colPos] == map->path->symbol)
        {
            leftPathExists = TRUE;
        }
    }
    else if(map->car->symbol == 'v')
    {
        if(map->charMapArray[map->car->rowPos][(map->car->colPos) + 1] == map->path->symbol)
        {
            leftPathExists = TRUE;
        }
    }
    return leftPathExists;
}
/* ----------------------------------------------------------------------------------------------- */

/* This function updates the game state by storing any relevant updated data into the gameStateList
   linked list. */

void updateGameState(Map* map, LinkedList* gameStateList)
{
    GameState* gameState = (GameState*)malloc(sizeof(GameState));

    int* playerRowPos;
    int* playerColPos;
    int* carRowPos;
    int* carColPos;
    char* carSymbol;
    int* carFrontRowPos;
    int* carFrontColPos;

    playerRowPos = (int*)malloc(sizeof(int));
    *playerRowPos = map->player->rowPos;
    gameState->playerRowPos = *playerRowPos;

    playerColPos = (int*)malloc(sizeof(int));
    *playerColPos = map->player->colPos;
    gameState->playerColPos = *playerColPos;

    carRowPos = (int*)malloc(sizeof(int));
    *carRowPos = map->car->rowPos;
    gameState->carRowPos = *carRowPos;

    carColPos = (int*)malloc(sizeof(int));
    *carColPos = map->car->colPos;
    gameState->carColPos = *carColPos;

    carSymbol = (char*)malloc(sizeof(char));
    *carSymbol = map->car->symbol;
    gameState->carSymbol = *carSymbol;

    carFrontRowPos = (int*)malloc(sizeof(int));
    *carFrontRowPos = map->car->frontRowPos;
    gameState->carFrontRowPos = *carFrontRowPos;

    carFrontColPos = (int*)malloc(sizeof(int));
    *carFrontColPos = map->car->frontColPos;
    gameState->carFrontColPos = *carFrontColPos;

    insertFirst((void*)gameState, gameStateList);

    free(playerRowPos);
    free(playerColPos);
    free(carRowPos);
    free(carColPos);
    free(carSymbol);
    free(carFrontRowPos);
    free(carFrontColPos);
}
