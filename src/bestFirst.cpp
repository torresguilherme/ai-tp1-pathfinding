#include "bestFirst.h"
#include <cmath>
#include <cstring>
#include <vector>
#define max(X, Y) X > Y ? X : Y
#define min(X, Y) X > Y ? Y : X
using namespace std;

// valor computado para f(x) = (2-w)g(x) + wh(x)
Position bestFirst(Map* map, const char *heuristic, int w, int xInicial, int yInicial, int xFinal, int yFinal)
{
	Position aux;
	aux.xs.push_back(xInicial);
	aux.ys.push_back(yInicial);
	aux.costs.push_back(0);
	aux.priority = w * hValue(aux, xFinal, yFinal, heuristic);

	for(int i = 0; i < map->height; i++)
	{
		vector<bool> v;
		aux.visited.push_back(v);
		for(int j = 0; j < map->width; j++)
		{
			aux.visited[i].push_back(false);
		}
	}

	aux.visited[xInicial][yInicial] = true;

	if(isFinal(aux, xFinal, yFinal))
	{
		return aux;
	}

	queue<Position> front;
	front.push(aux);

	while(!front.empty())
	{

	}

	// algoritmo falhou em encontrar a soluçao
	Position failure = aux;
	failure.xs.push_back(xFinal);
	failure.ys.push_back(yFinal);
	failure.costs.push_back(-1);
	return failure;
}

float hValue(Position p, int xFinal, int yFinal, const char *tipo)
{
	float dx = abs(p.xs.back() - xFinal);
	float dy = abs(p.ys.back() - yFinal);
	if(!strcmp(tipo, "manhattan"))
	{
		return dx + dy;
	}

	else if(!strcmp(tipo, "octile"))
	{
		return max(dx, dy) + 0.5 * min(dx, dy);
	}

	else
	{
		return 0.0; 
	}
}
