/* Implement a stack data structure using an array with the following operations: push, pop, and display.

Input:
- First line: integer n (number of operations)
- Next n lines: operation type and value (if applicable)
  - 1 value: push value
  - 2: pop
  - 3: display

Output:
- For display: print stack elements from top to bottom
- For pop: print popped element or 'Stack Underflow'*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int arr[MAX_SIZE];
    int top;
} Stack;

// Initialize stack
void initStack(Stack* stack) {
    stack->top = -1;
}

// Check if stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Check if stack is full
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Push operation
void push(Stack* stack, int value) {
    if(isFull(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++stack->top] = value;
}

// Pop operation
void pop(Stack* stack) {
    if(isEmpty(stack)) {
        printf("Stack Underflow\n");
        return;
    }
    printf("%d\n", stack->arr[stack->top--]);
}

// Display operation
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

    for(int i = 0; i < n; i++) {
        int operation;
        scanf("%d", &operation);

        if(operation == 1) {
            int value;
            scanf("%d", &value);
            push(&stack, value);
        } else if(operation == 2) {
            pop(&stack);
        } else if(operation == 3) {
            display(&stack);
        }
    }

    return 0;
}
