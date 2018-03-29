#include <malloc.h>
#include "linkedlist.h"

/* structure to hold the data and address of next node */
struct node {
	int data;
	struct node* next;
};

/* stucture type pointer, holds the address of the head of the structure*/

struct node* head;

/* 
	Funtion to insert data at the begining of the linked list
	Initial check "is it the first entry to the list" 
*/

struct node* _InsertBegining (int data,struct node * head) {
	
	int val=data;	
	struct node* temp = (struct node*)malloc(sizeof(struct node));
	temp->data=val;
	temp->next=NULL;
	if(head !=NULL) {
		temp->next=head;
	}
	head=temp;
	return head;
}
/*
	Function to insert the data to end of the linked list
*/
void _InsertEnd(int data, struct node* head) {

	struct node* temp=(struct node*)malloc(sizeof(struct node));
	struct node* end;
	end=head;
	temp->data=data;
	temp->next=NULL;
	
	/*iterate using head to end of the list*/	
	while(end->next!=NULL) {
		
		end=end->next;
	}

	/*replace end->next=null with temp address*/
	/*ie.. the address of the new data to linked list*/
	end->next=temp;
}

/* 
	Function to insert the data in the middle of the list
	based on the position mentioned by the user
*/
void _InsertRandom(struct node* head, int data,int pos) {
	
	int i=0;
	struct node* p=head;
	struct node* q=head;
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	temp->data=data;
	
	/* iterate to the position mentioned */
	for (i=0;i<pos-1;i++) {
		
		p=p->next;
	}	
	/*
	  replace q with address of the position pointed by p.
	  point p with the address of the newly inserted data.
      point the address field of newly created data to q
	*/
	q=p->next;
	p->next=temp;
	temp->next=q;
}	

/* 
	Function to delete the first entry of the list 
	Same is used for retrieving entry from the list (stack pop)
*/
struct node* _DeleteEntryBegining(struct node* head) {
	
	/* 
	   ret used for returning the poped data from the entry 
	   along with the updated head adress (return multiple arguments)
	*/
	struct node* ret=(struct node*) malloc(sizeof(struct node));	
	
	struct node* temp=head;
	int data;
	data=head->data;
	ret->data=data;
	head=head->next;
	ret->next=head;
	free(temp);	
	return ret;	
}

/*
	Function to delete the last entry in the list
	Can be used in FIFO queue
*/

int _DeleteEntryLast(struct node* head) {
	
	struct node* temp=head;
	struct node* temp1=head;	
	int data;
	/*iterate till the end of the queue*/
	while(temp->next!=NULL) {

		temp1=temp;	
		temp=temp->next;

	}
	data=temp->data;
	free(temp);
	temp1->next=NULL;
	return data;
}

/*
	Delete any particular data from the list
	Note : all entries are assumed to unique (no repetition)
*/
void _DeleteEntryRandom(struct node* head,int data) {
	
	struct node* temp=head;
	struct node* temp1=head;
	
	while(temp->data !=data) {
		temp1=temp;
		temp=temp->next;
	}
	temp1->next=temp->next;
	free(temp);
}

/*
	Function to print all the entries in the list
*/
void _Print(struct node* head) {
	
	struct node* temp=head;
	printf("\n list is = ");
	while(temp !=NULL) {
	
		printf("%d\t",temp->data);
		temp=temp->next;
	}
	printf("\n");
}


//void main() {
//	
//	struct node* head;
//	head=NULL;
//	head=_InsertBegining(4,head);
//	head=_InsertBegining(5,head);
//	_Print(head);
//	_InsertEnd(1,head);
//	_InsertEnd(2,head);
//	_Print(head);
//	_InsertRandom(head,10,1);
//	_Print(head);
//	head=_DeleteEntryBegining(head);
//	_Print(head);
//	_DeleteEntryLast(head);
//	_Print(head);
//	_DeleteEntryRandom(head,4);
//	_Print(head);
//}
