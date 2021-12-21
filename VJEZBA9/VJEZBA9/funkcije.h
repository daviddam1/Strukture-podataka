#include<stdio.h>
#include<stdlib.h>

typedef struct _stablo* stablo;
typedef struct _stablo {
	int broj;
	stablo lijevo;
	stablo desno;
}Stablo;


typedef struct cvor* pozicija;
typedef struct cvor {
	int broj;
	pozicija next;
} Cvor;
//a)
stablo unosElementa(stablo, int);
stablo unos(stablo);

int inorder(stablo);
int ispisStabla(stablo, int);
int Izbornik();
int broj();

//b)
int zamjeni(stablo);

//c)
int rng(int, int);
int UpisUDatoteku(stablo);
int UpisRekurzivno(FILE*, stablo);
