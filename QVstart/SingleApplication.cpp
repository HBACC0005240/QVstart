#include "stdafx.h"
#include "SingleApplication.h"
#include <QFileInfo>
#include <QtNetwork/QLocalSocket>
#define TIME_OUT 500  /// (ms)

SingleApplication::SingleApplication(int &argc, char **argv)
	: QApplication (argc,argv),m_pMainWidget(NULL),m_bIsRunning(false),m_pLocalServer(NULL)
{
	/// ȡӦ�ó�������ΪLocalServer������
	m_strServerName = QFileInfo(QCoreApplication::applicationFilePath()).fileName();
	initLocalConnection();
}

SingleApplication::~SingleApplication()
{

}
//************************************
//������:  isRunning
//����������Ƿ���һ��ʵ������
//��������
//����ֵ��bool
//ʱ�䣺2016/11/9 WZQ
//************************************
bool SingleApplication::isRunning()
{
	return m_bIsRunning;
}
//************************************
//������:  newLocalConnection
//������ͨ��socketͨѶʵ�ֳ��������У��������µ�����ʱ����
//��������
//����ֵ����
//ʱ�䣺2016/11/9 WZQ
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
//������:  initLocalConnection
//��������ʼ���������ӣ�������Ӳ���server���򴴽��������˳�
//��������
//����ֵ��void
//ʱ�䣺2016/11/9 WZQ
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
	/// ������Ӳ��Ϸ��������ʹ���һ��
	newLocalServer();
}
//************************************
//������:  newLocalServer
//������LocalServer
//��������
//����ֵ��void
//ʱ�䣺2016/11/9 WZQ
//************************************
void SingleApplication::newLocalServer()
{
	m_pLocalServer=new QLocalServer(this);
	connect(m_pLocalServer,SIGNAL(newConnection()),this,SLOT(newLocalConnection()));
	if(!m_pLocalServer->listen(m_strServerName))
	{
		/// ��ʱ����ʧ�ܣ������ǳ������ʱ���������̷����µģ������Ƴ�֮
		if(m_pLocalServer->serverError() == QAbstractSocket::AddressInUseError)
		{
			QLocalServer::removeServer(m_strServerName);
			m_pLocalServer->listen(m_strServerName);
		}/// end fi(m_pLocalServer->serverError() == QAbstractSocket::AddressInUseError)
	}/// end if(!m_pLocalServer->listen(m_strServerName))
}
//************************************
//������:  activateWindow
//����������������
//��������
//����ֵ��void
//ʱ�䣺2016/11/9 WZQ
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
//������:  disLocalConnect
//�������Ͽ����ط������ź�����
//��������
//����ֵ����
//ʱ�䣺2016/11/9 WZQ
//************************************
void SingleApplication::disLocalConnect()
{
	disconnect(m_pLocalServer,SIGNAL(newConnection()),this,SLOT(newLocalConnection()));
}
