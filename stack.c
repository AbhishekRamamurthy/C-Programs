#include"linkedlist.h"
#include"stack.h"

// Last in First out 

/*
	Print the entry made to the list
*/
void _PrintStack(struct node* head){
	
	_Print(head);
}

/*
	Push operation by using insert begining call in linkedlist.h
*/

struct node* _Push (int data,struct node* head){
	
	head=_InsertBegining(data,head);
	_PrintStack(head);
	return head;
}

/*
	Pop operation by using DeletEntryBegining call in linkedlist.h
*/

struct node* _Pop(struct node* head){

	struct node* temp;	
	temp=_DeleteEntryBegining(head);
	head=temp->next;
	_PrintStack(head);
	return temp;
}


