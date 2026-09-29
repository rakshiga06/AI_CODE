#include <stdio.h>
#include <limits.h>

#define N 20
#define FOUND -1

int graph[N][N];   // edge weights (0 = no edge)
int h[N];          // heuristic
int onPath[N];     // nodes on the current DFS path (avoids cycles)
int path[N];       // current path (stack)
int pathLen;
int nodes;
int goal;
int goalCost;

int search(int node, int g, int threshold)
{
    int f = g + h[node];

    if (f > threshold)          // prune, report the f that exceeded the limit
        return f;

    onPath[node] = 1;
    path[pathLen++] = node;

    if (node == goal)
    {
        goalCost = g;
        return FOUND;           // keep path[] intact
    }

    int min = INT_MAX;

    for (int i = 0; i < nodes; i++)
    {
        if (graph[node][i] > 0 && !onPath[i])
        {
            int t = search(i, g + graph[node][i], threshold);

            if (t == FOUND)
                return FOUND;

            if (t < min)
                min = t;
        }
    }

    // backtrack
    onPath[node] = 0;
    pathLen--;

    return min;
}

void idastar(int start)
{
    int threshold = h[start];

    while (1)
    {
        for (int i = 0; i < nodes; i++)
            onPath[i] = 0;
        pathLen = 0;

        int t = search(start, 0, threshold);

        if (t == FOUND)
        {
            printf("Path: ");
            for (int i = 0; i < pathLen; i++)
                printf("%d ", path[i]);
            printf("\nTotal cost: %d\n", goalCost);
            return;
        }

        if (t == INT_MAX)       // nothing left to explore
        {
            printf("No path exists\n");
            return;
        }

        threshold = t;          // raise the limit to the smallest f that was pruned
    }
}

int main()
{
    int edges, u, v, w, start;

    printf("Enter number of nodes (max %d): ", N);
    scanf("%d", &nodes);

    if (nodes <= 0 || nodes > N)
    {
        printf("Invalid number of nodes\n");
        return 1;
    }

    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            graph[i][j] = 0;

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v weight):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d %d", &u, &v, &w);
        if (u < 0 || u >= nodes || v < 0 || v >= nodes || w <= 0)
        {
            printf("Invalid edge\n");
            i--;
            continue;
        }
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