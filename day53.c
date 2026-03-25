/*Given a binary tree, print its vertical order traversal. Nodes that lie on the same vertical line should be printed together from top to bottom and from left to right.

Input Format:
- First line contains integer N (number of nodes)
- Second line contains N space-separated integers representing level-order traversal (-1 indicates NULL)

Output Format:
- Print nodes column by column from leftmost to rightmost vertical line

Example:
Input:
7
1 2 3 4 5 6 7

Output:
4
2
1 5 6
3
7*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

/* ---------- Binary Tree ---------- */
typedef struct {
    int val, left, right; /* indices into node array; -1 = NULL */
} Node;

Node tree[MAXN];
int node_count = 0;

/* Build tree from level-order input (-1 = NULL).
   Returns root index, or -1 if tree is empty. */
int build_tree(int *vals, int n) {
    if (n == 0 || vals[0] == -1) return -1;

    /* Allocate root */
    tree[0].val = vals[0]; tree[0].left = tree[0].right = -1;
    node_count = 1;

    int queue[MAXN], front = 0, back = 0;
    queue[back++] = 0;
    int i = 1;

    while (front < back && i < n) {
        int idx = queue[front++];

        /* Left child */
        if (i < n) {
            if (vals[i] != -1) {
                tree[node_count].val = vals[i];
                tree[node_count].left = tree[node_count].right = -1;
                tree[idx].left = node_count;
                queue[back++] = node_count++;
            }
            i++;
        }

        /* Right child */
        if (i < n) {
            if (vals[i] != -1) {
                tree[node_count].val = vals[i];
                tree[node_count].left = tree[node_count].right = -1;
                tree[idx].right = node_count;
                queue[back++] = node_count++;
            }
            i++;
        }
    }
    return 0; /* root is always index 0 */
}

/* ---------- Vertical Order Traversal ---------- */

/* BFS queue entry: node index + horizontal distance */
typedef struct { int idx, hd; } Entry;

/* Column store: for each hd, a dynamic list of node values */
#define MAX_HD_RANGE 2001 /* hd in [-1000, +1000] => offset by 1000 */
#define HD_OFFSET    1000

int col[MAX_HD_RANGE][MAXN]; /* col[hd + HD_OFFSET][i] = i-th value */
int col_size[MAX_HD_RANGE];
int min_hd, max_hd;

void vertical_order(int root) {
    if (root == -1) return;

    memset(col_size, 0, sizeof(col_size));
    min_hd = HD_OFFSET; /* track leftmost column seen */
    max_hd = HD_OFFSET; /* track rightmost column seen */

    Entry bfs[MAXN];
    int front = 0, back = 0;

    bfs[back].idx = root; bfs[back].hd = 0; back++;

    while (front < back) {
        Entry cur = bfs[front++];
        int idx = cur.idx, hd = cur.hd;
        int hdi = hd + HD_OFFSET;

        col[hdi][col_size[hdi]++] = tree[idx].val;

        if (hdi < min_hd) min_hd = hdi;
        if (hdi > max_hd) max_hd = hdi;

        if (tree[idx].left != -1) {
            bfs[back].idx = tree[idx].left;
            bfs[back].hd  = hd - 1;
            back++;
        }
        if (tree[idx].right != -1) {
            bfs[back].idx = tree[idx].right;
            bfs[back].hd  = hd + 1;
            back++;
        }
    }

    /* Print columns left to right */
    for (int h = min_hd; h <= max_hd; h++) {
        for (int i = 0; i < col_size[h]; i++) {
            if (i) printf(" ");
            printf("%d", col[h][i]);
        }
        printf("\n");
    }
}

/* ---------- Main ---------- */
int main(void) {
    int n;
    scanf("%d", &n);

    int vals[MAXN];
    for (int i = 0; i < n; i++) scanf("%d", &vals[i]);

    int root = build_tree(vals, n);
    vertical_order(root);

    return 0;
}
