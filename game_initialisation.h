#include "map_struct.h"

#ifndef GAME_INITIALISATION_H
#define GAME_INITIALISATION_H

int** mallocIntMap(Map map);
void readRemainingData(FILE* file, Map map);
char** mallocCharMap(Map map);
void initialiseMap(Map map);

#endif