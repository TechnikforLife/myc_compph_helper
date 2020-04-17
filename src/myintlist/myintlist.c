#include "myintlist.h"
#include <stdlib.h>


void dump_buffer(FILE *fp) {
  int ch;//current char being emptied

  while( (ch = fgetc(fp)) != EOF && ch != '\n' )
  /* No directiv needed */ ;
}

//the beginning of the list
KnotenPtr_t anfang = NULL;



void einfuegenKnoten( KnotenPtr_t neu ) {
	KnotenPtr_t hilfZeiger;//currently processed node
	KnotenPtr_t hilfZeiger2;//saves next node in the insertion process
	if(anfang==NULL){//list is empty
		anfang = neu;
		neu->next = NULL;

	}else{//list has elements in it
		hilfZeiger = anfang;

		//prevent duplication
		if(neu->wert==hilfZeiger->wert){
			printf("Not inserted, already saved.\n");
			return;

		//test rather the new value needs to go at the beginning
		}else if((neu->wert<hilfZeiger->wert)){
			anfang=neu;
			neu->next=hilfZeiger;
			return;
		}

		//itterate through list if there are more than 1 elements in the list
		while(hilfZeiger->next !=NULL){

			//do not insert if the value already exists
			if(neu->wert==hilfZeiger->wert){
				printf("Not inserted, already saved.\n");
				return;

			//test if the value fits between the current and next value
			}else if((neu->wert>hilfZeiger->wert)&&(neu->wert<hilfZeiger->next->wert)){

				//insert the node
				hilfZeiger2=hilfZeiger->next;
				hilfZeiger->next=neu;
				neu->next=hilfZeiger2;

				//exit
				return;
			}
			hilfZeiger = hilfZeiger->next;

		}

		//case of only 1 element being present in the list and the value not belonging at the beginning
		if(neu->wert==hilfZeiger->wert){//present duplication

			printf("Not inserted, already saved.\n");

			//exit
			return;
		}else {
			//insert the node
			hilfZeiger->next=neu;
			neu->next= NULL;

			//exit
			return;
		}
	}
}

void neuerKnoten( void ) {

	//memory allocation
  KnotenPtr_t neu = malloc(sizeof(Knoten_t));
  if( neu == NULL ) {
    printf("Kein Speicher vorhanden!?\n");
    return;
  }

  //get value from the user
  printf("Neuen Wert fuer Knoten eingeben: ");
  if( scanf("%d", &neu->wert) != 1 ) {
	  //cleanup
    dump_buffer(stdin);
    printf("Fehler bei der Eingabe\n");
    free(neu); // Speicher wieder freigeben
    return;
  }

  //cleanup
  dump_buffer(stdin);

  //insert node
  einfuegenKnoten( neu );
}

void loescheKnoten( int val ) {

  KnotenPtr_t hilfZeiger1;//currently processed node
  KnotenPtr_t hilfZeiger2;//next node

  //test rather the list is empty
  if( anfang != NULL ) {

	  //test rather the first value
	  //is the value to be deleted
    if( anfang->wert == val ) {

		//delete the first node
      hilfZeiger1 = anfang->next;
      free(anfang);
      anfang = hilfZeiger1;
    }
    else {
      hilfZeiger1 = anfang;

	  //itterate through the list until the end is reached
      while( hilfZeiger1->next != NULL ) {
        hilfZeiger2 = hilfZeiger1->next;

		//test rather the value of the next node is the value to be deleted
        if( hilfZeiger2->wert == val ) {

			//delete the next node
          hilfZeiger1->next = hilfZeiger2->next;
          free(hilfZeiger2);
          break;
        }
        hilfZeiger1 = hilfZeiger2;
      }  // Ende while
    }  // Ende else
  }  // Ende if
}

void knotenAuflisten( void ) {
  KnotenPtr_t hilfZeiger = anfang;//currently processed node

  printf("Elemente in der Liste:\n");
  while( hilfZeiger != NULL ) {
    printf("\t -> %d\n", hilfZeiger->wert);
    hilfZeiger = hilfZeiger->next;
  }
}

int searcher(/*Value to search for*/	int val){
	KnotenPtr_t hilfZeiger = anfang;//currently processed node
	int ret=1;

	//itterate till the end is reached
	while(hilfZeiger!=NULL){

		//check rather the value was found
		if(hilfZeiger->wert==val)return ret;

		//for the next step:
		++ret;
		hilfZeiger=hilfZeiger->next;
	}

	//value not found
	return -1;
}

void mymainloop(void) {
  int wahl = 0;//user decision, what to do
  int val = 0;//value to delete/search
  int addr=0;//point where value was found

  do {

	  //list options
    printf(" -1- Neues Element hinzufuegen\n");
    printf(" -2- Element loeschen\n");
    printf(" -3- Alle Elemente auflisten\n");
	printf(" -4- Nach einem Element suchen\n");
    printf(" -5- Programmende\n");
    printf(" Ihre Auswahl : ");

	//get input what to do
    if( scanf("%d", &wahl) != 1 ) {
      printf("Fehlerhafte Auswahl\n");
      wahl = 0;
      dump_buffer(stdin);
    }
    switch( wahl ) {
		//newnode
		case 1 : neuerKnoten(); break;

		//delete node
		case 2 : if( anfang == NULL ) {//check if the list is empty
                printf("Liste ist leer!\n");
				}
				else {

					//get value to delete
					printf("Wert zum Loeschen : ");
					if( scanf("%d", &val) != 1 ) {
						printf("Fehler bei der Eingabe\n");
					}
					else {
						loescheKnoten( val );
					}
				}
				break;

		//print list
		case 3 : if( anfang == NULL ) {//check if the list is empty
					printf("Liste ist leer!\n");
				}
				else {
					knotenAuflisten();
				}
				break;

		//search value
		case 4 :if( anfang == NULL ) {//check if the list is empty
                printf("Liste ist leer!\n");
				}else{

					//get value to search for
					printf("Zu suchender Wert: ");
					if( scanf("%d", &val) != 1 ) {
						printf("Fehler bei der Eingabe\n");
					}
					else {
						addr=searcher( val );
						if(addr==-1){//value was not found
							printf("%d ist nicht in der Liste.\n",val);
						}else{//value was found
							printf("%d ist an der %d. Stelle.\n",val,addr);
						}
					}


				}

    }
	//exit if it was selected
  }while( wahl != 5 );
}
