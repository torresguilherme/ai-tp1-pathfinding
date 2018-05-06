#ifndef IDS_H_
#define IDS_H_
#include "common.h"

Position IDS(Map* map, int xInicial, int yInicial, int xFinal, int yFinal);
Position depthFirst(Map*, Position, int);

#endif
