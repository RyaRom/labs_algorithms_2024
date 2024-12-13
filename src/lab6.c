#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of an AVL tree node
typedef struct AVLNode {
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// Function prototypes
AVLNode* createNode(int key);
int height(AVLNode* node);
int getBalance(AVLNode* node);
AVLNode* rightRotate(AVLNode* y);
AVLNode* leftRotate(AVLNode* x);
AVLNode* insert(AVLNode* node, int key);
AVLNode* deleteNode(AVLNode* root, int key);
void breadthFirstTraversal(AVLNode* root, int* arr, int* size);
void printTree(AVLNode* root, int level);
void removeOddNodes(AVLNode** root);

// Main function
void lab6() {
    AVLNode* root = NULL;
    int elements[] = {1, 2, 3, 4, 5, 6, 7}; // Example input
    int n = sizeof(elements) / sizeof(elements[0]);

    // Insert elements into the AVL tree
    for (int i = 0; i < n; i++) {
        root = insert(root, elements[i]);
    }

    // Perform cyclic removal of odd nodes
    while (root && (root->left || root->right)) {
        printf("Current Tree:\n");
        printTree(root, 0);
        removeOddNodes(&root);
    }

    printf("Final remaining node: %d\n", root ? root->key : -1);
    return 0;
}

// Utility functions
AVLNode* createNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

int height(AVLNode* node) {
    return node ? node->height : 0;
}

int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

AVLNode* insert(AVLNode* node, int key) {
    if (!node) return createNode(key);

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node; // No duplicate keys allowed
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

AVLNode* deleteNode(AVLNode* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left || !root->right) {
            AVLNode* temp = root->left ? root->left : root->right;
            free(root);
            return temp;
        } else {
            AVLNode* temp = root->right;
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

void breadthFirstTraversal(AVLNode* root, int* arr, int* size) {
    if (!root) return;

    AVLNode* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        AVLNode* current = queue[front++];
        arr[(*size)++] = current->key;

        if (current->left) queue[rear++] = current->left;
        if (current->right) queue[rear++] = current->right;
    }
}

void printTree(AVLNode* root, int level) {
    if (root) {
        printTree(root->right, level + 1);
        for (int i = 0; i < level; i++) printf("    ");
        printf("%d\n", root->key);
        printTree(root->left, level + 1);
    }
}

void removeOddNodes(AVLNode** root) {
    if (!*root) return;

    int arr[100];
    int size = 0;
    breadthFirstTraversal(*root, arr, &size);

    for (int i = 0; i < size; i++) {
        if (arr[i] % 2 != 0) {
            *root = deleteNode(*root, arr[i]);
        }
    }
}
