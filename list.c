#include "list.h"
#include "stock.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int containsText(const char *mainText, const char* minorText) {
    int str_len = strlen(mainText);
    int suffix_len = strlen(minorText);
    if (str_len < suffix_len) {
        return 0;
    }
    return strncmp(mainText + str_len - suffix_len, ".bin", suffix_len) == 0;
}

void createList( linked_list_t* listPtr) {
    listPtr->headPtr = NULL;
    listPtr->tailPtr = NULL;
    listPtr->count = 0;
}

void createListFromFiles(linked_list_t *listPtr, DIR *directory) {
	listPtr->headPtr = NULL;
    listPtr->tailPtr = NULL;
    listPtr->count = 0;
	struct dirent* dirEntryPtr;

    while( (dirEntryPtr = readdir(directory)) != NULL) {
        FILE* output;
        stock_t *stock;
        if (containsText(dirEntryPtr->d_name, ".bin")) {
            output = fopen(dirEntryPtr->d_name, "rb");
            while (!feof(output)) {
                if (output != NULL) {
                    readIntoStock(stock, output);
                    if (stock == NULL) {
                        break;
                    }
                    insertNode(listPtr, initNode(*stock));
                }
            } // ugly braces here..
        } // yeah, ik..
    } // but it works... soo...
	free(dirEntryPtr);
}

void insertNode( linked_list_t* listPtr, node_t* nPtr ) {
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

node_t* dequeueNode( linked_list_t* listPtr ) {
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

void deleteList( linked_list_t* listPtr ) {
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
    listPtr->headPtr = listPtr->tailPtr = NULL;
    listPtr->count = 0;
}

void traverseStack( const linked_list_t* listPtr ) { 
    if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->headPtr;
    while (selectedNode->nextPtr != NULL) {
        printStock(&selectedNode->stock);
        selectedNode = selectedNode->nextPtr;
    }
    printStock(&selectedNode->stock);
}

void traverseQueue( const linked_list_t* listPtr ) {
    if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode->previousPtr != NULL) {
        printStock(&selectedNode->stock);
        selectedNode = selectedNode->previousPtr;
    }
    printStock(&selectedNode->stock);
}

void printSpecificTicker(const linked_list_t* listPtr, const char ticker[]) {
	if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode->previousPtr != NULL) {
		if (strcmp(selectedNode->stock.ticker, ticker) == 0)
        	printStock(&selectedNode->stock);
        selectedNode = selectedNode->previousPtr;
    }
	if (strcmp(selectedNode->stock.ticker, ticker) == 0)
    	printStock(&selectedNode->stock);
}

void printNumberOfOwnedStocks( const linked_list_t* listPtr) {
    char * stockNames[20] = {NULL};
    int stockCount[20] = {0};
    int length = 20;

    if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode->previousPtr != NULL) {
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
    }
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
    printf("Stocks Owned\n");
    printf("------------\n");
    for (int i = 0; i < length; i++) {
        if (stockNames[i] != NULL) {
            printf("%s  %6d\n", stockNames[i], stockCount[i]);
        }
    }
}

int countTickerStocks( const linked_list_t* listPtr, const char ticker[]) {
	int value = 0;
	if (listPtr->count == 0) { return 0; }
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode->previousPtr != NULL) {
		if (strcmp(selectedNode->stock.ticker, ticker) == 0)
			value++;
        selectedNode = selectedNode->previousPtr;
    }
	if (strcmp(selectedNode->stock.ticker, ticker) == 0)
		value++;
	return value;
}

int countShares( const linked_list_t* listPtr) {
	int value = 0;
	if (listPtr->count == 0) { return 0; }
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode->previousPtr != NULL) {
		value += selectedNode->stock.numShares;
        selectedNode = selectedNode->previousPtr;
    }
	value += selectedNode->stock.numShares;
	return value;
}

// overwrites then closes given file | assumes `overwrite` is valid
void listUpdateSingleFile(const linked_list_t* listPtr, char* filename) {
    node_t* selectedNode = listPtr->tailPtr;
    FILE* overwrite = fopen(filename, "wb");
    fclose(overwrite);
    if (listPtr->count == 0) {
        remove(filename);
    }
    overwrite = fopen(filename, "wb");
    while (selectedNode != NULL) {
        fwrite(&selectedNode->stock, sizeof(stock_t), 1, overwrite);
        selectedNode = selectedNode->previousPtr;
    }
    fclose(overwrite);
}

