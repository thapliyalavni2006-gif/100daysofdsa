/*Find the Lowest Common Ancestor (LCA) of two nodes in a Binary Tree.

Input Format:
- First line contains integer N
- Second line contains level-order traversal (-1 represents NULL)
- Third line contains two node values

Output Format:
- Print the LCA value

Example:
Input:
7
1 2 3 4 5 6 7
4 5

Output:
2*/

#include <stdio.h>
#include <stdlib.h>

// ─── Data Structures ────────────────────────────────────────────────────────

typedef struct TreeNode {
    int val;
    struct TreeNode *left, *right;
} TreeNode;

// Simple queue for level-order tree building
typedef struct {
    TreeNode **data;
    int front, rear, size;
} Queue;

// ─── Queue Helpers ───────────────────────────────────────────────────────────

Queue *createQueue(int cap) {
    Queue *q    = malloc(sizeof(Queue));
    q->data     = malloc(cap * sizeof(TreeNode *));
    q->front    = q->rear = q->size = 0;
    return q;
}

void enqueue(Queue *q, TreeNode *node) { q->data[q->rear++] = node; q->size++; }
TreeNode *dequeue(Queue *q)            { q->size--; return q->data[q->front++]; }
int isEmpty(Queue *q)                  { return q->size == 0; }

// ─── Tree Construction (Level-Order) ─────────────────────────────────────────

TreeNode *newNode(int val) {
    TreeNode *node  = malloc(sizeof(TreeNode));
    node->val       = val;
    node->left      = node->right = NULL;
    return node;
}

TreeNode *buildTree(int *nodes, int n) {
    if (n == 0 || nodes[0] == -1) return NULL;

    TreeNode *root = newNode(nodes[0]);
    Queue *q       = createQueue(n);
    enqueue(q, root);
    int i = 1;

    while (!isEmpty(q) && i < n) {
        TreeNode *curr = dequeue(q);

        // Left child
        if (i < n && nodes[i] != -1) {
            curr->left = newNode(nodes[i]);
            enqueue(q, curr->left);
        }
        i++;

        // Right child
        if (i < n && nodes[i] != -1) {
            curr->right = newNode(nodes[i]);
            enqueue(q, curr->right);
        }
        i++;
    }

    free(q->data);
    free(q);
    return root;
}

// ─── LCA ─────────────────────────────────────────────────────────────────────

TreeNode *lca(TreeNode *root, int p, int q) {
    if (root == NULL)                         // ran off the tree
        return NULL;
    if (root->val == p || root->val == q)     // found one of the targets
        return root;

    TreeNode *left  = lca(root->left,  p, q);
    TreeNode *right = lca(root->right, p, q);

    if (left && right)   return root;         // p and q on opposite sides
    return left ? left : right;               // both in same subtree
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main() {
    int n;
    scanf("%d", &n);

    int *nodes = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        scanf("%d", &nodes[i]);

    int p, q;
    scanf("%d %d", &p, &q);

    TreeNode *root   = buildTree(nodes, n);
    TreeNode *result = lca(root, p, q);

    if (result)
        printf("%d\n", result->val);

    free(nodes);
    return 0;
}
