#ifndef BESTFIRST_H_
#define BESTFIRST_H_
#include "common.h"

Position bestFirst(Map*, const char*, int, int, int, int, int);
float hValue(Position, int, int, const char*);

#endif
