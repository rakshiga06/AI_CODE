// BFS - unweighted, undirected graph
#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int N;
int visited[MAX];
int queue[MAX], front = 0, rear = 0;

void enqueue(int node) {
    queue[rear++] = node;
}

int dequeue() {
    return queue[front++];
}

int isEmpty() {
    return front == rear;
}

void bfs(int start, int target) {
    for (int i = 0; i < N; i++) visited[i] = 0;
    front = rear = 0;

    visited[start] = 1;
    enqueue(start);

    printf("\nBFS Traversal: ");

    while (!isEmpty()) {
        int current = dequeue();
        printf("%d ", current);

        if (current == target) {
            printf("\n\nTrapped survivor found at Node %d!\n", target);
            return;
        }

        // explore all neighbors at this level before going deeper
        for (int i = 0; i < N; i++) {
            if (graph[current][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(i);
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
    printf("Enter target node (survivor location): ");
    scanf("%d", &target);

    bfs(start, target);

    return 0;
}