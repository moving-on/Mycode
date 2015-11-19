
#include<iostream>
using namespace std;


typedef struct
{
	int address;
	int data;
	int next;
}node;

typedef struct
{
	node* C;
	int TableSize;
}HashTable;

const int N = 100000;
int find(int address, HashTable *H);
int converse(HashTable *H, int nexthead, int K);
int main()
{
	int Address;
	int n;
	int K;
	cin >> Address >> n >> K;
	HashTable *H = new HashTable;
	H->C= new node[N];
	for (int i = 0; i < N; i++)
	{
		H->TableSize = N;
		H->C[i].address = -2;
		H->C[i].data = 0;
		H->C[i].next = -2;
	}
	for (int i = 0; i<n; ++i)
	{
		int address;
		cin >> address;
		int pos = find(address,H);
		H->C[pos].address = address;
		cin >> H->C[pos].data >> H->C[pos].next;

	}


	int convert_num = n / K;
	int nexthead = 100;
	for (int i = 0; i < convert_num; i++)
	{
		int tailaddress=converse(H,nexthead, K);
		int pos = find(nexthead, H);
		H->C[pos].next = tailaddress;
		nexthead = H->C[find(tailaddress, H)].next;
		
	}
}

int Hash(int address, int Tablesize)
{
	return address%Tablesize;
}

int find(int address,HashTable *H)
{
	int currentpos, newpos;
	int cnum = 0;
	newpos = currentpos = Hash(address, H->TableSize);
	while (H->C[newpos].address != -2&&H->C[newpos].address != address)
	{
		if (++cnum % 2)
		{
			newpos = currentpos + (cnum + 1) / 2 * (cnum + 1) / 2;
			while (newpos >= H->TableSize)
				newpos -= H->TableSize;
		}
		else
		{
			newpos = currentpos - cnum / 2 * cnum / 2;
			while (newpos<0)
				newpos += H->TableSize;
		}
	}
	return newpos;
}

int converse(HashTable *H, int address,int K)
{
	int pos = find(address,H);
	int tempaddress = address;
	for (int i = 0; i < K; i++)
	{
		int nextaddress = tempaddress;
		pos = find(nextaddress, H);
		tempaddress = H->C[pos].next;
		H->C[pos].next = address;
		address = nextaddress;
	}
	return tempaddress;
}