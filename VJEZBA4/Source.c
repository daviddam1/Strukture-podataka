#include<stdio.h>
#include<stdlib.h>

#define MAXSIZE 1024

typedef struct _element {
    int koeficijent;
    int eksponent;

    struct _element* next;
}element;

int UcitajDatoteku(element*, element*, FILE*);
element* Lista(element*, char*);
element* UmetniSortirano(element*, int, int);
int IspisiListu(element*);
element* ZbrojiElemente(element*, element*, element*);
element* PomnoziElemente(element*, element*, element*);

int main()
{
    element* polinom1 = NULL;
    element* polinom2 = NULL;
    element* zbroj = NULL;
    element* umnozak = NULL;
    
    polinom1 = (element*)malloc(sizeof(element));
    polinom2 = (element*)malloc(sizeof(element));
    zbroj = (element*)malloc(sizeof(element));
    umnozak = (element*)malloc(sizeof(element));

    polinom1->next = NULL;
    polinom2->next = NULL;
    zbroj->next = NULL;
    umnozak->next = NULL;

    FILE* datoteka = NULL;
    datoteka = fopen("polinomi.txt", "r");

    if (datoteka == NULL) {
        printf("ERROR!");
        return 0;
    }

    UcitajDatoteku(polinom1, polinom2, datoteka);
    
    printf("\nPolinom 1: ");
    IspisiListu(polinom1);
   
    printf("\n\nPolinom 2: ");
    IspisiListu(polinom2);
   
    zbroj= ZbrojiElemente(polinom1, polinom2, zbroj);
    printf("\n\nZbroj elemenata: ");
    IspisiListu(zbroj);
    
    umnozak = PomnoziElemente(polinom1, polinom2, umnozak);
    printf("\nUmnozak elementa: ");
    IspisiListu(umnozak);

    fclose(datoteka);
    return 0;
}

int UcitajDatoteku(element* polinom1, element* polinom2, FILE* datoteka)
{
    char* buffer = (char*)malloc(sizeof(char) * MAXSIZE);

    fgets(buffer, MAXSIZE, datoteka);
    polinom1 = Lista(polinom1, buffer);
    fgets(buffer, MAXSIZE, datoteka);
    polinom2 = Lista(polinom2, buffer);

    return 0;
}

element* Lista(element* head, char* buffer)
{
    int koeficijent, eksponent, n;

    while (*buffer != 0) {
        sscanf(buffer, " %d %d %n", &koeficijent, &eksponent, &n);
        buffer += n;
        head = UmetniSortirano(head, koeficijent, eksponent);
    }

    return head;
}

element* UmetniSortirano(element* head, int koeficijent, int eksponent)
{
    if (head->next == NULL) {
        element* novi = (element*)malloc(sizeof(element));
        novi->eksponent = eksponent;
        novi->koeficijent = koeficijent;
        novi->next = NULL;
        head->next = novi;
        return head;
    }

    element* pom = head->next;

    if (eksponent > pom->eksponent) {
        element* novi = (element*)malloc(sizeof(element));
        novi->eksponent = eksponent;
        novi->koeficijent = koeficijent;
        head->next = novi;
        novi->next = pom;
        return head;
    }

    else {
        while (pom->next != NULL && eksponent < pom->next->eksponent)
            pom = pom->next;

        if (pom->next != NULL && eksponent == pom->next->eksponent)
            pom->next->koeficijent += koeficijent;

        else if (eksponent == pom->eksponent)
            pom->koeficijent += koeficijent;

        else {
            element* novi = (element*)malloc(sizeof(element));
            novi->eksponent = eksponent;
            novi->koeficijent = koeficijent;
            novi->next = pom->next;
            pom->next = novi;
        }
    }

    return head;
}

int IspisiListu(element* P)
{
    if (P->next == NULL) {
        printf("\nPrazna lista.");
        return -1;
    }

    element* pom = P->next;

    do {
        printf("%d^%d + ", pom->koeficijent, pom->eksponent);
        pom = pom->next;
    } while (pom->next != NULL);
    printf("%d^%d ", pom->koeficijent, pom->eksponent);

    return 0;
}

element* ZbrojiElemente(element* polinom1, element* polinom2, element* zbroj)
{
    if (polinom1->next == NULL)
        return polinom2;
    if (polinom2->next == NULL)
        return polinom1;
    if (polinom1->next == NULL && polinom2->next == NULL)
        return NULL;

    polinom1 = polinom1->next;
    polinom2 = polinom2->next;

    while (polinom1 != NULL) {
        zbroj = UmetniSortirano(zbroj, polinom1->koeficijent, polinom1->eksponent);
        polinom1 = polinom1->next;
    }
    while (polinom2 != NULL) {
        zbroj = UmetniSortirano(zbroj, polinom2->koeficijent, polinom2->eksponent);
        polinom2 = polinom2->next;
    }

    return zbroj;
}


element* PomnoziElemente(element* polinom1, element* polinom2, element* head)
{
    element* pom1 = polinom1->next;
    element* pom2 = polinom2->next;

    while (pom1 != NULL) {
        pom2 = pom2->next;
        while (pom2 != NULL) {

            UmetniSortirano(head, pom1->koeficijent * pom2->koeficijent, pom1->eksponent + pom2->eksponent);
            pom2 = pom2->next;

        }
        pom1 = pom1->next;
    }

    return head;
}