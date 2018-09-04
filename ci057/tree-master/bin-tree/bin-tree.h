typedef int keyType;

typedef struct binTree{
    keyType key;
    struct binTree *left, *right;
}binTree;

binTree* insertNode(binTree *tree, keyType key);

binTree* removeNode(binTree *tree, keyType key);

binTree* removeMaxKey(binTree *tree);

binTree* freeTree(binTree *tree);

binTree* findNode(binTree *tree, keyType key);

binTree* findMinKey(binTree *tree);

binTree* findMaxKey(binTree *tree);

void printPreOrder(binTree *tree);

void printInOrder(binTree *tree);

void printPostOrder(binTree *tree);
