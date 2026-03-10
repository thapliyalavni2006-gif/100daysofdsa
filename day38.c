/* Deque (Double-Ended Queue)

A Deque is a linear data structure that allows insertion and deletion of elements from both the front and the rear. It provides more flexibility than a standard queue or stack.

Common Operations:
1. push_front(value): Insert an element at the front of the deque.
2. push_back(value): Insert an element at the rear of the deque.
3. pop_front(): Remove an element from the front of the deque.
4. pop_back(): Remove an element from the rear of the deque.
5. front(): Return the front element of the deque.
6. back(): Return the rear element of the deque.
7. empty(): Check whether the deque is empty.
8. size(): Return the number of elements in the deque.

Additional Operations:
- clear(): Remove all elements from the deque.
- erase(): Remove one or more elements from the deque.
- swap(): Swap contents of two deques.
- emplace_front(): Insert an element at the front without copying.
- emplace_back(): Insert an element at the rear without copying.
- resize(): Change the size of the deque.
- assign(): Replace elements with new values.
- reverse(): Reverse the order of elements.
- sort(): Sort the elements in ascending order.

Time Complexity:
- push_front, push_back, pop_front, pop_back, front, back, empty, size: O(1)
- clear, erase, resize, assign, reverse: O(n)
- sort: O(n log n)

Input:
- Sequence of deque operations with values (if applicable)

Output:
- Results of operations such as front, back, size, or the final state of the deque after all operations*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Node structure
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Deque structure
typedef struct {
    Node* front;
    Node* rear;
    int size;
} Deque;

// ===== BASIC OPERATIONS =====

// Initialize deque
void initDeque(Deque* dq) {
    dq->front = NULL;
    dq->rear = NULL;
    dq->size = 0;
}

// Check if deque is empty
bool empty(Deque* dq) {
    return dq->size == 0;
}

// Get size of deque
int size(Deque* dq) {
    return dq->size;
}

// 1. Push element at front
void push_front(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->prev = NULL;
    newNode->next = dq->front;
    
    if(empty(dq)) {
        dq->front = newNode;
        dq->rear = newNode;
    } else {
        dq->front->prev = newNode;
        dq->front = newNode;
    }
    
    dq->size++;
    printf("Pushed %d at front\n", value);
}

// 2. Push element at back
void push_back(Deque* dq, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = dq->rear;
    
    if(empty(dq)) {
        dq->front = newNode;
        dq->rear = newNode;
    } else {
        dq->rear->next = newNode;
        dq->rear = newNode;
    }
    
    dq->size++;
    printf("Pushed %d at back\n", value);
}

// 3. Pop element from front
int pop_front(Deque* dq) {
    if(empty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    
    Node* temp = dq->front;
    int value = temp->data;
    
    dq->front = dq->front->next;
    
    if(dq->front == NULL) {
        dq->rear = NULL;
    } else {
        dq->front->prev = NULL;
    }
    
    free(temp);
    dq->size--;
    
    printf("Popped %d from front\n", value);
    return value;
}

// 4. Pop element from back
int pop_back(Deque* dq) {
    if(empty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    
    Node* temp = dq->rear;
    int value = temp->data;
    
    dq->rear = dq->rear->prev;
    
    if(dq->rear == NULL) {
        dq->front = NULL;
    } else {
        dq->rear->next = NULL;
    }
    
    free(temp);
    dq->size--;
    
    printf("Popped %d from back\n", value);
    return value;
}

// 5. Get front element
int front(Deque* dq) {
    if(empty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return dq->front->data;
}

// 6. Get back element
int back(Deque* dq) {
    if(empty(dq)) {
        printf("Deque is empty!\n");
        return -1;
    }
    return dq->rear->data;
}

// ===== ADDITIONAL OPERATIONS =====

// Clear all elements
void clear(Deque* dq) {
    while(!empty(dq)) {
        pop_front(dq);
    }
    printf("Deque cleared\n");
}

// Display deque
void display(Deque* dq) {
    if(empty(dq)) {
        printf("Deque: []\n");
        return;
    }
    
    printf("Deque (front to back): [");
    Node* temp = dq->front;
    while(temp != NULL) {
        printf("%d", temp->data);
        if(temp->next != NULL) printf(", ");
        temp = temp->next;
    }
    printf("] (size=%d)\n", dq->size);
}

// Erase element at specific position
void erase(Deque* dq, int position) {
    if(position < 0 || position >= dq->size) {
        printf("Invalid position!\n");
        return;
    }
    
    if(position == 0) {
        pop_front(dq);
        return;
    }
    
    if(position == dq->size - 1) {
        pop_back(dq);
        return;
    }
    
    Node* temp = dq->front;
    for(int i = 0; i < position; i++) {
        temp = temp->next;
    }
    
    temp->prev->next = temp->next;
    temp->next->prev = temp->prev;
    
    printf("Erased %d at position %d\n", temp->data, position);
    free(temp);
    dq->size--;
}

// Swap contents of two deques
void swap(Deque* dq1, Deque* dq2) {
    Node* tempFront = dq1->front;
    Node* tempRear = dq1->rear;
    int tempSize = dq1->size;
    
    dq1->front = dq2->front;
    dq1->rear = dq2->rear;
    dq1->size = dq2->size;
    
    dq2->front = tempFront;
    dq2->rear = tempRear;
    dq2->size = tempSize;
    
    printf("Swapped deques\n");
}

// Reverse deque
void reverse(Deque* dq) {
    if(empty(dq) || dq->size == 1) {
        return;
    }
    
    Node* temp = dq->front;
    Node* swap = NULL;
    
    // Swap next and prev for all nodes
    while(temp != NULL) {
        swap = temp->prev;
        temp->prev = temp->next;
        temp->next = swap;
        temp = temp->prev;
    }
    
    // Swap front and rear
    swap = dq->front;
    dq->front = dq->rear;
    dq->rear = swap;
    
    printf("Deque reversed\n");
}

// Sort deque in ascending order (bubble sort)
void sort(Deque* dq) {
    if(empty(dq) || dq->size == 1) {
        return;
    }
    
    bool swapped;
    Node* ptr1;
    Node* lptr = NULL;
    
    do {
        swapped = false;
        ptr1 = dq->front;
        
        while(ptr1->next != lptr) {
            if(ptr1->data > ptr1->next->data) {
                int temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while(swapped);
    
    printf("Deque sorted\n");
}

// Resize deque
void resize(Deque* dq, int newSize, int fillValue) {
    while(dq->size > newSize) {
        pop_back(dq);
    }
    
    while(dq->size < newSize) {
        push_back(dq, fillValue);
    }
    
    printf("Resized to %d (fill=%d)\n", newSize, fillValue);
}

// Assign new values
void assign(Deque* dq, int count, int value) {
    clear(dq);
    for(int i = 0; i < count; i++) {
        push_back(dq, value);
    }
    printf("Assigned %d elements with value %d\n", count, value);
}

// Insert at specific position
void insert(Deque* dq, int position, int value) {
    if(position < 0 || position > dq->size) {
        printf("Invalid position!\n");
        return;
    }
    
    if(position == 0) {
        push_front(dq, value);
        return;
    }
    
    if(position == dq->size) {
        push_back(dq, value);
        return;
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    
    Node* temp = dq->front;
    for(int i = 0; i < position; i++) {
        temp = temp->next;
    }
    
    newNode->next = temp;
    newNode->prev = temp->prev;
    temp->prev->next = newNode;
    temp->prev = newNode;
    
    dq->size++;
    printf("Inserted %d at position %d\n", value, position);
}

// Get element at position
int at(Deque* dq, int position) {
    if(position < 0 || position >= dq->size) {
        printf("Invalid position!\n");
        return -1;
    }
    
    Node* temp = dq->front;
    for(int i = 0; i < position; i++) {
        temp = temp->next;
    }
    
    return temp->data;
}

// ===== MAIN DEMO =====
int main() {
    Deque dq;
    initDeque(&dq);
    
    printf("========================================\n");
    printf("      DEQUE IMPLEMENTATION DEMO        \n");
    printf("========================================\n\n");
    
    // Test basic operations
    printf("--- Basic Operations ---\n");
    push_back(&dq, 10);
    push_back(&dq, 20);
    push_front(&dq, 5);
    push_front(&dq, 1);
    display(&dq);
    
    printf("\nFront element: %d\n", front(&dq));
    printf("Back element: %d\n", back(&dq));
    printf("Size: %d\n", size(&dq));
    printf("Empty: %s\n\n", empty(&dq) ? "true" : "false");
    
    // Pop operations
    printf("--- Pop Operations ---\n");
    pop_front(&dq);
    pop_back(&dq);
    display(&dq);
    
    // Insert at position
    printf("\n--- Insert at Position ---\n");
    insert(&dq, 1, 15);
    display(&dq);
    
    // Erase
    printf("\n--- Erase at Position 1 ---\n");
    erase(&dq, 1);
    display(&dq);
    
    // Add more elements
    printf("\n--- Add More Elements ---\n");
    push_back(&dq, 30);
    push_back(&dq, 25);
    push_back(&dq, 35);
    display(&dq);
    
    // Reverse
    printf("\n--- Reverse ---\n");
    reverse(&dq);
    display(&dq);
    
    // Sort
    printf("\n--- Sort ---\n");
    sort(&dq);
    display(&dq);
    
    // Resize
    printf("\n--- Resize to 8 (fill with 0) ---\n");
    resize(&dq, 8, 0);
    display(&dq);
    
    // Access element
    printf("\n--- Access Element ---\n");
    printf("Element at position 3: %d\n", at(&dq, 3));
    
    // Create second deque for swap
    printf("\n--- Swap Test ---\n");
    Deque dq2;
    initDeque(&dq2);
    push_back(&dq2, 100);
    push_back(&dq2, 200);
    printf("Deque 1: ");
    display(&dq);
    printf("Deque 2: ");
    display(&dq2);
    
    swap(&dq, &dq2);
    printf("After swap:\n");
    printf("Deque 1: ");
    display(&dq);
    printf("Deque 2: ");
    display(&dq2);
    
    // Assign
    printf("\n--- Assign 5 elements with value 7 ---\n");
    assign(&dq, 5, 7);
    display(&dq);
    
    // Clear
    printf("\n--- Clear ---\n");
    clear(&dq);
    display(&dq);
    printf("Empty: %s\n", empty(&dq) ? "true" : "false");
    
    return 0;
}
