#include <stdio.h>
#define MAX 20

int graph[MAX][MAX];   // adjacency matrix (0/1)
int value[MAX];        // value/fitness of each node
int N;                  // number of nodes
int beamWidth;          // k

// check if a node is already in the beam
int isInBeam(int node, int beam[], int beamSize) {
    for (int i = 0; i < beamSize; i++)
        if (beam[i] == node) return 1;
    return 0;
}

void beamSearch(int start) {
    int beam[MAX], beamSize = 1;
    beam[0] = start;

    printf("\nInitial Beam: Node %d (Value = %d)\n", start, value[start]);

    int level = 0;
    while (1) {
        level++;
        int candidates[MAX], candValues[MAX], candCount = 0;

        // Generate all neighbors of all nodes currently in beam
        for (int b = 0; b < beamSize; b++) {
            int cur = beam[b];
            for (int i = 0; i < N; i++) {
                if (graph[cur][i] == 1 && !isInBeam(i, candidates, candCount)) {
                    candidates[candCount] = i;
                    candValues[candCount] = value[i];
                    candCount++;
                }
            }
        }

        if (candCount == 0) {
            printf("No further neighbors. Stopping.\n");
            break;
        }

        // Sort candidates by value descending (simple bubble sort)
        for (int i = 0; i < candCount - 1; i++) {
            for (int j = 0; j < candCount - i - 1; j++) {
                if (candValues[j] < candValues[j + 1]) {
                    int t1 = candValues[j]; candValues[j] = candValues[j+1]; candValues[j+1] = t1;
                    int t2 = candidates[j]; candidates[j] = candidates[j+1]; candidates[j+1] = t2;
                }
            }
        }

        // Check if best candidate improves over best in current beam
        int bestInBeam = value[beam[0]];
        for (int i = 1; i < beamSize; i++)
            if (value[beam[i]] > bestInBeam) bestInBeam = value[beam[i]];

        if (candValues[0] <= bestInBeam) {
            printf("No improvement possible. Stopping at Level %d.\n", level);
            break;
        }

        // Keep top-k (beamWidth) candidates as new beam
        beamSize = (candCount < beamWidth) ? candCount : beamWidth;
        for (int i = 0; i < beamSize; i++)
            beam[i] = candidates[i];

        printf("Level %d Beam: ", level);
        for (int i = 0; i < beamSize; i++)
            printf("Node %d (Val=%d)  ", beam[i], value[beam[i]]);
        printf("\n");
    }

    // Find best node in final beam
    int best = beam[0];
    for (int i = 1; i < beamSize; i++)
        if (value[beam[i]] > value[best]) best = beam[i];

    printf("\nBest Solution Found: Node %d, Value = %d\n", best, value[best]);
}

int main() {
    int edges, u, v, startNode;

    printf("Enter number of nodes: ");
    scanf("%d", &N);

    printf("Enter value (fitness) for each node:\n");
    for (int i = 0; i < N; i++) {
        printf("Value of Node %d: ", i);
        scanf("%d", &value[i]);
    }

    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges as (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;   // undirected
    }

    printf("Enter beam width (k): ");
    scanf("%d", &beamWidth);

    printf("Enter starting node: ");
    scanf("%d", &startNode);

    beamSearch(startNode);
    return 0;
}