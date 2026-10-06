#include <stdio.h>
#include <limits.h>

#define MAX 10
#define MAX_STATES 200000

int n;
int cost[MAX][MAX];

typedef struct {
    int uav;
    int zone;
    int g;
    int f;
    int usedMask;
    int parent;
} State;

State states[MAX_STATES];
int inOpen[MAX_STATES];
int stateCount = 0;

int best = INT_MAX;
int bestState = -1;
int nodesExpanded = 0, nodesPruned = 0;

int heuristic(int s)
{
    int h = 0;

    for (int i = states[s].uav; i < n; i++) {
        int mn = INT_MAX;

        for (int j = 0; j < n; j++)
            if (!(states[s].usedMask & (1 << j)) && cost[i][j] < mn)
                mn = cost[i][j];

        h += mn;
    }

    return h;
}

int GoalTest(int s)
{
    return states[s].uav == n;
}

int MoveGen(int s, int C[])
{
    int count = 0;

    for (int j = 0; j < n; j++) {

        if (states[s].usedMask & (1 << j))
            continue;

        if (stateCount >= MAX_STATES) {
            printf("State limit reached!\n");
            return count;
        }

        int k = stateCount++;

        states[k].uav = states[s].uav + 1;
        states[k].zone = j;
        states[k].g = states[s].g + cost[states[s].uav][j];
        states[k].usedMask = states[s].usedMask | (1 << j);
        states[k].parent = s;
        states[k].f = states[k].g + heuristic(k);
        inOpen[k] = 0;

        if (states[k].f >= best) {
            nodesPruned++;

            printf(" Pruned: UAV %d -> zone %d (f = %d >= best = %d)\n",
                   states[k].uav - 1, j, states[k].f, best);
        }
        else {
            C[count++] = k;
        }
    }

    return count;
}

void ReconstructPath(int s)
{
    if (states[s].parent == -1)
        return;

    ReconstructPath(states[s].parent);

    int u = states[s].uav - 1;

    printf("UAV %d -> Zone %d (cost %d)\n",
           u, states[s].zone, cost[u][states[s].zone]);
}

void greedyUpperBound(void)
{
    int cur = 0;

    for (int i = 0; i < n; i++) {

        int bj = -1;
        int mn = INT_MAX;

        for (int j = 0; j < n; j++)
            if (!(states[cur].usedMask & (1 << j)) && cost[i][j] < mn) {
                mn = cost[i][j];
                bj = j;
            }

        int k = stateCount++;

        states[k].uav = i + 1;
        states[k].zone = bj;
        states[k].g = states[cur].g + mn;
        states[k].f = states[k].g;
        states[k].usedMask = states[cur].usedMask | (1 << bj);
        states[k].parent = cur;
        inOpen[k] = 0;

        cur = k;
    }

    best = states[cur].g;
    bestState = cur;

    printf("Initial upper bound from greedy = %d\n", best);
}

void solve(void)
{
    states[0].uav = 0;
    states[0].zone = -1;
    states[0].g = 0;
    states[0].usedMask = 0;
    states[0].parent = -1;
    states[0].f = heuristic(0);

    stateCount = 1;
    inOpen[0] = 1;

    greedyUpperBound();

    while (1) {

        int cur = -1;
        int minF = INT_MAX;

        for (int i = 0; i < stateCount; i++)
            if (inOpen[i] &&
                (states[i].f < minF ||
                 (states[i].f == minF && cur != -1 &&
                  states[i].uav > states[cur].uav))) {

                minF = states[i].f;
                cur = i;
            }

        if (cur == -1)
            break;

        if (minF >= best) {

            for (int i = 0; i < stateCount; i++)
                if (inOpen[i]) {
                    inOpen[i] = 0;
                    nodesPruned++;
                }

            break;
        }

        inOpen[cur] = 0;
        nodesExpanded++;

        if (GoalTest(cur)) {
            best = states[cur].g;
            bestState = cur;
            break;
        }

        int C[MAX];
        int count = MoveGen(cur, C);

        for (int i = 0; i < count; i++)
            inOpen[C[i]] = 1;
    }
}

int main(void)
{
    printf("Enter n (UAVs = zones): ");
    scanf("%d", &n);

    printf("Enter cost matrix (%d x %d):\n", n, n);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    solve();

    printf("\nMinimum total cost = %d\n", best);

    ReconstructPath(bestState);

    printf("Nodes expanded: %d, nodes pruned: %d\n",
           nodesExpanded, nodesPruned);

    return 0;
}