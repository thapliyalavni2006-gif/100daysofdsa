/*Implement topological sorting using in-degree array and queue (Kahnâ€™s Algorithm).*/

#include <stdio.h>
#include <stdlib.h>

// Adjacency list node
typedef struct Node {
    int dest;
    struct Node* next;
} Node;

// Graph structure
typedef struct {
    int V;
    Node** adj;
} Graph;

// Create a new adjacency list node
Node* newNode(int dest) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->dest = dest;
    node->next = NULL;
    return node;
}

// Create a graph with V vertices
Graph* createGraph(int V) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->V = V;
    g->adj = (Node**)calloc(V, sizeof(Node*));
    return g;
}

// Add a directed edge u -> v
void addEdge(Graph* g, int u, int v) {
    Node* node = newNode(v);
    node->next = g->adj[u];
    g->adj[u] = node;
}

// Kahn's Algorithm for Topological Sort
// Returns 1 if successful, 0 if cycle detected
int kahnTopSort(Graph* g, int* result) {
    int V = g->V;

    // Step 1: Compute in-degree for every vertex
    int* inDegree = (int*)calloc(V, sizeof(int));
    for (int u = 0; u < V; u++) {
        for (Node* p = g->adj[u]; p; p = p->next)
            inDegree[p->dest]++;
    }

    // Step 2: Enqueue all vertices with in-degree 0
    int* queue = (int*)malloc(V * sizeof(int));
    int front = 0, rear = 0;

    for (int i = 0; i < V; i++)
        if (inDegree[i] == 0)
            queue[rear++] = i;

    // Step 3: Process the queue
    int count = 0; // tracks how many vertices are placed in result

    while (front < rear) {
        int u = queue[front++];
        result[count++] = u;

        // Reduce in-degree of every neighbor by 1
        for (Node* p = g->adj[u]; p; p = p->next) {
            if (--inDegree[p->dest] == 0)
                queue[rear++] = p->dest;
        }
    }

    free(inDegree);
    free(queue);

    // If count != V, there is a cycle
    return (count == V);
}

// Free graph memory
void freeGraph(Graph* g) {
    for (int i = 0; i < g->V; i++) {
        Node* cur = g->adj[i];
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

// ── Demo ──────────────────────────────────────────────────────────────────────
int main(void) {
    // Example DAG:
    //  5 → 2 → 3 → 1
    //  5 → 0 → 3
    //  4 → 0 → 1
    //  4 → 1
    int V = 6;
    Graph* g = createGraph(V);

    addEdge(g, 5, 2);
    addEdge(g, 5, 0);
    addEdge(g, 4, 0);
    addEdge(g, 4, 1);
    addEdge(g, 2, 3);
    addEdge(g, 3, 1);
    addEdge(g, 0, 3);

    printf("Graph edges:\n");
    printf("  5->2, 5->0, 4->0, 4->1, 2->3, 3->1, 0->3\n\n");

    int* result = (int*)malloc(V * sizeof(int));

    if (kahnTopSort(g, result)) {
        printf("Topological Order (Kahn's Algorithm):\n  ");
        for (int i = 0; i < V; i++)
            printf("%d%s", result[i], i < V - 1 ? " -> " : "\n");
    } else {
        printf("Graph contains a cycle — topological sort not possible.\n");
    }

    // ── Cycle detection demo ───────────────────────────────────────────────
    printf("\n--- Cycle Detection Demo ---\n");
    Graph* cyclic = createGraph(3);
    addEdge(cyclic, 0, 1);
    addEdge(cyclic, 1, 2);
    addEdge(cyclic, 2, 0);   // back-edge creates a cycle

    printf("Graph edges: 0->1, 1->2, 2->0  (cyclic)\n");

    int* result2 = (int*)malloc(3 * sizeof(int));
    if (kahnTopSort(cyclic, result2))
        printf("Topological order found.\n");
    else
        printf("Cycle detected — topological sort not possible.\n");

    free(result);
    free(result2);
    freeGraph(g);
    freeGraph(cyclic);
    return 0;
}