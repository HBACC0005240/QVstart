#ifndef ITDATAMGR_H
#define ITDATAMGR_H

#include <QObject>
#include "ITObject.h"
#include "ITDatabaseConn.h"
class ITDataMgr : public QObject
{
	Q_OBJECT

public:
	ITDataMgr();
	~ITDataMgr();
	static ITDataMgr& GetInstance(void);

	void saveData();
	ITObject* newOneData(int nType, ITObject* pOwer);



	static ITDataMgr dataBaseMgrInstance;
private:
	ITObjectList m_pDataBaseList;	//所有加载的文件指针
	ITObjectList m_pAddList;	//新加数据
};

#endif // ITDATAMGR_H
