/* Queue Using Array - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of elements)
- Second line: n space-separated integers

Output:
- Print queue elements from front to rear, space-separated

Example:
Input:
5
10 20 30 40 50

Output:
10 20 30 40 50*/

#include <stdio.h>
#include <stdlib.h>

// Node structure for queue
struct Node {
    int data;
    struct Node* next;
};

// Queue structure with front and rear pointers
typedef struct {
    struct Node* front;
    struct Node* rear;
} Queue;

// Initialize queue
void initQueue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Check if queue is empty
int isEmpty(Queue* q) {
    return q->front == NULL;
}

// Enqueue (insert at rear)
void enqueue(Queue* q, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    
    if(isEmpty(q)) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Dequeue (remove from front)
int dequeue(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue Underflow\n");
        return -1;
    }
    
    struct Node* temp = q->front;
    int value = temp->data;
    q->front = q->front->next;
    
    if(q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    return value;
}

// Display queue
void display(Queue* q) {
    if(isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    
    struct Node* temp = q->front;
    while(temp != NULL) {
        printf("%d", temp->data);
        if(temp->next != NULL) {
            printf(" ");
        }
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);
    
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        enqueue(&q, value);
    }
    
    display(&q);
    
    return 0;
}