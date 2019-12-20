#ifndef WZQ_GLOBAL_H
#define WZQ_GLOBAL_H

#include <QString>
#include <QMetaType>
#include <unordered_set>
#include "Singleton.h"
#include "ITProgressBar.h"

#define  GlobalInstance Global::instance()

class QApplication;

class Global : public Singleton<Global>
{
public:
	bool initParams(const QApplication& app);
	//  获取资源路径地址
	static QString getResourcePath(const QString &prefix, const QString &fileName);
	static QString getResourcePath(const QString &fileName);

	static std::shared_ptr<ITProgressBar> s_pProgressBar;
};

#endif//WZQ_GLOBAL_H
