/* Name: main.c
 * Description: contains `main` and functions for
 *              reporting, buying, and selling stocks
 * Where I learned DIR: https://c-for-dummies.com/blog/?p=3246
*/
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "list.h"
#include "date.h"
#include "node.h"
#include "stock.h"

void report(const linked_list_t* list) { 
    printNumberOfOwnedStocks(list);

    char input[MAX_TICKER_LENGTH];
    printf("Enter stock ticker symbol: ");
    scanf("%s",input);
    printf("Ticker   Purchase Date   Shares   Price Per Share\n");
    printf("-------------------------------------------------\n");
    printSpecificTicker(list, input);

}

void buy(linked_list_t* list) {
    printNumberOfOwnedStocks(list);
    char input[MAX_TICKER_LENGTH];
    printf("Enter stock ticker symbol: ");
    scanf("%s",input);
}

void sell(linked_list_t* list) {
    char input[MAX_TICKER_LENGTH];
    printf("Enter stock ticker symbol: ");
    scanf("%s",input);
    int count = countTicker(list, input);
    if (count == 0) {
        printf("You do not own any \"%s\" stocks", input);
        return;
    }
    linked_list_t newList = returnSpecifiedTicker(list, input);
    printf("You own %d %s shares.\n", count, input);
    int numSell;
    printf("Enter number of shares to sell: ");
    scanf("%d", &numSell);
    double stockPrice;
    printf("Enter stock price: ");
    scanf("%lf", &stockPrice);
    /*
    1. remove specified amount of shares
     a. count # shares in last stock
     b.  
    */
    printNumberOfOwnedStocks(&newList);
}

int main() {
    DIR* directory = opendir(".");
    int userInput = -1; // must be set to enter loop
    linked_list_t list;
    // reads *.bin into the list
    createList(&list, directory);

    printf("Welcome to YourTrade.com\n");
    while (userInput != 0) {
        printf("Reporting, buying or selling?\n");
        printf("(0=quit, 1=report, 2=buy, 3=sell): ");
        scanf("%d", &userInput);
        switch (userInput) {
            case 0:
                printf("Thank you for trading with YourTrade.com\n");
                break;
            case 1:
                report(&list);
                break;
            case 2:
                //buy();
                break;
            case 3:
                sell(&list);
                break;
            default:
                printf("Please enter a valid input.\n");
                userInput = -1; // in case the user inputs a non-int
                break;
        }
    }
    closedir(directory);
    deleteList(&list);
    
    return 0;
}
