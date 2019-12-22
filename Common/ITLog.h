#ifndef ITLOG_H
#define ITLOG_H
#include <fstream>
#include <sstream>
//#include <mutex>

enum LogLevel
{
	None	= 1,
	Info	= 1 << 1,
	Warning = 1 << 2,
	Error	= 1 << 3,
	AllLevel= Info | Warning | Error
};

enum ITLogMode
{
	Console = 1,
	LogFile = 1 << 1,
	AllMode = Console | LogFile
};

static std::ofstream s_logFile;
static int s_logLevel = AllLevel;
static ITLogMode s_logMode = AllMode;
//static std::mutex s_mutex;

class ITLogMessage
{
public:
	ITLogMessage(char* file, int line, LogLevel level);
	~ITLogMessage();

	std::stringstream& logStream() { return *m_msgTemp; }

	void write();

private:
	//向log文件中写入
	void writeLogFile();

	void writeConsole();

private:
	LogLevel m_level;
	std::stringstream* m_msgTemp;
};

class ITLoger
{
public:
	static void initLog(const std::string& logDir);

	//none 采用截断模式
	static void clearLog() {};

	//设置log显示方式
	static void setOutMode(const ITLogMode mode);

	//设置log输出级别
	static void setOutLevel(int level);

};

#define ITMSG_Error ITLogMessage( __FILE__, __LINE__, Error)
#define ITMSG_Warning ITLogMessage( __FILE__, __LINE__, Warning)
#define ITMSG_Info ITLogMessage( __FILE__, __LINE__, Info)

#define ITLOG(msg) MSG_## msg.logStream()

#define ITLOG_Error ITLOG(Error)
#define ITLOG_Warning ITLOG(Warning)
#define ITLOG_Info ITLOG(Info)

#endif//ITLOG_H