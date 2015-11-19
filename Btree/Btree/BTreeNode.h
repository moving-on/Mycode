//BTreeNode.h
//B-���ڵ�ʵ��
//2006.6.20
//write by :�����
//email:gordonbest@163.com
//////////////////////////////////////
#ifndef BTREENODE_H
#define BTREENODE_H

////////*************�����ļ�*****************///////////
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <queue>
using namespace std;

///////////**********���ڵ�����*****************//////////
//B-���Ľڵ㶨��
class BTreeNode{
	public:
		///*****��������************
		BTreeNode *m_pParent; 
		vector<int> m_vecData;//��һ���������洢����
		vector<BTreeNode *> m_vecSonNode; //�����洢ָ��Ҷ�ڵ�ָ��
		//**********�ڴ��趨�ڵ����***************************************************
		//enum{m_nKEYNUM=3,m_nMIN=m_nKEYNUM/2};//B-��һ���ڵ����洢�����ݵĸ��������ؼ���
		static  int m_nKEYNUM;
		static int m_nMIN;
		int m_nNodeShowPos;

		
		//**************���з���************
		//****************************
		//���캯��
		BTreeNode()
		{
			m_pParent=NULL;
			int count=m_nKEYNUM+m_nMIN;
			if(m_nKEYNUM==3)//������Ӵ��жϣ���release�汾�»������⣬debugģʽ���޴�
				count++;
			for(int i=0;i<count;i++)
				m_vecSonNode.push_back(NULL);
			m_nNodeShowPos=0;
		}
		//***************************
		//name:GetKEY
		//operation:���ؽ���key
		//param:none
		//return:(const int)
		const int GetKEY()const{
			return m_nKEYNUM;
		}

		
		//***************************
		//name:Search
		//operation:����
		//param:int obj
		//return:(int)���ҵ������λ��,��û���ҵ�������-1
		int Search(int obj)const;

		//************************************
		//name:SearchSonNodePos
		//operation:���Ҷ�Ӧ�ӽڵ��λ��
		//param:int obj
		//return:(int)���ض�Ӧ�ӽ��λ��,��Ӧ��m_vecSonNode
		int SearchSonNodePos(int obj)const;

		//****************************
		//name:showNode
		//operation:��������ڵ�ֵ
		//param:string space,bool isChangeLine
		//return:none
		void ShowNode(bool isChangeLine=true,string space="  ")const;
		
		//************************************
		//name:InsertSort
		//operation:���벢ʹ��������
		//param:int obj,BTreeNode left,BTreeNode right
		//return:(int)���ز�����λ��
		//�Ѿ���֤û���ظ�����
		//�������������ָ����ӽڵ㲻ΪNULLʱ��˵������Ҷ�ڵ�
		int InsertSort(int obj,BTreeNode *left,BTreeNode *right);

		//*****************************************
		//name:IsFull
		//operation:�жϹؼ����Ƿ��Ѿ���
		//param:none
		//return:(bool)��������true
		bool IsFull()const{
			return m_nKEYNUM<=m_vecData.size();
		}

		//******************************************
		//name:Split
		//operator:����ڵ��Ұ벿�ָ����ҽڵ�
		//param:int mid,BTreeNode &right
		//return:none
		void Split(int mid,BTreeNode *right);

		//*****************************************
		//name:IsLeaf
		//operation:�жϽڵ��Ƿ�ΪҶ�ڵ�
		//param:none
		//return:(bool)��Ҷ�ڵ㣬����true
		bool IsLeaf()const;

		//**************************************
		//name:Remove
		//operation:ɾ��������
		//param:int obj
		//return:none
		//����ǰ��֤obj�����ڽڵ���
		//����ǰ��֤�ڵ���Ҷ�ڵ�
		void Remove(int obj);

		//***************************************
		//name:RightIsMin
		//operation:�ж���ڵ��Ƿ�Ϊ��С��������Ŀ
		//param:int pos(�ڵ��λ��)
		//return:(bool)����ǣ�����true
		bool LeftIsMin(int pos)const;


		//***************************************
		//name:RightIsMin
		//operation:�ж���ڵ��Ƿ�Ϊ��С��������Ŀ
		//param:int pos(�������λ��)
		//return:(bool)����ǣ�����true
		bool RightIsMin(int pos)const;

		//**************************************
		//name:LeftMax
		//operation:�ҵ������������ֵ
		//param:int pos()(�������λ��)
		//return:(BTreeNode *)���ֵ���������ڵĽڵ�
		BTreeNode * LeftMax(int pos)const;


		//**************************************
		//name:RightMin
		//operation:�ҵ�����������Сֵ
		//param:int pos()(�������λ��)
		//return:(BTreeNode *)��Сֵ���������ڵĽڵ�
		BTreeNode * BTreeNode::RightMin(int pos)const;
				


		//******************************************
		//name:SearchPos
		//operation:������Ӧ�ӽڵ��ڵ�ǰ�ڵ��е�����λ��
		//param:BTreeNode * obj
		//return:(int)������Ӧλ��,��������ڣ����أ�1
		int SearchPos(BTreeNode * obj)const;

		//******************************************
		//name:IsLessThanMin
		//operation:�жϽڵ���������Ŀ�Ƿ�<m_nMIN
		//param:none
		//return:(bool)�������������Ŀ<m_nMIN,����true
		bool IsLessThanMin()const{
			return m_nMIN>m_vecData.size();
		}

		//*******************************************
		//name:IsMin
		//operation:�жϽڵ���������Ŀ�Ƿ񣽣�m_nMIN
		//param:none
		//return:(bool)�����ȷ���true
		bool IsMin()const{
			return m_vecData.size()==m_nMIN;
		}
		
		//*******************************************
		//name:GetDataCount
		//operation:��������ڵ������������ĸ���
		//param:none
		//return:(int) ������ĸ���
		int GetDataCount(){
			return m_vecData.size();
		}

		//*******************************************
		//name:GetDeep
		//operation:��������ڵ������е���ȣ������Ϊ0,���ӽ�����
		//param:none
		//return:(int) ���
		int GetDeep(){
			int deep;
			BTreeNode *node=this;
			for(deep=0;node!=NULL;deep++){
				node=node->m_pParent;
			}
			return deep-1;
		}

};
//end class BTreeNode
//////////////////////////////////////////////////////////////




#endif//BTREENODE_H