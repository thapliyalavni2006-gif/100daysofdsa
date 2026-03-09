/*Implement a Priority Queue using an array. An element with smaller value has higher priority.

Supported Operations:
- insert x
- delete
- peek

Input Format:
- First line contains integer N
- Next N lines contain operations

Output Format:
- Print the deleted or peeked element
- Print -1 if the queue is empty*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int size;
} PriorityQueue;

// Initialize priority queue
void initQueue(PriorityQueue* pq) {
    pq->size = 0;
}

// Check if queue is empty
int isEmpty(PriorityQueue* pq) {
    return pq->size == 0;
}

// Check if queue is full
int isFull(PriorityQueue* pq) {
    return pq->size == MAX_SIZE;
}

// Insert element (maintain sorted order - smaller value = higher priority)
void insert(PriorityQueue* pq, int value) {
    if(isFull(pq)) {
        printf("Queue Overflow\n");
        return;
    }
    
    // Find position to insert (maintain ascending order)
    int i;
    for(i = pq->size - 1; i >= 0 && pq->arr[i] > value; i--) {
        pq->arr[i + 1] = pq->arr[i];  // Shift right
    }
    
    pq->arr[i + 1] = value;
    pq->size++;
}

// Delete highest priority element (smallest value)
int delete(PriorityQueue* pq) {
    if(isEmpty(pq)) {
        return -1;
    }
    
    // Smallest element is at index 0
    int value = pq->arr[0];
    
    // Shift all elements left
    for(int i = 0; i < pq->size - 1; i++) {
        pq->arr[i] = pq->arr[i + 1];
    }
    
    pq->size--;
    return value;
}

// Peek highest priority element
int peek(PriorityQueue* pq) {
    if(isEmpty(pq)) {
        return -1;
    }
    return pq->arr[0];  // Smallest element
}

int main() {
    PriorityQueue pq;
    initQueue(&pq);
    
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        char operation[10];
        scanf("%s", operation);
        
        if(strcmp(operation, "insert") == 0) {
            int value;
            scanf("%d", &value);
            insert(&pq, value);
        } else if(strcmp(operation, "delete") == 0) {
            int result = delete(&pq);
            printf("%d\n", result);
        } else if(strcmp(operation, "peek") == 0) {
            int result = peek(&pq);
            printf("%d\n", result);
        }
    }
    
    return 0;
}