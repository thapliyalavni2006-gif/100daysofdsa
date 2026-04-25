#include <stdio.h>

/**
 * Function to perform Insertion Sort
 * @param arr: The array to be sorted
 * @param n: The size of the array
 */
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i]; // The element to be positioned
        j = i - 1;

        /* Move elements of arr[0..i-1] that are greater than key
           to one position ahead of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    int n;

    // Reading the size of the array
    if (scanf("%d", &n) != 1) return 0;

    int arr[n];

    // Reading the elements
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Applying the algorithm
    insertionSort(arr, n);

    // Printing the sorted output
    for (int i = 0; i < n; i++) {
        printf("%d%s", arr[i], (i == n - 1) ? "" : " ");
    }
    printf("\n");

    return 0;
}