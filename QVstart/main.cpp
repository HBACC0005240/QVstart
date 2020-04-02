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
	stringList << QString::fromLocal8Bit("���ͼ")
		<< QString::fromLocal8Bit("΢��")
		<< QString::fromLocal8Bit("456����")
		<< QString::fromLocal8Bit("123΢��")
		<< QString::fromLocal8Bit("a����")
		<< QString::fromLocal8Bit("b�й�")
		<< QString::fromLocal8Bit("����")
		<< QString::fromLocal8Bit("����ͼ")
		<< QString::fromLocal8Bit("KL1")
		<< QString::fromLocal8Bit("KL10")
		<< QString::fromLocal8Bit("KL2")
		<< QString::fromLocal8Bit("KL3")
		<< QString::fromLocal8Bit("KL13")
		<< QString::fromLocal8Bit("KL1(2)")
		<< QString::fromLocal8Bit("KL1(1)");

	//qSort(stringList.begin(), stringList.end(), collator);//���� qt�ڲ������õĻ���Windows����API CompareString ���������򲻷���Ҫ��
	qSort(stringList.begin(), stringList.end(), customCompareString);


	QVStart w;
	//	w.resize(100,300);
	QRect deskRect = QApplication::desktop()->availableGeometry();
	w.move(deskRect.right() - 280, 30);
	w.show();
	return a.exec();
}
