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

/* What it does exactly:
 * 0.
 * make sure the linked list is valid (must have collected info on the .bin files
 * already)
 * 
 * 1.
 * Print a list of stocks owned like so:
 *      Stocks Owned
 *      ------------
 *      AAPL     25
 *      DISCA     5
 *      GOOG     56
 * Must use a doubly linked list. function from list.c to print
 * (count the number of stocks, not files (duh))
 * 
 * 2.
 * Ask the use for the ticker symbol like so:
 *      Enter stock ticker symbol: <input> 
 * 
 * 3.
 * Print stocks that have the same ticker symbol in the list.
 * 
 * 4.
 * print the contents of the given file like so:
 *     Ticker   Purchase Date    Shares   Price Per Share
 *     --------------------------------------------------
 *     DISCA      7/15/2021        5        $   30.93
 * 
 * 5.
 * celebrate :D
*/
void report(DIR* directory, struct dirent* dirEntryPtr, linked_list_t* list) {
    
    printNumberOfOwnedStocks(list);

    char input[10];
    printf("Enter stock ticker symbol: ");
    scanf("%s\n",input);
    printSpecificTicker(list, input);

}

int main() {
    FILE* output;
    DIR* directory = opendir(".");
    struct dirent* dirEntryPtr;
    int userInput = -1; // must be set to enter loop
    int i = 0;
    linked_list_t list;
    node_t* nPtr;

    // reads *.bin into the list
    createList(&list, directory, dirEntryPtr);

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
                report(directory, dirEntryPtr, &list);
                break;
            case 2:
                //buy();
                break;
            case 3:
                //sell()
                break;
            default:
                printf("Please enter a valid input.\n");
                userInput = -1; // in case the user inputs a non-int
                break;
        }
    }
    free(dirEntryPtr);
    // fclose(output);
    closedir(directory);
    deleteList(&list);
    
    return 0;
}
