/*Using BFS or DFS, check if the entire graph is connected.

Input Format
n m
edges

Output Format
CONNECTED
NOT CONNECTED

Sample Input
4 2
1 2
3 4

Sample Output
NOT CONNECTED*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 1005

int adj[MAXN][MAXN], degree[MAXN];
int visited[MAXN];
int queue[MAXN * MAXN];
int n, m;

void bfs(int start) {
    int front = 0, rear = 0;
    queue[rear++] = start;
    visited[start] = 1;

    while (front < rear) {
        int node = queue[front++];
        for (int i = 0; i < degree[node]; i++) {
            int neighbor = adj[node][i];
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);

    memset(adj, 0, sizeof(adj));
    memset(degree, 0, sizeof(degree));
    memset(visited, 0, sizeof(visited));

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][degree[u]++] = v;
        adj[v][degree[v]++] = u;
    }

    bfs(1);

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            printf("NOT CONNECTED\n");
            return 0;
        }
    }

    printf("CONNECTED\n");
    return 0;
}