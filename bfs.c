#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int N;
int visited[MAX];
int parent[MAX];
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

void bfs(int start, int target) {
    for (int i = 0; i < N; i++) {
        visited[i] = 0;
        parent[i] = -1;
    }
    front = rear = 0;

    visited[start] = 1;
    enqueue(start);

    printf("\nBFS Traversal: ");

    while (!isEmpty()) {
        int current = dequeue();
        printf("%d ", current);

        if (GoalTest(current, target)) {
            printf("\n\nTrapped survivor found at Node %d!\n", target);
            ReconstructPath(target);
            return;
        }

        int succ[MAX];
        int n = MoveGen(current, succ);

        for (int k = 0; k < n; k++) {
            int next = succ[k];
            if (!visited[next]) {
                visited[next] = 1;
                parent[next] = current;
                enqueue(next);
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