#ifndef STOCK_T
#define STOCK_T

#include <dirent.h>
#include "date.h"
#include "list.h"
#define MAX_TICKER_LENGTH 6

typedef struct stock_t {
       char ticker[MAX_TICKER_LENGTH];
          date_t date; // date bought
             int numShares;
                double pricePerShare;
} stock_t;

void getStock( stock_t* stock );
void report(DIR* directory);
void buy(linked_list_t *list);
void sell();

#endif
