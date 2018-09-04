#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 4

int max(int a, int b) { return a > b ? a : b; }

typedef struct node
{
	int val;
	struct node *left;
	struct node *right;
	struct node *parent;
	int height;
} nodo_avl;


nodo_avl *find (nodo_avl *root, int val)
{
	if (root == NULL) return NULL;
	if (val < root->val)
		return find(root->left, val);
	else if (val > root->val)
		return find(root->right, val);
	else
		return root;
}

int height(nodo_avl *root)
{
    return root ? root->height : 0;
}

void adjust_height(nodo_avl *root)
{
	root->height = 1 + max(height(root->left), height(root->right));
}

/* We can assume node->left is non-null due to how this is called */
nodo_avl *rotate_right(nodo_avl *root)
{
	/* Fix pointers */
	nodo_avl *new_root = root->left;
	if (root->parent)
	{
		if (root->parent->left == root) root->parent->left = new_root;
		else root->parent->right = new_root;
	}
	new_root->parent = root->parent;
	root->parent = new_root;
	root->left = new_root->right;
    if (root->left) root->left->parent = root;
	new_root->right = root;

	/* Fix heights; root and new_root may be wrong. Do bottom-up */
	adjust_height(root);
	adjust_height(new_root);
	return new_root;
}

/* We can assume node->right is non-null due to how this is called */
nodo_avl *rotate_left(nodo_avl *root)
{
	/* Fix pointers */
	nodo_avl *new_root = root->right;
	if (root->parent)
	{
		if (root->parent->right == root) root->parent->right = new_root;
		else root->parent->left = new_root;
	}
	new_root->parent = root->parent;
	root->parent = new_root;
	root->right = new_root->left;
    if (root->right) root->right->parent = root;
	new_root->left = root;

	/* Fix heights; root and new_root may be wrong */
	adjust_height(root);
	adjust_height(new_root);
	return new_root;
}

nodo_avl *make_node(int val, nodo_avl *parent)
{
	nodo_avl *n = malloc(sizeof(nodo_avl));
	n->val = val;
    n->parent = parent;
	n->height = 1;
	n->left = NULL;
	n->right = NULL;

	return n;
}

nodo_avl *balance(nodo_avl *root)
{
    if (height(root->left) - height(root->right) > 1)
    {
        if (height(root->left->left) > height(root->left->right))
        {
            root = rotate_right(root);
        }
        else
        {
            rotate_left(root->left);
            root = rotate_right(root);
        }
    }
    else if (height(root->right) - height(root->left) > 1)
    {
        if (height(root->right->right) > height(root->right->left))
        {
            root = rotate_left(root);
        }
        else
        {
            rotate_right(root->right);
            root = rotate_left(root);
        }
    }
    return root;
}

nodo_avl *insert(nodo_avl *root, int val)
{
    nodo_avl *current = root;
    while (current->val != val)
    {
        if (val < current->val)
        {
            if (current->left) current = current->left;
            else
            {
                current->left = make_node(val, current);
                current = current->left;
            }
        }
        else if (val > current->val)
        {
            if (current->right) current = current->right;
            else
            {
                current->right = make_node(val, current);
                current = current->right;
            }
        }
        else return root; /* Value was in the tree, dumbass */
    }
    
    do
    {
        current  = current->parent;
        adjust_height(current);
        current = balance(current);
    } while (current->parent);
    
    return current;
}

/* Tests to make sure above code actually works */

void print_tree_indent(nodo_avl *node, int indent)
{
    int ix;
    for (ix = 0; ix < indent; ix++) printf(" ");
    if (node) 
    {
        printf("n: %d, alt: %d\n", node->val, node->height);
        print_tree_indent(node->left, indent + 4);
        print_tree_indent(node->right, indent + 4);
    }
}

void print_tree(nodo_avl *node)
{
    print_tree_indent(node, 0);
}


int main(int argc, char *argv[])
{
	nodo_avl *root;
	char buffer[SIZE];
	char insere[]= "i ";
	char remove[]= "r ";
	int chave;
    
    while (!(feof(stdin))){
    	fgets(buffer,SIZE-1,stdin);
    	scanf ("%d", &chave);
        printf("%s",buffer);
    	root = make_node(1, NULL);
            if (strcmp(buffer,insere) != 0){
    		if (strcmp(buffer,remove) !=0){
    			printf("AT");
    		}
    	else
    		root = insert(root,chave);
    	}
	}
    print_tree(root);
    return 0;
}
