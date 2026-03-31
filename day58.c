/*Construct a binary tree from given preorder and inorder traversal arrays.

Input Format:
- First line contains integer N
- Second line contains preorder traversal
- Third line contains inorder traversal

Output Format:
- Print postorder traversal of constructed tree

Example:
Input:
5
1 2 4 5 3
4 2 5 1 3

Output:
4 5 2 3 1
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int search(int inorder[], int start, int end, int value) {
    for (int i = start; i <= end; i++)
        if (inorder[i] == value) return i;
    return -1;
}

int preIndex = 0;

struct Node* buildTree(int preorder[], int inorder[], int inStart, int inEnd) {
    if (inStart > inEnd) return NULL;

    struct Node* node = newNode(preorder[preIndex++]);
    if (inStart == inEnd) return node;

    int inIdx = search(inorder, inStart, inEnd, node->data);
    node->left  = buildTree(preorder, inorder, inStart, inIdx - 1);
    node->right = buildTree(preorder, inorder, inIdx + 1, inEnd);
    return node;
}

int first = 1;

void postorder(struct Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    if (!first) printf(" ");
    printf("%d", root->data);
    first = 0;
}

int main() {
    int n;
    scanf("%d", &n);

    int preorder[n], inorder[n];
    for (int i = 0; i < n; i++) scanf("%d", &preorder[i]);
    for (int i = 0; i < n; i++) scanf("%d", &inorder[i]);

    struct Node* root = buildTree(preorder, inorder, 0, n - 1);
    postorder(root);
    printf("\n");
    return 0;
}