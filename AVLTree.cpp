#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct AvlNode {
	int data;
	struct AvlNode* left;
	struct AvlNode* right;
	int height;//ƽ������
};
typedef struct AvlNode* position;//���ڽڵ�
typedef struct AvlNode* avltree;//���ں�������ֵ������
avltree createNode(int data);
avltree Insert(int data, avltree T);
int Max(int x, int y);
int Height(avltree T);
avltree RotateWithLeft(avltree founder);
avltree  RotateWithRight(avltree founder);
avltree DoubleRotateWithLeft(avltree founder);
avltree DoubleRotateWithRight(avltree founder);
void preOrder(avltree T);
int main() {
	//�������ڵ�
	avltree root = createNode(4);
	//�����в����½ڵ�
	root=Insert(2, root);//��ʱ��¼���ڵ�ĵ�ַ��Ϊ���ڵ���ܻᷢ���仯
	root=Insert(6, root);
	root=Insert(1, root);
	root=Insert(3, root);
	root=Insert(5, root);
	root=Insert(7, root);
	root=Insert(16, root);
	printf("�����½ڵ�ǰ\n");
	preOrder(root);
	printf("\n�����½ڵ��\n");
	root = Insert(15, root);//Ԥ������������ƻ�7���ڽڵ�Ӧ��������˫������ת���������ӦΪ4��2��1��3��6��5��15��7��16
	preOrder(root);
	printf("\n�ٴβ���\n");
	root=Insert(14, root);//Ԥ����ӦΪ4��2��1��3��7��6��5��15��14��16
	preOrder(root);
	printf("\n����һ���ƻ����ڵ�����\n");
	root = Insert(13, root);//Ԥ����λ7,4,2,1,3,6,5,15,14,13,16
	preOrder(root);


	return 0;
}
//�����ڵ�
avltree createNode(int data) {
	position t = (avltree)malloc(sizeof(struct AvlNode));
	if (t) {
		t->data = data;
		t->left = NULL;
		t->right = NULL;
		t->height = 0;
		return t;
	}
	return NULL;
}
//�����ĸ߶�
int Height(avltree T) {
	if (!T)
		return -1;
	else
		return T->height;
}
//���������
int Max(int x, int y) {
	int max = x;
	if (x < y)
		max = y;
	return max;
}
//�ڶ������в���ڵ�
avltree Insert(int data, avltree T) {
	if (!T) {
		//ע�����ﲻ���½�һ������T���½�Ҳ������������
		//position T=createNode(data)������Tֻ��һ���ֲ�������ȥ�Ժ󽫻��ΪNULL
		 T = createNode(data);
		//������Ҫ��һ���жϿ��½ڵ��Ƿ񴴽��ɹ�����������Կ�ָ���쳣����
		if (T == NULL) {
			printf("�½ڵ㴴��ʧ��\n");
			return NULL;
		}
	}
	else if (data < T->data) {//����߲���
		T->left = Insert(data, T->left);
		if (fabs(Height(T->left) - Height(T->right)) == 2)
			if (data < T->left->data)//������������
				T = RotateWithLeft(T);
			else//������һ��������ת
				T = DoubleRotateWithLeft(T);
	}
	else if(data>T->data) {//���ұ߲���
		T->right = Insert(data, T->right);
		if (fabs(Height(T->left) - Height(T->right)) == 2)
			if (data > T->right->data)//��������һ���ҵ���
				T = RotateWithRight(T);
			else//�������һ��������ת
				T = DoubleRotateWithRight(T);
	}
	T->height = Max(Height(T->left), Height(T->right)) + 1;
	return T;//���ظ��ڵ�
}
//����
avltree RotateWithLeft(avltree founder) {//�������ߴ�����
	//�������ߵ���������Ϊ���ڵ�
	position temp = founder->left;
	founder->left = temp->right;//��Ϊtemp��temp->left�Ƿ����ߵ��������ȷ�����С�����԰������ڷ����ߵ���������
	temp->right = founder;//�������߹���temp�����������Ա�֤��ת�������Ϊ����������
	//���·����ߺ�temp��ƽ��������Ϣ
	founder->height = Max(Height(founder->left), Height(founder->right)) + 1;
	temp->height = Max(Height(temp->left), Height(temp->right)) + 1;
	return temp;//�������½ڵ�
}
//�ҵ���
avltree  RotateWithRight(avltree founder) {
	position temp = founder->right;
	founder->right = temp->left;
	temp->left = founder;
	founder->height = Max(Height(founder->left), Height(founder->right)) + 1;
	temp->height = Max(Height(temp->left), Height(temp->right)) + 1;
	return temp;

}
//����˫��
avltree DoubleRotateWithLeft(avltree founder) {
	//�Ƚ���һ���ҵ���
	founder->left = RotateWithRight(founder->left);
	//������һ������
	return RotateWithLeft(founder);
}
//����˫��
avltree DoubleRotateWithRight(avltree founder) {
	//�Ƚ���һ������
	founder->right = RotateWithLeft(founder->right);
	//������һ���ҵ���
	return RotateWithRight(founder);
}
//�������
void preOrder(avltree T) {
	if (T) {
		printf("%d ", T->data);
		preOrder(T->left);
		preOrder(T->right);
	}
}
