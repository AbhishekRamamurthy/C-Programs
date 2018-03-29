#include"linkedlist.h"

extern struct node {
	int data;
	struct node* next;
}*head;

extern struct node* _Push (int ,struct node*);
extern struct node* _Pop(struct node*);
extern void _Print(struct node*); 
