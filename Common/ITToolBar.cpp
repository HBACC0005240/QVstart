#include "stdafx.h"
#include "ITToolBar.h"

ITToolBar::ITToolBar(QWidget *parent)
	: QToolBar(parent)
{
// 	QString sTbStyle = QString("QToolBar{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff,stop: 1.0 #cccccc);\
// 							   border: 3px;spacing: 0px;}\
// 							   QToolBar QToolButton{border: none;margin:0px;padding:0px;}\
// 							   QToolBar QToolButton:hover{background-color: rgb(215,221,255); border: none;}");
	//QToolBar QToolButton{border: none;margin:0px;padding:0px;}

	//QString sTbStyle = QString("QToolBar{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff,stop: 1.0 #cccccc);\
	//						   border: 3px;spacing: 3px;}");
	QString sTbStyle = QString("QToolBar{background-color:#e7e7e7;border: 3px;border-bottom-color:#c7c7c7;}");//spacing: 0px;
	setStyleSheet(sTbStyle);

	setAutoFillBackground(true);
	setContextMenuPolicy(Qt::NoContextMenu);
	setIconSize(QSize(32,32));
	setAutoFillBackground(true);
	setBaseSize(QSize(42,21));
}

ITToolBar::ITToolBar( const QString &title, QWidget *parent /*= 0*/ )
{
	//QString sTbStyle = QString("QToolBar{background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #ffffff,stop: 1.0 #cccccc);\
// 								border: 3px;spacing: 3px;}");
	QString sTbStyle = QString("QToolBar{background-color:#e7e7e7;border: 3px;border-bottom-color:#c7c7c7;}");//spacing: 0px;
	setStyleSheet(sTbStyle);

	setAutoFillBackground(true);

	setWindowTitle(title);
	setContextMenuPolicy(Qt::NoContextMenu);
}

ITToolBar::~ITToolBar()
{

}

ITToolButton::ITToolButton(const QString &title,const QString &Icon, QWidget *parent)
	: QToolButton(parent)
{
	setText(title);
	QFont font = this->font();
	m_fmTitle = new QFontMetrics(font);
	int nWidth = m_fmTitle->width(title);
	setFixedWidth(nWidth+40);
	setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
	setPopupMode(QToolButton::InstantPopup);
	setIcon(QIcon(Icon));
}
ITToolButton::~ITToolButton()
{
	if(m_fmTitle)
	{
		delete m_fmTitle;
		m_fmTitle = 0;
	}
}