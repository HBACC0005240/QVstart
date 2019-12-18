#ifndef ITDATAMGR_H
#define ITDATAMGR_H

#include <QObject>
#include "ITData.h"
class ITDataMgr : public QObject
{
	Q_OBJECT

public:
	ITDataMgr();
	~ITDataMgr();
	static ITDataMgr& GetInstance(void);

	void saveData();
	ITData* newOneData(int nType, ITData* pOwer);



	static ITDataMgr dataBaseMgrInstance;
private:
	ITDataList m_pDataBaseList;	//所有加载的文件指针
	ITDataList m_pAddList;	//新加数据
};

#endif // ITDATAMGR_H
