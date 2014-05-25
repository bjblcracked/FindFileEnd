#include "StdAfx.h"
#include "MyCreateTable.h"
CMyCreateTable::~CMyCreateTable(void)
{
}
CMyCreateTable::CMyCreateTable(FILE_TABLE_MAP *FileTableMap)
{
	this->FileTableMap=FileTableMap;
}

void CMyCreateTable::SelectDiv()
{
	/*
	��ѡ��NTFS��ʽ��������
	*/
	WCHAR StartDiv=START_SCANF_DIV;
	WCHAR DivFileSystem[MAX_DIV_FILE_SYSTEM_STR_LEN]={};
	short res;
	WCHAR DeviceName[4]=_T("C:\\");
	while (StartDiv<=END_SCANF_DIV)
	{
		DeviceName[0]=StartDiv;
		res=GetVolumeInformationW(DeviceName,
			NULL,
			0,
			NULL,
			NULL,
			NULL,
			DivFileSystem,
			MAX_PATH);//��ȡ������Ϣ
		if (res&&(!wcscmp(DivFileSystem,TRUE_FILE_SYSTEM)))
		{//�Ժ�Ҫ�õ���ʼ��usn��־���������ַ�����ʽ�� \\.\C:�����ĸ�ʽ
			CString StrTempDiv(StartDiv);
			this->m_DivList.push_back(_T("\\\\.\\")+StrTempDiv+=_T(":"));
		}
		++StartDiv;
	}
}

void CMyCreateTable::GetDivHandle()
{
	/*
	����������� һֱ������ʼ��USN��־�Ϳ���
	*/
	size_t count=0;
	while (count<this->m_DivList.size())
	{
		HANDLE handDevice/*����������ͷ���������*/=CreateFile(this->m_DivList[count],//����վ���Ҫ���ָ�ʽ
			GENERIC_READ|GENERIC_WRITE,
			FILE_SHARE_READ|FILE_SHARE_WRITE,
			NULL,OPEN_EXISTING,
			FILE_ATTRIBUTE_READONLY,
			NULL);
		if (INVALID_HANDLE_VALUE!=handDevice)
		{
			wcout<<"��ȡ����������ɹ�"<<endl;
		}
		//��ʼ��USN��־
		DWORD br;
		CREATE_USN_JOURNAL_DATA mycujd;
		mycujd.AllocationDelta=0;
		mycujd.MaximumSize=0;

		unsigned short int st=DeviceIoControl(handDevice,
			FSCTL_CREATE_USN_JOURNAL,
			&mycujd,
			sizeof(mycujd),
			NULL,
			0,
			&br,
			NULL);

		if (false!=st)
		{//��ʼ��USN
			DIV_HANDLE_NODE TempNode(this->m_DivList[count],handDevice);
			this->m_DivHandleTable.push_back(TempNode);
		}
		++count;
	}
	//............��ʼ����ɵ�USN����������ͷ���m_DivHandleTable��  �Թ�����ɨ���ļ�ʹ��
}

void CMyCreateTable::CreateMaxFileTable(unsigned int *progress)
{
	this->SelectDiv();
	this->GetDivHandle();
	int Tmp=100/(this->m_DivHandleTable.size());
	size_t CountDiv=0;
	while (CountDiv<(this->m_DivHandleTable.size()))
	{
		MAX_TABLE_MAP MaxTableMap;
		this->CreateMinFileTable(&(this->m_DivHandleTable)[CountDiv],MaxTableMap);
		this->FileTableMap->push_back(MaxTableMap);
		CloseHandle(m_DivHandleTable[CountDiv].m_Handle);
		(*progress)=(CountDiv+1)*Tmp;
		++CountDiv;
	}
}

inline void CMyCreateTable::CreateMinFileTable(DIV_HANDLE_NODE *DivHandleNode, MAX_TABLE_MAP &MaxTableMap)
{
	MaxTableMap.DivName=DivHandleNode->DivName;
	STD_DIV_MAP * TempFileMap=new STD_DIV_MAP;
	MaxTableMap.m_StdDivMap=TempFileMap;
	//��ʼ������
	HANDLE handDevice=DivHandleNode->m_Handle;
	unsigned short res;
	DWORD dr;
	USN_JOURNAL_DATA myujd;
	res=DeviceIoControl(handDevice,FSCTL_QUERY_USN_JOURNAL,NULL,0,&myujd,sizeof(myujd),&dr,NULL);//�������ȡUSN��־��Ϣ
	if (res)
	{
		//��Щcout���Բ�Ҫ����
		//wcout<<"USN��־��Ϣ��ȡ�ɹ�"<<endl;
	}else
	{
		//wcout<<"USN��־��ȡʧ��"<<GetLastError()<<endl;
	}
	MFT_ENUM_DATA med;//��MFT_ENUM_DATA ��ȡUSN�е��ļ���Ϣ
	med.StartFileReferenceNumber=0;
	med.LowUsn=0;
	med.HighUsn=myujd.NextUsn;

	WCHAR buffer[MAX_BUFFER_LEN];
	DWORD usnDataSize;
	PUSN_RECORD UsnRecord;//������;���USN_RECORD��ָ������

	while (DeviceIoControl(handDevice,FSCTL_ENUM_USN_DATA,&med,sizeof(med),buffer,MAX_BUFFER_LEN,&usnDataSize,NULL))
	{
		DWORD dwRetBytes=usnDataSize-sizeof(USN);
		//�ҵ���һ��USN��¼
		UsnRecord=(PUSN_RECORD)(((PCHAR)buffer)+sizeof(USN));
		while (dwRetBytes>0)
		{
			//�����ȡ������Ϣ
			const int strLen=UsnRecord->FileNameLength;
			if (UsnRecord->FileAttributes&FILE_ATTRIBUTE_DIRECTORY)//�ж��ļ�����  �����ļ��У���ô��Ҫ�ں������\\��ʾ�����ļ��У��Ժ��������ļ�·��
			{
				CString StrFileName(UsnRecord->FileName, UsnRecord->FileNameLength/2);
				TempInfoMapNode.CurrFileName=StrFileName;
				TempInfoMapNode.CurrFileName+=_T("\\");//����б�ߴ����ļ���
				TempInfoMapNode.ParentFileNumber=UsnRecord->ParentFileReferenceNumber;
				TempFileMap->insert(make_pair(UsnRecord->FileReferenceNumber,TempInfoMapNode));
				//(*TempFileMap)[UsnRecord->FileReferenceNumber]=TempInfoMapNode;
			}else
			{
				CString StrFileName(UsnRecord->FileName, UsnRecord->FileNameLength/2);
				TempInfoMapNode.CurrFileName=StrFileName;
				TempInfoMapNode.ParentFileNumber=UsnRecord->ParentFileReferenceNumber;
				TempFileMap->insert(make_pair(UsnRecord->FileReferenceNumber,TempInfoMapNode));
				//(*TempFileMap)[UsnRecord->FileReferenceNumber]=TempInfoMapNode;
			}
			DWORD recordLen=UsnRecord->RecordLength;
			dwRetBytes-=recordLen;
			UsnRecord=(PUSN_RECORD)(((PCHAR)UsnRecord)+recordLen);
		}
		med.StartFileReferenceNumber=*(USN*)&buffer;
	}
}
