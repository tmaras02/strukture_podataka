#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX_NAME (150)
#define MAX_BOD (50)

typedef struct
{
	char ime[MAX_NAME];
	char prezime[MAX_NAME];
	int bodovi;
	int relativan_br_bodova;
}_student;

int countStudentsFromFile(char* filename);
void podaciStudenta(char* filename, _student*);

int main(void)
{
	char filename[MAX_FILE_NAME] = { 0 };

	printf("Insert filename > ");
	scanf(" %s", filename);

	printf("Broj studenata u datoteci %s je %d", filename, countStudentsFromFile(filename));

	_student* osoba;
	osoba = malloc(countStudentsFromFile(filename) * sizeof(_student));

	podaciStudenta(filename, osoba);

	return 0;
}

int countStudentsFromFile(char* filename)
{
	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Dear customer, the file %s didn't open!\r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{ // while not found end of file (EOF)
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0)
		{
			count++;
		}
	}

	fclose(fp);
	return count;
}

void podaciStudenta(char* filename, _student* osoba)
{
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Dear customer, the file %s didn't open!\r\n", filename);
	}

	int i = 0;

	while (!feof(fp))
	{ // while not found end of file (EOF)
		fscanf(fp, "%s %s %d", osoba[i].ime, osoba[i].prezime, &osoba[i].bodovi);
		osoba[i].relativan_br_bodova = (((float)osoba[i].bodovi) / MAX_BOD) * 100;
		i++;
	}

	fclose(fp);

	for (int j = 0; j < countStudentsFromFile(filename); j++)
	{
		printf("\n%s %s %d %d", osoba[j].ime, osoba[j].prezime, osoba[j].bodovi, osoba[j].relativan_br_bodova);
	}
}