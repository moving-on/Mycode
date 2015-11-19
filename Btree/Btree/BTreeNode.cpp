//BTreeNode.cpp

////////*************�����ļ�*****************///////////
#include "BTreeNode.h"

int BTreeNode::m_nKEYNUM=3;//����static����,�˴����ʼ�����ڵ���3������release�汾�����д�
int BTreeNode::m_nMIN=m_nKEYNUM/2;
//***************************
//name:Search
//operation:����
//param:int obj
//return:(int)���ҵ������λ��,��û���ҵ�������-1
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
//operation:���Ҷ�Ӧ�ӽڵ��λ��
//param:int obj
//return:(int)���ض�Ӧ�ӽ��λ��,��������Ѿ����ڣ����أ�1
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
//operation:��������ڵ�ֵ
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
//operation:���벢ʹ��������
//param:int obj,BTreeNode left,BTreeNode right
//return:(int)���ز�����λ��
//�Ѿ���֤û���ظ�����
//�������������ָ����ӽڵ㲻ΪNULLʱ��˵������Ҷ�ڵ�
int BTreeNode::InsertSort(int obj,BTreeNode *left,BTreeNode *right)
{
	int endPos=m_vecData.size();//β�����ݵ�λ��

	m_vecData.push_back(obj);
	sort(m_vecData.begin(),m_vecData.end());
	int pos=Search(obj);

	if(pos!=endPos){//�������ڵ㲻����β��������Ӧ���Ұ벿ָ������һλ
		for(int i=m_vecSonNode.size();i>pos+1;i--)
			m_vecSonNode[i]=m_vecSonNode[i-1];
	}
	m_vecSonNode[pos]=left;
	m_vecSonNode[pos+1]=right;

	if(left!=NULL) left->m_pParent=this;//�ӽڵ�͸��ڵ������
	if(right!=NULL) right->m_pParent=this;
	return pos;
}




//******************************************
//name:Split
//operator:����ڵ��Ұ벿�ָ����ҽڵ�
//param:int mid,BTreeNode &right
//return:none
void BTreeNode::Split(int mid,BTreeNode *right)
{
	BTreeNode *temp;
	int i, j;
	for(i=mid+1,j=0; i<m_vecData.size(); i++,j++){
		right->m_vecData.push_back(m_vecData[i]);

		right->m_vecSonNode[j]=temp=m_vecSonNode[i];//ת��
		right->m_vecSonNode[j+1]=m_vecSonNode[i+1];

		if(temp!=NULL)
			temp->m_pParent=right;//����ʱ���ҽڵ���ӽڵ�ָ���Լ��ĸ��ڵ�
	}

	temp=right->m_vecSonNode[j];//��Ӧ���һ��������
	if(temp!=NULL)
		temp->m_pParent=right;//����ʱ���ҽڵ���ӽڵ�ָ���Լ��ĸ��ڵ�

	for(i=mid,j=m_vecData.size();i<j;i++)//������ڵ����ڵ�ɾ��
		m_vecData.pop_back();
}



//*****************************************
//name:IsLeaf
//operation:�жϽڵ��Ƿ�ΪҶ�ڵ�
//param:none
//return:(bool)��Ҷ�ڵ㣬����true
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
//operation:ɾ��������
//param:int obj
//return:none
//����ǰ��֤obj�����ڽڵ���
//����ǰ��֤�ڵ���Ҷ�ڵ�
void BTreeNode::Remove(int obj)
{
	vector<int>::iterator it=find(m_vecData.begin(),m_vecData.end(),obj);
	if(it!=m_vecData.end())	
		m_vecData.erase(it);
}


//***************************************
//name:LeftIsMin
//operation:�ж���ڵ��Ƿ�Ϊ��С��������Ŀ
//param:int pos(�ڵ��λ��)
//return:(bool)����ǣ�����true
//���pos<0,����true
bool BTreeNode::LeftIsMin(int pos)const
{
	if(pos<0) return true;
	BTreeNode *temp=m_vecSonNode[pos];
	return m_nMIN==temp->m_vecData.size();
}


//***************************************
//name:RightIsMin
//operation:�ж���ڵ��Ƿ�Ϊ��С��������Ŀ
//param:int pos(�������λ��)
//return:(bool)����ǣ�����true
bool BTreeNode::RightIsMin(int pos)const
{
	if(pos>m_vecData.size()) return true;
	BTreeNode *temp=m_vecSonNode[pos];
	return m_nMIN==temp->m_vecData.size();
}


//**************************************
//name:LeftMax
//operation:�ҵ������������ֵ
//param:int pos()(�������λ��)
//return:(BTreeNode *)���ֵ���������ڵĽڵ�
BTreeNode * BTreeNode::LeftMax(int pos)const
{
	BTreeNode *temp=m_vecSonNode[pos];//�ȵ������
	BTreeNode *sonNode=temp->m_vecSonNode[temp->m_vecData.size()];//�ҵ����ҽڵ�
	while(sonNode!=NULL){
		temp=sonNode;
		sonNode=temp->m_vecSonNode[temp->m_vecData.size()];
	}
	return temp;
}


//**************************************
//name:RightMin
//operation:�ҵ�����������Сֵ
//param:int pos()(�������λ��)
//return:(BTreeNode *)��Сֵ���������ڵĽڵ�
BTreeNode * BTreeNode::RightMin(int pos)const
{
	BTreeNode *temp=m_vecSonNode[pos+1];//�ȵ����ұ�
	BTreeNode *sonNode=temp->m_vecSonNode[0];//�ҵ����ҽڵ�
	while(sonNode!=NULL){
		temp=sonNode;
		sonNode=temp->m_vecSonNode[0];
	}
	return temp;
}



//******************************************
//name:SearchPos
//operation:������Ӧ�ӽڵ��ڵ�ǰ�ڵ��е�����λ��
//param:BTreeNode * obj
//return:(int)������Ӧλ��,��������ڣ����أ�1
int BTreeNode::SearchPos(BTreeNode * obj)const
{
	for(int i=0;i<m_vecSonNode.size();i++){
		if(obj==m_vecSonNode[i])
			return i;
	}
	return -1;
}