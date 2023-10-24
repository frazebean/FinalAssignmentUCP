#include <stdio.h>
#include <stdlib.h>
#include "game_outcome.h"
#include "map_struct.h"
#include "constants.h"

int playerWins(Map* map)
{
    int playerWinState = FALSE;

    int playerRow = map->player->rowPos;
    int playerCol = map->player->colPos;
    int goalRow = map->goal->rowPos;
    int goalCol = map->goal->colPos;

    if(playerRow == goalRow && playerCol == goalCol)
    {
        playerWinState = TRUE;
    }

    return playerWinState;
}
int playerLoses(Map* map)
{
    int playerLoseState = FALSE;

    int playerRow = map->player->rowPos;
    int playerCol = map->player->colPos;
    int carRow = map->car->rowPos;
    int carCol = map->car->colPos;

    if(playerRow == carRow && playerCol == carCol)
    {
        playerLoseState = TRUE;
    }

    return playerLoseState;
}
