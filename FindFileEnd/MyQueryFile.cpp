#include "StdAfx.h"
#include "MyQueryFile.h"


CMyQueryFile::CMyQueryFile(FILE_TABLE_MAP * FileTableMap)
{
	this->FileTableMap=FileTableMap;
}

CMyQueryFile::~CMyQueryFile(void)
{
}
inline bool CMyQueryFile::JudgeInFileName(CString InputFileName,CString FileName)
{//�ҵ��ִ���˵����������Ŷ
	if (-1!=FileName.Find(InputFileName))
	{
		return true;
	}else
	{
		return false;
	}
}

void CMyQueryFile::InitQuery()
{//��ʼ���м��ѯ��
	//��ʼ�����ղ�ѯ�����
	this->m_ResTableVector=new RES_TABLE_VECTOR;
	//���������������ҲҪ�ͷŰ�
}

//��֧��inlien  ����������ö��ʱ��Ч�ʱȽϸ�
inline void CMyQueryFile::GetRealFilePath(
	DWORDLONG CurrFileNumber,
	CString & RealFilePath,
	size_t CountTableMap/*����Ǳ�ʾ��ĳ��ӳ����� Ϊʲô��ֱ�ӽ�ӳ��������أ� ����һ��*/
	)//�������Ҫ�����Ĳ������ܽ��еݹ�
{/*
 �ݹ��㷨������·��
 */
	//�ݹ��㷨���������
	/**
	�ݹ������ļ��ľ���·������·������OutRealPath
	*/
	STD_DIV_MAP::iterator ItrStart=this->FileTableMap->at(CountTableMap).m_StdDivMap->find(CurrFileNumber);
	if (ItrStart==this->FileTableMap->at(CountTableMap).m_StdDivMap->end())
	{
		return;
	}
	if (OUT_ROOT_NUMBER==ItrStart->second.ParentFileNumber)
	{
		RealFilePath=ItrStart->second.CurrFileName+RealFilePath;
		return;
	}
	RealFilePath=ItrStart->second.CurrFileName+RealFilePath;
	CurrFileNumber=ItrStart->second.ParentFileNumber;
	this->GetRealFilePath(CurrFileNumber,RealFilePath,CountTableMap);//�ݹ�õ��ļ�������·��
}

inline void CMyQueryFile::GetRealFilePath(
	DWORDLONG CurrFileNumber,
	CString & RealFilePath,
	STD_DIV_MAP::iterator InputItr,size_t CountTableMap)
{

	RealFilePath=InputItr->second.CurrFileName+RealFilePath;
	CurrFileNumber=InputItr->second.ParentFileNumber;
	this->GetRealFilePath(CurrFileNumber,RealFilePath,CountTableMap);//�ݹ�õ��ļ�������·��
}

inline void CMyQueryFile::GetRealFilePath(
	DWORDLONG CurrFileNumber, 
	CString & RealFilePath,
	size_t CountTableMap,
	STD_DIV_MAP::iterator &ItrFileInfo)
{
	STD_DIV_MAP::iterator ItrStart=this->FileTableMap->at(CountTableMap).m_StdDivMap->find(CurrFileNumber);
	ItrFileInfo=ItrStart;//����һ�β�ѯ�õ��ĵ�����ȡ����
	if (ItrStart==this->FileTableMap->at(CountTableMap).m_StdDivMap->end())
	{
		return;
	}
	if (OUT_ROOT_NUMBER==ItrStart->second.ParentFileNumber)
	{
		RealFilePath=ItrStart->second.CurrFileName+RealFilePath;
		return;
	}
	RealFilePath=ItrStart->second.CurrFileName+RealFilePath;
	CurrFileNumber=ItrStart->second.ParentFileNumber;
	this->GetRealFilePath(CurrFileNumber,RealFilePath,CountTableMap);//�ݹ�õ��ļ�������·��
}

RES_TABLE_VECTOR * CMyQueryFile::GetPointRealPathTable()
{
	return this->m_ResTableVector;
}

void CMyQueryFile::GetFileFormTableByNameEx(CString InputFileName)
{
	this->m_ResTableVector->clear();
	size_t CountDivVec=0;
	STD_DIV_MAP::iterator ItrBegin;
	CString DivName;
	CString RealFilePath;
	while (CountDivVec<(this->FileTableMap->size()))
	{
		DivName=this->FileTableMap->at(CountDivVec).DivName;
		DivName.Delete(0,4);
		DivName+=_T("\\");
		ItrBegin=this->FileTableMap->at(CountDivVec).m_StdDivMap->begin();
		while (ItrBegin!=this->FileTableMap->at(CountDivVec).m_StdDivMap->end())
		{
			if (ItrBegin->second.CurrFileName.Find(InputFileName)!=-1)
			{
				this->GetRealFilePath(ItrBegin->first,RealFilePath,ItrBegin,CountDivVec);
				RealFilePath=DivName+RealFilePath;
				REAL_RES_TABLE TempRealNode(RealFilePath,ItrBegin);
				this->m_ResTableVector->push_back(TempRealNode);
				//	MessageBox(NULL,RealFilePath,_T("�ļ�·��"),MB_OK);
				RealFilePath=_T("");//ÿ��ʹ����Ҫ����ϵõ����ļ�·��
			}
			++ItrBegin;
		}
		++CountDivVec;
	}
}
