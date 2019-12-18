#include "stdafx.h"
#include "ITDataMgr.h"

ITDataMgr::ITDataMgr()
{

}

ITDataMgr::~ITDataMgr()
{

}

ITDataMgr& ITDataMgr::GetInstance(void)
{
	static ITDataMgr dataBaseMgrInstance;
	return dataBaseMgrInstance;
}

void ITDataMgr::saveData()
{

}

ITData* ITDataMgr::newOneData(int nType,ITData* pOwer)
{
	if (pOwer == NULL || nType == 0)
		return NULL;
	ITData* pRet = NULL;
	{

		if (nType == DT_FileGroup)
		{
			pRet = new ITFileGroup("", nType, "");
			pRet->setDeviceOwner(pOwer);		
			if (pOwer->getDataType() == DT_FileGroup)
			{
				((ITFileGroup*)pOwer)->addChildGroup((ITFileGroup*)pRet);
			}
		}
		else if (nType == DT_File)
		{
			pRet = new ITFile("", nType, "");
			pRet->setDeviceOwner(pOwer);
			if (pOwer->getDataType() == DT_FileGroup)
			{
				((ITFileGroup*)pOwer)->addChildFile((ITFile*)pRet);
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