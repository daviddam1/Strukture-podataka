#include<stdio.h>
#include<stdlib.h>

typedef struct _stablo* stablo;
typedef struct _stablo {
	int broj;
	stablo lijevo;
	stablo desno;
}Stablo;

stablo noviElement(stablo,int);
stablo unos(stablo);

int Izbornik();

int broj();
int ispisStabla(stablo, int);
int preorder(stablo);
int inorder(stablo);
int postorder(stablo);
stablo pronadiElement(stablo, int);

stablo pronadiNajmanjiElement(stablo);
stablo izbrisiElement(const stablo, stablo);




