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

int minimax(int node, int isMax) {
    if (GoalTest(node))
        return tree[node].value;

    int C[MAX_CHILD];
    int count = MoveGen(node, C);

    int best = isMax ? INT_MIN : INT_MAX;

    for (int i = 0; i < count; i++) {
        int child = C[i];
        parent[child] = node;

        int score = minimax(child, !isMax);

        if (isMax) {
            if (score > best) {
                best = score;
                bestChild[node] = child;
            }
        } else {
            if (score < best) {
                best = score;
                bestChild[node] = child;
            }
        }
    }

    return best;
}

int main(void) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &tree[i].numChildren);

        if (tree[i].numChildren == 0) {
            scanf("%d", &tree[i].value);
        } else {
            for (int j = 0; j < tree[i].numChildren; j++)
                scanf("%d", &tree[i].children[j]);
        }
    }

    parent[0] = -1;

    int result = minimax(0, 1);

    printf("Best value for AI (MAX) = %d\n", result);
    printf("AI should move to node %d\n", bestChild[0]);

    int leaf = 0;

    while (!GoalTest(leaf))
        leaf = bestChild[leaf];

    printf("Path (best play): ");
    ReconstructPath(leaf);
    printf("\n");

    return 0;
}