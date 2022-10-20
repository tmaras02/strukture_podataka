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

int main()
{
	osoba os1;

	printf("u");
	return 0;
}
