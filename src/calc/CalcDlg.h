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
* 30 Jan 2003	AL	- initial revision
*
*/

#pragma once


class CCalcDlg : public CDialog {
public:
	CCalcDlg(CWnd* pParent = NULL);

	enum { IDD = IDD_CALC_DIALOG };

	void OnTextInput();
	void OnEval();
	void OnAbout();
	void OnCopy();

	BOOL PreTranslateMessage(MSG* pMsg);

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

protected:
	HICON m_hIcon;

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
};
