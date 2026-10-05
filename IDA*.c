#include <stdio.h>
#include <limits.h>

#define N 20
#define FOUND -1

int graph[N][N];
int h[N];
int onPath[N];
int parent[N];
int nodes;
int goal;
int goalCost;

int MoveGen(int state, int succ[])
{
    int count = 0;
    for (int i = 0; i < nodes; i++)
        if (graph[state][i] > 0)
            succ[count++] = i;
    return count;
}

int GoalTest(int state, int goal)
{
    return state == goal;
}

void ReconstructPath(int goal)
{
    int path[N];
    int count = 0;

    for (int temp = goal; temp != -1; temp = parent[temp])
        path[count++] = temp;

    printf("Path: ");
    for (int i = count - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\nTotal cost: %d\n", goalCost);
}

int search(int node, int g, int threshold)
{
    int f = g + h[node];

    if (f > threshold)
        return f;

    if (GoalTest(node, goal))
    {
        goalCost = g;
        return FOUND;
    }

    onPath[node] = 1;

    int succ[N];
    int n = MoveGen(node, succ);
    int min = INT_MAX;

    for (int k = 0; k < n; k++)
    {
        int next = succ[k];

        if (!onPath[next])
        {
            parent[next] = node;
            int t = search(next, g + graph[node][next], threshold);

            if (t == FOUND)
                return FOUND;

            if (t < min)
                min = t;
        }
    }

    onPath[node] = 0;

    return min;
}

void idastar(int start)
{
    int threshold = h[start];

    while (1)
    {
        for (int i = 0; i < nodes; i++)
        {
            onPath[i] = 0;
            parent[i] = -1;
        }

        int t = search(start, 0, threshold);

        if (t == FOUND)
        {
            ReconstructPath(goal);
            return;
        }

        if (t == INT_MAX)
        {
            printf("No path exists\n");
            return;
        }

        threshold = t;
    }
}

int main()
{
    int edges, u, v, w, start;

    printf("Enter number of nodes (max %d): ", N);
    scanf("%d", &nodes);

    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;
    }

    printf("Enter heuristic values:\n");
    for (int i = 0; i < nodes; i++)
        scanf("%d", &h[i]);

    printf("Enter start node: ");
    scanf("%d", &start);

    printf("Enter target node: ");
    scanf("%d", &goal);

    idastar(start);

    return 0;
}