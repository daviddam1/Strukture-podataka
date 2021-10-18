#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE (128)
#define MAX_LINE (1024)
#define MAX_BODOVI (20)

typedef struct{
    char ime[MAX_SIZE];
    char prezime[MAX_SIZE];
    double bodovi;

}student;


int ProcitajBrojRedakaIzDatoteke(char *nazivDatoteke);
student* AlocirajMemorijuIProcitajStudente(int BrojStudenata,char *nazivDatoteke);
student NajveciBrojBodova(student *studenti,int BrojStudenata);

int main()
{
    char *studenti=NULL;
    int BrojStudenata=0;
    int brojac=0;
    student *stud=NULL;
    student s;

    BrojStudenata=ProcitajBrojRedakaIzDatoteke(studenti);
    stud=AlocirajMemorijuIProcitajStudente(BrojStudenata,studenti);
    s=NajveciBrojBodova(stud,BrojStudenata);
    
    

   printf("Ime i Prezime        Aps. br. bodova  Rel. br. bodova\n\n");

   for(brojac;brojac<BrojStudenata;brojac++)
   {
       printf("%s %s     %.2lf%%           %.2lf%%\n",stud[brojac].ime,stud[brojac].prezime,stud[brojac].bodovi/MAX_BODOVI*100,(stud[brojac].bodovi/s.bodovi)*100);
   }

    return 0;
}

int ProcitajBrojRedakaIzDatoteke(char *nazivDatoteke)
{
    int brojac=0;
    FILE *datoteka=NULL;
    char BUFFER[MAX_LINE]={0};
    datoteka=fopen("studenti.txt","r");

    while(!feof(datoteka))
    {
        fgets(BUFFER,MAX_LINE,datoteka);
        brojac++;
    }

    fclose(datoteka);

    return brojac;
}

student* AlocirajMemorijuIProcitajStudente(int BrojStudenata,char *nazivDatoteke)
{
    int brojac=0;
    FILE *datoteka=NULL;
    student* studenti=NULL;

    studenti=(student*)malloc(BrojStudenata*sizeof(student));
    datoteka=fopen("studenti.txt","r");
    if(!datoteka)
    {
        printf("Greska alociranja memorije!");
        free(studenti);
        return NULL;
    }
    while(!feof(datoteka))
    {
        fscanf(datoteka," %s %s %lf",studenti[brojac].ime,studenti[brojac].prezime,&studenti[brojac].bodovi);
        brojac++;
    }

    fclose(datoteka);
    
    return studenti;

}

student NajveciBrojBodova(student *studenti,int BrojStudenata)
{
    int brojac=0;
    student temp={0};

    temp=studenti[0];
    for(brojac=1;brojac<BrojStudenata;brojac++)
        if(temp.bodovi<studenti[brojac].bodovi)
            temp=studenti[brojac];

    return temp;

}
