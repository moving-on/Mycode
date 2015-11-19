// TestDlg.h : main header file for the TESTDLG application
//

#if !defined(AFX_TESTDLG_H__C4BFDC90_D004_4682_9265_B6BFB6F748F5__INCLUDED_)
#define AFX_TESTDLG_H__C4BFDC90_D004_4682_9265_B6BFB6F748F5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestDlgApp:
// See TestDlg.cpp for the implementation of this class
//

class CTestDlgApp : public CWinApp
{
public:
	CTestDlgApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestDlgApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__C4BFDC90_D004_4682_9265_B6BFB6F748F5__INCLUDED_)
