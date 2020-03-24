#include "stdafx.h"
#include "ITUtil.h"
#include <QApplication>
#include <QFileDialog>
#include <functional>
#include "ITFileUtils.h"
ITExcuteExeThread::ITExcuteExeThread(QObject *parent, QString sExePath,QStringList sListParameter )
	:QThread(parent)
	,m_sExePath(sExePath)
	,m_sListParameter(sListParameter)
{
}

ITExcuteExeThread::~ITExcuteExeThread()
{
}

void ITExcuteExeThread::startThead()
{
	start(NormalPriority);
}

void ITExcuteExeThread::run()
{
	m_curProcess = new QProcess(this);
	m_curProcess->start(m_sExePath, m_sListParameter);
}

void ITExcuteExeThread::stopThead()
{
	m_curProcess->kill();
	exit();
}
////////////////////
bool ITUtil::writeInit(QString path, QString user_key, QString user_value)
{
	if(path.isEmpty() || user_key.isEmpty())
	{
		return false;
	}
	else
	{
		//创建配置文件操作对象
		QSettings *config = new QSettings(path, QSettings::IniFormat);

		//将信息写入配置文件
		config->beginGroup("config");
		config->setValue(user_key, user_value);
		config->endGroup();
		delete config;
		return true;
	} 
}

bool ITUtil::readInit(QString path, QString user_key, QString &user_value)
{
	user_value = QString("");
	if(path.isEmpty() || user_key.isEmpty())
	{
		return false;
	}
	else
	{
		//创建配置文件操作对象
		QSettings config(path, QSettings::IniFormat);

		//读取用户配置信息
		user_value = config.value(QString("config/") + user_key).toString();

		return true;
	}  
}

void ITUtil::SetAppPanSignFile(QString strFileName)
{
	s_strAppPanSign = strFileName;
}


QString ITUtil::GetAppPanSignFile()
{
	return s_strAppPanSign;
}

QString ITUtil::getTemplateRootPath()
{
	return QApplication::applicationDirPath() + "\\Template";
}

QString ITUtil::getTemplatePacketRootPath(const QString& sPath)
{
	return QApplication::applicationDirPath() + "\\TemplatePackets\\" + sPath;
}

QString ITUtil::getTemplateFilePath(QString filename)
{
	return getTemplateRootPath() + '\\' + filename;
}

QString ITUtil::getGSPTemplateFilePath()
{
	return getTemplateFilePath("GBMProjectTemplate.GSP");
}

QString ITUtil::getProjectsRootPath()
{
	return QApplication::applicationDirPath() + "\\Projects";
}  

QString ITUtil::getProjectRootPath(QString projectPath, bool isCooperate)
{
// 	QString sUserProjectPath = projectPath;
// 	if(isCooperate)
// 	{
// 		//项目数据的获取与当前登录的账号挂钩
// 		QString sLogUserID = GBMCloudLoginService::GetInstance()->getUserID();
// 		sUserProjectPath = sUserProjectPath+"\\"+sLogUserID;
//         QDir dir(sUserProjectPath);
//         if (!dir.exists())
//         {
//             dir.mkdir(sUserProjectPath);
//         }
// 	}
// 	
// 	return  sUserProjectPath+"\\files";
    return "";
}

QString ITUtil::getProjectRootPath(QString projectPath)
{
// 	bool bIsCooperate = true;
// #ifdef NOAPPINFO
// #else
// 	bIsCooperate = appcontext()->isCooperateProject();
// #endif // NOAPPINFO
// 	return getProjectRootPath(projectPath, bIsCooperate);
    return "";
}

QString ITUtil::getProjectGSPFilePath(QString projectPath)
{
	return ITUtil::getProjectRootPath(projectPath) + "\\GBMProjectTemplate.GSP";
}

QString ITUtil::getProjectSqlliteFilePath(QString projectPath)
{
	return ITUtil::getProjectRootPath(projectPath) + "\\GBMEdoDetailInfo.db";
}

QString ITUtil::getProjectFileRootPath(QString projectPath)
{
	QString dir = ITUtil::getProjectRootPath(projectPath) + "\\File";
	if(!directoryExists(dir))
		forceDirectories(dir);
	return dir;
}

QString ITUtil::getProjectFilePath(QString projectPath, UINT64 fileID)
{
	return getProjectFileRootPath(projectPath) + "\\" + QString::number(fileID);
}
QString ITUtil::getProjectGeoRootPath(QString projectPath)
{
	return getProjectRootPath(projectPath) + "\\geo";
}
QString ITUtil::getProjectOtherGeoRootPath(QString projectPath)
{
	QString path = getProjectRootPath(projectPath) + "\\OtherGeo";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}
QString ITUtil::getProjectOtherModelRootPath(QString projectPath)
{
	QString path = getProjectRootPath(projectPath) + "\\OtherModel";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}

QString ITUtil::getProjectScreenShotRootPath(QString projectPath)
{
	QString path = getProjectRootPath(projectPath) + "\\ScreenShot";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}

QString ITUtil::getProjectCadRootPath(QString projectPath)
{
  QString path = getProjectRootPath(projectPath) + "\\cad";
  QDir dir(path);
  if (!dir.exists())
    dir.mkpath(path);
  return path;
}

QString ITUtil::getProjectCadModelRootDir(QString projectPath)
{
	QString path = getProjectRootPath(projectPath) + "\\cad\\General";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}

QString ITUtil::getProjectMPPRootPath(QString projectPath)
{
	QString path = getProjectRootPath(projectPath) + "\\SchedulePlanFile";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}

QString ITUtil::getProjectSyncFilesRootPath( QString projectPath )
{
    QString path = getProjectRootPath(projectPath) + "\\SyncFiles";
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);
    return path;
}

//获取特定工程项目排砖文件夹路径
QString ITUtil::getProjectLayBrickDir(QString projectPath)
{
	return getProjectRootPath(projectPath) + "\\LayBrick\\";
}

QString ITUtil::getProjectSyncChangeCachePath( QString projectPath )
{
	QString path = getProjectSyncFilesRootPath(projectPath) + "\\ChangeCache.gsp";
	return path;
}

QString ITUtil::getProjectCacheLogPath( QString projectPath )
{
    QString path = getProjectSyncFilesRootPath(projectPath) + "\\cacheLog";
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);
    return path;
}

QString ITUtil::getProjectLogBackupPath( QString projectPath )
{
	QString path = getProjectSyncFilesRootPath(projectPath) + "\\logback";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}

QString ITUtil::getProjectCachePacketDataRootPath(QString projectPath)
{
	QString path = getProjectSyncFilesRootPath(projectPath) + "\\CachePacketData";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}

QString ITUtil::getProjectTempPacketRootPath(QString projectPath)
{
	QString path = getProjectSyncFilesRootPath(projectPath) + "\\TempPackets";
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}

QString ITUtil::getProjectConstPath(QString projectPath)
{
    QString path = getProjectRootPath(projectPath) + "\\ConsultFiles";
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);
    return path;
}

QString ITUtil::getProjectConstCloudPath(QString projectPath)
{
    QString path = getProjectConstPath(projectPath) + "\\CloudAttach";
    QDir dir(path);
    if (!dir.exists())
        dir.mkpath(path);
    return path;
}

QString ITUtil::getProjectLBfilePath(QString projectPath)
{
	QString path = getProjectRootPath(projectPath);
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);

	return path;
}

QString ITUtil::getStatAuditFileRootPath(QString projectPath, UINT64 uStatID)
{
	QString path = getProjectRootPath(projectPath) + QString("\\Data\\StatAudit\\%0").arg(uStatID);
	QDir dir(path);
	if (!dir.exists())
		dir.mkpath(path);
	return path;
}
QString ITUtil::getSpecialQueryCfg(QString projectPath)
{
  QString fn = getProjectRootPath(projectPath) + "\\SpecialQuery.txt";
  return fn;  
}
QString ITUtil::getProjectIGMSRootPath(QString projectPath,UINT64 revID)
{
	return getProjectRootPath(projectPath) + "\\IGMS\\" + QString::number(revID);
}

QString ITUtil::getAppTempRootPath()
{
	return QApplication::applicationDirPath() + "\\temp";	
}

 QString ITUtil::getQ4CalculatorPath()
 {
	 return QApplication::applicationDirPath() + "\\Q4Calculator\\Q4Calculator.exe"; 
 }

 QString ITUtil::getQ4CalcDataPath(QString projectPath)
 {
	 return getProjectRootPath(projectPath) + "\\Q4CalcData.GSP";
 }
QString ITUtil::getAppPanSymbolPath()
{
	return ITUtil::getTemplateRootPath() + "\\pansymbol"; 
}

QString ITUtil::getTemplateMoviePath()
{
	return QApplication::applicationDirPath() + "\\TemplateMovie"; 
}



QString ITUtil::getCloudExceptionPath(QString& sFileName)
{
	QString sDir = QApplication::applicationDirPath() + "\\Error\\Cloud\\LogFile";

	QDir dir(sDir);
	if (!dir.exists())
		dir.mkpath(sDir);

	return sDir+"\\"+sFileName; 
}
QString ITUtil::getGeoFileName(UINT64 lID)
{
	return QString("%1.geo").arg(lID);
}

QString ITUtil::getToolbarIconPath(QString iconName)
{
	return ":/ToolButton/Img/Icons/" + iconName;
}

QString ITUtil::getIconsPath(const QString& iconName)
{
	return ":/ToolButtonIcon/Res/ToolButtonIcon/" + iconName;
}

QString ITUtil::getReportIconsPath(const QString& iconName)
{
    return ":/ReportIcon/Resources/ReportIcon/" + iconName;
}

QString ITUtil::getLayBrickIconsPath(const QString& iconName)
{
	return ":/LayBrick/Resources/LayBrick/" + iconName;
}

QString ITUtil::getTreeWidgetIconPath(const QString& iconName)
{
	return ":/Icon/Resources/TreeWidget/" + iconName;
}

QString ITUtil::getViewerToolButtonIconPath(const QString& szIconName)
{
	return QApplication::applicationDirPath() + "\\Share\\ViewCoreResources\\ToolButtonIcons\\" + szIconName;
}

QString ITUtil::getNavigatorPath(const QString& iconName)
{
	return ":/Navigator/Resources/Navigator/" + iconName;
}

QString ITUtil::getMainWindowMenuPath(const QString& iconName)
{
	return ":/MainWindow/Resources/MainWindow/" + iconName;
}
QString ITUtil::getFeedBackPath(const QString& iconName)
{
	return ":/FeedBack/Resources/MainWindow/FeedBack/" + iconName;
}

QString ITUtil::getSkinPath(const QString& iconName)
{
	return ":/Skin/Resources/MainWindow/Skin/" + iconName;
}

QString ITUtil::getCursorPath(const QString& iconName)
{
	return ":/Cursor/Resources/Cursor/" + iconName;
}

QString ITUtil::getMarkerPath(const QString& iconName)
{
	return QApplication::applicationDirPath() + "\\Share\\ViewCoreResources\\Markers\\" + iconName;
}

QString ITUtil::getStaticMarkerPath(const QString& iconName)
{
	return ":/Marker/Resources/Marker/" + iconName;
}

QString ITUtil::getBarLevelIconsPath(const QString& iconName)
{
    return ":/BarLevelIcon/Resources/BarLevelIcon/" + iconName;
}

QString ITUtil::getGridConfigPath(QString moduleName, QString fileName)
{
	//if (GBMClientConfig::getInstance()->getProductType() == "ZJ")
	//{
	//	QString path = QString(":/config_ZJ/Resources/") + "config_ZJ\\" + moduleName + "\\" + fileName;
	//	if (fileExists(path))
	//		return path;
	//	else
	//	{
	//		return QString(":/config/Resources/") + "config\\" + moduleName + "\\" + fileName;
	//	}
	//}
	//else
	{
		return QString(":/config/Resources/") + "config\\" + moduleName + "\\" + fileName;
	}
}

QString ITUtil::getApplicationPath( const QString& iconName )
{
	return ":/Application/Res/Application/" + iconName;
}

QString ITUtil::getApplicationPath2(const QString& iconName)
{
	return ":/png/Resources/Application/" + iconName;
}

QString WcharArrayToQString(const wchar_t*  AWcharArray)
{
	return QString::fromUtf16(reinterpret_cast<const ushort*>(AWcharArray));
}

const wchar_t* QStringToWcharArray(const QString& AQString)
{
	return reinterpret_cast<const wchar_t*>(AQString.utf16());
}

#ifdef NOAPPINFO
#else
void GBMMessageBox::showInformation(const QString &msg,QWidget* parent)
{
	QWidget* parentWidget = parent;
	if (parentWidget == NULL)
		parentWidget = nullptr;
	QMessageBox::information(parentWidget, QObject::tr("Information"), msg);
	QApplication::processEvents();
}

void GBMMessageBox::showWarning( const QString &msg,QWidget* parent )
{
	QWidget* parentWidget = parent;
	if (parentWidget == NULL)
		parentWidget = nullptr;
	QMessageBox::warning(parentWidget, QObject::tr("Warning"), msg);
	QApplication::processEvents();
}

void GBMMessageBox::showError(const QString& msg,QWidget* parent)
{
	QWidget* parentWidget = parent;
	if (parentWidget == NULL)
		parentWidget = nullptr;
	QMessageBox::critical(parentWidget,QObject::tr("Error"),msg);
	QApplication::processEvents();
}

QMessageBox::StandardButton GBMMessageBox::showConfirm( const QString &msg, QMessageBox::StandardButtons btns,QWidget* parent )
{
	QWidget* parentWidget = parent;
	if (parentWidget == NULL)
		parentWidget = nullptr;
	QMessageBox::StandardButton enType = QMessageBox::question(parentWidget, QObject::tr("Confirm"), msg, btns);
	QApplication::processEvents();
	return enType;
}
#endif
/**
 \fn  QString ITUtil::getCADPaperDir(void)

 \brief CAD 文件的路径. 

 \author  zhangjb-a
 \date  2014-4-19

 \return  The cad paper dir.
 */
//#include "vtFilePath.h"
#include "GLDFileUtils.h"


QString ITUtil::getRecentProjectFilePath()
{
	return ITUtil::getProjectsRootPath() + "\\Recent.GSP";
}

QString ITUtil::getBarLevelIconFilePath( const QString& iConName )
{
	return QApplication::applicationDirPath()+"\\BarLevelIcon"+"\\"+iConName;
}

QString ITUtil::getScheduleTimeStateImagePath( const QString& iConName )
{
	return QApplication::applicationDirPath()+"\\ScheduleTimeState"+"\\"+iConName;
}

bool ITUtil::copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
	QDir sourceDir(fromDir);  
	QDir targetDir(toDir);  
	if(!targetDir.exists())
	{    /**< 如果目标目录不存在，则进行创建 */  
		if(!targetDir.mkdir(targetDir.absolutePath()))  
			return false;  
	}  

	QFileInfoList fileInfoList = sourceDir.entryInfoList();  
	foreach(QFileInfo fileInfo, fileInfoList)
	{  
		if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")  
			continue;  

		if(fileInfo.isDir())
		{    /**< 当为目录时，递归的进行copy */  
			if(!copyDirectoryFiles(fileInfo.filePath(),   
				targetDir.filePath(fileInfo.fileName()),  
				coverFileIfExist))  
				return false;  
		}  
		else
		{   /**< 当允许覆盖操作时，将旧文件进行删除操作 */  
			if(coverFileIfExist && targetDir.exists(fileInfo.fileName()))
			{  
				targetDir.remove(fileInfo.fileName());   
			}  

			/// 进行文件copy  
			if(!QFile::copy(fileInfo.filePath(),   
				targetDir.filePath(fileInfo.fileName())))
			{  
				return false;  
			}  
		}  
	}  
	return true;  
}

void ITUtil::packProject(QString projectPath, UINT64 llProjectID, QDataStream &stream,QString sLastVersion , bool bCooperate)
{
	if (directoryExists(projectPath))
	{
		IGLDZipFile *iZip = createZipFile();
		try
		{
			iZip->addFiles(projectPath);
			int nCooperate = bCooperate ? 1:0;
			iZip->setFileComment(QString("ProjectID=%0;Cooperate=%1;LastVersion=%2").arg(llProjectID).arg(nCooperate).arg(sLastVersion));
			iZip->saveToStream(stream.device());
			iZip->Release();
		}
		catch(...)
		{
			iZip->Release();
			throw;
		}
	}
}

QString ITUtil::getAppReportConfigPath()
{
    return ITUtil::getTemplateRootPath() + "\\ReportConfig\\";
}

QString ITUtil::getProjectReportConfigFile(QString projectPath, QString fileName)
{
    return ITUtil::getProjectRootPath(projectPath) + "\\ReportConfig\\" +  fileName;
}

//获取质量安全整改单目录
QString ITUtil::getNoticeFileDir()
{
	return ITUtil::getTemplateRootPath() + "\\NoticeFile\\";
}

//获取skp匹配规则配置文件
QString ITUtil::getSkpConfigPath()
{
	return QApplication::applicationDirPath() + "\\Template\\SKP2BIM5DConfig.GSP";
}

//获取排砖数据文件目录
QString ITUtil::getLayBrickTemplateDir()
{
	return ITUtil::getTemplateRootPath() + "\\LayBrick\\";
}

void ITUtil::doExportExcel(GlodonTableView *tableView, QString &pageName)
{
	if (tableView == NULL)
		return;
	QString	sExcelFile = QFileDialog::getSaveFileName(tableView, QObject::tr("Export"), pageName, QObject::tr("Excel file(*.xls)"));
	if(sExcelFile.isEmpty())
		return;
	GlodonTableViewToExcel::execute(tableView, sExcelFile, pageName);
}

void ITUtil::doExportExcel(GlodonTableView *tableView, const QString& filePath ,QString &pageName)
{
	if(filePath.isEmpty())
		return;
	if(tableView != NULL)
	{
		GlodonTableViewToExcel::execute(tableView,filePath,pageName);
        // panl-c-zx 2018.12.26 导出Excel时，添加表头 - 序号
        QFileInfo file(filePath);
        if (file.exists())
            writeSheetHead(filePath, QStringLiteral("序号"));
	}
}

void ITUtil::doExportExcel(GlodonTableView *tableView, const QString& filePath, QString &pageName, const QMap<QPair<int, int>, QString>& mapData)
{
	if (filePath.isEmpty())
		return;
	if (tableView != NULL)
	{
		GlodonTableViewToExcel::execute(tableView, filePath, pageName);
		// panl-c-zx 2018.12.26 导出Excel时，添加表头 - 序号
		QFileInfo file(filePath);
		if (file.exists())
		{
			writeSheetHead(filePath, QStringLiteral("序号"));
			writeSheetExternData(filePath, mapData);
		}
	}
}

void ITUtil::writeSheetExternData(const QString& filePath, const QMap<QPair<int, int>, QString>& mapData)
{
	GlodonXLSModel excelModel;
	if (true == excelModel.load(filePath))
	{
		Book* book = excelModel.book();
		if (nullptr != book)
		{
			Sheet* sheet = book->getSheet(0);
			libxl::Font* boldFont = book->addFont();
			Format* centralBoldFormat = book->addFormat();
			centralBoldFormat->setAlignH(ALIGNH_RIGHT);
			centralBoldFormat->setAlignV(ALIGNV_CENTER);
			centralBoldFormat->setFont(boldFont);
			for (auto it = mapData.begin(); it != mapData.end(); it++)
			{
				sheet->writeStr(it.key().first, it.key().second, it.value().toStdWString().c_str());
			}
		}
		excelModel.save(filePath);
	}
}



// panl-c-zx 2018.12.26 导出Excel时，添加表头 - 序号
void ITUtil::writeSheetHead(QString filePath, QString  headName)
{
    GlodonXLSModel excelModel;
    if (true == excelModel.load(filePath))
    {
        Book* book = excelModel.book();
        if (nullptr != book)
        {
            Sheet* sheet = book->getSheet(0);
            libxl::Font* boldFont = book->addFont();
            //boldFont->setBold(true);
            Format* centralBoldFormat = book->addFormat();
            centralBoldFormat->setAlignH(ALIGNH_CENTER);
            centralBoldFormat->setAlignV(ALIGNV_CENTER);
            centralBoldFormat->setFont(boldFont);
            sheet->setCol(0, 0, 5);
            sheet->setCellFormat(0, 0, centralBoldFormat);
            //CellType type = sheet->cellType(0, 0);
            sheet->writeStr(0, 0, headName.toStdWString().c_str());
        }
        excelModel.save(filePath);
    }
}

QString ITUtil::getFileHashValue(QString& stFilePath )
{
	QFile file(stFilePath);
	if(file.open(QIODevice::ReadWrite))
	{
		QCryptographicHash hash(QCryptographicHash::Md5);
		if(!file.atEnd())
		{
			hash.addData(file.readAll());
			QString  stHashValue;
			stHashValue.append(hash.result().toHex());
			return stHashValue;
		}
	}
	return QString();
}

std::wstring ITUtil::String2WString(const std::string& s)
{
	std::wstring wszStr;

	int nLength = MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, NULL, NULL);
	wszStr.resize(nLength);
	LPWSTR lpwszStr = new wchar_t[nLength];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, lpwszStr, nLength);
	wszStr = lpwszStr;
	delete[] lpwszStr;

	return wszStr;
}

QString ITUtil::GetTempDir()
{
// 	QString tempDir = QDir::tempPath() + QString("/%0").arg(GObjectID::NewID());
// 	forceDirectories(tempDir);
// 	return tempDir;
    return "";
}

//从注册表获取默认的路径
QString ITUtil::getRegEditDefaultPath()
{
	QSettings *reg = new QSettings("HKEY_LOCAL_MACHINE\\Software\\Glodon\\GBIM",  QSettings::NativeFormat);   
	QString result = reg->value("WorkSpace").toString();
	delete reg;
	return result;
}

void ITUtil::setRegEditDefaultPath(QString sPath)
{
	QSettings *reg = new QSettings("HKEY_LOCAL_MACHINE\\Software\\Glodon\\GBIM",  QSettings::NativeFormat);   
	reg->setValue("WorkSpace", sPath);
	delete reg;
}

QString ITUtil::getStringHashValue( QString& sStringContent )
{
	QByteArray byte_array;
	byte_array.append(sStringContent);
	QByteArray hash_byte_array = QCryptographicHash::hash(byte_array, QCryptographicHash::Md5);
	QString md5 = hash_byte_array.toHex();
	return md5;
}

QString ITUtil::getB5DPath( QString projectPath )
{
	QStringList strB5DFileList;
	findFiles(projectPath, QString("*.B5D"), strB5DFileList);

	if (strB5DFileList.count() > 0)
		return strB5DFileList[0];
	else
		return QString("");
}

QString ITUtil::getHistoryTemplateFilePath( QString strFileName, int nVersion )
{
	return getTemplateRootPath() + '\\' + "History" + "\\" + QString("%1").arg(nVersion) + "\\" + strFileName;
}

//获取报表历史版本模板文件
QString ITUtil::getReportHistoryTemplatePath(QString strFileName, int nVersion)
{
	return ITUtil::getTemplateRootPath() + "\\History\\Report\\" + QString("%1").arg(nVersion) + "\\" + strFileName;
}

QString ITUtil::getDemoProjectPath()
{
	 return QApplication::applicationDirPath() + "\\demo\\" + "Demo.P5D" ;
}


QString ITUtil::getAppUserFile()
{
    return QApplication::applicationDirPath()+"\\user.dat";
}

QString ITUtil::getProductConfigPath()
{
	return ":/ProductConfig/Resources/ProductConfig/ProductConfig.GSP";
}
QString ITUtil::getProductCooperateCachePath(const QString &projectPath)
{
	return getProjectRootPath(projectPath) + "\\SyncFiles\\" + "CooperateCache.GSP";
}

QString ITUtil::getAdminManageToolConfig( const QString& sName )
{
	return ":/AdminManage/Resources/config/AdminManage/"+sName;
}


QString ITUtil::GetConfigDirPath()
{
	return ":/config/Resources/config";
}

QString ITUtil::getPropSetCacheFilePath( const QString &projectPath )
{
	return getProjectRootPath(projectPath) + "\\SyncFiles\\" + "SQLLiteDelta.GSP";
}

bool ITUtil::checkContainCN( const QString& str )
{
	QRegExp rx("[\u4e00-\u9fa5]");//
	bool bRet = str.contains(rx);

	return bRet;
}

// 得到报表引擎路径
QString ITUtil::getGRPEnginePath()
{
#ifdef QT_DEBUG
	return exePath() + "GRPEngined.dll";
#else
	return exePath() + "GRPEngine.dll";
#endif
}

QString ITUtil::getConsultSynergyFilePath()
{
    return getTemplateFilePath("SynergyData.GSP");
}