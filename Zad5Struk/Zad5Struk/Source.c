#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 1024
#define ERROR -4597

struct _member;
typedef struct _member* position;
typedef struct _member {
	int number;
	position next;
}member;

int fileinput(char[MAX_LINE]);
int printPostfix();
int pop(float*);
int push(float*);
int check();
int Delete();
position top = NULL;

int main() {
	float result;
	char filename[MAX_LINE];
	printf("Upisite ime datoteke iz koje zelite citati: ");
	scanf("%s", filename);

	printPostfix(filename);

	result = fileinput(filename);
	if (result != ERROR) {
		printf("\nRezultat je %.2f", result);
	}
	else {
		printf("Neispravno postavljena jednadzba u datoteci");
	}
	return 0;
}

int fileinput(char filename[MAX_LINE]) {
	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("Nije pronadena datoteka koju ste trazili\n");
		return ERROR;
	}
	int n;
	int l;
	float temp1 = 0;
	float temp2 = 0;
	float* tmp1 = &temp1;
	float* tmp2 = &temp2;
	char ctemp[MAX_LINE];
	char oper[MAX_LINE];
	float rez;
	float* tempres;
	tempres = &rez;
	char* p = &ctemp;
	char line[MAX_LINE];
	fgets(ctemp, MAX_LINE, fp);
	while (strlen(p) > 0) {
		l = sscanf(p, "%f %n", &temp1, &n);
		if (l == 1) {
			push(tmp1);
		}
		else {
			sscanf(line, "%s %n", &oper, &n);
			if (!strcmp(oper, "+")) {
				pop(tmp1);
				pop(tmp2);
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				rez = temp2 + temp1;
				push(tempres);
			}
			else if (!strcmp(oper, "-")) {
				pop(tmp1);
				pop(tmp2);
				rez = temp2 - temp1;
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				push(tempres);
			}
			else if (!strcmp(oper, "*")) {
				pop(tmp1);
				pop(tmp2);
				rez = temp2 * temp1;
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				push(tempres);
			}
			else if (!strcmp(oper, "/")) {
				pop(tmp1);
				if (temp1 == 0) {
					printf("Dijeljenje sa 0 nije moguce\n");
					return ERROR;
				}
				pop(tmp2);
				if (temp1 == ERROR || temp2 == ERROR) return ERROR;
				rez = temp2 / temp1;
				push(tempres);
			}
			else {
				printf("Nepoznata operacija u datoteci\n");
			}

		}
		p += n;
		strcpy(line, p);
	}
	pop(tmp1);
	if (check() == 0) {
		return ERROR;
	}

	return *tmp1;
}

int printPostfix(char filename[MAX_LINE])
{
	printf("\nPostfiks iz datoteke: ");

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	char line[MAX_LINE];

	while (!feof(fp))
	{
		fgets(line, MAX_LINE, fp);
		puts(line);
	}

	fclose(fp);
}

int push(float* temp) {
	position q;
	q = (position)malloc(sizeof(member));
	if (q == NULL) {
		printf("Neuspjeno alocirana memorija\n");
		return ERROR;
	}
	q->number = *temp;
	q->next = top;
	top = q;
	return 0;
}

int pop(float* temp) {
	position q;
	if (top == NULL) {
		printf("Lista je prazna\n");
		*temp = ERROR;
		return ERROR;
	}
	*temp = top->number;
	q = top;
	top = top->next;
	free(q);
	return 0;
}

int check() {
	int i = 0;
	while (top != NULL) {
		top = top->next;
		i++;
	}
	if (i == 0) {
		return 1;
	}
	else {
		return 0;
	}
}
