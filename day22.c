/*ount Nodes in Linked List

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the result
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

int countNodes() {
    int count = 0;
    struct Node* temp = head;
    
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    
    return count;
}

int main() {
    int n;
    scanf("%d", &n);
    
    for(int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertAtEnd(data);
    }
    
    int totalNodes = countNodes();
    printf("%d\n", totalNodes);
    
    return 0;
}