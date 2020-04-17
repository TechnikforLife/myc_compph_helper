#ifndef DLL_H
#define DLL_H
typedef struct LISTNODE{
	struct LISTNODE* prev;
	struct LISTNODE* next;	
	double data;
}LISTNODE_t;
typedef struct LIST{
	LISTNODE_t* start;
	LISTNODE_t* end;	
}LIST_t;
LIST_t *list_create();

LISTNODE_t *list_insert(LIST_t*, LISTNODE_t*, double);


LISTNODE_t *list_unshift(LIST_t *L, double p);
LISTNODE_t *list_push(LIST_t *L, double p);


double list_shift(LIST_t *L);
double list_pop(LIST_t *L);

void list_delete(LIST_t *L, LISTNODE_t *E);

LIST_t *list_merge(LIST_t *L, LIST_t *M);

void list_free(LIST_t *L);
void printlist(LIST_t*);
#endif //ifndef DLL_H