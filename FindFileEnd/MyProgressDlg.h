#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CMyProgressDlg �Ի���

class CMyProgressDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyProgressDlg)

public:
	CMyProgressDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CMyProgressDlg();

	// �Ի�������
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	// ������
	CProgressCtrl m_ProgRessCtrl;
	void SetPog(unsigned int * Pog);
	void SetThreadText(CString Name);
	virtual BOOL OnInitDialog();
	// ��������  fuck
	CStatic m_StaticText;
};
