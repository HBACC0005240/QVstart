#include "stdafx.h"
#include "ITQueryLineEdit.h"

ITQueryLineEdit::ITQueryLineEdit( QWidget* parent )
{
	setTextMargins(0, 0, 38, 0);
//    resize(170,22);
// 	setFixedSize(170,22);

	m_pBtnQuery = new ITPushButton(this);
	m_pBtnQuery->loadPixmap(GlobalInstance->getResourcePath("QueryInEdit.png"));
    m_pBtnQuery->setToolTip(tr("Search"));
	m_pBtnClear = new ITPushButton(this);
	m_pBtnClear->loadPixmap(GlobalInstance->getResourcePath("ClearInEdit.png"));
    m_pBtnClear->setToolTip(tr("Clear"));

// 	pBtnClear->setGeometry(QRect(151, 3, 16, 16));
// 	pBtnQuery->setGeometry(QRect(132, 3, 16, 16));
    QHBoxLayout* pLayout= new QHBoxLayout(this);
    pLayout->addStretch();
    pLayout->addWidget(m_pBtnQuery);
    pLayout->addWidget(m_pBtnClear);
    pLayout->setSpacing(0);
    pLayout->setMargin(0);

	m_pBtnQuery->setCursor(Qt::PointingHandCursor);
	m_pBtnClear->setCursor(Qt::PointingHandCursor);

	QString strLineEditConnection = "QLineEdit {border: 1px solid gray; border-radius: 3px; padding:0px; background: white;  selection-background-color: darkgray;font-size:13px}";
	setStyleSheet(strLineEditConnection);
    setLayout(pLayout);
	connect(m_pBtnQuery,&QPushButton::clicked,this,&ITQueryLineEdit::onSendQuery);
	connect(m_pBtnClear,&QPushButton::clicked,this,&ITQueryLineEdit::onSendClear);
	connect(this,&QLineEdit::returnPressed,this,&ITQueryLineEdit::onSendQuery);
}

ITQueryLineEdit::~ITQueryLineEdit( void )
{

}

void ITQueryLineEdit::onSendQuery()
{
    if (this->hasFocus() == false 
        && m_pBtnClear->hasFocus()==false
        && m_pBtnQuery->hasFocus()==false)
        return;
	emit signalQuery();
}

void ITQueryLineEdit::onSendClear()
{
	QString tmp = this->text().trimmed();
	if (tmp.isEmpty())
		return;
    this->setText(QString());
	emit signalClear();  
}
