﻿#ifndef ITDATABASECONN_H
#define ITDATABASECONN_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>

class ITRecordSet
{
public:
	ITRecordSet();
	~ITRecordSet();

	QString getStrValue(const QString &strName);
	int getIntValue(const QString &strName);
	float getFloatValue(const QString &strName);
	double getDoubleValue(const QString &strName);
	QByteArray getByteData(const QString &strName);
	int getBitValue(const QString &strName);
	bool next();
public:
	QSqlQuery* m_sqlquery;
};
class ITDataBaseConn : public QObject
{
	Q_OBJECT

public:
	ITDataBaseConn(const ITDataBaseConn &dataBaseConn){}
	~ITDataBaseConn();
	ITDataBaseConn(QString strdbtype);
 
	bool isValid() {return m_db.isValid();}
	bool openDataBase(const QString &strDBName,						//´ò¿ªÊý¾Ý¿â
		               const QString& hostname="",
					  const QString &strUser="",
					  const QString &strPwd="",
					  int nport=0);

	bool execSql(const QString &strSql);							//Ö´ÐÐSQLÓï¾ä

	ITRecordSet* execQuerySql(const QString &strSql);

	QSqlQuery* getSqlQuery();
	QString getCurrentDBType(){return m_strDBType;}
	QString getCurrentDBUser(){return m_strDBUser;}
	QString getCurrentDBPwd(){return m_strDBPwd;}
	QString getCurrentDBIpAddr(){return m_strDBIpAddr;}
    QString getLastError(){return m_strLastError;}
private:
	QSqlDatabase	m_db;
	QString			m_strDBType;	//数据库类型
	QString			m_strDBIpAddr;	//数据库地址
	QString			m_strDBUser;	//数据库用户
	QString			m_strDBPwd;		//数据库密码
	QSqlQuery*		m_pQuery;
    QString         m_strLastError; //error info
};

#endif // ITDATABASECONN_H