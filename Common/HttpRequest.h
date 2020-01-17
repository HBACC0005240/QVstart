#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include "Export.h"
#include <QObject>
#include <QJsonArray>
#include <QJsonObject>

class QTimer;
class QNetworkAccessManager;

class BIMCORE_EXPORT HttpRequest : public QObject
{
	enum RequestType
	{
		None,
		Get,
		Post,
		Put,
		Delete
	};
public:
	static QJsonObject Request(QJsonObject input, RequestType methodtype, QString url);

	static QJsonObject HttpGet(QString url);

	static QJsonObject HttpPost(QJsonObject input, QString url);

	static QJsonObject HttpPut(QString url)
	{
		//none
		return QJsonObject();
	}

	static QJsonObject HttpDelete(QString url)
	{
		//none
		return QJsonObject();
	}

	//strFileDir: D:/xxx/xxx/ （文件名和后缀在回复中获取）
	static QString httpDownload(QString url, QString strFileDir);

private:
	inline static void init();

private:
	static QTimer* m_pTimer;
	static QNetworkAccessManager* m_pNetManager;
};

#endif//HTTPREQUEST_H
