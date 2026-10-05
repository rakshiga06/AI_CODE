#include <stdio.h>
#define MAX 20

int graph[MAX][MAX];
int value[MAX];
int parent[MAX];
int N;
int beamWidth;

int MoveGen(int state, int succ[]) {
    int count = 0;
    for (int i = 0; i < N; i++)
        if (graph[state][i] == 1)
            succ[count++] = i;
    return count;
}

int GoalTest(int bestCandidate, int bestInBeam) {
    return bestCandidate <= bestInBeam;
}

void ReconstructPath(int node) {
    int path[MAX];
    int count = 0;

    for (int temp = node; temp != -1; temp = parent[temp])
        path[count++] = temp;

    printf("Path: ");
    for (int i = count - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\n");
}

int isInList(int node, int list[], int size) {
    for (int i = 0; i < size; i++)
        if (list[i] == node) return 1;
    return 0;
}

void beamSearch(int start) {
    int beam[MAX], beamSize = 1;
    beam[0] = start;

    for (int i = 0; i < N; i++)
        parent[i] = -1;

    printf("\nInitial Beam: Node %d (Value = %d)\n", start, value[start]);

    int level = 0;
    while (1) {
        level++;
        int candidates[MAX], candValues[MAX], candCount = 0;

        for (int b = 0; b < beamSize; b++) {
            int cur = beam[b];
            int succ[MAX];
            int n = MoveGen(cur, succ);

            for (int k = 0; k < n; k++) {
                int next = succ[k];
                if (!isInList(next, candidates, candCount)) {
                    candidates[candCount] = next;
                    candValues[candCount] = value[next];
                    candCount++;
                    if (next != start && parent[next] == -1)
                        parent[next] = cur;
                }
            }
        }

        if (candCount == 0) {
            printf("No further neighbors. Stopping.\n");
            break;
        }

        for (int i = 0; i < candCount - 1; i++) {
            for (int j = 0; j < candCount - i - 1; j++) {
                if (candValues[j] < candValues[j + 1]) {
                    int t1 = candValues[j]; candValues[j] = candValues[j+1]; candValues[j+1] = t1;
                    int t2 = candidates[j]; candidates[j] = candidates[j+1]; candidates[j+1] = t2;
                }
            }
        }

        int bestInBeam = value[beam[0]];
        for (int i = 1; i < beamSize; i++)
            if (value[beam[i]] > bestInBeam)
                bestInBeam = value[beam[i]];

        if (GoalTest(candValues[0], bestInBeam)) {
            printf("No improvement possible. Stopping at Level %d.\n", level);
            break;
        }

        beamSize = (candCount < beamWidth) ? candCount : beamWidth;
        for (int i = 0; i < beamSize; i++)
            beam[i] = candidates[i];

        printf("Level %d Beam: ", level);
        for (int i = 0; i < beamSize; i++)
            printf("Node %d (Val=%d)  ", beam[i], value[beam[i]]);
        printf("\n");
    }

    int best = beam[0];
    for (int i = 1; i < beamSize; i++)
        if (value[beam[i]] > value[best]) best = beam[i];

    printf("\nBest Solution Found: Node %d, Value = %d\n", best, value[best]);
    ReconstructPath(best);
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
        graph[v][u] = 1;
    }

    printf("Enter beam width (k): ");
    scanf("%d", &beamWidth);

    printf("Enter starting node: ");
    scanf("%d", &startNode);

    beamSearch(startNode);
    return 0;
}