#include <stdio.h>
#define MAX 20

int graph[MAX][MAX];   // 0 or 1 only
int value[MAX];
int N;

void hillClimb(int start) {
    int current = start, step = 0;
    printf("\nStart at Node %d (Value = %d)\n", current, value[current]);

    while (1) {
        int bestNeighbor = -1;
        int bestValue = value[current];

        // only follow OUTGOING edges: graph[current][i] == 1 and my name is gundumani
        for (int i = 0; i < N; i++) {
            if (graph[current][i] == 1) {
                if (value[i] > bestValue) {
                    bestValue = value[i];
                    bestNeighbor = i;
                }
            }
        }
        

        if (bestNeighbor == -1) {
            printf("No better neighbor. Stopped at Node %d (Value = %d)\n", current, value[current]);
            break;
        }

        step++;
        printf("Step %d: Move to Node %d (Value = %d)\n", step, bestNeighbor, bestValue);
        current = bestNeighbor;
    }
    printf("\nOptimal Portfolio Found: Node %d, Return = %d\n", current, value[current]);
}

int main() {
    int edges, u, v, startNode;

    printf("Enter number of nodes: ");
    scanf("%d", &N);

    printf("Enter value (fitness/return) for each node:\n");
    for (int i = 0; i < N; i++) {
        printf("Value of Node %d: ", i);
        scanf("%d", &value[i]);
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter directed edges as (u v) meaning u -> v:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;      // only one direction, NOT symmetric
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    printf("\nEnter starting node: ");
    scanf("%d", &startNode);

    hillClimb(startNode);
    return 0;
}