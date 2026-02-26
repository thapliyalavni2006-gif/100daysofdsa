/* Doubly Linked List Insertion and Traversal - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the linked list elements in forward order, space-separated
*/

#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

struct Node* head = NULL;

void insertAtEnd(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if(head == NULL) {
        newNode->prev = NULL;
        head = newNode;
        return;
    }
    
    struct Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
}

void traverseForward() {
    if(head == NULL) {
        printf("\n");
        return;
    }
    
    struct Node* temp = head;
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
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertAtEnd(data);
    }
    
    traverseForward();
    
    return 0;
}