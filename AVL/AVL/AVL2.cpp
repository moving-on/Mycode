#include <cstdio>
#include <cstdlib>

typedef int ElementType;
typedef struct AvlNode              // AVL���Ľڵ�
{
	ElementType data;
	struct AvlNode *left;           // ����
	struct AvlNode *right;          // �Һ���
	int Height;
}*Position, *AvlTree;

AvlTree MakeEmpty(AvlTree T);
Position Find(ElementType x, AvlTree T);
Position FindMin(AvlTree T);
Position FindMax(AvlTree T);
AvlTree  Insert(ElementType x, AvlTree T);
AvlTree  Delete(ElementType x, AvlTree T);
ElementType Retrieve(Position P);
void Display(AvlTree T);

AvlTree MakeEmpty(AvlTree T)
{
	if (T != NULL)
	{
		MakeEmpty(T->left);
		MakeEmpty(T->right);
		free(T);
	}
	return NULL;
}

/*
* ���� ��������ͨ���������һ���Ľ��У����Ժķ�O(log n)ʱ�䣬��ΪAVL�����Ǳ���ƽ��ġ�
* ����Ҫ�����׼�������Ľṹ�������ڲ��Ҷ��ı䡣����������չ������������ģ�������Ϊ���Ҷ�������ṹ����
*/
Position Find(ElementType x, AvlTree T)
{
	if (T == NULL)
		return NULL;
	if (x < T->data)
		return Find(x, T->left);
	else if (x > T->data)
		return Find(x, T->right);
	else
		return  T;
}
/*
*   FindMax��FindMin ����������Сֵ��
*/
Position FindMin(AvlTree T)
{
	if (T == NULL)
		return NULL;
	if (T->left == NULL)
		return T;
	else
		return FindMin(T->left);
}
Position FindMax(AvlTree T)
{
	if (T != NULL)
		while (T->right != NULL)
			T = T->right;
	return T;
}
/*
*  ���ؽڵ�ĸ߶�
*/
static int Height(Position P)
{
	if (P == NULL)
		return -1;
	else
		return P->Height;
}
static int Max(int h1, int h2)
{
	return h1 > h2 ? h1 : h2;
}
/*
*  �˺�������k2ֻ��һ�����ӵĵ���ת��
*  ��K2����������֮����ת��
*  ���¸߶ȣ������µĸ��ڵ�
*/
static Position SingleRotateWithLeft(Position k2)     // LL��ת
{
	Position k1;
	k1 = k2->left;
	k2->left = k1->right;
	k1->right = k2;
	// ��Ϊ�Ƚϵ������Һ��ӵĸ߶ȣ������󸸽ڵ�ĸ߶�Ҫ��1
	k2->Height = Max(Height(k2->left), Height(k2->right)) + 1;
	k1->Height = Max(Height(k1->left), Height(k2->right)) + 1;
	return k1;
}
/*
*  �˺�������k1ֻ��һ���Һ��ӵĵ���ת��
*  ��K1�������Һ���֮����ת��
*  ���¸߶ȣ������µĸ��ڵ�
*/
static Position SingleRotateWithRight(Position k1)  // RR��ת
{
	Position k2;
	k2 = k1->right;
	k1->right = k2->left;
	k2->left = k1;
	/*����λ�ñ���, Ҫ���½��ĸ߶�ֵ*/
	k1->Height = Max(Height(k1->left), Height(k1->right)) + 1;
	k2->Height = Max(Height(k2->left), Height(k2->right)) + 1;
	return k2;
}
/*
* �˺������ڵ� ��� k3��һ�����ӣ��Լ�
* �������������Һ��ӣ�ִ�����˫��ת
* ���¸߶ȣ������µĸ��ڵ�
*/
static Position DoubleRotateLeft(Position k3)    // LR��ת
{
	//�� k3 �����ӣ�ִ���Ҳ൥��ת
	k3->left = SingleRotateWithRight(k3->left);
	// �ٶ� k3 ���� ��൥��ת
	return SingleRotateWithLeft(k3);
}
/*
* �˺������ڵ� ��� k4��һ���Һ��ӣ��Լ�
* �����Һ����������ӣ�ִ�����˫��ת
* ���¸߶ȣ������µĸ��ڵ�
*/
static Position DoubleRotateRight(Position k4)    // RL��ת
{
	//�� k4 ���Һ��ӣ�ִ����൥��ת
	k4->right = SingleRotateWithLeft(k4->right);
	// �ٶ� k4 ���� �Ҳ൥��ת
	return SingleRotateWithRight(k4);
}
/*
*  ��AVL���������ͨ����ͬ����δƽ��Ķ��������һ���Ѹ�����ֵ�������У�
*  �����Ե���������ڵ��ۻأ����ڲ����ڼ��Ϊ��ƽ������нڵ��Ͻ�����ת����ɡ�
*  ��Ϊ�ۻص����ڵ��·;�������1.5��log n���ڵ㣬��ÿ��AVL��ת���ķѺ㶨��ʱ�䣬
*  ���봦���������Ϻķ�O(log n) ʱ�䡣
*/
AvlTree  Insert(ElementType x, AvlTree T)
{
	//���T�����ڣ��򴴽�һ���ڵ���
	if (T == NULL)
	{
		T = (AvlTree)malloc(sizeof(struct AvlNode));
		{
			T->data = x;
			T->Height = 0;
			T->left = T->right = NULL;
		}
	}
	// ���Ҫ�����Ԫ��С�ڵ�ǰԪ��
	else if (x < T->data)
	{
		//�ݹ����
		T->left = Insert(x, T->left);
		//����Ԫ��֮���� T �����������������߶� ֮���� 2���������� AVLƽ�����ԣ���Ҫ����
		if (Height(T->left) - Height(T->right) == 2)
		{
			//��x���뵽��T->left����ֻ࣬�� ��൥��ת
			if (x < T->left->data)
				T = SingleRotateWithLeft(T);       // LL��ת
			else
				// x ���뵽��T->left���Ҳ࣬��Ҫ���˫��ת
				T = DoubleRotateLeft(T);          // LR��ת
		}
	}
	// ���Ҫ�����Ԫ�ش��ڵ�ǰԪ��
	else if (x > T->data)
	{
		T->right = Insert(x, T->right);
		if (Height(T->right) - Height(T->left) == 2)
		{
			if (x > T->right->data)
				T = SingleRotateWithRight(T);     //RR ��ת
			else
				T = DoubleRotateRight(T);        //RL��ת
		}
	}
	T->Height = Max(Height(T->left), Height(T->right)) + 1;
	return T;
}
/*
*  �Ե����ڵ���е�AVL����
*/
AvlTree Rotate(AvlTree T)
{

	if (Height(T->left) - Height(T->right) == 2)
	{
		if (Height(T->left->left) >= Height(T->left->right))
			T = SingleRotateWithLeft(T);  // LL��ת
		else
			T = DoubleRotateLeft(T);     // LR��ת
	}
	if (Height(T->right) - Height(T->left) == 2)
	{
		if (Height(T->right->right) >= Height(T->right->left))
			T = SingleRotateWithRight(T);  // RR��ת
		else
			T = DoubleRotateRight(T);     // RL��ת
	}
	return T;
}
/*
* ���ȶ�λҪɾ���Ľڵ㣬Ȼ���øýڵ���Һ��ӵ��������滻�ýڵ㣬
* �����µ����Ըýڵ�Ϊ��������ΪAVL�����������������������������
* ɾ�������������Ϻķ�O(log n) ʱ�䡣
*/
AvlTree  Delete(ElementType x, AvlTree T)
{
	if (T == NULL)
		return NULL;
	if (T->data == x)           // Ҫɾ���� x ���ڵ�ǰ�ڵ�Ԫ��
	{
		if (T->right == NULL)  // ����Ҫɾ���Ľڵ� T ���Һ���Ϊ��,��ֱ��ɾ��
		{
			AvlTree tmp = T;
			T = T->left;
			free(tmp);
		}
		else                 /* �����ҵ� T->right ��������Ӵ��� T */
		{
			AvlTree tmp = T->right;
			while (tmp->left)
				tmp = tmp->left;
			T->data = tmp->data;
			/* ����������T �����ֽڵ���е���*/
			T->right = Delete(T->data, T->right);
			T->Height = Max(Height(T->left), Height(T->right)) + 1;
		}
		return T;
	}
	else if (x > T->data)                       // Ҫɾ���� x ���ڵ�ǰ�ڵ�Ԫ�أ���T���������в���ɾ��
	{
		T->right = Delete(x, T->right);
	}
	else                                       // Ҫɾ���� x С�ڵ�ǰ�ڵ�Ԫ�أ���T���������в���ɾ��
	{
		T->left = Delete(x, T->left);
	}
	/*
	*   ��ɾ��Ԫ�غ����ƽ��
	*/
	T->Height = Max(Height(T->left), Height(T->right)) + 1;
	if (T->left != NULL)
		T->left = Rotate(T->left);
	if (T->right != NULL)
		T->right = Rotate(T->right);
	if (T)
		T = Rotate(T);
	return T;
}
/*
* ���ص�ǰλ�õ�Ԫ��
*/
ElementType Retrieve(Position P)
{
	return P->data;
}
/*
* �������
*/
void Display(AvlTree T)
{
	static int n = 0;
	if (NULL != T)
	{
		Display(T->left);
		printf("[%d] ndata=%d \n", ++n, T->data);
		Display(T->right);
	}
}

#define N 15
int main(void) {
	AvlTree T = NULL;
	int i;
	int j = 0;
	T = MakeEmpty(NULL);
	for (i = 0; i < N; i++, j = (j + 7) % 50)
	{
		printf("j=%d \n", j);
		T = Insert(j, T);
	}
	puts("���� 4 \n");
	T = Insert(4, T);
	Display(T);
	for (i = 0; i < N; i += 2)
	{
		printf("delelte: %d \n", i);
		T = Delete(i, T);
	}
	printf("detele:\n");
	printf("height=%d \n", T->Height);
	Display(T);

	printf("Min is %d, Max is %d\n", Retrieve(FindMin(T)),
		Retrieve(FindMax(T)));
	return EXIT_SUCCESS;
}