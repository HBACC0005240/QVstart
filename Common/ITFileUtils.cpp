#include "ITFileUtils.h"
#include <QCoreApplication>
#include <QProcess>
#include <QTemporaryFile>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QException>
#include <QDebug>
#include "ITSysUtils.h"
#include "ITStrUtils.h"
#ifdef WIN32
#include <ShlObj.h>
#endif


//���ܣ� ��ȡexe�ļ���������
QString exeFullName()
{
#ifdef WIN32
    // ��֧�ֳ�·��??
    wchar_t szModuleName[MAX_PATH + 1] = {0};
    GetModuleFileName(NULL, szModuleName, MAX_PATH + 1);
    QString strPath = QString::fromUtf16((ushort *)szModuleName);
    return strPath;
#else
    return qApp->applicationName();
#endif
}

/*************************************************************************
  ˵�������ص�ǰ����EXE�ļ���·��
  ��������
  ���أ���ǰ����EXE�ļ���·��
*************************************************************************/
QString exePath()
{
    return exeDir() + pathDelim(); //��ȡ��ǰӦ�ó���·��
}

QString exeDir()
{
#ifdef WIN32
    QString strPath = exeFullName();
    int nIndex = strPath.lastIndexOf('\\');
    if (nIndex < 0)
    {
        nIndex = strPath.lastIndexOf('/');
        if (nIndex < 0)
        {
            return QString();
        }
    }
    strPath = strPath.left(nIndex);
    return strPath;
#else
    return QCoreApplication::applicationDirPath(); //��ȡ��ǰӦ�ó���·��
#endif
}

QString moduleName(void *module)
{
    // todo
    return exeFullName();
    Q_UNUSED(module)
}

QString getCurrentDir()
{
    return QDir::currentPath();
}

bool isLibrary()
{
    const QString strModuleName = moduleName(NULL);
    const QString strModuleExt = extractFileExt(strModuleName);

    return QString::compare(strModuleExt, ".dll", Qt::CaseInsensitive) == 0;
}

bool fileExists(const QString &fileName)
{
    QFileInfo fileInfo(fileName);

    if (fileInfo.isDir())
    {
        return false;
    }

    return QFile::exists(fileName);
}

QIODevice *createFileStream(const QString &fileName)
{
    return new QFile(fileName);
}

QString extractFileExt(const QString &fileName)
{
    int nIndex = rPos('.', fileName);
    if (nIndex >= 0 && fileName[nIndex] == '.')
    {
        return copy(fileName, nIndex);
    }
    else
    {
        return QString();
    }
}

/*!
 * @brief �ı��ļ�������չ��
 * @param[in] fileName ���޸ĵ��ļ���
 * @param[in] extension ��׺��
 * @return �����޸ĺ���ļ���
*/
QString changeFileExt(const QString &fileName, const QString &extension)
{
    /* �����û�������ȷ������fileNameΪ�ļ��д���ʽû����ȷ�涨
       fileNameΪ�ջ��ļ���ʱ�� �������� */
    QFileInfo info(fileName);
    if (fileName.isEmpty() || info.isDir())
        return fileName;

    QString sResult = fileName;

    if(!info.suffix().isEmpty())
        sResult = sResult.remove(fileName.length()-(info.suffix().length())-1,info.suffix().length()+1);
    if(!extension.isEmpty())
        sResult += "." + extension;

    return sResult;
}

/*************************************************************************
 *���ߣ� zhouyl-a 2013-8-8
 *������
 *  1��oldFile : ���������ļ���
 *  2��newFile : ���ļ���
 *  3��failIfExists : ������ʶ; failIfExists == true ��������ļ����ھ�ʧ�ܣ�
 *                            failIfExists == false��������ļ����ھ͸��ǣ�
 *���أ�true �ɹ�, false ʧ��
*************************************************************************/
bool copyFile(const QString &oldFile, const QString &newFile, bool failIfExists)
{
    // ��� failIfExists Ϊ��,��newFile����,ֱ�ӷ���
    if (failIfExists && fileExists(newFile))
    {
        return false;
    }

    // ��� failIfExists Ϊ��,��newFile����
    if (!failIfExists && fileExists(newFile))
    {
        //ɾ��newFile
        QFile::remove(newFile);
    }

    return (QFile::copy(oldFile, newFile));

}

bool deleteFile(const QString &fileName)
{
    if (fileExists(fileName))
    {
        return QFile::remove(fileName);
    }
    return false;
}

bool deleteTree(const QString &path)
{
    if (path.isEmpty())
        return false;
    QString strPath = includeTrailingPathDelimiter(path);
    QDir dir(strPath);
    if (!dir.exists())
        return true;

    QFileInfoList fileList = dir.entryInfoList(QDir::AllEntries | QDir::Hidden);
    QString strFileName;
    QString strFile;
    foreach (QFileInfo fileInfo, fileList)
    {
        strFileName = fileInfo.fileName();
        if ((strFileName == QString("..")) || (strFileName == QString(".")))
            continue;
        if (fileInfo.isDir())
        {
            strFile = strPath + strFileName + "/";
            deleteTree(strFile);
        }
        else
        {
            strFile = strPath + strFileName;
            if (!fileInfo.permission(QFile::WriteOwner))
            {
                QFile file(strFile);
                file.setPermissions(QFile::WriteOwner);
            }
            QFile::remove(strFile);
        }
    }
    return dir.rmdir(strPath);
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-04
  ������ const QString &, QStrings &
  ���أ� ��
  ���ܣ� �õ�������Ŀ¼
*************************************************************************/
bool findSubFolders(const QString &path, QStrings &folders)
{
    QDir oDir(path);
    folders.clear();

    if(!oDir.exists())
    {
        return false;
    }

    oDir.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    folders = oDir.entryList();
    return true;
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-26
  ������ const QString &, const QStrings &, QStrings &
  ���أ� ��
  ���ܣ� ͨ����׺��Ѱ��Ŀ¼���Լ���ǰĿ¼��������Ŀ¼�������ļ�
*************************************************************************/
void findFiles(const QString &path, const QStrings &nameFilters, QStrings &files)
{
    QDir oDir(path);
    oDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);

    if (nameFilters.size() == 1)
    {
        if (!nameFilters.at(0).isEmpty())
        {
            oDir.setNameFilters(nameFilters);
        }
    }
    else
    {
        oDir.setNameFilters(nameFilters);
    }

    QStrings oFiles = oDir.entryList();
    for (int i = 0; i < oFiles.size(); i++)
    {
        files.append(includeTrailingPathDelimiter(path) + oFiles.at(i));
    }

    QStrings oSubFileDirs;
    findSubFolders(path, oSubFileDirs);
    for (int i = 0; i < oSubFileDirs.size(); i++)
    {
        findFiles((includeTrailingPathDelimiter(path) + oSubFileDirs.at(i)), nameFilters, files);
    }
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-26
  ������ const QString &, QStrings &, const QString &
  ���أ� ��
  ���ܣ� ͨ����׺��Ѱ��Ŀ¼���Լ���ǰĿ¼��������Ŀ¼�������ļ�
*************************************************************************/
void findFiles(const QString &path, const QString &nameFilter, QStrings &files)
{
    QStrings oNameFilters;
    if (nameFilter.isEmpty())
    {
        oNameFilters.append("*.*");

    }
    else
    {
        oNameFilters.append(nameFilter);
    }

    findFiles(path, oNameFilters, files);
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-26
  ������ const QString &, QStrings &, const QString &, bool
  ���أ� ��
  ���ܣ� ͨ����׺��Ѱ�ҵ�ǰĿ¼�������ļ�
*************************************************************************/
void getFiles(const QString &path, QStrings &files, const QString &nameFilter)
{
    QStrings oNameFilters;
    if (nameFilter.isEmpty())
    {
        oNameFilters.append("*.*");

    }
    else
    {
        oNameFilters.append(nameFilter);
    }

    getFiles(path, oNameFilters, files);
}

void getFiles(const QString &path, const QStrings &nameFilters, QStrings &files, bool includeDir)
{
    QDir oDir(path);
    if (includeDir)
    {
        oDir.setFilter(QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot);
    }
    else
    {
        oDir.setFilter(QDir::Files | QDir::NoDotAndDotDot);
    }

    if (nameFilters.size() == 1)
    {
        if (!nameFilters.at(0).isEmpty())
        {
            oDir.setNameFilters(nameFilters);
        }
    }
    else
    {
        oDir.setNameFilters(nameFilters);
    }

    files.append(oDir.entryList());
}

/*************************************************************************
  ���ߣ� yanyq-a 2013-07-31
  ������ QString&
  ���أ� QString
  ���ܣ� ��ȡ����ϵͳ�ɽ��ܵ��ļ���(��ӦԭGetValidFileName)
*************************************************************************/
QString getValidFileName(const QString &fileName)
{
    QStrings oInvalidChars = (QStrings() << "\\" << "/" << ":" << "\"" << ">" << "<" << "\r\n" << "|" << "?" << "*");
    QString sValidFileName(fileName);
    for (int i = 0; i < oInvalidChars.count(); ++i)
    {
        sValidFileName.replace(oInvalidChars[i], "_", Qt::CaseInsensitive);
    }

    return sValidFileName;
}

/*!
 * @brief ����ָ���ļ���
 * @param[in] path ·��
 * @return true �ɹ� false ʧ��
*/
bool createDir(const QString &path)
{
    QDir oDir;
    return oDir.mkpath(path);
}

bool forceDirectories(const QString &path)
{
    if (path.isEmpty())
        return false;
    QString strDir = excludeTrailingPathDelimiter(path);
    QDir oDir(strDir);
    if (oDir.exists())
        return true;
    QString strParentDir = extractFilePath(strDir);
    if (sameText(strParentDir, strDir))
        return true;
    return forceDirectories(strParentDir) && oDir.mkdir(strDir);
}

bool directoryExists(const QString &path)
{
    if (path.isEmpty())
    {
        return false;
    }
    QDir oDir(path);
    return oDir.exists();
}

QString extractFilePath(const QString &fileName)
{
    int nIndex = pathDelimPos(fileName);
    if (nIndex >= 0)
        return copy(fileName, 0, nIndex + 1);
    else
    {
        return QString();
    }
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-20
  ������ const QString &
  ���أ� QString
  ���ܣ� ���ļ����л�ȡĿ¼��(�ļ����ڸ�Ŀ¼��ʱȡ�õ�ֵ��û�С�/�����ڸ�Ŀ¼ʱһ���������̷������硰C:/��)
*************************************************************************/
QString extractFileDir(const QString &fileName)
{
    int nIndex = pathDelimPos(fileName);
    if (nIndex >= 0)
    {
        if ((nIndex >= 1) && (fileName[nIndex - 1] == driveDelim()))
        {
            ++nIndex;
        }
        return copy(fileName, 0, nIndex);
    }
    else
        return QString();
}

QString extractFileName(const QString &fileName)
{
    int nIndex = pathDelimPos(fileName);
    return copy(fileName, nIndex + 1);
}

QString extractFileNameOnly(const QString &fileName)
{
    QString result = extractFileName(fileName);
    int nDotPos = rPos(QChar('.'), result);
    if (nDotPos >= 0)
        return copy(result, 0, nDotPos);
    else
        return result;
}

// ���·��ת��Ϊ����·��
QString expandFileName(const QString &fileName)
{
    QFileInfo oFileInfo(fileName);
#ifdef WIN32
    return oFileInfo.absoluteFilePath().replace(QChar('/'), pathDelim());
#else
    return oFileInfo.absoluteFilePath();
#endif
}

/*************************************************************************
  ���ߣ� jiangjb 2013-06-14
  ������ const QString &, bool
  ���أ� ��
  ���ܣ� �����ļ�ֻ��
*************************************************************************/
void fileSetReadOnly(const QString &fileName, bool readOnly)
{
    if (readOnly)
    {
        QFile::setPermissions(fileName, QFile::ReadOther);
    }
    else
    {
        QFile::setPermissions(fileName, QFile::WriteOther | QFile::ReadOther);
    }
}

/*************************************************************************

  ���ߣ�liudi 2013 ԭ���ߣ�
  ������const QString &fileName
  ���أ�qint64
  ����: �����ļ���С

  �������ԭ����TGBQ4ZipFileUtils��
*************************************************************************/
qint64 getFileSize(const QString &fileName)
{
    QFileInfo fileInfo(fileName);

    return fileInfo.size();
}

QString getCommonDocumentsPath()
{
#ifdef Q_OS_WIN
    return getSpecialFolderPath(CSIDL_COMMON_DOCUMENTS);
#else
    return QString("");
#endif
}

QString getTempFile(const QString &prefix, const QString &path)
{
    QTemporaryFile tempFile(includeTrailingPathDelimiter(path) + prefix + "XXXXXX.tmp");
    tempFile.setAutoRemove(false);
    if (tempFile.open())
    {
        QString result = tempFile.fileName();
        tempFile.close();
        return result;
    }
    return QString();
}

int pathDelimPos(const QString &fileName)
{
    int nPathDelimPos = rPos(pathDelim(), fileName);
    int nBackSlashPos = rPos(backSlashDelim(), fileName);
    return (nPathDelimPos > nBackSlashPos ? nPathDelimPos : nBackSlashPos);
}

QString getCommandLineOutput(
        const QString &commandLine, const QString &workDir, int &exitCode)
{
    QProcess process;
    //process.setReadChannel(QProcess::StandardOutput);
    //process.setReadChannelMode(ForwardedChannels);
    process.setWorkingDirectory(workDir);
    process.start(commandLine);
    if (!process.waitForFinished(-1))
    {
        exitCode = -2;
        return QString();
    }
    if (process.exitStatus() == QProcess::NormalExit)
    {
        exitCode = process.exitCode();
        QByteArray array = process.readAllStandardOutput();
        return QString::fromLocal8Bit(array.constData());
    }
    else
    {
        exitCode = -1;
        return QString();
    }
}

QString loadQssFile(const QString &fileName)
{
    QFile oQssFile(fileName);
    if (!oQssFile.open(QIODevice::ReadOnly))
    {
        return QString();
    }
    else
    {
        return oQssFile.readAll();
    }
}
