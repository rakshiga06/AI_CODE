#include <stdio.h>
#include <limits.h>

#define MAX 10
#define MAX_STATES 100000

int n;                      
int cost[MAX][MAX];          


typedef struct {
    int uav;                 
    int zone;                
    int cost;               
    int usedMask;           
    int parent;             
} State;

State states[MAX_STATES];
int stateCount = 0;

int best = INT_MAX;        
int bestState = -1;        
int nodesVisited = 0, nodesPruned = 0;

int MoveGen(int s, int C[]) {
    int count = 0;                             
    for (int j = 0; j < n; j++) {
        if (states[s].usedMask & (1 << j)) continue;   

        int k = stateCount++;
        states[k].uav      = states[s].uav + 1;
        states[k].zone     = j;
        states[k].cost     = states[s].cost + cost[states[s].uav][j];
        states[k].usedMask = states[s].usedMask | (1 << j);
        states[k].parent   = s;                
        C[count++] = k;
    }
    return count;
}


int GoalTest(int s) {
    return states[s].uav == n;
}


void ReconstructPath(int s) {
    if (states[s].parent == -1) return;         
    ReconstructPath(states[s].parent);
    int u = states[s].uav - 1;
    printf("UAV %d -> Zone %d (cost %d)\n", u, states[s].zone, cost[u][states[s].zone]);
}


int lowerBound(int s) {
    int lb = states[s].cost;
    for (int i = states[s].uav; i < n; i++) {
        int mn = INT_MAX;
        for (int j = 0; j < n; j++)
            if (!(states[s].usedMask & (1 << j)) && cost[i][j] < mn)
                mn = cost[i][j];
        lb += mn;
    }
    return lb;
}

void solve(int s) {
    nodesVisited++;

    if (GoalTest(s)) {                         
        if (states[s].cost < best) {
            best = states[s].cost;
            bestState = s;
        }
        return;
    }

    int C[MAX];
    int count = MoveGen(s, C);

    for (int i = 0; i < count; i++) {
        int child = C[i];

        if (lowerBound(child) < best) {
            solve(child);
        } else {
            nodesPruned++;
            printf("  Pruned: UAV %d -> zone %d (bound >= %d, best = %d)\n",
                   states[child].uav - 1, states[child].zone, lowerBound(child), best);
        }
    }
}

int main(void) {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            scanf("%d", &cost[i][j]);

    states[0].uav = 0;
    states[0].zone = -1;
    states[0].cost = 0;
    states[0].usedMask = 0;
    states[0].parent = -1;
    stateCount = 1;

    solve(0);

    printf("Minimum total cost = %d\n", best);
    ReconstructPath(bestState);

    printf("Nodes visited: %d, branches pruned: %d\n", nodesVisited, nodesPruned);
    return 0;
}