#include <stdio.h>
#include <stdlib.h>
#include "avl-tree.h"

/*
 *  A simple left rotate
 */
void rotateLeft(avlNode **node){

    avlNode *a = *node;
    avlNode *b = a->right;
    a->right = b->left;
    b->left = a;
    a->balance = b->balance = 0;
    *node = b;
}

/*
 *  A simple right rotate
 */
void rotateRight(avlNode **node){

    avlNode *a = *node;
    avlNode *b = a->left;
    a->left = b->right;
    b->right = a;
    a->balance = b->balance = 0;
    *node = b;
}

int insert(avlNode **node, int key){

    if(!*node){
        avlNode *newNode = (avlNode*)malloc(sizeof(avlNode));
        if(!newNode){
            printf("\nMALLOC FAILURE");
            exit(0);
        }
        newNode->right = newNode->left = NULL;
        newNode->key = key;
        newNode->balance = 0;
        *node = newNode;
        return 1;
    }
    else if(key < (*node)->key){
        if(insert(&(*node)->left, key)){
            (*node)->balance--;
            switch((*node)->balance){
                case 0:
                    return 0;
                case -1:
                    return 1;
                case -2:
                    if((*node)->left->balance == -1)
                        rotateRight(node);
                    else{
                        switch((*node)->left->right->balance){
                            case -1:
                                rotateLeft(&(*node)->left);
                                rotateRight(node);
                                (*node)->right->balance++;
                                break;
                            case 0:
                                rotateLeft(&(*node)->left);
                                rotateRight(node);
                                break;
                            case 1:
                                rotateLeft(&(*node)->left);
                                rotateRight(node);
                                (*node)->left->balance--;
                                break;
                        }
                    }
                    return 0;
            }
        }
        else
            return 0;
    }
    else{
        if(insert(&(*node)->right, key)){
            (*node)->balance++;
            switch((*node)->balance){
                case 0:
                    return 0;
                case 1:
                    return 1;
                case 2:
                    if((*node)->right->balance == 1)
                        rotateLeft(node);
                    else{
                        switch((*node)->right->left->balance){
                            case -1:
                                rotateRight(&(*node)->right);
                                rotateLeft(node);
                                (*node)->right->balance++;
                                break;
                            case 0:
                                rotateRight(&(*node)->right);
                                rotateLeft(node);
                                break;
                            case 1:
                                rotateRight(&(*node)->right);
                                rotateLeft(node);
                                (*node)->left->balance--;
                                break;
                        }
                    }
                    return 0;
            }
        }
        else
            return 0;
    }
}

void printPreOrder(avlNode **node, int height){

    if(*node){
        printf("key: %d\tbalance: %d\theight: %d\n", (*node)->key, (*node)->balance, height);
        printPreOrder(&(*node)->left, height+1);
        printPreOrder(&(*node)->right, height+1);
    }
}

void printInOrder(avlNode **node, int height){

    if(*node){
        printInOrder(&(*node)->left, height+1);
        printf("key: %d\tbalance: %d\theight: %d\n", (*node)->key, (*node)->balance, height);
        printInOrder(&(*node)->right, height+1);
    }
}

void printPosOrder(avlNode **node, int height){

    if(*node){
        printPosOrder(&(*node)->left, height+1);
        printPosOrder(&(*node)->right, height+1);
        printf("key: %d\tbalance: %d\theight: %d\n", (*node)->key, (*node)->balance, height);
    }
}

int removeNode(avlNode **node, int key){

    if(node){
        if(node->key > key){
            node->left = removeNode(node->left, key);
            return node;
        }
        else if(node->key < key){
            node->right = removeNode(node->right, key);
            return node;
        }
        else{
            binnode *aux = NULL;
            if(node->left){
                if(node->right){
                    if(node->left->right){
                        aux = removeMaxKey(node->left);
                        aux->left = node->left;
                        aux->right = node->right;
                        free(node);
                        return aux;
                    }
                    else{
                        aux = node->left;
                        aux->right = node->right;
                        free(node);
                        return aux;
                    }
                }
                else{
                    aux = node->left;
                    free(node);
                    return aux;
                }
            }
            else if(node->right){
                aux = node->right;
                free(node);
                return aux;
            }
            else{
                free(node);
                return NULL;
            }
        }
    }
}

/*
 *  remove all nodes of the node
 */

void freenode(avlNode **node){
    if(*node){
        freenode(&(*node)->left);
        freenode(&(*node)->right);
        free(*node);
    }
}
