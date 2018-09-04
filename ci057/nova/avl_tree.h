#include "common.h"

#pragma once

typedef struct avl {
	int data;
	struct avl *left;
	struct avl *right;
	int height;
} avl_t, *avl_p, **avl_pp;

/* Generate AVL tree from an array of input values */
avl_pp generate_avl(int *arr, int len);

/* Initialize an AVL tree */
avl_pp init_avl(void);

/* Insert a node in AVL tree */
bool insert_avl_node(avl_pp head, int val);

/* Delete a node from AVL tree */
bool delete_avl_node(avl_pp head, int val);

/* Destroy the tree */
int destroy_avl(avl_pp head);

/* Print a tree in preorder */
int print_avl(avl_p root, avl_p parent);

/* Traverse tree in BFS to find a given value */
bool search_BFS_avl(avl_pp root, int val, bool stop);
