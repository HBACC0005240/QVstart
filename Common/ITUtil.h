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
	//��ȡTemplate�ļ���·��
	static QString getTemplateRootPath();
	//��ȡTemplate�ļ������ļ�·��
	static QString getTemplateFilePath(QString filename);
	//��ȡGBMProjectTemplateģ���ļ�·��
	static QString getGSPTemplateFilePath();
	//��ȡ���ݰ�ģ��·��
	static QString getTemplatePacketRootPath(const QString& sPath);
	//��ȡӦ�ó�����ʱ�ļ���·��
	static QString getAppTempRootPath();
	static QString getQ4CalculatorPath();
	static QString getQ4CalcDataPath(QString projectPath);
	//��ȡ�����ι�������Ҫ��ͼ��
	static QString getAppPanSymbolPath();
	//��ȡģ�嶯������Ҫ��ͼ��
	static QString getTemplateMoviePath();
	//��ȡ�ƶ������ļ�·��
	static QString getCloudExceptionPath(QString& sFileName);

	//��ȡ���й�����Ŀ�����ļ���·��
	static QString getProjectsRootPath();
	//��ȡ�������Ŀ�б��ļ�·��
	static QString getRecentProjectFilePath();

	//��ȡ�ض�������Ŀ�����ļ���·��
	static QString getProjectRootPath(QString projectPath, bool isCooperate);
	static QString getProjectRootPath(QString projectPath);
	//��ȡ�ض�������Ŀ��GSP�ļ�·��
	static QString getProjectGSPFilePath(QString projectPath);
	//��ȡ��Ŀ��ʶͼ��
	static QString getProjectMarkFilePath(QString projectPath);
	//��ȡSqlite���ݿ�����
	static QString getProjectSqlliteFilePath(QString projectPath);
	//��ȡ�ض�������Ŀ��File�ļ�·��
	static QString getProjectFileRootPath(QString projectPath);
	//��ȡ�ض�������Ŀ���ض�File�ļ�·��
	static QString getProjectFilePath(QString projectPath, UINT64 fileID);
	//��ȡ�ض�������ĿGeo�ļ���·��
	static QString getProjectGeoRootPath(QString projectPath);
	//��ȡ�ض�������ĿOtherGeo�ļ���·��
	static QString getProjectOtherGeoRootPath(QString projectPath);
	//��ȡ�ض�������ĿOtherModel�ļ���·��
	static QString getProjectOtherModelRootPath(QString projectPath);
	//��ȡ�ض�������ĿScreenShot�ļ���·��
	static QString getProjectScreenShotRootPath(QString projectPath);
	//��ȡ�ض�������ĿIGMS�ļ���·��
	static QString getProjectIGMSRootPath(QString projectPath,UINT64 revID);
	//��ȡ�ض�������ĿCAD�ļ���·��
	static QString getProjectCadRootPath(QString projectPath);
	//��ȡ�ض�������ĿCAD���ݿ�·��
	static QString getProjectCadModelRootDir(QString projectPath);
	//��ȡ�ض�������ĿMPP�ļ���·��
	static QString getProjectMPPRootPath(QString projectPath);
    //��ȡ�ض�������ĿSyncFiles�ļ���·��
    static QString getProjectSyncFilesRootPath( QString projectPath );
    static QString getProjectCacheLogPath( QString projectPath );
	static QString getProjectLogBackupPath( QString projectPath );
	static QString getProjectCachePacketDataRootPath( QString projectPath );
	static QString getProjectTempPacketRootPath(QString projectPath);
	static QString getProjectSyncChangeCachePath( QString projectPath );
	//��ȡ�ض�������Ŀ��ש�ļ���·��
	static QString getProjectLayBrickDir(QString projectPath);

	static QString getProjectLBfilePath(QString projectPath);

    //��ȡӦ�ó��򱨱�����·��
    static QString getAppReportConfigPath();
    //��ȡ�ض���Ŀ���������ļ�
    static QString getProjectReportConfigFile(QString projectPath, QString fileName);
	//��ȡ������ȫ���ĵ�Ŀ¼
	static QString getNoticeFileDir();
	//��ȡskpƥ����������ļ�
	static QString getSkpConfigPath();
	//��ȡ��ש�����ļ�Ŀ¼
	static QString getLayBrickTemplateDir();

    //��ȡgeo���ļ���
	static QString getGeoFileName(UINT64 lID);
	static QString getSpecialQueryCfg(QString projectPath);

	//��ȡ�ض�������Ŀ��ѯ�ļ���·��
    static QString getProjectConstPath(QString projectPath);
    static QString getProjectConstCloudPath(QString projectPath);
	static QString getStatAuditFileRootPath(QString projectPath, UINT64 uStatID);

	//��ע����ȡĬ�ϵ�·��
	static QString getRegEditDefaultPath();

	static void  setRegEditDefaultPath(QString sPath);

	//��ȡ������·��
	static QString getNavigatorPath(const QString& iconName);

	//��ȡIcon·��
	static QString getIconsPath(const QString& iconName);
    //��ȡReportIcon·��
    static QString getReportIconsPath(const QString& iconName);
	//��ȡ��שͼ��·��
	static QString getLayBrickIconsPath(const QString& iconName);
	//��ȡ�ֽ�ͼ���·��
	static QString getBarLevelIconFilePath(const QString& iConName);

	//��ȡ�ֽ�ͼ���·��
	static QString getScheduleTimeStateImagePath(const QString& iConName);

	//��ȡ���������ͼ��·��
	static QString getViewerToolButtonIconPath(const QString& szIconName);

	//��ȡ��״ͼͼ��·��
	static QString getTreeWidgetIconPath(const QString& iconName);

	//��ȡ������˵�ͼ��·��
	static QString getMainWindowMenuPath(const QString& iconName);

	//��ȡ������˵�ͼ��·��
	static QString getFeedBackPath(const QString& iconName);

	//��ȡƤ��·��
	static QString getSkinPath(const QString& iconName);

	//���ͼ��
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
	//����Ŀ�ڵ�user.datд������
	static void writePassword(const QString& sProjectPath);

	static void doExportExcel(GlodonTableView *tableView, QString &pageName);
	static void doExportExcel(GlodonTableView *tableView, const QString& filePath ,QString &pageName);
	static void doExportExcel(GlodonTableView *tableView, const QString& filePath, QString &pageName, const QMap<QPair<int, int>, QString>& mapData);

	static QString getFileHashValue(QString& stFilePath);

	static QString getStringHashValue(QString& sStringContent);

	static void packFileToZip(const QString& stFilePath,QString& stZipName, bool use7Z = true);

	//��ȡB5D�ļ�·��
	static QString getB5DPath(QString projectPath);
	//��ȡ��ʷ�汾ģ���ļ�
	static QString getHistoryTemplateFilePath(QString strFileName, int nVersion);
	//��ȡ������ʷ�汾ģ���ļ�
	static QString getReportHistoryTemplatePath(QString strFileName, int nVersion);

	/// �������������ͼƬ
	static void SetAppPanSignFile(QString strFileName);
	static QString GetAppPanSignFile();

	//��������·��
	static QString getDemoProjectPath();

	//��ȡ��װĿ¼���û���Ϣ
	static QString getProjectUserFile(QString sProjectPath);
	//��ȡ��ĿĿ¼���û���Ϣ
	static QString getAppUserFile();

	static QString getProductConfigPath();
	static QString getProductCooperateCachePath(const QString &projectPath);

	static QString getAdminManageToolConfig(const QString& sName);
	static QString GetConfigDirPath();

	static QString getPropSetCacheFilePath(const QString &projectPath);

	static bool checkContainCN(const QString& str);

	static QString GetElementSubTypeName(int iElementType);

	// �õ���������·��
	static QString getGRPEnginePath();
	static std::wstring String2WString(const std::string& s);

	// ��ȡ��ʱĿ¼
	static QString GetTempDir();

    // ��ȡ
    static QString getConsultSynergyFilePath();

    // panl-c-zx 2018.12.26 ����Excelʱ����ӱ�ͷ - ���
    static void writeSheetHead(QString filePath, QString  headName);

	// houy 20190618
	static void writeSheetExternData(const QString& filePath, const QMap<QPair<int, int>, QString>& mapData);

public:
	static QString s_szProjPath;

	/// �����������ߺ󱳵ı�־
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
* @brief �����ַ���ת��ΪQString����                                 
* @param[in] const wchar_t * WcharArray
* @return QString    
*/

QString WcharArrayToQString(const wchar_t*  WcharArray);

/*!
* @brief ��QString����ת��Ϊ���ַ���                              
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