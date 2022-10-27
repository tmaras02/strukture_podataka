#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME (1024)

struct _osoba;
typedef struct _osoba* Pozicija;
typedef struct _osoba
{
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int g_rod;
	Pozicija next;
} osoba;

int unosP(Pozicija p);
int ispis(Pozicija p);
int unosK(Pozicija p);
int traziPrez(Pozicija p);
int brisi(Pozicija p);

int main()
{
	osoba Head;
	Head.next = NULL;
	char izbor;

	while (1) {
		printf("Unesite: P -> unos na pocetak, I -> ispis, K -> unos na kraj, T -> trazi po prezimenu, B -> brisi, X -> izlaz \n\n");
		printf("Unos: ");
		scanf(" %c", &izbor);

		if (izbor == 'P' || izbor == 'p')
			unosP(&Head);
		else if (izbor == 'I' || izbor == 'i')
			ispis(Head.next);
		else if (izbor == 'K' || izbor == 'k')
			unosK(&Head);
		else if (izbor == 'T' || izbor == 't')
			traziPrez(Head.next);
		else if (izbor == 'B' || izbor == 'b')
			brisi(&Head);
		else if (izbor == 'X' || izbor == 'x')
			break;
		else
			printf("\nNeispravan unos, pokusajte ponovo!\n\n");
	}
	
	return 0;
}

int unosP(Pozicija p)
{
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(osoba));

	if (q == NULL)
	{
		printf("\nNeuspjesna alokacija memorije!\n");
		return ERROR;
	}

	printf("\nUnesite ime osobe: ");
	scanf(" %s", q -> ime);
	printf("\nUnesite prezime osobe: ");
	scanf(" %s", q -> prezime);
	printf("\nUnesite godinu rodenja osobe: ");
	scanf("%d", &q -> g_rod);
	printf("\n");

	q -> next = p-> next;
	p -> next = q;

	return 0;
}

int ispis(Pozicija p)
{
	while (p != NULL)
	{
		printf("\n%s %s %d \n\n", p -> ime, p -> prezime, p -> g_rod);
		p = p -> next;
	}

	return 0;
}

int unosK(Pozicija p)
{
	while ( p-> next != NULL)
	{
		p = p -> next;
	}

	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(osoba));

	if (q == NULL)
	{
		printf("\nNeuspjesna alokacija memorije!\n\n");
		return ERROR;
	}

	printf("\nUnesite ime osobe: ");
	scanf(" %s", q -> ime);
	printf("\nUnesite prezime osobe: ");
	scanf(" %s", q -> prezime);
	printf("\nUnesite godinu rodenja osobe: ");
	scanf("%d", &q -> g_rod);
	printf("\n");

	q -> next = p -> next;
	p -> next = q;

	return 0;
}

int traziPrez(Pozicija p)
{
	char prez[MAX_NAME];

	printf("\nUnesite prezime osobe koju zelite pronaci: ");
	scanf("%s", &prez);

	while (p != NULL && strcmp(prez, p -> prezime) != 0)
	{
		p = p -> next;
	}
	if (p == NULL)
		printf("\nOsoba s prezimenom koje ste unijeli ne postoji!\n\n");
	else
		printf("\nAdresa trazene osobe je: %p\n\n", p);

	return 0;
}

int brisi(Pozicija p)
{
	Pozicija pret = NULL;
	char prez[MAX_NAME];

	printf("\nUnesite prezime osobe koju zelite izbrisati: ");
	scanf("%s", &prez);
	printf("\n");

	while (p -> next != NULL && strcmp(prez, p -> prezime) != 0)
	{
		pret = p;
		p = p->next;
	}

	if (pret != NULL && strcmp(prez, p -> prezime) == 0)
	{
		p = pret -> next;
		pret -> next = p -> next;
	}

	return 0;
}
