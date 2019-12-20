#include "Stdafx.h"
#include "ITMessageBox.h"

void ITMessageBox::showInformation(const QString &msg, QWidget* parent)
{
	QWidget* parentWidget = parent;
	if (parentWidget == NULL)
		parentWidget = ITMessageBox_MainWindow;
	QMessageBox::information(parentWidget, QStringLiteral("��ʾ"), msg);
	QApplication::processEvents();
}

void ITMessageBox::showWarning(const QString &msg, QWidget* parent)
{
	QWidget* parentWidget = parent;
	if (parentWidget == NULL)
		parentWidget = ITMessageBox_MainWindow;
	QMessageBox::warning(parentWidget, QStringLiteral("����"), msg);
	QApplication::processEvents();
}

void ITMessageBox::showError(const QString& msg, QWidget* parent)
{
	QWidget* parentWidget = parent;
	if (parentWidget == NULL)
		parentWidget = ITMessageBox_MainWindow;
	QMessageBox::critical(parentWidget, QStringLiteral("����"), msg);
	QApplication::processEvents();
}

QMessageBox::StandardButton ITMessageBox::showConfirm(const QString &msg, QMessageBox::StandardButtons btns, QWidget* parent)
{
	QWidget* parentWidget = parent;
	if (parentWidget == NULL)
		parentWidget = ITMessageBox_MainWindow;
	QMessageBox::StandardButton enType = QMessageBox::question(parentWidget, QStringLiteral("ȷ��"), msg, btns);
	QApplication::processEvents();
	return enType;
}