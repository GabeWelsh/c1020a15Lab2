/* Name: node.c
 * Description: define `initNode`
*/
#include "node.h"
#include <stdlib.h>

node_t* initNode(int num) {
    node_t* nodePtr = malloc(sizeof(node_t));
    nodePtr->i = num;
    return nodePtr;
}
