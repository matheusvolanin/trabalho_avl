#include <stdlib.h>
#include <stdio.h>
#include "bin-tree.h"

/*
 *  adds a new node in the tree
 *  don't store duplicate keys
 */
binTree* insertNode(binTree *tree, keyType key){

    if(!tree){
        binTree *t = (binTree*)calloc(1, sizeof(binTree));
        t->key = key;
        t->left = t->right = NULL;
        return t;
    }
    else if(tree->key > key){
        tree->left = insertNode(tree->left, key);
        return tree;
    }
    else if(tree->key < key){
        tree->right = insertNode(tree->right, key);
        return tree;
    }
    else{
        return tree;
    }
}

/*
 *  remove the node that store the key
 * */
binTree* removeNode(binTree *tree, keyType key){

    if(tree){
        if(tree->key > key){
            tree->left = removeNode(tree->left, key);
            return tree;
        }
        else if(tree->key < key){
            tree->right = removeNode(tree->right, key);
            return tree;
        }
        else{
            binTree *aux = NULL;
            if(tree->left){
                if(tree->right){
                    if(tree->left->right){
                        aux = removeMaxKey(tree->left);
                        aux->left = tree->left;
                        aux->right = tree->right;
                        free(tree);
                        return aux;
                    }
                    else{
                        aux = tree->left;
                        aux->right = tree->right;
                        free(tree);
                        return aux;
                    }
                }
                else{
                    aux = tree->left;
                    free(tree);
                    return aux;
                }
            }
            else if(tree->right){
                aux = tree->right;
                free(tree);
                return aux;
            }
            else{
                free(tree);
                return NULL;
            }
        }
    }
}

binTree* removeMaxKey(binTree *tree){

    binTree *a = tree, *b = tree->right;
    while(a->right->right){
        a = b;
        b = b->right;
    }
    a -> right = b->left;
    return b;
}

binTree* findNode(binTree *tree, keyType key){

    if(!tree){
        return NULL;
    }
    else if(tree->key > key){
        return findNode(tree->left, key);
    }
    else if(tree->key < key){
        return findNode(tree->right, key);
    }
    else{
        return tree;
    }
}

binTree* findMinKey(binTree *tree){

    if(tree){
        binTree *aux = tree;
        while(aux->left){
            aux = aux->left;
        }
        return aux;
    }
    return NULL;
}

binTree* findMaxKey(binTree *tree){

    if(tree){
        binTree *aux = tree;
        while(aux->right){
            aux = aux->right;
        }
        return aux;
    }
    return NULL;
}

void printPreOrder(binTree *tree){

    if(tree){
        printf("%d ", tree->key);
        printPreOrder(tree->left);
        printPreOrder(tree->right);
    }
}

void printInOrder(binTree *tree){

    if(tree){
        printInOrder(tree->left);
        printf("%d ", tree->key);
        printInOrder(tree->right);
    }
}

void printPostOrder(binTree *tree){

    if(tree){
        printPostOrder(tree->left);
        printPostOrder(tree->right);
        printf("%d ", tree->key);
    }
}

binTree* freeTree(binTree *tree){

    if(tree){
        tree->left = freeTree(tree->left);
        tree->right = freeTree(tree->right);
        free(tree);
        return NULL;
    }
}

int main(){

    int key, i;
    binTree *root = NULL;
    for(i = 0; i < 5; i++){
        scanf("%d", &key);
        root = insertNode(root, key);
    }
    binTree *aux = findMinKey(root);
    printInOrder(root);
    while(aux){
        root = removeNode(root, aux->key);
        aux = findMinKey(root);
    }
    return 0;
}
