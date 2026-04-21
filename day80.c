#include <stdio.h>
#include <limits.h>

#define MAX_VERTICES 100
#define INF LLONG_MAX / 2

int main() {
    int n;
    scanf("%d", &n);

    long long dist[MAX_VERTICES][MAX_VERTICES];

    // Read adjacency matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            long long val;
            scanf("%lld", &val);
            if (val == -1 && i != j) {
                dist[i][j] = INF;
            } else {
                dist[i][j] = val;
            }
        }
    }

    // Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Print result
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j > 0) printf(" ");
            if (dist[i][j] == INF) {
                printf("-1");
            } else {
                printf("%lld", dist[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}