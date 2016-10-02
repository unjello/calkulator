/*
* application entry point
*
* calculator
* (c) 2003 andrzej lichnerowicz. all rights reserved.
* 
* permission to copy, use, modify, sell and distribute this software 
* is granted provided this copyright notice appears in all copies. 
* this software is provided "as is" without express or implied warranty, 
* and with no claim as to its suitability for any purpose.
*
* Changeslog:
* 30 Jan 2003	AL	- initial revision
*
*/
#include "StdAfx.h"
#include "Calc.h"
#include "CalcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


BEGIN_MESSAGE_MAP(CCalcApp, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()


CCalcApp::CCalcApp() {
}
CCalcApp theApp;


BOOL CCalcApp::InitInstance() {
	InitCommonControls();
	CWinApp::InitInstance();
	AfxEnableControlContainer();


	CCalcDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();

	return FALSE;
}
