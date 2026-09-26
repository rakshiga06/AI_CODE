// Depth-Limited DFS
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int N;
int visited[MAX];

// returns 1 if target found within depth limit, 0 otherwise
int dls(int current, int target, int limit, int depth) {
    printf("Visit Node %d (depth %d)\n", current, depth);
    visited[current] = 1;

    if (current == target) {
        printf("\nTarget %d found at depth %d!\n", target, depth);
        return 1;
    }

    if (depth == limit) {
        return 0;   // hit the limit, go no deeper
    }

    for (int i = 0; i < N; i++) {
        if (graph[current][i] == 1 && !visited[i]) {
            if (dls(i, target, limit, depth + 1)) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    int edges, u, v, start, target, limit;

    printf("Enter number of nodes: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges as pairs (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter start node: ");
    scanf("%d", &start);
    printf("Enter target node: ");
    scanf("%d", &target);
    printf("Enter depth limit: ");
    scanf("%d", &limit);

    for (int i = 0; i < N; i++) visited[i] = 0;

    printf("\nDLS Traversal (limit = %d):\n", limit);
    int result = dls(start, target, limit, 0);

    if (!result)
        printf("\nTarget not found within depth limit %d.\n", limit);

    return 0;
}