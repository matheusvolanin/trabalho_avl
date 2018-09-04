typedef int keyType;

typedef struct avlNode{
    keyType balance, key;
    struct avlNode *left, *right;
}avlNode;

void rotateLeft(avlNode **node);

void rotateRight(avlNode **node);

int insert(avlNode **node, keyType key);

void printPreOrder(avlNode **node, keyType height);

void printInOrder(avlNode **node, keyType height);

void printPostOrder(avlNode **node, keyType height);

void freeTree(avlNode **node);
