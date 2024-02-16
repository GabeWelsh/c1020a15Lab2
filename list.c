#include "list.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>

void createList( dbl_linked_list_t* listPtr ) {
    listPtr->headPtr = NULL;
    listPtr->tailPtr = NULL;
    listPtr->count = 0;
}

void insertNode( dbl_linked_list_t* listPtr, node_t* nPtr ) {
    if (listPtr->count == 0) {
        listPtr->headPtr = nPtr;
        listPtr->tailPtr = nPtr;
        listPtr->count++;
    } else {
        nPtr->nextPtr = listPtr->headPtr;
        listPtr->headPtr->previousPtr = nPtr;
        listPtr->headPtr = nPtr;
        listPtr->count++;
    }
}

node_t* popNode( dbl_linked_list_t* listPtr ) {
    if (listPtr->count > 1) {
        listPtr->headPtr = listPtr->headPtr->nextPtr;
        node_t* node = listPtr->headPtr->previousPtr;
        listPtr->headPtr->previousPtr = NULL;
        listPtr->count--;
        return node;
    } else if (listPtr->count == 1) {
        node_t* temp = listPtr->headPtr;
        listPtr->headPtr = NULL;
        listPtr->tailPtr = NULL;
        listPtr->count--;
        return temp;
    } else {
        return NULL;
    }
}

node_t* dequeueNode( dbl_linked_list_t* listPtr ) {
    if (listPtr->count > 1) {
        listPtr->tailPtr = listPtr->tailPtr->previousPtr;
        node_t* node = listPtr->tailPtr->nextPtr;
        listPtr->tailPtr->nextPtr = NULL;
        listPtr->count--;
        return node;
    } else {
        node_t* temp = listPtr->tailPtr;
        listPtr->headPtr = NULL;
        listPtr->tailPtr = NULL;
        listPtr->count--;
        return temp;
    }
}

void deleteList( dbl_linked_list_t* listPtr ) {
    if (listPtr->count == 0) {
        // do what's at the bottom
    } else {
        node_t* selectedNode = listPtr->headPtr;
        while (selectedNode->nextPtr != NULL) {
            selectedNode = selectedNode->nextPtr;
            free(selectedNode->previousPtr);
        }
        free(selectedNode);
    }
    listPtr->headPtr = NULL;
    listPtr->tailPtr = NULL;
    listPtr->count = 0;
}

void traverseStack( const dbl_linked_list_t* listPtr ) { 
    if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->headPtr;
    while (selectedNode->nextPtr != NULL) {
       printf("%d ", selectedNode->i);
       selectedNode = selectedNode->nextPtr;
    }
    printf("%d\n", selectedNode->i);
}

void traverseQueue( const dbl_linked_list_t* listPtr ) {
    if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode->previousPtr != NULL) {
        printf("%d ", selectedNode->i);
        selectedNode = selectedNode->previousPtr;
    }
    printf("%d\n", selectedNode->i);
}

