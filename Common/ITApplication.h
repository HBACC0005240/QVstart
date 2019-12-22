#ifndef ITAPPLICATION_H
#define ITAPPLICATION_H

#include <QApplication>
#include <QKeyEvent>

class ITApplication : public QApplication
{
	Q_OBJECT

public:
	ITApplication(int &argc, char **argv, int _internal = ApplicationFlags);
	~ITApplication(){}

	bool notify(QObject *pObj, QEvent *ev);

private:
	unsigned int getDragDirection();

private:
	int						m_iPosX;
	int						m_iPosY;
	QPoint					m_StartPt;
	int						m_iOriginWidth;
	int						m_iOriginHeight;
	unsigned int			m_uiDragSizeMode;
	bool					m_bStartDragSize;
};

#endif //ITAPPLICATION_H
