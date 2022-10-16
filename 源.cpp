#include<stdio.h>
#include<stdlib.h>
#define MAX 100
//����һ��ͼ�ṹ
typedef struct GNode* ptrG;
struct GNode {
	int vex[MAX];//�����
	int edge[MAX][MAX];//�߱�
	int vexnum;//����ĸ���
	int edgenum;//�ߵ�����
};
//����һ���߽ڵ�
struct ENode {
	int v1;//����1
	int v2;//����2
};
typedef struct ENode* Edge;
//����һ���������еĽṹ����ʵ��
struct QNode {
	int front;
	int rear;
	int data[MAX];
	int tag;//���ڼ�������Ƿ�����
};
typedef struct QNode* ptrQ;
int Dvex_tag[MAX] = { 0 };//���ڱ��������ȱ����б����ʹ��Ķ���
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
	printf("��������ڶ���\n");
	scanf_s("%d", &entryvex);
	printf("������ȱ���Ϊ\n");
	BFS(graph,entryvex);
	printf("\n");
	printf("��������ڶ���\n");
	scanf_s("%d", &entryvex);
	printf("������ȱ���Ϊ\n");
	DFS(graph, entryvex);
	return 0;
}
//��ʼ����ͼ
ptrG createNullGraph(int vexnum) {
	ptrG graph = (ptrG)malloc(sizeof(struct GNode));
	if (graph) {
		graph->vexnum = vexnum;
		graph->edgenum = 0;
		graph->edge[0][0] = { 0 };
		return graph;
	}
	printf("�ڴ�ռ�����ʧ��\n");
	return NULL;
}
//�����
void InsertEdge(ptrG graph, Edge e) {
	graph->edge[e->v1][e->v2] = 1;
	graph->edge[e->v2][e->v1] = 1;
}
//����һ��������ͼ���ڽӾ����ʾ
ptrG BulidGraph() {
	int nv;
	printf("�����붥��ĸ���\n");
	scanf_s("%d", &nv);
	ptrG graph = createNullGraph(nv);
	printf("������ߵ�����\n");
	scanf_s("%d", &graph->edgenum);
	//����ߵ���Ϣ
	if (graph->edgenum != 0) {
		//����һ���߽ڵ�
		Edge e = (Edge)malloc(sizeof(struct ENode));
		printf("�����������붥���ڶ��������±�\n");
		for (int i = 0; i < graph->edgenum; i++) {
			if (e) {
				//����ߵ���Ϣ
				scanf_s("%d %d", &e->v1, &e->v2);
			}
			else {
				printf("�߽ڵ��ڴ�����ʧ��\n");
				return NULL;
			}
			//�����
			InsertEdge(graph, e);
		}
	}
	//���붥������Ϣ
	printf("�����붥������Ϣ\n");
	for (int i = 0; i < graph->vexnum; i++) {
		scanf_s("%d", &graph->vex[i]);
	}
	return graph;
}
//������ȱ���
void BFS(ptrG graph,int entryvex) {
	int vex_tag[MAX] = { 0 };//0��ʾδ������1��ʾ�����ʹ���
	//����һ����������
	ptrQ q = createNullQueue();
	printf("%d ", entryvex);
	if (Index(graph, entryvex) != -1) {
		vex_tag[Index(graph, entryvex)] = 1;
	}
	//����ڶ������
	AddQ(q, entryvex);
	//��ʼ����
	while (!IsEmpty(q)) {
		//����ڶ������
		int v=DeleteQ(q);
		//��ʼ������w�ڽӵ����ж���
		for (int y = FistNeighbor(graph, v); y != -1; y = NextNeighbor(graph, v, graph->vex[y])) {
			if (vex_tag[y] == 0) {
				printf("%d ", graph->vex[y]);
				vex_tag[y] = 1;
				AddQ(q, graph->vex[y]);
			}
		}
	}
}
//������ȱ���
void DFS(ptrG graph, int entryvex) {
	
	printf("%d ", entryvex);//����һ����ڶ���
	//����ڶ�����vex_tag���λ�ø�ֵΪ1
	if (Index(graph, entryvex) != -1) {
		Dvex_tag[Index(graph, entryvex)] = 1;
	}
	//��ʼ������ȱ���
	for (int w = FistNeighbor(graph, entryvex); w != -1; w = NextNeighbor(graph,entryvex, graph->vex[w])) {
		if (!Dvex_tag[w]) {
			DFS(graph, graph->vex[w]);
		}
	}
}
//����һ���ն���
ptrQ createNullQueue() {
	ptrQ q = (ptrQ)malloc(sizeof(struct QNode));
	if (q) {
		q->front = -1;
		q->rear = -1;
		q->tag = 0;
		return q;
	}
	printf("�ڴ�����ʧ��\n");
	return NULL;
}
//�ж��Ƿ����
int IsFull(ptrQ q) {
	if ((q->rear-q->front==MAX||q->front == q->rear) && q->tag == 1) {
		return 1;
	}
	return 0;
}
//���
void AddQ(ptrQ q, int data) {
	//�ж��Ƿ����
	if (IsFull(q)) {
		printf("����\n");
		return;
	}
	//���
	q->rear++;
	q->rear = q->rear % MAX;//����ѭ��
	q->data[q->rear] = data;
	q->tag = 1;//��Ӹ�ֵΪ1
}
//�ж��Ƿ�ӿ�
int IsEmpty(ptrQ q) {
	if (q->front == q->rear && q->tag == 0) {
		return 1;
	}
	return 0;
}
//����
int DeleteQ(ptrQ q) {
	//�ж��Ƿ�ӿ�
	if (IsEmpty(q)) {
		printf("�ӿ�\n");
		return NULL;
	}
	//����
	q->front++;
	q->front = q->front % MAX;
	q->tag = 0;//���Ӹ�ֵΪ0
	return q->data[q->front];
}
//Ѱ���붥��V�ڽӵĵ�һ������,���������ڶ��������±�
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
	return -1;//��ʾû����ö����ڽӵĶ����û���ҵ�
}
//Ѱ���붥��V�ڽӵ�Y����һ����V�ڽӵĶ���
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
//���ض���V�ڶ��������±�
int Index(ptrG graph,int v) {
	for (int i = 0; i < graph->vexnum; i++) {
		if (graph->vex[i] == v) {
			return i;
		}
	}
	return -1;
}