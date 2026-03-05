/*Convert an infix expression to postfix notation using stack.

Input:
- Single line: infix expression (operands are single characters)

Output:
- Print the postfix expression

Example:
Input:
A+B*C

Output:
ABC*+
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Stack for operators
char stack[MAX_SIZE];
int top = -1;

// Push to stack
void push(char c) {
    if(top < MAX_SIZE - 1) {
        stack[++top] = c;
    }
}

// Pop from stack
char pop() {
    if(top >= 0) {
        return stack[top--];
    }
    return '\0';
}

// Peek top of stack
char peek() {
    if(top >= 0) {
        return stack[top];
    }
    return '\0';
}

// Check if character is operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

// Get precedence of operator
int precedence(char c) {
    if(c == '^') return 3;
    if(c == '*' || c == '/') return 2;
    if(c == '+' || c == '-') return 1;
    return 0;
}

// Check if operator is right associative
int isRightAssociative(char c) {
    return (c == '^');
}

// Convert infix to postfix
void infixToPostfix(char* infix) {
    char postfix[MAX_SIZE];
    int j = 0;
    int len = strlen(infix);
    
    for(int i = 0; i < len; i++) {
        char ch = infix[i];
        
        // Skip spaces
        if(ch == ' ') {
            continue;
        }
        
        // If operand (letter or digit), add to output
        if(isalnum(ch)) {
            postfix[j++] = ch;
        }
        // If '(', push to stack
        else if(ch == '(') {
            push(ch);
        }
        // If ')', pop until '('
        else if(ch == ')') {
            while(top >= 0 && peek() != '(') {
                postfix[j++] = pop();
            }
            pop(); // Remove '(' from stack
        }
        // If operator
        else if(isOperator(ch)) {
            while(top >= 0 && peek() != '(' &&
                  (precedence(peek()) > precedence(ch) ||
                   (precedence(peek()) == precedence(ch) && !isRightAssociative(ch)))) {
                postfix[j++] = pop();
            }
            push(ch);
        }
    }
    
    // Pop remaining operators
    while(top >= 0) {
        postfix[j++] = pop();
    }
    
    postfix[j] = '\0';
    printf("%s\n", postfix);
}

int main() {
    char infix[MAX_SIZE];
    scanf("%s", infix);
    infixToPostfix(infix);
    return 0;
}
