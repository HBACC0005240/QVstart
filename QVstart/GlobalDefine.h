#pragma once

#define UserCfgPath "User/"


static QString ReadIniValString(const QString& strSection,const QString& strKeyword,const QString& strDefault,const QString& strFileName)
{
	TCHAR Buffer[2048];
	GetPrivateProfileString(strSection.toStdWString().c_str(), strKeyword.toStdWString().c_str(),\
		strDefault.toStdWString().c_str(), Buffer, sizeof(Buffer), strFileName.toStdWString().c_str());
	return QString::fromStdWString(Buffer);
}