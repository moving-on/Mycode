//BTree.h
//B-树数据结构的实现
//包含查找、遍历、插入、删除
//2006.6.20
//write by：宋瑞丰
//email:gordonbest@163.com
/////////////////////////////////////////////////////////


#ifndef BTREE_H
#define BTREE_H


////////*************包含文件*****************///////////
#include "BTreeNode.h"



////////////***********B-树类的声明******************////////////////
//template<typename type>
class BTree{
	public:
		//*****私有数据***********
		BTreeNode *m_BtreeRoot; //根节点
		int m_nKEYNUM;
		
		//******私有方法**********
		//***********************************
		//name:FindToLeaf
		//operation:找到数据要插入的叶节点
		//param:type obj
		//return:返回相应的指针
		BTreeNode * FindToLeaf(int obj);



		//***********************************
		//name:Find
		//operation:找到数据所在的节点
		//param:type obj
		//return:返回相应节点指针，如果数据不存在，返回NULL
		BTreeNode * Find(int obj);

		//******************************
		//name:CreatNewNode
		//operation:创造一个新节点
		//param:none
		//return:(BTreeNode *)返回指向新节点的指针
		BTreeNode *CreatNewNode(){
			return new BTreeNode();
		}

		//******************************
		//name:InsertData
		//operation:插入数据项,并保证树结构是B－树
		//param:BTreeNode tNode,int obj
		//return:none
		void InsertData(BTreeNode *tNode,int obj);

		//*******************************
		//name:ShowFront
		//operation:先序遍历
		//param:BTreeNode * obj
		//return:none
		void ShowFront(BTreeNode * obj)const;

		//***********************************
		//name:ShowMid
		//operation:中序遍历
		//param:BTreeNode * obj
		//return:none
		void ShowMid(BTreeNode * obj)const;

		//***************************************8
		//name:Combine
		//operation:将左节点，一个数据项，右节点组合
		//param:BTreeNode *left,int mid,BTreeNode *right
		//retutn:(BTreeNode *)组和以后的节点指针
		BTreeNode * Combine(BTreeNode *left,int mid,BTreeNode *right);


		//****************************************
		//name:EraseData
		//operation:删除数据项,保持B－树性质
		//param:BTreeNode *node,int obj
		//return:none
		void EraseData(BTreeNode *node,int obj);


		//******************************
		//name:EraseNoLeaf
		//operation:删除数据在非叶节点上
		//param:BTreeNode *node,int obj
		//return:none
		void EraseNoLeaf(BTreeNode *node,int obj);

		
		//**********************************************
		//name:EraseLeftMin
		//operation:删除,数据项数目等于m_nMIN
		//param:BTreeNode *node,int obj
		//return:none
		void EraseLeftMin(BTreeNode *node,int obj);
		
		//***********************************************
		//name:CombineAndLink
		//operation:组合相应节点,连接父节点
		//param:BTreeNode * obj
		//return:(BTreeNode *)返回组合后的节点的父节点
		BTreeNode * CombineAndLink(BTreeNode * obj);

		//************************************
		//name:ClearNode
		//operation:清空树
		//param:BTreeNode *
		//return:void
		void ClearNode(BTreeNode * obj);
		
	public:
		//****************************
		//构造函数
		BTree(int key=3){
			m_nKEYNUM=key;
			BTreeNode::m_nKEYNUM=this->m_nKEYNUM;
			m_BtreeRoot=CreatNewNode();
		}

		const int GetKey()const{
			return m_nKEYNUM;
		}
		
		BTreeNode * GetRoot()const{
			return m_BtreeRoot;
		}
		//*****************************
		//name:CeratTree
		//operator:创造一棵B-树
		//param:int * start,int num
		//return:none
		void CreatTree(int *start,int num);

		//****************************
		//name:Display
		//operation:输出所有数据项
		//papram:none
		//return:none
		void Display()const;

		//*****************************
		//name:Inserrt
		//operation:插入数据项
		//param:int obj
		//return:none
		void Insert(int obj);


		//***********************************
		//name:search
		//operation:查找数据项是否存在
		//param:int obj
		//return:(bool)存在，返回true
		bool Search(int obj);


		//************************************
		//name:Erase
		//operation:删除相应数据项
		//param:int obj
		//return:none
		void Erase(int obj){
			m_BtreeRoot->m_pParent=NULL;
			BTreeNode *temp=Find(obj);
			if(temp!=NULL)
				EraseData(temp,obj);
		}

		//************************************
		//name:IsEmpty
		//operation:查看树是否为空
		//param:none
		//return:(bool)为空true
		bool IsEmpty(){
			return m_BtreeRoot->GetDataCount()==0;
		}

		

		//************************************
		//name:Clear
		//operation:清空树
		//param:none
		//return:void
		void Clear()
		{
			while(!m_BtreeRoot->m_vecData.empty())
				m_BtreeRoot->m_vecData.pop_back();
			m_BtreeRoot->m_vecSonNode[0]=NULL;
		}

};//end class BTree
///////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
#endif//BTREE_H