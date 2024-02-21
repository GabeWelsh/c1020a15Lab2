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

int endsWithBin(const char *str) {
    int str_len = strlen(str);
    int suffix_len = strlen(".bin");
    if (str_len < suffix_len) {
        return 0;
    }
    return strncmp(str + str_len - suffix_len, ".bin", suffix_len) == 0;
}

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
 * Compare the input given to file names then read the file that was selected.
 * If the user provides bad input, give them a warning and ask for a reinput.
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
void report(DIR* directory, struct dirent* dirEntryPtr, linked_list_t* list);


int main() {
    FILE* output;
    DIR* directory = opendir(".");
    struct dirent* dirEntryPtr;
    int userInput = -1; // must be set to enter loop
    int i = 0;
    linked_list_t list;
    node_t* nPtr;
    createList(&list);
    stock_t stockList[3];

    //// use when reading
    while( (dirEntryPtr = readdir(directory)) != NULL) {
        // if d_name ends in .bin
        // fopen the file and make sure it's not NULL
        // use readStock()
        if (endsWithBin(dirEntryPtr->d_name)) {
            output = fopen(dirEntryPtr->d_name, "rb");
            if (output != NULL) {
                readStock(&stockList[i], output);
                printStock(&stockList[i]);
            }
            i++;
        }
    }

    printf("Ticker  Purchase Date   Shares   Price Per Share\n------------------------------------------------\n");
    for (int j = 0; j < 3; j++) {
        printStock(&stockList[j]);
    }

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
                //report(directory);
                break;
            case 2:
                //buy();
                break;
            case 3:
                //sell()
                break;
            default:
                printf("Enter a valid input.\n");
                break;
        }
    }
    free(dirEntryPtr);
    fclose(output);
    closedir(directory);
    
    return 0;
}
