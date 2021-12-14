#include "funkcije.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int md(stablo current) {
	stablo dir;
	dir = (stablo)malloc(sizeof(stablo));
	dir->ime = (char*)malloc(MAX * sizeof(char));


	if (!dir)
		printf("Ne mogu alocirati memoriju!");

	if (current->child != NULL) {
		current = current->child;
		while (current->sibling != NULL)
			current = current->sibling;
		current->sibling = dir;
	}
	else
		current->child = dir;

	scanf(" %s", dir->ime);

	dir->child = NULL;
	dir->sibling = NULL;

	return 0;
}

int direktorij(stablo current)
{
	if (current->child == NULL)
	{
		printf("Direktorij je prazan!\n");
		return 0;
	}

	current = current->child;

	printf("Direktoriji: \n");
	printf("		%s\n", current->ime);

	while (current->sibling != NULL)
	{
		printf("		 %s\n", current->sibling->ime);
		current = current->sibling;
	}

	return 0;
}

int putanja(stog head, stablo root, stablo current)
{
	stog pok = NULL;

	pok = PronadiZadnjeg(head);

	printf("\n");

	if (head->next == NULL)
	{
		printf("%s>", root->ime);
		return EXIT_SUCCESS;
	}

	while (pok->prev != NULL)
	{
		printf("%s>", pok->direktorij->ime);
		pok=pok->prev;
	}

	printf("%s>", current->ime);

	return 0;
}

stablo cd(stablo current, stog head)
{
	stablo datoteka=NULL;
	char* imeDir = NULL;
	imeDir = (char*)malloc(MAX * sizeof(char));

	scanf(" %s", imeDir);

	if (current->child == NULL)
	{
		printf("Direktorij ne postoji!\n");
		return current;
	}

	datoteka = naziv(current, imeDir);
	if (datoteka == 0)
	{
		printf("Ne mogu pronaci direktorij!\n");
		return current;
	}

	push(head, current);

	return datoteka;
}

stablo nazad(stablo current, stog head)
{
	stablo datoteka;

	datoteka = pop(head);

	if (datoteka == NULL)
	{
		printf("ERROR!\n");
		datoteka = current;
	}

	return datoteka;
}

stablo naziv(stablo current, char* Ime)
{
	if (current->child == NULL)
		printf("Direktorij je prazan!\n");

	current = current->child;


	while (strcmp(Ime, current->ime) != 0 && current->sibling != NULL) {
		current = current->sibling;
	}

	if (current->sibling == NULL) {
		if (strcmp(Ime, current->ime) != 0)
			return 0;
		else
			return current;
	}

	else
		return current;

}

int push(stog head, stablo dir)
{
	stog novi = (stog)malloc(sizeof(struct _stog));

	novi->next = head->next;
	novi->prev = head;
	if (head->next != NULL)
		head->next->prev = novi;
	head->next = novi;
	novi->direktorij = dir;

	return 0;
}

stablo pop(stog head) {

	stog pok = (stog)malloc(sizeof(stog));
	
	stablo pok1 = NULL;

	if (head->next == NULL)
		return 0;

	pok = head->next;
	pok1 = pok->direktorij;
	head->next = head->next->next;

	if (head->next != NULL)
		head->next->prev = head;
	free(pok);

	return pok1;
}

stog PronadiZadnjeg(stog head)
{
	stog pok;

	pok = head->next;

	if (pok == NULL)
		return NULL;

	while (pok->next != NULL)
		pok=pok->next;

	return pok;
}

int Izbornik(stablo root, stog head)
{
	stablo current = root;
	char unos[MAX] = { 0 };
	
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("izbornik - Izbornik\n");
	printf("md <filename> - Dodaj novi direktorij\n");
	printf("cd <filename> - Otvori direktorij\n");
	printf("cd.. - Zatvoriti direktorij\n");
	printf("dir - Ispisi listu direktorija u trenutnome direktoriju\n");
	printf("exit - Izlaz\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

	while (1)
	{
		putanja(head, root, current);
		scanf(" %s", unos);


		if (!strcmp(unos, "md")) 
			md(current);

		else if (!strcmp(unos, "cd"))
			current = cd(current, head);

		else if (!strcmp(unos, "cd..")) 
			current = nazad(current, head);

		else if (!strcmp(unos, "dir"))
			direktorij(current);
		

		else if (!strcmp(unos, "exit")) 
			return 1;
		

		else if(!strcmp(unos,"izbornik"))
			return 0;
	
		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}

