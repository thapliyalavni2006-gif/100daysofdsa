/*  Given an array of n integers, reverse the array in-place using two-pointer approach.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the reversed array, space-separated
*/

#include <stdio.h>

int main() {
    int n, i;
    scanf("%d", &n);

    int arr[n];

    // Input array
    for(i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Two-pointer approach
    int left = 0, right = n - 1;
    while(left < right) {
        int temp = arr[left];
        arr[left] = arr[right];
        arr[right] = temp;

        left++;
        right--;
    }

    // Output reversed array
for(i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}
