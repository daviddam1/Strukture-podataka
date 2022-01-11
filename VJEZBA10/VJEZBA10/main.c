#include"funkcije.h"

int main()
{
	Lista headElement = {
		.imeDrzave = NULL,
		.root = NULL,
		.next = NULL
	};

	ListaDrzavePozicija head = &headElement;

	char odabranaDrzava[MAX_LENGTH] = { NULL };
	int odabranoStan = 0;
	int status = 0;
	ListaDrzavePozicija TrazenaDrzava = NULL;

	UcitajDrzavu(head);
	IspisiSveElementeListe(head->next);

	printf("Unesi drzavu i stanovnistvo: ");
	scanf(" %s %d", odabranaDrzava, &odabranoStan);

	TrazenaDrzava = PronadiDrzavu(head, odabranaDrzava);

	if (TrazenaDrzava && TrazenaDrzava->root)
		PronadiGradove(TrazenaDrzava->root, odabranoStan);
	

	return 0;
}