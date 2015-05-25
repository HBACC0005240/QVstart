#include "stdafx.h"
#include "QVstart.h"
#include <QtGui>
#include <QGridLayout>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForLocale(codec);
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);		
	QTranslator translator;
	translator.load(QString(":/MITSConTool/Resources/qt_zh_CN.qm"));	
	a.installTranslator(&translator);
	QVstart w;	
//	w.resize(100,300);
	QRect deskRect = QApplication::desktop()->availableGeometry();
	w.move(deskRect.right()-280,30);
	w.show();

	return a.exec();


}
