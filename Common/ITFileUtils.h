#ifndef ITFILEUTILS_H
#define ITFILEUTILS_H

#include <QString>
#include <QStringList>
#include <QIODevice>
typedef QStringList QStringList;
typedef QStringList QStrings;

QString exeFullName();
QString exePath();
QString exeDir();

QString moduleName(void *module);

QString getCurrentDir();

QString getCommonDocumentsPath();

QString getTempFile(const QString &prefix, const QString &path);

bool isLibrary();

//实现Win32平台函数BOOL CopyFile(LPCTSTR lpExistingFileName,LPCTSTR lpNewFileName,BOOL bFailIfExists );
bool copyFile(const QString &oldFile, const QString &newFile, bool failIfExists);

bool deleteFile(const QString &fileName);
bool deleteTree(const QString &path);

bool fileExists(const QString &fileName);
QIODevice *createFileStream(const QString &fileName);
QString extractFileExt(const QString &fileName);
QString changeFileExt(const QString &fileName, const QString &extension);

bool findSubFolders(const QString &path, QStrings &folders);
void findFiles(const QString &path, const QStrings &nameFilters, QStrings &files);
void findFiles(const QString &path, const QString &nameFilter, QStrings &files);
void getFiles(const QString &path, QStrings &files, const QString &nameFilter = "");
void getFiles(const QString &path, const QStrings &nameFilters, QStrings &files, bool includeDir = false);
QString getValidFileName(const QString &fileName);

bool createDir(const QString &path);
bool forceDirectories(const QString &path);
bool directoryExists(const QString &path);

QString extractFilePath(const QString &fileName);
QString extractFileDir(const QString &fileName);
QString extractFileName(const QString &fileName);
QString extractFileNameOnly(const QString &fileName);
QString expandFileName(const QString &fileName);
int pathDelimPos(const QString &fileName);
void fileSetReadOnly(const QString &fileName, bool readOnly = true);

qint64 getFileSize(const QString &fileName);

// 取得运行命令行的输出:默认的codepage为Local8Bit(中文操作系统为936)
QString getCommandLineOutput(
    const QString &commandLine, const QString &workDir, int &exitCode);

QString loadQssFile(const QString &fileName);
#endif // ITFILEUTILS_H
