#include <stdio.h>

int lowerBound(int arr[], int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] < x)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int upperBound(int arr[], int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] <= x)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo;
}

int main() {
    int n;
    scanf("%d", &n);

    int arr[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    int x;
    scanf("%d", &x);

    printf("%d %d\n", lowerBound(arr, n, x), upperBound(arr, n, x));

    return 0;
}