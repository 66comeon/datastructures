#include<stdio.h>
#include<stdlib.h>
#define MAX 100
//建立一个图结构
typedef struct GNode* ptrG;
struct GNode {
	int vex[MAX];//顶点表
	int edge[MAX][MAX];//边表
	int vexnum;//顶点的个数
	int edgenum;//边的条数
};
//建立一个边节点
struct ENode {
	int v1;//顶点1
	int v2;//顶点2
};
typedef struct ENode* Edge;
//建立一个辅助队列的结构数组实现
struct QNode {
	int front;
	int rear;
	int data[MAX];
	int tag;//用于鉴别队列是否满了
};
typedef struct QNode* ptrQ;
int Dvex_tag[MAX] = { 0 };//用于标记深度优先遍历中被访问过的顶点
ptrG createNullGraph(int vexnum);
void InsertEdge(ptrG graph, Edge e);
ptrG BulidGraph();
void BFS(ptrG graph, int entryvex);
ptrQ createNullQueue();
int IsFull(ptrQ q);
void AddQ(ptrQ q, int data);
int IsEmpty(ptrQ q);
int DeleteQ(ptrQ q);
int FistNeighbor(ptrG graph, int v);
int NextNeighbor(ptrG graph, int v, int y);
int Index(ptrG graph, int v);
void DFS(ptrG graph, int entryvex);
int main() {
	int entryvex;
	ptrG graph = BulidGraph();
	printf("请输入入口顶点\n");
	scanf_s("%d", &entryvex);
	printf("广度优先遍历为\n");
	BFS(graph,entryvex);
	printf("\n");
	printf("请输入入口顶点\n");
	scanf_s("%d", &entryvex);
	printf("深度优先遍历为\n");
	DFS(graph, entryvex);
	return 0;
}
//初始化空图
ptrG createNullGraph(int vexnum) {
	ptrG graph = (ptrG)malloc(sizeof(struct GNode));
	if (graph) {
		graph->vexnum = vexnum;
		graph->edgenum = 0;
		graph->edge[0][0] = { 0 };
		return graph;
	}
	printf("内存空间申请失败\n");
	return NULL;
}
//插入边
void InsertEdge(ptrG graph, Edge e) {
	graph->edge[e->v1][e->v2] = 1;
	graph->edge[e->v2][e->v1] = 1;
}
//建立一个完整的图用邻接矩阵表示
ptrG BulidGraph() {
	int nv;
	printf("请输入顶点的个数\n");
	scanf_s("%d", &nv);
	ptrG graph = createNullGraph(nv);
	printf("请输入边的条数\n");
	scanf_s("%d", &graph->edgenum);
	//插入边的信息
	if (graph->edgenum != 0) {
		//申请一个边节点
		Edge e = (Edge)malloc(sizeof(struct ENode));
		printf("请输入欲插入顶点在顶点表里的下标\n");
		for (int i = 0; i < graph->edgenum; i++) {
			if (e) {
				//读入边的信息
				scanf_s("%d %d", &e->v1, &e->v2);
			}
			else {
				printf("边节点内存申请失败\n");
				return NULL;
			}
			//插入边
			InsertEdge(graph, e);
		}
	}
	//读入顶点表的信息
	printf("请输入顶点表的信息\n");
	for (int i = 0; i < graph->vexnum; i++) {
		scanf_s("%d", &graph->vex[i]);
	}
	return graph;
}
//广度优先遍历
void BFS(ptrG graph,int entryvex) {
	int vex_tag[MAX] = { 0 };//0表示未被访问1表示被访问过了
	//建立一个辅助队列
	ptrQ q = createNullQueue();
	printf("%d ", entryvex);
	if (Index(graph, entryvex) != -1) {
		vex_tag[Index(graph, entryvex)] = 1;
	}
	//让入口顶点入队
	AddQ(q, entryvex);
	//开始遍历
	while (!IsEmpty(q)) {
		//让入口顶点出队
		int v=DeleteQ(q);
		//开始遍历和w邻接的所有顶点
		for (int y = FistNeighbor(graph, v); y != -1; y = NextNeighbor(graph, v, graph->vex[y])) {
			if (vex_tag[y] == 0) {
				printf("%d ", graph->vex[y]);
				vex_tag[y] = 1;
				AddQ(q, graph->vex[y]);
			}
		}
	}
}
//深度优先遍历
void DFS(ptrG graph, int entryvex) {
	
	printf("%d ", entryvex);//访问一下入口顶点
	//将入口顶点在vex_tag里的位置赋值为1
	if (Index(graph, entryvex) != -1) {
		Dvex_tag[Index(graph, entryvex)] = 1;
	}
	//开始深度优先遍历
	for (int w = FistNeighbor(graph, entryvex); w != -1; w = NextNeighbor(graph,entryvex, graph->vex[w])) {
		if (!Dvex_tag[w]) {
			DFS(graph, graph->vex[w]);
		}
	}
}
//创建一个空队列
ptrQ createNullQueue() {
	ptrQ q = (ptrQ)malloc(sizeof(struct QNode));
	if (q) {
		q->front = -1;
		q->rear = -1;
		q->tag = 0;
		return q;
	}
	printf("内存申请失败\n");
	return NULL;
}
//判读是否队满
int IsFull(ptrQ q) {
	if ((q->rear-q->front==MAX||q->front == q->rear) && q->tag == 1) {
		return 1;
	}
	return 0;
}
//入队
void AddQ(ptrQ q, int data) {
	//判读是否队满
	if (IsFull(q)) {
		printf("队满\n");
		return;
	}
	//入队
	q->rear++;
	q->rear = q->rear % MAX;//利于循环
	q->data[q->rear] = data;
	q->tag = 1;//入队赋值为1
}
//判读是否队空
int IsEmpty(ptrQ q) {
	if (q->front == q->rear && q->tag == 0) {
		return 1;
	}
	return 0;
}
//出队
int DeleteQ(ptrQ q) {
	//判读是否队空
	if (IsEmpty(q)) {
		printf("队空\n");
		return NULL;
	}
	//出队
	q->front++;
	q->front = q->front % MAX;
	q->tag = 0;//出队赋值为0
	return q->data[q->front];
}
//寻找与顶点V邻接的第一个顶点,并返回其在顶点表里的下标
int FistNeighbor(ptrG graph, int v) {
	int i,j;
	for (i = 0; i < graph->vexnum; i++) {
		if (graph->vex[i] == v) {
			break;
		}
	}
	for (j = 0; j < graph->vexnum; j++) {
		if (graph->edge[i][j] == 1) {
			return j;
		}
	}
	return -1;//表示没有与该顶点邻接的顶点或没有找到
}
//寻找与顶点V邻接的Y的下一个与V邻接的顶点
int NextNeighbor(ptrG graph, int v, int y) {
	int i, j,k;
	for (i = 0; i < graph->vexnum; i++) {
		if (graph->vex[i] == v) {
			break;
		}
	}
	for (k = 0; k < graph->vexnum; k++) {
		if (graph->vex[k] == y) {
			break;
		}
	}
	for (j = k + 1; j < graph->vexnum; j++) {
		if (graph->edge[i][j] == 1) {
			return j;
		}
	}
	return -1;
}
//返回顶点V在顶点表里的下标
int Index(ptrG graph,int v) {
	for (int i = 0; i < graph->vexnum; i++) {
		if (graph->vex[i] == v) {
			return i;
		}
	}
	return -1;
}