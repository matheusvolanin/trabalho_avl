#include <stdio.h>
#include "avl-tree.h"

/*
 *  just a dummy example
 */

int main(){

    avlNode *node = NULL;
    insert(&node, 8);
    insert(&node, 4);
    insert(&node, 9);
    insert(&node, 10);
    insert(&node, 2);
    insert(&node, 6);
    insert(&node, 1);
    insert(&node, 3);
    insert(&node, 5);
    insert(&node, 7);
    printInOrder(&node, 0);
    printf("\n");
    freeTree(&node);
    node = NULL;
    return 0;
}
