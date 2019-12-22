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
	/// 是否已经有实例运行
	bool isRunning();
	void disLocalConnect();	//断开本进程的连接
public slots:
	/// 有链接时触发
	void newLocalConnection();
private:
	/// 初始化本地连接
	void initLocalConnection();
	/// 创建服务端
	void newLocalServer();
	/// 激活窗口
	void activateWindow();
	unsigned int getDragDirection();

private:
	int						m_iPosX;
	int						m_iPosY;
	QPoint					m_StartPt;
	int						m_iOriginWidth;
	int						m_iOriginHeight;
	unsigned int			m_uiDragSizeMode;
	bool					m_bStartDragSize;
	bool m_bIsRunning;				/// 是否已经有实例运行
	QLocalServer* m_pLocalServer;	/// 本地Socket Server
	QString m_strServerName;		///服务名称 
	QWidget* m_pMainWindow;//保存一个你窗体的指针
};

#endif //ITAPPLICATION_H
