#include <stdio.h>
#include <stdlib.h>
#include "rbtree.h"



/*********��ؽṹ�弰API����*******************/


/**
*  typedef enum Color{
*       RED   = 1,
*       BLACK = 0
* }Color; //���������ɫ
*
*typedef struct Node{
*   struct Node *parent;  //���ڵ�
*   struct Node *left;    //������
*   struct Node *right;   //������
*   int          key;     //key
*        //data ��
*   Color        color;   //�ڵ���ɫ
*}Node,*RBTree;
*/

/**
* API����
*
*void  rbInsert(RBTree *T,int key);  //����һ�����
*Node *rbSearch(RBTree T,int key);   //���ҽ��
*void  rbDelete(RBTree *T,Node *z);  //ɾ�����
*Node *rbMinKey(RBTree T);           //������С�Ľ��
*Node *rbMaxKey(RBTree T);           //�������Ľ��
*void  rbPrint(RBTree T);            //��ӡ�����
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