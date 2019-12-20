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
	
	setRange(0, CTotalSteps);
	setFixedSize(nWidth, nHeight);
	window()->setWindowModality(Qt::WindowModal);
	setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	raise();

	//把进度条放在屏幕中心
	QDesktopWidget* desktopWidget = QApplication::desktop(); 
	QRect applicationRect = desktopWidget->availableGeometry(desktopWidget->screenNumber());
	int x = applicationRect.x() + applicationRect.width() / 2 - nWidth / 2;
	int y = applicationRect.y() + applicationRect.height() / 2 - nHeight / 2 + 50;
	setGeometry(x, y, nWidth, nHeight);

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

void ITProgressBar::UpdateProgress(int APos )
{
	if (m_nMaxRange == 0)
		return;
	if (APos == m_nMaxRange)
	{
		m_nCurrentStep = CTotalSteps;
		setValue(m_nCurrentStep);
		repaint();
		QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);
	}
	else
	{
		int iStep = APos * CTotalSteps / m_nMaxRange;
		if (iStep != m_nCurrentStep)
		{
			m_nCurrentStep = iStep;
			setValue(m_nCurrentStep);
			repaint();
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
		repaint();
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
	repaint();
}

void ITProgressBar::ShowImmediately()
{
	show();
	raise();
	//repaint();
	QApplication::processEvents();
}


