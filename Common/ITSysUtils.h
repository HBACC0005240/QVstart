#ifndef ITSYSUTILS_H
#define ITSYSUTILS_H
#include <QChar>
#include <QString>


QString includeTrailingBackslash(const QString &s);
QString includeTrailingPathDelimiter(const QString &s);
QString excludeTrailingBackslash(const QString &s);
QString excludeTrailingPathDelimiter(const QString &s);
QChar pathDelim();
QChar driveDelim();
QChar backSlashDelim();
bool isPathDelimiter(const QString &s, int index);

double fileDateToDateTime(int fileDate);
int DateTimeToFileDate(double value);

QString getUserNameDef();
QString getHostName();
unsigned getCoreCount();
QString getMacString();
QString getCPUIdString();

//�˷�����win 8��win 10�»�ȡ�������ȷ,����win 7���ֵ����ϻ�ȡ�������,����ʹ��getPhysicalDriveSerialNumber����
QString getDiskSerialNoString();

QString getPhysicalDriveSerialNumber();
QString getComputerGUID();
QString valueFromRegistry(const QString &regPath, const QString &regKey);
QString environmentVariable(const QString &name);
bool setEnvironmentVariable(const QString &name, const QString &value);
QString getUserDocumentsPath();
QString getUserAppDataPath();
qint64 getAvailPhysMem();
unsigned long memoryUsage();

QString getSpecialFolderPath(int CSIDL);

#endif // ITSYSUTILS_H
