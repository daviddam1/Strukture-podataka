#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH (128)
#define MAX_LINE (1024)
#define HASH_SIZE (11)

struct _ListaDrzave;
typedef struct _ListaDrzave* ListaDrzavePozicija;
struct _StabloGradovi;
typedef struct _StabloGradovi* StabloGradoviPozicija;

typedef struct _ListaDrzave {
	char *imeDrzave;
	ListaDrzavePozicija root;
	ListaDrzavePozicija next;
}Lista;

typedef struct _StabloGradovi {
	char *imeGrada;
	int brojStanovnika;
	StabloGradoviPozicija lijevo;
	StabloGradoviPozicija desno;
}Stablo;

ListaDrzavePozicija novaDrzava(char*);
int UmetniDrzavu(ListaDrzavePozicija, ListaDrzavePozicija);
int UmetniIza(ListaDrzavePozicija, ListaDrzavePozicija);
ListaDrzavePozicija pronadiDrzavu(ListaDrzavePozicija, char*);

StabloGradoviPozicija noviGrad(char*, int);
int gradUsporedi(StabloGradoviPozicija, StabloGradoviPozicija);

int ProcitajIzDatoteke(ListaDrzavePozicija[], char*);
int IspisListe(ListaDrzavePozicija);

StabloGradoviPozicija StvoriStabloIzDatoteke(char*);
int UmetniElement(StabloGradoviPozicija, StabloGradoviPozicija);
int IspisSilazno(StabloGradoviPozicija);
int IspisiVeci(StabloGradoviPozicija,int);

int TraziGrad(StabloGradoviPozicija[]);