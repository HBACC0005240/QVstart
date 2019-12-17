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

	void initLoadUserCfg();				///初始化加载用户配置信息
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
	QAction*				m_pMinimizeAction;		//最小号按钮
	QAction*				m_pMaximizeAction;		//最大化按钮
	QAction*				m_pRestoreAction;		//恢复按钮
	QAction*				m_pQuitAction;			//退出按钮
	QSystemTrayIcon*		m_pTrayIcon;			//系统托盘图标
	QMenu *					m_pTrayIconMenu;		//系统托盘菜单
};

#endif // QVSTART_H
