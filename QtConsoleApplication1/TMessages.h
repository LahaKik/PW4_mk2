#pragma once

#include <qobject.h>

enum ClientMessage
{
	DETERMINANT_REQUEST = 4,
	TRANSPOSE_REQUEST = 6,
};

enum ServerMessage
{
	DETERMINANT_ANSWER = 5,
	TRANSPOSE_ANSWER = 7,

	ERROR_MESSAGE = 99
};

enum TypeNum
{
	RATIONAL,
	REAL,
	COMPLEX
};

static const QChar TMessageSeparator = ';';

QString& operator<< (QString&, const QString&);
QString& operator>> (QString&, int&);
QString& operator>> (QString&, double&);
QByteArray& operator>> (QByteArray&, int&);
QByteArray& operator>> (QByteArray&, double&);

QString& operator << (QString&,const double&);
