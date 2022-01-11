#include "funkcije.h"

int UnesiSortirano(ListaDrzavePozicija head, ListaDrzavePozicija noviElement)
{
	ListaDrzavePozicija pom=head;

	while (pom->next && strcmp(pom->next->imeDrzave, noviElement->imeDrzave))
		pom = pom->next;

	noviElement->next = pom->next;
	pom->next = noviElement;

	return 0;
}

ListaDrzavePozicija stvoriDrzavu(char ime[])
{
	ListaDrzavePozicija element = NULL;

	element = (ListaDrzavePozicija)malloc(sizeof(Lista));
	if (!element) {
		printf("Ne mogu alocirati memoriju!");
		return -1;
	}

	strcpy(element->imeDrzave, ime);

	element->next = NULL;
	element->root = NULL;

	return element;
}

int UmetniUStablo(StabloGradoviPozicija pozicija, StabloGradoviPozicija noviElement)
{
	if (!pozicija)
		return noviElement;
	else if (noviElement->brojStanovnika > pozicija->brojStanovnika)
		pozicija->desno = UmetniUStablo(pozicija->desno, noviElement);

	else if (noviElement->brojStanovnika < pozicija->brojStanovnika)
		pozicija->lijevo = UmetniUStablo(pozicija->lijevo, noviElement);
	
	else {

		int status = 0;
		status = strcmp(noviElement->imeGrada, pozicija->imeGrada);

		if (status > 0)
			pozicija->desno = UmetniUStablo(pozicija->desno, noviElement);

		else if (status < 0)
			pozicija->lijevo = UmetniUStablo(pozicija->lijevo, noviElement);

		else {
			printf("\nElement vec postoji!\n");
			
			free(noviElement);
		}

	}

	return pozicija;
}

int UcitajDrzavu(ListaDrzavePozicija head)
{
	FILE* fp = NULL;
	char drzava[MAX_LENGTH] = { 0 };
	char datoteka[MAX_LENGTH] = { 0 };
	int byte = 0;

	ListaDrzavePozicija noviElement = NULL;

	fp = fopen("drzave.txt", "r");
	if (!fp)
	{
		printf("\nNe mogu otvoriti datoteku!\n");
		return -1;
	}

	char* buffer = (char*)malloc(MAX_LINE*sizeof(char));

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);

		if (sscanf(buffer, " %s %s %n", drzava, datoteka, &byte) == 2) {

			noviElement = stvoriDrzavu(drzava);
			UnesiSortirano(head, noviElement);
			noviElement->root = UcitajGrad(datoteka);
			buffer += byte;
		}
	}

	fclose(fp);
	
	return 0;
}

StabloGradoviPozicija StvoriGrad(char ime[], int brStanovnika)
{
	StabloGradoviPozicija noviElement = NULL;
	noviElement = (StabloGradoviPozicija)malloc(sizeof(Stablo));

	if (!noviElement) {
		printf("Ne mogu alocirati memoriju!\n");
		return -1;
	}

	strcpy(noviElement->imeGrada, ime);
	noviElement->brojStanovnika = brStanovnika;

	noviElement->desno = NULL;
	noviElement->lijevo = NULL;

	return noviElement;

}

int UcitajGrad(char datoteka[])
{
	FILE* fp = NULL;
	char grad[MAX_LENGTH] = { 0 };
	int brStanovnika[MAX_LENGTH] = { 0 };
	int byte = 0;
	StabloGradoviPozicija noviGrad = NULL;
	StabloGradoviPozicija root = NULL;
	fp=fopen(datoteka,"r");

	
	if (!fp)
	{
		printf("\nNe mogu otvoriti datoteku!\n");
		return -1;
	}

	char* buffer = (char*)malloc(MAX_LINE * sizeof(char));

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);

		if (sscanf(buffer, " %s %d %n", grad, &brStanovnika, &byte) == 2) {

			noviGrad = StvoriGrad(grad,brStanovnika);
			root = UmetniUStablo(root,noviGrad);
			buffer += byte;
		}
	}

	fclose(fp);
	return root;
}

int Inorder(StabloGradoviPozicija pozicija)
{
	if (!pozicija)
		return 0;

	Inorder(pozicija->lijevo);
	printf(" %s", pozicija->imeGrada);
	Inorder(pozicija->desno);

	return 0;
}

ListaDrzavePozicija PronadiDrzavu(ListaDrzavePozicija head, char TrazenaDrzava[])
{
	ListaDrzavePozicija pom = head;

	while (pom && strcmp(pom->imeDrzave, TrazenaDrzava))
		pom = pom->next;

	if (pom)
		return pom;

	else
	{
		printf("Ne postoji unesena drzava!\n");
		return 0;
	}

}

int IspisiSveElementeListe(ListaDrzavePozicija head)
{
	ListaDrzavePozicija pom = head;

	while (pom)
	{
		printf("%s \n", pom->imeDrzave);
		Inorder(pom->root);
		puts(" ");
		pom = pom->next;
	}

	return 0;
}

int PronadiGradove(StabloGradoviPozicija pozicija, int Stan)
{
	if (pozicija)
	{
		PronadiGradove(pozicija->lijevo, Stan);

		if (pozicija->brojStanovnika > Stan)
		{
			printf("%s ", pozicija->imeGrada);

		}

		PronadiGradove(pozicija->desno, Stan);
	}

	return 0;
}