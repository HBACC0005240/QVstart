#pragma once
#include <windows.h>
#include <vector>
#include <string>
using namespace std;

enum CharType
{
	Type_Number,
	Type_Period,
	Type_String
};
//ANSI转化成UNICODE
static LPWSTR ANSITOUNICODE(const char* pBuf)
{
	int lenA = lstrlenA(pBuf);
	int lenW=0;
	LPWSTR lpszFile;
	lenW = MultiByteToWideChar(CP_ACP,0,pBuf,lenA,0,0);
	if(lenW > 0)
	{
		lpszFile = SysAllocStringLen(0,lenW);
		MultiByteToWideChar(CP_ACP,0,pBuf,lenA,lpszFile,lenW);
	}
	return lpszFile;
}
static wchar_t* AnsiToUnicode( const char* szStr )
{
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, NULL, 0 );
	if (nLen == 0)
	{
		return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, szStr, -1, pResult, nLen );
	return pResult;
}


static CharType ClassifyChar(char c)
{
	if ( c == '.' )
		return Type_Period;
	else if ( c >= '0' && c <= '9' )
		return Type_Number;
	else
		return Type_String;
}

// Split version string into individual components. A component is continuous
// run of characters with the same classification. For example, "1.20rc3" would
// be split into ["1",".","20","rc","3"].
static vector<string> SplitVersionString(const string& version)
{
	vector<string> list;

	if ( version.empty() )
		return list; // nothing to do here

	string s;
	const size_t len = version.length();

	s = version[0];
	CharType prevType = ClassifyChar(version[0]);

	for ( size_t i = 1; i < len; i++ )
	{
		const char c = version[i];
		const CharType newType = ClassifyChar(c);

		if ( prevType != newType || prevType == Type_Period )
		{
			// We reached a new segment. Period gets special treatment,
			// because "." always delimiters components in version strings
			// (and so ".." means there's empty component value).
			list.push_back(s);
			s = c;
		}
		else
		{
			// Add character to current segment and continue.
			s += c;
		}

		prevType = newType;
	}

	// Don't forget to add the last part:
	list.push_back(s);

	return list;
}


/// Helper class for RIIA handling of allocated buffers
struct DataBuffer
{
	DataBuffer(size_t size)
	{
		data = new unsigned char[size];
		memset(data, 0, size);
	}

	~DataBuffer() { delete[] data; }

	unsigned char *data;
};


// Simple conversion between wide and narrow strings (only safe for ASCII!):

template<typename TIn, typename TOut>
inline std::basic_string<TOut> ConvertString(const std::basic_string<TIn>& s)
{
	std::basic_string<TOut> out;
	out.reserve(s.length());

	for ( typename std::basic_string<TIn>::const_iterator i = s.begin(); i != s.end(); ++i )
	{
		out += static_cast<TOut>(*i);
	}

	return out;
}

inline std::string WideToAnsi(const std::wstring& s)
{
	return ConvertString<wchar_t, char>(s);
}

inline std::wstring AnsiToWide(const std::string& s)
{
	return ConvertString<char, wchar_t>(s);
}


// Checking of Windows version

inline bool IsWindowsVistaOrGreater()
{
	OSVERSIONINFOEXW osvi = { sizeof(osvi), 0, 0, 0, 0, { 0 }, 0, 0 };
	DWORDLONG const dwlConditionMask = VerSetConditionMask(
		VerSetConditionMask(
		VerSetConditionMask(
		0, VER_MAJORVERSION, VER_GREATER_EQUAL),
		VER_MINORVERSION, VER_GREATER_EQUAL),
		VER_SERVICEPACKMAJOR, VER_GREATER_EQUAL);
	osvi.dwMajorVersion = HIBYTE(_WIN32_WINNT_VISTA);
	osvi.dwMinorVersion = LOBYTE(_WIN32_WINNT_VISTA);
	osvi.wServicePackMajor = 0;

	return VerifyVersionInfoW(&osvi, VER_MAJORVERSION | VER_MINORVERSION | VER_SERVICEPACKMAJOR, dwlConditionMask) != FALSE;
}


// Dynamic loading of symbols that may be unavailable on earlier
// versions of Windows

template<typename T>
inline T* LoadDynamicFunc(const char *func, const char *dll)
{
	return reinterpret_cast<T*>(GetProcAddress(GetModuleHandleA(dll), func));
}

#define LOAD_DYNAMIC_FUNC(func, dll) \
	LoadDynamicFunc<decltype(func)>(#func, #dll)


static void string_replace(string&s1,const string&s2,const string&s3)
{
	string::size_type pos=0;
	string::size_type a=s2.size();
	string::size_type b=s3.size();
	while((pos=s1.find(s2,pos))!=string::npos)
	{
		s1.replace(pos,a,s3);
		pos+=b;
	}
}
static std::vector<std::string> string_split(std::string str,std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str+=pattern; //扩展字符串以方便操作
	int size=str.size();

	for ( int i=0; i<size; i++)
	{
		pos=str.find(pattern,i);
		if (pos<size)
		{
			std::string s=str.substr(i,pos-i);
			result.push_back(s);
			i=pos+pattern.size()-1;
		}
	}
	return result;
}
