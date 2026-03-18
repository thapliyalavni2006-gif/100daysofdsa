/*Problem: Level Order Traversal

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications*/

#include <stdio.h>
#include <stdlib.h>

// ─── Tree Node ───────────────────────────────────────────
typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* newNode(int val) {
    TreeNode* n = malloc(sizeof(TreeNode));
    n->val = val; n->left = n->right = NULL;
    return n;
}

// ─── Queue for BFS ───────────────────────────────────────
typedef struct {
    TreeNode** data;
    int front, rear, capacity;
} Queue;

Queue* createQueue(int cap) {
    Queue* q = malloc(sizeof(Queue));
    q->data = malloc(cap * sizeof(TreeNode*));
    q->front = q->rear = 0;
    q->capacity = cap;
    return q;
}

void enqueue(Queue* q, TreeNode* node) { q->data[q->rear++] = node; }
TreeNode* dequeue(Queue* q)            { return q->data[q->front++]; }
int queueSize(Queue* q)                { return q->rear - q->front; }
void freeQueue(Queue* q)               { free(q->data); free(q); }

// ─── Level Order Traversal ───────────────────────────────
// Returns a 2D array; levelSizes[i] = number of nodes at level i
// *levelCount is set to the total number of levels
int** levelOrder(TreeNode* root, int* levelCount, int** levelSizes) {
    if (!root) { *levelCount = 0; return NULL; }

    int maxNodes = 10000;
    Queue* q = createQueue(maxNodes);
    enqueue(q, root);

    int** result   = malloc(maxNodes * sizeof(int*));
    *levelSizes    = malloc(maxNodes * sizeof(int));
    *levelCount    = 0;

    while (queueSize(q) > 0) {
        int size = queueSize(q);
        result[*levelCount]          = malloc(size * sizeof(int));
        (*levelSizes)[*levelCount]   = size;

        for (int i = 0; i < size; i++) {
            TreeNode* node = dequeue(q);
            result[*levelCount][i] = node->val;
            if (node->left)  enqueue(q, node->left);
            if (node->right) enqueue(q, node->right);
        }
        (*levelCount)++;
    }

    freeQueue(q);
    return result;
}

// ─── Helpers ─────────────────────────────────────────────
void printResult(int** result, int levelCount, int* levelSizes) {
    printf("[");
    for (int i = 0; i < levelCount; i++) {
        printf("[");
        for (int j = 0; j < levelSizes[i]; j++) {
            printf("%d", result[i][j]);
            if (j < levelSizes[i] - 1) printf(", ");
        }
        printf("]");
        if (i < levelCount - 1) printf(", ");
    }
    printf("]\n");
}

void freeResult(int** result, int levelCount) {
    for (int i = 0; i < levelCount; i++) free(result[i]);
    free(result);
}

// ─── Main ─────────────────────────────────────────────────
int main() {
    int levelCount, *levelSizes;
    int **result;

    //      3
    //     / \
    //    9  20
    //       / \
    //      15   7
    TreeNode* root = newNode(3);
    root->left        = newNode(9);
    root->right       = newNode(20);
    root->right->left = newNode(15);
    root->right->right= newNode(7);

    result = levelOrder(root, &levelCount, &levelSizes);
    printf("Test 1: "); printResult(result, levelCount, levelSizes);
    // [[3], [9, 20], [15, 7]]
    freeResult(result, levelCount); free(levelSizes);

    // Single node
    TreeNode* single = newNode(1);
    result = levelOrder(single, &levelCount, &levelSizes);
    printf("Test 2: "); printResult(result, levelCount, levelSizes);
    // [[1]]
    freeResult(result, levelCount); free(levelSizes);

    // Empty tree
    result = levelOrder(NULL, &levelCount, &levelSizes);
    printf("Test 3: "); printResult(result, levelCount, levelSizes);
    // []

    return 0;
}