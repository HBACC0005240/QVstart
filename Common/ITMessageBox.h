#pragma once
#include <QMessageBox>
#include "Global.h"
class ITMessageBox
{
public:

    static void showInformation(const QString &msg, QWidget* parent = NULL);
    static void showWarning(const QString &msg, QWidget* parent = NULL);
    static void showError(const QString& msg, QWidget* parent = NULL);
    static QMessageBox::StandardButton showConfirm(const QString &msg, QMessageBox::StandardButtons btns, QWidget* parent = NULL);
};




