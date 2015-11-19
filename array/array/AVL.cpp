#include<iostream>
#include<vector>

using namespace std;

#define Node(T) BitNode<T>*
template<class T>
class BitNode
{
	int bf;
	T data;
	Node(T) lchild;
	Node(T) rchild;
public:
	BitNode(int bf,T d, Node(T) l, Node(T) r) :bf(bf),data(d), lchild(l), rchild(r){ }
	T getData(){ return data; }
	template<class T1>
	friend class BiTree;
};

enum Status { LH = 1, EH = 0, RH = -1 };

template<class T>
class BiTree
{
private:
	
	Node(T) H;
	bool insertAVL(Node(T) *P, T& e, bool* taller);
	void R_Rotate(Node(T) *P);
	void L_Rotate(Node(T) *P);
	void LeftBalance(Node(T) *P);
	void RightBalance(Node(T) *p);
	void preorder(Node(T));
public:
	vector<T> v;
	BiTree(vector<T> v, Node(T) P) :v(v), H(P){}
	~BiTree(){}
	void createTree();
	void Print();

};

template<class T>
void BiTree<T>::Print()
{
	preorder(H);
}

template<class T>
void BiTree<T>::preorder(Node(T) P)
{
	if (!P)
		return;
	else
	{
		cout << P->data << endl;
		preorder(P->lchild);
		preorder(P->rchild);

	}
}



template<class T>
bool BiTree<T>::insertAVL(Node(T) *P, T& e, bool* taller)
{
	if (!*P)
	{
		*P = new BitNode<T>(EH,e, NULL, NULL);
		*taller = true;
	}
	else
	{
		if (e == (*P)->data)
		{
			*taller = false;
			return false;
		}
		if (e < (*P)->data)
		{
			if (!insertAVL(&(*P)->lchild, e, taller))
				return false;
			if (*taller)
			{
				switch ((*P)->bf)
				{
				case LH:
					LeftBalance(P);
					*taller = false;
					break;
				case EH:
					(*P)->bf = LH;
					*taller = true;
					break;
				case RH:
					(*P)->bf = EH;
					*taller = false;
					break;
				}
			}
		}
		else
		{
			if (!insertAVL(&(*P)->rchild, e, taller))
				return false;
			if (*taller)
			{
				switch ((*P)->bf)
				{
				case LH:
					(*P)->bf = EH;
					*taller = false;
					break;
				case EH:
					(*P)->bf = RH;
					*taller = true;
					break;
				case RH:
					RightBalance(P);
					*taller = false;
					break;
				}
			}
		}
	}
	return true;
}

template<class T>
void BiTree<T>::R_Rotate(Node(T) *P)
{
	Node(T) L;
	L = (*P)->lchild;
	(*P)->lchild = L->rchild;
	L->rchild = (*P);
	*P = L;
}

template<class T>
void BiTree<T>::L_Rotate(Node(T) *P)
{
	Node(T) R;
	R = (*P)->rchild;
	(*P)->rchild = R->lchild;
	R->lchild = (*P);
	*P = R;
}

template<class T>
void BiTree<T>::LeftBalance(Node(T) *P)
{
	Node(T) L;
	Node(T) Lr;
	L = (*P)->lchild;
	switch (L->bf)
	{
	case LH:
		(*P)->bf = L->bf = EH;
		R_Rotate(P);
		break;
	case RH:
		Lr = L->rchild;
		switch (Lr->bf)
		{
		case LH:
			(*P)->bf = RH;
			L->bf = EH;
			break;
		case EH:
			(*P)->bf = L->bf = EH;
			break;
		case RH:
			(*P)->bf = EH;
			L->bf = LH;
			break;
		}
		Lr->bf = EH;
		L_Rotate(&L);
		R_Rotate(P);
	}
}

template<class T>
void BiTree<T>::RightBalance(Node(T) *P)
{
	Node(T) R;
	Node(T) Rl;
	R = (*P)->rchild;
	switch (R->bf)
	{
	case RH:
		(*P)->bf = R->bf = EH;
		L_Rotate(P);
		break;
	case LH:
		Rl = R->lchild;
		switch (Rl->bf)
		{
		case LH:
			(*P)->bf = EH;
			R->bf = RH;
			break;
		case EH:
			(*P)->bf = R->bf = EH;
			break;
		case RH:
			(*P)->bf = LH;
			R->bf = EH;
			break;
		}
		Rl->bf = EH;
		R_Rotate(&R);
		L_Rotate(P);
	}
}

template<class T>
void BiTree<T>::createTree()
{
	bool taller;
	for (int i = 0; i < v.size(); i++)
	{
		insertAVL(&H, v[i], &taller);
	}
}


int main()
{
	int a[] = { 3, 2, 1, 4, 5, 6, 7, 10, 9, 8 };
	vector<int> v(a,a+10);
	BiTree<int> P(v, NULL);
	P.createTree();
	P.Print();

}