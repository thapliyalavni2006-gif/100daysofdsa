/* Height of Binary Tree

Implement the solution for this problem.

Input:
- Input specifications

Output:
- Output specifications*/

#include <stdio.h>
#include <stdlib.h>

// ── Tree Node ──────────────────────────────────────────────────────────────

typedef struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ── Core Solution ──────────────────────────────────────────────────────────

/*
 * Returns the height of a binary tree.
 *
 * Height = number of edges on the longest root-to-leaf path.
 *   - Empty tree  → -1  (edge-count convention)
 *   - Single node →  0
 *
 * Time:  O(n)  — every node visited exactly once
 * Space: O(h)  — recursion stack (h = height)
 *               O(log n) balanced | O(n) skewed
 */
int heightOfBinaryTree(TreeNode* root) {
    if (root == NULL)
        return -1;  // base case: empty tree

    int leftHeight  = heightOfBinaryTree(root->left);
    int rightHeight = heightOfBinaryTree(root->right);

    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// ── Helpers ────────────────────────────────────────────────────────────────

TreeNode* newNode(int val) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->val   = val;
    node->left  = NULL;
    node->right = NULL;
    return node;
}

/* Build tree from level-order array. Use -1 to represent NULL nodes. */
TreeNode* buildTree(int* values, int size) {
    if (size == 0 || values[0] == -1) return NULL;

    TreeNode** queue = (TreeNode**)malloc(size * sizeof(TreeNode*));
    int front = 0, back = 0;

    TreeNode* root = newNode(values[0]);
    queue[back++] = root;
    int i = 1;

    while (front < back && i < size) {
        TreeNode* node = queue[front++];

        if (i < size) {
            if (values[i] != -1) {
                node->left = newNode(values[i]);
                queue[back++] = node->left;
            }
            i++;
        }

        if (i < size) {
            if (values[i] != -1) {
                node->right = newNode(values[i]);
                queue[back++] = node->right;
            }
            i++;
        }
    }

    free(queue);
    return root;
}

void freeTree(TreeNode* root) {
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// ── Tests ──────────────────────────────────────────────────────────────────

typedef struct {
    int*  values;
    int   size;
    int   expected;
    char* label;
} TestCase;

void runTests() {
    /* -1 represents NULL in level-order arrays */
    int empty[]    = {};
    int single[]   = {1};
    int perfect2[] = {1, 2, 3};
    int perfect3[] = {1, 2, 3, 4, 5, 6, 7};
    int leftSkew[] = {1, 2, -1, 3, -1, -1, -1, 4};
    int rightSkew[]= {1, -1, 2, -1, -1, -1, 3};
    int unbal[]    = {1, 2, 3, 4, -1, -1, 5};

    TestCase tests[] = {
        { empty,     0, -1, "Empty tree"              },
        { single,    1,  0, "Single node"             },
        { perfect2,  3,  1, "Perfect tree (2 levels)" },
        { perfect3,  7,  2, "Perfect tree (3 levels)" },
        { leftSkew,  8,  3, "Left-skewed"             },
        { rightSkew, 7,  2, "Right-skewed"            },
        { unbal,     7,  2, "Unbalanced"              },
    };

    int n = sizeof(tests) / sizeof(tests[0]);

    printf("%-30s %-10s %-10s %s\n", "Test", "Expected", "Got", "Status");
    printf("%-30s %-10s %-10s %s\n", "----", "--------", "---", "------");

    for (int i = 0; i < n; i++) {
        TreeNode* root   = buildTree(tests[i].values, tests[i].size);
        int       result = heightOfBinaryTree(root);
        int       pass   = (result == tests[i].expected);

        printf("%-30s %-10d %-10d %s\n",
               tests[i].label,
               tests[i].expected,
               result,
               pass ? "✅ PASS" : "❌ FAIL");

        freeTree(root);
    }
}

// ── Main ───────────────────────────────────────────────────────────────────

int main() {
    runTests();

    /* ── Visual walkthrough ──────────────────────────────────────────────
     *
     *         1          ← level 0
     *        / \
     *       2   3        ← level 1
     *      / \
     *     4   5          ← level 2
     *    /
     *   6                ← level 3   →  height = 3
     */
    printf("\nWalkthrough on sample tree:\n");
    printf("        1\n");
    printf("       / \\\n");
    printf("      2   3\n");
    printf("     / \\\n");
    printf("    4   5\n");
    printf("   /\n");
    printf("  6\n\n");

    int vals[]   = {1, 2, 3, 4, 5, -1, -1, 6};
    TreeNode* t  = buildTree(vals, 8);
    printf("heightOfBinaryTree(root) = %d\n", heightOfBinaryTree(t));
    freeTree(t);

    return 0;
}
