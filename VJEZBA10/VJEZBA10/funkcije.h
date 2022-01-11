#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LENGTH (128)
#define MAX_LINE (1024)

struct _ListaDrzave;
typedef struct _ListaDrzave * ListaDrzavePozicija;
struct _StabloGradovi;
typedef struct _StabloGradovi* StabloGradoviPozicija;

typedef struct _ListaDrzave {
	char imeDrzave[MAX_LENGTH];
	ListaDrzavePozicija root;
	ListaDrzavePozicija next;
}Lista;

typedef struct _StabloGradovi {
	char imeGrada[MAX_LENGTH];
	int brojStanovnika;
	StabloGradoviPozicija lijevo;
	StabloGradoviPozicija desno;
}Stablo;

int UnesiSortirano(ListaDrzavePozicija , ListaDrzavePozicija);
ListaDrzavePozicija stvoriDrzavu(char);
int UmetniUStablo(StabloGradoviPozicija, StabloGradoviPozicija);
int UcitajDrzavu(ListaDrzavePozicija);

StabloGradoviPozicija StvoriGrad(char, int);
int Inorder(StabloGradoviPozicija);
int UcitajGrad(char);

ListaDrzavePozicija PronadiDrzavu(ListaDrzavePozicija, char);
int IspisiSveElementeListe(ListaDrzavePozicija);
int PronadiGradove(StabloGradoviPozicija, int);