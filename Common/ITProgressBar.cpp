#include "stdafx.h"

#include <QApplication>
#include <QDesktopWidget>
#include "ITProgressBar.h"


ITProgressBar::ITProgressBar( QWidget * parent /*= 0*/, int minRange /*= 0*/, int maxRange /*= 30*/,
							   int nWidth /*= 450*/, int nHeight /*= 30*/ )
	: QProgressBar()
	, m_nCount(0)
	, m_nMaxRange(0)
	, m_nCurrentPos(0)
{
	setAlignment(Qt::AlignVCenter);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowModality(Qt::ApplicationModal);

	setRange(0, CTotalSteps);
	setValue(0);
	setFixedSize(nWidth, nHeight);
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	raise();

	//把进度条放在屏幕中心
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect applicationRect = desktopWidget->availableGeometry(desktopWidget->screenNumber());
	int x = applicationRect.x() + applicationRect.width() / 2 - nWidth / 2;
	int y = applicationRect.y() + applicationRect.height() / 2 - nHeight / 2 + 50;
//	setGeometry(x, y, nWidth, nHeight);
	move(x, y);

	m_nOneStepValue = maxRange / CTotalSteps + 1;
	m_nCurrentStep = 0;
}

ITProgressBar::~ITProgressBar()
{

}

void ITProgressBar::showEvent(QShowEvent *e)
{
	window()->setWindowModality(Qt::ApplicationModal);
	QProgressBar::showEvent(e);
}

void ITProgressBar::hideEvent(QHideEvent *e)
{
	window()->setWindowModality(Qt::NonModal);
	QProgressBar::hideEvent(e);
}

void ITProgressBar::paintEvent(QPaintEvent * ev)
{
	//必须每次绘制都设置模态才行
	setWindowModality(Qt::ApplicationModal);

	QPainter p(this);
	p.setRenderHint(QPainter::Antialiasing);

	int _width = width();
	int _height = height();
	QRect bgRect = rect();

	QRect backRect = QRect(35, _height * 0.56, 400, 12);
	QRect textRect = backRect.adjusted(backRect.width(), -40, 60, 40);
	QRect descRect = QRect(35, _height * 0.29, 400, 24);

	QPainterPath path;
	path.addRoundRect(bgRect, 10, 10);
	p.setClipPath(path);

	const double k = (double)(value() - minimum()) / (maximum() - minimum());
	int x = (int)(backRect.width() * k);
	QRect valueRect = backRect.adjusted(0, 0, x - backRect.width(), 0);


	QString valueStr = QString("%1%").arg(QString::number(value()));

	//绘制背景
	p.setBrush(QColor("#f1f5f8"));
	p.setPen(QPen(QColor("#dbe6f4")));
	p.drawRoundedRect(bgRect, 16, 16);

	//绘制进度条 背景
	p.setBrush(QColor(230, 230, 230));
	p.setPen(QColor(230, 230, 230));
	p.drawRoundedRect(backRect, 6, 6);

	//绘制进度条 前景
	p.setBrush(QColor("#0054c2"));
	p.drawRoundedRect(valueRect, 6, 6);


	//绘制百分比文字
	QFont fontValue = QFont("Microsoft YaHei UI", 14, QFont::Bold);
	p.setFont(fontValue);
	p.setPen(QColor("#0054c2"));
	p.drawText(textRect, Qt::AlignCenter, valueStr);

	//绘制描述
	QFont font = QFont("Microsoft YaHei UI", 12);
	p.setFont(font);
	p.setPen(QColor("#626262"));
	p.drawText(descRect, Qt::AlignLeft, m_strPrompt);
}

void ITProgressBar::UpdateProgress(int APos )
{
	if (m_nMaxRange == 0)
		return;
	if (APos == m_nMaxRange)
	{
		m_nCurrentStep = CTotalSteps;
		setValue(m_nCurrentStep);
		update();
		QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
	}
	else
	{
		int iStep = APos * CTotalSteps / m_nMaxRange;
		if (iStep != m_nCurrentStep)
		{
			m_nCurrentStep = iStep;
			setValue(m_nCurrentStep);
			update();
			QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
		}
	}
	m_nCurrentPos = APos;
}

void ITProgressBar::GotoNextPos()
{
	UpdateProgress(m_nCurrentPos+1);
}

void ITProgressBar::GotoNextStep()
{
	m_nCurrentStep++;
    if(m_nCurrentStep <= CTotalSteps)
	{
		int nPos = m_nCurrentStep * m_nOneStepValue;
		setValue(nPos);
	}
}

void ITProgressBar::SetMaxRange( int maxRange)
{
	reset();
	m_nMaxRange = maxRange;
	if (maxRange == 0)
	{
		setRange(0, 0);
		reset();
		update();
		//QApplication::processEvents();
	}
	else
	{
		setMaximum(CTotalSteps);
		m_nCurrentStep = 0;
		//m_nCount = 0;
		m_nCurrentPos = 0;
		m_nOneStepValue = maxRange / CTotalSteps + 1;
	}
}

void ITProgressBar::UpdatePrompt( QString qsText )
{
    setFormat(qsText);
	update();
}

void ITProgressBar::ShowImmediately()
{
	show();
	raise();
	//repaint();
	QApplication::processEvents();
}


