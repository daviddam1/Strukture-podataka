#include"funkcije.h"

int UmetniIza(ListaDrzavePozicija pozicija, ListaDrzavePozicija novaDrzava)
{
	novaDrzava->next = pozicija->next;
	pozicija->next = novaDrzava;

	return EXIT_SUCCESS;
}

int UmetniDrzavu(ListaDrzavePozicija  head, ListaDrzavePozicija novaDrzava)
{
	ListaDrzavePozicija pom = head;

	while (pom->next)
	{
		if (strcmp(novaDrzava->imeDrzave, pom->next->imeDrzave) < 0)
		{
			UmetniIza(pom, novaDrzava);
			return EXIT_SUCCESS;
		}
	}pom = pom->next;

	UmetniIza(pom, novaDrzava);

	return EXIT_SUCCESS;
}

ListaDrzavePozicija novaDrzava(char* imeDrzave)
{
	ListaDrzavePozicija nova = NULL;
	nova = (ListaDrzavePozicija)malloc(sizeof(Lista));
	if (!nova)
	{
		printf("Ne mogu alocirati memoriju!\n");
		return EXIT_FAILURE;
	}

	strcpy(nova->imeDrzave, imeDrzave);
	nova->root = NULL;
	nova->next = NULL;

	return nova;
}

StabloGradoviPozicija noviGrad(char* imeGrada, int stan)
{
	StabloGradoviPozicija novi = NULL;
	novi = (StabloGradoviPozicija)malloc(sizeof(Stablo));
	if (!novi)
	{
		printf("Ne mogu alocirati memoriju!\n");
		return EXIT_FAILURE;
	}

	strcpy(novi->imeGrada, imeGrada);
	novi->brojStanovnika = stan;
	novi->lijevo = NULL;
	novi->desno = NULL;

	return novi;

}

int usporediGrad(StabloGradoviPozicija prvi, StabloGradoviPozicija drugi)
{
	int rez = 0;

	rez = prvi->brojStanovnika - drugi->brojStanovnika;
	if (!rez)
	{
		rez = strcmp(prvi->imeGrada, drugi->imeGrada);
	}

	return rez;
}
int ProcitajIzDatoteke(ListaDrzavePozicija hash[HASH_SIZE],char *imeDatoteke)
{
	FILE* fp = NULL;
	ListaDrzavePozicija pomDrzava = NULL;

	char* buffer = NULL;
	char* pom = NULL;
	char* imeDrzave = NULL;
	char* gradImeDatoteke = NULL;

	int velicinaDatoteke = 0;
	int citaj = 0;
	int drzava = 0;
	int kljuc = 0;
	int limit = 0;

	imeDrzave = (char*)malloc(MAX_LINE);
	gradImeDatoteke=(char*)malloc(MAX_LINE);

	if (!imeDrzave || !gradImeDatoteke)
	{
		printf("Ne mogu alocirati memoriju\n");
		return EXIT_FAILURE;
	}

	fp = fopen(imeDatoteke, "r");

	if (!fp)
	{
		printf("Ne mogu otvoriti datoteku!\n");
		return EXIT_FAILURE;
	}

	fseek(fp, 0, SEEK_END);
	velicinaDatoteke = ftell(fp);
	rewind(fp);

	buffer = (char*)malloc(velicinaDatoteke + 1);

	if (!buffer)
	{
		printf("Ne mogu alocirati memoriju!\n");
		return EXIT_FAILURE;
	}

	fread(buffer, velicinaDatoteke, 1, fp);
	fclose(fp);

	pom = buffer;

	while (strlen(pom) > 0)
	{
		drzava = sscanf(pom, "%s %s %n", imeDrzave, gradImeDatoteke, &citaj);
		pom += citaj;

		if (drzava == 2)
		{
			pomDrzava = novaDrzava(imeDrzave);

			if (pomDrzava)
			{
				pomDrzava->root = StvoriStabloIzDatoteke(gradImeDatoteke);
				if (strlen(pomDrzava->imeDrzave) < limit)
					limit = strlen(pomDrzava->imeDrzave);

				for (int i = 0; i < limit; i++)
				{
					kljuc += (pomDrzava->imeDrzave)[i];
				}

				kljuc = kljuc % HASH_SIZE;
				UmetniDrzavu(hash[kljuc], pomDrzava);

				kljuc = 0;
				limit = 5;
			}
		}

	}

	return 0;
}

int IspisSilazno(StabloGradoviPozicija pozicija)
{
	if (pozicija == NULL)
		return EXIT_SUCCESS;
	IspisSilazno(pozicija->desno);
	printf("%s - Stanovnistvo %d\n", pozicija->imeGrada, pozicija->brojStanovnika);
	IspisSilazno(pozicija->lijevo);
	return EXIT_SUCCESS;

}

int IspisListe(ListaDrzavePozicija head)
{
	ListaDrzavePozicija pom = head->next;

	if (!pom)
	{
		return EXIT_SUCCESS;
	}

	while (pom)
	{
		printf("%s:\n", pom->imeDrzave);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		IspisSilazno(pom->root);
		printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
		printf("\n");
	}
}


int UmetniElement(StabloGradoviPozicija pozicija, StabloGradoviPozicija noviElement)
{
	int drzava = 0;
	int pom = 0;

	if (!pozicija)
	{
		printf("Stablo ne postoji!\n");
		return EXIT_SUCCESS;
	}

	pom = gradUsporedi(noviElement, pozicija);
	if (!pom)
	{
		free(noviElement);
		return EXIT_SUCCESS;
	}

	if (pom < 0)
	{
		if (!(pozicija->lijevo))
		{
			pozicija->lijevo = noviElement;
			return EXIT_SUCCESS;
		}
		drzava = UmetniElement(pozicija->lijevo, noviElement);
		return EXIT_SUCCESS;
	}

	else
	{
	
		if (!pozicija->desno)
		{
			pozicija->desno = noviElement;
			return EXIT_SUCCESS;
		}
		drzava = UmetniElement(pozicija->desno, noviElement);
		return EXIT_SUCCESS;

	}

	return EXIT_SUCCESS;
}

StabloGradoviPozicija StvoriStabloIzDatoteke(char* imeDatoteke)
{
	FILE* fp = NULL;
	StabloGradoviPozicija pomGrad = NULL;
	StabloGradoviPozicija root = NULL;
	
	char* buffer = NULL;
	char* pom = NULL;
	char* imeGrada = NULL;

	int velicinaDatoteke = 0;
	int citaj = 0;
	int pop = 0;
	int drzava = 0;

	imeGrada = (char*)malloc(MAX_LINE);

	fp = fopen(imeDatoteke, "r");

	if (!fp)
	{
		printf("Ne mogu otvoriti datoteku!");
		return EXIT_FAILURE;
	}

	fseek(fp, 0, SEEK_END);
	velicinaDatoteke = ftell(fp);
	rewind(fp);

	buffer=(char*)malloc(velicinaDatoteke + 1);
	if (!buffer)
	{
		printf("Ne mogu alocirati memoriju!\n");
		return EXIT_SUCCESS;
	}

	fread(buffer, velicinaDatoteke, 1, fp);
	fclose(fp);

	pom = buffer;

	while (strlen(pom) > 0)
	{
		drzava = sscanf(pom, "%s %d %n", imeGrada, &pop, &citaj);
		pom += citaj;

		if (drzava == 2)
		{
			pomGrad = noviGrad(imeDatoteke, pop);
			if (pomGrad)
			{
				if (!root)
					root = pomGrad;
				else
					UmetniElement(root, pomGrad);
			}
		}
	}

	return root;
}

int IspisiVeci(StabloGradoviPozicija pozicija, int limit)
{
	if (pozicija == NULL)
		return EXIT_SUCCESS;
	IspisiVeci(pozicija->lijevo, limit);
	if (pozicija->brojStanovnika)
		printf("%s - Stanovnistvo %d\n", pozicija->imeGrada, pozicija->brojStanovnika);
	IspisiVeci(pozicija->desno, limit);

	return EXIT_SUCCESS;
}

ListaDrzavePozicija pronadiDrzavu(ListaDrzavePozicija head, char* imeDrzave)
{
	ListaDrzavePozicija pom = head;
	while (pom)
	{
		if (pom->imeDrzave && !strcmp(pom->imeDrzave, imeDrzave))
			return pom;
		pom = pom->next;
	}
	return NULL;
}

int TraziGrad(StabloGradoviPozicija hash[HASH_SIZE])
{
	char* imeDrzave = NULL;
	ListaDrzavePozicija pronadi = NULL;
	int pop = 0;

	int kljuc = 0;
	int limit = 0;

	printf("Unesi drzavu: ");
	imeDrzave = (char*)malloc(MAX_LINE);
	
	fgets(imeDrzave, MAX_LINE, stdin);
	imeDrzave[strcspn(imeDrzave, "\n")] = 0;

	if (strlen(imeDrzave) < limit)
		limit = strlen(imeDrzave);

	for (int i = 0; i < limit; i++)
		kljuc += imeDrzave[i];

	kljuc = kljuc % HASH_SIZE;

	pronadi = pronadiDrzavu(hash[kljuc], imeDrzave);

	if (!pronadi)
	{
		printf("Ne mogu pronaci drzavu!\n");
	}

	printf("Unesi stanovistvo: ");
	scanf("%d", &pop);

	printf("\nGradovi u %s s populacijom preko %d", pronadi->imeDrzave, pop);
	IspisiVeci(pronadi->root, pop);

	return EXIT_SUCCESS;
		
}

int ObrisiVezanuListu(ListaDrzavePozicija head)
{
	ListaDrzavePozicija pom = NULL;

	while (head->next != NULL)
	{
		pom = head->next;
		pom->root = ObrisiStablo(pom->root);

		head->next = pom->next;

		free(pom);
	}

	return 0;
}

StabloGradoviPozicija ObrisiStablo(StabloGradoviPozicija root)
{
	if (root == NULL)
		return NULL;

	if (root->lijevo)
		root->lijevo = ObrisiStablo(root->lijevo);

	if (root->desno)
		root->desno = ObrisiStablo(root->desno);

	free(root);
}

int ObrisiMemoriju(ListaDrzavePozicija hashTablica[])
{
	int brojac = 0;
	for (brojac; brojac < 11; brojac++)
	{
		ObrisiVezanuListu(&hashTablica);
	}

	return EXIT_SUCCESS;
}