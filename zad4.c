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
int input(char[MAX_LINE],position);
int sort(position);
int print(position);
int main() {
	polinom Head;
	Head.next = NULL;
	char filename[MAX_LINE];
	printf("Upisite ime datoteke\n");
	scanf("%s", filename);
	input(filename,&Head);
	print(&Head);
	return 0;
}
int input(char filename[MAX_LINE],position pos) {
	position q = NULL;
	q = (position)malloc(sizeof(polinom));
	FILE* fp = NULL;
	fp = fopen(filename, "r");
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
	while (pos->next != NULL) {
		printf("%dx ^%d \n", pos->coef, pos->exp);
		pos = pos->next;
	}
	return 0;
}
