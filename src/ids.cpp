#include "ids.h"

Position IDS(Map* map, int xInicial, int yInicial, int xFinal, int yFinal)
{
	Position aux;

	//initial values
	float cost = 0;
	int curX = xInicial;
	int curY = yInicial;

	aux.xs.push_back(xInicial);
	aux.ys.push_back(yInicial);
	aux.costs.push_back(cost);

	if(isFinal(aux, xFinal, yFinal))
	{
		return aux;
	}

	for(int i = 0; i < map->height * map->width; i++)
	{
		Position ret = depthFirst(map, aux, i);
		if(isFinal(ret, xFinal, yFinal))
		{
			return ret;
		}
	}
}

Position depthFirst(Map *map, Position aux, int depth)
{
}
