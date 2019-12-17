#pragma once

#include "stdafx.h"
#include "GlobalDef.h"
class ITDevice;
class ITDir;
class ITFile;
typedef QList<ITDevice*> ITDeviceList;
typedef QList<ITDir*> ITDirList;
typedef QList<ITFile*> ITFileList;

//�豸״̬
enum ITDevStatus				
{
	ITDEV_STATUS_NORMAL = 0,	//����
	ITDEV_STATUS_ADD = 1,       //����
	ITDEV_STATUS_EDIT = 2,     	//�޸�
	ITDEV_STATUS_DELETE = 3,    //ɾ��
};

//����
class ITDevice
{
public:
	ITDevice();
	ITDevice(QString strDeviceName, int nDeviceType, QString strDeviceCode);
	virtual ~ITDevice();

	//����״ֵ̬
	int getStatus(void) { return m_nStatus; };
	void setAddStatus(void) { m_nStatus = ITDEV_STATUS_ADD; }
	virtual void setDelStatus(void) { m_nStatus = ITDEV_STATUS_DELETE; }
	void setEditStatus(void) { if (m_nStatus == ITDEV_STATUS_NORMAL)m_nStatus = ITDEV_STATUS_EDIT; }
	void setNomalStatus(void) { m_nStatus = ITDEV_STATUS_NORMAL; }

	void setDevType(int nType) { m_nDevType = nType; }
	int getDevType() { return m_nDevType; }

	void setDevCode(const QString& strCode) { m_strDevCode = strCode; }
	QString getDevCode() { return m_strDevCode; }

	void setDevName(const QString& strName) { m_strDevName = strName; }
	QString getDevName() { return m_strDevName; }

	void setDevDesc(const QString& strDesc) { m_strDesc = strDesc; }
	QString getDevDesc() { return m_strDesc; }

	void setDeviceOwner(ITDevice *pDevice) { m_pOwner = pDevice; }
	ITDevice* getDeviceOwner(void) { return m_pOwner; }
private:
	QString m_strDevCode;		//Ψһ����
	QString m_strDevName;		//����
	QString m_strRemark;		//��ע
	QString m_strDesc;			//����
	int m_nStatus;				//�豸�޸�״̬, ���޸�״̬���豸�в��š�������ͨ��
	ITDevice*	m_pOwner;		//���ڵ�
	int m_nDevType;				//����
};
class ITDir :public ITDevice
{
public:
	ITDir();
	ITDir(QString strName, int nDeviceType, QString strDeviceCode);
	virtual ~ITDir();

	bool addChildDir(ITDir* pDir);
	bool removeChildDir(ITDir* pDir);
	void clearAllSubDir() { m_pSubDirList.clear(); }

	bool addChildFile(ITFile* pFile);
	bool removeChildFile(ITFile* pFile);
	void clearAllSubFile() { m_pSubFileList.clear(); }
private:
	ITFileList m_pSubFileList;	//Ŀ¼���ļ��б�
	ITDirList m_pSubDirList;	//Ŀ¼�µ�Ŀ¼

};
//�ļ���
class ITFile :public ITDevice
{
public:
	ITFile();
	ITFile(QString strName, int nDeviceType, QString strDeviceCode);
	virtual ~ITFile();

	void setFileType(const int& nType) { m_nFileType = nType; }
	int getFileType() { return m_nFileType; }

	void setFileBaseDir(const QString& strDir) { m_strBaseDir = strDir; }
	QString getFileBaseDir() { return m_strBaseDir; }

	void setFilePath(const QString& strPath) { m_strFilePath = strPath; }
	QString getFilePath() { return m_strFilePath; }

	int getOrdinal(void) { return m_nOrdinal; }
	void setOrdial(int nOrdinal) { m_nOrdinal = nOrdinal; }
private:
	int m_nFileType;		//�ļ�����
	QString m_strBaseDir;	//�ļ���Ŀ¼
	QString m_strFilePath;	//�ļ�ȫ·��
	QIcon m_fileIcon;		//�ļ�ͼ��
	int m_nOrdinal;	        //��������

};