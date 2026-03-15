/*Given a queue of integers, reverse the queue using a stack.

Input Format:
- First line contains integer N
- Second line contains N space-separated integers

Output Format:
- Print the reversed queue

Example:
Input:
5
10 20 30 40 50

Output:
50 40 30 20 10*/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int queue[n], stack[n];

    for (int i = 0; i < n; i++)
        scanf("%d", &queue[i]);

    // Enqueue to stack (reverse order)
    int top = -1;
    int front = 0;

    while (front < n)
        stack[++top] = queue[front++];

    // Pop from stack back to queue
    int rear = 0;
    while (top >= 0)
        queue[rear++] = stack[top--];

    for (int i = 0; i < n; i++)
        printf("%d ", queue[i]);

    return 0;
}