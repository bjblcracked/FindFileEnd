#include "stdafx.h"
#include "MyDefFile.h"

void InitMyListCtrl(CListCtrl * m_ListCtrl)
{
	m_ListCtrl->SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES/*��ʾ����*/);
	//m_ListCtrl->InsertColumn(0,_T("�ļ���"),LVCFMT_CENTER,220);
	m_ListCtrl->InsertColumn(0,_T("�ļ�·��"),LVCFMT_CENTER,1000);
// 	m_ListCtrl->InsertColumn(2,_T("�ļ���С"),LVCFMT_CENTER,220);
// 	m_ListCtrl->InsertColumn(3,_T("�ļ�����޸�����"),LVCFMT_CENTER,220);
}

void SetMyListCtrl(CListCtrl * m_ListCtrl, RES_TABLE_VECTOR *FileRealRes)
{
	m_ListCtrl->DeleteAllItems();
	size_t CountRes=0;
	while (CountRes<FileRealRes->size())
	{
		m_ListCtrl->InsertItem(CountRes,FileRealRes->at(CountRes).RealFilePath);
		++CountRes;
	}
}