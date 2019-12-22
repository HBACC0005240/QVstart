#include "ITApplication.h"
#include <QWidget>
#include <QDesktopServices>

#define Drag_Epsilon	3

enum DragDirection
{
	Dir_None = 0,
	Dir_Top = 0x1,
	Dir_Bottom = 0x2,
	Dir_Left = 0x4,
	Dir_Right = 0x8,
	Dir_TopLeft = Dir_Top | Dir_Left,
	Dir_TopRight = Dir_Top | Dir_Right,
	Dir_BottomLeft = Dir_Bottom | Dir_Left,
	Dir_BottomRight = Dir_Bottom | Dir_Right,
};

ITApplication::ITApplication(int &argc, char **argv, int _internal)
	: QApplication(argc,argv,_internal)
	, m_uiDragSizeMode(Dir_None)
	, m_bStartDragSize(false)
{
}

unsigned int ITApplication::getDragDirection()
{
	QWidget* activeWidget = qApp->activeWindow();
	unsigned int iFlag = Dir_None;
	
	if (activeWidget != nullptr && !activeWidget->isMaximized())
	{
		QPoint ptCursor = activeWidget->mapFromGlobal(QCursor::pos());

		int	iRightX = ptCursor.x() - activeWidget->width();
		int iBottomY = ptCursor.y() - activeWidget->height();

		if (iBottomY < Drag_Epsilon && iBottomY > -Drag_Epsilon)
		{
			iFlag |= Dir_Bottom;
		}
		else if (ptCursor.y() < Drag_Epsilon && ptCursor.y() > -Drag_Epsilon)
		{
			iFlag |= Dir_Top;
		}

		if (iRightX < Drag_Epsilon && iRightX > -Drag_Epsilon)
		{
			iFlag |= Dir_Right;
		}
		else if (ptCursor.x() < Drag_Epsilon && ptCursor.x() > -Drag_Epsilon)
		{
			iFlag |= Dir_Left;
		}

		if (activeWindow() != NULL)
		{
			switch (iFlag)
			{
			case Dir_Top:
			case Dir_Bottom:
				if (overrideCursor() == NULL)
					setOverrideCursor(Qt::SizeVerCursor);
				else
					changeOverrideCursor(Qt::SizeVerCursor);
				break;
			case Dir_Left:
			case Dir_Right:
				if (overrideCursor() == NULL)
					setOverrideCursor(Qt::SizeHorCursor);
				else
					changeOverrideCursor(Qt::SizeHorCursor);
				break;
			case Dir_TopLeft:
			case Dir_BottomRight:
				if (overrideCursor() == NULL)
					setOverrideCursor(Qt::SizeFDiagCursor);
				else
					changeOverrideCursor(Qt::SizeFDiagCursor);
				break;
			case Dir_TopRight:
			case Dir_BottomLeft:
				if (overrideCursor() == NULL)
					setOverrideCursor(Qt::SizeBDiagCursor);
				else
					changeOverrideCursor(Qt::SizeBDiagCursor);
				break;
			default:
				restoreOverrideCursor();
				break;
			}
		}
	}
	return iFlag;
}

bool ITApplication::notify(QObject *pObj, QEvent *ev)
{
	QWidget* activeWidget = qApp->activeWindow();
	if (activeWidget != NULL)
	{
		switch (ev->type())
		{
		case QEvent::MouseButtonPress:
			{
				if (!m_bStartDragSize)
				{
					if (m_uiDragSizeMode != Dir_None)
					{
						m_bStartDragSize = true;
						m_StartPt = QCursor::pos();
						QPoint ptPos = activeWidget->pos();
						m_iPosX = ptPos.x();
						m_iPosY = ptPos.y();
						m_iOriginHeight = activeWidget->height();
						m_iOriginWidth = activeWidget->width();
						return true;
					}
				}
			}
			break;
		case QEvent::MouseButtonRelease:
			{
				if (m_bStartDragSize)
				{
					m_bStartDragSize = false;
					return true;
				}
			}
			break;
		case QEvent::MouseMove:
			{
				if (m_bStartDragSize)
				{
					QPoint endPt = QCursor::pos();
					int iWidth = m_iOriginWidth,iHeight = m_iOriginHeight;
					int iPosX = m_iPosX,iPosY = m_iPosY;
					if (m_uiDragSizeMode & Dir_Top)
					{
						iHeight -= (endPt.y() - m_StartPt.y());
						if (iHeight >= activeWidget->minimumHeight())
							iPosY += (endPt.y() - m_StartPt.y());
					}
					else if (m_uiDragSizeMode & Dir_Bottom)
						iHeight += (endPt.y() - m_StartPt.y());
						
					if (m_uiDragSizeMode & Dir_Left)
					{
						iWidth -= (endPt.x() - m_StartPt.x());
						if (iWidth >= activeWidget->minimumWidth())
							iPosX += (endPt.x() - m_StartPt.x());
					}
					else if (m_uiDragSizeMode & Dir_Right)
						iWidth += (endPt.x() - m_StartPt.x());

					activeWidget->setGeometry(iPosX,iPosY,iWidth,iHeight);
					return true;
				}
				else
				{
					m_uiDragSizeMode = getDragDirection();
				}
			}
			break;
		case QEvent::MouseButtonDblClick:
			{
				m_uiDragSizeMode = Dir_None;
				restoreOverrideCursor();
			}			
			break;
		default:
			break;
		}
	}	
	bool result = QApplication::notify(pObj, ev);
	return result;
}