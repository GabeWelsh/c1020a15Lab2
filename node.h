#ifndef NODE_T
#define NODE_T

typedef struct node_t {
    int i;
    struct node_t* nextPtr;
    struct node_t* previousPtr;
} node_t;

node_t* initNode(int num);

#endif
