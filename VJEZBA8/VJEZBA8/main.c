#include"funkcije.h"
#include<stdio.h>
#include<stdlib.h>

int main()
{
	stablo root;
	root = NULL;

	Izbornik();

	do 
	{
	 root = unos(root);
	} while (root);

	return 0;
}