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

	vector<vector<bool>> visited;
	for(int i = 0; i < map->height; i++)
	{
		vector<bool> v;
		visited.push_back(v);
		for(int j = 0; j < map->width; j++)
		{
			visited[i].push_back(false);
		}
	}

	visited[xInicial][yInicial] = true;

	if(isFinal(aux, xFinal, yFinal))
	{
		return aux;
	}

	vector<Position> front;
	front.push_back(aux);

	while(!front.empty())
	{
		//ordena a fila de acordo com a prioridade de cada nó
		qsort(front.data(), front.size(), sizeof(Position), compare);
		Position current = front.front();
		front.erase(front.begin());
		if(isFinal(current, xFinal, yFinal))
		{
			return current;
		}

		bool upFree = false;
		bool downFree = false;
		bool leftFree = false;
		bool rightFree = false;
		// empurra outros nos na pilha
		// up
		if(current.xs.back() > 0
				&& map->matrix[current.xs.back() - 1][current.ys.back()] == '.'
				&& !visited[current.xs.back() - 1][current.ys.back()])
		{
			upFree = true;
			Position newP = current;
			newP.xs.push_back(current.xs.back() - 1);
			newP.ys.push_back(current.ys.back());
			newP.costs.push_back(newP.costs.back()+1);
			newP.depth = current.depth + 1;
			visited[newP.xs.back()][newP.ys.back()] = true;
			newP.priority = (2 - w) * newP.costs.back() + w * hValue(newP, xFinal, yFinal, heuristic);
			front.push_back(newP);
		}

		// down
		if(current.xs.back() < map->height - 1
				&& map->matrix[current.xs.back() + 1][current.ys.back()] == '.'
				&& !visited[current.xs.back() + 1][current.ys.back()])
		{
			downFree = true;
			Position newP = current;
			newP.xs.push_back(current.xs.back() + 1);
			newP.ys.push_back(current.ys.back());
			newP.costs.push_back(newP.costs.back()+1);
			newP.depth = current.depth + 1;
			visited[newP.xs.back()][newP.ys.back()] = true;
			newP.priority = (2 - w) * newP.costs.back() + w * hValue(newP, xFinal, yFinal, heuristic);
			front.push_back(newP);
		}

		// left
		if(current.ys.back() > 0
				&& map->matrix[current.xs.back()][current.ys.back() - 1] == '.'
				&& !visited[current.xs.back()][current.ys.back() - 1])
		{
			leftFree = true;
			Position newP = current;
			newP.ys.push_back(current.ys.back() - 1);
			newP.xs.push_back(current.xs.back());
			newP.costs.push_back(newP.costs.back()+1);
			newP.depth = current.depth + 1;
			visited[newP.xs.back()][newP.ys.back()] = true;
			newP.priority = (2 - w) * newP.costs.back() + w * hValue(newP, xFinal, yFinal, heuristic);
			front.push_back(newP);
		}
		// right
		if(current.ys.back() < map->width - 1
				&& map->matrix[current.xs.back()][current.ys.back() + 1] == '.'
				&& !visited[current.xs.back()][current.ys.back() + 1])
		{
			rightFree = true;
			Position newP = current;
			newP.ys.push_back(current.ys.back() + 1);
			newP.xs.push_back(current.xs.back());
			newP.costs.push_back(newP.costs.back()+1);
			newP.depth = current.depth + 1;
			visited[newP.xs.back()][newP.ys.back()] = true;
			newP.priority = (2 - w) * newP.costs.back() + w * hValue(newP, xFinal, yFinal, heuristic);
			front.push_back(newP);
		}

		// diag
		if(upFree && leftFree && map->matrix[current.xs.back()-1][current.ys.back()-1] == '.')
		{
			Position newP = current;
			newP.ys.push_back(current.ys.back() - 1);
			newP.xs.push_back(current.xs.back() - 1);
			newP.costs.push_back(newP.costs.back()+1.5);
			newP.depth = current.depth + 1;
			visited[newP.xs.back()][newP.ys.back()] = true;
			newP.priority = (2 - w) * newP.costs.back() + w * hValue(newP, xFinal, yFinal, heuristic);
			front.push_back(newP);
		}
		if(upFree && rightFree && map->matrix[current.xs.back()-1][current.ys.back()+1] == '.')
		{
			Position newP = current;
			newP.ys.push_back(current.ys.back() + 1);
			newP.xs.push_back(current.xs.back() - 1);
			newP.costs.push_back(newP.costs.back()+1.5);
			newP.depth = current.depth + 1;
			visited[newP.xs.back()][newP.ys.back()] = true;
			newP.priority = (2 - w) * newP.costs.back() + w * hValue(newP, xFinal, yFinal, heuristic);
			front.push_back(newP);
		}
		if(downFree && leftFree && map->matrix[current.xs.back()+1][current.ys.back()-1] == '.')
		{
			Position newP = current;
			newP.ys.push_back(current.ys.back() - 1);
			newP.xs.push_back(current.xs.back() + 1);
			newP.costs.push_back(newP.costs.back()+1.5);
			newP.depth = current.depth + 1;
			visited[newP.xs.back()][newP.ys.back()] = true;
			newP.priority = (2 - w) * newP.costs.back() + w * hValue(newP, xFinal, yFinal, heuristic);
			front.push_back(newP);
		}
		if(downFree && rightFree && map->matrix[current.xs.back()+1][current.ys.back()+1] == '.')
		{
			Position newP = current;
			newP.ys.push_back(current.ys.back() + 1);
			newP.xs.push_back(current.xs.back() + 1);
			newP.costs.push_back(newP.costs.back()+1.5);
			newP.depth = current.depth + 1;
			visited[newP.xs.back()][newP.ys.back()] = true;
			newP.priority = (2 - w) * newP.costs.back() + w * hValue(newP, xFinal, yFinal, heuristic);
			front.push_back(newP);
		}
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
	if(tipo == NULL)
	{
		return 0.0;
	}

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

int compare(const void *a, const void *b)
{
	Position *pa = (Position*) a;
	Position *pb = (Position*) b;
	return (int)(pa->priority - pb->priority);
}
