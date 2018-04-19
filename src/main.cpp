#include <cstring>
#include "ids.h"
/*
#include "ucs.h"
#include "bestFirst.h"
#include "aStar.h"
*/

int main(int argc, char **argv)
{
	const char *fileName = argv[1];
	const char *algorithm = argv[2];
	int xInicial = atoi(argv[3]);
	int yInicial = atoi(argv[4]);
	int xFinal = atoi(argv[5]);
	int yFinal = atoi(argv[6]);

	const char *heuristic;
	if (!strcmp(algorithm, "A*"))
	{
		heuristic = argv[7];
	}

	// inicializa mapa
	Map *m = initMap(fileName);
	
	// aplica o algoritmo
	// libera o mapa
	freeMap(m);
}
