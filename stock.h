#ifndef STOCK_T
#define STOCK_T

#include "date.h"
#define MAX_TICKER_LENGTH 6

typedef struct stock_t {
       char ticker[MAX_TICKER_LENGTH];
          date_t date; // date bought
             int numShares;
                double pricePerShare;
} stock_t;

// add functions for stock_t here
void getStock( stock_t* stock );

#endif
