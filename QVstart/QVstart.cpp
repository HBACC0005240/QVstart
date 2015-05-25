#include "stdafx.h"
#include "QVstart.h"

QVstart::QVstart(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	ui.listWidget->setAcceptDrops(true);
	initLoadUserCfg();
	QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
	animation->setDuration(1000);
	animation->setStartValue(0);
	animation->setEndValue(1);
	animation->start();
	setWindowFlags( Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint | Qt::Popup);	
	ui.tabWidget->setTabText(0,"����");
	ui.tabWidget->setTabText(1,"����");
	createSysTrayAction();
	connect(ui.pushButton_close,SIGNAL(clicked()),this,SLOT(doBtnClicked()));
	connect(ui.pushButton_min,SIGNAL(clicked()),this,SLOT(doBtnClicked()));
	connect(ui.pushButton_max,SIGNAL(clicked()),this,SLOT(doBtnClicked()));
	connect(ui.listWidget,SIGNAL(itemClicked(QListWidgetItem* )),this,SLOT(doListWidgetItemClicked(QListWidgetItem*)));
}

QVstart::~QVstart()
{

}
//************************************
//������:  initLoadUserCfg(
//��������ʼ�������û�������Ϣ
//��������
//����ֵ����
//ʱ�䣺2015/5/6 WZQ
//************************************
void QVstart::initLoadUserCfg()
{
	QString strCfgFilePath = QApplication::applicationDirPath()+QString("/%1/user.ini").arg(UserCfgPath);
	QSettings iniFile(strCfgFilePath,QSettings::IniFormat);
	iniFile.setIniCodec(QTextCodec::codecForName("GB2312"));
	iniFile.beginGroup("QStartFiles");
	int nStartCount = iniFile.value("StartCount",0).toInt();
	for(int i=1;i<=nStartCount;++i)
	{
		QString strDirPath  = ReadIniValString("QStartFiles",QString("fileDirPath%1").arg(i),"",strCfgFilePath);
		QString strFilePath = ReadIniValString("QStartFiles",QString("filePath%1").arg(i),"",strCfgFilePath);
		QString strFileName = ReadIniValString("QStartFiles",QString("fileName%1").arg(i),"",strCfgFilePath);
	//	QString strDirPath = iniFile.value(QString("fileDirPath%1").arg(i),"").toString();
	//	QString strFilePath = iniFile.value(QString("filePath%1").arg(i),"").toString();
	//	QString strFileName = iniFile.value(QString("fileName%1").arg(i),"").toString();

		QFileInfo fileInfo(strFilePath);
		if(strFileName.isEmpty())
			strFileName = fileInfo.baseName();
		QFileIconProvider seekIcon;
		QIcon icon = seekIcon.icon(fileInfo);		
		QListWidgetItem* pItem = new QListWidgetItem(icon,strFileName);
		pItem->setData(Qt::UserRole,strFilePath);
		ui.listWidget->addItem(pItem);
	}
	iniFile.endGroup();
	
}
void QVstart::closeEvent(QCloseEvent *event)
{	
	QApplication::quit();
}
void QVstart::quitAndDeleteAllInfo()
{	
	qApp->quit();	
}

void QVstart::enterEvent(QEvent *)
{
	QRect rc;
	QRect rect;
	rect = this->geometry();
	rc.setRect(rect.x(),rect.y(),rect.width(),rect.height());
	if(rect.top()<0)
	{
		rect.setX(rc.x());
		rect.setY(0);
		move(rc.x(),-2);
	}
}

void QVstart::leaveEvent(QEvent *)
{
	QRect rc;
	QRect rect;
	rect = this->geometry();
	rc.setRect(rect.x(),rect.y(),rect.width(),rect.height());
	if(rect.top()<0)
	{
		move(rc.x(),-rc.height()+2);
	}
}

//�ޱ߿��ƶ�  ͨ��������϶�
void QVstart::mousePressEvent(QMouseEvent* event)
{
	if(event->button()==Qt::LeftButton)
	{
	//	m_pressedpoint = event->pos();
		m_bmove=true;
		m_pressedpoint = event->globalPos();	//���������λ��
		m_windowspoint = this->pos();			//������������λ��
		m_oldmousepoint = m_pressedpoint-m_windowspoint;	//�����λ�� �ڽ�����ʼ��ıȽ�
	}
}

void QVstart::mouseMoveEvent(QMouseEvent *event)
{
	if(m_bmove)
	{
		/*QPoint temppoint = event->globalPos();	//����������  ���涶������������ȫ�ֺ;ֲ������ε�
		int tempdx = temppoint.x()-m_pressedpoint.x();
		int tempdy = temppoint.y()-m_pressedpoint.y();*/
		move(event->globalPos()-m_oldmousepoint);		//move�ƶ����ǽ������� �µ����λ�ü�ȥ��ǰ����ڽ����λ�ò� ����Ҫ�ƶ���Ŀ��� �ƶ����ǽ������ʼ����
	}
}
void QVstart::mouseReleaseEvent(QMouseEvent *event)
{
	if(event->button()==Qt::LeftButton)
	{
		m_bmove=false;
	}
}

void QVstart::doBtnClicked()
{
	QObject* obj = sender();
	if(obj == ui.pushButton_close)
	{
		QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
		animation->setDuration(1000);
		animation->setStartValue(1);
		animation->setEndValue(0);
		animation->start();
		connect(animation, SIGNAL(finished()), this, SLOT(close()));
	}else if(obj == ui.pushButton_min)
	{
		hide();
	}else if(obj == ui.pushButton_max)
	{
		if(isMaximized())
			showNormal();
		else
			showMaximized();
	}
}
void QVstart::createSysTrayAction()
{
	m_pMinimizeAction = new QAction("��С��", this);		///���̲˵���
	connect(m_pMinimizeAction, SIGNAL(triggered()), this, SLOT(hide()));

	m_pMaximizeAction = new QAction("���", this);
	connect(m_pMaximizeAction, SIGNAL(triggered()), this, SLOT(showMaximized()));

	m_pRestoreAction = new QAction("�ָ�", this);
	connect(m_pRestoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

	m_pQuitAction = new QAction("�˳�", this);
	connect(m_pQuitAction, SIGNAL(triggered()), this, SLOT(quitAndDeleteAllInfo()));
	m_pTrayIconMenu = new QMenu(this);				///���̲˵�
	m_pTrayIconMenu->addAction(m_pMinimizeAction);
	m_pTrayIconMenu->addAction(m_pMaximizeAction);
	m_pTrayIconMenu->addAction(m_pRestoreAction);
	m_pTrayIconMenu->addSeparator();
	m_pTrayIconMenu->addAction(m_pQuitAction);

	m_pTrayIcon = new QSystemTrayIcon(this);			///����ͼ�� 
	connect(m_pTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
		this, SLOT(doIconActivated(QSystemTrayIcon::ActivationReason)));
	m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
	m_pTrayIcon->setToolTip("��������");
	m_pTrayIcon->setIcon(QIcon(":/QVstart/Resources/update.png"));
	m_pTrayIcon->show();
//	m_pTrayIcon->showMessage(QString("��̨���£�"), QString("���ڼ�����°汾��Ϣ�����Ժ�"));	//��ʾ�����ݣ��Զ��������ʧ

}
///��������ͼ��������ź� �ۺ���
void QVstart::doIconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason) 
	{
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:	
		showNormal();				///�ָ�
		break;
	case QSystemTrayIcon::MiddleClick:
		break;
	default:
		;
	}
}

void QVstart::doListWidgetItemClicked(QListWidgetItem* pItem)
{
	if(pItem == NULL)
		return;
	QString strFilePath = pItem->data(Qt::UserRole).toString();
	if(strFilePath.isEmpty())
		return;
	strFilePath = QDir::toNativeSeparators(strFilePath);
	QProcess* process = new QProcess();
	QStringList argument;
	argument << strFilePath;
	process->start(strFilePath,argument);
	// �ȴ���������  
	if (!process->waitForStarted())  
	{  
		QMessageBox::information(this,"����","��������ʧ�ܣ�");
		return;   
	}  	
	return;
}
void QVstart::dragEnterEvent(QDragEnterEvent *event)  
{  
	if (event->mimeData()->hasFormat("text/uri-list")) {  
		event->acceptProposedAction();  
	}  
}  

void QVstart::dropEvent(QDropEvent *event)  
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