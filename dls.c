#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int N;
int visited[MAX];
int parent[MAX];

int MoveGen(int state, int succ[]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        if (graph[state][i] == 1)
            succ[count++] = i;
    return count;
}

int GoalTest(int state, int target) {
    return state == target;
}

void ReconstructPath(int target) {
    int path[MAX];
    int count = 0;

    for (int temp = target; temp != -1; temp = parent[temp])
        path[count++] = temp;

    printf("Path: ");
    for (int i = count - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\nNumber of edges: %d\n", count - 1);
}

int dls(int current, int target, int limit, int depth) {
    printf("Visit Node %d (depth %d)\n", current, depth);
    visited[current] = 1;

    if (GoalTest(current, target)) {
        printf("\nTarget %d found at depth %d!\n", target, depth);
        ReconstructPath(target);
        return 1;
    }

    if (depth == limit) {
        return 0;
    }

    int succ[MAX];
    int n = MoveGen(current, succ);

    for (int k = 0; k < n; k++) {
        int next = succ[k];
        if (!visited[next]) {
            parent[next] = current;
            if (dls(next, target, limit, depth + 1)) {
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

    for (int i = 0; i < N; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }

    printf("\nDLS Traversal (limit = %d):\n", limit);
    int result = dls(start, target, limit, 0);

    if (!result)
        printf("\nTarget not found within depth limit %d.\n", limit);

    return 0;
}