/*Implement a hash table using quadratic probing with formula:

h(k, i) = (h(k) + i*i) % m

Input Format
Same as previous.

Output Format
Result of SEARCH operations.

Sample Input
7
4
INSERT 49
INSERT 56
SEARCH 49
SEARCH 15

Sample Output
FOUND
NOT FOUND
*/

#include <stdio.h>
#include <string.h>

#define EMPTY -1
#define DELETED -2

int table[10000];
int m;

int hash(int k) {
    return k % m;
}

void insert(int k) {
    for (int i = 0; i < m; i++) {
        int idx = (hash(k) + i * i) % m;
        if (table[idx] == EMPTY || table[idx] == DELETED) {
            table[idx] = k;
            return;
        }
    }
}

void search(int k) {
    for (int i = 0; i < m; i++) {
        int idx = (hash(k) + i * i) % m;
        if (table[idx] == EMPTY) {
            printf("NOT FOUND\n");
            return;
        }
        if (table[idx] == k) {
            printf("FOUND\n");
            return;
        }
    }
    printf("NOT FOUND\n");
}

int main() {
    scanf("%d", &m);
    for (int i = 0; i < m; i++) table[i] = EMPTY;

    int n;
    scanf("%d", &n);

    char op[10];
    int val;
    for (int i = 0; i < n; i++) {
        scanf("%s %d", op, &val);
        if (strcmp(op, "INSERT") == 0) insert(val);
        else if (strcmp(op, "SEARCH") == 0) search(val);
    }
    return 0;
}