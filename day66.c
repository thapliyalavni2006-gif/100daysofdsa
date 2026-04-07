/*Detect cycle in directed graph using DFS and recursion stack.

Output:
- YES if cycle exists*/

#include <stdio.h>
#include <stdbool.h>

#define MAX 100

bool visited[MAX], recStack[MAX];
int adj[MAX][MAX], V;

bool dfs(int v) {
    visited[v] = recStack[v] = true;
    for (int i = 0; i < V; i++) {
        if (adj[v][i]) {
            if (!visited[i] && dfs(i)) return true;
            if (recStack[i]) return true;
        }
    }
    recStack[v] = false;
    return false;
}

bool hasCycle() {
    for (int i = 0; i < V; i++)
        if (!visited[i] && dfs(i)) return true;
    return false;
}

int main() {
    int E, u, v;
    scanf("%d %d", &V, &E);
    while (E--) {
        scanf("%d %d", &u, &v);
        adj[u][v] = 1;
    }
    puts(hasCycle() ? "YES" : "NO");
}