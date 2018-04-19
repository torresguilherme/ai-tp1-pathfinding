#include "ids.h"

Position IDS(Map* map, int xInicial, int yInicial, int xFinal, int yFinal)
{
	Position ret;

	//initial values
	float cost = 0;
	int curX = xInicial;
	int curY = yInicial;

	ret.xs.push_back(xInicial);
	ret.ys.push_back(yInicial);
	ret.costs.push_back(cost);

	return ret;
}
