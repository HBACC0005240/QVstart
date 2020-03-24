#ifndef GLDSTRUTILS_H
#define GLDSTRUTILS_H
#include "GlobalDef.h"

#if defined(WIN32) || defined(WIN64)
#include "wtypes.h"
#endif
#include <QString>
#include <QIODevice>
#if defined(WIN32) || defined(WIN64)
    extern  const QString sLineBreak;
#else
    extern  const QString sLineBreak;
#endif

/*
//获取C风格字符串（\0结尾的字符串）的长度
size_t CStrLength(const char *sz);
size_t CStrLength(const wchar_t *wsz);
size_t WideCStrLength(const wchar_t *wsz);
wchar_t *WideLowerCase(wchar_t **ppWsz);
//比较两个字符串，大小写敏感
bool SameStr(const char *szA, const char *szB);
bool WideSameStr(const wchar_t *wszA, const wchar_t *wszB);
//比较两个字符串，大小写不敏感
bool SameText(const char *szA, const char *szB);
bool WideSameText(const wchar_t *wszA, const wchar_t *wszB);

wchar_t *charToWchar(const char *str);
char *wcharToChar(const wchar_t *pwstr);
*/
 QString utf8ToUnicode(const char *in, int length = -1);

// 分段进行utf8 到 local8bit 的转换
// QIODevice *utf8ToUnicode(QIODevice *inStream);
// 分段读出utf8流中的字符串，可一次全部读出
 QString utf8ToUnicodeString(QIODevice *inStream, int nLength  = -1);

// 分段进行unicode 到 utf8 的转换
// QIODevice *unicodeToUTF8BySegment(QIODevice *inStream, int length = -1);
// 分段进行GB2312 To UTF8
// QIODevice *gbkToUTF8BySegment(QIODevice *inStream, int length = -1);

 QByteArray unicodeToUTF8(const QChar *in, int length = -1);
inline QByteArray unicodeToUTF8(const QString &in) { return unicodeToUTF8(in.constData(), in.length()); }

 QString asciiToUnicode(const char *in, int length = -1, const char *name = NULL);
 QByteArray unicodeToAscii(const QChar *in, int length = -1, const char *name = NULL);
inline QByteArray unicodeToAscii(const QString &in, const char *name = NULL) { return unicodeToAscii(in.constData(), in.length(), name); }

 QString gbkToUnicode(const char *in, int length = -1);
 QByteArray unicodeToGBK(const QChar *in, int length = -1);
inline QByteArray unicodeToGBK(const QString &in) { return unicodeToGBK(in.constData(), in.length()); }

 QString ansiUpperCase(const QString &value);
 QString ansiLowerCase(const QString &value);

 QString upperCase(const QString &value);
 QString lowerCase(const QString &value);

 char upperCase(const char ch);
 char lowerCase(const char ch);

 wchar_t upperCase(const wchar_t ch);
 wchar_t lowerCase(const wchar_t ch);

 int compareStr(const QStringRef &s1, const QStringRef &s2);
 int compareStr(const QStringRef &s1, const QString &s2);
 int compareStr(const QString &s1, const QString &s2);
 int compareStr(const QByteArray &s1, const QByteArray &s2);

 int compareText(const QStringRef &s1, const QStringRef &s2);
 int compareText(const QStringRef &s1, const QString &s2);
 int compareText(const QString &s1, const QString &s2);
 int compareText(const QByteArray &s1, const QByteArray &s2);

int compareQVariant(const QVariant &v1, const QVariant &v2);
 bool sameQVariant(const QVariant &v1, const QVariant &v2);

 bool sameStr(const QString &s1, const QString &s2);
// 不区分大小写
inline bool sameText(const QString &s1, const QString &s2)
{
    return 0 == s1.compare(s2, Qt::CaseInsensitive);
}
// 不区分大小写
inline bool sameText(const QString &s1, const QLatin1String &s2)
{
    return 0 == s1.compare(s2, Qt::CaseInsensitive);
}

// 不区分大小写
inline bool sameText(const QStringRef &s1, const QLatin1String &s2)
{
    return 0 == s1.compare(s2, Qt::CaseInsensitive);
}

 int length(const QString &s);
 int pos(const QString &subs, const QString &s);
 int pos(const QChar &subs, const QString &s);
 int pos(const QString &subs, const QString &s, int nFrom);
 int rPos(const QString &subs, const QString &s, int times = 1);
 int rPos(const QChar &subs, const QString &s, int times = 1);
 int rPosEx(const QChar &subs, const QString &s, int offset);
 QString trim(const QString &s);
 QString trimRight(const QString &s);
 QString trimLeft(const QString &s);
 QString copy(const QString &s, int position, int n = -1);
 QString copyForDelphi(const QString &s, int position, int n = MaxInt);
 QString stringReplace(const QString &s, const QString &before, const QString &after);
 bool containsText(const QString &text, const QString subText);
 QString leftStr(const QString &text, int count);
 QString rightStr(const QString &text, int count);
 QStringList split(const QString &s, QChar sep);
 QStringList split(const QString &s, const QString &sep);

 bool isInt(const QString &s);
 bool isInt64(const QString &s);
 bool isUInt64(const QString &s);
 bool isNumeric(const QString &s);
 bool isDateTime(const QString &s);

 bool charIsDigit(const QChar &ch);

 bool variantTypeIsByte(const QVariant::Type type);
 bool variantTypeIsShort(const QVariant::Type type);
 bool variantTypeIsInt(const QVariant::Type type);
inline bool variantTypeIsInt64(const QVariant::Type type)
{ return (type == QVariant::LongLong || type == QVariant::ULongLong); }
 bool variantTypeIsDigit(const QVariant::Type type);
 bool variantTypeIsFloat(const QVariant::Type type);
 bool variantTypeIsNumeric(const QVariant::Type type);
 bool variantTypeIsDateTime(const QVariant::Type type);
 bool variantTypeIsUnsigned(const QVariant::Type type);

#ifdef WIN32
 QString BSTRToQString(const BSTR & s);
 BSTR QStringToBSTR(const QString & s);
 void freeBSTR(BSTR & s);
#endif

 QString format(const QString &s, const QVariantList &a);
 QString format(const QString &s, const QString &a, const QString &before = QString("%s"));
 QString format(const QString &s, int a);
 QString format(const QString &s, long a);
 QString format(const QString &s, long long a);
 QString format(const QString &s, double a);
 QString format(const QString &s, const QChar &a, const QString &before = QString("%s"));
//QString format(const QString &s, const QVariant &a);

 QString boolToStr(bool a, bool useBoolStrs = false);
 bool strToBool(const QString &s);
 bool strToBoolDef(const QString &s, bool def = false);
 QString intToStr(int a);
 QString int64ToStr(qint64 a);
 QString uint64ToStr(quint64 a);
 int strToInt(const QString &s);
 int strToIntDef(const QString &s, int def);
 qint64 strToInt64(const QString &s, int base = 10);
 qint64 strToInt64Def(const QString &s, qint64 def);
 quint64 strToUInt64(const QString &s);
 quint64 strToUInt64Def(const QString &s, quint64 def);
 QString floatToStr(double a);
 double strToFloat(const QString &s);
 double strToFloatDef(const QString &s, double def);
 QString dateTimeToStr(const QDateTime &datetime, QString format = "yyyy-MM-dd hh:mm:ss");
 QDateTime strToDateTime(const QString &s, QString format = "yyyy-M-d hh:mm:ss");
 QString byteArrayToStr(const QByteArray &a);
 QByteArray strToByteArray(const QString &s);
 QString intToHex(int value, int digits);

 QString stuffString(const QString &text, int nStart, int nLength, const QString &subText);
 int occurs(const char delimiter, const QString &srcStr);



 QString quotedStr(const QString &str, const char quote = '\'');
 QByteArray quotedStr(const QByteArray &str, const char quote);

 QString dequotedStr(const QString &str, const char quote);
 QByteArray dequotedStr(const QByteArray &str, const char quote);

 QString extractQuotedStr(QString &str, const char quote);

 QIODevice* stringToStream(const QString &in);
 QString streamToString(QIODevice* in);

 QIODevice* byteArrayToStream(const QByteArray &in);
 QByteArray streamToByteArray(QIODevice* in);

 QDate intToDate(int d);
 int dateToInt(const QDate &date);

 QTime doubleToTime(double t);
 double timeToDouble(const QTime &time);

 QDateTime doubleToDateTime(double d);
 double dateTimeToDouble(const QDateTime &dateTime);

 QString intToColorHex(int value, int length = 6);
 QString variantToString(const QVariant &value);

 int yearOf(double d);
 int monthOf(double d);
 int weekOf(double d);
 int dayOf(double d);
 int hourOf(double d);
 int minuteOf(double d);
 int secondOf(double d);
 int milliSecondOf(double d);

struct GFormatSettings
{
    byte currencyFormat;
    byte negCurrFormat;
    char thousandSeparator;
    char decimalSeparator;
    byte currencyDecimals;
    char dateSeparator;
    char timeSeparator;
    char listSeparator;
    QString currencyString;
    QString shortDateFormat;
    QString lonQDateFormat;
    QString timeAMString;
    QString timePMString;
    QString shortTimeFormat;
    QString lonQTimeFormat;
    QString shortMonthNames[12];
    QString longMonthNames[12];
    QString shortDayNames[7];
    QString longDayNames[7];
    int twoDigitYearCenturyWindow;
};

 double chsStrToDateTime(const QString &s);
 QString dateTimeToChsStr(double dateTime);
 bool isChsDateTime(const QString &s);
 bool tryStrToDateTime(const QString &s, QDateTime &value);
 bool tryStrToDateTime(const QString &s, QDateTime &value,
                 const GFormatSettings &formatSettings);

 bool sameDateTime(double dateTime1, double dateTime2);
 int compareDateTime(double dateTime1, double dateTime2);

 QString getHZPY(const QString &src);
 QString firstLetter(int nCode);
 QString reverseString(const QString &s);
 QString regExprReplace(const QString &text, const QString &regEx, const QString &replacement);

 QString getSubString(const QString &srcStr, char delimiter, int index);
 QString getSubString(const QString &srcStr, const QString &delimiter, int index);

 int posN(const char delimiter, const QString srcStr, int times = 1);
 int posN(const QString subStr, const QString srcStr, int times = 1);

 QString stringOfChar(char Char, int count);


 QString boolToXMLString(bool v);
 bool xmlStringToBool(const QString &s);
 QString floatToXMLString(double v);
 QString encodeXMLString(const QString &value, bool encodeCrLf);

/**
  GUID 相关处理函数
*/
 QString createGuidString();
 GUID createGUID();
 QString GUIDToStr(const GUID &a);
 GUID strToGUID(const QString &text);
 QVariant GUIDToVariant(const GUID &a);
 GUID variantToGUID(const QVariant &text);
 QByteArray GUIDToByteArray(const GUID value);
 GUID byteArrayToGUID(const QByteArray &ba);
 int compareGUID(const GUID &g1, const GUID &g2);
 bool isGUID(const QString &s);
 bool variantTypeIsGUID(const QVariant::Type type);
 QUuid GUIDToGUuid(const GUID &value);
 GUID GUuidToGUID(const QUuid &value);

template <typename Set, typename T>
inline void include(Set &set, const T t)
{
    set |= (byte(1) << byte(t));
}

template <typename Set, typename T>
inline void exclude(Set &set, const T t)
{
    set &= ~(byte(1) << byte(t));
}

template <typename Set, typename T>
inline bool contains(const Set &set, const T t)
{
    return set & (byte(1) << byte(t));
}

//type:0(), 1(], 2[), 3[]
template <typename T>
Q_DECL_CONSTEXPR inline bool isInInterval( const T &val, const T &min, const T &max, int type = 3)
{
    return ((1 == (type & 1)) ? (val <= max) : (val < max))
            && ((2 == (type & 2)) ? (val >= min) : (val > min));
}

 LONGLONG getStartTime();
 double getLastTime(LONGLONG startTime);

#endif // GLDSTRUTILS_H

