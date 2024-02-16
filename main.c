/* Name: main.c
 * Description: contains main function
*/
#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "date.h"
#include "node.h"
#include "stock.h"

int main() {
    FILE* output;
    int userInput;

    output = fopen("GOOG.bin","rb");
    
    while (!feof(output)) {
        printf("aaa\n");
    }
    //printf("Welcome to YourTrade.com\n");
    //printf("Reporting, buying or selling?\n");
    //printf("(0=quit, 1=report, 2=buy, 3=sell): ");
    //scanf("%d\n", &userInput);

    //do {
//
    //} while( userInput != 0);
    fclose(output);
    // printf("Thank you for trading with YourTrade.com\n");
    return 0;
}
