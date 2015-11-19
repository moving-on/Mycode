#include <stdio.h>
#include <stdlib.h>

/**
* �����������
* 1.ÿ�����Ҫô��ɫ,Ҫô��ɫ
* 2.������Ǻ�ɫ��
* 3.ÿ��Ҷ�ӽ�㶼�Ǻ�ɫ(nil���)
* 4.���һ������Ϊ��ɫ,��ô�����ӽ�㶼�Ǻ�ɫ   (����������������ɫ���)
* 5.����һ��㵽Ҷ�ӽ��ÿ��·���Ϻ�ɫ���ĸ��������
*/

/**
*  ����ת����  ���赱ǰ���Ϊx
*  1.����Ϊ������������
*      x->parent = x->right;
*  2.���������Ʊ�Ϊ���׽��,���ݽ��ķֲ���ȷ��,������Ϊ���׺�,������游���ķֲ�
*      if(x==x->parent->parent->left){
*          x->parent->parent->left = x->right;
*      }else{
*          x->parent->parent->right = x->right;
*      }
*      x->right->parent = x->parent;
*  3.��������������Ϊ��ǰ�����ҽ��
*      x->right = x->right->left;
*
*         5                               7
*          \         ���5����ת         /  \
*           7       -------------->      5   8
*          / \                            \
*          6  8                            6
*/


/**
*  ����ת����  ���赱ǰ���Ϊx
*  1.����Ϊ���������ҽ��
*      x->parent = x->left;
*  2.���������Ʊ�Ϊ���׽��,���ݽ��ķֲ���ȷ������������游���ķֲ�
*      if(x==x->parent->left){
*          x->parent->parent->left = x->left;
*      }else{
*          x->parent->parent->right = x->left;
*      }
*      x->left->parent = x->parent;
*  3.���������ҽ��,��Ϊ��ǰ��������
*      x->left = x->left->right;
*
*      4                                 2
*     /           �ڵ�4����ת           / \
*     2          ------------->         1  4
*    / \                                   /
*    1  3                                 3
*/


/**
*   ���Ĳ������
*   1.�ڵ�����׶˲���,�ҽڵ��Ǻ�ɫ�� (�������ڵ�x)
*   2.�����������ڵ��Ǻ�ɫ��,��Ҫ���е���
*     1.x�ĸ��ڵ����游�ڵ��������
*      case1 :�常�ڵ�y�Ǻ�ɫ
*              1.��y��x�ĸ���ͬʱ��Ϊ��ɫ
*              2.Ȼ���x���游��Ϊ��ɫ
*              3.��x����Ϊ�游�ڵ�
*      case2:�常�ڵ��Ǻ�ɫ,x���ҽڵ�
*              1.��x��Ϊx��parent
*              2.����תx
*      case3:�常�ڵ��Ǻ�ɫ,x����ڵ�
*              1.��x��parent���
*              2.x���游���
*              3.����תx���游�ڵ�
*     2.x�ĸ��ڵ����游�ڵ��������(����ͬ��)
*   3.�������Ϊ���ڵ�,�򽫸��ڵ���
*
*/

/**
*   ����ɾ������  ����ɾ���ڵ�Ϊz  ʵ��ɾ���ڵ�y xɾ��y��Ψһ�ӽڵ�(������)
*   1.�����һ������Ϊ��,ֱ��ɾ��  y=z
*   2.�����������Ϊ����,ɾ��������������ߵĽڵ�,���������Ϊ��,��ɾ�����Ƚڵ���Ϊ������������ y
*   3. if(y->left!=NULL) x=y->left else x= y->right;
*   4.��ԭ��y�ĸ�ĸ����Ϊx�ĸ�ĸ��Ϊy������ɾ��  ,x��y�����еķֲ�ȡ����y�ڸ����еķֲ�,���y����ڵ�,��xҲ����ڵ�,���y���ҽڵ���xҲ���ҽڵ�
*   5.���y!=z���y��ֵ����z
*   6.���yΪ��ɫ��,��Ҫ���е���,��Ϊ��ĳ��·��������һ����ɫ�ڵ�
*
*   ɾ��������������:
*      1.ɾ���ĵ�����ѭ����,������ x��Ϊ���ڵ���x��һ����ɫ�ڵ�,���x��һ����ɫ�ڵ���,ֱ��Ⱦ�켴��
*      2.���������
*          x�������� ����x���ֵܽڵ�Ϊw
*              case 1: wΪ��ɫ
*                      1.w�ź�
*                      2.x��parent���
*                      3.����תx��parent
*                      4.�����ֵܽڵ� w = x->parent->right;
*              case 2: w��ɫ �������������Ǻ�ɫ
*                      1.w �ź�
*                      2.x��Ϊx��parent
*              case 3: w��ɫ w���������Ǻ�ɫ w���������Ǻ�ɫ
*                      1.w�ź�
*                      2.w�������ź�
*                      3.����תw
*                      4.�����ֵܽڵ�   w=x->parent->right;
*              case 4: w���������Ǻ�ɫ
*                      1.w��ɫΪx���׵���ɫ
*                      2.x��parent�ź�
*                      3.w���������ź�
*                      4.����תx��parent
*              ������� x=T  �˳�
*          x�������� (����ͬ��)
*      3.���ø��ڵ����ɫ,�����п��ܸı��˸��ڵ����ɫ
*
*/



/*���������ɫ*/
typedef enum Color{
	RED = 1,
	BLACK = 0
}Color;
typedef struct Node{
	struct Node *parent;  //���ڵ�
	struct Node *left;    //������
	struct Node *right;   //������
	int          key;     //key
	/*data ��*/
	Color        color;   //�ڵ���ɫ
}Node, *RBTree;

/*����һ�����*/
void  rbInsert(RBTree *T, int key);
/*���ҽ��*/
Node *rbSearch(RBTree T, int key);
/*ɾ�����*/
void  rbDelete(RBTree *T, Node *z);
/*������С�Ľ��*/
Node *rbMinKey(RBTree T);
/*�������Ľ��*/
Node *rbMaxKey(RBTree T);
/*��ӡ�����*/
void  rbPrint(RBTree T);



/*�������*/
static void InsertFixup(RBTree *T, Node *z);
/*ɾ������*/
static void DeleteFixup(RBTree *T, Node *x);
static Node *Parent(Node *x);
static Node *Left(Node *x);
static Node *Right(Node *x);
static void LeftRotate(RBTree *T, Node *x);
static void RightRotate(RBTree *T, Node *x);
static Node *RealDeleteNode(RBTree *T, Node *x);

/*����ڵ��ָ��*/
static Node *nil = NULL;


/*��ȡ���׽ڵ�*/
static Node *Parent(Node *x){
	return x->parent;
}

static Node *Left(Node *x){
	return x->left;
}

static Node *Right(Node *x){
	return x->right;
}

static void LeftRotate(RBTree *T, Node *x){     //����ת�����xԭ����������y��ת��Ϊx�ĸ�ĸ
	if (x->right != nil)
	{
		Node *y = Right(x);
		x->right = y->left;
		if (y->left != nil)
		{
			y->left->parent = x;
		}
		y->parent = x->parent;


		if (x->parent == nil)
		{
			*T = y;
		}
		else
		{
			if (x == Left(Parent(x)))
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
		}
		y->left = x;
		x->parent = y;
	}
}



static void RightRotate(RBTree *T, Node *x)   //����ת�����xԭ����������y��ת��Ϊx�ĸ�ĸ
{
	if (x->left != nil)
	{
		Node *y = Left(x);
		x->left = y->right;
		if (y->right != nil)
		{
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nil)
		{
			*T = y;
		}
		else
		{
			if (x == Left(Parent(x)))
			{
				x->parent->left = y;
			}
			else
			{
				x->parent->right = y;
			}
		}
		y->right = x;
		x->parent = y;
	}
}

/*����ʵ��Ҫɾ���Ľ��*/
static Node *RealDeleteNode(RBTree *T, Node *x){
	Node *p = x->right;
	while (p->left != nil)
	{
		p = p->left;

	}
	return p;
}

void rbInsert(RBTree *T, int key){
	if ((*T) == NULL){
		*T = (Node*)malloc(sizeof(Node));
		//��ʼ��nil���
		nil = (Node*)malloc(sizeof(Node));
		nil->color = BLACK;
		//���ý���ָ��
		(*T)->parent = nil;
		(*T)->left = nil;
		(*T)->right = nil;
		//���ý������,key ��color
		(*T)->key = key;
		(*T)->color = BLACK;
	}
	else{
		Node *x = *T;
		Node *p = nil;
		while (x != nil){
			p = x;
			if (key>x->key)
				x = x->right;
			else if (key<x->key)
				x = x->left;
			else
				return;
		}
		x = (Node*)malloc(sizeof(Node));
		x->parent = p;
		x->left = nil;
		x->right = nil;

		x->key = key;
		x->color = RED;
		if (key<p->key){
			p->left = x;
		}
		else{
			p->right = x;
		}
		InsertFixup(T, x);
	}
}

/*�������*/
static void InsertFixup(RBTree *T, Node *z){
	Node *y;
	while (Parent(z)->color == RED){
		if (Parent(z) == Parent(Parent(z))->left){
			y = Parent(Parent(z))->right;  //��ȡ�常���
			if (y->color == RED){             //case 1  ����常���Ϊ��ɫ,��Ѹ��ڵ���常����ź�,�游����ź�,z���Ƶ��游���
				y->color = BLACK;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = Parent(Parent(z));
			}
			else{
				if (z == Parent(z)->right){   //case 2  ����常���Ϊ��ɫ,z�ҽ��,z����Ϊ���׽��,����תz���,��ʱ��Ϊcase3�����
					z = z->parent;
					LeftRotate(T, z);
				}
				z->parent->color = BLACK;   //case 3 �常���Ϊ��ɫ,��z������,z�ĸ������ź�,z���游�ź�,Ȼ����תz���游���
				Parent(Parent(z))->color = RED;
				RightRotate(T, Parent(Parent(z)));
			}
		}
		else{  //�Գ� ����ͬ��
			y = Parent(Parent(z))->left;
			if (y->color == RED){
				y->color = BLACK;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				z = Parent(Parent(z));
			}
			else{
				if (z == Parent(z)->left){
					z = z->parent;
					RightRotate(T, z);
				}
				z->parent->color = BLACK;
				Parent(Parent(z))->color = RED;
				LeftRotate(T, Parent(Parent(z)));
			}
		}
	}
	(*T)->color = BLACK;
}

/**
*   ����ɾ������  ����ɾ���ڵ�Ϊz  ʵ��ɾ���ڵ�y xɾ��y��Ψһ�ӽڵ�(������)
*   1.�����һ������Ϊ��,ֱ��ɾ��  y=z
*   2.�����������Ϊ����,ɾ��������������ߵĽڵ�,���������Ϊ��,��ɾ�����Ƚڵ���Ϊ������������ y
*   3. if(y->left!=NULL) x=y->left else x= y->right;
*   4.��ԭ��y�ĸ�ĸ����Ϊx�ĸ�ĸ��Ϊy������ɾ��  ,x��y�����еķֲ�ȡ����y�ڸ����еķֲ�,���y����ڵ�,��xҲ����ڵ�,���y���ҽڵ���xҲ���ҽڵ�
*   5.���y!=z���y��ֵ����z
*   6.���yΪ��ɫ��,��Ҫ���е���,��Ϊ��ĳ��·��������һ����ɫ�ڵ�
*
*/

void rbDelete(RBTree *T, Node *z){
	if (z == nil || z == NULL)
		return;
	Node *y;
	Node *x;
	if (z->left == nil || z->right == nil){
		y = z;
	}
	else{
		y = RealDeleteNode(T, z);
	}
	//xָ��ʵ��ɾ�������ӽ��
	if (y->left != nil)
		x = y->left;
	else
		x = y->right;

	x->parent = y->parent;   //ɾ�����y
	if (y->parent == nil){
		*T = x;
	}
	else{
		if (y == Parent(y)->left)
			y->parent->left = x;
		else
			y->parent->right = x;
	}
	if (y != z){
		z->key = y->key;
	}
	//���ɾ���Ľ���Ǻ�ɫ,Υ��������5,Ҫ����ɾ������
	if (y->color == BLACK){
		DeleteFixup(T, x);
	}
}



/*ɾ������*/
static void DeleteFixup(RBTree *T, Node *x){
	while (x != (*T) && x->color == BLACK){
		if (x == Parent(x)->left){
			Node *w = Parent(x)->right;  //w Ϊx���ֵܽ��
			if (w->color == RED){          //case 1 �ֵܽ��Ϊ��ɫ
				w->color = BLACK;
				x->parent->color = RED;
				LeftRotate(T, Parent(x));
				w = Parent(x)->right;
			}
			if (w == nil) break;
			if (Left(w)->color == BLACK && Right(w)->color == BLACK){   //case2 �ֵܽ��������ӽ�㶼Ϊ��
				w->color = RED;
				x = Parent(x);
			}
			else if (w->right->color == BLACK){    //case3 w��������Ϊ��ɫ,������Ϊ��ɫ
				w->color = RED;
				w->left->color = BLACK;
				RightRotate(T, w);
				w = Parent(x)->right;
			}
			w->color = x->parent->color;         //case 4 w��������Ϊ��ɫ
			x->parent->color = BLACK;
			w->right->color = BLACK;
			LeftRotate(T, Parent(x));
		}
		else{  //�Գ� ����ͬ��
			Node *w = Parent(x)->left;
			if (w->color == RED){                 //case 1
				w->color = BLACK;
				x->parent->color = RED;
				RightRotate(T, Parent(x));
				w = Parent(x)->left;
			}
			if (w == nil) break;
			if (Left(w)->color == BLACK && Right(w)->color == BLACK){  //case 2
				w->color = RED;
				x = Parent(x);
			}
			else if (w->left->color == BLACK){                       //case 3
				w->color = RED;
				w->right->color = BLACK;
				LeftRotate(T, w);
				w = Parent(x)->left;
			}
			w->color = x->parent->color;
			x->parent->color = BLACK;
			w->left->color = BLACK;
			RightRotate(T, Parent(x));
		}
		x = *T;
	}
	x->color = BLACK;
}



/*����ĳ�����*/
Node *rbSearch(RBTree T, int key){
	if (T != nil){
		if (T->key<key)
			rbSearch(T->right, key);
		else if (T->key>key)
			rbSearch(T->left, key);
		else
			return T == nil ? NULL : T;
	}
}

/*��ӡ���*/
void rbPrint(RBTree T){
	if (T != NULL && T != nil){
		rbPrint(T->left);
		printf("%d(%s)\n", T->key, (T->color == RED) ? "��" : "��");
		rbPrint(T->right);
	}
}
/*������С��С���*/
Node *rbMinKey(RBTree T){
	Node *x = T;
	Node *p = nil;
	while (x != nil){
		p = x;
		x = x->left;
	}
	return p == nil ? NULL : p;
}

/*���������*/
Node *rbMaxKey(RBTree T){
	Node *x = T;
	Node *p = nil;
	while (x != nil){
		p = x;
		x = x->right;
	}
	return p == nil ? NULL : p;
}