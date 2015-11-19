// TestDlgDlg.cpp : implementation file
//


#include "TestDlg.h"
#include "TestDlgDlg.h"
#include "BTree.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog

CTestDlgDlg::CTestDlgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlgDlg)
	m_nDeleteData = 0;
	m_nNodeCount = 0;
	m_nInsertData = 0;
	m_nRandCount = 0;
	m_nTREEKEY = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlgDlg)
	DDX_Control(pDX, ID_CreateRand, m_CreateBut);
	DDX_Control(pDX, IDC_RAND_SPIN, m_nRandSpin);
	DDX_Text(pDX, IDC_DELETE_DATA, m_nDeleteData);
	DDV_MinMaxInt(pDX, m_nDeleteData, 0, 1000);
	DDX_Text(pDX, IDC_NODE_COUNT, m_nNodeCount);
	DDX_Text(pDX, IDC_INSERT_DATA, m_nInsertData);
	DDV_MinMaxInt(pDX, m_nInsertData, 0, 999);
	DDX_Text(pDX, IDC_RAND_COUNT, m_nRandCount);
	DDV_MinMaxInt(pDX, m_nRandCount, 0, 100);
	DDX_Text(pDX, IDC_TREE_KEY, m_nTREEKEY);
	DDV_MinMaxInt(pDX, m_nTREEKEY, 3, 20);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlgDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlgDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_INSERT, OnInsert)
	ON_BN_CLICKED(IDC_DELETE, OnDelete)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_BN_CLICKED(ID_CreateRand, OnCreateRand)
	ON_BN_CLICKED(IDC_ERASEALL, OnEraseall)
	ON_BN_CLICKED(IDC_About, OnAbout)
	ON_BN_CLICKED(IDC_SET_TREE_KEY, OnSetTreeKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg message handlers

BOOL CTestDlgDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// ********************add my code***************************************
	srand(time(0));
	pos_x=0;
	m_nNodeCount=0;
	m_nInsertData=rand()%1000;
	m_nDeleteData=rand()%1000;
	m_nRandCount=10;
	m_nTREEKEY=3;
	m_pBTree=NULL;
	m_nNodeWidth=25;
	m_nDeepHeight=15;
	SetDC();
	m_nRandSpin.SetRange(0,100);
	m_hScroll=(CScrollBar *)GetDlgItem(IDC_H_SCROLL_BAR);
	UpdateData(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlgDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlgDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
	//*****************add my code*************************************8
	if(m_pBTree!=NULL)
		DrawDetail();
	m_hScroll->SetScrollRange(0,m_MaxWidth);
	m_hScroll->SetScrollPos(pos_x);
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlgDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

//operation: new 一个树对象
//name:CreateBTree
//param:(int key)树的阶数
//return:void
void CTestDlgDlg::CreateBTree(int key)
{
	if(m_pBTree!=NULL){
		if(m_pBTree->GetKey()!=m_nTREEKEY){//如果没有改变阶数，不做处理
			OnEraseall();
			delete m_pBTree;
		}
		else
			return;
	}
	m_pBTree=new BTree(key);
	m_nNodeHeight=m_pBTree->GetRoot()->GetKEY()*10;
}

//operation:插入相应节点
//name:OnInsert
//param:none
//return:void
void CTestDlgDlg::OnInsert() 
{
	if(UpdateData()==FALSE)  return;
	if(m_pBTree==NULL)
		CreateBTree(m_nTREEKEY);
	// TODO: Add your control notification handler code here
	if(m_pBTree->Search(m_nInsertData)==true){
		MessageBox("已经存在！");
		m_nInsertData=rand()%1000;
		UpdateData(false);
		return;
	}
	m_pBTree->Insert(m_nInsertData);
	m_nNodeCount++;
	InvalidateRect(&m_VisRect);
	SetNodePos();
	if(m_nNodeCount!=0)
			m_CreateBut.SetWindowText("随机插入");
	m_nInsertData=rand()%1000;
	UpdateData(false);
}

//operation:删除相应的节点
//name:OnDelete
//param:none
//return:void
void CTestDlgDlg::OnDelete() 
{
	if(UpdateData()==FALSE)  return;
	if(m_pBTree==NULL)
		CreateBTree(m_nTREEKEY);
	// TODO: Add your control notification handler code here
	if(m_pBTree->Search(m_nDeleteData)!=true){
		MessageBox("不存在！");
		m_nDeleteData=rand()%1000;
		UpdateData(false);
		return;
	}
	m_pBTree->Erase(m_nDeleteData);
	m_nNodeCount--;
	InvalidateRect(&m_VisRect);
	SetNodePos();
	if(m_nNodeCount==0)
		m_CreateBut.SetWindowText("生成");
	m_nDeleteData=rand()%1000;
	UpdateData(false);
}

//operation:根据设置的节点相应显示位置画图,按层次遍历画节点
//name:DrawDetail
//param:none
//return:void
void CTestDlgDlg::DrawDetail()
{
	queue<BTreeNode *> drawQue;
	BTreeNode *currNode=m_pBTree->GetRoot();
	if(currNode->IsLeaf()){//只有一个节点
		DrawNode(currNode);
		return;
	}
	drawQue.push(currNode);
	while(!drawQue.empty()){
		currNode=drawQue.front();
		drawQue.pop();
		DrawNode(currNode);
		if(!currNode->IsLeaf()){
			DrawLine(currNode);
		}
		if(!currNode->IsLeaf()){
			for(int i=0;i<currNode->GetDataCount()+1;i++){
				drawQue.push(currNode->m_vecSonNode[i]);
			}
		}//end if
	}//end while
}

//operation:找出树的最底层根结点，将所有根结点插入队列中
//name:GetLeafNodeQue
//param:(queue<BTreeNode*> & que)
//return:void
void CTestDlgDlg::GetLeafNodeQue(queue<BTreeNode*> & que)
{
	BTreeNode *currNode=m_pBTree->GetRoot();
	que.push(currNode);
	while(!currNode->IsLeaf()){
		for(int i=0;i<currNode->GetDataCount()+1;i++){
			que.push(currNode->m_vecSonNode[i]);
		}
		que.pop();
		currNode=que.front();
	}
}


//operation:设置树的que(不是最底层的叶节点)这一层节点的显示位置
//name:SetParentNodePos
//param:(queue<BTreeNode*> & que)返回que的上一层的节点的队列
//return:void
void CTestDlgDlg::SetParentNodePos(queue<BTreeNode*> & que)
{
	BTreeNode *currNode=NULL;
	BTreeNode *leftChildNode=NULL;
	BTreeNode *rightChildNode=NULL;
	BTreeNode *currParentNode=NULL;
	int nodePos;
	int nodeCount=que.size();
	for (nodeCount=que.size();nodeCount!=0;nodeCount--) {
		//setPosition
		currNode=que.front();
		nodePos=currNode->GetDataCount()/2;//找到最中间的子节点的位置，位置从0开始
		leftChildNode=currNode->m_vecSonNode[nodePos];//取得那个子结点的指针
		//根据子结点的显示位置设置父节点的显示位置
		if(currNode->GetDataCount()%2==1 ){//让父节点指向子节点的线画在子节点中间
			rightChildNode=currNode->m_vecSonNode[nodePos+1];
			nodePos=leftChildNode->m_nNodeShowPos+leftChildNode->GetDataCount();
			nodePos=(nodePos+rightChildNode->m_nNodeShowPos-1)/2;
		}
		else{
			nodePos=leftChildNode->m_nNodeShowPos+leftChildNode->GetDataCount()/2;
		}
		currNode->m_nNodeShowPos=nodePos;
		que.pop();
		//Add parent Node to parentQueue
		if(currParentNode==currNode->m_pParent || currNode->m_pParent==NULL){
			continue;//防止相同节点插入队列
		}
		else{
			que.push(currNode->m_pParent);
			currParentNode=currNode->m_pParent;
		}
	}//end for
}

//operation:设置所有节点在显示时候的相关位置
//name:SetNodePos
//param:none
//return:void
void CTestDlgDlg::SetNodePos()
{
	queue<BTreeNode *> leafNodeQue;
	queue<BTreeNode *> parentNodeQue;
	GetLeafNodeQue(leafNodeQue);
	BTreeNode *currNode;
	BTreeNode *currParentNode=NULL;
	int nodePos=1;
	while(!leafNodeQue.empty()){
		//setPosition
		currNode=leafNodeQue.front();
		currNode->m_nNodeShowPos=nodePos;
		nodePos=nodePos+currNode->GetDataCount()+1;
		leafNodeQue.pop();
		//Add parent Node to parentQueue
		if(currParentNode==currNode->m_pParent || currNode->m_pParent==NULL){
			continue;//防止相同节点插入队列
		}
		else{
			parentNodeQue.push(currNode->m_pParent);
			currParentNode=currNode->m_pParent;
		}
	}//end while
	m_MaxWidth=nodePos*m_nNodeWidth;
//	TRACE("%d\n",m_MaxWidth);
	while(!parentNodeQue.empty()){
		SetParentNodePos(parentNodeQue);
	}
}

//operation:画连接父节点和子结点的线条
//name:DrawLine
//param:(BTreeNode *node)
//return:void
void CTestDlgDlg::DrawLine(BTreeNode *node)
{
	int startPos;
	int endPos;
	BTreeNode *childNode;
	for(int i=0;i<node->GetDataCount()+1;i++){
		startPos=(node->m_nNodeShowPos+i)*m_nNodeWidth-pos_x;
		childNode=node->m_vecSonNode[i];
		endPos=(childNode->m_nNodeShowPos+childNode->GetDataCount())*m_nNodeWidth;
		endPos=endPos-childNode->GetDataCount()*(m_nNodeWidth/2)-pos_x;
		m_pDrawDC->MoveTo(startPos,node->GetDeep()*m_nNodeHeight+m_nDeepHeight);
		m_pDrawDC->LineTo(endPos,(node->GetDeep()+1)*m_nNodeHeight);
	}
	
}

//operation:画节点和包围节点的框
//name:DrawNode
//param:BTreeNode *node
//return:void
void CTestDlgDlg::DrawNode(BTreeNode *node)
{
	CString str;
	int x=0;
	int y=0;
	int rightTop=0;
	int rightBottom=0;
	for(int i=0;i<node->GetDataCount();i++){
		str.Format("%d",node->m_vecData[i]);
		x=(node->m_nNodeShowPos+i)*m_nNodeWidth-pos_x;
		if((x+m_nNodeWidth)<0 || x>(m_VisRect.right-m_VisRect.left))//当节点超出可视范围，不画
			continue;
		y=node->GetDeep()*m_nNodeHeight;
		m_pDrawDC->TextOut(x,y,str);
		m_pDrawDC->MoveTo(x,y);
		m_pDrawDC->LineTo(x,y+m_nDeepHeight);
		m_pDrawDC->LineTo(x+m_nNodeWidth,y+m_nDeepHeight);
		m_pDrawDC->LineTo(x+m_nNodeWidth,y);
		m_pDrawDC->LineTo(x,y);
	}
}

//operation:设置画图的dc
//name:SetDC
//param:none
//return:void
void CTestDlgDlg::SetDC()
{
	m_Board=(CStatic*)GetDlgItem(IDC_BOARD);
	m_Board->GetClientRect(&m_VisRect);
	m_VisRect.right+=15;
	m_VisRect.bottom+=15;
	m_pDrawDC=new CClientDC(m_Board);
	m_pDrawDC->SetBkMode(RGB(212,208,200));
	m_pDrawDC->SetTextColor(RGB(56,56,206));
	m_Pen.CreatePen(PS_SOLID,1,RGB(244,27,52));
	m_pDrawDC->SelectObject(m_Pen);
}

void CTestDlgDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CString str;
	switch(nSBCode) {
	case SB_LINELEFT:
	case SB_PAGELEFT:
		if(pos_x>0)//控制滚动，使超出可视范围部分不画
			pos_x-=m_MaxWidth/10;
		else 
			return;
		break;
	case SB_LINERIGHT:
	case SB_PAGERIGHT:
		if(pos_x<m_MaxWidth-m_VisRect.right)
			pos_x+=m_MaxWidth/10;
		else
			return;
		break;
	case SB_THUMBTRACK:
		if(nPos<m_MaxWidth-m_VisRect.right+50)
			pos_x=nPos;
		TRACE("%d\n",nPos);
		break;
	default:
		return;
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
	InvalidateRect(&m_VisRect);
}



void CTestDlgDlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}


//operation:do nothing，去掉enter按键的作用
void CTestDlgDlg::OnOK() 
{
	// TODO: Add extra validation here
	//do nothing
}

//operation:随机生成节点,随机插入节点
//name:OnCreateRand
//param:none
//return:void
void CTestDlgDlg::OnCreateRand()
{
	if(m_pBTree==NULL)
		CreateBTree(m_nTREEKEY);
	if((m_nNodeCount+m_nRandCount)>1000){
		MessageBox("您要求的节点数超过最大数1000");
		return;
	}
	// TODO: Add your control notification handler code here
	if(UpdateData()==FALSE)  return;
	int i=0;
	TRACE("%d",m_nRandCount);
	while(i!=m_nRandCount){
		int temp=rand()%1000;
		if(m_pBTree->Search(temp)!=true){
			m_pBTree->Insert(temp);
			i++;
		}
	}
	m_nNodeCount+=i;
	UpdateData(false);
	InvalidateRect(&m_VisRect);
	SetNodePos();
	m_CreateBut.SetWindowText("随机插入");
}


//operation:清除所有节点
//name:OnEraseall
//param:none
//return:void
void CTestDlgDlg::OnEraseall() 
{
	// TODO: Add your control notification handler code here
	if(m_pBTree==NULL)
		return;
	m_pBTree->Clear();
	m_pBTree=NULL;
	m_nNodeCount=0;
	UpdateData(false);
	m_CreateBut.SetWindowText("生成");
	pos_x=0;
	InvalidateRect(&m_VisRect);
}

void CTestDlgDlg::OnAbout() 
{
	// TODO: Add your control notification handler code here
	CAboutDlg about;
	about.DoModal();
}

//operation:设置树的阶数
//name:OnSetTreeKey
//param:none
//return:void
void CTestDlgDlg::OnSetTreeKey() 
{
	// TODO: Add your control notification handler code here
	if(UpdateData()==FALSE)  return;
	CreateBTree(m_nTREEKEY);
	UpdateData(false);
}

//bool CTestDlgDlg::IsMoveInVisRect(const CPoint &point)
//{
//	if(point.x>m_VisRect.left && point.x<m_VisRect.right)
//		return true;
//	else
//		return false;
//}
