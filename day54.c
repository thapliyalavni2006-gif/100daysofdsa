/*Perform zigzag (spiral) level order traversal of a binary tree. Alternate levels should be traversed left-to-right and right-to-left.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 indicates NULL)

Output Format:
- Print traversal in zigzag order

Example:
Input:
7
1 2 3 4 5 6 7

Output:
1 3 2 4 5 6 7*/

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

// Build tree from level-order input (-1 = NULL)
Node* buildTree(int* arr, int n) {
    if (n == 0 || arr[0] == -1) return NULL;
    Node* root = newNode(arr[0]);
    Node* queue[1000];
    int front = 0, rear = 0;
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
    return root;
}

void zigzagTraversal(Node* root) {
    if (!root) return;

    // Two stacks to alternate directions
    Node* stack1[1000], *stack2[1000];
    int top1 = -1, top2 = -1;
    int first = 1; // 1 = left-to-right

    stack1[++top1] = root;

    while (top1 != -1 || top2 != -1) {
        if (first) {
            // Process stack1, push children to stack2 (right then left for next level R-to-L)
            while (top1 != -1) {
                Node* curr = stack1[top1--];
                printf("%d ", curr->data);
                if (curr->right) stack2[++top2] = curr->right;
                if (curr->left)  stack2[++top2] = curr->left;
            }
        } else {
            // Process stack2, push children to stack1 (left then right for next level L-to-R)
            while (top2 != -1) {
                Node* curr = stack2[top2--];
                printf("%d ", curr->data);
                if (curr->left)  stack1[++top1] = curr->left;
                if (curr->right) stack1[++top1] = curr->right;
            }
        }
        first = !first;
    }
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    int arr[1000];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    Node* root = buildTree(arr, n);
    zigzagTraversal(root);
    return 0;
}