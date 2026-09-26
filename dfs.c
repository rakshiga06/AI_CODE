// DFS - unweighted, undirected graph (iterative, using a stack)
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int N;
int visited[MAX];
int stack[MAX], top = -1;

void push(int node) {
    stack[++top] = node;
}

int pop() {
    return stack[top--];
}

int isEmpty() {
    return top == -1;
}

void dfs(int start, int target) {
    for (int i = 0; i < N; i++) visited[i] = 0;
    top = -1;

    push(start);

    printf("\nDFS Traversal: ");

    while (!isEmpty()) {
        int current = pop();

        if (visited[current]) continue; 

        visited[current] = 1;
        printf("%d ", current);

        if (current == target) {
            printf("\n\nReached deepest target point: Node %d!\n", target);
            return;
        }

        // push all unvisited neighbors (they'll be explored before older stack entries)
        for (int i = 0; i < N; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                push(i);
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