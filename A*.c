#include <stdio.h>
#include <limits.h>

#define N 20

int graph[N][N];
int h[N];
int g[N];
int inOpen[N];
int parent[N];
int nodes;

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
    printf("\nTotal cost: %d\n", g[goal]);
}

void astar(int start, int goal)
{
    for (int i = 0; i < nodes; i++)
    {
        inOpen[i] = 0;
        parent[i] = -1;
        g[i] = INT_MAX;
    }

    g[start] = 0;
    inOpen[start] = 1;

    while (1)
    {
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

        if (current == -1)
        {
            printf("No path exists\n");
            return;
        }

        inOpen[current] = 0;

        if (GoalTest(current, goal))
        {
            ReconstructPath(goal);
            return;
        }

        int succ[N];
        int n = MoveGen(current, succ);

        for (int k = 0; k < n; k++)
        {
            int next = succ[k];
            int newG = g[current] + graph[current][next];

            if (newG < g[next])
            {
                g[next] = newG;
                parent[next] = current;
                inOpen[next] = 1;
            }
        }
    }
}

int main()
{
    int edges, u, v, w, start, target;

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
    scanf("%d", &target);

    astar(start, target);

    return 0;
}