/* Given weighted graph with non-negative edges, compute shortest path from source using priority queue.*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 100

// ─── Structures ───────────────────────────────────────────────────────────────

typedef struct Edge {
    int dest, weight;
    struct Edge* next;
} Edge;

typedef struct {
    int vertex, dist;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size, capacity;
} MinHeap;

typedef struct {
    Edge* head[MAX_VERTICES];
    int V;
} Graph;

// ─── Graph ────────────────────────────────────────────────────────────────────

Graph* createGraph(int V) {
    Graph* g = malloc(sizeof(Graph));
    g->V = V;
    for (int i = 0; i < V; i++) g->head[i] = NULL;
    return g;
}

void addEdge(Graph* g, int src, int dest, int weight) {
    Edge* e = malloc(sizeof(Edge));
    e->dest = dest;
    e->weight = weight;
    e->next = g->head[src];
    g->head[src] = e;

    // Undirected: add reverse edge
    e = malloc(sizeof(Edge));
    e->dest = src;
    e->weight = weight;
    e->next = g->head[dest];
    g->head[dest] = e;
}

// ─── Min-Heap ─────────────────────────────────────────────────────────────────

MinHeap* createHeap(int cap) {
    MinHeap* h = malloc(sizeof(MinHeap));
    h->data = malloc(cap * sizeof(HeapNode));
    h->size = 0;
    h->capacity = cap;
    return h;
}

void swap(HeapNode* a, HeapNode* b) { HeapNode t = *a; *a = *b; *b = t; }

void heapifyUp(MinHeap* h, int i) {
    while (i > 0) {
        int parent = (i - 1) / 2;
        if (h->data[parent].dist > h->data[i].dist) {
            swap(&h->data[parent], &h->data[i]);
            i = parent;
        } else break;
    }
}

void heapifyDown(MinHeap* h, int i) {
    int smallest = i, l = 2*i+1, r = 2*i+2;
    if (l < h->size && h->data[l].dist < h->data[smallest].dist) smallest = l;
    if (r < h->size && h->data[r].dist < h->data[smallest].dist) smallest = r;
    if (smallest != i) {
        swap(&h->data[i], &h->data[smallest]);
        heapifyDown(h, smallest);
    }
}

void push(MinHeap* h, int vertex, int dist) {
    h->data[h->size++] = (HeapNode){vertex, dist};
    heapifyUp(h, h->size - 1);
}

HeapNode pop(MinHeap* h) {
    HeapNode top = h->data[0];
    h->data[0] = h->data[--h->size];
    heapifyDown(h, 0);
    return top;
}

// ─── Dijkstra ─────────────────────────────────────────────────────────────────

void dijkstra(Graph* g, int src) {
    int V = g->V;
    int dist[MAX_VERTICES], prev[MAX_VERTICES], visited[MAX_VERTICES];

    for (int i = 0; i < V; i++) {
        dist[i]    = INT_MAX;
        prev[i]    = -1;
        visited[i] = 0;
    }
    dist[src] = 0;

    MinHeap* h = createHeap(V * V);
    push(h, src, 0);

    while (h->size > 0) {
        HeapNode cur = pop(h);
        int u = cur.vertex;

        if (visited[u]) continue;   // stale entry — skip
        visited[u] = 1;

        for (Edge* e = g->head[u]; e; e = e->next) {
            int v = e->dest, w = e->weight;
            if (!visited[v] && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
                push(h, v, dist[v]);
            }
        }
    }

    // ── Print results ──
    printf("\n  Dijkstra from source: %d\n", src);
    printf("  %-10s %-12s %s\n", "Vertex", "Distance", "Path");
    printf("  %-10s %-12s %s\n", "------", "--------", "----");

    for (int i = 0; i < V; i++) {
        printf("  %-10d ", i);
        if (dist[i] == INT_MAX) {
            printf("%-12s unreachable\n", "INF");
            continue;
        }
        printf("%-12d ", dist[i]);

        // Reconstruct path via prev[]
        int path[MAX_VERTICES], len = 0, cur2 = i;
        while (cur2 != -1) { path[len++] = cur2; cur2 = prev[cur2]; }
        for (int j = len - 1; j >= 0; j--)
            printf("%d%s", path[j], j ? " -> " : "\n");
    }

    free(h->data);
    free(h);
}

// ─── Driver ───────────────────────────────────────────────────────────────────

int main(void) {
    /*
     *  Graph layout:
     *
     *      0 ──(4)── 1 ──(1)── 2
     *      |         |         |
     *     (8)       (2)       (5)
     *      |         |         |
     *      7 ──(1)── 6 ──(6)── 5 ──(2)── 3
     *      |                             |
     *     (7)                           (9)
     *      |                             |
     *      8 ──────────(10)──────────── 4
     */
    Graph* g = createGraph(9);
    addEdge(g, 0, 1, 4);
    addEdge(g, 0, 7, 8);
    addEdge(g, 1, 2, 8);
    addEdge(g, 1, 7, 11);
    addEdge(g, 2, 3, 7);
    addEdge(g, 2, 5, 4);
    addEdge(g, 2, 8, 2);
    addEdge(g, 3, 4, 9);
    addEdge(g, 3, 5, 14);
    addEdge(g, 4, 5, 10);
    addEdge(g, 5, 6, 2);
    addEdge(g, 6, 7, 1);
    addEdge(g, 6, 8, 6);
    addEdge(g, 7, 8, 7);

    dijkstra(g, 0);
    return 0;
}