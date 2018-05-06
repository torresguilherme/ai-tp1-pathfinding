#include "ids.h"
using namespace std;

Position IDS(Map* map, int xInicial, int yInicial, int xFinal, int yFinal)
{
	Position aux;

	//initial values
	float cost = 0;

	aux.xs.push_back(xInicial);
	aux.ys.push_back(yInicial);
	aux.costs.push_back(cost);
	aux.depth = 0;

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

	stack<Position> frontier;
	Position current;

	for(int i = 1; i < map->height * map->width; i++)
	{
		frontier.push(aux);
		while(!frontier.empty())
		{
			current = frontier.top();
			frontier.pop();
			if(current.depth == i)
			{
				// verifica se é o nó final
				if(isFinal(current, xFinal, yFinal))
				{
					return current;
				}
			}
			else
			{
				bool upFree = false;
				bool downFree = false;
				bool leftFree = false;
				bool rightFree = false;
				// empurra outros nos na pilha
				// up
				if(current.xs.back() > 1
				&& map->matrix[current.xs.back() - 1][current.ys.back()] == '.'
				&& !current.visited[current.xs.back() - 1][current.ys.back()])
				{
					upFree = true;
					Position newP = current;
					newP.xs.push_back(current.xs.back() - 1);
					newP.ys.push_back(current.ys.back());
					newP.costs.push_back(newP.costs.back()+1);
					newP.depth = current.depth + 1;
					newP.visited[newP.xs.back()-1][newP.ys.back()] = true;
					frontier.push(newP);
				}

				// down
				if(current.xs.back() < map->height - 1
				&& map->matrix[current.xs.back() + 1][current.ys.back()] == '.'
				&& !current.visited[current.xs.back() + 1][current.ys.back()])
				{
					downFree = true;
					Position newP = current;
					newP.xs.push_back(current.xs.back() + 1);
					newP.ys.push_back(current.ys.back());
					newP.costs.push_back(newP.costs.back()+1);
					newP.depth = current.depth + 1;
					newP.visited[newP.xs.back()+1][newP.ys.back()] = true;
					frontier.push(newP);
				}

				// left
				if(current.ys.back() > 1
				&& map->matrix[current.xs.back()][current.ys.back() - 1] == '.'
				&& !current.visited[current.xs.back()][current.ys.back() - 1])
				{
					leftFree = true;
					Position newP = current;
					newP.ys.push_back(current.ys.back() - 1);
					newP.xs.push_back(current.xs.back());
					newP.costs.push_back(newP.costs.back()+1);
					newP.depth = current.depth + 1;
					newP.visited[newP.xs.back()][newP.ys.back()-1] = true;
					frontier.push(newP);
				}

				// right
				if(current.ys.back() < map->width - 1
				&& map->matrix[current.xs.back()][current.ys.back() + 1] == '.'
				&& !current.visited[current.xs.back()][current.ys.back() + 1])
				{
					rightFree = true;
					Position newP = current;
					newP.ys.push_back(current.ys.back() + 1);
					newP.xs.push_back(current.xs.back());
					newP.costs.push_back(newP.costs.back()+1);
					newP.depth = current.depth + 1;
					newP.visited[newP.xs.back()][newP.ys.back()+1] = true;
					frontier.push(newP);
				}
	
				// diag
				if(upFree && leftFree && map->matrix[current.xs.back()-1][current.ys.back()-1] == '.')
				{
					Position newP = current;
					newP.ys.push_back(current.ys.back() - 1);
					newP.xs.push_back(current.xs.back() - 1);
					newP.costs.push_back(newP.costs.back()+1.5);
					newP.depth = current.depth + 1;
					newP.visited[newP.xs.back()-1][newP.ys.back()-1] = true;
					frontier.push(newP);
				}
				if(upFree && rightFree && map->matrix[current.xs.back()-1][current.ys.back()+1] == '.')
				{
					Position newP = current;
					newP.ys.push_back(current.ys.back() + 1);
					newP.xs.push_back(current.xs.back() - 1);
					newP.costs.push_back(newP.costs.back()+1.5);
					newP.depth = current.depth + 1;
					newP.visited[newP.xs.back()-1][newP.ys.back()+1] = true;
					frontier.push(newP);
				}
				if(downFree && leftFree && map->matrix[current.xs.back()+1][current.ys.back()-1] == '.')
				{
					Position newP = current;
					newP.ys.push_back(current.ys.back() - 1);
					newP.xs.push_back(current.xs.back() + 1);
					newP.costs.push_back(newP.costs.back()+1.5);
					newP.depth = current.depth + 1;
					newP.visited[newP.xs.back()+1][newP.ys.back()-1] = true;
					frontier.push(newP);
				}
				if(downFree && rightFree && map->matrix[current.xs.back()+1][current.ys.back()+1] == '.')
				{
					Position newP = current;
					newP.ys.push_back(current.ys.back() + 1);
					newP.xs.push_back(current.xs.back() + 1);
					newP.costs.push_back(newP.costs.back()+1.5);
					newP.depth = current.depth + 1;
					newP.visited[newP.xs.back()+1][newP.ys.back()+1] = true;
					frontier.push(newP);
				}
			}
		}
	}

	// returns failure
	Position failure;
	failure = aux;
	failure.xs.push_back(xFinal);
	failure.ys.push_back(yFinal);
	failure.costs.push_back(0);
	return failure;
}
