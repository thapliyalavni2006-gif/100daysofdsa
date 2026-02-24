/*Delete First Occurrence of a Key - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers
- Third line: integer key

Output:
- Print the linked list elements after deletion, space-separated
*/
#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* head = NULL;

void insertAtEnd(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    
    if(head == NULL) {
        head = newNode;
        return;
    }
    
    struct Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void deleteFirstOccurrence(int key) {
    if(head == NULL) {
        printf("List is empty\n");
        return;
    }
    
    // If key is at head
    if(head->data == key) {
        struct Node* temp = head;
        head = head->next;
        free(temp);
        return;
    }
    
    // Search for key in rest of list
    struct Node* temp = head;
    while(temp->next != NULL && temp->next->data != key) {
        temp = temp->next;
    }
    
    // If key found
    if(temp->next != NULL) {
        struct Node* delNode = temp->next;
        temp->next = delNode->next;
        free(delNode);
    }
}

void display() {
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
    int n, key;
    
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertAtEnd(data);
    }
    
    scanf("%d", &key);
    
    deleteFirstOccurrence(key);
    
    display();
    
    return 0;
}