/*
* main dialog
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
* 12 Mar 2003	AL	+ added overflow guard for hex, bin and oct
* 07 Mar 2003	AL	* decimal number formatting fixed
*					* formatting done on streams
*					* tuned error reporting
* 30 Jan 2003	AL	- initial revision
*
*/
#include "StdAfx.h"
#include "Calc.h"
#include "CalcDlg.h"
#include "../core/Engine.h"
#include <sstream>

#include <boost/spirit/phoenix/primitives.hpp>
#include <boost/spirit/phoenix/binders.hpp>
using namespace phoenix;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CCalcDlg::CCalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalcDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCalcDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_INPUT,OnTextInput)
	ON_COMMAND(IDM_EVAL,OnEval)
	ON_COMMAND(IDM_ABOUT,OnAbout)
	ON_COMMAND(IDM_COPY,OnCopy)
END_MESSAGE_MAP()


CString long2bin(unsigned long num) {
	CString tmp;
	for(int i=0;i<32;++i) {
		tmp+=num&(1<<i)?"1":"0";
	}
	while(i&&tmp[i-1]=='0') --i;

	if(!i) return "0";
	CString ret;
	while(i--) ret+=tmp[i];

	return ret;
}

BOOL CCalcDlg::OnInitDialog() {
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	((CEdit*)GetDlgItem(IDC_EVAL_DEC))->ModifyStyle(ES_LEFT|ES_CENTER,ES_RIGHT);
	((CEdit*)GetDlgItem(IDC_EVAL_HEX))->ModifyStyle(ES_LEFT|ES_CENTER,ES_RIGHT);
	((CEdit*)GetDlgItem(IDC_EVAL_BIN))->ModifyStyle(ES_LEFT|ES_CENTER,ES_RIGHT);
	((CEdit*)GetDlgItem(IDC_EVAL_OCT))->ModifyStyle(ES_LEFT|ES_CENTER,ES_RIGHT);
	((CEdit*)GetDlgItem(IDC_EVAL_EXP))->ModifyStyle(ES_LEFT|ES_CENTER,ES_RIGHT);

	CButton* wndDecRadio=(CButton*)GetDlgItem(IDC_DEC);
	wndDecRadio->SetCheck(TRUE);
	CEdit* wndInput=(CEdit*)GetDlgItem(IDC_INPUT);
	wndInput->SetFocus();
	OnTextInput();
	
	return FALSE;
}

void CCalcDlg::OnPaint() {
	if (IsIconic())	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		dc.DrawIcon(x, y, m_hIcon);
	} else {
		CDialog::OnPaint();
	}
}

HCURSOR CCalcDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalcDlg::OnTextInput() {
	CEdit* wndInput=(CEdit*)GetDlgItem(IDC_INPUT);
	
	CEdit* wndDec=(CEdit*)GetDlgItem(IDC_EVAL_DEC);
	CEdit* wndHex=(CEdit*)GetDlgItem(IDC_EVAL_HEX);
	CEdit* wndBin=(CEdit*)GetDlgItem(IDC_EVAL_BIN);
	CEdit* wndOct=(CEdit*)GetDlgItem(IDC_EVAL_OCT);
	CEdit* wndExp=(CEdit*)GetDlgItem(IDC_EVAL_EXP);

	CString sInput;
	wndInput->GetWindowText(sInput);

	try {
		double ret=Calculate(sInput.GetBuffer());

		ostringstream dec_,hex_,oct_,exp_;
		dec_.precision(10);
		dec_<<ret;
		hex_<<hex<<uppercase<<static_cast<DWORD>(ret);
		oct_<<oct<<static_cast<DWORD>(ret);
		exp_<<scientific<<showpoint<<ret;
		wndDec->SetWindowText(dec_.str().c_str());
		wndExp->SetWindowText(exp_.str().c_str());
		if(ret>double(0xffffffff)) {
			wndHex->SetWindowText("Overflow");
			wndBin->SetWindowText("Overflow");
			wndOct->SetWindowText("Overflow");
		} else {
			wndHex->SetWindowText(hex_.str().c_str());
			wndBin->SetWindowText(long2bin(static_cast<DWORD>(ret)));
			wndOct->SetWindowText(oct_.str().c_str());
		}
	} catch(...) {
		const char* sResult=sInput==""?"0":"Error";
		wndDec->SetWindowText(sResult);
		wndHex->SetWindowText(sResult);
		wndBin->SetWindowText(sResult);
		wndOct->SetWindowText(sResult);
		wndExp->SetWindowText(sResult);
	}
}

void CCalcDlg::OnEval() {
	CButton* wndDec=(CButton*)GetDlgItem(IDC_DEC);
	CButton* wndHex=(CButton*)GetDlgItem(IDC_HEX);
	CButton* wndBin=(CButton*)GetDlgItem(IDC_BIN);
	CButton* wndOct=(CButton*)GetDlgItem(IDC_OCT);
	CButton* wndExp=(CButton*)GetDlgItem(IDC_EXP);

	CString sNewInput,sDecInput,sHexInput;
	((CEdit*)GetDlgItem(IDC_INPUT))->GetWindowText(sNewInput);
	((CEdit*)GetDlgItem(IDC_EVAL_DEC))->GetWindowText(sDecInput);

	if(sDecInput!="Error") {
		((CEdit*)GetDlgItem(IDC_EVAL_HEX))->GetWindowText(sHexInput);
		if(sHexInput!="Overflow") {
			if(wndHex->GetCheck()) {
				CString txt;
				((CEdit*)GetDlgItem(IDC_EVAL_HEX))->GetWindowText(txt);
				sNewInput="0x"+txt;
			}
			if(wndBin->GetCheck()) {
				CString txt;
				((CEdit*)GetDlgItem(IDC_EVAL_BIN))->GetWindowText(txt);
				sNewInput=txt+"b";
			}
			if(wndOct->GetCheck()) {
				CString txt;
				((CEdit*)GetDlgItem(IDC_EVAL_OCT))->GetWindowText(txt);
				sNewInput="0"+txt;
			}
		}
		if(wndDec->GetCheck()) ((CEdit*)GetDlgItem(IDC_EVAL_DEC))->GetWindowText(sNewInput);
		if(wndExp->GetCheck()) ((CEdit*)GetDlgItem(IDC_EVAL_EXP))->GetWindowText(sNewInput);
		((CEdit*)GetDlgItem(IDC_INPUT))->SetWindowText(sNewInput);
	}
}

class CAboutDlg : public CDialog {
public:
	CAboutDlg();

	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()

void CCalcDlg::OnAbout() {
	CAboutDlg dlg;
	dlg.DoModal();
}

void CCalcDlg::OnCopy() {
	if(!OpenClipboard()) {
		MessageBox("cannot copy to clipboard","commencing ritual harakiri");
		return;
	}
	if(!EmptyClipboard()) {
		MessageBox("cannot copy to clipboard","commencing ritual harakiri");
		return;
	}
	CString sInput;
	((CEdit*)GetDlgItem(IDC_INPUT))->GetWindowText(sInput);
	const long len=sInput.GetLength();
	HGLOBAL hData=GlobalAlloc(GMEM_MOVEABLE,len+1);
	if(hData==NULL) { 
		MessageBox("cannot copy to clipboard","commencing ritual harakiri");
		CloseClipboard(); 
		return; 
	} 
	char *temp=(char*)GlobalLock(hData); 
	strcpy(temp,sInput.GetBuffer());
	GlobalUnlock(hData);
	if(::SetClipboardData(CF_TEXT,hData)==NULL) {
		MessageBox("cannot copy to clipboard","commencing ritual harakiri");
		CloseClipboard();
		return;
	}
	CloseClipboard();
}

BOOL CCalcDlg::PreTranslateMessage(MSG* pMsg) {
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_ESCAPE) {
		((CEdit*)GetDlgItem(IDC_INPUT))->SetWindowText("");
		OnTextInput();
		return TRUE;
	}

	return CDialog::PreTranslateMessage(pMsg);
}
