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
	_student* osoba = NULL;
	int count = 0;

	printf("Insert filename > ");
	scanf(" %s", filename);

	count = countStudentsFromFile(filename);


	if (count > 0) {
		printf("Broj studenata u datoteci %s je %d", filename, count);
		osoba = malloc(count * sizeof(_student));

		if (!osoba) {
			perror("Memory allocation failed for students!");
			return EXIT_FAILURE;
		}

		podaciStudenta(filename, osoba, count);
	}

	return 0;
}

int countStudentsFromFile(char* filename)
{
	FILE* fp = NULL;
	int count = 0;
	char ime[MAX_NAME] = { 0 };
	char prezime[MAX_NAME] = { 0 };
	int bodovi = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Dear customer, the file %s didn't open!\r\n", filename);
		return FILE_DIDNT_OPEN_ERROR;
	}

	while (!feof(fp))
	{ // while not found end of file (EOF)
		int result = fscanf(fp, " %s %s %d", ime, prezime, &bodovi);
		if (result == 3) {
			count++;
		}
	}

	fclose(fp);
	return count;
}

int podaciStudenta(char* filename, _student* osoba, int count)
{
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };
	int i = 0;

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Dear customer, the file %s didn't open!\r\n", filename);
		return EXIT_FAILURE;
	}


	while (!feof(fp))
	{ // while not found end of file (EOF)
		fscanf(fp, " %s %s %d", osoba[i].ime, osoba[i].prezime, &osoba[i].bodovi);
		osoba[i].relativan_br_bodova = (((float)osoba[i].bodovi) / MAX_BOD) * 100;
		i++;
	}

	fclose(fp);

	for (int j = 0; j < count; j++)
	{
		printf("\n%s %s %d %d", osoba[j].ime, osoba[j].prezime, osoba[j].bodovi, osoba[j].relativan_br_bodova);
	}
}
