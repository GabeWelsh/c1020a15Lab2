/* Name: stock.c
 * Description: functions for `stock_t`
*/
#include "stock.h"
#include <stdio.h>

// prints a stock in a purdy format:
// <stock name>      <month/day/year>    <numShares>      $   <pricePerShare>
void printStock( const stock_t* stock) {
    printf(" %s     %2d/%2d/%4d   %6d         $%3.2lf\n",
    stock->ticker, stock->date.month, stock->date.day,
    stock->date.year, stock->numShares, stock->pricePerShare);
}
// reads value from given file to a stock
// assumes filePtr is open to a valid file
void readIntoStock( stock_t* stock, FILE* filePtr) {
    fread(stock, sizeof(struct stock_t), 1, filePtr);
}
// filePtr is in append/write mode and valid
// returns 0 if success, 1 otherwise
int writeStockToFile(stock_t* stock, FILE* filePtr) {
    if (fwrite(stock, sizeof(struct stock_t), 1, filePtr) != 1){
        return 1;
    }

    return 0;
}
