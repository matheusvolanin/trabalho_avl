#include <stdio.h>
#include "bin-tree.h"

/*
 *  just a dummy example.
 */
int main(){

    int key, i;
    binTree *root = NULL;
    for(i = 0; i < 5; i++){
        scanf("%d", &key);
        root = insertNode(root, key);
    }
    binTree *aux = findMinKey(root);
    while(aux){
        root = removeNode(root, aux->key);
        aux = findMinKey(root);
    }
    return 0;
}
