/** 
 *  @file myintlist.h 
 *  @brief Provides functions to handle a dynamic integer array
 *  @author Dichter nd@nocoffeetech.de 
 * 
 *   
 * 
 *  @date 5.04.2020  	First Implementation of:
 *						knoten,Knoten_t,KnotenPtr_t,
 *						dump_buffer, einfuegenKnoten 
 *						neuerKnoten, loescheKnoten, knotenAuflisten 
 *						searcher,mymainloop
 * 
 *  @todo english ,different data type, ability formultiple lists, speicherfreigabe
 * 
 *  @test -
 * 
 *  @bug No known bugs  
 * 
 *  @version 0.1   
 */
 
#ifndef MYINTLIST_H
#define MYINTLIST_H

#include <stdio.h>

/**
 * @define MAX
 * @brief Defines maximum
 *
#define MAX 256*/



/**
 * @struct struct knoten
 * @brief Structure to save a node (value,pointer to next node)
 */
struct knoten {
  int wert;
  struct knoten *next;
};



/**
 * @typedef typedef struct knoten Knoten_t
 * @brief Typedefinition of structure knoten
 */
typedef struct knoten Knoten_t;



/**
 * @typedef typedef struct knoten* KnotenPtr_t
 * @brief Typedefinition of structure knoten*
 */
typedef struct knoten* KnotenPtr_t;



/**
 * @fn void dump_buffer(FILE* fp);
 * @brief Function to empty the given file stream
 *
 * Function to empty the given file stream until EOF or '\n'
 * @param fp Filestream to empty
 */
void dump_buffer(FILE* fp);



/**
 * @fn void einfuegenKnoten( KnotenPtr_t neu);
 * @brief Inserts the given node into the list
 *
 * The Node gets inserted so that the list stays sorted
 * and that there will not be any duplicates of values
 *
 * @param neu Node to insert
 */
void einfuegenKnoten( KnotenPtr_t neu);



/**
 * @fn void neuerKnoten( void );
 * @brief Creates a new node
 *
 * Creates a new node, prompts the user to insert the needed value and calls einfuegenKnoten
 */
void neuerKnoten( void );



/**
 * @fn void loescheKnoten( int val);
 * @brief Deletes node of value val from list
 */
void loescheKnoten( int val);



/**
 * @fn void knotenAuflisten( void );
 * @brief Prints the list
 */
void knotenAuflisten( void );



/**
 * @fn int searcher(int val);
 * @brief Searches for a given value "val" in the list and returns its position
 *
 * @param val Value to search for
 *
 * @return Position of searched value (-1 if it was not found)
 */
int searcher(int val);



/**
 * @fn void mymainloop(void);
 * @brief Runs the main interface of the list programm
 */
void mymainloop(void);

#endif //ifndef MYINTLIST_H