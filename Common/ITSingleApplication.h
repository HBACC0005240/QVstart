#ifndef ITSINGLEAPPLICATION_H
#define ITSINGLEAPPLICATION_H

#include <QObject>
#include <QApplication>
#include <QtNetwork/QLocalServer>
#include <QWidget>

class ITSingleApplication : public QApplication 
{
	Q_OBJECT

public:
	ITSingleApplication(int &argc, char **argv);
	~ITSingleApplication();

	/// 是否已经有实例运行
	bool isRunning();
	void disLocalConnect();	//断开本进程的连接
	QWidget* m_pMainWidget;/// MainWindow指针
private slots:
	/// 有链接时触发
	void newLocalConnection();
private:
	/// 初始化本地连接
	void initLocalConnection();
	/// 创建服务端
	void newLocalServer();
	/// 激活窗口
	void activateWindow();
private:
	bool m_bIsRunning;				/// 是否已经有实例运行
	QLocalServer* m_pLocalServer;	/// 本地Socket Server
	QString m_strServerName;		///服务名称 
};

#endif // ITSINGLEAPPLICATION_H
