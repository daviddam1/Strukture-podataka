#include"funkcije.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	stablo root;
	stog head;
	int brojac = 0;

	root = (stablo*)malloc(sizeof(struct _stablo));
	root->child = NULL;
	root->sibling = NULL;
	
	head = (stog*)malloc(sizeof(struct _stog));
	head->next = NULL;
	head->prev = NULL;

	
	root->ime = (char*)malloc(MAX * sizeof(char));
	root->ime = "C:";

	do {
		brojac = Izbornik(root, head);
	} while (!brojac);

	return 0;
}






