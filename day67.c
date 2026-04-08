/*Print topological ordering of a Directed Acyclic Graph (DAG) using DFS.*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Adjacency list node
struct Node {
    int dest;
    struct Node* next;
};

// Graph structure
struct Graph {
    int vertices;
    struct Node* adjList[MAX];
};

// Stack structure
int stack[MAX];
int stackTop = -1;

void push(int val) {
    stack[++stackTop] = val;
}

int pop() {
    return stack[stackTop--];
}

// Create a new adjacency list node
struct Node* createNode(int dest) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Create a graph with 'vertices' number of vertices
struct Graph* createGraph(int vertices) {
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->vertices = vertices;
    for (int i = 0; i < vertices; i++)
        graph->adjList[i] = NULL;
    return graph;
}

// Add a directed edge u -> v
void addEdge(struct Graph* graph, int u, int v) {
    struct Node* newNode = createNode(v);
    newNode->next = graph->adjList[u];
    graph->adjList[u] = newNode;
}

// DFS-based recursive helper
void dfs(struct Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;

    struct Node* temp = graph->adjList[vertex];
    while (temp) {
        if (!visited[temp->dest])
            dfs(graph, temp->dest, visited);
        temp = temp->next;
    }

    // Push to stack AFTER visiting all descendants
    push(vertex);
}

// Perform topological sort
void topologicalSort(struct Graph* graph) {
    int visited[MAX] = {0};

    // Call DFS for every unvisited vertex
    for (int i = 0; i < graph->vertices; i++) {
        if (!visited[i])
            dfs(graph, i, visited);
    }

    // Pop from stack to get topological order
    printf("Topological Order: ");
    while (stackTop != -1)
        printf("%d ", pop());
    printf("\n");
}

// Driver code
int main() {
    struct Graph* graph = createGraph(6);

    addEdge(graph, 5, 2);
    addEdge(graph, 5, 0);
    addEdge(graph, 4, 0);
    addEdge(graph, 4, 1);
    addEdge(graph, 2, 3);
    addEdge(graph, 3, 1);

    topologicalSort(graph);

    return 0;
}