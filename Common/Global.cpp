#include "Global.h"

#include <QDir>
#include <QSettings>
#include <QApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>
std::shared_ptr<ITProgressBar> Global::s_pProgressBar = nullptr;
bool Global::initParams(const QApplication& app)
{
	QStringList argumentList = app.arguments();
	QMap<QString, QString> commandOptions;
	for( int i = 1; i < argumentList.count(); ++i )
	{
		QString argument = argumentList[i];
		int firstEqualIndex = argument.indexOf( "=" );
		QString optionName = argument.mid( 2, firstEqualIndex - 2 );
		QString optionValue = argument.mid( firstEqualIndex + 1 );
		commandOptions.insert( optionName, optionValue );
	}	
	return true;
}

QString Global::getResourcePath(const QString & prefix, const QString & fileName)
{
	QString path = QString(":/%1/Resource/%1/%2").arg(prefix).arg(fileName);
	return path;
}
QString Global::getResourcePath(const QString & fileName)
{
	QString path = QString(":/%1/Resource/%1").arg(fileName);
	return path;
}