/*Build a graph with adjacency list representation. Use linked lists or dynamic arrays.

Input:
- n (vertices)
- m (edges)
- edges (u, v)

Output:
- List of adjacency lists for each vertex*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node *next;
} Node;

typedef struct {
    int   n;
    Node **adj;
} Graph;

Node *make_node(int v) {
    Node *nd = malloc(sizeof *nd);
    nd->vertex = v;
    nd->next   = NULL;
    return nd;
}

void add_edge(Graph *g, int u, int v) {
    Node *nd = make_node(v);
    if (!g->adj[u]) {
        g->adj[u] = nd;
    } else {
        Node *cur = g->adj[u];
        while (cur->next) cur = cur->next;
        cur->next = nd;
    }
}

Graph *create_graph(int n) {
    Graph *g = malloc(sizeof *g);
    g->n   = n;
    g->adj = calloc(n + 1, sizeof(Node *));
    return g;
}

void free_graph(Graph *g) {
    for (int i = 1; i <= g->n; i++) {
        Node *cur = g->adj[i];
        while (cur) {
            Node *tmp = cur->next;
            free(cur);
            cur = tmp;
        }
    }
    free(g->adj);
    free(g);
}

void print_graph(const Graph *g) {
    printf("\nAdjacency List:\n");
    for (int i = 1; i <= g->n; i++) {
        printf("Vertex %d: HEAD", i);
        for (Node *cur = g->adj[i]; cur; cur = cur->next)
            printf(" -> %d", cur->vertex);
        printf(" -> NULL\n");
    }
}

int main(void) {
    int n, m;

    printf("Enter vertices: ");  scanf("%d", &n);
    printf("Enter edges   : ");  scanf("%d", &m);

    Graph *g = create_graph(n);

    printf("Enter %d edges (u v):\n", m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(g, u, v);   // directed: u -> v only
        add_edge(g, v, u);   // remove this line for directed graph
    }

    print_graph(g);
    free_graph(g);
    return 0;
}