#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXN 100005

typedef struct Edge {
    int to, w, next;
} Edge;

typedef struct {
    int dist, node;
} HeapNode;

Edge edges[MAXN * 2];
int head[MAXN], dist[MAXN], cnt;
int n, m;

void add_edge(int u, int v, int w) {
    edges[cnt] = (Edge){v, w, head[u]};
    head[u] = cnt++;
}

// Min-heap
HeapNode heap[MAXN * 2];
int heap_size = 0;

void push(int d, int node) {
    heap[++heap_size] = (HeapNode){d, node};
    int i = heap_size;
    while (i > 1 && heap[i].dist < heap[i/2].dist) {
        HeapNode tmp = heap[i]; heap[i] = heap[i/2]; heap[i/2] = tmp;
        i /= 2;
    }
}

HeapNode pop() {
    HeapNode top = heap[1];
    heap[1] = heap[heap_size--];
    int i = 1;
    while (1) {
        int smallest = i, l = 2*i, r = 2*i+1;
        if (l <= heap_size && heap[l].dist < heap[smallest].dist) smallest = l;
        if (r <= heap_size && heap[r].dist < heap[smallest].dist) smallest = r;
        if (smallest == i) break;
        HeapNode tmp = heap[i]; heap[i] = heap[smallest]; heap[smallest] = tmp;
        i = smallest;
    }
    return top;
}

void dijkstra(int src) {
    for (int i = 1; i <= n; i++) dist[i] = INT_MAX;
    dist[src] = 0;
    push(0, src);

    while (heap_size > 0) {
        HeapNode cur = pop();
        int u = cur.node, d = cur.dist;
        if (d > dist[u]) continue;
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to, w = edges[e].w;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                push(dist[v], v);
            }
        }
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= n; i++) head[i] = -1;

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        add_edge(u, v, w);
        add_edge(v, u, w);
    }

    int src;
    scanf("%d", &src);
    dijkstra(src);

    for (int i = 1; i <= n; i++)
        printf("%d%c", dist[i], i == n ? '\n' : ' ');

    return 0;
}