/* Name: node.c
 * Description: define `initNode`
*/
#include "node.h"
#include <stdlib.h>

// parameter: stock to be inserted into the node
// returns pointer to dynamically allocated node_t
node_t* initNode(stock_t stock) {
    node_t* nodePtr = malloc(sizeof(node_t));
    nodePtr->stock = stock;
    return nodePtr;
}
