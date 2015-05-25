#ifndef QVSTART_H
#define QVSTART_H

#include <QtGui/QDialog>
#include "ui_QVstart.h"

class QVstart : public QDialog
{
	Q_OBJECT

public:
	QVstart(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QVstart();

	void initLoadUserCfg();				///��ʼ�������û�������Ϣ
	void createSysTrayAction();
protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	void closeEvent(QCloseEvent *event);
	void dragEnterEvent(QDragEnterEvent *event);  
	void dropEvent(QDropEvent *event);  
public slots:
	void doBtnClicked();
	void doIconActivated(QSystemTrayIcon::ActivationReason reason);
	void quitAndDeleteAllInfo();
	void doListWidgetItemClicked(QListWidgetItem* pItem);
private:
	Ui::QVstartClass ui;
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
