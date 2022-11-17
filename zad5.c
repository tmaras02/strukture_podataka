#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define ERROR -1
#define MAX 1024

struct _stack;
typedef struct _stack* position;
typedef struct _stack {
    float number;
    position next;
}stack;

position top = NULL;

int readFromFile(char* filename, char* line);
int push(float number);
float pop();
int printStack();
int readFromBuffer(char* line);
int operations(char operand);
int Delete();

int main(void)
{
    char filename[MAX] = { 0 };
    char line[MAX] = { 0 };
    float result = 0;

    printf("Enter the file name: ");
    scanf(" %s", filename);
    printf("\n");

    readFromFile(filename, line);

    printf("Postfix from file: %s\n", line);

    result = top->next->number;
    printf("\nResult: %.2f\n", result);
    
    return 0;
}

int readFromFile(char* filename, char* line)
{
    char buffer[MAX] = { 0 };
    FILE* fp = NULL;
    fp = fopen(filename, "r");


    if (fp == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", filename);
        return ERROR;
    }

    while (!feof(fp)) {
        fgets(buffer, MAX, fp);
        readFromBuffer(buffer);
    }

    strcpy(line, buffer);

    fclose(fp);

    return 0;
}

int push(float number)
{
    position new = NULL;
    new = (position)malloc(sizeof(stack));

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return ERROR;
    }

    new->number = number;

    new->next = top;
    top = new;
    
    return 0;
}

int printStack() {
    position temp = top;

    if (temp == NULL) {
        printf("Stack is empty");
        return ERROR;
    }

    while (temp != NULL) {
        printf("%.2f\n", temp->number);

        temp = temp->next;
    }
    return 0;
}

float pop() {
    position temp;
    float number = 0;
    if (top == NULL) {
        printf("Stack is empty!");
        return ERROR;
    }

    number = top->number;
    temp = top;
    top = top->next;
    free(temp);

    return number;
}

int readFromBuffer(char* line) {

    float number = 0;
    char operand = 0;
    int n = 0;
    int r = 0;


    while (strlen(line) > 0)
    {
        r = sscanf(line, " %f %n", &number, &n);

        if (r == 1)
        {
            push(number);
            line += n;

        }
        else
        {
            sscanf(line, " %c %n", &operand, &n);
            operations(operand);
            line += n;
        }
    }
    return 0;
}



int operations(char operand) {
    float number1 = 0;
    float number2 = 0;
    float r = 0;

    number1 = pop();
    number2 = pop();

    switch (operand) {
    case '+':
        r = number2 + number1;
        push(r);
        break;
    case '-':
        r = number2 - number1;
        push(r);
        break;
    case '*':
        r = number1 * number2;
        push(r);
        break;
    case '/':
        if (number1 == 0)
        {
            printf("Dividing by zero isn't possible!\n");
            return ERROR;
        }
        else
        {
            r = number2 / number1;
            push(r);
        }
        break;
    default:
        printf("Wrong postfix expression!");
        return ERROR;
    }
    return 0;
}

int Delete() {
    position head = top->next;
    position temp;

    while (head != NULL) {
        temp = head->next;
        free(head);
        head = temp;
    }
    return 0;
}
