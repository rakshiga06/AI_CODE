#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int N;
int visited[MAX];
int parent[MAX];
int stack[MAX * MAX], top = -1;

void push(int node) {
    stack[++top] = node;
}

int pop() {
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

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

void dfs(int start, int target) {
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    top = -1;

    push(start);

    printf("\nDFS Traversal: ");

    while (!isEmpty()) {
        int current = pop();

        if (visited[current]) continue;

        visited[current] = 1;
        printf("%d ", current);

        if (GoalTest(current, target)) {
            printf("\n\nReached deepest target point: Node %d!\n", target);
            ReconstructPath(target);
            return;
        }

        int succ[MAX];
        int n = MoveGen(current, succ);

        for (int k = 0; k < n; k++) {
            int next = succ[k];
            if (!visited[next]) {
                parent[next] = current;
                push(next);
            }
        }
    }

    printf("\n\nTarget node %d not reachable.\n", target);
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

    dfs(start, target);

    return 0;
}