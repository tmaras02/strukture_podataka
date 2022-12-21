#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define ERROR -1

struct _stablo;
typedef struct _stablo* Position;
typedef struct _stablo {
	int num;
	Position left;
	Position right;
}stablo;

int inorder(Position current);
int postorder(Position current);
int preorder(Position current);
int levelOrder(Position current);
int Height(Position current);
int currentLevel(Position current, int lvl);
Position insert(Position current, Position q);
Position createElement(int number);
void find_op(Position current);
Position find(Position current, int trazi);
Position delete(Position current, int brisi);
Position findMax(Position current);
Position findMin(Position current);

int main()
{
	Position root = NULL;
	Position q;

	root = insert(4, root);
	insert(1, root);
	insert(12, root);
	insert(10, root);
	insert(3, root);
	insert(14, root);
	insert(2, root);

	int brisi = 0;
	int choice = 0;
	int broj = 0;


	do {

		printf("\nOdaberi: \n 0-Insert element\n 1-Print postorder\n 2-Print inorder\n 3-Print preorder\n 4-Print level order\n 5-Find\n 6-Delete\n 7-Exit\n\n ");
		scanf("%d", &choice);
		switch (choice) {
		case 0:
			printf("\n Unesi broj koji zelis upisati: ");
			scanf("%d", &broj);
			root = insert(broj, root);
			break;

		case 1:
			printf("\n Ispis postorder: ");
			postorder(root);
			printf("\n");
			break;
		case 2:
			printf("\n Ispis inorder: ");
			inorder(root);
			printf("\n");
			break;

		case 3:
			printf("\n Ispis preorder: ");
			preorder(root);
			printf("\n");
			break;

		case 4:
			printf("\n Ispis level order: ");
			levelOrder(root);
			printf("\n");
			break;

		case 5:
			find_op(root);
			break;

		case 6:
			printf("\n Unesi broj koji zelis izbrisati: ");
			scanf("%d", &brisi);
			delete(root, brisi);
			break;

		case 7:
			break;

		default:
			printf("\nPogresan unos!\n");
			break;

		}
	} while (choice != 7);
	return 0;
}

int inorder(Position current) {
	if (current == NULL)
		return 0;

	inorder(current->left);
	printf(" %d ", current->num);
	inorder(current->right);

	return 1;
}

int preorder(Position current) {
	if (current == NULL)
		return 0;

	printf(" %d ", current->num);
	preorder(current->left);
	preorder(current->right);

	return 1;
}

int postorder(Position current) {
	if (current == NULL)
		return 0;

	postorder(current->left);
	postorder(current->right);
	printf(" %d ", current->num);

	return 1;
}

int levelOrder(Position current) {
	if (current == NULL) {
		return 0;
	}

	int h = Height(current);
	for (int i = 0; i < h; i++)
		currentLevel(current, i);

	return 1;
}

int Height(Position current) {

	if (current == NULL)
		return 0;
	else {
		int LHeight = Height(current->left);
		int RHeight = Height(current->right);

		if (LHeight > RHeight)
			return (LHeight + 1);
		else
			return (RHeight + 1);
	}
}

int currentLevel(Position current, int lvl) {

	if (current == NULL)
		return 0;

	if (lvl == 1) {
		printf(" %d ", current->num);
	}
	else if (lvl > 1) {
		currentLevel(current->left, lvl - 1);
		currentLevel(current->right, lvl - 1);
	}

	return 1;
}

Position insert(int number, Position current) {
	if (current == NULL)
		return createElement(number);
	else if (current->num < number)
		current->right = insert(number, current->right);
	else if (current->num > number)
		current->left = insert(number, current->left);

	return current;
}

Position createElement(int number)
{
	Position newElement = NULL;
	newElement = (Position)malloc(sizeof(stablo));
	if (!newElement)
	{
		printf("\nCan't allocate memory!\n");
		return ERROR;
	}

	newElement->num = number;
	newElement->left = NULL;
	newElement->right = NULL;

	return newElement;
}

void find_op(Position current) {

	int trazi;
	Position vrijednost;
	printf("\n Upisite element koji trazite: ");
	scanf("%d", &trazi);
	vrijednost = find(current, trazi);

	if (vrijednost == NULL)
		printf("\n Taj broj ne postoji u stablu!\n");
	else

		printf("\n Broj %d je pronaden u stablu: %d\n",trazi,&trazi);
}

Position find(Position current, int trazi) {

	if (current == NULL)
		return NULL;
	else if (current->num > trazi)
		return find(current->left, trazi);
	else if (current->num < trazi)
		return find(current->right, trazi);
	return current;

}

Position findMax(Position current)
{
	while (current->right != NULL)
		current = current->right;
	return current;
}

Position findMin(Position current)
{
	while (current->left != NULL)
		current = current->left;
	return current;
}

Position delete(Position current, int brisi)
{
	if (NULL == current)
		printf("\n Taj element ne postoji!\n");

	else if (current->num > brisi)
		current->left = delete(current->left, brisi);

	else if (current->num < brisi)
		current->right = delete(current->right, brisi);

	else {
		if (current->left) {
			Position temp = findMax(current->left);
			current->num = temp->num;
			current->left = delete(current->left, temp->num);
		}
		else if (current->right) {
			Position temp = findMin(current->right);
			current->num = temp->num;
			current->right = delete(current->right, temp->num);
		}
		else {
			free(current);
			return NULL;
		}
	}
	return current;
}
