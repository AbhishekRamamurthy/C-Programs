#include <stdio.h>
#include "stack.h"

int main() {
	int data;
	struct node* temp;
	head=NULL;
	head=_Push(5,head);
	
	head=_Push(6,head);
	head=_Push(7,head);
	temp=_Pop(head);
	data=temp->data;
	head=temp->next;
	printf("data retrieved is= %d",data);
	free(temp);
}

