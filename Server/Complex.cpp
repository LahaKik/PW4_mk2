#include "Complex.h"

TComplex::TComplex(const QByteArray& arr)
{
	int IndSep = arr.indexOf(separator.toLatin1());
	re = arr.left(IndSep).toInt();
	im = arr.right(arr.length() - IndSep - 1).toInt();
}

TComplex::TComplex(const TComplex& right)
{
	re = right.re;
	im = right.im;
}

QChar TComplex::separator = TMessageSeparator;

QByteArray& operator>> (QByteArray& arr, TComplex& num)
{
	int IndSep = arr.indexOf(TComplex::separator.toLatin1());
	IndSep = arr.indexOf(TComplex::separator.toLatin1(), IndSep + 1);
	if (IndSep > 0)
	{
		num = TComplex(arr.left(IndSep));
		arr = arr.right(arr.length() - IndSep - 1);
	}
	return arr;
}

QString& operator<< (QString& str, TComplex& num)
{
	str.append(QString().setNum(num.re));
	str.append(TMessageSeparator);
	str.append(QString().setNum(num.im));
	str.append(TMessageSeparator);
	return str;
}

QString TComplex::ToQString()
{
	QString str;
	str.append(QString().setNum(re));
	str.append(TMessageSeparator);
	str.append(QString().setNum(im));
	str.append(TMessageSeparator);
	return str;
}