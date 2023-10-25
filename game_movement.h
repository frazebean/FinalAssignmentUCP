#include "map_struct.h"
#include "linked_list.h"

#ifndef GAME_MOVEMENT_H
#define GAME_MOVEMENT_H

void updateMap(Map* map);
void revertMap(Map* map);

void movePlayerUp(Map* map);
void movePlayerDown(Map* map);
void movePlayerLeft(Map* map);
void movePlayerRight(Map* map);

void moveCarFacingUp(Map* map);
void moveCarFacingDown(Map* map);
void moveCarFacingLeft(Map* map);
void moveCarFacingRight(Map* map);

void moveCarUp(Map* map);
void moveCarDown(Map* map);
void moveCarLeft(Map* map);
void moveCarRight(Map* map);

void moveCar(Map* map);

int pathOnRight(Map* map);
int pathOnLeft(Map* map);

void updatePlayerRowPos(Map* map, LinkedList* playerRowPosList);
void updatePlayerColPos(Map* map, LinkedList* playerColPosList);
void updateCarRowPos(Map* map, LinkedList* carRowPosList);
void updateCarColPos(Map* map, LinkedList* carColPosList);
void updateCarSymbol(Map* map, LinkedList* carSymbolList);

#endif