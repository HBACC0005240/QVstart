#include "stdafx.h"
#include "QVStart.h"
#include <QtWidgets/QApplication>
#include <QString>
#include "ITSingleApplication.h"
#include <string>
#include "ITCollator.h"
#include "PublicFun.h"
using namespace std;

int main(int argc, char *argv[])
{	
	//	QApplication a(argc, argv);
	ITSingleApplication a(argc, argv);
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

	QLocale local(QLocale::English);
	ITCollator collator(local);
	QStringList stringList;
	stringList << QString::fromLocal8Bit("天地图")
		<< QString::fromLocal8Bit("微软")
		<< QString::fromLocal8Bit("456哈哈")
		<< QString::fromLocal8Bit("123微软")
		<< QString::fromLocal8Bit("a气象")
		<< QString::fromLocal8Bit("b中国")
		<< QString::fromLocal8Bit("猪猪")
		<< QString::fromLocal8Bit("地质图")
		<< QString::fromLocal8Bit("KL1")
		<< QString::fromLocal8Bit("KL10")
		<< QString::fromLocal8Bit("KL2")
		<< QString::fromLocal8Bit("KL3")
		<< QString::fromLocal8Bit("KL13")
		<< QString::fromLocal8Bit("KL1(2)")
		<< QString::fromLocal8Bit("KL1(1)");

	//qSort(stringList.begin(), stringList.end(), collator);//不行 qt内部最后调用的还是Windows自身API CompareString 现在它排序不符合要求
	qSort(stringList.begin(), stringList.end(), customCompareString);


	QVStart w;
	//	w.resize(100,300);
	QRect deskRect = QApplication::desktop()->availableGeometry();
	w.move(deskRect.right() - 280, 30);
	w.show();
	return a.exec();
}
