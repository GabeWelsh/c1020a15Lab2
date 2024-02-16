/* Name: list.h
 * Description: 
*/
#ifndef LIST_T
#define LIST_T

#include "node.h"

typedef struct {
    node_t* headPtr;
    node_t* tailPtr;
    int count;
} dbl_linked_list_t;

void createList( dbl_linked_list_t* listPtr );
void insertNode( dbl_linked_list_t* listPtr, node_t* nPtr );
node_t* popNode( dbl_linked_list_t* listPtr );
node_t* dequeueNode( dbl_linked_list_t* listPtr );
void deleteList( dbl_linked_list_t* listPtr );
void traverseStack( const dbl_linked_list_t* listPtr );
void traverseQueue( const dbl_linked_list_t* listPtr );

#endif
