#include "doublelinkedlist.h"
#include <stdlib.h>
#include <stdio.h>
LIST_t *list_create(){
	LIST_t* newlist=NULL;
	newlist=(LIST_t*)malloc(sizeof(LIST_t));
	if(newlist==NULL){
		fprintf(stderr,"RAM allocation Error(newlist)!\n");
		exit(EXIT_FAILURE);
	}
	newlist->start=NULL;
	newlist->end=NULL;
	return newlist;
}
LISTNODE_t *list_insert(/*list to insert into*/	LIST_t *L,
						/*Node to insert after*/LISTNODE_t *E,
						/*Value to insert*/		double val){
	if (L==NULL){
		fprintf(stderr,"Create a List first\n");
		exit(EXIT_FAILURE);
	}
	LISTNODE_t* newnode=NULL;
	newnode=(LISTNODE_t*)malloc(sizeof(LISTNODE_t));
	if(newnode==NULL){
		fprintf(stderr,"RAM allocation Error(newnode)!\n");
		exit(EXIT_FAILURE);
	}
	newnode->data=val;
	if(L->start==NULL){//empty list
		printf("List ist empty(ignoring E)\n");
		newnode->prev=NULL;
		newnode->next=NULL;
		L->start=newnode;
		L->end=newnode;
	}else{//list with existing elements
		if(E==NULL){//insert at beginning
			newnode->next=L->start;
			newnode->prev=L->start->prev;
			L->start->prev=newnode;
			L->start=newnode;
		}else if(E==L->end){//insert at the end
			newnode->next=E->next;
			newnode->prev=E;
			E->next=newnode;
			L->end=newnode;
		}else{//insert somewhere else
			newnode->next=E->next;
			newnode->prev=E;
			E->next->prev=newnode;
			E->next=newnode;
		}
	}
	return newnode;
}

//add element at the end
LISTNODE_t *list_unshift(LIST_t *L, double val){
	LISTNODE_t* newnode=NULL;
	newnode=list_insert(L,L->end,val);
	return newnode;
}

//add element at the beginning
LISTNODE_t *list_push(LIST_t *L, double val){
	LISTNODE_t* newnode=NULL;
	newnode=list_insert(L,NULL,val);
	return newnode;
}

//return data at the beginning and delete element
double list_shift(LIST_t *L){
	double tempdouble=0.;
	LISTNODE_t* temp=NULL;
	tempdouble=L->start->data;
	temp=L->start;
  if(L->start->next!=NULL){
    L->start->next->prev=L->start->prev;
  }
	L->start=temp->next;
	free(temp);
	return tempdouble;
}

//return data at the end and delete element
double list_pop(LIST_t *L){
	double tempdouble=0.;
	LISTNODE_t* temp=NULL;
	tempdouble=L->end->data;
	L->end->prev->next=L->end->next;
	temp=L->end;
	L->end=temp->prev;
	free(temp);
	return tempdouble;
}

void list_delete(LIST_t *L, LISTNODE_t *E){
	if(L->start==E){
		L->start=E->next;
		E->next->prev=E->prev;
	}else if(L->end==E){
		L->end=E->prev;
		E->prev->next=E->next;
	}else{
		E->prev->next=E->next;
		E->next->prev=E->prev;
	}
	free(E);
}

LIST_t *list_merge(LIST_t *L, LIST_t *M){
	LIST_t* newlist;
	newlist=list_create();
	newlist->start=L->start;
	newlist->end=M->end;
	L->end->next=M->start;
	M->start->prev=L->end;
	free(L);
	free(M);
	return newlist;
}

void list_free(LIST_t *L){
	if(L->start==NULL){
		printf("Empty List(free)!\n");
	}else{
		LISTNODE_t* temp=NULL;
		LISTNODE_t* itterator=L->start;
		while(itterator->next!=NULL){
			temp=itterator->next;
			free(itterator);
			itterator=temp;
		}
		free(itterator);
	}
	free(L);
}

void printlist(/*list to print*/	LIST_t *L){
	if(L->start==NULL){
		printf("Empty List(print)!\n");
	}else{
		printf("L={");
		LISTNODE_t* itterator=L->start;
		while(itterator->next!=NULL){
			printf(" %f,",itterator->data);
			itterator=itterator->next;
		}
		printf(" %f}\n",itterator->data);
	}
}
