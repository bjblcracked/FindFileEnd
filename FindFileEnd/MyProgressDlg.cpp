// MyProgressDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FindFileEnd.h"
#include "MyProgressDlg.h"
#include "afxdialogex.h"


// CMyProgressDlg �Ի���

IMPLEMENT_DYNAMIC(CMyProgressDlg, CDialogEx)

	CMyProgressDlg::CMyProgressDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyProgressDlg::IDD, pParent)
{

}

CMyProgressDlg::~CMyProgressDlg()
{
}

void CMyProgressDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_ProgRessCtrl);
	DDX_Control(pDX, IDC_STATIC1, m_StaticText);
}


BEGIN_MESSAGE_MAP(CMyProgressDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyProgressDlg ��Ϣ�������
void CMyProgressDlg::SetPog(unsigned int * Pog)
{
	//HWND
	
	if (*Pog<=100&&Pog)
	{
		this->m_ProgRessCtrl.SetPos(*Pog);
		if (100==(*Pog))
		{
			Sleep(500);
			this->ShowWindow(SW_HIDE);
			TRACE("�ر�ɨ����̶Ի���\n");
		}
	}
}

BOOL CMyProgressDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	/*AfxGetMainWnd()->*/
	SetWindowPos(&CWnd::wndTopMost,0,0,0,0,SWP_NOSIZE|SWP_NOMOVE);//���ô�����ǰ
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CMyProgressDlg::SetThreadText(CString Name)
{
	this->m_StaticText.SetWindowText(Name);
}
