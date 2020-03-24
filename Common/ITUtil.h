#ifndef GBMUtil_H
#define GBMUtil_H

#include <QtGui>
#include <QString>
#include <QMessageBox>
//#include "Glodon.BIM.ViewerBase/GBMViewConst.h"

#define USE_MANUAL_CLEARGSP		0
#define PERFORMANCE_TEST		0

using namespace std;

class ITExcuteExeThread:public QThread
{
public:
	ITExcuteExeThread(QObject *parent,QString sExePath,QStringList sListParameter);
	~ITExcuteExeThread();

	void startThead();
	void stopThead();
protected:
	void run();
private:
	QString m_sExePath;
	QStringList m_sListParameter;
	QProcess *  m_curProcess;
};

class ITUtil
{

public:
	//获取Template文件夹路径
	static QString getTemplateRootPath();
	//获取Template文件夹下文件路径
	static QString getTemplateFilePath(QString filename);
	//获取GBMProjectTemplate模板文件路径
	static QString getGSPTemplateFilePath();
	//获取数据包模板路径
	static QString getTemplatePacketRootPath(const QString& sPath);
	//获取应用程序临时文件夹路径
	static QString getAppTempRootPath();
	static QString getQ4CalculatorPath();
	static QString getQ4CalcDataPath(QString projectPath);
	//获取新漫游功能所需要的图标
	static QString getAppPanSymbolPath();
	//获取模板动画所需要的图标
	static QString getTemplateMoviePath();
	//获取云端配置文件路径
	static QString getCloudExceptionPath(QString& sFileName);

	//获取所有工程项目数据文件夹路径
	static QString getProjectsRootPath();
	//获取最近打开项目列表文件路径
	static QString getRecentProjectFilePath();

	//获取特定工程项目数据文件夹路径
	static QString getProjectRootPath(QString projectPath, bool isCooperate);
	static QString getProjectRootPath(QString projectPath);
	//获取特定工程项目的GSP文件路径
	static QString getProjectGSPFilePath(QString projectPath);
	//获取项目标识图标
	static QString getProjectMarkFilePath(QString projectPath);
	//获取Sqlite数据库名称
	static QString getProjectSqlliteFilePath(QString projectPath);
	//获取特定工程项目的File文件路径
	static QString getProjectFileRootPath(QString projectPath);
	//获取特定工程项目的特定File文件路径
	static QString getProjectFilePath(QString projectPath, UINT64 fileID);
	//获取特定工程项目Geo文件夹路径
	static QString getProjectGeoRootPath(QString projectPath);
	//获取特定工程项目OtherGeo文件夹路径
	static QString getProjectOtherGeoRootPath(QString projectPath);
	//获取特定工程项目OtherModel文件夹路径
	static QString getProjectOtherModelRootPath(QString projectPath);
	//获取特定工程项目ScreenShot文件夹路径
	static QString getProjectScreenShotRootPath(QString projectPath);
	//获取特定工程项目IGMS文件夹路径
	static QString getProjectIGMSRootPath(QString projectPath,UINT64 revID);
	//获取特定工程项目CAD文件夹路径
	static QString getProjectCadRootPath(QString projectPath);
	//获取特定工程项目CAD数据库路径
	static QString getProjectCadModelRootDir(QString projectPath);
	//获取特定工程项目MPP文件夹路径
	static QString getProjectMPPRootPath(QString projectPath);
    //获取特定工程项目SyncFiles文件夹路径
    static QString getProjectSyncFilesRootPath( QString projectPath );
    static QString getProjectCacheLogPath( QString projectPath );
	static QString getProjectLogBackupPath( QString projectPath );
	static QString getProjectCachePacketDataRootPath( QString projectPath );
	static QString getProjectTempPacketRootPath(QString projectPath);
	static QString getProjectSyncChangeCachePath( QString projectPath );
	//获取特定工程项目排砖文件夹路径
	static QString getProjectLayBrickDir(QString projectPath);

	static QString getProjectLBfilePath(QString projectPath);

    //获取应用程序报表配置路径
    static QString getAppReportConfigPath();
    //获取特定项目报表配置文件
    static QString getProjectReportConfigFile(QString projectPath, QString fileName);
	//获取质量安全整改单目录
	static QString getNoticeFileDir();
	//获取skp匹配规则配置文件
	static QString getSkpConfigPath();
	//获取排砖数据文件目录
	static QString getLayBrickTemplateDir();

    //获取geo的文件名
	static QString getGeoFileName(UINT64 lID);
	static QString getSpecialQueryCfg(QString projectPath);

	//获取特定工程项目咨询文件夹路径
    static QString getProjectConstPath(QString projectPath);
    static QString getProjectConstCloudPath(QString projectPath);
	static QString getStatAuditFileRootPath(QString projectPath, UINT64 uStatID);

	//从注册表获取默认的路径
	static QString getRegEditDefaultPath();

	static void  setRegEditDefaultPath(QString sPath);

	//获取导航栏路径
	static QString getNavigatorPath(const QString& iconName);

	//获取Icon路径
	static QString getIconsPath(const QString& iconName);
    //获取ReportIcon路径
    static QString getReportIconsPath(const QString& iconName);
	//获取排砖图标路径
	static QString getLayBrickIconsPath(const QString& iconName);
	//获取钢筋图标的路径
	static QString getBarLevelIconFilePath(const QString& iConName);

	//获取钢筋图标的路径
	static QString getScheduleTimeStateImagePath(const QString& iConName);

	//获取浏览工具条图标路径
	static QString getViewerToolButtonIconPath(const QString& szIconName);

	//获取树状图图标路径
	static QString getTreeWidgetIconPath(const QString& iconName);

	//获取主窗体菜单图标路径
	static QString getMainWindowMenuPath(const QString& iconName);

	//获取主窗体菜单图标路径
	static QString getFeedBackPath(const QString& iconName);

	//获取皮肤路径
	static QString getSkinPath(const QString& iconName);

	//光标图标
	static QString getCursorPath(const QString& iconName);
	static QString getMarkerPath(const QString& iconName);
	static QString getStaticMarkerPath(const QString& iconName);

	static QString getApplicationPath(const QString& iconName);
	static QString getApplicationPath2(const QString& iconName);

	static QString getToolbarIconPath(QString iconName);
    static QString getBarLevelIconsPath(const QString& iconName);

	static QString getGridConfigPath(QString moduleName, QString fileName);

	static bool writeInit(QString path, QString user_key, QString user_value);
	static bool readInit(QString path, QString user_key, QString &user_value);

	static bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist);
	static void packProject(QString projectPath, UINT64 llProjectID, QDataStream &stream, QString sLastVersion ,bool bCooperate = false ); 
	//向项目内的user.dat写入密码
	static void writePassword(const QString& sProjectPath);

	static void doExportExcel(GlodonTableView *tableView, QString &pageName);
	static void doExportExcel(GlodonTableView *tableView, const QString& filePath ,QString &pageName);
	static void doExportExcel(GlodonTableView *tableView, const QString& filePath, QString &pageName, const QMap<QPair<int, int>, QString>& mapData);

	static QString getFileHashValue(QString& stFilePath);

	static QString getStringHashValue(QString& sStringContent);

	static void packFileToZip(const QString& stFilePath,QString& stZipName, bool use7Z = true);

	//获取B5D文件路径
	static QString getB5DPath(QString projectPath);
	//获取历史版本模板文件
	static QString getHistoryTemplateFilePath(QString strFileName, int nVersion);
	//获取报表历史版本模板文件
	static QString getReportHistoryTemplatePath(QString strFileName, int nVersion);

	/// 设置行走人物后背图片
	static void SetAppPanSignFile(QString strFileName);
	static QString GetAppPanSignFile();

	//案例工程路径
	static QString getDemoProjectPath();

	//获取安装目录的用户信息
	static QString getProjectUserFile(QString sProjectPath);
	//获取项目目录的用户信息
	static QString getAppUserFile();

	static QString getProductConfigPath();
	static QString getProductCooperateCachePath(const QString &projectPath);

	static QString getAdminManageToolConfig(const QString& sName);
	static QString GetConfigDirPath();

	static QString getPropSetCacheFilePath(const QString &projectPath);

	static bool checkContainCN(const QString& str);

	static QString GetElementSubTypeName(int iElementType);

	// 得到报表引擎路径
	static QString getGRPEnginePath();
	static std::wstring String2WString(const std::string& s);

	// 获取临时目录
	static QString GetTempDir();

    // 获取
    static QString getConsultSynergyFilePath();

    // panl-c-zx 2018.12.26 导出Excel时，添加表头 - 序号
    static void writeSheetHead(QString filePath, QString  headName);

	// houy 20190618
	static void writeSheetExternData(const QString& filePath, const QMap<QPair<int, int>, QString>& mapData);

public:
	static QString s_szProjPath;

	/// 用于人物行走后背的标志
	static QString s_strAppPanSign;

};

#ifdef NOAPPINFO
#else
namespace GBMMessageBox
{
	void showInformation(const QString &msg,QWidget* parent = NULL);
	void showWarning( const QString &msg,QWidget* parent = NULL);
	void showError( const QString& msg,QWidget* parent = NULL);
	QMessageBox::StandardButton showConfirm( const QString &msg, QMessageBox::StandardButtons btns, QWidget* parent = NULL);
}
#endif
/*!
* @brief 将宽字符串转换为QString类型                                 
* @param[in] const wchar_t * WcharArray
* @return QString    
*/

QString WcharArrayToQString(const wchar_t*  WcharArray);

/*!
* @brief 将QString类型转换为宽字符串                              
* @param[in] const QString & AQString
* @return const wchar_t*    
*/
const wchar_t* QStringToWcharArray(const QString& AQString);

#define OutputSystemError DWORD dw = GetLastError(); \
LPVOID lpMsgBuf; \
FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,NULL,dw, \
			  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),(LPTSTR) &lpMsgBuf,0,NULL); \
OutputDebugString(static_cast<LPCWSTR>(lpMsgBuf));

#endif