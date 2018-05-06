#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <cstdlib>
#include <vector>
#include <stack>
#include <queue>
#include <iterator>

typedef struct Position
{
	std::vector<int> xs;
	std::vector<int> ys;
	std::vector<float> costs;
	std::vector<std::vector<bool>> visited;
	int depth;
	float priority;
} Position;

typedef struct Map
{
	char type[20];
	int height;
	int width;
	char name[20];
	char** matrix;
} Map;

Map *initMap(const char* fileName);
void freeMap(Map*);
bool isFinal(Position p, int xFinal, int yFinal);

#endif
