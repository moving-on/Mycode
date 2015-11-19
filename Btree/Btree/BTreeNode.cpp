//BTreeNode.cpp

////////*************包含文件*****************///////////
#include "BTreeNode.h"

int BTreeNode::m_nKEYNUM=3;//定义static变量,此处需初始化大于等于3，否则release版本运行有错
int BTreeNode::m_nMIN=m_nKEYNUM/2;
//***************************
//name:Search
//operation:查找
//param:int obj
//return:(int)查找到结果的位置,若没有找到，返回-1
int BTreeNode::Search(int obj)const
{
	for(int i=0;i<m_vecData.size();i++){
		if(obj==m_vecData[i])
			return i;
	}
	return -1;
}



//************************************
//name:SearchSonNodePos
//operation:查找对应子节点的位置
//param:int obj
//return:(int)返回对应子结点位置,如果数据已经存在，返回－1
int BTreeNode::SearchSonNodePos(int obj)const
{
	for(int i=0;i<m_vecData.size();i++){
		if(obj==m_vecData[i]) 
			return -1;
		if(obj<m_vecData[i])
			return i;
	}
	return m_vecData.size();
}



//****************************
//name:showNode
//operation:输出各个节点值
//param:string space,bool isChangeLine
//return:none
void BTreeNode::ShowNode(bool isChangeLine/* =true */,string space/* ="  " */)const
{
	for(int i=0;i<m_vecData.size();i++)
		cout<<m_vecData[i]<<space;
	if(isChangeLine)cout<<endl;
}



//************************************
//name:InsertSort
//operation:插入并使序列有序
//param:int obj,BTreeNode left,BTreeNode right
//return:(int)返回插入后的位置
//已经保证没有重复的项
//当插入数据项，他指向的子节点不为NULL时，说明不是叶节点
int BTreeNode::InsertSort(int obj,BTreeNode *left,BTreeNode *right)
{
	int endPos=m_vecData.size();//尾部数据的位置

	m_vecData.push_back(obj);
	sort(m_vecData.begin(),m_vecData.end());
	int pos=Search(obj);

	if(pos!=endPos){//如果插入节点不是在尾部，将相应的右半部指针右移一位
		for(int i=m_vecSonNode.size();i>pos+1;i--)
			m_vecSonNode[i]=m_vecSonNode[i-1];
	}
	m_vecSonNode[pos]=left;
	m_vecSonNode[pos+1]=right;

	if(left!=NULL) left->m_pParent=this;//子节点和父节点的连接
	if(right!=NULL) right->m_pParent=this;
	return pos;
}




//******************************************
//name:Split
//operator:将左节点右半部分赋给右节点
//param:int mid,BTreeNode &right
//return:none
void BTreeNode::Split(int mid,BTreeNode *right)
{
	BTreeNode *temp;
	int i, j;
	for(i=mid+1,j=0; i<m_vecData.size(); i++,j++){
		right->m_vecData.push_back(m_vecData[i]);

		right->m_vecSonNode[j]=temp=m_vecSonNode[i];//转移
		right->m_vecSonNode[j+1]=m_vecSonNode[i+1];

		if(temp!=NULL)
			temp->m_pParent=right;//分离时，右节点的子节点指向自己的父节点
	}

	temp=right->m_vecSonNode[j];//对应最后一个数据项
	if(temp!=NULL)
		temp->m_pParent=right;//分离时，右节点的子节点指向自己的父节点

	for(i=mid,j=m_vecData.size();i<j;i++)//将多余节点从左节点删除
		m_vecData.pop_back();
}



//*****************************************
//name:IsLeaf
//operation:判断节点是否为叶节点
//param:none
//return:(bool)是叶节点，返回true
bool BTreeNode::IsLeaf()const
{
	for(int i=0;i<=m_vecData.size();i++){
		if(m_vecSonNode[i]!=NULL)
			return false;
	}
	return true;
}



//**************************************
//name:Remove
//operation:删除数据项
//param:int obj
//return:none
//调用前保证obj存在于节点中
//调用前保证节点是叶节点
void BTreeNode::Remove(int obj)
{
	vector<int>::iterator it=find(m_vecData.begin(),m_vecData.end(),obj);
	if(it!=m_vecData.end())	
		m_vecData.erase(it);
}


//***************************************
//name:LeftIsMin
//operation:判断左节点是否为最小数据项数目
//param:int pos(节点的位置)
//return:(bool)如果是，返回true
//如果pos<0,返回true
bool BTreeNode::LeftIsMin(int pos)const
{
	if(pos<0) return true;
	BTreeNode *temp=m_vecSonNode[pos];
	return m_nMIN==temp->m_vecData.size();
}


//***************************************
//name:RightIsMin
//operation:判断左节点是否为最小数据项数目
//param:int pos(数据项的位置)
//return:(bool)如果是，返回true
bool BTreeNode::RightIsMin(int pos)const
{
	if(pos>m_vecData.size()) return true;
	BTreeNode *temp=m_vecSonNode[pos];
	return m_nMIN==temp->m_vecData.size();
}


//**************************************
//name:LeftMax
//operation:找到左子树中最大值
//param:int pos()(数据项的位置)
//return:(BTreeNode *)最大值数据项所在的节点
BTreeNode * BTreeNode::LeftMax(int pos)const
{
	BTreeNode *temp=m_vecSonNode[pos];//先到最左边
	BTreeNode *sonNode=temp->m_vecSonNode[temp->m_vecData.size()];//找到最右节点
	while(sonNode!=NULL){
		temp=sonNode;
		sonNode=temp->m_vecSonNode[temp->m_vecData.size()];
	}
	return temp;
}


//**************************************
//name:RightMin
//operation:找到右子树的最小值
//param:int pos()(数据项的位置)
//return:(BTreeNode *)最小值数据项所在的节点
BTreeNode * BTreeNode::RightMin(int pos)const
{
	BTreeNode *temp=m_vecSonNode[pos+1];//先到最右边
	BTreeNode *sonNode=temp->m_vecSonNode[0];//找到最右节点
	while(sonNode!=NULL){
		temp=sonNode;
		sonNode=temp->m_vecSonNode[0];
	}
	return temp;
}



//******************************************
//name:SearchPos
//operation:查找相应子节点在当前节点中的连接位置
//param:BTreeNode * obj
//return:(int)返回相应位置,如果不存在，返回－1
int BTreeNode::SearchPos(BTreeNode * obj)const
{
	for(int i=0;i<m_vecSonNode.size();i++){
		if(obj==m_vecSonNode[i])
			return i;
	}
	return -1;
}