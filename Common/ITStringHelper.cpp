#include "stdafx.h"
#include "ITStringHelper.h"

QString ITStringHelper::WcharArrayToQString(const wchar_t*  AWcharArray)
{
	return QString::fromUtf16(reinterpret_cast<const ushort*>(AWcharArray));
}

const wchar_t* ITStringHelper::QStringToWcharArray(const QString& AQString)
{
	return reinterpret_cast<const wchar_t*>(AQString.utf16());
}

QRect ITStringHelper::GetStrBoundingRect(const QString& str, const QFont& font, int width)
{
	QFontMetrics metrics(font);
	return metrics.boundingRect(0, 0, width, 0, Qt::TextWordWrap, str);
}

QString ITStringHelper::NumberToString(double num)
{
	QString result = QString::number(num, 'f');
	
	int i = result.size() - 1;
	while (i >= 0)
	{
		if ('0' != result.at(i))
		{
			break;
		}
		--i;
	}

	if (i != result.size() - 1)
	{
		result.remove(i + 1, result.size() - 1 - i);
		if ('.' == result.at(result.size() - 1))
		{
			result.remove(result.size() - 1, 1);
		}
	}

	return result;
}

bool ITStringHelper::isDate(QString strDate, QString strFormat, QString &desDate)
{
	try
	{
		QDateTime local(QDateTime::currentDateTime());
		int cury = local.date().year();
		int curm = local.date().month();
		int curd = local.date().day();
		int y, m, d;
		sscanf_s(strDate.toStdString().c_str(), strFormat.toStdString().c_str(), &y, &m, &d);
		if (y > 0 && y <= cury && m > 0 && m <= curm && d > 0 && d <= curd)
		{
			desDate = QString("%1-%2-%3").arg(y).arg(m).arg(d);
			return true;
		}
		else
			return false;
	}
	catch (...)
	{
		return false;
	}
}
bool ITStringHelper::isDateTime(QString strDate, QString &desDate)
{
	strDate.trimmed();
	QString dateStr, timeStr;
	int spaceIndex = strDate.indexOf(" ");
	if (spaceIndex >= 9)
	{
		dateStr = strDate.left(spaceIndex);
		timeStr = strDate.mid(spaceIndex + 1);
	}
	else
	{
		dateStr = strDate;
	}
	bool result = false;
	if (false == dateStr.isEmpty())
	{
		bool d = isDate(dateStr, QString("%d.%d.%d"), desDate);
		bool a = isDate(dateStr, QString("%d/%d/%d"), desDate);
		bool b = isDate(dateStr, QString("%d-%d-%d"), desDate);
		bool c = isDate(dateStr, QStringLiteral("%dÄê%dÔÂ%d"), desDate);
		result = a || b || c || d;
	}
	if (result && false == timeStr.isEmpty())
	{
		int h, m, s;
		sscanf_s(timeStr.toStdString().c_str(), "%d:%d:%d", &h, &m, &s);
		if (h >= 0 && h < 23 &&
			m >= 0 && m < 60 &&
			s >= 0 && s < 60)
		{
			result = true;
			QString temp;
			temp.sprintf(" %02d:%02d:%02d", h, m, s);
			desDate.append(temp);
		}
		else

			result = false;
	}
	return result;
}
