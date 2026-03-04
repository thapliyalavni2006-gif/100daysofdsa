/*Implement push and pop operations on a stack and verify stack operations.

Input:
- First line: integer n
- Second line: n integers to push
- Third line: integer m (number of pops)

Output:
- Print remaining stack elements from top to bottom*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

void initStack(Stack* stack) {
    stack->top = -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

void push(Stack* stack, int value) {
    if(isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

int pop(Stack* stack) {
    if(isEmpty(stack)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[stack->top--];
}

void display(Stack* stack) {
    if(isEmpty(stack)) {
        printf("Stack is empty\n");
        return;
    }
    
    for(int i = stack->top; i >= 0; i--) {
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

int main() {
    Stack stack;
    initStack(&stack);
    
    int n;
    scanf("%d", &n);
    
    // Push n elements
    for(int i = 0; i < n; i++) {
        int value;
        scanf("%d", &value);
        push(&stack, value);
    }
    
    int m;
    scanf("%d", &m);
    
    // Pop m elements
    for(int i = 0; i < m; i++) {
        pop(&stack);
    }
    
    // Display remaining elements
    display(&stack);
    
    return 0;
}