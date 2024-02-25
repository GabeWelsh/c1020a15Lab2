/* Name: main.c
 * Description: contains `main` and functions for
 *              reporting, buying, and selling stocks
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include "list.h"
#include "date.h"
#include "node.h"
#include "stock.h"

void report(const linked_list_t* list) { 
    printNumberOfOwnedStocks(list);
    char input[MAX_TICKER_LENGTH];
    printf("Enter stock ticker symbol: ");
    scanf("%s",input);
    printSpecificTicker(list, input);
    return;
}

// returns: 1 = bad | 0 = good
int buy() {
    char ticker[MAX_TICKER_LENGTH];
    printf("Enter stock ticker symbol: ");
    scanf("%s", ticker);

    char filename[MAX_TICKER_LENGTH + 6]; // +6 for ".bin"
    snprintf(filename, sizeof(filename), "%s.bin", ticker);

    int numShares;
    printf("Enter number of shares: ");
    scanf("%d", &numShares);
    double sharePrice;
    printf("Enter stock price: ");
    scanf("%lf", &sharePrice);

    date_t date = getDate();

    stock_t stock;
    strcpy(stock.ticker, ticker);
    stock.date = date;
    stock.numShares = numShares;
    stock.pricePerShare = sharePrice;
    
    printStock(&stock);

    FILE* filePtr = fopen(filename, "a");
    if (filePtr == NULL) {
        printf("Could not open file for some reason\n");
        return 1;
    }
    if (writeStockToFile(&stock, filePtr) != 0) {
        printf("`fwrite` was unsuccessful!\n");
        fclose(filePtr);
        return 1;
    }
    fclose(filePtr);
    return 0;
}

void sell() {
    char ticker[MAX_TICKER_LENGTH];
    printf("Enter stock ticker symbol: ");
    scanf("%s", ticker);

    char filename[MAX_TICKER_LENGTH + 6]; // +6 for ".bin"
    snprintf(filename, sizeof(filename), "%s.bin", ticker);
    
    FILE* fileRB = fopen(filename, "rb");
    if (fileRB == NULL) {
        printf("You do not own any \"%s\" stocks.\n", ticker);
        return;
    }
    // get data from file
    stock_t tempStock;
    linked_list_t list;
    createList(&list);

    while(fread(&tempStock, sizeof(stock_t), 1, fileRB) == 1) {
        insertNode(&list, initNode(tempStock));
    }
    fclose(fileRB);

    sortList(&list);

    // print # of shares and get input
    int shares = countShares(&list);
    printf("You own %d shares of \"%s\"\n", shares, filename);
    int toSell;
    double stockPrice;
    printf("How many do you want to sell? ");
    scanf("%d", &toSell);
    if (toSell > countShares(&list)) {
        printf("You do not own that many shares!\n");
        return;
    } else if (toSell <= 0) {
        printf("Input must be above 0\n");
        return;
    }
    printf("What is the current stock price? ");
    scanf("%lf", &stockPrice);
    // calc money and edit list accordingly
    double priceToBuy, sellingPrice;
    priceToBuy = sellingPrice = 0;
    while (toSell > 0) { // Note: not possible to go out of bounds (line 97) so no need to check ********************************
        if (list.tailPtr->stock.numShares > toSell) { // not deleting all shares (end loop)
            priceToBuy += toSell * list.tailPtr->stock.pricePerShare;
            sellingPrice += toSell * stockPrice;
            int temp = list.tailPtr->stock.numShares;
            list.tailPtr->stock.numShares -= toSell;
            toSell -= temp; // should be negative
        } else { // either we move to next stock or num of shares = num to sell
            priceToBuy += list.tailPtr->stock.pricePerShare * list.tailPtr->stock.numShares; // all of them
            sellingPrice += list.tailPtr->stock.numShares * stockPrice;
            toSell -= list.tailPtr->stock.numShares;
            free(dequeueNode(&list)); // it changes tailPtr
        }
    }
    // print results
    printf("Total price to buy the stocks: $%.2lf\n", priceToBuy);
    printf("The total selling price: $%.2lf\n", sellingPrice);
    if (priceToBuy > sellingPrice)
        printf("You lost: $%.2lf\n", (priceToBuy-sellingPrice));
    else
        printf("You gained: $%.2lf\n", (sellingPrice - priceToBuy));
    // update file
    FILE* overwrite = fopen(filename, "wb");
    if (overwrite == NULL) {
        printf("For some reason, the file can't be opened for writing\n");
        return;
    }
    listUpdateSingleFile(&list, filename);
}

int main() {
    DIR* directory;
    int userInput;
    linked_list_t mainList;
    
    printf("Welcome to YourTrade.com\n");
    do {
        printf("Reporting, buying or selling?\n");
        printf("(0=quit, 1=report, 2=buy, 3=sell): ");
        scanf("%d", &userInput);
        switch (userInput) {
            case 0:
                printf("Thank you for trading with YourTrade.com\n");
                break;
            case 1:
                directory = opendir(".");
                createListFromFiles(&mainList, directory);
                closedir(directory);

                report(&mainList);

                deleteList(&mainList);

                break;
            case 2:
                if (buy() == 1) {
                    userInput = 0; // exit the program
                }
                break;
            case 3:
                sell();
                break;
            default:
                printf("Please enter a valid input.\n");
                break;
        }
    } while (userInput != 0);
    return 0;
}
