#pragma once

#include "stdafx.h"
#include "GlobalDef.h"
class ITDevice;
class ITDir;
class ITFile;
typedef QList<ITDevice*> ITDeviceList;
typedef QList<ITDir*> ITDirList;
typedef QList<ITFile*> ITFileList;

//设备状态
enum ITDevStatus				
{
	ITDEV_STATUS_NORMAL = 0,	//正常
	ITDEV_STATUS_ADD = 1,       //增加
	ITDEV_STATUS_EDIT = 2,     	//修改
	ITDEV_STATUS_DELETE = 3,    //删除
};

//基类
class ITDevice
{
public:
	ITDevice();
	ITDevice(QString strDeviceName, int nDeviceType, QString strDeviceCode);
	virtual ~ITDevice();

	//设置状态值
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
	QString m_strDevCode;		//唯一编码
	QString m_strDevName;		//名称
	QString m_strRemark;		//备注
	QString m_strDesc;			//描述
	int m_nStatus;				//设备修改状态, 有修改状态的设备有部门、主机和通道
	ITDevice*	m_pOwner;		//父节点
	int m_nDevType;				//类型
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
	ITFileList m_pSubFileList;	//目录下文件列表
	ITDirList m_pSubDirList;	//目录下的目录

};
//文件类
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
	int m_nFileType;		//文件类型
	QString m_strBaseDir;	//文件主目录
	QString m_strFilePath;	//文件全路径
	QIcon m_fileIcon;		//文件图标
	int m_nOrdinal;	        //用于排序

};