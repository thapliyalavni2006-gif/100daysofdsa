/*Count Leaf Nodes

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications*/

/*
 * Count Leaf Nodes in a Binary Tree
 *
 * A leaf node is a node with no children (left == NULL && right == NULL).
 *
 * Approaches:
 *   1. Recursive DFS  — O(n) time, O(h) space
 *   2. Iterative BFS  — O(n) time, O(w) space
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─────────────────────────────────────────────
 * Tree Node
 * ───────────────────────────────────────────── */
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *new_node(int val) {
    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->val   = val;
    node->left  = NULL;
    node->right = NULL;
    return node;
}

void free_tree(TreeNode *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

/* ─────────────────────────────────────────────
 * Approach 1: Recursive DFS
 * ───────────────────────────────────────────── */
int count_leaves_recursive(TreeNode *root) {
    if (!root)                              return 0;   /* empty subtree   */
    if (!root->left && !root->right)        return 1;   /* leaf node found */
    return count_leaves_recursive(root->left)
         + count_leaves_recursive(root->right);
}

/* ─────────────────────────────────────────────
 * Approach 2: Iterative BFS  (queue via circular array)
 * ───────────────────────────────────────────── */
#define MAX_NODES 1024

int count_leaves_iterative(TreeNode *root) {
    if (!root) return 0;

    TreeNode *queue[MAX_NODES];
    int front = 0, back = 0;
    int count = 0;

    queue[back++] = root;

    while (front != back) {
        TreeNode *node = queue[front++];

        if (!node->left && !node->right) {
            count++;
        } else {
            if (node->left)  queue[back++] = node->left;
            if (node->right) queue[back++] = node->right;
        }
    }

    return count;
}

/* ─────────────────────────────────────────────
 * Helper: build tree from level-order array
 * Use 0 as a sentinel for "no node" (works for positive-value trees)
 * ───────────────────────────────────────────── */
TreeNode *build_tree(int *vals, int len) {
    if (len == 0 || vals[0] == 0) return NULL;

    TreeNode **nodes = (TreeNode **)calloc(len, sizeof(TreeNode *));
    nodes[0] = new_node(vals[0]);

    for (int i = 1; i < len; i++) {
        if (vals[i] == 0) continue;          /* NULL slot */
        nodes[i] = new_node(vals[i]);

        int parent = (i - 1) / 2;
        if (!nodes[parent]) continue;
        if (i % 2 == 1) nodes[parent]->left  = nodes[i];
        else             nodes[parent]->right = nodes[i];
    }

    TreeNode *root = nodes[0];
    free(nodes);
    return root;
}

/* ─────────────────────────────────────────────
 * Tests
 * ───────────────────────────────────────────── */
typedef struct {
    int        vals[16];
    int        len;
    int        expected;
    const char *desc;
} TestCase;

int main(void) {
    TestCase tests[] = {
        /* vals (0 = NULL),          len, expected, description          */
        { {1,2,3,4,5,0,6},           7,  4, "Standard tree"            },
        { {1},                        1,  1, "Single node (leaf)"       },
        { {0},                        0,  0, "Empty tree"               },
        { {1,2,3},                    3,  2, "Perfect 2-level tree"     },
        { {1,2,3,4,5,6,7},           7,  4, "Perfect 3-level tree"     },
        { {1,2,0,3,0,0,0,4},         8,  1, "Left-skewed tree"         },
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    printf("%-30s %8s %9s %9s %5s\n",
           "Description", "Expected", "Recursive", "Iterative", "Pass");
    printf("%s\n", "─────────────────────────────────────────────────────────────────");

    int all_pass = 1;
    for (int i = 0; i < n; i++) {
        TreeNode *root = build_tree(tests[i].vals, tests[i].len);
        int rec = count_leaves_recursive(root);
        int itr = count_leaves_iterative(root);
        int ok  = (rec == tests[i].expected) && (itr == tests[i].expected);
        if (!ok) all_pass = 0;

        printf("%-30s %8d %9d %9d %5s\n",
               tests[i].desc,
               tests[i].expected,
               rec, itr,
               ok ? "✓" : "✗");

        free_tree(root);
    }

    printf("%s\n", "─────────────────────────────────────────────────────────────────");
    printf("All tests passed: %s\n", all_pass ? "true" : "false");
    return 0;
}