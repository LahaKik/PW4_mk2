#pragma once
#include <iostream>
#include <qstring.h>
#include <qbytearray.h>
#include "../QtConsoleApplication1/TMessages.h"


struct TComplex
{
private:
	static QChar separator;
public:
	double re, im;

	TComplex() : re(0), im(0) {}

	template<typename T>
	TComplex(T Re) : re(Re), im(0) {};

	template<typename T>
	TComplex(T Re, T Im) : re(Re), im(Im) {};

	template<typename T, typename P>
	TComplex(T Re, P Im) : re(Re), im(Im) {};

	TComplex(const QByteArray&);
	TComplex(const TComplex&);

	TComplex& operator= (const TComplex& right)
	{
		re = right.re;
		im = right.im;
		return *this;
	}

	TComplex& operator= (TComplex& right)
	{
		re = right.re;
		im = right.im;
		return *this;
	}

	TComplex operator-()
	{
		re = -re;
		im = -im;
		return *this;
	}

	template<typename T>
	TComplex& operator+= (const T& right)
	{
		re = re + right;
		return *this;
	}

	template<>
	TComplex& operator+= (const TComplex& right)
	{
		re = re + right.re;
		im = im + right.im;
		return *this;
	}

	template<typename T>
	TComplex operator+ (const T& right) const
	{
		re += right;
		return *this;
	}

	template<>
	TComplex operator+ (const TComplex& right) const
	{
		return TComplex(re + right.re, im + right.im);
	}

	template<typename T>
	TComplex& operator*= (const T& right)
	{
		re = re * right;
		im = im * right;
		return *this;
	}

	template<>
	TComplex& operator*= (const TComplex& right)
	{
		double RRe = right.re;
		double RIm = right.im;
		re = re * RRe - im * RIm;
		im = re * RIm + RRe * im;
		return *this;
	}

	template<typename T>
	TComplex operator* (const T& right) const
	{
		re *= right;
		im *= right;
		return *this;
	}

	template<>
	TComplex operator* (const TComplex& right) const
	{
		double RRe = right.re;
		double RIm = right.im;
		return TComplex(re * RRe - im * RIm, re * RIm + RRe * im);
	}

	TComplex operator/ (const TComplex& right) const
	{
		double NewRe = (re * right.re + im * right.im) / (right.re * right.re + +right.im * right.im);
		double NewIm = (im * right.re - re * right.im) / (right.re * right.re + +right.im * right.im);
		return TComplex(round(NewRe * 1000000000) / 1000000000, round(NewIm * 1000000000) / 1000000000);
	}

	template<typename T>
	bool operator!= (const T& right)
	{
		if (im == 0 && re == right)
			return false;
		return true;
	}

	template<>
	bool operator!= (const TComplex& right)
	{
		if (im == right.im && re == right.re)
			return false;
		return true;
	}

	friend std::ostream& operator<< (std::ostream& strm, TComplex&  num)
	{
		if (num.im != 0)
			if (num.im > 0)
				strm << num.re << "+" << num.im << "i";
			else
				strm << num.re << num.im << "i";
		else
			strm << num.re;
		return strm;
	}

	friend std::istream& operator>> (std::istream& strm, TComplex& num)
	{
		strm >> num.re;
		strm >> num.im;
		return strm;
	}

	friend QByteArray& operator>> (QByteArray&, TComplex&);
	friend QString& operator<< (QString&, TComplex&);
	QString ToQString();
};