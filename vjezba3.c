#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXLINE 50

typedef struct element{
	char ime[MAXLINE];
	char prezime [MAXLINE];
	int godRod;

	struct element* next;
}student;


//2. VJEZBA
int Izbornik(student*);
int UnosPocetak(student*);
int IspisListe(student*);
int UnosKraj(student*);
int ObrisiStudenta(student*,student*);	

student* PronadjiPrethodni(student*, student*);
student* PronadjiZadnji(student *);
student* PronadjiPrezime(student*,char*);


//3. VJEZBA
int DodajElementIspred(student*,student*);
int DodajElementIza(student*,student*);
int SortirajListuPoPrezimenima(student*);
int UpisiListu(student*);
int	ProcitajListu(student*);


int main()
{
	student *head=(student*)malloc(sizeof(student));
	int brojac=0;
	head->next=NULL;

	do{
		brojac=Izbornik(head);
	}while(!brojac);
	
	return 0;
}

int UnosPocetak(student* head)
{
	student *s=NULL;
	s=(student*)malloc(sizeof(student));

	s->next=head->next;
	head->next=s;
	head=s;

	printf("Unesi ime: ");
	scanf("%s",s->ime);
	printf("Unesi prezime: ");
	scanf("%s",s->prezime);
	printf("Unesi godinu rodjenja: ");
	scanf("%d",&s->godRod);
	printf("\n");

	return 0;
	
}

int IspisListe(student* head)
{
	student* s = NULL;

	s= head->next;

	printf("		LISTA:\n");
		while (s != NULL)
		{
			printf("Ime: %s\n",s->ime);
			printf("Prezime: %s\n", s->prezime);
			printf("Godina rodjena: %d\n", s->godRod);
			printf("\n");

			s = s->next;
		}


	return 0;
}

int UnosKraj(student* head)
{
	student *s=NULL;
	s=(student*)malloc(sizeof(student));
	student *s1=NULL;
	s1=(student*)malloc(sizeof(student));


	s1=PronadjiZadnji(head);
	
	s->next=NULL;
	s1->next=s;;

	printf("Unesi ime: ");
	scanf("%s",s->ime);
	printf("Unesi prezime: ");
	scanf("%s",s->prezime);
	printf("Unesi godinu rodjenja: ");
	scanf("%d",&s->godRod);
	printf("\n");

	return 0;
}

int Izbornik(student* head)
{
	int odabir=0;

	char prezime[MAXLINE];
	student* nadjiPrezime=(student*)malloc(sizeof(student));
	
	
	char obrisi[MAXLINE];
	student* obrisiEl=(student*)malloc(sizeof(student));
	

	char ispred[MAXLINE];
	student *umetniIspred=(student*)malloc(sizeof(student));

	char iza[MAXLINE];
	student *umetniIza=(student*)malloc(sizeof(student));
	
	printf("		IZBORNIK		\n");
	printf("1- Unos od pocetka\n");
	printf("2- Unos na kraj\n");
	printf("3- Ispis liste\n");
	printf("4- Pronadji prezime\n");
	printf("5- Obrisi element\n");
	printf("6- Unesi element ispred\n");
	printf("7- Unesi element iza\n");
	printf("8- Sortiraj listu abecedno po prezimenima\n");
	printf("9- Upisi u datoteku\n");
	printf("10- Procitaj iz datoteka\n");
	printf("11- Unesi ponovno\n");
	printf("0- Izlaz iz izbornika\n");
	printf("\n");

	while(1)
	{
		printf("Unesite odabir u izbornik: ");
		scanf("%d",&odabir);
		switch(odabir)
		{
			case(1):UnosPocetak(head);
				break;
			case(2):UnosKraj(head);
				break;
			case(3):IspisListe(head);
				break;
			case(4):printf("\nUnesite prezime koje zelite pronaci: ");
				scanf("%s",prezime);
				nadjiPrezime=PronadjiPrezime(head,prezime);
				printf("Ime: %s\nPrezime: %s\nGodina rodjenja: %d\n",nadjiPrezime->ime,nadjiPrezime->prezime,nadjiPrezime->godRod);
				break;
			case(5):printf("\nKoji element zelite obrisati (unesite prezime): ");
				scanf("%s",obrisi);
				obrisiEl=PronadjiPrezime(head,obrisi);
				ObrisiStudenta(head,obrisiEl);
				printf("Uspjesno ste izbrisali studenta!");
				break;
			case(6):printf("\nUnesi ispred elementa (unesi prezime ispred elementa kojeg zelis upisati):");
				scanf("%s",ispred);
				umetniIspred=PronadjiPrezime(head,ispred);
				DodajElementIspred(head,umetniIspred);
				break;
			case(7):printf("\nUnesi iza elementa (unesi prezime iza elementa kojeg zelis upisati):");
				scanf("%s",iza);
				umetniIza=PronadjiPrezime(head,iza);
				DodajElementIza(head,umetniIza);
				break;
			case(8):SortirajListuPoPrezimenima(head);
				break;
			case(9):UpisiListu(head);
				break;
			case(10):ProcitajListu(head);
				break;
			case(11):
				return 1;
			case(0):
				return -1;
		}
	}
	
	return 0;
}

student *PronadjiPrethodni(student* head, student* element)
{
	student* stud=head;

	while(stud!=NULL&&stud->next!=element)
	{
		stud=stud->next;
	}

	return stud;

}

student* PronadjiZadnji(student *head)
{
	student *stud=NULL;
	stud=head;
	
	while(stud!=NULL&&stud->next!=NULL)
	{
		stud=stud->next;
	}

	return stud;
}

student* PronadjiPrezime(student* head,char* prezime)
{
	student* stud=NULL;
	stud=head;

	while(stud!=NULL&&strcmp(stud->prezime,prezime))
	{
		stud=stud->next;
	}

	return stud;
}

int ObrisiStudenta(student* head,student* element)
{
	student *stud1=NULL;
	stud1=(student*)malloc(sizeof(student));
	student *stud2=NULL;
	stud2=(student*)malloc(sizeof(student));

	stud2=element;
	stud1=PronadjiPrethodni(head,element);
	stud1->next=stud2->next;

	free(stud2);

	return 0;
		
}

int DodajElementIspred(student* head,student* element)
{
	student *stud=NULL;
	stud=(student*)malloc(sizeof(student));
	student *pozicija=NULL;
	pozicija=(student*)malloc(sizeof(student));

	pozicija=PronadjiPrethodni(head,element);

	pozicija->next=stud;
	stud->next=element;
	
	printf("Unesi ime: ");
	scanf("%s",stud->ime);
	printf("Unesi prezime: ");
	scanf("%s",stud->prezime);
	printf("Unesi godinu rodjenja: ");
	scanf("%d",&stud->godRod);
	printf("\n");

	return 0;

}
int DodajElementIza(student* head,student* element)
{
	student *stud=NULL;
	stud=(student*)malloc(sizeof(student));

	printf("Unesi ime: ");
	scanf("%s",stud->ime);
	printf("Unesi prezime: ");
	scanf("%s",stud->prezime);
	printf("Unesi godinu rodjenja: ");
	scanf("%d",&stud->godRod);
	printf("\n");

	stud->next=element->next;
	element->next=stud;

	return 0;
}

int SortirajListuPoPrezimenima(student* head)
{
	student * stud = head;
	student * stud1 = NULL;
	student * pretStud = NULL;
	student * zadnji = NULL;

	while (stud->next != zadnji)
	{
		pretStud = stud;
		stud1 = pretStud->next;

		while (stud1->next != zadnji)
		{
			if (strcmp(stud1->prezime, stud1->next->prezime) > 0)
			{
				pretStud->next = stud1->next;
				stud1->next = stud1->next->next;
				pretStud->next->next = stud1;
				stud1 = pretStud->next;
			}
			pretStud = stud1;
			stud1 = stud1->next;
		}
		zadnji = stud1;
	}

	return 0;
}
int UpisiListu(student* head)
{
	student* stud = NULL;
	stud = (student*)malloc(sizeof(student));
	stud = head->next;

	FILE* fp = NULL;
	fp = fopen("studenti.txt", "w");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}
	
	while (stud != NULL) {
		fprintf(fp,"Ime: %s\n",stud->ime);
		fprintf(fp,"Prezime: %s\n",stud->prezime);
		fprintf(fp,"Godina rodjenja: %d\n",stud->godRod);
		printf("\n");
		
		stud = stud->next;
	}

	fclose(fp);

	return 0;
}

int	ProcitajListu(student* head)
{
	student *stud=NULL;
	student *stud1=NULL;
	int i=0,brojac=0;
	char BUFFER[MAXLINE]={0};

	stud1=PronadjiZadnji(head);

	FILE *fp=fopen("lista.txt","r");
	if(fp==NULL)
	{
		printf("ERROR!");
		return -1;
	}

	while(fgets(BUFFER,MAXLINE,fp))
		brojac++;

	rewind(fp);

	for(i=0;i<brojac;i++)
	{
		stud=(student*)malloc(sizeof(student));

		stud->next=NULL;
		stud1->next=stud;
		stud1=stud1->next;

		fscanf(fp,"%s %s %d",stud1->ime,stud1->prezime,&stud1->godRod);
	}

	fclose(fp);

	return 0;
}
