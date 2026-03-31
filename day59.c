/*Construct a binary tree from given inorder and postorder traversal arrays.

Input Format:
- First line contains integer N
- Second line contains inorder traversal
- Third line contains postorder traversal

Output Format:
- Print preorder traversal of constructed tree

Example:
Input:
5
4 2 5 1 3
4 5 2 3 1

Output:
1 2 4 5 3*/

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

int postIndex;

struct Node* buildTree(int inorder[], int postorder[], int inStart, int inEnd) {
    if (inStart > inEnd) return NULL;

    struct Node* node = newNode(postorder[postIndex--]);
    if (inStart == inEnd) return node;

    // Find root in inorder to split left and right subtrees
    int mid = inStart;
    while (inorder[mid] != node->data) mid++;

    // Right subtree built before left (postIndex goes right to left)
    node->right = buildTree(inorder, postorder, mid + 1, inEnd);
    node->left  = buildTree(inorder, postorder, inStart, mid - 1);

    return node;
}

int first = 1;

void preorder(struct Node* root) {
    if (!root) return;
    if (!first) printf(" ");
    printf("%d", root->data);
    first = 0;
    preorder(root->left);
    preorder(root->right);
}

int main() {
    int n;
    scanf("%d", &n);

    int inorder[n], postorder[n];
    for (int i = 0; i < n; i++) scanf("%d", &inorder[i]);
    for (int i = 0; i < n; i++) scanf("%d", &postorder[i]);

    postIndex = n - 1;  // Start from last element (root)

    struct Node* root = buildTree(inorder, postorder, 0, n - 1);
    preorder(root);
    printf("\n");
    return 0;
}