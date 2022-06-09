#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 50
#define INFINITY 9999
typedef struct GNode *MGraph;
struct GNode
{
    int Nv;
    int Ne;
    int G[MaxVertexNum][MaxVertexNum];
    int V1, V2;
};
typedef struct ENode *Edge;
struct ENode
{
    int v1,v2;
    int Weight;
};
MGraph CreateGraph(int VertexNum)
{
    MGraph Graph;
    int v,w;
    Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (v=0;v<Graph->Nv;v++)
        for (w=0;w<Graph->Nv;w++)
            Graph->G[v][w] = INFINITY;
    return Graph;
}
void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->v1][E->v2] = E->Weight;
    Graph->G[E->v2][E->v1] = E->Weight;
}
MGraph BuildGraph()
{
    MGraph Graph;
    Edge E;
    int Nv, i;
    scanf("%d", &Nv);
    Graph = CreateGraph(Nv);
    scanf("%d", &Graph->Ne);
    scanf("%d %d", &Graph->V1, &Graph->V2);
    Graph->V1--;
    Graph->V2--;
    if (Graph->Ne!=0)
    {
        E = (Edge)malloc(sizeof(struct ENode));
        for (i=0;i<Graph->Ne;i++)
        {
            scanf("%d %d %d", &E->v1, &E->v2, &E->Weight);
            E->v1--;
            E->v2--;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
int FindMinDist(MGraph Graph, int dist[],int collected[])
{
    int v, MinDist, MinV;
    MinDist = INFINITY;
    for (v=0;v<Graph->Nv;v++)
    {
        if (collected[v]==0 && dist[v]<MinDist)
        {
            MinDist = dist[v];
            MinV = v;
        }
    }
    if (MinDist < INFINITY)
        return MinV;
    else
        return -1;
}
Dijkstra(MGraph Graph)
{
    /*初始化*/
    int dist[Graph->Nv];
    int v, w;
    int collected[Graph->Nv];
    for (v=0;v<Graph->Nv;v++)
    {
        dist[v] = Graph->G[Graph->V1][v];
        collected[v] = 0;
    }
    /*收录源点*/
    dist[Graph->V1] = 0;
    collected[Graph->V1] = 1;
    while(1)
    {
        /*将v收录MST*/
        v = FindMinDist(Graph, dist, collected);
        if (v==-1) break;
        collected[v] = 1;
        /*扩展*/
        for (w=0;w<Graph->Nv;w++)
        {
            if (collected[w]==0 && Graph->G[v][w]<INFINITY)
                if (dist[v]+Graph->G[v][w]<dist[w])
                {
                    dist[w] = Graph->G[v][w]+dist[v];
                }
        }
    }
    printf("%d\n", dist[Graph->V2]);
}
int main()
{
    int i ,j;
    MGraph Graph = BuildGraph();
    Dijkstra(Graph);
    return 0;
}
