
#ifndef DEKLARACIJE_H
#define DEKLARACIJE_H

typedef struct _ElementStoga* pozicija;
typedef struct _ElementStoga {
	double broj;
	pozicija next;
}ElementStoga;

int IzracunajPostfix(char* imeDatoteke, double* rezultat);
char* ProcitajDatoteku(char* imeDatoteke);
int ParseStringIntoPostfix(char* buffer, double* rezultat);
int RezultatStoga(pozicija* head, double* rezultat);
pozicija StvoriElementStoga(double broj);
int UmetniIza(pozicija head, pozicija noviElement);
int IspisStoga(pozicija head);
int Pop(pozicija head, double* rezultat);
int IzvediOperaciju(pozicija head,char operacija, double* rezultat);

#endif