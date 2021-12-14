#ifndef funkcije
#define funkcije


#define MAX (50)

typedef struct _stablo* stablo;
typedef struct _stablo {
	char *ime;
	stablo child;
	stablo sibling;

};

typedef struct _stog *stog;
struct _stog{
	stablo direktorij;
	
	stog next;
	stog prev;
};

int md(stablo);
int direktorij(stablo);
int putanja(stog, stablo, stablo);

stablo cd(stablo, stog);
stablo nazad(stablo, stog);
stablo naziv(stablo, char*);

int push(stog, stablo);
stablo pop(stog);

stog PronadiZadnjeg(stog);
int Izbornik(stablo,stog);

#endif 
