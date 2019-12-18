#include "stdafx.h"
#include "QVStart.h"
#include <QtWidgets/QApplication>
#include <QString>
#include "SingleApplication.h"
#include <string>
using namespace std;

int main(int argc, char *argv[])
{	
	//	QApplication a(argc, argv);
	SingleApplication a(argc, argv);
	if (a.isRunning())
		return 1;
#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
#else
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif
	QTranslator translator;
	translator.load(QString(":/QVStart/Resources/qt_zh_CN.qm"));
	a.installTranslator(&translator);
	QVStart w;
	//	w.resize(100,300);
	QRect deskRect = QApplication::desktop()->availableGeometry();
	w.move(deskRect.right() - 280, 30);
	w.show();
	return a.exec();
}
