#include "stdafx.h"
#include "ITDataMgr.h"

ITDataMgr::ITDataMgr(QObject *parent)
	: QObject(parent)
{

}

ITDataMgr::~ITDataMgr()
{

}

ITDevice* ITDataMgr::newOneDevice(int nType,ITDevice* pOwer)
{
	if (pOwer == NULL || nType == 0)
		return NULL;
	ITDevice* pRet = NULL;
	{

		if (nType == DT_DIR)
		{
			pRet = new ITDir("", nType, "");
			pRet->setDeviceOwner(pOwer);		
			if (pOwer->getDevType() == DT_DIR)
			{
				((ITDir*)pOwer)->addChildDir((ITDir*)pRet);
			}
		}
		else if (nType == DT_File)
		{
			pRet = new ITFile("", nType, "");
			pRet->setDeviceOwner(pOwer);
			if (pOwer->getDevType() == DT_DIR)
			{
				((ITDir*)pOwer)->addChildFile((ITFile*)pRet);
			}
		}		
		if (pRet)
		{
			pRet->setAddStatus();
			m_pAddList.append(pRet);		
		}
		return pRet;
	}
	return pRet;
}