//BTreeNode.h
//B-树节点实现
//2006.6.20
//write by :宋瑞丰
//email:gordonbest@163.com
//////////////////////////////////////
#ifndef BTREENODE_H
#define BTREENODE_H

////////*************包含文件*****************///////////
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <string>
#include <queue>
using namespace std;

///////////**********树节点声明*****************//////////
//B-树的节点定义
class BTreeNode{
	public:
		///*****共有数据************
		BTreeNode *m_pParent; 
		vector<int> m_vecData;//用一个向量来存储数据
		vector<BTreeNode *> m_vecSonNode; //用来存储指向叶节点指针
		//**********在此设定节点阶数***************************************************
		//enum{m_nKEYNUM=3,m_nMIN=m_nKEYNUM/2};//B-树一个节点最多存储的数据的个数，即关键字
		static  int m_nKEYNUM;
		static int m_nMIN;
		int m_nNodeShowPos;

		
		//**************公有方法************
		//****************************
		//构造函数
		BTreeNode()
		{
			m_pParent=NULL;
			int count=m_nKEYNUM+m_nMIN;
			if(m_nKEYNUM==3)//如果不加此判断，在release版本下会有问题，debug模式下无错
				count++;
			for(int i=0;i<count;i++)
				m_vecSonNode.push_back(NULL);
			m_nNodeShowPos=0;
		}
		//***************************
		//name:GetKEY
		//operation:返回阶数key
		//param:none
		//return:(const int)
		const int GetKEY()const{
			return m_nKEYNUM;
		}

		
		//***************************
		//name:Search
		//operation:查找
		//param:int obj
		//return:(int)查找到结果的位置,若没有找到，返回-1
		int Search(int obj)const;

		//************************************
		//name:SearchSonNodePos
		//operation:查找对应子节点的位置
		//param:int obj
		//return:(int)返回对应子结点位置,对应于m_vecSonNode
		int SearchSonNodePos(int obj)const;

		//****************************
		//name:showNode
		//operation:输出各个节点值
		//param:string space,bool isChangeLine
		//return:none
		void ShowNode(bool isChangeLine=true,string space="  ")const;
		
		//************************************
		//name:InsertSort
		//operation:插入并使序列有序
		//param:int obj,BTreeNode left,BTreeNode right
		//return:(int)返回插入后的位置
		//已经保证没有重复的项
		//当插入数据项，他指向的子节点不为NULL时，说明不是叶节点
		int InsertSort(int obj,BTreeNode *left,BTreeNode *right);

		//*****************************************
		//name:IsFull
		//operation:判断关键字是否已经满
		//param:none
		//return:(bool)满，返回true
		bool IsFull()const{
			return m_nKEYNUM<=m_vecData.size();
		}

		//******************************************
		//name:Split
		//operator:将左节点右半部分赋给右节点
		//param:int mid,BTreeNode &right
		//return:none
		void Split(int mid,BTreeNode *right);

		//*****************************************
		//name:IsLeaf
		//operation:判断节点是否为叶节点
		//param:none
		//return:(bool)是叶节点，返回true
		bool IsLeaf()const;

		//**************************************
		//name:Remove
		//operation:删除数据项
		//param:int obj
		//return:none
		//调用前保证obj存在于节点中
		//调用前保证节点是叶节点
		void Remove(int obj);

		//***************************************
		//name:RightIsMin
		//operation:判断左节点是否为最小数据项数目
		//param:int pos(节点的位置)
		//return:(bool)如果是，返回true
		bool LeftIsMin(int pos)const;


		//***************************************
		//name:RightIsMin
		//operation:判断左节点是否为最小数据项数目
		//param:int pos(数据项的位置)
		//return:(bool)如果是，返回true
		bool RightIsMin(int pos)const;

		//**************************************
		//name:LeftMax
		//operation:找到左子树中最大值
		//param:int pos()(数据项的位置)
		//return:(BTreeNode *)最大值数据项所在的节点
		BTreeNode * LeftMax(int pos)const;


		//**************************************
		//name:RightMin
		//operation:找到右子树的最小值
		//param:int pos()(数据项的位置)
		//return:(BTreeNode *)最小值数据项所在的节点
		BTreeNode * BTreeNode::RightMin(int pos)const;
				


		//******************************************
		//name:SearchPos
		//operation:查找相应子节点在当前节点中的连接位置
		//param:BTreeNode * obj
		//return:(int)返回相应位置,如果不存在，返回－1
		int SearchPos(BTreeNode * obj)const;

		//******************************************
		//name:IsLessThanMin
		//operation:判断节点数据项数目是否<m_nMIN
		//param:none
		//return:(bool)如果是数据项数目<m_nMIN,返回true
		bool IsLessThanMin()const{
			return m_nMIN>m_vecData.size();
		}

		//*******************************************
		//name:IsMin
		//operation:判断节点数据项数目是否＝＝m_nMIN
		//param:none
		//return:(bool)如果相等返回true
		bool IsMin()const{
			return m_vecData.size()==m_nMIN;
		}
		
		//*******************************************
		//name:GetDataCount
		//operation:返回这个节点包含的数据项的个数
		//param:none
		//return:(int) 数据项的个数
		int GetDataCount(){
			return m_vecData.size();
		}

		//*******************************************
		//name:GetDeep
		//operation:返回这个节点在树中的深度，根结点为0,往子结点递增
		//param:none
		//return:(int) 深度
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