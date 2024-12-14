#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

AVLNode *createNode(int key);

int height(AVLNode *node);

int getBalance(AVLNode *node);

AVLNode *rightRotate(AVLNode *y);

AVLNode *leftRotate(AVLNode *x);

AVLNode *insert(AVLNode *node, int key);

AVLNode *deleteNode(AVLNode *root, int key);

void printTree(AVLNode *root, int level);

void collectBreadthFirst(AVLNode *root, int *arr, int *size, int *levels);

AVLNode *rebuildTree(int *arr, int size);

void removeOddLevelNodesCyclic(AVLNode **root);

void lab6() {
    AVLNode *root = NULL;
    int elements[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int n = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < n; i++) {
        root = insert(root, elements[i]);
    }

    while (root && (root->left || root->right)) {
        printf("Current Tree:\n");
        printTree(root, 0);
        removeOddLevelNodesCyclic(&root);
    }

    printf("Final remaining node: %d\n", root ? root->key : -1);
}

AVLNode *createNode(int key) {
    AVLNode *node = (AVLNode *) malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(AVLNode *node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode *node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode *rightRotate(AVLNode *y) {
    AVLNode *x = y->left;
    AVLNode *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

AVLNode *leftRotate(AVLNode *x) {
    AVLNode *y = x->right;
    AVLNode *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

AVLNode *insert(AVLNode *node, int key) {
    if (!node) return createNode(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }

    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        return rightRotate(node);
    }
    if (balance < -1 && key > node->right->key) {
        return leftRotate(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

AVLNode *deleteNode(AVLNode *root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left || !root->right) {
            AVLNode *temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            AVLNode *temp = root->right;
            while (temp->left) temp = temp->left;
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    root->height = 1 + (height(root->left) > height(root->right) ? height(root->left) : height(root->right));

    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void printTree(AVLNode *root, int level) {
    if (root) {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++) printf("    ");
        printf("%d\n", root->key);
        printTree(root->left, level + 1);
    }
}

void collectBreadthFirst(AVLNode *root, int *arr, int *size, int *levels) {
    if (!root) return;

    AVLNode *queue[100];
    int levelQueue[100];
    int front = 0, rear = 0;

    queue[rear] = root;
    levelQueue[rear++] = 1;

    while (front < rear) {
        AVLNode *current = queue[front];
        int level = levelQueue[front++];

        arr[*size] = current->key;
        levels[(*size)++] = level;

        if (current->left) {
            queue[rear] = current->left;
            levelQueue[rear++] = level + 1;
        }
        if (current->right) {
            queue[rear] = current->right;
            levelQueue[rear++] = level + 1;
        }
    }
}

AVLNode *rebuildTree(int *arr, int size) {
    AVLNode *newRoot = NULL;
    for (int i = 0; i < size; i++) {
        newRoot = insert(newRoot, arr[i]);
    }
    return newRoot;
}

void removeOddLevelNodesCyclic(AVLNode **root) {
    if (!*root) return;

    int arr[100];
    int levels[100];
    int size = 0;

    collectBreadthFirst(*root, arr, &size, levels);

    int newArr[100];
    int newSize = 0;

    for (int i = 0; i < size; i++) {
        if (levels[i] % 2 == 0) {
            newArr[newSize++] = arr[i];
        }
    }

    *root = rebuildTree(newArr, newSize);
}
