/*Check whether a given binary tree satisfies the Min-Heap property.

Input Format:
- First line contains integer N
- Second line contains level-order traversal

Output Format:
- Print YES if valid Min-Heap, otherwise NO

Example:
Input:
7
1 3 5 7 9 8 10

Output:
YES
*/

#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int isHeap = 1;
    for (int i = 0; i < n; i++) {
        int left  = 2 * i + 1;
        int right = 2 * i + 2;

        if (left  < n && arr[left]  < arr[i]) { isHeap = 0; break; }
        if (right < n && arr[right] < arr[i]) { isHeap = 0; break; }
    }

    printf("%s\n", isHeap ? "YES" : "NO");
    return 0;
}