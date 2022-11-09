#define _CRT_SECURE_NO_WARNINGS

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_LINE 1024
#define ERROR (-1)

struct _polinom;
typedef struct _polinom *position;
typedef struct _polinom {
	int coef;
	int exp;
	position next;
}polinom;

int input(char[MAX_LINE],position,position);
int sort(position,position);
int print(position);
int add(position, position, position);
int check(position);

int main() {
	polinom Head;
	polinom Head2;
	polinom Headadd;
	polinom Headmul;

	Headadd.next = NULL;
	Head.next = NULL;
	Head2.next = NULL;
	Headmul.next = NULL;

	char filename[MAX_LINE];

	printf("Upisite ime datoteke: ");
	scanf("%s", filename);
	printf("\n");

	input(filename,&Head,&Head2);
	print(&Head);
	print(&Head2);
	add(&Head, &Head2, &Headadd);
	multiply(&Head, &Head2, &Headmul);
	print(&Headadd);
	print(&Headmul);

	return 0;
}

int input(char filename[MAX_LINE],position pos,position pos2) {
	position q = NULL;
	q = (position)malloc(sizeof(polinom));
	if (q == NULL)
	{
		printf("\nNeuspjesna alokacija memorije!\n");
		return ERROR;
	}

	FILE* fp = NULL;
	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Dear customer, the file %s didn't open!\r\n", filename);
		return ERROR;
	}

	char buffer[MAX_LINE];
	char* p = buffer;
	int n = 0;
	int e = 0;
	int c = 0;

	fgets(buffer, MAX_LINE, fp);

	while (strlen(p) > 0) {
		sscanf(p, "%d %d %n", &c, &e, &n);
		p += n;
		q->coef = c;
		q->exp = e;
		sort(pos,q);
		q = (position)malloc(sizeof(polinom));
		if (q == NULL)
		{
			printf("\nNeuspjesna alokacija memorije!\n");
			return ERROR;
		}
	}

	fgets(buffer, MAX_LINE, fp);
	p = buffer;

	while (strlen(p) > 0) {
		sscanf(p, "%d %d %n", &c, &e, &n);
		p += n;
		q->coef = c;
		q->exp = e;
		sort(pos2, q);
		q = (position)malloc(sizeof(polinom));
		if (q == NULL)
		{
			printf("\nNeuspjesna alokacija memorije!\n");
			return ERROR;
		}
	}

	return 0;
}

int sort(position pos, position q) {
	while (pos->next!=NULL && pos->next->exp<q->exp) {
		pos = pos->next;
	}
	q->next = pos->next;
	pos->next = q;

	return 0;
}

int print(position pos) {
	pos = pos->next;

	while (pos!= NULL) {
		if (pos->coef != 0) {
			printf("%dx^%d  ", pos->coef, pos->exp);
			pos = pos->next;
		}
		else
			pos = pos->next;
	}

	printf("\n\n");

	return 0;
}

int add(position p1, position p2, position rez){
	position q;

	p1 = p1->next;
	p2 = p2->next;

	while (p1!= NULL && p2!= NULL) {
		q = (position)malloc(sizeof(polinom));
		if (q == NULL)
		{
			printf("\nNeuspjesna alokacija memorije!\n");
			return ERROR;
		}

		if (p1->exp > p2->exp) {
			q->coef = p2->coef;
			q->exp = p2->exp;
			sort(rez, q);
			p2 = p2->next;
		}
		else if (p1->exp < p2->exp) {
			q->coef = p1->coef;
			q->exp = p1->exp;
			sort(rez, q);
			p1 = p1->next;
		}
		else {
			q->coef = p1->coef + p2->coef;
			q->exp = p1->exp;
			sort(rez, q);
			p1 = p1->next;
			p2 = p2->next;
		}
	}

	if (p1 == NULL) {
		while (p2 != NULL) {
			q = (position)malloc(sizeof(polinom));
			if (q == NULL)
			{
				printf("\nNeuspjesna alokacija memorije!\n");
				return ERROR;
			}
			q->coef = p2->coef;
			q->exp = p2->exp;
			sort(rez, q);
			p2 = p2->next;
		}
	}

	if (p2 == NULL) {
		while (p1!= NULL) {
			q = (position)malloc(sizeof(polinom));
			if (q == NULL)
			{
				printf("\nNeuspjesna alokacija memorije!\n");
				return ERROR;
			}
			q->coef = p1->coef;
			q->exp = p1->exp;
			sort(rez, q);
			p1 = p1->next;
		}
	}

	check(rez);

	return 0;
}

int check(position p) {
	p = p->next;

	position q;
	q = (position)malloc(sizeof(polinom));
	if (q == NULL)
	{
		printf("\nNeuspjesna alokacija memorije!\n");
		return ERROR;
	}
	q = p->next;

	while (q != NULL) {
		if (p->exp == q->exp) {
			p->coef = p->coef + q->coef;
			p->next = q->next;
			free(q);
			q = p->next;
		}
		p = p->next;
		q = q->next;
	}

	return 0;
}

int multiply(position p1, position p2, position rez) {
	position reset;

	p1 = p1->next;
	p2 = p2->next;
	reset = p2;
	
	position q;

	while (p1 != NULL) {
		while (p2 != NULL) {
			q = (position)malloc(sizeof(polinom));
			if (q == NULL)
			{
				printf("\nNeuspjesna alokacija memorije!\n");
				return ERROR;
			}
			q->coef = p1->coef * p2->coef;
			q->exp = p1->exp + p2->exp;
			sort(rez, q);
			p2 = p2->next;
		}
		p2 = reset;
		p1 = p1->next;
	}

	check(rez);

	return 0;
}
