/*Given weighted undirected graph, compute total weight of Minimum Spanning Tree using Prim’s algorithm.

Input Format
n m
u v w
...

Output Format
Total weight of MST.

Sample Input
4 5
1 2 3
1 3 5
2 3 1
2 4 4
3 4 2

Sample Output
6*/

#include <stdio.h>
#include <limits.h>

#define MAXN 105

int n, m;
int graph[MAXN][MAXN];
int key[MAXN];
int inMST[MAXN];

int main() {
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            graph[i][j] = INT_MAX;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        if (graph[u][v] > w) {
            graph[u][v] = w;
            graph[v][u] = w;
        }
    }

    for (int i = 1; i <= n; i++) {
        key[i] = INT_MAX;
        inMST[i] = 0;
    }
    key[1] = 0;

    long long total = 0;

    for (int iter = 0; iter < n; iter++) {
        // Pick vertex with minimum key not yet in MST
        int u = -1;
        for (int i = 1; i <= n; i++)
            if (!inMST[i] && (u == -1 || key[i] < key[u]))
                u = i;

        inMST[u] = 1;
        total += key[u];

        // Update keys of adjacent vertices
        for (int v = 1; v <= n; v++)
            if (!inMST[v] && graph[u][v] != INT_MAX && graph[u][v] < key[v])
                key[v] = graph[u][v];
    }

    printf("%lld\n", total);
    return 0;
}