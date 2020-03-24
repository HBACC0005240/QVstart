#include "ITSysUtils.h"

#include <QStandardPaths>
#include <QVector>
#include <QSettings>
#include <QDir>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include "ITStrUtils.h"
#ifdef WIN32
#   include <windows.h>
#   include <nb30.h>
#   include <ShlObj.h>
#   include <memory>
#   ifdef _MSC_VER
#       pragma comment(lib, "NETAPI32.LIB")
#   endif
#else
#   include <unistd.h>
//#   include <sys/sysconf.h>
#   include <sys/ioctl.h>
#   include <sys/socket.h>
#   include <netinet/in.h>
#   include <net/if.h>
#   include <stdio.h>
#endif

#if defined(__GNUC__)    // GCC
#include <cpuid.h>
#endif

#if _MSC_VER >=1400    // VC2005才支持intrin.h
#include <intrin.h>    // 所有Intrinsics函数
#endif

#ifdef WIN32
const QChar c_GLDPathDelim = 0x5c; // '\\'
const QChar c_GLDPathDelim_Linux = '/'; // '\\'
const QChar c_GLDDriveDelim = 0x3a; // ':'
#else
const QChar c_GLDPathDelim = 0x2f; // '/'
const QChar c_GLDPathDelim_Linux = '/'; // '\\'
const QChar c_GLDDriveDelim = 0x00; // ''
#endif

char HardDriveSerialNumber[MAX_PATH];

#define  MAX_IDE_DRIVES           16
#define  DFP_GET_VERSION          0x00074080
#define  DFP_RECEIVE_DRIVE_DATA   0x0007c088
#define  IDE_ATAPI_IDENTIFY       0xA1
#define  IDE_ATA_IDENTIFY         0xEC

typedef struct _GETVERSIONOUTPARAMS
{
    BYTE bVersion;       // Binary driver version.
    BYTE bRevision;      // Binary driver revision.
    BYTE bReserved;      // Not used.
    BYTE bIDEDeviceMap;  // Bit map of IDE devices.
    DWORD fCapabilities; // Bit mask of driver capabilities.
    DWORD dwReserved[4]; // For future use.
} GETVERSIONOUTPARAMS, *PGETVERSIONOUTPARAMS, *LPGETVERSIONOUTPARAMS;

BYTE IdOutCmd[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];

QChar pathDelim()
{
    return c_GLDPathDelim;
}

QChar driveDelim()
{
    return c_GLDDriveDelim;
}

QChar backSlashDelim()
{
    return 0x2f; // '/'
}

bool isPathDelimiter(const QString &s, int index)
{
    return (index > 0) && (index < s.length()) && ((s.at(index) == c_GLDPathDelim) || (s.at(index) == c_GLDPathDelim_Linux));
}

QString includeTrailingBackslash(const QString &s)
{
    return includeTrailingPathDelimiter(s);
}

QString includeTrailingPathDelimiter(const QString &s)
{
    QString result = s;
    if (!isPathDelimiter(s, s.length() - 1))
    {
        result += c_GLDPathDelim;
    }
    return result;
}

QString excludeTrailingBackslash(const QString &s)
{
    return excludeTrailingPathDelimiter(s);
}

QString excludeTrailingPathDelimiter(const QString &s)
{
    QString result = s;
    if (isPathDelimiter(s, s.length() - 1))
        result.chop(1);
    return result;
}

double fileDateToDateTime(int fileDate)
{
    int nYear(0);
    int nMonth(0);
    int nDay(0);
    int nHour(0);
    int nMin(0);
    int nSec(0);
    int nHi(0);
    int nLow(0);
    nHi = (fileDate & 0xffff0000) >> 16;
    nYear = (nHi >> 9) + 1980;
    nMonth = (nHi >> 5) & 15;
    nDay = (nHi & 31);
    nLow = fileDate & 0x0000ffff;
    nHour = nLow >> 11;
    nMin = (nLow >> 5) & 63;
    nSec = (nLow & 31) << 1;
    return dateTimeToDouble(QDateTime(QDate(nYear, nMonth, nDay), QTime(nHour, nMin, nSec)));
}

int DateTimeToFileDate(double value)
{
    int nResult = 0;
    int nYear(0);
    int nMonth(0);
    int nDay(0);
    int nHour(0);
    int nMin(0);
    int nSec(0);
    QDateTime dateTime = doubleToDateTime(value);
    QDate date = dateTime.date();
    QTime time = dateTime.time();
    if ((yearOf(value) < 1980) || (yearOf(value) > 2107))
        nResult = 0;
    else
    {
        nYear = date.year();
        nMonth = date.month();
        nDay = date.day();
        nHour = time.hour();
        nMin = time.minute();
        nSec = time.second();
        nResult |= ((nSec >> 1) | (nMin << 5) | (nHour << 11)) & 0x0000ffff;
        nResult |= ((nDay | (nMonth << 5) | (nYear - 1980) << 9)) << 16;
    }
    return nResult;
}

QString getUserNameDef()
{
#ifdef _MSC_VER
    char *pBuff;
    size_t nLen;

    if (0 == _dupenv_s(&pBuff, &nLen, "USERNAME"))
    {
        QString sName(pBuff);
        free(pBuff);

        return sName;
    }

    free(pBuff);
    return QString("");
#else
    return QString(getenv("USER"));
#endif
}

QString getHostName()
{
    char szAddr[255] = { '\0' };

#ifdef Q_OS_WIN
    unsigned long uSize = 255;
    GetComputerNameA(szAddr, &uSize);
#else
    gethostname(szAddr, sizeof(szAddr));
#endif

    return QString(szAddr);
}

unsigned getCoreCount()
{
    unsigned uCount = 1; // 至少一个

#ifdef Q_OS_WIN
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    uCount = si.dwNumberOfProcessors;
#else
    uCount = sysconf(_SC_NPROCESSORS_CONF);
#endif

    return uCount;
}

/****************************************************************************************************
  作者： ruanlz 2015-07-14
  函数名称：getCPUIdString
  返回： QString
  功能： 获取cpuID
  备注： 使用__cpuid函数获取cpuid,对于不支持__cpuid函数的win32下的编译器使用了内联汇编实现__cpuid函数
        在windows下使用wmic命令做了验证，非windows平台在ubuntu 12.04.01和maxos 10.9上做了验证但因为
        是在虚拟机上运行，硬件信息不能验证,所以准确性不能定论。
  注意： cpu序列号不唯一，相同型号的cpu的cpu序列号可能相同
  处理器：Intel 486以上和AMD am486以上的X86架构的处理器，不支持除X86以外架构的处理器
****************************************************************************************************/

#if defined(_WIN64)
// 64位下不支持内联汇编. 应使用__cpuid、__cpuidex等Intrinsics函数。
#elif defined(WIN32)
#if _MSC_VER < 1600    // VS2010. 据说VC2008 SP1之后才支持__cpuidex
void __cpuidex(INT32 CPUInfo[4], INT32 InfoType, INT32 ECXValue)
{
    if (NULL==CPUInfo)    return;
    _asm{
        // load. 读取参数到寄存器
        mov edi, CPUInfo;    // 准备用edi寻址CPUInfo
        mov eax, InfoType;
        mov ecx, ECXValue;
        // CPUID
        cpuid;
        // save. 将寄存器保存到CPUInfo
        mov    [edi], eax;
        mov    [edi+4], ebx;
        mov    [edi+8], ecx;
        mov    [edi+12], edx;
    }
}
#endif    // #if _MSC_VER < 1600    // VS2010. 据说VC2008 SP1之后才支持__cpuidex

#if _MSC_VER < 1400    // VC2005才支持__cpuid
void __cpuid(INT32 CPUInfo[4], INT32 InfoType)
{
    __cpuidex(CPUInfo, InfoType, 0);
}
#endif    // #if _MSC_VER < 1400    // VC2005才支持__cpuid

#endif    // #if defined(_WIN64)

QString getCPUIdString()
{
#ifdef Q_OS_WIN
    QString sCpuid;//存储cpuid的字符串
    INT32 nCpuid[4];//存储寄存器数据

    //获取cpuid
    __cpuid(nCpuid,0x01);

    //把结果格式化进入字符串
    char pbufer[17];
    sprintf_s(pbufer,17,"%.8X%.8X",nCpuid[3],nCpuid[0]);//格式化字符串
    sCpuid = QString(QLatin1String(pbufer));//将char转换成QString
    return sCpuid;
#else
    /*在ubuntu 12.04.1上测试可以获取到cpuid号，但因为在虚拟机上运行的Linux，硬件是虚拟的，不能保证绝对正确*/
//#define cpuid(in,a,b,c,d) asm("cpuid":"=a"(a),"=b"(b),"=c"(c),"=d"(d):"a"(in));
    //定义AT&T风格的汇编代码，用来完成cpuid命令。
    int eax,ebx,ecx,edx;//存储寄存器的内容
    QString sCpuid;//存储cpuid的字符串
    __cpuid(1,eax,ebx,ecx,edx);
    char pbufer[17];
    sprintf(pbufer, "%.8X%.8X",edx,eax);//格式化字符串
    sCpuid = QString(GLatin1String(pbufer));//将char转换成QString
    return sCpuid;
#endif
}


/****************************************************************************************************
  作者： litz-a 2016-02-18
  函数名称：getPhysicalDriveSerialNumber
  返回： QString
  功能： 获取系统的第一块硬盘的序列号
  操作系统：支持windows95及以上版本的windows操作系统，暂不支持其他操作系统。
****************************************************************************************************/
#ifdef Q_OS_WIN
char *convertToString(DWORD diskdata[256], int firstIndex, int lastIndex, char* buf)
{
    int position = 0;

    for (int index = firstIndex; index <= lastIndex; index++)
    {
        buf[position++] = (char)(diskdata[index] / 256);
        buf[position++] = (char)(diskdata[index] % 256);
    }

    buf[position] = '\0';

    for (int index = position - 1; index > 0 && isspace(buf[index]); index--)
    {
        buf[index] = '\0';
    }

    return buf;
}

void printIdeInfo(int drive, DWORD diskdata[256])
{
    Q_UNUSED(drive);
    char serialNumber[MAX_PATH];
    char bufferSize[32];

    convertToString(diskdata, 10, 19, serialNumber);
    sprintf_s(bufferSize, sizeof(bufferSize), "%u", diskdata[21] * 512);

    if (0 == HardDriveSerialNumber[0] && (isalnum(serialNumber[0]) || isalnum(serialNumber[19])))
    {
        strcpy_s(HardDriveSerialNumber, sizeof(HardDriveSerialNumber), serialNumber);
    }
}

BOOL doIdentify(HANDLE hPhysicalDriveIOCTL, PSENDCMDINPARAMS pSCIP,
    PSENDCMDOUTPARAMS pSCOP, BYTE bIDCmd, BYTE bDriveNum,
    PDWORD lpcbBytesReturned)
{
    // Set up data structures for IDENTIFY command.
    pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;
    pSCIP->irDriveRegs.bFeaturesReg = 0;
    pSCIP->irDriveRegs.bSectorCountReg = 1;
    pSCIP -> irDriveRegs.bSectorNumberReg = 1;
    pSCIP->irDriveRegs.bCylLowReg = 0;
    pSCIP->irDriveRegs.bCylHighReg = 0;

    // Compute the drive number.
    pSCIP->irDriveRegs.bDriveHeadReg = 0xA0 | ((bDriveNum & 1) << 4);

    // The command can either be IDE identify or ATAPI identify.
    pSCIP->irDriveRegs.bCommandReg = bIDCmd;
    pSCIP->bDriveNumber = bDriveNum;
    pSCIP->cBufferSize = IDENTIFY_BUFFER_SIZE;

    return (DeviceIoControl(hPhysicalDriveIOCTL, DFP_RECEIVE_DRIVE_DATA,
                            (LPVOID)pSCIP,
                            sizeof(SENDCMDINPARAMS) - 1,
                            (LPVOID)pSCOP,
                            sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1,
                            lpcbBytesReturned,
                            NULL));
}

int getPhysicalDriveInNTWithAdminRights()
{
    int done = FALSE;
    int drive = 0;

    for (drive = 0; drive < MAX_IDE_DRIVES; drive++)
    {
        HANDLE hPhysicalDriveIOCTL = 0;

        wchar_t driveName[MAX_PATH] = { 0 };
        swprintf_s(driveName, MAX_PATH, L"\\\\.\\PhysicalDrive%d", drive);

        hPhysicalDriveIOCTL = CreateFile(driveName,
                                         GENERIC_READ | GENERIC_WRITE,
                                         FILE_SHARE_READ | FILE_SHARE_WRITE,
                                         NULL,
                                         OPEN_EXISTING,
                                         0,
                                         NULL);

        if (hPhysicalDriveIOCTL == INVALID_HANDLE_VALUE)
        {

        }
        else
        {
            GETVERSIONOUTPARAMS VersionParams;
            DWORD cbBytesReturned = 0;

            memset((void*)&VersionParams, 0, sizeof(VersionParams));

            if (!DeviceIoControl(hPhysicalDriveIOCTL,
                                 DFP_GET_VERSION,
                                 NULL,
                                 0,
                                 &VersionParams,
                                 sizeof(VersionParams),
                                 &cbBytesReturned,
                                 NULL))
            {

            }

            if (VersionParams.bIDEDeviceMap > 0)
            {
                BYTE bIDCmd = 0;
                SENDCMDINPARAMS scip;
                bIDCmd = (VersionParams.bIDEDeviceMap >> drive & 0x10) ? IDE_ATAPI_IDENTIFY : IDE_ATA_IDENTIFY;

                memset(&scip, 0, sizeof(scip));
                memset(IdOutCmd, 0, sizeof(IdOutCmd));

                if (doIdentify(hPhysicalDriveIOCTL,
                               &scip,
                               (PSENDCMDOUTPARAMS)&IdOutCmd,
                               (BYTE)bIDCmd,
                               (BYTE)drive,
                                &cbBytesReturned))
                {
                    DWORD diskdata[256];

                    USHORT *pIdSector = (USHORT *)((PSENDCMDOUTPARAMS)IdOutCmd)->bBuffer;

                    for (int index = 0; index < 256; index++)
                    {
                        diskdata[index] = pIdSector[index];
                    }

                    printIdeInfo(drive, diskdata);

                    done = TRUE;
                }
            }

            CloseHandle(hPhysicalDriveIOCTL);
        }
    }

    return done;
}

QString getPhysicalDriveSerialNumber()
{
    if(getPhysicalDriveInNTWithAdminRights())
    {
        return QString(HardDriveSerialNumber).trimmed();
    }

    DWORD dwResult = NO_ERROR;

    // call CreateFile to get a handle to physical drive
    HANDLE hDevice = ::CreateFile(L"\\\\.\\PHYSICALDRIVE0",
                                  0,
                                  FILE_SHARE_READ | FILE_SHARE_WRITE,
                                  NULL,
                                  OPEN_EXISTING,
                                  0,
                                  NULL);

    std::shared_ptr<void> spHandle(hDevice, CloseHandle);

    if (INVALID_HANDLE_VALUE == spHandle.get())
    {
        return QString("");
    }

    // set the input STORAGE_PROPERTY_QUERY data structure
    STORAGE_PROPERTY_QUERY storagePropertyQuery;
    ZeroMemory(&storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY));
    storagePropertyQuery.PropertyId = StorageDeviceProperty;
    storagePropertyQuery.QueryType = PropertyStandardQuery;

    // get the necessary output buffer size
    STORAGE_DESCRIPTOR_HEADER storageDescriptorHeader = { 0 };
    DWORD dwBytesReturned = 0;
    if (!::DeviceIoControl(spHandle.get(), IOCTL_STORAGE_QUERY_PROPERTY,
        &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        &storageDescriptorHeader, sizeof(STORAGE_DESCRIPTOR_HEADER),
        &dwBytesReturned, NULL))
    {
        dwResult = ::GetLastError();
        return QString("");
    }

    // allocate the necessary memory for the output buffer
    const DWORD dwOutBufferSize = storageDescriptorHeader.Size;
    char* pOutBuffer = new char[dwOutBufferSize];
    ZeroMemory(pOutBuffer, dwOutBufferSize);

    // get the storage device descriptor
    if (!::DeviceIoControl(spHandle.get(), IOCTL_STORAGE_QUERY_PROPERTY,
        &storagePropertyQuery, sizeof(STORAGE_PROPERTY_QUERY),
        pOutBuffer, dwOutBufferSize,
        &dwBytesReturned, NULL) || (0 == dwBytesReturned))
    {
        dwResult = ::GetLastError();
        delete[]pOutBuffer;
        return QString("");
    }

    // Now, the output buffer points to a STORAGE_DEVICE_DESCRIPTOR structure
    // followed by additional info like vendor ID, product ID, serial number, and so on.
    STORAGE_DEVICE_DESCRIPTOR* pDeviceDescriptor = (STORAGE_DEVICE_DESCRIPTOR*)pOutBuffer;
    const DWORD dwSerialNumberOffset = pDeviceDescriptor->SerialNumberOffset;

    QString strSerialNumber("");

    if (dwSerialNumberOffset != 0)
    {
        // finally, get the serial number
        strSerialNumber = QString(pOutBuffer + dwSerialNumberOffset);
    }

    // perform cleanup and return
    delete[] pOutBuffer;

    return strSerialNumber.trimmed();
}
#else
//非windows操作系统统一返回空字符串
QString getPhysicalDriveSerialNumber()
{
    return QString("");
}
#endif

/****************************************************************************************************
  作者： ruanlz 2015-07-14
  函数名称：getDiskSerialNoString
  返回： QString
  功能： 获取系统的第一块硬盘的序列号，并不一定是c盘或者系统盘所在的硬盘
  注意： 获取硬盘id时，程序必须有管理员权限才能获取，否则返回空
  操作系统：支持windows95及以上版本的windows操作系统，暂不支持其他操作系统。
  警告： 此方法在win 8和win 10下获取结果不正确,且在win 7部分电脑上获取结果乱码,
        建议使用getPhysicalDriveSerialNumber方法(added by litz-a)
****************************************************************************************************/
#ifdef Q_OS_WIN
//把WORD数组调整字节序为little-endian，并滤除字符串结尾的空格。
void ToLittleEndian(PUSHORT pWords, int nFirstIndex, int nLastIndex, LPTSTR pBuf)
{
    int index;
    LPTSTR pDest = pBuf;
    for(index = nFirstIndex; index <= nLastIndex; ++index)
    {
        pDest[0] = pWords[index] >> 8;
        pDest[1] = pWords[index] & 0xFF;
        pDest += 2;
    }
    *pDest = 0;

    //trim space at the endof string; 0x20: _T(' ')
    --pDest;
    while(*pDest == 0x20)
    {
        *pDest = 0;
        --pDest;
    }
}

//滤除字符串起始位置的空格
void TrimStart(LPTSTR pBuf)
{
    if(*pBuf != 0x20)
    {
        return;
    }

    LPTSTR pDest = pBuf;
    LPTSTR pSrc = pBuf + 1;
    while(*pSrc == 0x20)
        ++pSrc;

    while(*pSrc)
    {
        *pDest = *pSrc;
        ++pDest;
        ++pSrc;
    }
    *pDest = 0;
}

QString getDiskSerialNoString()
{
    TCHAR  szSerialNo[24];
    BYTE IdentifyResult[sizeof(SENDCMDOUTPARAMS) + IDENTIFY_BUFFER_SIZE - 1];
    DWORD dwBytesReturned;
    GETVERSIONINPARAMS get_version;
    SENDCMDINPARAMS send_cmd = { 0 };

    HANDLE hFile = CreateFile(L"\\\\.\\PHYSICALDRIVE0", GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        return QString("");
    }

    //get version
    DeviceIoControl(hFile, SMART_GET_VERSION, NULL, 0,
                    &get_version, sizeof(get_version), &dwBytesReturned, NULL);
    //identify device

    //send_cmd.irDriveRegs.bCommandReg = (get_version.bIDEDeviceMap & 0x10)? ATAPI_ID_CMD : ID_CMD;
    //说明： 当以ATAPI_ID_CMD的形式去获取硬盘信息时会获取不到，ID_CMD则可以获取，暂时测得电脑上还没有测出错误，
    //      暂时对这个问题没有更好的解决方法，所以暂时先改为都已ID_CMD的命令格式去获取硬盘信息。
    send_cmd.irDriveRegs.bCommandReg = (get_version.bIDEDeviceMap & 0x10)? ID_CMD : ID_CMD;
    DeviceIoControl(hFile, SMART_RCV_DRIVE_DATA, &send_cmd, sizeof(SENDCMDINPARAMS) - 1,
                    IdentifyResult, sizeof(IdentifyResult), &dwBytesReturned, NULL);
    CloseHandle(hFile);

    //获取结果
    PUSHORT pWords = (USHORT*)(((SENDCMDOUTPARAMS*)IdentifyResult)->bBuffer);

    ToLittleEndian(pWords, 10, 19, szSerialNo);
    TrimStart(szSerialNo);
    QString sDiskSerialNo;
    sDiskSerialNo = QString::fromWCharArray(szSerialNo);
    return sDiskSerialNo;
}
#else
//非windows操作系统统一返回空字符串
QString getDiskSerialNoString()
{
    return QString("");
}
#endif

/****************************************************************************************************
  作者： ruanlz 2015-07-14
  函数名称：getComputerGUID
  返回： QString
  功能： 获取电脑唯一标示，返回结果是32位的字符串
  注意： 因为依赖于getDiskSerialNoString函数，所以在没有管理员权限下返回的磁盘序列号可能
        是空的，在有管理员权限和没有管理员权限的情况下，此函数的返回值可能不一样。
****************************************************************************************************/
#ifdef Q_OS_WIN
QString getComputerGUID()
{
    QString sCpuid,sDiskSerialNo;
    QString sComputerGUID;

    //获取cpuid和磁盘序列号
    sCpuid = getCPUIdString();
    sDiskSerialNo = getDiskSerialNoString();
    sComputerGUID = sCpuid + sDiskSerialNo;
    return sComputerGUID;
}
#endif


#ifdef Q_OS_WIN
unsigned getNetworkCardCount()
{
    LANA_ENUM leAdapt;
    NCB ncb;
    memset(&ncb, 0, sizeof(ncb));

    ncb.ncb_command = NCBENUM;
    ncb.ncb_buffer = (unsigned char*)&leAdapt;
    ncb.ncb_length = sizeof(leAdapt);

    if (Netbios(&ncb) == 0)
    {
        return leAdapt.length;
    }

    return 0;
}

#endif

QString getMacString()
{
#ifdef Q_OS_WIN

    //int nCount = getNetworkCardCount();
    NCB ncb;
    ADAPTER_STATUS adapt;

    QVector<QString> vecRes;
    memset(&ncb, 0, sizeof(ncb));

    UCHAR uRetCode;
    LANA_ENUM   lenum;
    ncb.ncb_command  =  NCBENUM;
    ncb.ncb_buffer  =  (UCHAR  * ) & lenum;
    ncb.ncb_length  =   sizeof (lenum);
    uRetCode  =  Netbios(  & ncb );

    for (int i = 0; i < lenum.length; ++i)
    {
        memset(  & ncb,  0 ,  sizeof (ncb) );
        ncb.ncb_command  =  NCBRESET;
        ncb.ncb_lana_num  =  lenum.lana[i];
        uRetCode  =  Netbios(&ncb);
        if (NRC_GOODRET != uRetCode)
        {
            continue;
        }
        memset(&ncb, 0 , sizeof(ncb));
        ncb.ncb_command = NCBASTAT;
        ncb.ncb_lana_num = lenum.lana[i];
        strcpy_s((char*)ncb.ncb_callname, sizeof(ncb.ncb_callname), "*");
        ncb.ncb_buffer = (unsigned char*)&adapt;
        ncb.ncb_length = sizeof(adapt);

        char szBuff[128] = { '\0' };

        Netbios(&ncb);
#ifdef _MSC_VER
        sprintf_s(
#else
        sprintf(
#endif
                szBuff, "%02X-%02X-%02X-%02X-%02X-%02X\r\n",
                adapt.adapter_address[0],
                adapt.adapter_address[1],
                adapt.adapter_address[2],
                adapt.adapter_address[3],
                adapt.adapter_address[4],
                adapt.adapter_address[5]);

        vecRes.push_back(QString(szBuff));
    }

    if (vecRes.size() > 0)
    {
        return vecRes[0];
    }
#else
    struct ifreq ifreq;
    int sock;
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) > 0)
    {
         strcpy(ifreq.ifr_name, "");
         if (ioctl(sock, SIOCGIFADDR, &ifreq) > 0)
         {
             char szBuff[128] = { '\0' };
             sprintf(szBuff, "%02X-%02X-%02X-%02X-%02X-%02X\r\n",
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[0],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[1],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[2],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[3],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[4],
                     (unsigned char)ifreq.ifr_ifru.ifru_addr.sa_data[5]);

             return QString(szBuff);
         }
    }
#endif

    return QString("");
}

/****************************************************************************************************
  作者： yanyq-a 2013-07-30
  参数： const QString&, const QString&
  返回： QString
  功能： 读取注册表相应键值(对应原GrandFileUtils::GetShellFolderPath)
****************************************************************************************************/
QString valueFromRegistry(const QString &regPath, const QString &regKey)
{
    QSettings oSetting(regPath, QSettings::NativeFormat);
    QString result = oSetting.value(regKey, "").toString();
    if ((result.length() > 0) && !((result.right(1) == "\\") || result.right(1) == "/"))
    {
        result += "/";
    }
    return QDir::fromNativeSeparators(result);
}

QString environmentVariable(const QString &envVAR)
{
    QByteArray vardir = qgetenv(envVAR.toStdString().data());

    // 有可能没有此环境变量，返回空
    return vardir;
}

bool setEnvironmentVariable(const QString &name, const QString &value)
{
    // todo
    return false;
    Q_UNUSED(name)
	Q_UNUSED(value)
}

/****************************************************************************************************
  作者： yanyq-a 2013-07-30
  参数： 无
  返回： QString
  功能： 获取当前用户的文档目录
****************************************************************************************************/
QString getUserDocumentsPath()
{
    return QDir::fromNativeSeparators(QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation).append('/'));
}

/****************************************************************************************************
  作者： yanyq-a 2013-07-30
  参数： 无
  返回： QString
  功能： 获取当前用户的应用程序数据目录
****************************************************************************************************/
QString getUserAppDataPath()
{
#ifdef WIN32
    return getSpecialFolderPath(CSIDL_APPDATA);
#else
    return QString();
#endif
}

/****************************************************************************************************
  作者： yanyq-a 2013-08-09
  参数： 无
  返回： qint64
  功能： 可用物理内存
****************************************************************************************************/
qint64 getAvailPhysMem()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX oMemory;
    oMemory.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&oMemory);
    return oMemory.ullAvailPhys;
#else
    FILE *pfd;
    char *pend;
    qint64 nFree = 0;
    char szBuff[256] = { '\0' };

    pfd = fopen("/proc/meminfo", "r");

    while (true)
    {
        memset(szBuff, 0, 256);
        pend = fgets(szBuff, 256, pfd);

        if (NULL == pend) break;
        if (strncmp(szBuff, "MemFree", 7) == 0)
        {
            nFree = atoll(szBuff);
            break;
        }
    }

    return nFree;
#endif
}

/**************************************************************************
  作者： yanyq-a 2013-08-09
  参数： 无
  返回： unsigned long
  功能： 物理内存使用率
**************************************************************************/
unsigned long memoryUsage()
{
#ifdef Q_OS_WIN
    MEMORYSTATUSEX oMemory;
    oMemory.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&oMemory);
    return oMemory.dwMemoryLoad;
#else
    FILE *pfd;
    char *pend;
    qint64 nTotal = 0;
    qint64 nFree = 0;
    char szBuff[256] = { '\0' };

    pfd = fopen("/proc/meminfo", "r");

    while (true)
    {
        memset(szBuff, 0, 256);
        pend = fgets(szBuff, 256, pfd);

        if (NULL == pend) break;
        if (strncmp(szBuff, "MemTotal", 8) == 0)
        {
            nTotal = atoll(szBuff);
        }
        if (strncmp(szBuff, "MemFree", 7) == 0)
        {
            nFree = atoll(szBuff);
        }
    }

    if (nTotal <= 0)
    {
        return 0;
    }
    else
    {
        return ((nTotal - nFree) * 100) / nTotal;
    }
#endif
}

QString getSpecialFolderPath(int CSIDL)
{
#ifdef WIN32
    wchar_t path[MAX_PATH];
    if (SHGetSpecialFolderPath(0, path, CSIDL, FALSE))
        return QDir::fromNativeSeparators(QString::fromWCharArray(path).append('/'));
    else
        return QString();
#else
    return QString();
#endif
}
