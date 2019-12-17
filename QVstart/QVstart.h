#ifndef QVSTART_H
#define QVSTART_H

#include <QtWidgets/QDialog>
#include "ui_QVStart.h"
#include <string>
#define UserCfgPath "User/"
using namespace std;

class QVStart : public QDialog
{
	Q_OBJECT

public:
	QVStart(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~QVStart();

	void initLoadUserCfg();				///��ʼ�������û�������Ϣ
	void createSysTrayAction();
	bool startProcess(const QString& strFilePath, const QString& strArgs, bool isWaitFini = false);
	bool startProcess(std::string processName, bool isWaitFini=false);
	QString ReadIniValString(const QString& strSection, const QString& strKeyword, const QString& strDefault, const QString& strFileName);
protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);
	void dropEvent(QDropEvent *event);
	bool eventFilter(QObject *, QEvent *);
	public slots:
	void doBtnClicked();
	void doIconActivated(QSystemTrayIcon::ActivationReason reason);
	void quitAndDeleteAllInfo();
	void doListWidgetItemClicked(QListWidgetItem* pItem);
private:
	Ui::QVStartClass ui;
	bool		m_bmove;
	QPoint		m_pressedpoint;
	QPoint		m_windowspoint;
	QPoint		m_oldmousepoint;
	QAction*				m_pMinimizeAction;		//��С�Ű�ť
	QAction*				m_pMaximizeAction;		//��󻯰�ť
	QAction*				m_pRestoreAction;		//�ָ���ť
	QAction*				m_pQuitAction;			//�˳���ť
	QSystemTrayIcon*		m_pTrayIcon;			//ϵͳ����ͼ��
	QMenu *					m_pTrayIconMenu;		//ϵͳ���̲˵�
};

#endif // QVSTART_H
