#include "list.h"
#include "stock.h"
#include "date.h"
#include "node.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int containsText(const char *mainText, const char* minorText) {
    int main_len = strlen(mainText);
    int minor_len = strlen(minorText);
    if (main_len < minor_len) {
        return 0;
    }
    return strncmp(mainText + main_len - minor_len, ".bin", minor_len) == 0;
}

// sorts in decending order (oldest at tail)
void sortList(linked_list_t *listPtr) {
    if (listPtr->count <= 1) {
        return;
    }
    node_t *nodeOne, *nodeTwo;
    stock_t tempStock;

    for (nodeOne = listPtr->headPtr->nextPtr; nodeOne != NULL; nodeOne = nodeOne->nextPtr) {
        tempStock = nodeOne->stock;
        nodeTwo = nodeOne->previousPtr;
        while (nodeTwo != NULL && datecmp(nodeTwo->stock.date, tempStock.date) == -1) {
            nodeTwo->nextPtr->stock = nodeTwo->stock;
            nodeTwo = nodeTwo->previousPtr;
        }
        if (nodeTwo == NULL) {
            listPtr->headPtr->stock = tempStock;
        } else {
            nodeTwo->nextPtr->stock = tempStock;
        }
    }
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

    while ((dirEntryPtr = readdir(directory)) != NULL) {
        FILE* input;
        stock_t stock;
        if (containsText(dirEntryPtr->d_name, ".bin")) {
            input = fopen(dirEntryPtr->d_name, "rb");
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
        listPtr->tailPtr->nextPtr = node->previousPtr = NULL;
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
    while (listPtr->count != 0) {
        free(dequeueNode(listPtr));
    }
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

void printSpecificTicker(const linked_list_t* listPtr, const char ticker[]) {
	char filename[MAX_TICKER_LENGTH + 6];
    snprintf(filename, sizeof(filename), "%s.bin", ticker);
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        printf("You do not own any of that stock!\n");
        return;
    }
    fclose(fp);
    printf("Ticker   Purchase Date   Shares   Price Per Share\n");
    printf("-------------------------------------------------\n");
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode != NULL) {
		if (strcmp(selectedNode->stock.ticker, ticker) == 0)
        	printStock(&selectedNode->stock);
        selectedNode = selectedNode->previousPtr;
    }
}

void printNumberOfOwnedStocks( const linked_list_t* listPtr) {
    char* stockNames[20] = {NULL};
    int stockCount[20] = {0};
    int length = 20;

    if (listPtr->count == 0) { return; }
    node_t* selectedNode = listPtr->tailPtr;
    while (selectedNode != NULL) {
        for (int i = 0; i < length; i++) {
            if (stockNames[i] == NULL) {
                stockNames[i] = selectedNode->stock.ticker;
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
    if (stockNames[0] == NULL){
        printf("You do not own any stocks\n");
    }
    printf("Stocks Owned\n");
    printf("------------\n");
    for (int i = 0; i < length; i++) {
        if (stockNames[i] != NULL) {
            printf("%s  %6d\n", stockNames[i], stockCount[i]);
        }
    }
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

void listUpdateSingleFile(linked_list_t* listPtr, const char* filename) {
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
