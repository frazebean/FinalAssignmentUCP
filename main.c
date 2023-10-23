#include <stdio.h>
#include <stdlib.h>
#include "game_initialisation.h"
#include "map_struct.h"
#include "game_display.h"

int main(int argc, char** argv)
{
    FILE* file = fopen(argv[1], "r");
    int numberRead;

    /* Declare the 'Map' struct. This stores a map 'object' in a sense. */
    Map map;

    /* NOTE: The code within the borders below are all responsible for file IO. */
    /* ---------------------------------------------------------------------------------------------- */
    /* First check if the number of command line arguments is correct. */
    if(argc != 2)
    {
        printf("Usage: ./traffic <map_file_name>\n");
    }
    /* If two command line arguments are supplied, we then check if we can read from the file. */
    else
    {
        /* Give error if there is no source file to read from. */
        if(file == NULL)
        {
            perror("Error opening source file");
        }
        else
        {
            /* We read the first two integers, which denotes the map row and column. */
            numberRead = fscanf(file, "%d %d", &map.mapRow, &map.mapColumn);
            if(numberRead != 2)
            {
                perror("Error reading data");
            }
            else
            {
                /* Malloc a 2D map array WITH INTEGERS read from the file. */
                map.intMapArray = mallocIntMap(map);

                /* Read remaining data in the file. */
                readRemainingData(file, map);

                /* Malloc the actual map: Integers converted to characters. */
                map.charMapArray = mallocCharMap(map);

                /* Initialise the map with correct characters. */
                initialiseMap(map);
            }

            /* Prints the map */
            displayMap(map);

            /* This error checking goes at the very bottom. */
            if(ferror(file))
            {
                perror("Error reading from source file\n");
            }
        }
    }
    fclose(file);
    /* ---------------------------------------------------------------------------------------------- */

    return 0;
}