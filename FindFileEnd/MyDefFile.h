#pragma once
#include "stdafx.h"
#include <afxwin.h>//���ͷ�ļ��ر�����������������ĳ��ͷ�ļ���ǰ�����  FUCK
#include <Windows.h>
#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <WinIoCtl.h>
#include <map>
#include <vector>
//#include "MyCreateTable.h"

#define LQMAIN int main()
#define  START {
#define  END }

#define OUT_ROOT_NUMBER 1407374883553285 //�������������Ŀ¼��������
#define MAX_DIV_FILE_SYSTEM_STR_LEN 6
#define START_SCANF_DIV 'A'
#define END_SCANF_DIV 'Z'
#define TRUE_FILE_SYSTEM _T("NTFS")
#define  MAX_BUFFER_LEN 65536
using namespace std;
//�ļ���Ϣ�ڵ�
typedef struct FILE_INFO_VEC_NODE 
{
	CString CurrFileName;
	DWORDLONG CurrFileNumber;
};
//ÿ���̶�Ӧ�ı�
typedef vector<FILE_INFO_VEC_NODE> STD_TABLE_VEC;
//��װ�ɽṹ�����
typedef struct MAX_TABLE_VEC
{
	CString DivName;
	STD_TABLE_VEC *m_StaTable;
};
//�������������ж�Ӧ�ı�
typedef vector<MAX_TABLE_VEC> FILE_TABLE_VEC;
//.....

//�ļ���Ϣ�ڵ�
typedef struct FILE_INFO_MAP_NODE
{
	CString CurrFileName;
	DWORDLONG ParentFileNumber;//��ǰ�ļ��ĸ���Ŀ¼
	//unsigned short FileAttribute;//��ʾ���ļ����� �ļ���ʲô��
	// 	FILE_INFO_MAP_NODE()
	// 	{
	// 	//	this->FileAttribute=0;
	// 	}
};
//����Ķ���һ��
typedef DWORDLONG FILE_INDEX;
typedef DWORDLONG FILE_NUMBER;
//ÿ���̶�Ӧ���ļ�ӳ���
typedef map<FILE_NUMBER,FILE_INFO_MAP_NODE> STD_DIV_MAP;
//�������������ж�Ӧ���ļ�ӳ���
typedef struct MAX_TABLE_MAP
{
	CString DivName;
	STD_DIV_MAP * m_StdDivMap;
};

typedef vector<MAX_TABLE_MAP> FILE_TABLE_MAP;
//....
//�м��ѯ�����  �м��ѯ�������������������������������������������������������������������������������������������������������������������������������������������������������������������������
typedef vector<DWORDLONG> TEMP_RES_TABLE;
//ÿ���̶�Ӧ�Ĳ�ѯ�����
typedef struct MAX_TEMP_RES_TABLE
{
	CString DivName;
	TEMP_RES_TABLE * m_TempResTable;
	//ǿ��ʹ�ù��캯��
	MAX_TEMP_RES_TABLE(CString DivName,TEMP_RES_TABLE * TempResTable)//ǿ��ʹ�ù��캯��
	{
		this->DivName=DivName;
		this->m_TempResTable=TempResTable;
	}
	~MAX_TEMP_RES_TABLE()
	{
		//��ʱ�Ȳ����������������
		//	delete this->m_TempResTable;
		//���ﲻ��delete ������� ��Ϊ��ֻ�г�ʼ����ʱ��Ÿ������ڴ� Ҫ������delete��  ��ô�´β������군��
	}
};
//�������������ж�Ӧ���м��ѯ��
typedef vector<MAX_TEMP_RES_TABLE> RES_TABLE;
//......................


//�����������
//typedef vector<HANDLE> DIV_HANDLE_TABLE;

typedef struct DIV_HANDLE_NODE//�������캯������
{
	CString DivName;//����������
	HANDLE m_Handle;//���������

	DIV_HANDLE_NODE(CString DivName,HANDLE DivHandle)
	{
		this->DivName=DivName;
		this->m_Handle=DivHandle;
	}
};

typedef vector<DIV_HANDLE_NODE> DIV_HANDLE_TABLE;// ������У���

//���ڲ�ѯ��������ض���  ����ѯ�����������������������������������������������������������������������������������������������������������������������������������������������������������������������������

typedef struct REAL_RES_TABLE 
{
	CString RealFilePath;
	STD_DIV_MAP::iterator ItrFileInfo;

	REAL_RES_TABLE(CString RealPath,STD_DIV_MAP::iterator ItrFileInfo)
	{//ǿ��ʹ�ù��캯��
		this->ItrFileInfo=ItrFileInfo;
		this->RealFilePath=RealPath;
	}
};
typedef vector<REAL_RES_TABLE> RES_TABLE_VECTOR;//���Ĳ�ѯ��

//������̺߳���ʹ�õĲ���

typedef struct THREAD_PARAM 
{
	size_t *m_CtrlThread;
	STD_TABLE_VEC *m_pStdTableVec;//�������������ļ�ӳ���
	TEMP_RES_TABLE *m_pTempResTable;//�������������м��ѯ��
	CString m_InputName;//������ļ�����
	THREAD_PARAM(size_t *CtrlThread,STD_TABLE_VEC *pStdTableVec,TEMP_RES_TABLE *pTempResTable,CString InputName)//ǿ�ƹ��캯��
	{
		this->m_CtrlThread=CtrlThread;
		this->m_InputName=InputName;
		this->m_pStdTableVec=pStdTableVec;
		this->m_pTempResTable=pTempResTable;
	}
};

typedef vector<THREAD_PARAM*> THREAD_PARAM_VEC;

void InitMyListCtrl(CListCtrl * m_ListCtrl);

void SetMyListCtrl(CListCtrl * m_ListCtrl, RES_TABLE_VECTOR *FileRealRes);

