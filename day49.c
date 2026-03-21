#include <stdio.h>
#include <stdlib.h>

// BST Node structure
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a value into the BST
Node* insert(Node* root, int data) {
    // Base case: empty tree or reached a leaf position
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insert(root->left, data);   // Go left
    } else if (data > root->data) {
        root->right = insert(root->right, data); // Go right
    }
    // If data == root->data, duplicate — do nothing

    return root;
}

// In-order traversal (Left → Root → Right) — prints sorted order
void inorder(Node* root) {
    if (root == NULL) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

// Free the entire tree
void freeTree(Node* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    Node* root = NULL;

    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        int val;
        scanf("%d", &val);
        root = insert(root, val);
    }

    printf("In-order traversal: ");
    inorder(root);
    printf("\n");

    freeTree(root);
    return 0;
}
