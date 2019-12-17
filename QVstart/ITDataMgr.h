#ifndef ITDATAMGR_H
#define ITDATAMGR_H

#include <QObject>
#include "ITDevice.h"
class ITDataMgr : public QObject
{
	Q_OBJECT

public:
	ITDataMgr(QObject *parent);
	~ITDataMgr();
	static ITDataMgr& getITDataMgrInstance(void);

	ITDevice* newOneDevice(int nType, ITDevice* pOwer);
private:
	ITDeviceList m_pFileList;	//所有加载的文件指针
	ITDeviceList m_pAddList;	//新加数据
};

#endif // ITDATAMGR_H
