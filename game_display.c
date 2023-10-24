#include <stdio.h>
#include <stdlib.h>
#include "game_display.h"
#include "map_struct.h"

void displayMap(Map* map)
{
    int r, c;

    displayTopBottomBorders(map);  /* Displays top border. */
    for(r = 0; r < map->mapRow; r++)
    {
        printf("*");  /* Displays the left border. */
        for(c = 0; c < map->mapColumn; c++)
        {
            printf("%c", map->charMapArray[r][c]);
        }
        printf("*");  /* Displays the right border. */

        printf("\n");
    }
    displayTopBottomBorders(map);  /* Displays bottom border. */

    displayControls();
}

void displayTopBottomBorders(Map* map)
{
    int c;
    for(c = 0; c < (map->mapColumn+2); c++)
    {
        printf("*");
    }
    printf("\n");
}

void displayControls()
{
    printf("Press w to move up\n");
    printf("Press s to move down\n");
    printf("Press a to move left\n");
    printf("Press d to move right\n");
    printf("Press u to undo\n");
}