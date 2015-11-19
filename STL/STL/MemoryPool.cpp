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
	USHORT nFree;//可用内存单元的数量
	USHORT nFirst;//第一个可用内存单元的编号
	USHORT nDummyAlign1;
	MemoryBlock *pnext;//指向下一个内存块
	char aData[1];//内存块从这里开始，作为编号为0的内存单元的首地址
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
	MemoryBlock* pBlock;//指向第一个内存块
	USHORT nUnitSize;//内存单元的大小
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
	char *pData = aData;//指向0号单元
	for (USHORT i = 1; i < nTypes; i++)
	{
		*reinterpret_cast<USHORT*>(pData) = i;//对每个单元的前两个字节标出下一个可用存储单元的编号
		pData += nUnitSize;//跳到下一个存储单元
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
        //第一次调用初始化内存块
		pMyBlock = new(nGrowSize, nUnitSize) MemoryBlock(nGrowSize, nUnitSize);
		pBlock = pMyBlock;
		return (void*)(pBlock->aData);
	}
	pMyBlock = pBlock;
	while (pMyBlock&&!pMyBlock->nFree)//寻找可用的内存块
		pMyBlock = pMyBlock->pnext;
	if (pMyBlock)//有可用内存资源
	{
		cout << "have memory" << endl;
		char* pFree = pMyBlock->aData + (pMyBlock->nFirst*nUnitSize);//第一个可用内存单元的地址
		pMyBlock->nFirst = *((USHORT*)pFree);//取得该内存单元下一个可分配内存单元的编号
		pMyBlock->nFree--;//可用内存单元数减一
		return (void*)pFree;//返回分配的内存单元的地址
	}
	else//已经没有可用内存块
	{
		cout << "add a new block" << endl;
		if (!nGrowSize)
			return NULL;
		pMyBlock = new(nGrowSize, nUnitSize) MemoryBlock(nGrowSize, nUnitSize);//再分配一个内存块
		if (!pMyBlock)
			return NULL;
		pMyBlock->pnext = pBlock;//内存池指针指向新分配的内存块
		pBlock = pMyBlock;
		return (void*)(pMyBlock->aData);
	}
}

void MemoryPool::Free(void* pFree)
{
	MemoryBlock* pMyBlock = pBlock;
	MemoryBlock* preMyBlock=pBlock;
	//判断要释放的内存单元是否在某内存块的地址范围
	while (((ULONG)pMyBlock->aData > (ULONG)pFree) || (((ULONG)pMyBlock->aData + pMyBlock->nSize) <= (ULONG)pFree))
	{
		preMyBlock = pMyBlock;
		pMyBlock = pMyBlock->pnext;
	}
	//找到内存单元所在的内存块
	cout << "free the union" << endl;
	pMyBlock->nFree++;//内存块可用单元数加一
	*((USHORT*)pFree) = pMyBlock->nFirst;//将内存块头信息中的下一个可用单元的编号存入释放内存单元的头两个字节
	pMyBlock->nFirst = (USHORT)(((ULONG)pFree - (ULONG)(pMyBlock->aData)) / nUnitSize);//计算释放内存单元的编号，放入头信息中，作为下一个可用内存单元
	if (pMyBlock->nFree*nUnitSize == pMyBlock->nSize)
	{
		cout << "delete the block" << endl;
		preMyBlock->pnext = pMyBlock->pnext;//如果该内存块已经为空，就释放掉它，并将其从内存池链表中移除
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

