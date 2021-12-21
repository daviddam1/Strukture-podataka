#include"funkcije.h"
#include<stdio.h>
#include<stdlib.h>

//a) potrebno obaviti unos brojeva kako je zadano u zadataku, program je napravljen za sve slucajeve unosa brojeva!
/*c) jedini problem kod ispisa u datoteku je append mode koji samo nastavlja
	u isti redak ispisivati obicni inorder ispis pod a) i sumirani inorder ispis pod b)*/

int main()
{
	stablo root = NULL;

	Izbornik();

	do {
		root = unos(root);
	} while (root);

	return 0;
}