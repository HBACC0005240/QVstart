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
	ITDeviceList m_pFileList;	//���м��ص��ļ�ָ��
	ITDeviceList m_pAddList;	//�¼�����
};

#endif // ITDATAMGR_H
