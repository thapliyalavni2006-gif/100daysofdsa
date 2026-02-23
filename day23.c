/*Merge Two Sorted Linked Lists - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers (first list)
- Third line: integer m
- Fourth line: m space-separated integers (second list)

Output:
- Print the merged linked list elements, space-separated
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

struct Node* mergeSortedLists(struct Node* head1, struct Node* head2) {
    if(head1 == NULL) return head2;
    if(head2 == NULL) return head1;
    
    struct Node* mergedHead = NULL;
    struct Node* tail = NULL;
    
    while(head1 != NULL && head2 != NULL) {
        struct Node* smaller;
        
        if(head1->data <= head2->data) {
            smaller = head1;
            head1 = head1->next;
        } else {
            smaller = head2;
            head2 = head2->next;
        }
        
        if(mergedHead == NULL) {
            mergedHead = smaller;
            tail = smaller;
        } else {
            tail->next = smaller;
            tail = smaller;
        }
    }
    
    if(head1 != NULL) {
        tail->next = head1;
    }
    if(head2 != NULL) {
        tail->next = head2;
    }
    
    return mergedHead;
}

void printList(struct Node* head) {
    struct Node* temp = head;
    while(temp != NULL) {
        printf("%d", temp->data);
        if(temp->next != NULL) printf(" ");
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    
    int n;
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertAtEnd(&head1, data);
    }
    
    int m;
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int data;
        scanf("%d", &data);
        insertAtEnd(&head2, data);
    }
    
    struct Node* mergedList = mergeSortedLists(head1, head2);
    printList(mergedList);
    
    return 0;
}