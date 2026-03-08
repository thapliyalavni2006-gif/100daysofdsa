/*Circular Queue Using Array - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of elements to enqueue)
- Second line: n space-separated integers
- Third line: integer m (number of dequeue operations)

Output:
- Print queue elements from front to rear after operations, space-separated

Example:
Input:
5
10 20 30 40 50
2

Output:
30 40 50 10 20
*/

#include <stdio.h>
#include <stdlib.h>

// Node structure for circular queue
struct Node {
    int data;
    struct Node* next;
};

// Circular queue structure
typedef struct {
    struct Node* rear;  // Only need rear pointer for circular queue
} CircularQueue;

// Initialize circular queue
void initQueue(CircularQueue* q) {
    q->rear = NULL;
}

// Check if queue is empty
int isEmpty(CircularQueue* q) {
    return q->rear == NULL;
}

// Enqueue (insert at rear)
void enqueue(CircularQueue* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    
    if(isEmpty(q)) {
        // First node points to itself
        newNode->next = newNode;
        q->rear = newNode;
    } else {
        // Insert after rear
        newNode->next = q->rear->next;  // Point to front
        q->rear->next = newNode;         // Old rear points to new node
        q->rear = newNode;               // Update rear
    }
}

// Dequeue (remove from front)
int dequeue(CircularQueue* q) {
    if(isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    
    struct Node* front = q->rear->next;
    int value = front->data;
    
    if(front == q->rear) {
        // Only one node
        free(front);
        q->rear = NULL;
    } else {
        // Multiple nodes
        q->rear->next = front->next;
        free(front);
    }
    
    return value;
}

// Display queue
void display(CircularQueue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    
    struct Node* temp = q->rear->next;  // Start from front
    
    do {
        printf("%d", temp->data);
        if(temp != q->rear) {
            printf(" ");
        }
        temp = temp->next;
    } while(temp != q->rear->next);
    
    printf("\n");
}

int main() {
    CircularQueue q;
    initQueue(&q);
    
    int n, m;
    
    // Read number of elements to enqueue
    scanf("%d", &n);
    
    // Enqueue n elements
    for(int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        enqueue(&q, value);
    }
    
    // Read number of dequeue operations
    scanf("%d", &m);
    
    // Perform m dequeue operations
    for(int i = 0; i < m; i++) {
        dequeue(&q);
    }
    
    // Display remaining elements
    display(&q);
    
    return 0;
}