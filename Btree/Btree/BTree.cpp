//BTree.cpp

////////*************包含文件*****************///////////
#include "BTree.h"


//***********************************
//name:FindToLeaf
//operation:找到数据要插入的叶节点
//param:type obj
//return:返回相应的叶节点指针，如果数据重复，返回NULL
BTreeNode * BTree::FindToLeaf(int obj)
{
	BTreeNode *temp=m_BtreeRoot;
	int pos=0;
	while(!temp->IsLeaf()){
		pos=temp->SearchSonNodePos(obj);
		if(pos==-1) return NULL;//判断数据是否重复
		temp=temp->m_vecSonNode[pos];
	}
	pos=temp->SearchSonNodePos(obj);//对叶节点查找
	if(pos==-1)return NULL;
	return temp;
}


//***********************************
//name:Find
//operation:找到数据所在的节点
//param:type obj
//return:返回相应节点指针，如果数据不存在，返回NULL
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
//operation:先序遍历
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
//operation:插入数据项,并保证树结构是B－树
//param:BTreeNode tNode,int obj
//return:none
void BTree::InsertData(BTreeNode *tNode,int obj)
{
	BTreeNode *left=NULL,*right=NULL;
	BTreeNode *temp=tNode;
	while(1){
		temp->InsertSort(obj,left,right);
		if(!temp->IsFull()) return ;//插入结束

		//插入以后，节点的数据项已满,进行向上传递数据项的操作
		left=temp;
		obj=left->m_vecData[left->m_nKEYNUM/2];
		right=CreatNewNode();
		left->Split(left->m_nKEYNUM/2,right);

		if(temp->m_pParent==NULL){
			temp=CreatNewNode();
			m_BtreeRoot=temp;//如果父节点不存在，创造的父节点，必定是根节点
		}
		else{
			temp=temp->m_pParent;
		}
	}//end while	
}



//***********************************
//name:ShowMid
//operation:中序遍历
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
//operator:创造一棵B-树
//param:int * start,int num
//return:none
void BTree::CreatTree(int *start,int num)
{
	BTreeNode *temp=NULL;
	for(int i=0;i<num;start++,i++){
		temp=FindToLeaf(*start);
		if(temp!=NULL)//如果数据没有重复，插入
			InsertData(temp,*start);
	}
}




//****************************
//name:Display
//operation:输出所有数据项
//papram:none
//return:none
void BTree::Display()const
{
	if(m_BtreeRoot->m_vecData.size()==0){
		cout<<"节点为空\n";
		return ;
	}
	cout<<"*******************************************\n";
	cout<<"按节点前序遍历：\n";
	ShowFront(m_BtreeRoot);
//	cout<<"中序遍历：\n";
//	ShowMid(m_BtreeRoot);
}




//*****************************
//name:Inserrt
//operation:插入数据项
//param:int obj
//return:none
void BTree::Insert(int obj)
{
	BTreeNode *temp=NULL;
	temp=FindToLeaf(obj);
	if(temp!=NULL)//如果数据没有重复，插入
		InsertData(temp,obj);
}

//***********************************
//name:search
//operation:查找数据项是否存在
//param:int obj
//return:(bool)存在，返回true
bool BTree::Search(int obj){
	BTreeNode *temp=FindToLeaf(obj);
	if(temp==NULL)
		return true;
	else return false;
}


//***************************************8
//name:Combine
//operation:将左节点，一个数据项，右节点组合
//param:BTreeNode *left,int mid,BTreeNode *right
//retutn:(BTreeNode *)组和以后的节点指针
BTreeNode * BTree::Combine(BTreeNode *left,int mid,BTreeNode *right)
{
	BTreeNode *temp=NULL;
	left->m_vecData.push_back(mid);//先将中间节点插入
	int i,j;
	for(i=left->m_vecData.size(),j=0;j<right->m_vecData.size();i++,j++){
		left->m_vecData.push_back(right->m_vecData[j]);
		temp=right->m_vecSonNode[j];
		left->m_vecSonNode[i]=temp;
		if (temp!=NULL) temp->m_pParent=left;//连接父节点
	}
	temp=right->m_vecSonNode[j];//针对最后一个数据项的操作
	left->m_vecSonNode[i]=temp;
	if (temp!=NULL) temp->m_pParent=left;
	return left;
}



//****************************************
//name:EraseData
//operation:删除数据项,保持B－树性质
//param:BTreeNode *node,int obj
//return:none
void BTree::EraseData(BTreeNode *node,int obj)
{
	if(!node->IsLeaf()){//不是叶节点
		EraseNoLeaf(node,obj);
	}
	else{//叶节点
		//数据项不是最小,或删除的是叶子根节点
		if(node->m_vecData.size() > node->m_nMIN || node->m_pParent==NULL)
			node->Remove(obj);
		else
			EraseLeftMin(node,obj);
	}
}



//******************************
//name:EraseNoLeaf
//operation:删除数据在非叶节点上
//param:BTreeNode *node,int obj
//return:none
void BTree::EraseNoLeaf(BTreeNode *node,int obj)
{
	BTreeNode *temp=NULL;
	int changeData=0;
	int pos=node->Search(obj);//obj在节点node中的位置
	temp=node->LeftMax(pos);
	if(!temp->IsMin()){//中序前驱节点数据项数目大于m_nMIN
			changeData=temp->m_vecData[temp->m_vecData.size()-1];
			node->m_vecData[pos]=changeData;
			temp->Remove(changeData);
			return ;//删除结束
	}
	temp=node->RightMin(pos);
	if(!temp->IsMin()){//中序后继节点数据项数目大于m_nMIN
		changeData=temp->m_vecData[0];
		node->m_vecData[pos]=changeData;
		temp->Remove(changeData);
		return ;//删除结束
	}
	//左右子节点均为最小数据数目
	temp=node->RightMin(pos);
	changeData=temp->m_vecData[0];
	node->m_vecData[pos]=changeData;
	EraseLeftMin(temp,changeData);
}




//**********************************************
//name:EraseLeftMin
//operation:删除,数据项数目等于m_nMIN
//param:BTreeNode *node,int obj
//return:none
void BTree::EraseLeftMin(BTreeNode *node,int obj)
{
	BTreeNode *temp=node;
	BTreeNode *parent=temp->m_pParent;
	int changeData=0;	
	BTreeNode *left=NULL;
	BTreeNode *right=NULL;
	int pos=parent->SearchPos(node);//查找目标节点在其父节点中位置
	//如果左兄弟数据项数目大于m_nMIN
	if(!parent->LeftIsMin(pos-1)){
		left=parent->m_vecSonNode[pos-1];
		//将父节点parent->m_vecData[pos-1]传递到目标节点
		node->Remove(obj);
		node->InsertSort(parent->m_vecData[pos-1],NULL,NULL);
		//将左节点最大值覆盖parent->m_vecData[pos-1]
		int deletePos=left->m_vecData.size()-1;
		parent->m_vecData[pos-1]=left->m_vecData[deletePos];
		left->m_vecData.pop_back();//删除左子节点最大值
		return ;//删除结束
	}
	//如果右兄弟数据项数目大于m_nMIN
	if(!parent->RightIsMin(pos+1)){
		right=parent->m_vecSonNode[pos+1];
		//将父节点parent->m_vecData[pos]传递到目标节点
		node->Remove(obj);
		node->InsertSort(parent->m_vecData[pos],NULL,NULL);
		//将右节点最小值覆盖parent->m_vecData[pos]
		parent->m_vecData[pos]=right->m_vecData[0];
		right->m_vecData.erase(right->m_vecData.begin());//删除右子结点最小值
		return ;//删除结束
	}
	//左右兄弟结点数据项数目均为最小值
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
//operation:组合相应节点,连接父节点
//param:BTreeNode * obj
//return:(BTreeNode *)返回组合后的节点的父节点
BTreeNode * BTree::CombineAndLink(BTreeNode * obj){
	BTreeNode *temp;
	BTreeNode *parent=obj->m_pParent;
	
	int pos=parent->SearchPos(obj);
	//左兄弟不存在
	if(pos==0)
		pos++;
	//将obj左兄弟和其父节点中序后继数据项，以及obj本身组合
	temp=Combine(parent->m_vecSonNode[pos-1],parent->m_vecData[pos-1],
				parent->m_vecSonNode[pos]);

	parent->Remove(parent->m_vecData[pos-1]);//从父节点删除被temp组合的数据项
	parent->m_vecSonNode[pos-1]=temp;//连接组合后的子结点
	temp->m_pParent=parent;
	for(int i=pos;i<=parent->m_vecData.size();i++){//移动子结点指针
		parent->m_vecSonNode[i]=parent->m_vecSonNode[i+1];
	}

	if(temp->IsFull()){//当合并以后的节点不符合规范时,将节点分离
			BTreeNode *right=CreatNewNode();
			int mid=temp->m_vecData[temp->m_nKEYNUM/2];
			temp->Split(temp->m_nKEYNUM/2,right);
			parent->InsertSort(mid,temp,right);
	}
	if(parent->IsLessThanMin() && parent->m_pParent==NULL){//当parent已经是根节点
		if(parent->m_vecData.size()==0){//父节点可能为空
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
//operation:清空树
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
