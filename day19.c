/* Given an array of integers, find two elements whose sum is closest to zero.

Input:
- First line: integer n
- Second line: n space-separated integers

Output:
- Print the pair of elements whose sum is closest to zero*/

#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}

int main(){
    int n;
    scanf("%d", &n);
    
    int arr[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &arr[i]);
    }
    
    qsort(arr, n, sizeof(int), compare);
    
    int left = 0;
    int right = n - 1;
    int minSum = arr[left] + arr[right];
    int num1 = arr[left];
    int num2 = arr[right];
    
    while(left < right){
        int sum = arr[left] + arr[right];
        
        if(abs(sum) < abs(minSum)){
            minSum = sum;
            num1 = arr[left];
            num2 = arr[right];
        }
        
        if(sum < 0){
            left++;
        } else if(sum > 0){
            right--;
        } else {
            break;
        }
    }
    
    printf("%d %d\n", num1, num2);
    
    return 0;
}