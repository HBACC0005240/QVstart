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


//功能： 获取exe文件完整名称
QString exeFullName()
{
#ifdef WIN32
    // 不支持长路径??
    wchar_t szModuleName[MAX_PATH + 1] = {0};
    GetModuleFileName(NULL, szModuleName, MAX_PATH + 1);
    QString strPath = QString::fromUtf16((ushort *)szModuleName);
    return strPath;
#else
    return qApp->applicationName();
#endif
}

/*************************************************************************
  说明：返回当前运行EXE文件的路径
  参数：无
  返回：当前运行EXE文件的路径
*************************************************************************/
QString exePath()
{
    return exeDir() + pathDelim(); //获取当前应用程序路径
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
    return QCoreApplication::applicationDirPath(); //获取当前应用程序路径
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
 * @brief 改变文件名的扩展名
 * @param[in] fileName 被修改的文件名
 * @param[in] extension 后缀名
 * @return 返回修改后的文件名
*/
QString changeFileExt(const QString &fileName, const QString &extension)
{
    /* 由于用户需求不明确，对于fileName为文件夹处理方式没有明确规定
       fileName为空或文件夹时， 不做处理 */
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
 *作者： zhouyl-a 2013-8-8
 *参数：
 *  1）oldFile : 被拷贝的文件名
 *  2）newFile : 新文件名
 *  3）failIfExists : 操作标识; failIfExists == true 则是如果文件存在就失败；
 *                            failIfExists == false则是如果文件存在就覆盖；
 *返回：true 成功, false 失败
*************************************************************************/
bool copyFile(const QString &oldFile, const QString &newFile, bool failIfExists)
{
    // 如果 failIfExists 为真,且newFile存在,直接返回
    if (failIfExists && fileExists(newFile))
    {
        return false;
    }

    // 如果 failIfExists 为假,且newFile存在
    if (!failIfExists && fileExists(newFile))
    {
        //删除newFile
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
  作者： jiangjb 2013-06-04
  参数： const QString &, QStrings &
  返回： 无
  功能： 得到所有子目录
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
  作者： jiangjb 2013-06-26
  参数： const QString &, const QStrings &, QStrings &
  返回： 无
  功能： 通过后缀名寻找目录下以及当前目录下所有子目录的所有文件
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
  作者： jiangjb 2013-06-26
  参数： const QString &, QStrings &, const QString &
  返回： 无
  功能： 通过后缀名寻找目录下以及当前目录下所有子目录的所有文件
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
  作者： jiangjb 2013-06-26
  参数： const QString &, QStrings &, const QString &, bool
  返回： 无
  功能： 通过后缀名寻找当前目录下所有文件
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
  作者： yanyq-a 2013-07-31
  参数： QString&
  返回： QString
  功能： 获取操作系统可接受的文件名(对应原GetValidFileName)
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
 * @brief 创建指定文件夹
 * @param[in] path 路径
 * @return true 成功 false 失败
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
  作者： jiangjb 2013-06-20
  参数： const QString &
  返回： QString
  功能： 从文件名中获取目录名(文件不在根目录下时取得的值后没有“/”，在根目录时一样，都是盘符，例如“C:/”)
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

// 相对路径转换为绝对路径
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
  作者： jiangjb 2013-06-14
  参数： const QString &, bool
  返回： 无
  功能： 设置文件只读
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

  作者：liudi 2013 原作者：
  参数：const QString &fileName
  返回：qint64
  功能: 返回文件大小

  这个函数原来在TGBQ4ZipFileUtils中
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
