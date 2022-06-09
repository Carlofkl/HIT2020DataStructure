#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 50
#define INFINITY 9999

typedef struct ENode *Edge;
struct ENode
{
    int v1,v2;
    int Weight;
};
typedef struct AdjVNode *PtrToAdjVNode;
struct AdjVNode
{
    int AdjV;
    int Weight;
    PtrToAdjVNode Next;
};
typedef struct Vnode
{
    PtrToAdjVNode FirstEdge;
}AdjList[MaxVertexNum];
typedef struct GNode *LGraph;
struct GNode
{
    int Nv;
    int Ne;
    AdjList G;
};
LGraph CreateGraph(int VertexNum)
{
    int v;
    LGraph Graph = (LGraph)malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (v=1;v<=Graph->Nv;v++)
        Graph->G[v].FirstEdge = NULL;
    return Graph;
}
void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->v2;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->v1].FirstEdge;
    Graph->G[E->v1].FirstEdge = NewNode;

    NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->v1;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->v2].FirstEdge;
    Graph->G[E->v2].FirstEdge = NewNode;
}
LGraph BuildGraph()
{
    LGraph Graph;
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
            E->v1;
            E->v2;
            InsertEdge(Graph, E);
        }
    }
    return Graph;
}
/*-------------------- ���㲢�鼯���� --------------------*/

/*typedef Vertex ElementType; /* Ĭ��Ԫ�ؿ����÷Ǹ�������ʾ
typedef Vertex SetName;     /* Ĭ���ø������±���Ϊ��������
typedef ElementType SetType[MaxVertexNum]; /* ���輯��Ԫ���±��0��ʼ */

void InitializeVSet( int S[], int N )
{ /* ��ʼ�����鼯 */
    int X;

    for ( X=1; X<=N; X++ ) S[X] = -1;
}

/*void Union( int S[], int Root1, int Root2 )
{ /* ����Ĭ��Root1��Root2�ǲ�ͬ���ϵĸ����
    /* ��֤С���ϲ���󼯺�
    if ( S[Root2] < S[Root1] ) { /* �������2�Ƚϴ�
        S[Root2] += S[Root1];     /* ����1���뼯��2
        S[Root1] = Root2;
    }
    else {                         /* �������1�Ƚϴ�
        S[Root1] += S[Root2];     /* ����2���뼯��1
        S[Root2] = Root1;
    }
}*/

int Find( int S[], int X )
{ /* Ĭ�ϼ���Ԫ��ȫ����ʼ��Ϊ-1 */
    if ( S[X] == -1 ) /* �ҵ����ϵĸ� */
        return X;
    else
        return S[X] = Find( S, S[X]); /* ·��ѹ�� */
}

int CheckCycle( int VSet[], int V1, int V2 )
{ /* �������V1��V2�ı��Ƿ������е���С�������Ӽ��й��ɻ�· */
    int Root1, Root2;

    Root1 = Find( VSet, V1 ); /* �õ�V1��������ͨ������ */
    Root2 = Find( VSet, V2 ); /* �õ�V2��������ͨ������ */

    if( Root1==Root2 ) /* ��V1��V2�Ѿ���ͨ����ñ߲���Ҫ */
        return 0;
     /* ����ñ߿��Ա��ռ���ͬʱ��V1��V2����ͬһ��ͨ�� */
    VSet[Root1] = Root2; //Union( VSet, Root1, Root2 );
    return 1;
}
/*-------------------- ���鼯������� --------------------*/

/*-------------------- �ߵ���С�Ѷ��� --------------------*/
void PercDown( Edge ESet, int p, int N )
{ /* �ı����4.24��PercDown( MaxHeap H, int p )    */
  /* ��N��Ԫ�صı���������ESet[p]Ϊ�����Ӷѵ���Ϊ����Weight����С�� */
    int Parent, Child;
    struct ENode X;

    X = ESet[p]; /* ȡ��������ŵ�ֵ */
    for( Parent=p; (Parent*2+1)<N; Parent=Child ) {
        Child = Parent * 2 + 1;
        if( (Child!=N-1) && (ESet[Child].Weight>ESet[Child+1].Weight) )
            Child++;  /* Childָ�������ӽ��Ľ�С�� */
        if( X.Weight <= ESet[Child].Weight ) break; /* �ҵ��˺���λ�� */
        else  /* ����X */
            ESet[Parent] = ESet[Child];
    }
    ESet[Parent] = X;
}

void InitializeESet( LGraph Graph, Edge ESet )
{ /* ��ͼ�ıߴ�������ESet�����ҳ�ʼ��Ϊ��С�� */
    int V;
    PtrToAdjVNode W;
    int ECount;

    /* ��ͼ�ıߴ�������ESet */
    ECount = 0;
    for ( V=0; V<Graph->Nv; V++ )
        for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
            if ( V < W->AdjV ) { /* �����ظ�¼������ͼ�ıߣ�ֻ��V1<V2�ı� */
                ESet[ECount].v1 = V;
                ESet[ECount].v2 = W->AdjV;
                ESet[ECount++].Weight = W->Weight;
            }
    /* ��ʼ��Ϊ��С�� */
    for ( ECount=Graph->Ne/2; ECount>=0; ECount-- )
        PercDown( ESet, ECount, Graph->Ne );
}

int GetEdge( Edge ESet, int CurrentSize )
{ /* ������ǰ�ѵĴ�СCurrentSize������ǰ��С��λ�õ����������� */

    /* ����С���뵱ǰ�ѵ����һ��λ�õı߽��� */
    struct ENode temp;
    temp = ESet[0];
    ESet[0] = ESet[CurrentSize-1];
    ESet[CurrentSize-1] = temp;
    //Swap( &ESet[0], &ESet[CurrentSize-1]);
    /* ��ʣ�µı߼�����������С�� */
    PercDown( ESet, 0, CurrentSize-1 );

    return CurrentSize-1; /* ������С������λ�� */
}
/*-------------------- ��С�Ѷ������ --------------------*/

void Kruskal(LGraph Graph)
{
    int TotalWeight;
    int ECount, NextEdge;
    int VSet[Graph->Nv]; //��������
    Edge ESet; //������
    LGraph MST = CreateGraph(Graph->Nv);

    InitializeVSet(VSet, Graph->Nv); //��ʼ�����㲢�鼯
    ESet = (Edge)malloc(sizeof(struct ENode)*Graph->Ne);
    InitializeESet(Graph, ESet); //��ʼ������С��
    TotalWeight = ECount = 0; //��ʼ����¼�ı�����Ȩ�غ�

    NextEdge = Graph->Ne; //ԭʼ�߼��Ĺ�ģ
    //printf("hhh\n");
    while (ECount <Graph->Nv-1)
    {
        NextEdge = GetEdge(ESet, NextEdge); //�ӱ���С���еõ���С�ߵ�λ��
        if (NextEdge < 0)  break;//�߼�����
        //����ñߵļ��벻���ɻ�·�������˵Ľ�㲻����ͬһ��ͨ��
        if (CheckCycle(VSet, ESet[NextEdge].v1, ESet[NextEdge].v2)==1)
        {
            //���ñ߲���MST��
            //InsertEdge(MST, ESet+NextEdge);
            TotalWeight += ESet[NextEdge].Weight;
            ECount++;
            printf("%d %d\n",ESet[NextEdge].v1, ESet[NextEdge].v2);
        }
    }
    if (ECount < Graph->Nv-1)
        TotalWeight = -1; //������
    printf("%d",TotalWeight);
}
int main()
{
    int i ,j;
    LGraph Graph = BuildGraph();
    printf("\n");
    /*for (i=1;i<=Graph->Nv;i++)
    {
        while(Graph->G[i].FirstEdge!=NULL)
        {
            printf("%d %d||",Graph->G[i].FirstEdge->AdjV,Graph->G[i].FirstEdge->Weight);
            Graph->G[i].FirstEdge = Graph->G[i].FirstEdge->Next;
        }
        printf("\n");
    }*/
    Kruskal(Graph);
    return 0;
}
