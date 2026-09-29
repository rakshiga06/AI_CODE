#include <stdio.h>
#include <limits.h>

#define N 20

int graph[N][N];   // edge weights (0 = no edge)
int h[N];          // heuristic
int g[N];          // cost from start to node
int visited[N];    // closed list
int inOpen[N];     // open list
int parent[N];
int nodes;

void astar(int start, int goal)
{
    for (int i = 0; i < nodes; i++)
    {
        visited[i] = 0;
        inOpen[i] = 0;
        parent[i] = -1;
        g[i] = INT_MAX;
    }

    g[start] = 0;
    inOpen[start] = 1;
    int found = 0;

    while (1)
    {
        // Pick node from OPEN with the smallest f = g + h
        int current = -1;
        int minF = INT_MAX;

        for (int i = 0; i < nodes; i++)
        {
            if (inOpen[i] && g[i] + h[i] < minF)
            {
                minF = g[i] + h[i];
                current = i;
            }
        }

        if (current == -1)      // open list empty
            break;

        inOpen[current] = 0;
        visited[current] = 1;

        if (current == goal)    // stop when goal is expanded, not discovered
        {
            found = 1;
            break;
        }

        // Relax neighbours
        for (int i = 0; i < nodes; i++)
        {
            if (graph[current][i] > 0)
            {
                int newG = g[current] + graph[current][i];

                if (newG < g[i])        // found a cheaper path
                {
                    g[i] = newG;
                    parent[i] = current;
                    inOpen[i] = 1;
                    visited[i] = 0;     // re-open if it was closed
                }
            }
        }
    }

    if (!found)
    {
        printf("No path exists\n");
        return;
    }

    int path[N];
    int count = 0;

    for (int temp = goal; temp != -1; temp = parent[temp])
        path[count++] = temp;

    printf("Path: ");
    for (int i = count - 1; i >= 0; i--)
        printf("%d ", path[i]);
    printf("\nTotal cost: %d\n", g[goal]);
}

int main()
{
    int edges, u, v, w, start, target;

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
    scanf("%d", &target);

    astar(start, target);

    return 0;
}

//edge relaxation-is the process of checking whether a shorter path to a node can be obtained through another node, and updating its distance and parent if a shorter path is found.