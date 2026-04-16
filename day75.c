/*Given an array of integers containing both positive and negative values, find the length of the longest contiguous subarray whose sum is equal to zero.

Input Format
An integer array arr[].

Output Format
Print the length of the longest subarray with sum equal to zero.

Sample Input
15 -2 2 -8 1 7 10 23

Sample Output
5*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000
#define HASH_SIZE 20003  // Prime, large enough for offset sums

typedef struct Entry {
    int key;    // prefix sum
    int value;  // first index seen
    int used;
} Entry;

Entry hashTable[HASH_SIZE];

void resetTable() {
    memset(hashTable, 0, sizeof(hashTable));
    for (int i = 0; i < HASH_SIZE; i++)
        hashTable[i].used = 0;
}

// Hash map: store first occurrence index of a prefix sum
int hashIndex(int key) {
    return ((key % HASH_SIZE) + HASH_SIZE) % HASH_SIZE;  // Handle negatives
}

void insertHash(int key, int value) {
    int idx = hashIndex(key);
    while (hashTable[idx].used && hashTable[idx].key != key)
        idx = (idx + 1) % HASH_SIZE;  // Linear probing
    if (!hashTable[idx].used) {
        hashTable[idx].key = key;
        hashTable[idx].value = value;
        hashTable[idx].used = 1;
    }
    // If already exists, do NOT update (we want first occurrence)
}

int getHash(int key, int* found) {
    int idx = hashIndex(key);
    while (hashTable[idx].used) {
        if (hashTable[idx].key == key) {
            *found = 1;
            return hashTable[idx].value;
        }
        idx = (idx + 1) % HASH_SIZE;
    }
    *found = 0;
    return -1;
}

int longestZeroSumSubarray(int* arr, int n) {
    resetTable();

    // prefixSum = 0 seen at index -1 (before array starts)
    insertHash(0, -1);

    int prefixSum = 0;
    int maxLen = 0;

    for (int i = 0; i < n; i++) {
        prefixSum += arr[i];

        int found;
        int prevIdx = getHash(prefixSum, &found);

        if (found) {
            int len = i - prevIdx;   // subarray from prevIdx+1 to i
            if (len > maxLen)
                maxLen = len;
        } else {
            insertHash(prefixSum, i);
        }
    }

    return maxLen;
}

int main() {
    int arr[MAX_SIZE], n = 0;
    while (scanf("%d", &arr[n]) == 1)
        n++;

    printf("%d\n", longestZeroSumSubarray(arr, n));
    return 0;
}