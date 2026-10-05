#include <stdio.h>
#include <limits.h>

#define N 20
#define found -1 

int graph[N][N];
int nodes;
int onPath;
// int path[N];
// int pathlen;
int goalcost;
int parent[N];
int h[N];
int goal;

int movegen(int state , ){
    for(int i =0 , i<nodes ; i++){
        if(graph[node][i] > 0 ){
            succ[count++]=i;
        }
    }return count;
}

int goaltest(int node , int goal){
    retunr node==goal;
}


void reconstuctpath(int goal){
    int pathlen;
    int count

    for(int temp =goal , temp !=-1 ; temp=parent[temp]){
        path[count++]=temp;
    }
    printf("path: \n");
    for(int i = count -1 ; i>=0 ; i--){
        printf("%d->" , path[i]);

    }
    printf("totalcost: ", goalcost);
}

int search(int node , g, threshold ){
    f = g + h[i];
    if(f> threshold){
        return f;
    }
    if(goaltest(node , goal)){
        return found;
    }

    for
}