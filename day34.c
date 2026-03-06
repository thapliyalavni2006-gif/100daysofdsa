/*Evaluate Postfix Expression - Implement using linked list with dynamic memory allocation.

Input:
- Postfix expression with operands and operators

Output:
- Print the integer result

Example:
Input:
2 3 1 * + 9 -

Output:
-4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Node structure for stack
struct Node {
    int data;
    struct Node* next;
};

// Stack operations
struct Node* push(struct Node* top, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = top;
    return newNode;
}

struct Node* pop(struct Node* top, int* value) {
    if(top == NULL) {
        return NULL;
    }
    *value = top->data;
    struct Node* temp = top;
    top = top->next;
    free(temp);
    return top;
}

int isEmpty(struct Node* top) {
    return top == NULL;
}

// Check if character is operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Evaluate postfix expression
int evaluatePostfix(char* expression) {
    struct Node* stack = NULL;
    int i = 0;
    int len = strlen(expression);
    
    while(i < len) {
        // Skip spaces
        if(expression[i] == ' ') {
            i++;
            continue;
        }
        
        // If digit or negative number
        if(isdigit(expression[i]) || (expression[i] == '-' && isdigit(expression[i + 1]))) {
            int num = 0;
            int sign = 1;
            
            // Handle negative sign
            if(expression[i] == '-') {
                sign = -1;
                i++;
            }
            
            // Extract complete number
            while(i < len && isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            
            num *= sign;
            stack = push(stack, num);
        }
        // If operator
        else if(isOperator(expression[i])) {
            int b, a;
            stack = pop(stack, &b);
            stack = pop(stack, &a);
            
            int result;
            switch(expression[i]) {
                case '+':
                    result = a + b;
                    break;
                case '-':
                    result = a - b;
                    break;
                case '*':
                    result = a * b;
                    break;
                case '/':
                    result = a / b;
                    break;
            }
            
            stack = push(stack, result);
            i++;
        }
        else {
            i++;
        }
    }
    
    int finalResult;
    stack = pop(stack, &finalResult);
    return finalResult;
}

int main() {
    char expression[1000];
    fgets(expression, sizeof(expression), stdin);
    
    // Remove newline if present
    expression[strcspn(expression, "\n")] = '\0';
    
    int result = evaluatePostfix(expression);
    printf("%d\n", result);
    
    return 0;
}