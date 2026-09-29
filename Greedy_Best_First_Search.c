#include <stdio.h>
#include <limits.h>

#define N 20

int graph[N][N];
int h[N];
int visited[N];   // closed list (already expanded)
int inOpen[N];    // open list (discovered, waiting to be expanded)
int parent[N];
int nodes;

void greedyBFS(int start, int goal)
{
    for (int i = 0; i < nodes; i++)
    {
        visited[i] = 0;
        inOpen[i] = 0;
        parent[i] = -1;
    }

    inOpen[start] = 1;
    int found = 0;

    while (1)
    {
        // Pick node from OPEN list with the smallest heuristic
        int current = -1;
        int minH = INT_MAX;

        for (int i = 0; i < nodes; i++)
        {
            if (inOpen[i] && h[i] < minH)
            {
                minH = h[i];
                current = i;
            }
        }

        // Open list empty -> no path
        if (current == -1)
            break;

        inOpen[current] = 0;
        visited[current] = 1;

        if (current == goal)
        {
            found = 1;
            break;
        }

        // Add unvisited neighbours to the open list
        for (int i = 0; i < nodes; i++)
        {
            if (graph[current][i] && !visited[i] && !inOpen[i])
            {
                parent[i] = current;
                inOpen[i] = 1;
            }
        }
    }

    if (!found)
    {
        printf("No path exists\n");
        return;
    }

    // Build path from goal back to start
    int path[N];
    int count = 0;

    for (int temp = goal; temp != -1; temp = parent[temp])
        path[count++] = temp;

    printf("Path: ");
    for (int i = count - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\n");
}

int main()
{
    int edges, u, v, start, target;

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

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++)
    {
        scanf("%d %d", &u, &v);
        if (u < 0 || u >= nodes || v < 0 || v >= nodes)
        {
            printf("Invalid edge\n");
            i--;
            continue;
        }
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter heuristic values:\n");
    for (int i = 0; i < nodes; i++)
        scanf("%d", &h[i]);

    printf("Enter start node: ");
    scanf("%d", &start);

    printf("Enter target node: ");
    scanf("%d", &target);

    greedyBFS(start, target);

    return 0;
}