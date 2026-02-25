/*Count Occurrences of an Element in Linked List - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n (number of nodes)
- Second line: n space-separated integers (linked list elements)
- Third line: integer key (element to be counted)

Output:
- Print the number of times the key appears in the linked list*/

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

int countOccurrences(int key) {
    int count = 0;
    struct Node* temp = head;
    
    while(temp != NULL) {
        if(temp->data == key) {
            count++;
        }
        temp = temp->next;
    }
    
    return count;
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
    
    int count = countOccurrences(key);
    printf("%d\n", count);
    
    return 0;
}