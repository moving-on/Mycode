#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"



/*********相关结构体及API函数*******************/


/**
*  typedef enum Color{
*       RED   = 1,
*       BLACK = 0
* }Color; //定义结点的颜色
*
*typedef struct Node{
*   struct Node *parent;  //父节点
*   struct Node *left;    //左子树
*   struct Node *right;   //右子树
*   int          key;     //key
*        //data 域
*   Color        color;   //节点颜色
*}Node,*RBTree;
*/

/**
* API函数
*
*void  rbInsert(RBTree *T,int key);  //插入一个结点
*Node *rbSearch(RBTree T,int key);   //查找结点
*void  rbDelete(RBTree *T,Node *z);  //删除结点
*Node *rbMinKey(RBTree T);           //查找最小的结点
*Node *rbMaxKey(RBTree T);           //查找最大的结点
*void  rbPrint(RBTree T);            //打印红黑树
*/







int main(int argc, char **argv){
	RBTree T = NULL;
	Node   *x;
	int i = 0;
	for (i = 1; i <= 20; i++)
		rbInsert(&T, i);
	// rbInsert(&T,80);
	// rbInsert(&T,90);
	// rbInsert(&T,40);
	// rbDelete(&T,rbSearch(T,130));
	// rbDelete(&T,rbSearch(T,90));
	rbPrint(T);
	printf("max=%d\n", rbMaxKey(T)->key);
	printf("min=%d\n", rbMinKey(T)->key);
	printf("search=%d\n", rbSearch(T, 16)->key);
	return 0;
}