#include <stdio.h>

#define MAX 20

int graph[MAX][MAX];
int value[MAX];
int N;

void hillClimb(int start){
    int current=start;


    printf("\nstart at node %d(Value =%d)\n",current,value[current]);

    while(1){
        int bestNeighbor=-1;
        int bestValue=value[current];

        for(int i=0;i<N;i++){
            if(graph[current][i]==1){
                if(value[i]>bestValue){
                    // bestValue=value[i];
                    bestNeighbor=i;
                    bestValue=value[bestNeighbor];
                }

            }
        }

        if (bestNeighbor==-1){
            printf("no better neighbour, stopped at node &d with value=%d",current,value[current]);
            break;

        }

        printf("moved to node %d value= %d\n",bestNeighbor,value[bestNeighbor]);
        current=bestNeighbor;
    }
    printf("optimal value found at node %d value=%d",current,value[current]);
}

int main(){
    int edges , u , v_node, startNode;

    printf("enter no.of nodes: ");
    scanf("%d",&N);

    printf("enter values for each node\n");
    for(int i=0;i<N;i++){
        printf("value of node %d: ",i);
        scanf("%d",&value[i]);
    }

    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            graph[i][j]=0;

        }
    }

    printf("enter no.of edges: ");
    scanf("%d",&edges);

    printf("Enter edges as pairs (u v) meaning node u is connected to node v:\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v_node);
        graph[u][v_node] = 1;
        graph[v_node][u] = 1;   // undirected graph
    }

    // Show adjacency matrix
    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%d ", graph[i][j]);
        printf("\n");
    }

    printf("\nEnter starting node: ");
    scanf("%d", &startNode);

    hillClimb(startNode);

    return 0;


}