#ifndef STOCK_T
#define STOCK_T

#include "date.h"
#include <stdio.h>
#define MAX_TICKER_LENGTH 6

typedef struct stock_t {
   char ticker[MAX_TICKER_LENGTH];
   date_t date; // date bought
   int numShares;
   double pricePerShare;
} stock_t;

// prints a stock in a purdy format:
// <stock name>      <month/day/year>    <numShares>      $   <pricePerShare>
void printStock( const stock_t* stock);
// reads value from given file to a stock
void readIntoStock( stock_t* stock, FILE* filePtr);
// filePtr is in append/write mode and valid
// returns 0 if success, 1 otherwise
int writeStockToFile(stock_t* stock, FILE* filePtr);

#endif
