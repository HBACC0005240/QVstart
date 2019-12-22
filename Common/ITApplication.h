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
	/// �Ƿ��Ѿ���ʵ������
	bool isRunning();
	void disLocalConnect();	//�Ͽ������̵�����
public slots:
	/// ������ʱ����
	void newLocalConnection();
private:
	/// ��ʼ����������
	void initLocalConnection();
	/// ���������
	void newLocalServer();
	/// �����
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
	bool m_bIsRunning;				/// �Ƿ��Ѿ���ʵ������
	QLocalServer* m_pLocalServer;	/// ����Socket Server
	QString m_strServerName;		///�������� 
	QWidget* m_pMainWindow;//����һ���㴰���ָ��
};

#endif //ITAPPLICATION_H
