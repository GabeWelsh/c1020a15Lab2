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
    int count = countTickerShares(list, input);
    if (count == 0) {
        printf("You do not own any \"%s\" stocks", input);
        return;
    }
    linked_list_t newList = returnSpecifiedTicker(list, input);
    int numSell;
    printf("Enter number of shares to sell: ");
    scanf("%d", &numSell);
    if (count < numSell) {
        printf("You do not own that many shares!\n");
        return;
    }
    double stockPrice;
    printf("Enter stock price: ");
    scanf("%lf", &stockPrice);
    /*
        2. go through the queue of stocks removing the number of shares 
    needed and calculating and printing the total price to buy the stocks
      a. total selling price, and the gains (or losses).
        3. Open the file again in write mode and writes the entire file from the updated contents of the list
      a. If the user sells all shares of a stock in a file, then the program has to delete the file
    */
    
    double GainOrLoss;
    calculate_sell_t sell = calculateSell(&newList, numSell, stockPrice);
    printf("Shares sold: $%.2lf\n", sell.sum);
    printf("Shares bought: $%.2lf\n", sell.originalSum);
    if (sell.sum > sell.originalSum)
        printf("Gained: $%.2lf\n", sell.sum - sell.originalSum);
    else
        printf("Lost: $%.2lf\n", sell.originalSum - sell.sum);
}

int main() {
    DIR* directory = opendir(".");
    int userInput = -1; // must be set to enter loop
    linked_list_t mainList;
    // reads *.bin into the list
    createList(&mainList, directory);

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
                directory = opendir(".");
                createList(&mainList, directory);
                report(&mainList);
                break;
            case 2:
                directory = opendir(".");
                createList(&mainList, directory);
                //buy();
                break;
            case 3:
                directory = opendir(".");
                createList(&mainList, directory);
                sell(&mainList);
                break;
            default:
                printf("Please enter a valid input.\n");
                userInput = -1; // in case the user inputs a non-int
                break;
        }
    }
    closedir(directory);
    deleteList(&mainList);
    
    return 0;
}
