#include<iostream>
#include<algorithm>
using namespace std;


#define Tree(T)  Node<T>* 

#define Node_t(T)  Node<T>* 
template<class T>
struct Node
{
	Node_t(T) left;
	Node_t(T) right;
	int height;
	T data;
};


template<class T>
int Height(Node_t(T) node)
{
	if (node == NULL)
		return -1;
	else
		return node->height;
}
template<class T>
Node_t(T) NewNode(T x)
{
	Node_t(T) t = new Node<T>();
	t->left = NULL;
	t->right = NULL;
	t->height = 0;
	t->data = x;
	return t;
}

template<class T>
Node_t(T) RightRotate(Node_t(T) a)
{
	Node_t(T) b = a->left;
	a->left = b->right;
	b->right = a;
	a->height = max(Height(a->left), Height(a->right)) + 1;
	b->height = max(Height(b->left), Height(b->right)) + 1;
	return b;
}

template<class T>
Node_t(T) LeftRotate(Node_t(T) a)
{
	Node_t(T) b = a->right;
	a->right = b->left;
	b->left = a;
	a->height = max(Height(a->left), Height(a->right)) + 1;
	b->height = max(Height(b->left), Height(b->right)) + 1;
	return b;
}

template<class T>
Node_t(T) RightLeftRotate(Node_t(T) a)
{
	a->right = RightRotate(a->right);
	return LeftRotate(a);
} 

template<class T>
Node_t(T) LeftRightRotate(Node_t(T) a)
{
	a->left = LeftRotate(a->left);
	return RightRotate(a);
}

template<class T>
Node_t(T) Insert(T x, Node_t(T) t)
{
	if (t == NULL)
	{
		t = NewNode(x);
	}
	else if (x < t->data)
	{
		t->left = Insert(x, t->left);
		if (Height(t->left) - Height(t->right) == 2)
		{
			if (x < t->left->data)
				t = RightRotate(t);
			else
				t = LeftRightRotate(t);
		}
	}
	else
	{
		t->right = Insert(x, t->right);
		if (Height(t->right) - Height(t->left) == 2)
		{
			if (x > t->right->data)
				t = LeftRotate(t);
			else
				t = RightLeftRotate(t);
		}
	}
	t->height = max(Height(t->left), Height(t->right)) + 1;
	return t;
}

template<class T>
void postOrder(Node_t(T) t)
{
	if (t == NULL)
		return;
	else
	{
		cout << t->data << " ";
		postOrder(t->left);
		postOrder(t->right);
	}
}

int main()
{
	Node_t(int) t = NewNode(2);
	for (int i = 0; i < 10; i++)
		t = Insert(i, t);
	postOrder(t);
}