#include "funkcije.h"
#include <stdio.h>
#include <stdlib.h>


int main()
{
    ListaDrzavePozicija hashTable[HASH_SIZE];

    for (int i = 0; i < HASH_SIZE; i++)
    {
        hashTable[i] = (ListaDrzavePozicija)malloc(sizeof(ListaDrzavePozicija));
        hashTable[i]->imeDrzave = NULL;
        hashTable[i]->root = NULL;
        hashTable[i]->next = NULL;
    }


    ProcitajIzDatoteke(hashTable, "drzave.txt");

    for (int i = 0; i < HASH_SIZE; i++)
    {
        IspisListe(hashTable[i]);
    }

    TraziGrad(hashTable);

    ObrisiMemoriju(hashTable);

    return 0;
}