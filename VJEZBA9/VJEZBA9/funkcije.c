#include "funkcije.h"
#include<stdio.h>
#include<time.h>
#define SPACE (10)
#define MIN (10)
#define MAX (90)


stablo unosElementa(stablo root, int br)
{
	stablo noviElement = (stablo)malloc(sizeof(Stablo));
	noviElement = root;
	if (noviElement == NULL)
	{
		stablo noviElement = (stablo)malloc(sizeof(Stablo));
		noviElement->broj = br;
		noviElement->lijevo = NULL;
		noviElement->desno = NULL;

		return noviElement;
	}

	else if (br >= noviElement->broj)
		noviElement->desno = unosElementa(noviElement->desno, br);

	else if (br < noviElement->broj)
		noviElement->lijevo= unosElementa(noviElement->lijevo, br);
	

	return noviElement;	
}

int inorder(stablo root)
{
	if (root == NULL)
		return 0;
	inorder(root->lijevo);
	printf("%d ", root->broj);
	inorder(root->desno);

	return EXIT_SUCCESS;
}

int ispisStabla(stablo root, int space)
{
	int i = 0;
	if (root == NULL)
		return NULL;

	space += SPACE;
	ispisStabla(root->lijevo, space);
	printf("\n");

	for (i = SPACE; i < space; i++)
		printf(" ");
	printf("%d\n", root->broj);

	ispisStabla(root->desno, space);

	return EXIT_SUCCESS;
}

int Izbornik()
{
	printf("\n************************************\n");
	printf("1 - Unos novog elementa\n");
	printf("2 - Ispis stabla\n");
	printf("3 - Ispis inorder\n");
	printf("4 - Ispis sa sumiranom djecom\n");
	printf("5 - Random broj\n");
	printf("6 - Ispis inorder sa sumiranom djecom\n");

	printf("7 - Izbornik\n");
	printf("\n************************************\n");
}

stablo unos(stablo root)
{
	int i = 0;
	int odabir = 0;
	stablo izbor = NULL;

	printf("\nOdaberi unos: ");
	scanf("%d", &odabir);

	switch (odabir) {
	case 1:
		root = unosElementa(root, broj());
		return root;
	case 2:
		ispisStabla(root, 0);
		return root;
	case 3:
		printf("\nINORDER ISPIS: ");
		inorder(root);
		printf("\n");
		UpisUDatoteku(root);
		return root;
	//b)
	case 4:
		root->broj = zamjeni(root);
		ispisStabla(root, 0);
		return root;
	//c)
	case 5:
		for (i = 0; i < 10; i++) {
			root = unosElementa(root, rng(MIN, MAX));
			return root;
		}
	case 6:
		printf("\nINORDER ISPIS (sumirano): ");
		inorder(root);
		UpisUDatoteku(root);
		return root;
	case 7:
		Izbornik();
		return 1;
	case 0:
		return NULL;
	default:
		printf("Pogresan unos!\n");
		return 0;
	}
}

int broj()
{
	int br = 0;
	printf("Unesi broj: ");
	scanf("%d", &br);

	return br;
}

int zamjeni(stablo root)
{
	int pom=0;
	if (root == NULL)
		return 0;

	else {
		pom = root->broj;
		root->broj = zamjeni(root->desno) + zamjeni(root->lijevo);
	}

	return pom + root->broj;
}

//c)
int rng(int d, int g)
{
	srand(time(0));
	int Broj = 0;
	Broj = (rand() % (g - d + 1))+d;
	
	return Broj;
}

int UpisUDatoteku(stablo root)
{
	FILE* fp = fopen("ispis.txt", "a");
	UpisRekurzivno(fp, root);

	fclose(fp);

	return EXIT_SUCCESS;
}

int UpisRekurzivno(FILE* fp, stablo root)
{
	if (root != NULL)
	{
		UpisRekurzivno(fp,root->lijevo);
		fprintf(fp, "%d ", root->broj);
		UpisRekurzivno(fp,root->desno);		
	}

	return EXIT_SUCCESS;
}