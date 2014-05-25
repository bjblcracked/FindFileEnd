
// FindFileEndDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FindFileEnd.h"
#include "FindFileEndDlg.h"
#include "afxdialogex.h"
#include "MyDefFile.h"
#include <process.h>
#include "MyProgressDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
//����һ��ȫ�ֵĽ�����ʾ�Ի���

// CFindFileEndDlg �Ի���

void ProcThread(void* Param)
{
	CMyCreateTable * pCreate=((PARAM_INPUT*)Param)->m_pCreat;
	unsigned int * Progress=((PARAM_INPUT*)Param)->m_Progress;
	pCreate->CreateMaxFileTable(Progress);
	_endthread();
}

void ProcThreadPog(void * Param)
{
	CMyProgressDlg * Dlg=((POG_PARAM*)Param)->m_Dlg;
	unsigned * Pog=((POG_PARAM*)Param)->m_Pog;
	Dlg->Create(IDD_DIALOG1);
	Dlg->ShowWindow(SW_SHOW);
	Dlg->SetThreadText(_T("��ȡUSN��־��......."));
	int Flg=0;
	while ((*Pog)<=100)
	{
		Dlg->SetPog(Pog);
		if (100==(*Pog))
		{
			++Flg;
		}
		if (Flg)
		{
			_endthread();
		}
	}
}
CFindFileEndDlg::CFindFileEndDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFindFileEndDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	FileTableMap=new FILE_TABLE_MAP;
	FileRealRes=nullptr;
	this->m_CreatTable=new CMyCreateTable(FileTableMap);
	this->m_QueryFile= new CMyQueryFile(FileTableMap);//��ʼ��һ��
}

void CFindFileEndDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_InputFileName);
	DDX_Control(pDX, IDC_LIST1, m_ListCrtl);
}

BEGIN_MESSAGE_MAP(CFindFileEndDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CFindFileEndDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CFindFileEndDlg::OnEnChangeEdit1)
	ON_WM_CHAR()
	ON_NOTIFY(NM_RCLICK, IDC_LIST1, &CFindFileEndDlg::OnNMRClickList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CFindFileEndDlg::OnNMDblclkList1)
	ON_COMMAND(ID_32771, &CFindFileEndDlg::OnRClickOpenFile)
END_MESSAGE_MAP()


// CFindFileEndDlg ��Ϣ�������

BOOL CFindFileEndDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	//this->m_CreatTable->CreateMaxFileTable();//��ʼ����ѯ��
	unsigned int * MyProgress=new unsigned int;
	*MyProgress=1;
	PARAM_INPUT *Param=new PARAM_INPUT;
	Param->m_pCreat=this->m_CreatTable;
	Param->m_Progress=MyProgress;
	_beginthread(ProcThread,0,Param);

	CMyProgressDlg *ProgressDlg=new CMyProgressDlg;
	POG_PARAM *PogParam=new POG_PARAM;
	PogParam->m_Dlg=ProgressDlg;
	PogParam->m_Pog=MyProgress;
	//ProgressDlg->Create()
	//ProgressDlg.DoModal();
	_beginthread(ProcThreadPog,0,PogParam);

	this->m_QueryFile->InitQuery();
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitMyListCtrl(&m_ListCrtl);
	//������ʾ�Ի���
	//ProgressDlg.DoModal();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFindFileEndDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
	RECT EditRec;
	RECT WndRec;
	RECT ListCtrlRec;
	this->GetClientRect(&WndRec);
	this->m_InputFileName.GetClientRect(&EditRec);
	this->m_ListCrtl.GetClientRect(&ListCtrlRec);
	//EditRec.right=WndRec.right;
	//EditRec.left=WndRec.left;
	this->m_InputFileName.MoveWindow(0,0,WndRec.right,25);
	this->m_ListCrtl.MoveWindow(0,25,WndRec.right,WndRec.bottom);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFindFileEndDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFindFileEndDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	CString InputFileName;
	this->m_InputFileName.GetWindowText(InputFileName);
	if (InputFileName.GetLength()<2)
	{
		MessageBox(_T("�ļ�����̫���ˣ����̫���˲�����ʾ��"));
	}else
	{
		//MessageBox(InputFileName);
		m_QueryFile->GetFileFormTableByNameEx(InputFileName);
		this->FileRealRes=m_QueryFile->GetPointRealPathTable();
		SetMyListCtrl(&m_ListCrtl,FileRealRes);
		size_t CountFile=FileRealRes->size();
		CString CountStr;
		CountStr.Format(_T("�����ҵ���%d���ļ�"),CountFile);
		GetWindowText(InputFileName);
		SetWindowText(InputFileName+=CountStr);
	}
	//GetWindowText(InputFileName);
	//ShellExecute(0,L"open",FileRealRes->at(0).RealFilePath,NULL,NULL,SW_SHOW);//ʹ��ϵͳ���ļ�
}


void CFindFileEndDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	CString Tmp;
	m_InputFileName.GetWindowText(Tmp);
	SetWindowText(Tmp+=_T(" - Go For It!"));
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CFindFileEndDlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{//�������������
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nChar=='\n')
	{
		OnBnClickedButton1();
	}
	CDialogEx::OnChar(nChar, nRepCnt, nFlags);
}


BOOL CFindFileEndDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (WM_KEYFIRST<=pMsg->message&&pMsg->message<=WM_KEYLAST)
	{
		//MessageBox(_T("���̰���"));
		if (pMsg->wParam==VK_RETURN)
		{
			OnBnClickedButton1();
			return TRUE;
		}
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CFindFileEndDlg::OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMenu m_menu;
	m_menu.LoadMenu(IDR_MENU1);
	int x=pNMItemActivate->ptAction.x;
	int y=pNMItemActivate->ptAction.y;
	CPoint pt;

	//��ȡ��ǰ����λ��
	GetCursorPos(&pt);
	//
	//m_List.GetDC()->LPtoDP(&pt);
	m_menu.GetSubMenu(0)->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON,pt.x,pt.y,this);
	//.......
	*pResult = 0;
}


void CFindFileEndDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//MessageBox(_T("DBClick"));
	POSITION ps=this->m_ListCrtl.GetFirstSelectedItemPosition();
	if (ps)
	{
		int item=this->m_ListCrtl.GetNextSelectedItem(ps);
		CString FileRealPath=this->m_ListCrtl.GetItemText(item,0); //��ȡ�ļ���
		//MessageBox(ws);
		ShellExecute(0,_T("open"),FileRealPath,NULL,NULL,SW_SHOW); //���ļ�
	}
	*pResult = 0;
}


void CFindFileEndDlg::OnRClickOpenFile()
{
	// TODO: �ڴ���������������
// 	MessageBox(_T("������ڴ��"));
// 	int * tmp=(int*)malloc(sizeof(char)*1024*1024*50);
}
