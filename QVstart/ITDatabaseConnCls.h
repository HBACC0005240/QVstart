#ifndef MITSDATABASECONN_H
#define MITSDATABASECONN_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlRecord>

class ITDBRecordSet
{
public:
	ITDBRecordSet();
	~ITDBRecordSet();

	QString getStrValue(const QString &strName);
	int getIntValue(const QString &strName);
	float getFloatValue(const QString &strName);
	QByteArray getByteData(const QString &strName);
	int getBitValue(const QString &strName);
	bool next();
public:
	QSqlQuery* m_sqlquery;
};
class ITDataBaseConnCls: public QObject
{
	Q_OBJECT

public:
	ITDataBaseConnCls(const ITDataBaseConnCls &dataBaseConn){}

	~ITDataBaseConnCls();

	ITDataBaseConnCls(QString strdbtype);
public:                    

	bool openDataBase(const QString &strDBName,						//打开数据库
		               const QString& hostname="",
					  const QString &strUser="",
					  const QString &strPwd="",
					  int nport=0);	
	bool execSql(const QString &strSql);							//执行SQL语句

	ITDBRecordSet* execQuerySql(const QString &strSql);

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

#endif // MITSDATABASECONN_H
