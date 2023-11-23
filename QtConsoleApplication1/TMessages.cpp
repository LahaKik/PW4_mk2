#include "TMessages.h"

QString& operator<< (QString& left, const QString& right)
{
	left += right;
	left.append(TMessageSeparator);
	return left;
}

QString& operator>> (QString& str, int& num)
{
	int IndSep = str.indexOf(TMessageSeparator);
	if (IndSep > 0)
	{
		num = str.left(IndSep).toInt();
		str = str.right(str.length() - IndSep - 1);
	}
	return str;
}

QString& operator>> (QString& str, double& num)
{
	int IndSep = str.indexOf(TMessageSeparator);
	if (IndSep > 0)
	{
		num = str.left(IndSep).toDouble();
		str = str.right(str.length() - IndSep - 1);
	}
	return str;
}

QByteArray& operator>> (QByteArray& str, int& num)
{
	int IndSep = str.indexOf(TMessageSeparator.toLatin1());
	if (IndSep > 0)
	{
		num = str.left(IndSep).toInt();
		str = str.right(str.length() - IndSep - 1);
	}
	return str;
}

QByteArray& operator>> (QByteArray& arr, double& num)
{
	int IndSep = arr.indexOf(TMessageSeparator.toLatin1());
	if (IndSep > 0)
	{
		num = arr.left(IndSep).toDouble();
		arr = arr.right(arr.length() - IndSep - 1);
	}
	return arr;
}