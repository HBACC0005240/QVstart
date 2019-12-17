#include "StdAfx.h"
#include "ITDataBaseConnCls.h"
#include <QSqlError>
ITDBRecordSet::ITDBRecordSet()
{
	m_sqlquery = NULL;
}
ITDBRecordSet::~ITDBRecordSet()
{
	if(m_sqlquery!=NULL)
	{
		delete m_sqlquery;
		m_sqlquery=NULL;
	}
}

QString ITDBRecordSet::getStrValue(const QString &strName)
{
	if(m_sqlquery!=NULL)
	{
		int nameCol = m_sqlquery->record().indexOf(strName);
		if(nameCol!=-1)
		{			
			return m_sqlquery->value(nameCol).toString();
		}
	}
	return "";
}

int ITDBRecordSet::getIntValue(const QString &strName)
{
	if(m_sqlquery!=NULL)
	{
		int nameCol = m_sqlquery->record().indexOf(strName);
		if(nameCol!=-1)
		{
			return m_sqlquery->value(nameCol).toInt();
		}
	}
	return 0;
}

float ITDBRecordSet::getFloatValue(const QString &strName)
{
	if(m_sqlquery!=NULL)
	{
		int nameCol = m_sqlquery->record().indexOf(strName);
		if(nameCol!=-1)
		{
			return m_sqlquery->value(nameCol).toFloat();
		}
	}
	return 0;
}

QByteArray ITDBRecordSet::getByteData(const QString &strName)
{
	if(m_sqlquery!=NULL)
	{
		int nameCol = m_sqlquery->record().indexOf(strName);
		if(nameCol!=-1)
		{
			return m_sqlquery->value(nameCol).toByteArray();
		}
	}
	return 0;
}

int ITDBRecordSet::getBitValue(const QString &strName)
{
	if(m_sqlquery!=NULL)
	{
		int ret = 0;
		int nameCol = m_sqlquery->record().indexOf(strName);
		if(nameCol!=-1)
		{
			QVariant var = m_sqlquery->value(nameCol);
			QByteArray bytearray = var.toByteArray();
			char* szChar = bytearray.data();
			if(szChar)
			{
				ret = (int)((*szChar)&0x0f);
				ret = ret!=0 ? 1:0;
			}
			return ret;
		}
	}
	return 0;
}
bool ITDBRecordSet::next()
{
	return m_sqlquery->next();
}
ITDataBaseConnCls::ITDataBaseConnCls(QString strdbtype)
{
	if(strdbtype.contains("SQLServer", Qt::CaseInsensitive) || strdbtype.contains("ODBC", Qt::CaseInsensitive))
		m_db = QSqlDatabase::addDatabase("QODBC");
	else if(strdbtype.contains("Oracle", Qt::CaseInsensitive))
		m_db = QSqlDatabase::addDatabase("QOCI");
	else if(strdbtype.contains("MYSQL", Qt::CaseInsensitive))
		m_db = QSqlDatabase::addDatabase("QMYSQL");
	else if(strdbtype.contains("SQLITE", Qt::CaseInsensitive))
		m_db = QSqlDatabase::addDatabase("QSQLITE");
	else if(strdbtype.contains("m", Qt::CaseInsensitive))
		m_db = QSqlDatabase::addDatabase("QMYSQL"); 
	else if(strdbtype.contains("O", Qt::CaseInsensitive))
		m_db = QSqlDatabase::addDatabase("QOCI");	
	else if (strdbtype.contains("postgres", Qt::CaseInsensitive))
		m_db = QSqlDatabase::addDatabase("QPSQL", "postgres");
	else
		m_db = QSqlDatabase::addDatabase("QODBC");

	m_strDBType = strdbtype;
	m_pQuery = new QSqlQuery(m_db);
}

ITDataBaseConnCls::~ITDataBaseConnCls()
{
	m_db.close();
	if (m_pQuery)
	{
		delete m_pQuery;
		m_pQuery = NULL;
	}
}

bool ITDataBaseConnCls::openDataBase( const QString &strDBName,const QString& strhostname,const QString &strUser,const QString &strPwd,int nport )
{
	QString strDriver;
	if(m_strDBType.contains("SQLServer",Qt::CaseInsensitive) || m_strDBType.contains("ODBC", Qt::CaseInsensitive))
	{
		strDriver = QString("DRIVER={SQL SERVER};port=1433;SERVER=%1;DATABASE=%2").arg(strhostname).arg(strDBName);
		nport = 1433;
	}
	else if(m_strDBType.contains("Oracle", Qt::CaseInsensitive))
	{
		strDriver = strDBName;
		nport = 1521;
	}
	else if(m_strDBType.contains("MYSQL", Qt::CaseInsensitive))
	{
		strDriver = strDBName;
		nport = 3306;
	}else if(m_strDBType.contains("SQLITE", Qt::CaseInsensitive))
	{
		strDriver = strDBName;		
	}else
	{
		strDriver = QString("DRIVER={SQL SERVER};port=1433;SERVER=%1;DATABASE=%2").arg(strhostname).arg(strDBName);
		nport = 1433;
	}		
	m_strDBPwd = strPwd;
	m_strDBUser = strUser;
	m_strDBIpAddr = strhostname;

	m_db.setDatabaseName(strDriver);
	m_db.setHostName(strhostname);
	m_db.setUserName(strUser);
	m_db.setPassword(strPwd);
 	if(m_strDBType=="ORACLE")
 		m_db.setPort(nport);

	if(m_db.isOpen())
    {
        m_strLastError.clear();
		return true;
    }else
    {
        if(m_db.open() == false)
        {
            m_strLastError.clear();
			m_strLastError = m_db.lastError().text();
			qDebug()<< m_strLastError;
			return false;
        }else
        {
            return true;
        }
    }
}

ITDBRecordSet* ITDataBaseConnCls::execQuerySql(const QString &strSql)
{
	QSqlQuery *pSqlQuery = new QSqlQuery(m_db);
	if(pSqlQuery)
	{
		pSqlQuery->clear();
		if(pSqlQuery->exec(strSql))
		{
			ITDBRecordSet* recordset = new ITDBRecordSet;
			recordset->m_sqlquery = pSqlQuery;
			return recordset;
		}
		else
		{
			m_strLastError.clear();
			m_strLastError = pSqlQuery->lastError().text();
			qDebug() << m_strLastError;
		}
	}
	return NULL;
}
bool ITDataBaseConnCls::execSql( const QString &strSql )
{
	bool bSuc = false;
	m_pQuery->clear();
	if(m_pQuery->exec(strSql))
	{
		bSuc = true;
	}else
	{
		m_strLastError.clear();
		m_strLastError = m_pQuery->lastError().text();
		qDebug() << m_strLastError;
	}
	return bSuc;
}

QSqlQuery* ITDataBaseConnCls::getSqlQuery()
{
	if(m_pQuery==NULL)
		return NULL;
	m_pQuery->clear();
	return m_pQuery;
}