#include "stdafx.h"
#include "ITDevice.h"


ITDevice::ITDevice()
{
	m_nStatus = ITDEV_STATUS_NORMAL;
}
ITDevice::ITDevice(QString strDeviceName, int nDeviceType, QString strDeviceCode)
{
	m_nDevType = nDeviceType;
	m_strDevCode = strDeviceCode;
	m_strDevName = strDeviceName;
	m_pOwner = NULL;
	m_nStatus = ITDEV_STATUS_NORMAL;
}

ITDevice::~ITDevice()
{
}

ITDir::ITDir()
{
	
}
ITDir::ITDir(QString strName, int nDeviceType, QString strDeviceCode)
	:ITDevice(strName, nDeviceType, strDeviceCode)
{

}

ITDir::~ITDir()
{
}
bool ITDir::addChildDir(ITDir* pDir)
{
	if (!pDir)
		return false;
	for (int i = 0; i < m_pSubDirList.size(); ++i)
	{
		if (m_pSubDirList[i] == pDir)
		{
			return true;
		}
	}
	m_pSubDirList.push_back(pDir);
	return true;
}
bool ITDir::removeChildDir(ITDir* pDir)
{
	if (!pDir)
		return false;
	m_pSubDirList.removeOne(pDir);
	return true;
}
bool ITDir::addChildFile(ITFile* pFile)
{
	if (!pFile)
		return false;
	for (int i = 0; i < m_pSubFileList.size(); ++i)
	{
		if (m_pSubFileList[i] == pFile)
		{
			return true;
		}
	}
	m_pSubFileList.push_back(pFile);
	return true;
}
bool ITDir::removeChildFile(ITFile* pFile)
{
	if (!pFile)
		return false;
	m_pSubFileList.removeOne(pFile);
	return true;
}

ITFile::ITFile()
{
	m_nOrdinal = 0;
	m_nFileType = 0;
}
ITFile::ITFile(QString strName, int nDeviceType, QString strDeviceCode)
	:ITDevice(strName, nDeviceType, strDeviceCode)
{

}

ITFile::~ITFile()
{
}
