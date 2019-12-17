#include "stdafx.h"
#include "SingleApplication.h"
#include <QFileInfo>
#include <QtNetwork/QLocalSocket>
#define TIME_OUT 500  /// (ms)

SingleApplication::SingleApplication(int &argc, char **argv)
	: QApplication (argc,argv),m_pMainWidget(NULL),m_bIsRunning(false),m_pLocalServer(NULL)
{
	/// 取应用程序名作为LocalServer的名字
	m_strServerName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
	initLocalConnection();
}

SingleApplication::~SingleApplication()
{

}
//************************************
//函数名:  isRunning
//描述：检查是否有一个实例运行
//参数：无
//返回值：bool
//时间：2016/11/9 WZQ
//************************************
bool SingleApplication::isRunning()
{
	return m_bIsRunning;
}
//************************************
//函数名:  newLocalConnection
//描述：通过socket通讯实现程序单例运行，监听到新的连接时触发
//参数：无
//返回值：无
//时间：2016/11/9 WZQ
//************************************
void SingleApplication::newLocalConnection()
{
	QLocalSocket* pSocket = m_pLocalServer->nextPendingConnection();
	if(pSocket != NULL)
	{
		pSocket->waitForReadyRead(2*TIME_OUT);
		delete pSocket;
		activateWindow();
	}/// end if(pSocket != NULL)
}
//************************************
//函数名:  initLocalConnection
//描述：初始化本地连接，如果连接不上server，则创建，否则退出
//参数：无
//返回值：void
//时间：2016/11/9 WZQ
//************************************
void SingleApplication::initLocalConnection()
{
	m_bIsRunning=false;
	QLocalSocket socket;
	socket.connectToServer(m_strServerName);
	if(socket.waitForConnected(TIME_OUT))
	{
		fprintf(stderr,"%s already running.\n",m_strServerName.toLocal8Bit().constData());
		m_bIsRunning=true;		
		return;
	}/// end if(socket.waitForConnected(TIME_OUT))
	/// 如果连接不上服务器，就创建一个
	newLocalServer();
}
//************************************
//函数名:  newLocalServer
//描述：LocalServer
//参数：无
//返回值：void
//时间：2016/11/9 WZQ
//************************************
void SingleApplication::newLocalServer()
{
	m_pLocalServer=new QLocalServer(this);
	connect(m_pLocalServer,SIGNAL(newConnection()),this,SLOT(newLocalConnection()));
	if(!m_pLocalServer->listen(m_strServerName))
	{
		/// 此时监听失败，可能是程序崩溃时，残留进程服务导致的，将其移除之
		if(m_pLocalServer->serverError() == QAbstractSocket::AddressInUseError)
		{
			QLocalServer::removeServer(m_strServerName);
			m_pLocalServer->listen(m_strServerName);
		}/// end fi(m_pLocalServer->serverError() == QAbstractSocket::AddressInUseError)
	}/// end if(!m_pLocalServer->listen(m_strServerName))
}
//************************************
//函数名:  activateWindow
//描述：激活主窗口
//参数：无
//返回值：void
//时间：2016/11/9 WZQ
//************************************
void SingleApplication::activateWindow()
{
	if(m_pMainWidget != NULL)
	{
		m_pMainWidget->activateWindow();
		m_pMainWidget->showNormal();
		m_pMainWidget->raise();
	}
}
//************************************
//函数名:  disLocalConnect
//描述：断开本地服务器信号连接
//参数：无
//返回值：无
//时间：2016/11/9 WZQ
//************************************
void SingleApplication::disLocalConnect()
{
	disconnect(m_pLocalServer,SIGNAL(newConnection()),this,SLOT(newLocalConnection()));
}
