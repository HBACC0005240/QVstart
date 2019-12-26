#ifndef ITAPPLICATION_H
#define ITAPPLICATION_H

#include <QApplication>
#include <QKeyEvent>
#include <QtNetwork/QLocalServer>
#include <QWidget>
#include <QtNetwork/QLocalSocket>

class ITApplication : public QApplication
{
	Q_OBJECT

public:
	ITApplication(int &argc, char **argv, int _internal = ApplicationFlags);
	~ITApplication(){}

	bool notify(QObject *pObj, QEvent *ev);
	void setWindowInstance(QWidget* wnd);
	
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
	QWidget* m_pMainWindow;//保存一个你窗体的指针
};

#endif //ITAPPLICATION_H
