#include <stdio.h>
#include <limits.h>

#define MAX_NODES 100
#define MAX_CHILD 10

typedef struct {
    int numChildren;
    int children[MAX_CHILD];
    int value;
} Node;

Node tree[MAX_NODES];

int parent[MAX_NODES];
int bestChild[MAX_NODES];
int leavesVisited = 0;

int MoveGen(int state, int C[]) {
    int count = 0;

    for (int i = 0; i < tree[state].numChildren; i++)
        C[count++] = tree[state].children[i];

    return count;
}

int GoalTest(int state) {
    return tree[state].numChildren == 0;
}

void ReconstructPath(int node) {
    if (parent[node] == -1) {
        printf("%d", node);
        return;
    }

    ReconstructPath(parent[node]);
    printf(" -> %d", node);
}

int alphabeta(int node, int isMax, int alpha, int beta) {

    if (GoalTest(node)) {
        leavesVisited++;
        return tree[node].value;
    }

    int C[MAX_CHILD];
    int count = MoveGen(node, C);

    int best = isMax ? INT_MIN : INT_MAX;

    for (int i = 0; i < count; i++) {

        int child = C[i];

        parent[child] = node;

        int score = alphabeta(child, !isMax, alpha, beta);

        if (isMax) {

            if (score > best) {
                best = score;
                bestChild[node] = child;
            }

            if (best > alpha)
                alpha = best;

        } else {

            if (score < best) {
                best = score;
                bestChild[node] = child;
            }

            if (best < beta)
                beta = best;
        }

        if (alpha >= beta) {
            printf("Pruned remaining children of node %d\n", node);
            break;
        }
    }

    return best;
}

int main(void) {

    int n, totalLeaves = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {

        scanf("%d", &tree[i].numChildren);

        if (tree[i].numChildren == 0) {
            scanf("%d", &tree[i].value);
            totalLeaves++;
        } else {

            for (int j = 0; j < tree[i].numChildren; j++)
                scanf("%d", &tree[i].children[j]);
        }
    }

    parent[0] = -1;

    int result = alphabeta(0, 1, INT_MIN, INT_MAX);

    printf("Best value for engine (MAX) = %d\n", result);
    printf("Engine should move to node %d\n", bestChild[0]);
    printf("Leaves evaluated: %d out of %d\n", leavesVisited, totalLeaves);

    int leaf = 0;

    while (!GoalTest(leaf))
        leaf = bestChild[leaf];

    printf("Path (best play): ");
    ReconstructPath(leaf);
    printf("\n");

    return 0;
}