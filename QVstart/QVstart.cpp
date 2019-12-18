#include "stdafx.h"
#include "QVStart.h"
#include "PublicFun.h"
#include "ITDataMgr.h"

QVStart::QVStart(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	/*setAttribute(Qt::WA_TranslucentBackground, true);
	setWindowOpacity(0.5);*/
	this->setAcceptDrops(true);
	ui.listWidget->installEventFilter(this);
	ui.listWidget->setViewMode(QListView::IconMode);
	ui.listWidget->setAcceptDrops(true);
	ui.listWidget->setDragDropMode(QAbstractItemView::DragDrop);
	ui.listWidget->setDragEnabled(true);
	ui.listWidget->setDropIndicatorShown(true);
	initLoadUserCfg();
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(1000);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->start();
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | Qt::Popup);
	ui.tabWidget->setTabText(0, "分类");
	ui.tabWidget->setTabText(1, "备用");
	createSysTrayAction();
	ui.pushButton_close->setToolTip("关闭");
	ui.pushButton_min->setToolTip("最小化");
	ui.pushButton_max->setToolTip("最大化");
	connect(ui.pushButton_close, SIGNAL(clicked()), this, SLOT(doBtnClicked()));
	connect(ui.pushButton_min, SIGNAL(clicked()), this, SLOT(doBtnClicked()));
	connect(ui.pushButton_max, SIGNAL(clicked()), this, SLOT(doBtnClicked()));
	connect(ui.listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(doListWidgetItemClicked(QListWidgetItem*)));
}

QVStart::~QVStart()
{
	ITDataMgr::GetInstance().saveData();
}

QString QVStart::ReadIniValString(const QString& strSection, const QString& strKeyword, const QString& strDefault, const QString& strFileName)
{
	TCHAR Buffer[2048];
	GetPrivateProfileString(strSection.toStdWString().c_str(), strKeyword.toStdWString().c_str(), \
			strDefault.toStdWString().c_str(), Buffer, sizeof(Buffer), strFileName.toStdWString().c_str());
	return QString::fromStdWString(Buffer);
}
//************************************
//函数名:  initLoadUserCfg(
//描述：初始化加载用户配置信息
//参数：无
//返回值：无
//时间：2015/5/6 WZQ
//************************************
void QVStart::initLoadUserCfg()
{
	QString strCfgFilePath = QApplication::applicationDirPath() + QString("/%1/user.ini").arg(UserCfgPath);
	QSettings iniFile(strCfgFilePath, QSettings::IniFormat);
	iniFile.setIniCodec(QTextCodec::codecForName("GB2312"));
	iniFile.beginGroup("QStartFiles");
	int nStartCount = iniFile.value("StartCount", 0).toInt();
	for (int i = 1; i <= nStartCount; ++i)
	{
		QString strDirPath = ReadIniValString("QStartFiles", QString("fileDirPath%1").arg(i), "", strCfgFilePath);
		QString strFilePath = ReadIniValString("QStartFiles", QString("filePath%1").arg(i), "", strCfgFilePath);
		QString strFileName = ReadIniValString("QStartFiles", QString("fileName%1").arg(i), "", strCfgFilePath);
		//	QString strDirPath = iniFile.value(QString("fileDirPath%1").arg(i),"").toString();
		//	QString strFilePath = iniFile.value(QString("filePath%1").arg(i),"").toString();
		//	QString strFileName = iniFile.value(QString("fileName%1").arg(i),"").toString();

		QFileInfo fileInfo(strFilePath);
		if (strFileName.isEmpty())
			strFileName = fileInfo.baseName();
		QFileIconProvider seekIcon;
		QIcon icon = seekIcon.icon(fileInfo);
		QListWidgetItem* pItem = new QListWidgetItem(icon, strFileName);
		pItem->setData(Qt::UserRole, strFilePath);
		ui.listWidget->addItem(pItem);
	}
	iniFile.endGroup();

}
void QVStart::closeEvent(QCloseEvent *event)
{
	QApplication::quit();
}
void QVStart::quitAndDeleteAllInfo()
{
	qApp->quit();
}

void QVStart::enterEvent(QEvent *)
{
	QRect rc;
	QRect rect;
	rect = this->geometry();
	rc.setRect(rect.x(), rect.y(), rect.width(), rect.height());
	if (rect.top()<0)
	{
		rect.setX(rc.x());
		rect.setY(0);
		move(rc.x(), -2);
	}
}

void QVStart::leaveEvent(QEvent *)
{
	QRect rc;
	QRect rect;
	rect = this->geometry();
	rc.setRect(rect.x(), rect.y(), rect.width(), rect.height());
	if (rect.top()<0)
	{
		move(rc.x(), -rc.height() + 2);
	}
}

//无边框移动  通过鼠标点击拖动
void QVStart::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		//	m_pressedpoint = event->pos();
		m_bmove = true;
		m_pressedpoint = event->globalPos();	//鼠标点击桌面位置
		m_windowspoint = this->pos();			//界面所在桌面位置
		m_oldmousepoint = m_pressedpoint - m_windowspoint;	//鼠标点击位置 在界面起始点的比较
	}
}

void QVStart::mouseMoveEvent(QMouseEvent *event)
{
	if (m_bmove)
	{
		/*QPoint temppoint = event->globalPos();	//用这个坐标点  界面抖动很厉害，在全局和局部坐标点晃荡
		int tempdx = temppoint.x()-m_pressedpoint.x();
		int tempdy = temppoint.y()-m_pressedpoint.y();*/
		move(event->globalPos() - m_oldmousepoint);		//move移动的是界面坐标 新的鼠标位置减去以前鼠标在界面的位置差 就是要移动的目标点 移动的是界面的起始坐标
	}
}
void QVStart::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		m_bmove = false;
	}
}

void QVStart::doBtnClicked()
{
	QObject* obj = sender();
	if (obj == ui.pushButton_close)
	{
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(1000);
		animation->setStartValue(1);
		animation->setEndValue(0);
		animation->start();
		connect(animation, SIGNAL(finished()), this, SLOT(close()));
	}
	else if (obj == ui.pushButton_min)
	{
		hide();
	}
	else if (obj == ui.pushButton_max)
	{
		if (isMaximized())
			showNormal();
		else
			showMaximized();
	}
}
void QVStart::createSysTrayAction()
{
	m_pMinimizeAction = new QAction("最小化", this);		///托盘菜单项
	connect(m_pMinimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

	m_pMaximizeAction = new QAction("最大化", this);
	connect(m_pMaximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

	m_pRestoreAction = new QAction("恢复", this);
	connect(m_pRestoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

	m_pQuitAction = new QAction("退出", this);
	connect(m_pQuitAction, SIGNAL(triggered()), this, SLOT(quitAndDeleteAllInfo()));
	m_pTrayIconMenu = new QMenu(this);				///托盘菜单
	m_pTrayIconMenu->addAction(m_pMinimizeAction);
	m_pTrayIconMenu->addAction(m_pMaximizeAction);
	m_pTrayIconMenu->addAction(m_pRestoreAction);
	m_pTrayIconMenu->addSeparator();
	m_pTrayIconMenu->addAction(m_pQuitAction);

	m_pTrayIcon = new QSystemTrayIcon(this);			///托盘图标 
	connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(doIconActivated(QSystemTrayIcon::ActivationReason)));
	m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
	m_pTrayIcon->setToolTip("音速启动");
	m_pTrayIcon->setIcon(QIcon(":/QVStart/Resources/update.png"));
	m_pTrayIcon->show();
	//	m_pTrayIcon->showMessage(QString("后台更新："), QString("正在检查最新版本信息，请稍后！"));	//显示的数据，自动几秒后消失

}
///处理托盘图标点击后的信号 槽函数
void QVStart::doIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		showNormal();				///恢复
		break;
	case QSystemTrayIcon::MiddleClick:
		break;
	default:
		;
	}
}

void QVStart::doListWidgetItemClicked(QListWidgetItem* pItem)
{
	if (pItem == NULL)
		return;
	QString strFilePath = pItem->data(Qt::UserRole).toString();
	if (strFilePath.isEmpty())
		return;
	strFilePath = QDir::toNativeSeparators(strFilePath);
	QFileInfo fileInfo(strFilePath);
	if (fileInfo.isSymLink())
	{
		strFilePath = fileInfo.symLinkTarget();
	}
	startProcess(strFilePath,"",false);
	//QProcess* process = new QProcess();
	//QStringList argument;
	//argument << strFilePath;
	//process->start(strFilePath, argument);
	//// 等待进程启动  
	//if (!process->waitForStarted())
	//{
	//	QMessageBox::information(this, "错误：", "启动程序失败！");
	//	return;
	//}
	return;
}
void QVStart::dragEnterEvent(QDragEnterEvent *event)
{
	if (event->mimeData()->hasFormat("text/uri-list")) {
		event->acceptProposedAction();
	}
}

void QVStart::dropEvent(QDropEvent *event)
{
	QList<QUrl> urls = event->mimeData()->urls();
	if (urls.isEmpty()) {
		return;
	}

	QString fileName = urls.first().toLocalFile();
	if (fileName.isEmpty()) {
		return;
	}

	/*if (readFile(fileName)) {
	setWindowTitle(tr("%1 - %2").arg(fileName, tr("Drag File")));
	}  */
}
bool QVStart::eventFilter(QObject *obj, QEvent *event)
{
	if (obj == ui.listWidget)
	{
		if (event->type() == QEvent::DragEnter)
		{
			QDropEvent* dropEvent = (QDropEvent*)event;
			if (dropEvent->mimeData()->hasFormat("text/uri-list"))
			{
				dropEvent->acceptProposedAction();
			}
			else
				dropEvent->ignore();
		}
		else if (event->type() == QEvent::DragMove)
		{
			QDropEvent* dropEvent = (QDropEvent*)event;
			if (dropEvent->mimeData()->hasFormat("text/uri-list"))
			{
				dropEvent->setDropAction(Qt::MoveAction);
				dropEvent->accept();
			}
			else
				dropEvent->ignore();
		}
		else if (event->type() == QEvent::Drop)
		{
			QDropEvent* dropEvent = (QDropEvent*)event;
			QList<QUrl> urls = dropEvent->mimeData()->urls();
			if (urls.isEmpty())
			{
				return QDialog::eventFilter(obj, event);
			}

			QString strFilePath = urls.first().toLocalFile();
			if (strFilePath.isEmpty())
			{
				return QDialog::eventFilter(obj, event);
			}
			QString strFileName;
			QFileInfo fileInfo(strFilePath);
			if (strFileName.isEmpty())
				strFileName = fileInfo.baseName();
			if (fileInfo.isSymLink())
			{
				strFilePath = fileInfo.symLinkTarget();
				fileInfo.setFile(strFilePath);
			}
			QFileIconProvider seekIcon;
			QIcon icon = seekIcon.icon(fileInfo);
			QListWidgetItem* pItem = new QListWidgetItem(icon, strFileName);
			pItem->setData(Qt::UserRole, strFilePath);
			ui.listWidget->addItem(pItem);

		}else
			return QDialog::eventFilter(obj, event);
		return true;
	}
	else
		return QDialog::eventFilter(obj, event);
}

bool QVStart::startProcess(const QString& strFilePath, const QString& strArgs, bool isWaitFini)
{
	SHELLEXECUTEINFO sei;
	::ZeroMemory(&sei, sizeof(SHELLEXECUTEINFO));
	sei.cbSize = sizeof(SHELLEXECUTEINFO);
	sei.lpFile = (LPCWSTR)strFilePath.toStdWString().c_str();
	sei.nShow = SW_SHOWDEFAULT;
	sei.fMask = SEE_MASK_NOCLOSEPROCESS;//SEE_MASK_FLAG_NO_UI;	// We display our own dialog box on error
	sei.lpParameters = (LPCWSTR)strArgs.toStdWString().c_str();
	bool bRet = ::ShellExecuteEx(&sei);
	if (bRet)
	{
		if (isWaitFini)
		{
			WaitForSingleObject(sei.hProcess, INFINITE);
			return true;
		}
	}
	return false;
}
bool QVStart::startProcess(std::string processName, bool isWaitFini)
{
	STARTUPINFO StartInfo;
	PROCESS_INFORMATION pinfo;
	//对程序的启动信息不作任何设定，全部清0 
	memset(&StartInfo, 0, sizeof(STARTUPINFO));
	StartInfo.cb = sizeof(STARTUPINFO);//设定结构的大小 
	StartInfo.wShowWindow = SW_SHOW;
	StartInfo.dwFlags = STARTF_USESHOWWINDOW;

	bool bRet = CreateProcess(
		NULL, //启动程序路径名  
		(LPWSTR)(processName.c_str()), //参数（当exeName为NULL时，可将命令放入参数前） 
		NULL, //使用默认进程安全属性 
		NULL, //使用默认线程安全属性 
		false,//句柄不继承 
		NORMAL_PRIORITY_CLASS,//使用正常优先级 
		NULL, //使用父进程的环境变量 
		NULL, //指定工作目录 
		&StartInfo, //子进程主窗口如何显示 
		&pinfo); //用于存放新进程的返回信息 
	int nEro = GetLastError();
	if (bRet)
	{
		if (isWaitFini)
		{
			WaitForSingleObject(pinfo.hProcess, INFINITE);
			CloseHandle(pinfo.hThread);
			CloseHandle(pinfo.hProcess);
			return true;
		}
	}
	return false;
}
