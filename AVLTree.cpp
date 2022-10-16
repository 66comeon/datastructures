#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct AvlNode {
	int data;
	struct AvlNode* left;
	struct AvlNode* right;
	int height;//平衡因子
};
typedef struct AvlNode* position;//用于节点
typedef struct AvlNode* avltree;//用于函数返回值的类型
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
	//创建根节点
	avltree root = createNode(4);
	//向树中插入新节点
	root=Insert(2, root);//随时记录根节点的地址因为根节点可能会发生变化
	root=Insert(6, root);
	root=Insert(1, root);
	root=Insert(3, root);
	root=Insert(5, root);
	root=Insert(7, root);
	root=Insert(16, root);
	printf("插入新节点前\n");
	preOrder(root);
	printf("\n插入新节点后\n");
	root = Insert(15, root);//预测这样插入会破坏7所在节点应进行左右双旋，旋转后先序遍历应为4，2，1，3，6，5，15，7，16
	preOrder(root);
	printf("\n再次插入\n");
	root=Insert(14, root);//预测结果应为4，2，1，3，7，6，5，15，14，16
	preOrder(root);
	printf("\n插入一个破坏根节点的情况\n");
	root = Insert(13, root);//预测结果位7,4,2,1,3,6,5,15,14,13,16
	preOrder(root);


	return 0;
}
//创建节点
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
//求树的高度
int Height(avltree T) {
	if (!T)
		return -1;
	else
		return T->height;
}
//两者求最大
int Max(int x, int y) {
	int max = x;
	if (x < y)
		max = y;
	return max;
}
//在二叉树中插入节点
avltree Insert(int data, avltree T) {
	if (!T) {
		//注意这里不是新建一个变量T，新建也不能像这样：
		//position T=createNode(data)这样做T只是一个局部变量出去以后将会变为NULL
		 T = createNode(data);
		//这里需要加一个判断看新节点是否创建成功，避免下面对空指针异常引用
		if (T == NULL) {
			printf("新节点创建失败\n");
			return NULL;
		}
	}
	else if (data < T->data) {//往左边插入
		T->left = Insert(data, T->left);
		if (fabs(Height(T->left) - Height(T->right)) == 2)
			if (data < T->left->data)//成立就做左单旋
				T = RotateWithLeft(T);
			else//否则做一次右左旋转
				T = DoubleRotateWithLeft(T);
	}
	else if(data>T->data) {//往右边插入
		T->right = Insert(data, T->right);
		if (fabs(Height(T->left) - Height(T->right)) == 2)
			if (data > T->right->data)//成立就做一次右单旋
				T = RotateWithRight(T);
			else//否则就做一次左右旋转
				T = DoubleRotateWithRight(T);
	}
	T->height = Max(Height(T->left), Height(T->right)) + 1;
	return T;//返回根节点
}
//左单旋
avltree RotateWithLeft(avltree founder) {//将发现者传下来
	//将发现者的左子树作为父节点
	position temp = founder->left;
	founder->left = temp->right;//因为temp和temp->left是发现者的左子树比发现者小，所以把他挂在发现者的左子树上
	temp->right = founder;//将发现者挂在temp的右子树上以保证旋转后该数仍为二叉搜索树
	//更新发现者和temp的平衡因子信息
	founder->height = Max(Height(founder->left), Height(founder->right)) + 1;
	temp->height = Max(Height(temp->left), Height(temp->right)) + 1;
	return temp;//返回新新节点
}
//右单旋
avltree  RotateWithRight(avltree founder) {
	position temp = founder->right;
	founder->right = temp->left;
	temp->left = founder;
	founder->height = Max(Height(founder->left), Height(founder->right)) + 1;
	temp->height = Max(Height(temp->left), Height(temp->right)) + 1;
	return temp;

}
//右左双旋
avltree DoubleRotateWithLeft(avltree founder) {
	//先进行一次右单旋
	founder->left = RotateWithRight(founder->left);
	//最后进行一次左单旋
	return RotateWithLeft(founder);
}
//左右双旋
avltree DoubleRotateWithRight(avltree founder) {
	//先进行一次左单旋
	founder->right = RotateWithLeft(founder->right);
	//最后进行一次右单旋
	return RotateWithRight(founder);
}
//先序遍历
void preOrder(avltree T) {
	if (T) {
		printf("%d ", T->data);
		preOrder(T->left);
		preOrder(T->right);
	}
}
