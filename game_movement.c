#include <stdio.h>
#include <stdlib.h>
#include "map_struct.h"
#include "game_movement.h"

void updateMap(Map* map)
{
    int r, c;
    for(r = 0; r < map->mapRow; r++)
    {
        for(c = 0; c < map->mapColumn; c++)
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
