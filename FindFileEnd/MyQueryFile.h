#pragma once
#include "MyDefFile.h"
#include <process.h>
class CMyQueryFile
{
public:
	CMyQueryFile(FILE_TABLE_MAP * FileTableMap);//����ʹ��������캯��
	~CMyQueryFile(void);
public:
	void InitQuery();
	void GetFileFormTableByNameEx(CString InputFileName);
	RES_TABLE_VECTOR * GetPointRealPathTable();
private:
	void GetRealFilePath(
		DWORDLONG CurrFileNumber,
		CString & RealFilePath,
		size_t CountTableMap);//�����4�����صİ汾
	void GetRealFilePath(
		DWORDLONG CurrFileNumber,
		CString & RealFilePath,
		STD_DIV_MAP * StdDivMap);
	void GetRealFilePath(
		DWORDLONG CurrFileNumber,
		CString & RealFilePath,
		size_t CountTableMap,
		STD_DIV_MAP::iterator &ItrFileInfo);//������������غ�������ǰ�������غ���    ma ?

	void GetRealFilePath(
		DWORDLONG CurrFileNumber,
		CString & RealFilePath,
		STD_DIV_MAP::iterator InputItr,size_t CountTableMap);

	bool JudgeInFileName(CString InputFileName,CString FileName);//�ж�����Ĵ�  �Ƿ��ĳ���ļ������
private:
	FILE_TABLE_MAP * FileTableMap;//����Ӳ�̵��ļ�����ӳ���
	FILE_TABLE_VEC * FileTableVec;//����Ӳ�̵ı�
	RES_TABLE m_MaxTempResTable;//������������Ӧ���м��ѯ�����

	RES_TABLE_VECTOR *m_ResTableVector;//������治�������̷���
};

