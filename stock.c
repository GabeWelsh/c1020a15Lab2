/* Name: stock.c
 * Description: functions for `stock_t`
*/
#include "stock.h"
#include <stdio.h>
/*
typedef struct stock_t {
   char ticker[MAX_TICKER_LENGTH];
   date_t date; // date bought
   int numShares;
   double pricePerShare;
} stock_t;
*/

// prints a stock in a purdy format:
// <stock name>      <month/day/year>    <numShares>      $   <pricePerShare>
void printStock( stock_t* stock) {
    printf("%6s     %2d/%2d/%4d %6d       $%8lf\n",
    stock->ticker, stock->date.month, stock->date.day,
    stock->date.year, stock->numShares, stock->pricePerShare);
}
// reads value from given file to a stock
// assumes filePtr is open to a valid file
void readStock( stock_t* stock, FILE* filePtr) {
    fread(stock, sizeof(stock_t), 1, filePtr);
}

