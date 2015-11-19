// TestDlgDlg.h : header file
//

#if !defined(AFX_TESTDLGDLG_H__3A1E6430_98F2_41D4_9E49_39C015273BF1__INCLUDED_)
#define AFX_TESTDLGDLG_H__3A1E6430_98F2_41D4_9E49_39C015273BF1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "BTree.h"
#include <time.h>
#include <stdlib.h>



/////////////////////////////////////////////////////////////////////////////
// CTestDlgDlg dialog

class CTestDlgDlg : public CDialog
{
// Construction
public:
	CTestDlgDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlgDlg)
	enum { IDD = IDD_TESTDLG_DIALOG };
	CButton	m_CreateBut;
	CSpinButtonCtrl	m_nRandSpin;
	int		m_nDeleteData;
	int		m_nNodeCount;
	CString	m_strInsertData;
	int		m_nInsertData;
	int		m_nRandCount;
	int		m_nTREEKEY;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnInsert();
	afx_msg void OnDelete();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual void OnOK();
	afx_msg void OnCreateRand();
	afx_msg void OnEraseall();
	afx_msg void OnAbout();
	afx_msg void OnSetTreeKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//**********************add my code******************************************
private:
	BTree* m_pBTree;
	CClientDC *  m_pDrawDC;
	CScrollBar *m_hScroll;
	CStatic *m_Board;
	int pos_x;
	int m_nNodeWidth;
	int m_nNodeHeight;
	int m_nDeepHeight;
	int m_MaxWidth;//画所有节点最大的宽度
	CRect m_VisRect;//可视的矩形
	CPen m_Pen;
	void DrawNode(BTreeNode *node);
	void DrawLine(BTreeNode *node);
	void CreateBTree(int key);
	void SetNodePos();
	void SetParentNodePos(queue<BTreeNode*> & que);
	void GetLeafNodeQue(queue<BTreeNode*> & que);
public:
	void DrawDetail();
	void SetDC();
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLGDLG_H__3A1E6430_98F2_41D4_9E49_39C015273BF1__INCLUDED_)
