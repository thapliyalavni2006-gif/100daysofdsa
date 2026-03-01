/* Rotate Linked List Right by k Places - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers
- Third line: integer k

Output:
- Print the linked list elements after rotation, space-separated
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    
    if(*head == NULL) {
        *head = newNode;
        return;
    }
    
    struct Node* temp = *head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

int getLength(struct Node* head) {
    int count = 0;
    while(head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}

struct Node* rotateRight(struct Node* head, int k) {
    if(head == NULL || head->next == NULL || k == 0) {
        return head;
    }
    
    // Get length of list
    int length = getLength(head);
    
    // Optimize k (if k > length, we only need k % length rotations)
    k = k % length;
    
    if(k == 0) {
        return head;
    }
    
    // Find the last node and make it circular
    struct Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = head;  // Make circular
    
    // Find the new tail (length - k - 1 steps from head)
    int stepsToNewTail = length - k;
    struct Node* newTail = head;
    for(int i = 1; i < stepsToNewTail; i++) {
        newTail = newTail->next;
    }
    
    // New head is next of new tail
    struct Node* newHead = newTail->next;
    
    // Break the circle
    newTail->next = NULL;
    
    return newHead;
}

void display(struct Node* head) {
    if(head == NULL) {
        printf("\n");
        return;
    }
    
    while(head != NULL) {
        printf("%d", head->data);
        if(head->next != NULL) {
            printf(" ");
        }
        head = head->next;
    }
    printf("\n");
}

int main() {
    struct Node* head = NULL;
    int n, k;
    
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertAtEnd(&head, data);
    }
    
    scanf("%d", &k);
    
    head = rotateRight(head, k);
    
    display(head);
    
    return 0;
}