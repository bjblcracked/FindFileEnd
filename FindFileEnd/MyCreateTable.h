#pragma once
#include "MyDefFile.h"
typedef vector<CString> DIV_VEC;
class CMyCreateTable
{
public:
	CMyCreateTable(FILE_TABLE_MAP *FileTableMap);
	~CMyCreateTable(void);
public:
	void CreateMaxFileTable(unsigned int *progress);//�����ܱ�

private:
	void SelectDiv();
	void GetDivHandle();
	void CreateMinFileTable(DIV_HANDLE_NODE *DivHandleNode,//�������������
	MAX_TABLE_MAP &MaxTableMap);//�����̵Ŀ��ٲ��ұ�
	FILE_INFO_MAP_NODE TempInfoMapNode;
private:
	FILE_TABLE_MAP * FileTableMap;
	DIV_VEC m_DivList;
	DIV_HANDLE_TABLE m_DivHandleTable;//�����������
};

