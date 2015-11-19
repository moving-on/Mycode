//BTree.cpp

////////*************�����ļ�*****************///////////
#include "BTree.h"


//***********************************
//name:FindToLeaf
//operation:�ҵ�����Ҫ�����Ҷ�ڵ�
//param:type obj
//return:������Ӧ��Ҷ�ڵ�ָ�룬��������ظ�������NULL
BTreeNode * BTree::FindToLeaf(int obj)
{
	BTreeNode *temp=m_BtreeRoot;
	int pos=0;
	while(!temp->IsLeaf()){
		pos=temp->SearchSonNodePos(obj);
		if(pos==-1) return NULL;//�ж������Ƿ��ظ�
		temp=temp->m_vecSonNode[pos];
	}
	pos=temp->SearchSonNodePos(obj);//��Ҷ�ڵ����
	if(pos==-1)return NULL;
	return temp;
}


//***********************************
//name:Find
//operation:�ҵ��������ڵĽڵ�
//param:type obj
//return:������Ӧ�ڵ�ָ�룬������ݲ����ڣ�����NULL
BTreeNode * BTree::Find(int obj)
{
	BTreeNode *temp=m_BtreeRoot;
	int pos=0;
	while(!temp->IsLeaf()){
		if(temp->Search(obj)!=-1) return temp;
		pos=temp->SearchSonNodePos(obj);
		temp=temp->m_vecSonNode[pos];
	}
	if(temp->Search(obj)!=-1) 
		return temp;
	else 
		return NULL;
}



//*******************************
//name:ShowFront
//operation:�������
//param:BTreeNode * obj
//return:none
void BTree::ShowFront(BTreeNode * obj)const
{
	if(obj==NULL) return;
	else obj->ShowNode();
	if(!obj->IsLeaf()){
		for(int i=0;i<=obj->m_vecData.size();i++){
			ShowFront(obj->m_vecSonNode[i]);
		}
	}
}




//******************************
//name:Insert
//operation:����������,����֤���ṹ��B����
//param:BTreeNode tNode,int obj
//return:none
void BTree::InsertData(BTreeNode *tNode,int obj)
{
	BTreeNode *left=NULL,*right=NULL;
	BTreeNode *temp=tNode;
	while(1){
		temp->InsertSort(obj,left,right);
		if(!temp->IsFull()) return ;//�������

		//�����Ժ󣬽ڵ������������,�������ϴ���������Ĳ���
		left=temp;
		obj=left->m_vecData[left->m_nKEYNUM/2];
		right=CreatNewNode();
		left->Split(left->m_nKEYNUM/2,right);

		if(temp->m_pParent==NULL){
			temp=CreatNewNode();
			m_BtreeRoot=temp;//������ڵ㲻���ڣ�����ĸ��ڵ㣬�ض��Ǹ��ڵ�
		}
		else{
			temp=temp->m_pParent;
		}
	}//end while	
}



//***********************************
//name:ShowMid
//operation:�������
//param:BTreeNode * obj
//return:none
void BTree::ShowMid(BTreeNode * obj)const
{
	if(obj==NULL) return;
	if(!obj->IsLeaf()){
	 	for(int i=0;i<=obj->m_vecData.size();i++){
			ShowMid(obj->m_vecSonNode[i]);
			if(i!=obj->m_vecData.size())
				cout<<obj->m_vecData[i]<<"  ";
		}//end for
	}//end if
	else obj->ShowNode(false);
}



//*****************************
//name:CeratTree
//operator:����һ��B-��
//param:int * start,int num
//return:none
void BTree::CreatTree(int *start,int num)
{
	BTreeNode *temp=NULL;
	for(int i=0;i<num;start++,i++){
		temp=FindToLeaf(*start);
		if(temp!=NULL)//�������û���ظ�������
			InsertData(temp,*start);
	}
}




//****************************
//name:Display
//operation:�������������
//papram:none
//return:none
void BTree::Display()const
{
	if(m_BtreeRoot->m_vecData.size()==0){
		cout<<"�ڵ�Ϊ��\n";
		return ;
	}
	cout<<"*******************************************\n";
	cout<<"���ڵ�ǰ�������\n";
	ShowFront(m_BtreeRoot);
//	cout<<"���������\n";
//	ShowMid(m_BtreeRoot);
}




//*****************************
//name:Inserrt
//operation:����������
//param:int obj
//return:none
void BTree::Insert(int obj)
{
	BTreeNode *temp=NULL;
	temp=FindToLeaf(obj);
	if(temp!=NULL)//�������û���ظ�������
		InsertData(temp,obj);
}

//***********************************
//name:search
//operation:�����������Ƿ����
//param:int obj
//return:(bool)���ڣ�����true
bool BTree::Search(int obj){
	BTreeNode *temp=FindToLeaf(obj);
	if(temp==NULL)
		return true;
	else return false;
}


//***************************************8
//name:Combine
//operation:����ڵ㣬һ��������ҽڵ����
//param:BTreeNode *left,int mid,BTreeNode *right
//retutn:(BTreeNode *)����Ժ�Ľڵ�ָ��
BTreeNode * BTree::Combine(BTreeNode *left,int mid,BTreeNode *right)
{
	BTreeNode *temp=NULL;
	left->m_vecData.push_back(mid);//�Ƚ��м�ڵ����
	int i,j;
	for(i=left->m_vecData.size(),j=0;j<right->m_vecData.size();i++,j++){
		left->m_vecData.push_back(right->m_vecData[j]);
		temp=right->m_vecSonNode[j];
		left->m_vecSonNode[i]=temp;
		if (temp!=NULL) temp->m_pParent=left;//���Ӹ��ڵ�
	}
	temp=right->m_vecSonNode[j];//������һ��������Ĳ���
	left->m_vecSonNode[i]=temp;
	if (temp!=NULL) temp->m_pParent=left;
	return left;
}



//****************************************
//name:EraseData
//operation:ɾ��������,����B��������
//param:BTreeNode *node,int obj
//return:none
void BTree::EraseData(BTreeNode *node,int obj)
{
	if(!node->IsLeaf()){//����Ҷ�ڵ�
		EraseNoLeaf(node,obj);
	}
	else{//Ҷ�ڵ�
		//���������С,��ɾ������Ҷ�Ӹ��ڵ�
		if(node->m_vecData.size() > node->m_nMIN || node->m_pParent==NULL)
			node->Remove(obj);
		else
			EraseLeftMin(node,obj);
	}
}



//******************************
//name:EraseNoLeaf
//operation:ɾ�������ڷ�Ҷ�ڵ���
//param:BTreeNode *node,int obj
//return:none
void BTree::EraseNoLeaf(BTreeNode *node,int obj)
{
	BTreeNode *temp=NULL;
	int changeData=0;
	int pos=node->Search(obj);//obj�ڽڵ�node�е�λ��
	temp=node->LeftMax(pos);
	if(!temp->IsMin()){//����ǰ���ڵ���������Ŀ����m_nMIN
			changeData=temp->m_vecData[temp->m_vecData.size()-1];
			node->m_vecData[pos]=changeData;
			temp->Remove(changeData);
			return ;//ɾ������
	}
	temp=node->RightMin(pos);
	if(!temp->IsMin()){//�����̽ڵ���������Ŀ����m_nMIN
		changeData=temp->m_vecData[0];
		node->m_vecData[pos]=changeData;
		temp->Remove(changeData);
		return ;//ɾ������
	}
	//�����ӽڵ��Ϊ��С������Ŀ
	temp=node->RightMin(pos);
	changeData=temp->m_vecData[0];
	node->m_vecData[pos]=changeData;
	EraseLeftMin(temp,changeData);
}




//**********************************************
//name:EraseLeftMin
//operation:ɾ��,��������Ŀ����m_nMIN
//param:BTreeNode *node,int obj
//return:none
void BTree::EraseLeftMin(BTreeNode *node,int obj)
{
	BTreeNode *temp=node;
	BTreeNode *parent=temp->m_pParent;
	int changeData=0;	
	BTreeNode *left=NULL;
	BTreeNode *right=NULL;
	int pos=parent->SearchPos(node);//����Ŀ��ڵ����丸�ڵ���λ��
	//������ֵ���������Ŀ����m_nMIN
	if(!parent->LeftIsMin(pos-1)){
		left=parent->m_vecSonNode[pos-1];
		//�����ڵ�parent->m_vecData[pos-1]���ݵ�Ŀ��ڵ�
		node->Remove(obj);
		node->InsertSort(parent->m_vecData[pos-1],NULL,NULL);
		//����ڵ����ֵ����parent->m_vecData[pos-1]
		int deletePos=left->m_vecData.size()-1;
		parent->m_vecData[pos-1]=left->m_vecData[deletePos];
		left->m_vecData.pop_back();//ɾ�����ӽڵ����ֵ
		return ;//ɾ������
	}
	//������ֵ���������Ŀ����m_nMIN
	if(!parent->RightIsMin(pos+1)){
		right=parent->m_vecSonNode[pos+1];
		//�����ڵ�parent->m_vecData[pos]���ݵ�Ŀ��ڵ�
		node->Remove(obj);
		node->InsertSort(parent->m_vecData[pos],NULL,NULL);
		//���ҽڵ���Сֵ����parent->m_vecData[pos]
		parent->m_vecData[pos]=right->m_vecData[0];
		right->m_vecData.erase(right->m_vecData.begin());//ɾ�����ӽ����Сֵ
		return ;//ɾ������
	}
	//�����ֵܽ����������Ŀ��Ϊ��Сֵ
	temp->Remove(obj);
	while(temp!=NULL){
		if(temp->IsLessThanMin()){
			temp=CombineAndLink(temp);
		}
		else return;
	}
}



//***********************************************
//name:CombineAndLink
//operation:�����Ӧ�ڵ�,���Ӹ��ڵ�
//param:BTreeNode * obj
//return:(BTreeNode *)������Ϻ�Ľڵ�ĸ��ڵ�
BTreeNode * BTree::CombineAndLink(BTreeNode * obj){
	BTreeNode *temp;
	BTreeNode *parent=obj->m_pParent;
	
	int pos=parent->SearchPos(obj);
	//���ֵܲ�����
	if(pos==0)
		pos++;
	//��obj���ֵܺ��丸�ڵ�������������Լ�obj�������
	temp=Combine(parent->m_vecSonNode[pos-1],parent->m_vecData[pos-1],
				parent->m_vecSonNode[pos]);

	parent->Remove(parent->m_vecData[pos-1]);//�Ӹ��ڵ�ɾ����temp��ϵ�������
	parent->m_vecSonNode[pos-1]=temp;//������Ϻ���ӽ��
	temp->m_pParent=parent;
	for(int i=pos;i<=parent->m_vecData.size();i++){//�ƶ��ӽ��ָ��
		parent->m_vecSonNode[i]=parent->m_vecSonNode[i+1];
	}

	if(temp->IsFull()){//���ϲ��Ժ�Ľڵ㲻���Ϲ淶ʱ,���ڵ����
			BTreeNode *right=CreatNewNode();
			int mid=temp->m_vecData[temp->m_nKEYNUM/2];
			temp->Split(temp->m_nKEYNUM/2,right);
			parent->InsertSort(mid,temp,right);
	}
	if(parent->IsLessThanMin() && parent->m_pParent==NULL){//��parent�Ѿ��Ǹ��ڵ�
		if(parent->m_vecData.size()==0){//���ڵ����Ϊ��
			m_BtreeRoot=parent->m_vecSonNode[0];
			m_BtreeRoot->m_pParent=NULL;
			return NULL;
		}
		m_BtreeRoot=parent;
		m_BtreeRoot->m_pParent=NULL;
		return NULL;
	}
	return parent;
}


//************************************
//name:ClearNode
//operation:�����
//param:none
//return:void
void BTree::ClearNode(BTreeNode * obj)
{
	BTreeNode *temp;
	if(obj==NULL) return;
	for(int i=0;i<=obj->m_vecData.size();i++){
		ClearNode(obj->m_vecSonNode[i]);
		temp=m_BtreeRoot->m_vecSonNode[i];
		if(temp!=NULL){
			delete temp;
		}
	}//end for
}
