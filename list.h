/* Name: list.h
 * Description: 
*/
#ifndef LIST_T
#define LIST_T

#include "node.h"
#include <dirent.h>

typedef struct {
    node_t* headPtr;
    node_t* tailPtr;
    int count;
} linked_list_t;


void printNumberOfOwnedStocks( const linked_list_t* listPtr);
void printSpecificTicker(const linked_list_t* listPtr, const char ticker[]);
int countTickerStocks( const linked_list_t* listPtr, const char ticker[]);
int countShares( const linked_list_t* listPtr);
void listUpdateSingleFile( linked_list_t* listPtr, const char* filename );

void createList( linked_list_t* listPtr);
void createListFromFiles(linked_list_t *listPtr, DIR *directory);
void insertNode( linked_list_t* listPtr, node_t* nPtr );
node_t* popNode( linked_list_t* listPtr );
node_t* dequeueNode( linked_list_t* listPtr );
void deleteList( linked_list_t* listPtr );
void traverseStack( const linked_list_t* listPtr );
void traverseQueue( const linked_list_t* listPtr );

#endif
