#include "deklaracije.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int main(int argc, char* argv[])
{
	double rezultat = 0;

	if (argc == 1)
	{
		if (IzracunajPostfix("postfix.txt",&rezultat) == EXIT_SUCCESS)
		{
			printf("Rezultat je: %0.1lf\n", rezultat);
		}
	}
	else if (IzracunajPostfix(argv[1], &rezultat) == EXIT_SUCCESS)
	{
		printf("Rezultat je %0.1lf\n", rezultat);
	}

	return EXIT_SUCCESS;

}