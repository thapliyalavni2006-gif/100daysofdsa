/*Perform inorder, preorder, and postorder traversals of a given binary tree.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 represents NULL)

Output Format:
- Print inorder, preorder, and postorder traversals
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int val) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->val = val;
    n->left = n->right = NULL;
    return n;
}

Node* buildTree(int* arr, int size) {
    if (size == 0 || arr[0] == -1) return NULL;

    Node** queue = (Node**)malloc(size * sizeof(Node*));
    int front = 0, rear = 0;

    Node* root = newNode(arr[0]);
    queue[rear++] = root;
    int i = 1;

    while (front < rear && i < size) {
        Node* node = queue[front++];

        // Left child
        if (i < size) {
            if (arr[i] != -1) {
                node->left = newNode(arr[i]);
                queue[rear++] = node->left;
            }
            i++;
        }

        // Right child
        if (i < size) {
            if (arr[i] != -1) {
                node->right = newNode(arr[i]);
                queue[rear++] = node->right;
            }
            i++;
        }
    }

    free(queue);
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}

void freeTree(Node* root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    int n;
    scanf("%d", &n);

    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    Node* root = buildTree(arr, n);
    free(arr);

    printf("Inorder:   "); inorder(root);   printf("\n");
    printf("Preorder:  "); preorder(root);  printf("\n");
    printf("Postorder: "); postorder(root); printf("\n");

    freeTree(root);
    return 0;
}
