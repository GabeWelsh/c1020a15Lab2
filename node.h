#ifndef NODE_T
#define NODE_T

#include "stock.h"
typedef struct node_t {
    stock_t stock;
    struct node_t* nextPtr;
    struct node_t* previousPtr;
} node_t;

node_t* initNode(stock_t stock);
void deleteNode(stock_t stock);
#endif
