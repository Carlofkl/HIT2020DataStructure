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
/*-------------------- 最小堆定义 --------------------*/
typedef struct HNode *MinHeap;
struct HNode{
    int *data;
    int size;
    int capacity;
};
MinHeap CreateHeap(int MaxSize)
{
    MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
    H->data = (int *)malloc((MaxSize+1)*sizeof(int));
    H->size = 0;
    H->capacity = MaxSize;
    H->data[0] = INFINITY+1;
    return H;
}
int IsFull(MinHeap H)
{
    if (H->size == H->capacity);
        return 1;
    return 0;
}
int IsEmpty(MinHeap H)
{
    if (H->size == 0)
        return 1;
    return 0;
}
int Insert(MinHeap H, int x)
{
    int i;
    if (IsFull(H))
    {
        printf("最小堆已满");
        return -1;
    }
    i = ++H->size; //i指向插入后堆中的最后一个元素的位置
    for (;H->data[i/2]<x;i/=2)
        H->data[i] = H->data[i/2]; //上滤x
    H->data[i] = x; //将x插入
    return 1;
}
int DeleteMin(MinHeap H)
{//从最大堆H中取出键值为最大的元素，并删除一个结点
   int parent, child;
   int MinItem, x;
   if(IsEmpty(H))
   {
       printf("最大堆已为空");
       return -1;
   }
   MinItem = H->data[1];//取出根结点存放的最大值
   //用最小堆中最后一个元素从根结点开始向上过滤下层结点
   x = H->data[H->size--]; //堆得规模要减小
   for (parent = 1; parent*2 <= H->size; parent = child)
   {
        child = parent * 2;
        if ((child!=H->size) && (H->data[child] < H->data[child+1]))
            child ++; // child 较大者
        if (x>= H->data[child]) break;
        else H->data[parent] = H->data[child];
   }
   H->data[parent] = x;
   return MinItem;
}
void PercDown(MinHeap H, int p)
{
    int parent, child;
    int x;
    x = H->data[p];
    for (parent=p;parent*2<=H->size;parent=child)
    {
        child = parent * 2;
        if ((child!=H->size) && (H->data[child]<H->data[child+1]))
            child ++;
        if (x>=H->data[child]) break;
        else //下率
            H->data[parent] = H->data[child];
    }
    H->data[parent] = x;
}
void BuildHeap(MinHeap H)
{//调整H->data[]中的元素，使满足最大堆的有序性
    int i;
    for (i=H->size/2;i>0;i--)
        PercDown(H,i);
}
int GetMinDist( MGraph Graph, int dist[])
{ /* 给定当前堆的大小CurrentSize，将当前最小边位置弹出并调整堆 */

    /* 将最小边与当前堆的最后一个位置的边交换 */
    int CurrentSize = Graph->Nv;
    int temp;
    temp = dist[0];
    dist[0] = dist[CurrentSize-1];
    dist[CurrentSize-1] = temp;
    //Swap( &ESet[0], &ESet[CurrentSize-1]);
    /* 将剩下的边继续调整成最小堆 */
    PercDown( dist,  CurrentSize-1 );

    return CurrentSize-1; /* 返回最小dist下标 */
}
/*-------------------- 最小堆定义结束 --------------------*/

int FindMinDist(MGraph Graph, int dist[])
{
    int v, MinDist, MinV;
    MinDist = INFINITY;
    for (v=0;v<Graph->Nv;v++)
    {
        if (dist[v]!=0 && dist[v]<MinDist)
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
void Prim(MGraph Graph)
{
    /*初始化*/
    int dist[Graph->Nv], TotalWeight, VCount;
    int v, w, parent[Graph->Nv];
    Edge E = (Edge)malloc(sizeof(struct ENode));
    MGraph MST = CreateGraph(Graph->Nv);
    TotalWeight = 0;
    VCount = 0;
    for (v=0;v<Graph->Nv;v++)
    {
        dist[v] = Graph->G[0][v];
        parent[v] = 0;
    }
    /*收录源点*/
    dist[0] = 0;
    VCount ++;
    parent[0] = -1;

    while(1)
    {
        /*将v收录MST*/
        v = FindMinDist(Graph, dist);
        if (v==-1)
            break;
        E->v1 = parent[v];
        E->v2 = v;
        E->Weight = dist[v];
        InsertEdge(MST, E);
        TotalWeight += dist[v];
        VCount ++;
        dist[v] = 0;
        /*扩展*/
        for (w=0;w<Graph->Nv;w++)
        {
            if (dist[w]!=0 && Graph->G[v][w]<INFINITY)
                if (Graph->G[v][w]<dist[w])
                {
                    dist[w] = Graph->G[v][w];
                    parent[w] = v;
                }
        }
    }
    if (VCount < Graph->Nv)
        TotalWeight = -1;

    printf("%d\n", TotalWeight);
    for (v=0;v<MST->Nv;v++)
        for (w=v;w<MST->Nv;w++)
        {
            if (MST->G[v][w]!=INFINITY)
                printf("%d %d\n", v+1, w+1);
        }
}
int main()
{
    int i ,j;
    MGraph Graph = BuildGraph();
    Prim(Graph);
    return 0;
}
