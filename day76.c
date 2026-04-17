/*#include <stdio.h>

#define MAX 100001

int parent[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b)
        parent[a] = b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == i)
            count++;

    printf("%d\n", count);
    return 0;
}*/

#include <stdio.h>

#define MAX 100001

int parent[MAX];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b)
        parent[a] = b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 1; i <= n; i++)
        parent[i] = i;

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        unite(u, v);
    }

    int count = 0;
    for (int i = 1; i <= n; i++)
        if (find(i) == i)
            count++;

    printf("%d\n", count);
    return 0;
}