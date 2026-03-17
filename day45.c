/*Find the height (maximum depth) of a given binary tree.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 represents NULL)

Output Format:
- Print the height of the tree

Example:
Input:
7
1 2 3 4 5 -1 -1

Output:
3*/

#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

struct TreeNode* newNode(int val) {
    struct TreeNode* node = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    node->val = val;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode* buildTree(int* nodes, int n) {
    if (n == 0 || nodes[0] == -1) return NULL;

    struct TreeNode** queue = (struct TreeNode**)malloc(n * sizeof(struct TreeNode*));
    int front = 0, rear = 0;

    struct TreeNode* root = newNode(nodes[0]);
    queue[rear++] = root;

    int i = 1;
    while (front < rear && i < n) {
        struct TreeNode* node = queue[front++];

        // Left child
        if (i < n) {
            if (nodes[i] != -1) {
                node->left = newNode(nodes[i]);
                queue[rear++] = node->left;
            }
            i++;
        }

        // Right child
        if (i < n) {
            if (nodes[i] != -1) {
                node->right = newNode(nodes[i]);
                queue[rear++] = node->right;
            }
            i++;
        }
    }

    free(queue);
    return root;
}

int height(struct TreeNode* root) {
    if (root == NULL) return 0;
    int left  = height(root->left);
    int right = height(root->right);
    return 1 + (left > right ? left : right);
}

int main() {
    int n;
    scanf("%d", &n);

    int* nodes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &nodes[i]);

    struct TreeNode* root = buildTree(nodes, n);
    printf("%d\n", height(root));

    free(nodes);
    return 0;
}