#include "ITLog.h"
#include <iostream>
#include <time.h>
#include <stdio.h>

ITLogMessage::ITLogMessage(char* file, int line, LogLevel level)
{
	m_level = level;
	time_t stamp = time(0);
	tm theTm;
	localtime_s(&theTm, &stamp);
	//s_mutex.lock();
	m_msgTemp = new std::stringstream();
	*m_msgTemp << "[" << file << " row:" << line <<" " <<
		theTm.tm_hour << ":" << theTm.tm_min << ":" << theTm.tm_sec <<"]£º ";
	//s_mutex.unlock();
}

ITLogMessage::~ITLogMessage()
{
	write();
}

void ITLogMessage::write()
{
	if (!s_logLevel & m_level)
	{
		return;
	}
	
//	s_mutex.lock();
	switch (s_logMode)
	{
	case Console:
		writeConsole();
		break;
	case LogFile:
		writeLogFile();
		break;
	case AllMode:
		writeConsole();
		writeLogFile();
		break;
	default:
		break;
	}
//	s_mutex.unlock();
}

void ITLogMessage::writeLogFile()
{
	auto strInfo = m_msgTemp->str();
	s_logFile << strInfo << std::endl;
}

void ITLogMessage::writeConsole()
{
	auto strInfo = m_msgTemp->str();
	std::cout << strInfo << std::endl;
}

void ITLoger::initLog(const std::string& logDir)
{
	time_t cuTime = time(nullptr);
	tm theTm;
	localtime_s(&theTm, &cuTime);
	theTm.tm_year;
	theTm.tm_mon;
	std::string strTime;
	char charTime[20];
	strftime(charTime, 18, "%Y-%m-%d", &theTm);
	std::string strFilePath = logDir + charTime + ".log";
	s_logFile.open(strFilePath, std::ios::out | std::ios::app);
	
	if (s_logFile.is_open())
	{
		return;
	}
	std::cout << "open log file failed!" << std::endl;
}

void ITLoger::setOutMode(const ITLogMode mode)
{
	s_logMode = mode;
}

void ITLoger::setOutLevel(int level)
{
	s_logLevel = level;
}
