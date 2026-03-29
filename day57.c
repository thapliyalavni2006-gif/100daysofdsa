/*Convert a binary tree into its mirror image by swapping left and right children at every node.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print inorder traversal of mirrored tree

Example:
Input:
7
1 2 3 4 5 6 7

Output:
7 3 6 1 5 2 4*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    
    Node** queue = (Node**)malloc(n * sizeof(Node*));
    int front = 0, rear = 0;
    
    Node* root = newNode(arr[0]);
    queue[rear++] = root;
    int i = 1;
    
    while (front < rear && i < n) {
        Node* curr = queue[front++];
        
        if (i < n && arr[i] != -1) {
            curr->left = newNode(arr[i]);
            queue[rear++] = curr->left;
        }
        i++;
        
        if (i < n && arr[i] != -1) {
            curr->right = newNode(arr[i]);
            queue[rear++] = curr->right;
        }
        i++;
    }
    
    free(queue);
    return root;
}

void mirror(Node* root) {
    if (!root) return;
    
    Node* temp = root->left;
    root->left = root->right;
    root->right = temp;
    
    mirror(root->left);
    mirror(root->right);
}

int first = 1;
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    if (!first) printf(" ");
    printf("%d", root->data);
    first = 0;
    inorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);
    
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    
    Node* root = buildTree(arr, n);
    mirror(root);
    inorder(root);
    printf("\n");
    
    free(arr);
    return 0;
}