/* Find Intersection Point of Two Linked Lists - Implement using linked list with dynamic memory allocation.

Input:
- First line: integer n
- Second line: n space-separated integers (first list)
- Third line: integer m
- Fourth line: m space-separated integers (second list)

Output:
- Print value of intersection node or 'No Intersection'
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

// Method 1: Using length difference
struct Node* findIntersection(struct Node* head1, struct Node* head2) {
    if(head1 == NULL || head2 == NULL) {
        return NULL;
    }
    
    int len1 = getLength(head1);
    int len2 = getLength(head2);
    
    struct Node* ptr1 = head1;
    struct Node* ptr2 = head2;
    
    // Advance the longer list
    int diff = abs(len1 - len2);
    
    if(len1 > len2) {
        for(int i = 0; i < diff; i++) {
            ptr1 = ptr1->next;
        }
    } else {
        for(int i = 0; i < diff; i++) {
            ptr2 = ptr2->next;
        }
    }
    
    // Now traverse both together
    while(ptr1 != NULL && ptr2 != NULL) {
        if(ptr1->data == ptr2->data) {
            return ptr1;
        }
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    
    return NULL;
}

// Method 2: Two-pointer approach (Alternative)
struct Node* findIntersectionTwoPointer(struct Node* head1, struct Node* head2) {
    if(head1 == NULL || head2 == NULL) {
        return NULL;
    }
    
    struct Node* ptr1 = head1;
    struct Node* ptr2 = head2;
    
    // Traverse both lists
    while(ptr1 != ptr2) {
        // When ptr1 reaches end, switch to head2
        ptr1 = (ptr1 == NULL) ? head2 : ptr1->next;
        // When ptr2 reaches end, switch to head1
        ptr2 = (ptr2 == NULL) ? head1 : ptr2->next;
        
        // Check if both reached end without intersection
        if(ptr1 != ptr2 && ptr1 == NULL && ptr2 == NULL) {
            return NULL;
        }
    }
    
    return ptr1;
}

int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    
    int n, m;
    
    // Read first list
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        int data;
        scanf("%d", &data);
        insertAtEnd(&head1, data);
    }
    
    // Read second list
    scanf("%d", &m);
    for(int i = 0; i < m; i++) {
        int data;
        scanf("%d", &data);
        insertAtEnd(&head2, data);
    }
    
    // Find intersection
    struct Node* intersection = findIntersection(head1, head2);
    
    if(intersection != NULL) {
        printf("%d\n", intersection->data);
    } else {
        printf("No Intersection\n");
    }
    
    return 0;
}