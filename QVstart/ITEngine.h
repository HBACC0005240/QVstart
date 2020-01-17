#pragma once

#include <QObject>
#include "ITDatabaseConn.h"
#include <QSqlTableModel>
#include "ITObjectID.h"
typedef QList<QSqlTableModel*> QSqlTableModelList;
class ITEngine : public QObject
{
	Q_OBJECT

public:
	ITEngine();
	~ITEngine();
	static ITEngine& GetInstance(void);

	bool connectToDataBase(const QString& dbName,const QString& dbType,const QString& dbIP,\
		const QString& loginUser,const QString& logingPwd,const int port=0);
	bool loadDataBaseData();
	static ITEngine engineInstance;
	QSqlTableModel* getTable(const QString& szTableName) { return m_tableForModel.value(szTableName); }
	bool saveTableData(QSqlTableModel* pTable);
	bool saveToDataBase();
private:
	ITDataBaseConn* m_pDBConn;
	QString						m_strDBName;			//��ǰ���ݿ�����
	QString						m_strDBIp;				//��ǰ���ݿ����ӵ�ַ
	QString						m_strDBType;			//��ǰ���ݿ�����
	QString						m_strDBUser;			//��ǰ���ݿ��û���
	QString						m_strDBPwd;				//��ǰ���ݿ�����
	QSqlTableModelList			m_sqlTableModels;		//���б�ģ��
	QHash<QString, QSqlTableModel*> m_tableForModel;
};
