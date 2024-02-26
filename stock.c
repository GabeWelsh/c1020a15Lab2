/* Name: stock.c
 * Description: functions for `stock_t`
*/
#include "stock.h"
#include <stdio.h>

// prints a stock in a purdy format:
// <stock name>      <month/day/year>    <numShares>      $   <pricePerShare>
// parameter: stock: the stock to be printed
void printStock( const stock_t* stock) {
    printf(" %s     %2d/%2d/%4d   %6d         $%3.2lf\n",
    stock->ticker, stock->date.month, stock->date.day,
    stock->date.year, stock->numShares, stock->pricePerShare);
}
