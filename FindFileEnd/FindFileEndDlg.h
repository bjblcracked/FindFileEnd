
// FindFileEndDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "MyDefFile.h"
#include "MyCreateTable.h"
#include "MyQueryFile.h"
#include "MyProgressDlg.h"

typedef struct PARAM_INPUT
{//ɨ���̲߳�����
	CMyCreateTable * m_pCreat;
	unsigned int *m_Progress;
};

typedef struct POG_PARAM
{
	CMyProgressDlg * m_Dlg;
	unsigned int * m_Pog;
};
// CFindFileEndDlg �Ի���
class CFindFileEndDlg : public CDialogEx
{
// ����
public:
	CFindFileEndDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FINDFILEEND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CMyProgressDlg m_ProgressDlg;
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ������ļ�����
	CEdit m_InputFileName;
	CListCtrl m_ListCrtl;

	 FILE_TABLE_MAP * FileTableMap;//������ó�ȫ�ֵ�  ���ô��ʵ��
	 RES_TABLE_VECTOR *FileRealRes;
	 afx_msg void OnBnClickedButton1();

	 CMyCreateTable *m_CreatTable;
	 CMyQueryFile *m_QueryFile;
	 afx_msg void OnEnChangeEdit1();
	 afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	 virtual BOOL PreTranslateMessage(MSG* pMsg);
	 afx_msg void OnNMRClickList1(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	 afx_msg void OnRClickOpenFile();
};
