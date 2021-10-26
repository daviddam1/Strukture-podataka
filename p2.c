#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXSIZE (50)

struct _Osoba;
typedef struct _Osoba *pozicija;

typedef struct _Osoba {
	char ime[MAXSIZE];
	char prezime[MAXSIZE];
	int godRod;
	pozicija slijedeci;
}Osoba;

int PocetakListe(pozicija head, char* ime, char* prezime, int godRod);
int KrajListe(pozicija head, char* ime, char* prezime, int godRod);
int IspisListe(pozicija prvi);
pozicija StvoriOsobu(char* ime, char* prezime, int godRod);
int UpisiIza(pozicija Pozicija, pozicija novaOsoba);
pozicija PronadjiZadnjeg(pozicija head);
int PronadjiPoPrezimenu(pozicija prvi,char* prezime);
pozicija PronadjiPrije(pozicija prvi);
int ObrisiPoslije(pozicija head, char* prezime);


int main(int argc,char** argv)
{
	int i,n;
	Osoba Head = { .slijedeci = NULL, .ime = {0}, .prezime = {0}, .godRod = 0 };
	pozicija p = &Head;

	printf("Koliko osoba zelite unijeti: ");
	scanf("%d", &n);

	StvoriOsobu(Head.ime, Head.prezime, Head.godRod);

	return EXIT_SUCCESS;
}

int PocetakListe(pozicija head, char* ime, char* prezime, int godRod)
{
	pozicija novaOsoba = NULL;
	
	novaOsoba = StvoriOsobu(ime, prezime, godRod);
	if (!novaOsoba)
	{
		return -1;
	}

	UpisiIza(head, novaOsoba);

	return EXIT_SUCCESS;
}

int KrajListe(pozicija head, char* ime, char* prezime, int godRod)
{
	pozicija novaOsoba = NULL;
	pozicija zadnja = NULL;

	novaOsoba = StvoriOsobu(ime, prezime, godRod);
	if (!novaOsoba)
	{
		return -1;
	}

	zadnja = PronadjiZadnjeg(head);
	UpisiIza(zadnja, novaOsoba);

	return EXIT_SUCCESS;
}

int IspisListe(pozicija prvi)
{
	pozicija temp = prvi;

	while (temp)
	{
		printf("Ime: %s, prezime: %s, godina rodjenja: %d\n",
			temp->ime, temp->prezime, temp->godRod);
	}

	return EXIT_SUCCESS;
}

pozicija StvoriOsobu(char* ime, char* prezime, int godRod)
{
	pozicija novaOsoba = NULL;

	novaOsoba = (pozicija)malloc(sizeof(Osoba));
	if (!novaOsoba)
	{
		perror("Ne mogu alocirati memoriju!\n");
		return -1;
	}

	strcpy(novaOsoba->ime, ime);
	strcpy(novaOsoba->prezime, prezime);
	novaOsoba->godRod = godRod;
	novaOsoba->slijedeci = NULL;

	return novaOsoba;
}

int UpisiIza(pozicija Pozicija, pozicija novaOsoba)
{
	novaOsoba->slijedeci = Pozicija->slijedeci;
	Pozicija->slijedeci = novaOsoba;

	return EXIT_SUCCESS;
}

pozicija PronadjiZadnjeg(pozicija head)
{
	pozicija temp = head;
	
	while (temp->slijedeci) {}

	return temp;
}

int PronadjiPoPrezimenu(pozicija prvi, char* prezime)
{
	pozicija temp = prvi;
	
	while (temp) {
		if (strcmp(temp->prezime, prezime) == 0)
			return temp;
	}

	return temp;
}

pozicija PronadjiPrije(pozicija head,pozicija prvi)
{
	pozicija temp1 = head;
	pozicija temp = prvi;

	while (temp1)
	{
		if (temp1->slijedeci == temp)
		{
			return temp1;
		}

		temp1 = temp1->slijedeci;			
	}

	return NULL;

}

int ObrisiPoslije(pozicija head, char* prezime)
{
	char* prezime1 = prezime;
	pozicija pom = head;
	pozicija pom1 = PronadjiPoPrezimenu(pom, prezime1);
	pom->slijedeci = pom->slijedeci;
	free(pom);
}
