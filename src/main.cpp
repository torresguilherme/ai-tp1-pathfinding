#include <cstring>
#include "ids.h"
#include "bestFirst.h"

int main(int argc, char **argv)
{
	const char *fileName = argv[1];
	const char *algorithm = argv[2];
	int xInicial = atoi(argv[3]);
	int yInicial = atoi(argv[4]);
	int xFinal = atoi(argv[5]);
	int yFinal = atoi(argv[6]);

	const char *heuristic;
	if (!strcmp(algorithm, "A*")||!strcmp(algorithm, "greedyBFS"))
	{
		heuristic = argv[7];
	}

	// inicializa mapa
	Map *m = initMap(fileName);

	Position solution;
	if(!strcmp(algorithm, "IDS"))
	{
		solution = IDS(m, xInicial, yInicial, xFinal, yFinal);
	}
	else if(!strcmp(algorithm, "UCS"))
	{
		solution = bestFirst(m, heuristic, 0, xInicial, yInicial, xFinal, yFinal);
	}
	else if(!strcmp(algorithm, "greedyBFS"))
	{
		solution = bestFirst(m, heuristic, 2, xInicial, yInicial, xFinal, yFinal);
	}
	else if(!strcmp(algorithm, "A*"))
	{
		solution = bestFirst(m, heuristic, 1, xInicial, yInicial, xFinal, yFinal);
	}
	else
	{
		std::cerr<<"tipo de algoritmo nao reconhecido"<<std::endl;
		return -1;
	}

	std::cout<<"<"<<solution.xs.front()<<", "<<solution.ys.front()<<", "<<solution.costs.front()<<">"<<std::endl;
	std::cout<<"<"<<solution.xs.back()<<", "<<solution.ys.back()<<", "<<solution.costs.back()<<">"<<std::endl<<std::endl;
	
	// aplica o algoritmo
	// libera o mapa
	freeMap(m);
}
