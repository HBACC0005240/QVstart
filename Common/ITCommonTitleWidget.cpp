#include "stdafx.h"
#include "ITCommonTitleWidget.h"


ITCommonTitleWidget::ITCommonTitleWidget(QWidget *parent)
	: QWidget(parent)
	, m_strTitle("")
{
	QHBoxLayout *pTitleLayout = new QHBoxLayout();

	m_pLabelTitle = new QLabel(this);
	m_pLabelTitle->setStyleSheet("QLabel{border: 1px;border-radius: 4px;color:black;}");
	m_pLabelTitle->setText(m_strTitle);
	pTitleLayout->addWidget(m_pLabelTitle);
	pTitleLayout->addStretch();

	m_btnMinimize = new QPushButton(this);
	m_btnMinimize->setToolTip(QStringLiteral("最小化"));
	m_btnMinimize->setIcon(QIcon(GlobalInstance->getResourcePath("DlgMin.png")));
	m_btnMinimize->setIconSize(QSize(15,15));
	m_btnMinimize->setFlat(true);
	m_btnMinimize->setVisible(false);

	m_btnMaximize = new QPushButton(this);
	m_btnMaximize->setToolTip(QStringLiteral("最大化"));
	m_btnMaximize->setIcon(QIcon(GlobalInstance->getResourcePath("DlgMax.png")));
	m_btnMaximize->setIconSize(QSize(15,15));
	m_btnMaximize->setFlat(true);
	m_btnMaximize->setVisible(false);

	m_btnClose = new QPushButton(this);
	m_btnClose->setToolTip(QStringLiteral("关闭"));
	m_btnClose->setIcon(QIcon(GlobalInstance->getResourcePath("DlgClose.png")));
	m_btnClose->setIconSize(QSize(15,15));
	m_btnClose->setFlat(true);

	pTitleLayout->addWidget(m_btnMinimize);
	pTitleLayout->addWidget(m_btnMaximize);
	pTitleLayout->addWidget(m_btnClose);

	connect(m_btnMinimize,SIGNAL(clicked()),this,SIGNAL(sigDlgMinimize()));
	connect(m_btnMaximize,SIGNAL(clicked()),this,SIGNAL(sigDlgMaximize()));
	connect(m_btnClose,SIGNAL(clicked()),this,SIGNAL(sigDlgClose()));

	setLayout(pTitleLayout);

	resize(1000,35);

	m_pixmapBkg = QPixmap(size());
	m_pixmapBkg.fill(QColor(246,246,246));
}

ITCommonTitleWidget::ITCommonTitleWidget(QWidget *parent,const QString &closePng,const QString &logoIconName)
{
	QHBoxLayout *pTitleLayout = new QHBoxLayout();
	QString dlgClosePng = closePng;
	if( dlgClosePng == "" )
		dlgClosePng = "DlgClose.png";

	if( &logoIconName != NULL )
	{
		QLabel *imgLabel = new QLabel(this);
		imgLabel->setPixmap(QPixmap(GlobalInstance->getResourcePath("DlgLogo.png")));
		pTitleLayout->addWidget(imgLabel);
	}

	m_pLabelTitle = new QLabel(this);
	m_pLabelTitle->setStyleSheet("QLabel{border: 1px;border-radius: 4px;color:black;}");
	m_pLabelTitle->setText(m_strTitle);
	pTitleLayout->addWidget(m_pLabelTitle);
	pTitleLayout->addStretch();

	m_btnMinimize = new QPushButton(this);
	m_btnMinimize->setToolTip(QStringLiteral("最小化"));
	m_btnMinimize->setIcon(QIcon(GlobalInstance->getResourcePath("DlgMin.png")));
	m_btnMinimize->setIconSize(QSize(15,15));
	m_btnMinimize->setFlat(true);
	m_btnMinimize->setVisible(false);

	m_btnMaximize = new QPushButton(this);
	m_btnMaximize->setToolTip(QStringLiteral("最大化"));
	m_btnMaximize->setIcon(QIcon(GlobalInstance->getResourcePath("DlgMax.png")));
	m_btnMaximize->setIconSize(QSize(15,15));
	m_btnMaximize->setFlat(true);
	m_btnMaximize->setVisible(false);

	m_btnClose = new QPushButton(this);
	m_btnClose->setToolTip(QStringLiteral("关闭"));
	m_btnClose->setIcon(QIcon(GlobalInstance->getResourcePath(dlgClosePng)));
	m_btnClose->setIconSize(QSize(15,15));
	m_btnClose->setFlat(true);

	pTitleLayout->addWidget(m_btnMinimize);
	pTitleLayout->addWidget(m_btnMaximize);
	pTitleLayout->addWidget(m_btnClose);

	connect(m_btnMinimize,SIGNAL(clicked()),this,SIGNAL(sigDlgMinimize()));
	connect(m_btnMaximize,SIGNAL(clicked()),this,SIGNAL(sigDlgMaximize()));
	connect(m_btnClose,SIGNAL(clicked()),this,SIGNAL(sigDlgClose()));

	setLayout(pTitleLayout);

	resize(1000,35);

	m_pixmapBkg = QPixmap(size());
	m_pixmapBkg.fill(QColor(246,246,246));
}

ITCommonTitleWidget::~ITCommonTitleWidget()
{

}

void ITCommonTitleWidget::setColor(const QColor &titleColor)
{
	m_pixmapBkg.fill(titleColor);
}

void ITCommonTitleWidget::setDlgTitle( QString strTitle )
{
	m_pLabelTitle->setText(strTitle);
}

void ITCommonTitleWidget::mousePressEvent( QMouseEvent *event )
{
	m_ptPress = event->pos();
	m_bIsMove = true;
	setCursor(Qt::SizeAllCursor);
}

void ITCommonTitleWidget::mouseMoveEvent( QMouseEvent *event )
{
	if((event->buttons() == Qt::LeftButton) && m_bIsMove)
	{
		QWidget* parent_widget = this->parentWidget();
		if (parent_widget ==NULL)
			return;
		QPoint parent_point = parent_widget->pos();
		parent_point.setX(parent_point.x() + event->x() - m_ptPress.x());
		parent_point.setY(parent_point.y() + event->y() - m_ptPress.y());
		parent_widget->move(parent_point);
	}	
}

void ITCommonTitleWidget::mouseReleaseEvent( QMouseEvent *event )
{
	if(m_bIsMove)
	{
		m_bIsMove = false;
		setCursor(Qt::ArrowCursor);
	}
}

void ITCommonTitleWidget::paintEvent( QPaintEvent *event )
{
	QPainter painter(this);
	painter.drawPixmap(rect(),m_pixmapBkg);
}

void ITCommonTitleWidget::setMinBtnVisible( bool bVisible )
{
	m_btnMinimize->setVisible(bVisible);
}

void ITCommonTitleWidget::setMaxBtnVisible( bool bVisible )
{
	m_btnMaximize->setVisible(bVisible);
}

void ITCommonTitleWidget::setCloseBtnVisible( bool bVisible )
{
	m_btnClose->setVisible(bVisible);
}
