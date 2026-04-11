/*Compute shortest path from source and detect negative weight cycles using Bellman-Ford.

Input:
- n vertices
- m edges (u,v,w)

Output:
- Shortest distances OR NEGATIVE CYCLE*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INF LLONG_MAX

typedef long long ll;

typedef struct {
    int u, v;
    ll w;
} Edge;

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Edge *edges = malloc(m * sizeof(Edge));
    for (int i = 0; i < m; i++)
        scanf("%d %d %lld", &edges[i].u, &edges[i].v, &edges[i].w);

    int src;
    scanf("%d", &src);

    ll *dist = malloc(n * sizeof(ll));
    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[src] = 0;

    // Relax all edges (n-1) times
    for (int iter = 0; iter < n - 1; iter++) {
        int updated = 0;
        for (int i = 0; i < m; i++) {
            int u = edges[i].u, v = edges[i].v;
            ll  w = edges[i].w;
            if (dist[u] != INF && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                updated = 1;
            }
        }
        if (!updated) break; // Early exit
    }

    // Detect negative-weight cycles (n-th relaxation)
    int neg_cycle = 0;
    for (int i = 0; i < m; i++) {
        int u = edges[i].u, v = edges[i].v;
        ll  w = edges[i].w;
        if (dist[u] != INF && dist[u] + w < dist[v]) {
            neg_cycle = 1;
            break;
        }
    }

    if (neg_cycle) {
        printf("NEGATIVE CYCLE\n");
    } else {
        printf("Shortest distances from vertex %d:\n", src);
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF)
                printf("  %d -> %d : INF\n", src, i);
            else
                printf("  %d -> %d : %lld\n", src, i, dist[i]);
        }
    }

    free(edges);
    free(dist);
    return 0;
}