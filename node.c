/* Name: node.c
 * Description: define `initNode`
*/
#include "node.h"
#include <stdlib.h>

node_t* initNode(stock_t stock) {
    node_t* nodePtr = malloc(sizeof(node_t));
    nodePtr->stock = stock;
    return nodePtr;
}
