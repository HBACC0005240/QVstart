#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include "Global.h"
class ITCommonTitleWidget : public QWidget
{
	Q_OBJECT

public:
	ITCommonTitleWidget(QWidget *parent);
	ITCommonTitleWidget(QWidget *parent,const QString &closePng,const QString &logoIconName = *(QString*)NULL);
	~ITCommonTitleWidget();

	void setDlgTitle(QString strTitle);
	void setMinBtnVisible(bool bVisible);
	void setMaxBtnVisible(bool bVisible);
	void setCloseBtnVisible(bool bVisible);

	void setColor(const QColor &titleColor);

protected:
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void paintEvent(QPaintEvent *event);

signals:
	void sigDlgMinimize();
	void sigDlgMaximize();
	void sigDlgClose();

private:
	QPixmap			m_pixmapBkg;
	QString			m_strTitle;
	QLabel*			m_pLabelTitle;
	QPushButton*	m_btnMinimize;
	QPushButton*	m_btnMaximize;
	QPushButton*	m_btnClose;
	bool			m_bIsMove;
	QPoint			m_ptPress;
};

