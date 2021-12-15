#include"funkcije.h"
#include<stdio.h>
#define SPACE (10)

stablo noviElement(stablo root,int Broj)
{
	stablo novi = (stablo)malloc(sizeof(Stablo));	
	novi = root;
	if (novi == NULL) {
		stablo novi = (stablo)malloc(sizeof(Stablo));
		novi->broj = Broj;
		novi->lijevo = NULL;
		novi->desno = NULL;

		return novi;
	}

	else if (Broj > novi->broj)
		novi->desno = noviElement(novi->desno, Broj);

	else if (Broj < novi->broj)
		novi->lijevo = noviElement(novi->lijevo, Broj);

	return novi;
}

stablo unos(stablo root)
{
	int odabir = 0;
	stablo izbor = NULL;

	printf("\nOdaberi unos: ");
	scanf("%d", &odabir);

	switch (odabir) {
	case 1:
		root = noviElement(root, broj());
		return root;
	case 2:
		ispisStabla(root, 0);
		return root;
	case 3:
		printf("\nPREORDER ISPIS:");
		preorder(root);
		printf("\n");
		return root;
	case 4:
		printf("\nINORDER ISPIS:");
		inorder(root);
		printf("\n");
		return root;
	case 5:
		printf("\nPOSTORDER ISPIS:");
		postorder(root);
		printf("\n");
		return root;
	case 6:	
		izbor = pronadiElement(root, broj());
		izbrisiElement(root, izbor);
		return root;
	case 7:
		Izbornik();
		return root;
	case 0:
		return NULL;
	default:
		printf("Pogresan unos!\n");
		return 1;
	}

}

int broj()
{
	int br = 0;
	printf("Unesi broj: ");
	scanf("%d", &br);

	return br;
}

int ispisStabla(stablo root, int space)
{
	int i = 0;
	if (root == NULL)
		return NULL;

	space += SPACE;
	ispisStabla(root->desno, space);
	printf("\n");

	for (i = SPACE; i < space; i++)
		printf(" ");
	printf("%d\n", root->broj);

	ispisStabla(root->lijevo, space);

	return EXIT_SUCCESS;
}

int preorder(stablo root)
{
	if (root == NULL)
		return NULL;

	printf(" %d ", root->broj);
	preorder(root->lijevo);
	preorder(root->desno);

	return EXIT_SUCCESS;
}

int inorder(stablo root)
{
	if (root == NULL)
		return NULL;
	inorder(root->lijevo);
	printf(" %d ", root->broj);
	inorder(root->desno);

	return EXIT_SUCCESS;
}
int postorder(stablo root)
{
	if (root == NULL)
		return NULL;
	postorder(root->lijevo);
	postorder(root->desno);
	printf(" %d ", root->broj);

	return EXIT_SUCCESS;	
}

stablo pronadiElement(stablo root, int p)
{
	stablo element = NULL;
	element = root;

	if (element == NULL)
		return NULL;

	else if (element->broj == p)
		return element;

	else if (p > element->broj)
		return pronadiElement(element->desno, p);

	else if (p < element->broj)
		return pronadiElement(element->lijevo, p);

	return element;
}

stablo pronadiNajmanjiElement(stablo root)
{
	if (root == NULL)
		return NULL;
	else if (root->lijevo == NULL)
		return root;

	return pronadiNajmanjiElement(root->lijevo);
}

stablo izbrisiElement(const stablo root, stablo obrisi)
{
	stablo pom = (stablo)root;
	stablo temp = NULL;

	if (pom == NULL)
		return NULL;

	else if (obrisi->broj < pom->broj)
		pom->lijevo = izbrisiElement(pom->lijevo, obrisi);

	else if (obrisi->broj > pom->broj)
		pom->desno = izbrisiElement(pom->desno, obrisi);

	else if (pom->lijevo && pom->desno)
	{
		temp = pronadiNajmanjiElement(pom->desno);
		pom->broj = temp->broj;
		pom->desno = izbrisiElement(pom->desno, pom);
	}

	else {
		temp = pom;

		if (pom->lijevo == NULL)
			pom = pom->desno;
		else
			pom = pom->lijevo;

		free(temp);
	}

	return pom;

}

int Izbornik()
{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("1 - Unesi novi element\n");
	printf("2 - Ispis stabla\n");
	printf("3 - Ispisi elemente stabla (PREORDER)\n");
	printf("4 - Ispisi elemente stabla (INORDER)\n");
	printf("5 - Ispisi elemente stabla (POSTORDER)\n");
	printf("6 - Izbrisi element stabla\n");
	printf("7 - Ponovo ispisi izbornik\n");
	printf("0 - Zatvori program\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	return 0;
}