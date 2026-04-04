/* Perform DFS starting from a given source vertex using recursion.

Input:
- n
- adjacency list
- starting vertex s

Output:
- DFS traversal order*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int visited[MAX];
int adj[MAX][MAX];
int degree[MAX];

void dfs(int node, int n) {
    visited[node] = 1;
    printf("%d ", node);
    for (int i = 0; i < degree[node]; i++) {
        int neighbor = adj[node][i];
        if (!visited[neighbor]) {
            dfs(neighbor, n);
        }
    }
}

int main() {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        degree[i] = 0;
        visited[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        int x;
        while (scanf("%d", &x) && x != -1) {
            adj[i][degree[i]++] = x;
        }
    }

    int s;
    scanf("%d", &s);

    dfs(s, n);
    printf("\n");

    return 0;
}