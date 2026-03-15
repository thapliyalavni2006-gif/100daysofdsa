/*Construct a Binary Tree from the given level-order traversal.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers (-1 represents NULL)

Output Format:
- Print inorder traversal of the constructed tree

Example:
Input:
7
1 2 3 4 5 -1 6

Output:
4 2 5 1 3 6*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int val) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

void inorder(struct Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    if (arr[0] == -1) return 0;

    struct Node* queue[n];
    int front = 0, rear = 0;

    struct Node* root = newNode(arr[0]);
    queue[rear++] = root;

    int i = 1;
    while (front < rear && i < n) {
        struct Node* curr = queue[front++];

        // Left child
        if (i < n) {
            if (arr[i] != -1) {
                curr->left = newNode(arr[i]);
                queue[rear++] = curr->left;
            }
            i++;
        }

        // Right child
        if (i < n) {
            if (arr[i] != -1) {
                curr->right = newNode(arr[i]);
                queue[rear++] = curr->right;
            }
            i++;
        }
    }

    inorder(root);
    return 0;
}