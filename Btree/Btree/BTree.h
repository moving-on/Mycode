//BTree.h
//B-�����ݽṹ��ʵ��
//�������ҡ����������롢ɾ��
//2006.6.20
//write by�������
//email:gordonbest@163.com
/////////////////////////////////////////////////////////


#ifndef BTREE_H
#define BTREE_H


////////*************�����ļ�*****************///////////
#include "BTreeNode.h"



////////////***********B-���������******************////////////////
//template<typename type>
class BTree{
	public:
		//*****˽������***********
		BTreeNode *m_BtreeRoot; //���ڵ�
		int m_nKEYNUM;
		
		//******˽�з���**********
		//***********************************
		//name:FindToLeaf
		//operation:�ҵ�����Ҫ�����Ҷ�ڵ�
		//param:type obj
		//return:������Ӧ��ָ��
		BTreeNode * FindToLeaf(int obj);



		//***********************************
		//name:Find
		//operation:�ҵ��������ڵĽڵ�
		//param:type obj
		//return:������Ӧ�ڵ�ָ�룬������ݲ����ڣ�����NULL
		BTreeNode * Find(int obj);

		//******************************
		//name:CreatNewNode
		//operation:����һ���½ڵ�
		//param:none
		//return:(BTreeNode *)����ָ���½ڵ��ָ��
		BTreeNode *CreatNewNode(){
			return new BTreeNode();
		}

		//******************************
		//name:InsertData
		//operation:����������,����֤���ṹ��B����
		//param:BTreeNode tNode,int obj
		//return:none
		void InsertData(BTreeNode *tNode,int obj);

		//*******************************
		//name:ShowFront
		//operation:�������
		//param:BTreeNode * obj
		//return:none
		void ShowFront(BTreeNode * obj)const;

		//***********************************
		//name:ShowMid
		//operation:�������
		//param:BTreeNode * obj
		//return:none
		void ShowMid(BTreeNode * obj)const;

		//***************************************8
		//name:Combine
		//operation:����ڵ㣬һ��������ҽڵ����
		//param:BTreeNode *left,int mid,BTreeNode *right
		//retutn:(BTreeNode *)����Ժ�Ľڵ�ָ��
		BTreeNode * Combine(BTreeNode *left,int mid,BTreeNode *right);


		//****************************************
		//name:EraseData
		//operation:ɾ��������,����B��������
		//param:BTreeNode *node,int obj
		//return:none
		void EraseData(BTreeNode *node,int obj);


		//******************************
		//name:EraseNoLeaf
		//operation:ɾ�������ڷ�Ҷ�ڵ���
		//param:BTreeNode *node,int obj
		//return:none
		void EraseNoLeaf(BTreeNode *node,int obj);

		
		//**********************************************
		//name:EraseLeftMin
		//operation:ɾ��,��������Ŀ����m_nMIN
		//param:BTreeNode *node,int obj
		//return:none
		void EraseLeftMin(BTreeNode *node,int obj);
		
		//***********************************************
		//name:CombineAndLink
		//operation:�����Ӧ�ڵ�,���Ӹ��ڵ�
		//param:BTreeNode * obj
		//return:(BTreeNode *)������Ϻ�Ľڵ�ĸ��ڵ�
		BTreeNode * CombineAndLink(BTreeNode * obj);

		//************************************
		//name:ClearNode
		//operation:�����
		//param:BTreeNode *
		//return:void
		void ClearNode(BTreeNode * obj);
		
	public:
		//****************************
		//���캯��
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
		//operator:����һ��B-��
		//param:int * start,int num
		//return:none
		void CreatTree(int *start,int num);

		//****************************
		//name:Display
		//operation:�������������
		//papram:none
		//return:none
		void Display()const;

		//*****************************
		//name:Inserrt
		//operation:����������
		//param:int obj
		//return:none
		void Insert(int obj);


		//***********************************
		//name:search
		//operation:�����������Ƿ����
		//param:int obj
		//return:(bool)���ڣ�����true
		bool Search(int obj);


		//************************************
		//name:Erase
		//operation:ɾ����Ӧ������
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
		//operation:�鿴���Ƿ�Ϊ��
		//param:none
		//return:(bool)Ϊ��true
		bool IsEmpty(){
			return m_BtreeRoot->GetDataCount()==0;
		}

		

		//************************************
		//name:Clear
		//operation:�����
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