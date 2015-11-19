#include<iostream>
#include<new>
#include<vector>
using namespace std;
#define MEMPOOL_ALIGNMENT 4
#define USHORT unsigned short
#define ULONG unsigned long

struct MemoryBlock
{
	USHORT nSize;
	USHORT nFree;//�����ڴ浥Ԫ������
	USHORT nFirst;//��һ�������ڴ浥Ԫ�ı��
	USHORT nDummyAlign1;
	MemoryBlock *pnext;//ָ����һ���ڴ��
	char aData[1];//�ڴ������￪ʼ����Ϊ���Ϊ0���ڴ浥Ԫ���׵�ַ
	static void* operator new(size_t,USHORT nTypes,USHORT nUnitSize)
	{
		return ::operator new(sizeof(MemoryBlock) + nTypes*nUnitSize);
	}
		static void operator delete(void *p, size_t)
	{
		::operator delete(p);
	}
	MemoryBlock(USHORT nTypes = 1, USHORT nUintSize = 0);
	~MemoryBlock(){}
};

struct MemoryPool
{
private:
	MemoryBlock* pBlock;//ָ���һ���ڴ��
	USHORT nUnitSize;//�ڴ浥Ԫ�Ĵ�С
	USHORT nInitSize;
	USHORT nGrowSize;
public:
	static int nBlocks;
	MemoryPool(USHORT nUintSize, USHORT nInitSize = 1024, USHORT nGrowSize = 256);
	~MemoryPool();
	void* Alloc();
	void Free(void* p);
};

int MemoryPool::nBlocks = 0;

MemoryPool::~MemoryPool()
{
	nBlocks++;
	MemoryBlock *tmp = pBlock;
	while (pBlock)
	{
		tmp = pBlock->pnext;
		delete tmp;
		pBlock = tmp;
		cout << "delete block " << nBlocks << "..." << endl;
	}
}

MemoryBlock::MemoryBlock(USHORT nTypes, USHORT nUnitSize) :nSize(nTypes*nUnitSize), nFree(nTypes - 1), nFirst(1), pnext(0)
{
	char *pData = aData;//ָ��0�ŵ�Ԫ
	for (USHORT i = 1; i < nTypes; i++)
	{
		*reinterpret_cast<USHORT*>(pData) = i;//��ÿ����Ԫ��ǰ�����ֽڱ����һ�����ô洢��Ԫ�ı��
		pData += nUnitSize;//������һ���洢��Ԫ
	}
}

MemoryPool::MemoryPool(USHORT _nUnitSize, USHORT _nInitSize, USHORT _nGrowSize)
{
	pBlock = NULL;
	nInitSize = _nInitSize;
	nGrowSize = _nGrowSize;
	if (_nUnitSize > 4)
		nUnitSize = (_nUnitSize + (MEMPOOL_ALIGNMENT - 1))&~(MEMPOOL_ALIGNMENT - 1);
	else if (_nUnitSize <= 2)
		nUnitSize = 2;
	else
		nUnitSize = 4;
}

void* MemoryPool::Alloc()
{
	MemoryBlock* pMyBlock;
	if (!pBlock)
	{
		cout << "the first time"<< endl;
        //��һ�ε��ó�ʼ���ڴ��
		pMyBlock = new(nGrowSize, nUnitSize) MemoryBlock(nGrowSize, nUnitSize);
		pBlock = pMyBlock;
		return (void*)(pBlock->aData);
	}
	pMyBlock = pBlock;
	while (pMyBlock&&!pMyBlock->nFree)//Ѱ�ҿ��õ��ڴ��
		pMyBlock = pMyBlock->pnext;
	if (pMyBlock)//�п����ڴ���Դ
	{
		cout << "have memory" << endl;
		char* pFree = pMyBlock->aData + (pMyBlock->nFirst*nUnitSize);//��һ�������ڴ浥Ԫ�ĵ�ַ
		pMyBlock->nFirst = *((USHORT*)pFree);//ȡ�ø��ڴ浥Ԫ��һ���ɷ����ڴ浥Ԫ�ı��
		pMyBlock->nFree--;//�����ڴ浥Ԫ����һ
		return (void*)pFree;//���ط�����ڴ浥Ԫ�ĵ�ַ
	}
	else//�Ѿ�û�п����ڴ��
	{
		cout << "add a new block" << endl;
		if (!nGrowSize)
			return NULL;
		pMyBlock = new(nGrowSize, nUnitSize) MemoryBlock(nGrowSize, nUnitSize);//�ٷ���һ���ڴ��
		if (!pMyBlock)
			return NULL;
		pMyBlock->pnext = pBlock;//�ڴ��ָ��ָ���·�����ڴ��
		pBlock = pMyBlock;
		return (void*)(pMyBlock->aData);
	}
}

void MemoryPool::Free(void* pFree)
{
	MemoryBlock* pMyBlock = pBlock;
	MemoryBlock* preMyBlock=pBlock;
	//�ж�Ҫ�ͷŵ��ڴ浥Ԫ�Ƿ���ĳ�ڴ��ĵ�ַ��Χ
	while (((ULONG)pMyBlock->aData > (ULONG)pFree) || (((ULONG)pMyBlock->aData + pMyBlock->nSize) <= (ULONG)pFree))
	{
		preMyBlock = pMyBlock;
		pMyBlock = pMyBlock->pnext;
	}
	//�ҵ��ڴ浥Ԫ���ڵ��ڴ��
	cout << "free the union" << endl;
	pMyBlock->nFree++;//�ڴ����õ�Ԫ����һ
	*((USHORT*)pFree) = pMyBlock->nFirst;//���ڴ��ͷ��Ϣ�е���һ�����õ�Ԫ�ı�Ŵ����ͷ��ڴ浥Ԫ��ͷ�����ֽ�
	pMyBlock->nFirst = (USHORT)(((ULONG)pFree - (ULONG)(pMyBlock->aData)) / nUnitSize);//�����ͷ��ڴ浥Ԫ�ı�ţ�����ͷ��Ϣ�У���Ϊ��һ�������ڴ浥Ԫ
	if (pMyBlock->nFree*nUnitSize == pMyBlock->nSize)
	{
		cout << "delete the block" << endl;
		preMyBlock->pnext = pMyBlock->pnext;//������ڴ���Ѿ�Ϊ�գ����ͷŵ�������������ڴ���������Ƴ�
		delete pMyBlock;
	}
}

int main()
{
	MemoryPool *m = new MemoryPool(4);
	int *h;
	int *p=(int*)m->Alloc();
	*p = 1;
	h = p;
	for (int i = 2; i < 256; i++)
	{
		p = (int*)m->Alloc();
		*p = i;
	}
	for (; h != p; h++)
		cout << *h << " " << endl;
	delete m;
}

