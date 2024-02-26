#include "list.h"
#include "stock.h"
#include "date.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// function only in this file
// returns 1 if `mainText` ends with `minorText`, 0 otherwise
int stringEndsWith(const char *mainText, const char* minorText) {
    int main_len = strlen(mainText);
    int minor_len = strlen(minorText);
    if (main_len < minor_len) {
        return 0;
    }
    return (strncmp(mainText + main_len - minor_len, ".bin", minor_len) == 0);
}

// sets each variable in supplied list to it's corresponding NULL value
void createList( linked_list_t* listPtr) {
    listPtr->headPtr = NULL;
    listPtr->tailPtr = NULL;
    listPtr->count = 0;
}

// goes through all .bin files in supplied directory and reads it into given list
// assumes `directory` was just opened and valid | assumes `listPtr` is not NULL
void createListFromFiles(linked_list_t *listPtr, DIR *directory) {
    listPtr->headPtr = NULL;
    listPtr->tailPtr = NULL;
    listPtr->count = 0;
    struct dirent* dirEntryPtr;

    while ((dirEntryPtr = readdir(directory)) != NULL) {
        if (stringEndsWith(dirEntryPtr->d_name, ".bin")) {
            stock_t stock;
            FILE* input = fopen(dirEntryPtr->d_name, "rb");
            if (input != NULL) {
                while (fread(&stock, sizeof(struct stock_t), 1, input) == 1) {
                    insertNode(listPtr, initNode(stock));
                }
                fclose(input);
            } else {
                printf("Error creating list (could not open file): \"%s\"", dirEntryPtr->d_name);
            }
        }
    }
}

// inserts supplied node (`nPtr`) into supplied `listPtr` at the head
// assumes `listPtr` and `nPtr` are not NULL
void insertNode( linked_list_t* listPtr, node_t* nPtr ) {
    if (listPtr->count == 0) {
        listPtr->headPtr = nPtr;
        listPtr->tailPtr = nPtr;
        listPtr->count++;
    } else {
        nPtr->nextPtr = listPtr->headPtr;
        nPtr->previousPtr = NULL;
        listPtr->headPtr->previousPtr = nPtr;
        listPtr->headPtr = nPtr;
        listPtr->count++;
    }
}

// returns the node contained at `listPtr`'s head
// returns NULL if `listPtr` is empty
node_t* popNode( linked_list_t* listPtr ) {
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

// returns the node contained at `listPtr`'s tail
// returns NULL if `listPtr` is empty
node_t* dequeueNode( linked_list_t* listPtr ) {
    if (listPtr->count > 1) {
        listPtr->tailPtr = listPtr->tailPtr->previousPtr;
        node_t* node = listPtr->tailPtr->nextPtr;
        listPtr->tailPtr->nextPtr = node->previousPtr = NULL;
        listPtr->count--;
        return node;
    } else if (listPtr->count == 1) {
        node_t* node = listPtr->tailPtr;
        listPtr->headPtr = NULL;
        listPtr->tailPtr = NULL;
        listPtr->count--;
        return node;
    } else {
        return NULL;
    }
}

// iterates through entire list, dequeueing then freeing each node
// assumes `listPtr` is not NULL
void deleteList( linked_list_t* listPtr ) {
    while (listPtr->count != 0) {
        free(dequeueNode(listPtr));
    }
}

// iterates through `listPtr` starting at the head,
//               printing each stock along the way
// assumes `listPtr` is not NULL
void traverseStack( const linked_list_t* listPtr ) { 
    if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->headPtr;
    while (selectedNode->nextPtr != NULL) {
        printStock(&selectedNode->stock);
        selectedNode = selectedNode->nextPtr;
    }
    printStock(&selectedNode->stock);
}

// iterates through `listPtr` starting at the tail,
//               printing each stock along the way
// assumes `listPtr` is not NULL
void traverseQueue( const linked_list_t* listPtr ) {
    if (listPtr->count == 0) { 
        printf("Empty list\n");
        return;
    }
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode != NULL) {
        printStock(&selectedNode->stock);
        selectedNode = selectedNode->previousPtr;
    }
}

// iterate through `listPtr` starting at the tail, 
//    printing only the stocks that match `ticker`
// assumes `listPtr` is not NULL and contains at least 
//                              1 of the given `ticker`
void printSpecificTicker(const linked_list_t* listPtr, const char ticker[]) {
	char filename[MAX_TICKER_LENGTH + 6];
    snprintf(filename, sizeof(filename), "%s.bin", ticker);
    printf("Ticker   Purchase Date   Shares   Price Per Share\n");
    printf("-------------------------------------------------\n");
    node_t* selectedNode = listPtr->tailPtr;
    int count = listPtr->count;
    while (count != 0 && selectedNode != NULL) {
		if (strcmp(selectedNode->stock.ticker, ticker) == 0)
        	printStock(&selectedNode->stock);
        selectedNode = selectedNode->previousPtr;
        count--;
    }
}

// prints the number of owned  per each ticker
// <ticker> <number of shares>
// note: limit is 20 unique tickers
void printNumberOfOwnedShares( const linked_list_t* listPtr) {
    char* stockNames[20] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,
                           NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL };
    int stockCount[20] = {0};
    int length = 20;

    if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->tailPtr;
    int count = listPtr->count;
    while (count != 0 && selectedNode != NULL) {
        for (int i = 0; i < length; i++) {
            if (stockNames[i] == NULL) {
                stockNames[i] = selectedNode->stock.ticker;
                stockCount[i] = 1;
                break;
            } else if (strcmp(selectedNode->stock.ticker, stockNames[i]) == 0) {
                stockCount[i]++;
                break;
            }
        }
        selectedNode = selectedNode->previousPtr;
        count--;
    }
    if (stockNames[0] == NULL){
        printf("You do not own any stocks\n");
        return;
    }
    printf("Stocks Owned\n");
    printf("------------\n");
    for (int i = 0; i < length; i++) {
        if (stockNames[i] != NULL) {
            printf("%s  %6d\n", stockNames[i], stockCount[i]);
        } else {
            break;
        }
    }
}

// iterates through the given list starting at the tail
//                     and sums up all the nodes shares
// assumes that `listPtr` is not NULL
// returns the total number of shares in the list
int countShares( const linked_list_t* listPtr) {
	int value = 0;
	if (listPtr->count == 0) { return 0; }
    node_t* selectedNode = listPtr->tailPtr;
    int count = listPtr->count;
    while (count > 0 && selectedNode != NULL) {
        value += selectedNode->stock.numShares;
        selectedNode = selectedNode->previousPtr;
    }
	return value;
}

// opens given `filename` and overwrites it with the data stored in `listPtr`
// assumes `listPtr` is not NULL
// NOTE: this function will delete `listPtr` since it uses `dequeueNode`
void listUpdateSingleFile(linked_list_t* listPtr, const char* filename) {
    if (listPtr->count == 0) {
        remove(filename);
        return;
    }
    FILE* overwrite = fopen(filename, "wb");
    if (overwrite == NULL) {
        printf("Error opening file for writing\n");
        return;
    }
    while (listPtr->count > 0) {
        node_t* temp = dequeueNode(listPtr);
        if (fwrite(temp, sizeof(struct stock_t), 1, overwrite) != 1) {
            printf("Issue writing stock to file\n");
        }
        free(temp);
    }
    fclose(overwrite);
}
