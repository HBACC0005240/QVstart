/*!
 字符串帮助类
*/

#pragma once
#include <QString>
#include <QRect>
#include <QFont>


class ITStringHelper
{
public:
	// 将宽字符串转换为QString类型
	static QString WcharArrayToQString(const wchar_t*  WcharArray);

	// 将QString类型转换为宽字符串
	static const wchar_t* QStringToWcharArray(const QString& AQString);

	// 计算给定显示宽度下的字符串包围盒
	static QRect GetStrBoundingRect(const QString& str, const QFont& font, int width);

	// 将数字转换为字符串（不用科学计数法，保留所有有效位）
	static QString NumberToString(double num);

	// 检测当前字符串是否是有效日期时间
	static bool isDateTime(QString strDate, QString &desDate);
private:
	static bool isDate(QString strDate, QString strFormat, QString &desDate);

};