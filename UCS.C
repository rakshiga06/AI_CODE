#include <stdio.h>
#include <limits.h>

#define N 20

int graph[N][N];
int g[N];
int visited[N];
int inOpen[N];
int parent[N];
int nodes;

int MoveGen(int state, int C[])
{
    int count = 0;
    for (int i = 0; i < nodes; i++)
        if (graph[state][i] > 0)
            C[count++] = i;
    return count;
}

int GoalTest(int state, int goal)
{
    return state == goal;
}

void ReconstructPath(int node)
{
    if (parent[node] == -1)
    {
        printf("%d ", node);
        return;
    }

    ReconstructPath(parent[node]);
    printf("%d ", node);
}

void ucs(int start, int goal)
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
        int current = -1;
        int minG = INT_MAX;

        for (int i = 0; i < nodes; i++)
        {
            if (inOpen[i] && g[i] < minG)
            {
                minG = g[i];
                current = i;
            }
        }

        if (current == -1)
            break;

        inOpen[current] = 0;
        visited[current] = 1;

        if (GoalTest(current, goal))
        {
            found = 1;
            break;
        }

        int C[N];
        int count = MoveGen(current, C);

        for (int k = 0; k < count; k++)
        {
            int i = C[k];

            if (!visited[i])
            {
                int newG = g[current] + graph[current][i];

                if (newG < g[i])
                {
                    g[i] = newG;
                    parent[i] = current;
                    inOpen[i] = 1;
                }
            }
        }
    }

    if (!found)
    {
        printf("No path exists\n");
        return;
    }

    printf("Path: ");
    ReconstructPath(goal);
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

    printf("Enter start node: ");
    scanf("%d", &start);

    printf("Enter target node: ");
    scanf("%d", &target);

    ucs(start, target);

    return 0;
}