#include "deklaracije.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int IzracunajPostfix(char* imeDatoteke, double* rezultat)
{
	char* buffer = NULL;
	int status = 0;

	buffer = ProcitajDatoteku(imeDatoteke);
	if (buffer == NULL)
		return EXIT_FAILURE;

	status = ParseStringIntoPostfix(buffer, rezultat);
	if (status != EXIT_SUCCESS)
		return EXIT_FAILURE;

	return EXIT_SUCCESS;

}

char* ProcitajDatoteku(char* imeDatoteke)
{
	FILE* datoteka = NULL;
	int duljinaDatoteke = 0;
	char* buffer = NULL;

	datoteka = fopen(imeDatoteke, "rb");
	if (!datoteka)
	{
		perror("Ne mogu otvoriti datoteku!\n");
		return -1;
	}

	fseek(datoteka, 0, SEEK_END);
	duljinaDatoteke = ftell(datoteka);

	buffer = (char*)calloc(duljinaDatoteke + 1, sizeof(char));
	if (!buffer)
	{
		perror("Ne mogu alocirati memoriju!\n");
		return -1;
	}

	rewind(datoteka);
	fread(buffer, sizeof(char), duljinaDatoteke, datoteka);
	printf("|%s|\n", buffer);
	fclose(datoteka);

	return buffer;
}

int ParseStringIntoPostfix(char* buffer, double* rezultat)
{
	ElementStoga head = { .broj = 0, .next = NULL };
	char* currentBuffer = buffer;
	int status = 0;
	int numBytes = 0;
	char operacija = 0;
	double broj = 0.0;
	pozicija noviElementStoga = NULL;

	while (strlen(currentBuffer) > 0)
	{
		status = sscanf(currentBuffer, " %lf %n", &broj, &numBytes);
		if (status != 1)
		{
			sscanf(currentBuffer, " %c %n", &operacija, &numBytes);
			status = IzvediOperaciju(&head,operacija, rezultat);

			if (status != EXIT_SUCCESS) {
				return EXIT_FAILURE;
			}

			broj = *rezultat;
		}

		noviElementStoga = StvoriElementStoga(broj);
		if (!noviElementStoga)
		{
			return EXIT_FAILURE;
		}

		currentBuffer += numBytes;
		printf("|%s| = ", currentBuffer);

		UmetniIza(&head, noviElementStoga);
	}
	printf("Stog je prazan!\n");

	return RezultatStoga(&head, rezultat);
}

int RezultatStoga(pozicija head, double* rezultat)
{
	int status = EXIT_SUCCESS;

	status = Pop(head, rezultat);
	if (status != EXIT_SUCCESS)
		return status;

	if (head->next)
	{
		system("cls");
		printf("Postfix nije u redu!\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

pozicija StvoriElementStoga(double broj)
{
	pozicija noviElement = NULL;

	noviElement = (pozicija)malloc(sizeof(ElementStoga));

	if (!noviElement)
	{
		perror("Ne mogu alocirati memoriju!\n");
		return NULL;
	}

	noviElement->broj = broj;
	noviElement->next = NULL;

	return noviElement;

}

int UmetniIza(pozicija head, pozicija noviElement)
{
	noviElement->next = head->next;
	head->next = noviElement;

	IspisStoga((*head).next);

	return EXIT_SUCCESS;
}

int IspisStoga(pozicija head)
{
	pozicija pom = head;
	while (pom)
	{
		printf(" %0.1lf", pom->broj);
		pom = pom->next;
	}
	printf("\n");

	return EXIT_SUCCESS;

}

int Pop(pozicija head, double* rezultat)
{
	pozicija element = NULL;

	element = head->next;
	if (!element)
	{
		perror("Stog je prazan!\n");
		return -1;
	}

	head->next = element->next;
	*rezultat = element->broj;

	free(element);

	return EXIT_SUCCESS;
}

int IzvediOperaciju(pozicija head, char operacija, double* rezultat)
{
	double operand1 = 0, operand2 = 0;
	int status1 = 0, status2 = 0;

	status1 = Pop(head, &operand1);
	if (status1 != EXIT_SUCCESS)
		return EXIT_FAILURE;

	status2 = Pop(head, &operand2);
	if (status2!= EXIT_SUCCESS)
		return EXIT_FAILURE;

	switch (operacija) {
	case'+':
		*rezultat = operand2 + operand1;
		break;
	case'-':
		*rezultat = operand2 - operand1;
		break;
	case'*':
		*rezultat = operand2 * operand1;
		break;
	case'/':
		if (operand1 == 0)
		{
			perror("Ne mogu dijeliti s nulom!\n");
			return -1;
		}
		*rezultat = operand2 /operand1;
		break;

	}

	return EXIT_SUCCESS;
}