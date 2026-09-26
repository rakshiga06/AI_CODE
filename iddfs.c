// Iterative Deepening DFS
#include <stdio.h>

#define MAX 20
#define MAX_DEPTH 20   // safety cap on how deep IDDFS will try

int graph[MAX][MAX];
int N;
int visited[MAX];

int dls(int current, int target, int limit, int depth) {
    printf("Visit Node %d (depth %d)\n", current, depth);
    visited[current] = 1;

    if (current == target) {
        return 1;
    }

    if (depth == limit) {
        return 0;
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

void iddfs(int start, int target) {
    for (int limit = 0; limit <= MAX_DEPTH; limit++) {

        for (int i = 0; i < N; i++) visited[i] = 0;   // reset for each new attempt

        printf("\n--- Trying with depth limit = %d ---\n", limit);

        if (dls(start, target, limit, 0)) {
            printf("\nTarget %d found within depth limit %d!\n", target, limit);
            return;
        }
    }

    printf("\nTarget %d not found up to max depth %d.\n", target, MAX_DEPTH);
}

int main() {
    int edges, u, v, start, target;

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

    iddfs(start, target);

    return 0;
}