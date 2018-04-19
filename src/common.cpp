#include "common.h"
using namespace std;

Map *initMap(const char *fileName)
{
	Map *ret = (Map*)malloc(sizeof(Map));
	FILE *f = fopen(fileName, "r");
	if(f == NULL)
	{
		cerr<<"arquivo de entrada nao encontrado"<<endl;
		exit(1);
	}

	if(!fscanf(f, "type %s", ret->type))
	{
		cout<<"entrada formatada incorretamente"<<endl;
		exit(1);
	}
	fseek(f, 1, SEEK_CUR);
	if(!fscanf(f, "height %i", &ret->height))
	{
		cout<<"entrada formatada incorretamente"<<endl;
		exit(1);
	}
	fseek(f, 1, SEEK_CUR);
	if(!fscanf(f, "width %i", &ret->width))
	{
		cout<<"entrada formatada incorretamente"<<endl;
		exit(1);
	}
	fseek(f, 1, SEEK_CUR);
	if(!fscanf(f, "%s", ret->name))
	{
		cout<<"entrada formatada incorretamente"<<endl;
		exit(1);
	}
	fseek(f, 1, SEEK_CUR);
	ret->matrix = (char**)malloc(sizeof(char*) * ret->height);
	for(int i = 0; i < ret->height; i++)
	{
		ret->matrix[i] = (char*)malloc(sizeof(char) * ret->width);
		for (int j = 0; j < ret->width; j++)
		{
			if(!fscanf(f, "%c", &ret->matrix[i][j]))
			{
				cout<<"entrada formatada incorretamente"<<endl;
				exit(1);
			}
		}
		fseek(f, 1, SEEK_CUR);
	}
	return ret;
}

void freeMap(Map *m)
{
	for(int i = 0; i < m->height; i++)
	{
		delete[] m->matrix[i];
	}
	delete[] m->matrix;
	delete m;
}

bool isFinal(Position p, int xFinal, int yFinal)
{
	return (p.xs[p.ys.size() - 1] == xFinal && p.ys[p.ys.size() - 1] == yFinal);
}
