#pragma once
#include <vector>
#include <iostream>
#include <qstring.h>
#include <qbytearray.h>
#include "../QtConsoleApplication1/TMessages.h"


class Rational
{
	using Uint = unsigned int;
private:
	static QChar separator;
	void MakeIrreducible();
public:
	int upNum;
	int downNum;

	Rational()
		: upNum(1), downNum(1)
	{
	}
	Rational(int upNum, int downNum)
		: upNum(upNum), downNum(downNum)
	{
		MakeIrreducible();
	}
	Rational(int upNum)
		: upNum(upNum), downNum(1)
	{
	}

	Rational(const QByteArray&);

	Rational& operator= (const Rational& right)
	{
		upNum = right.upNum;
		downNum = right.downNum;
		return *this;
	}

	Rational operator-()
	{
		upNum = -upNum;
		return *this;
	}

	template<typename T>
	Rational& operator+= (const T& right)
	{
		upNum += right * downNum;
		return *this;
	}

	template<>
	Rational& operator+= (const Rational& right)
	{
		upNum = upNum * right.downNum + right.upNum * downNum;
		downNum *= right.downNum;
		MakeIrreducible();
		return *this;
	}

	template<typename T>
	Rational operator+ (const T& right) const
	{
		*this += right;
		return *this;
	}

	template<>
	Rational operator+ (const Rational& right) const
	{
		Rational temp(upNum, downNum);
		temp += right;
		return temp;
	}

	template<typename T>
	Rational& operator*= (const T& right)
	{
		upNum *= right;
		MakeIrreducible();
		return *this;
	}

	template<>
	Rational& operator*= (const Rational& right)
	{
		upNum *= right.upNum;
		downNum *= right.downNum;
		MakeIrreducible();
		return *this;
	}

	template<typename T>
	Rational operator* (const T& right)
	{
		*this *= right;
		return *this;
	}

	template<>
	Rational operator* (const Rational& right)
	{
		Rational tmp(*this);
		tmp *= right;
		return tmp;
	}

	template<typename T>
	Rational operator/ (const T& right) const
	{
		Rational tmp;
		if (right > 0)
			tmp = Rational(1, right);
		else if (right < 0)
			tmp = Rational(-1, -right);
		else
			return Rational(0, 0);
		Rational sec;
		sec *= tmp;
		return sec;

	}
	template<>
	Rational operator/ (const Rational& right) const
	{
		Rational fst(right);
		Rational sec(*this);
		sec *= fst.Invert();
		return sec;
	}

	template<typename T>
	bool operator!= (const T& right)
	{
		if (downNum == 1 && upNum == right)
			return false;
		return true;
	}

	template<>
	bool operator!= (const Rational& right)
	{
		if (downNum == right.downNum && upNum == right.upNum)
			return false;
		return true;
	}

	friend std::ostream& operator<< (std::ostream& strm, Rational& const num)
	{
		strm << num.upNum << "/" << num.downNum;
		return strm;
	}

	friend std::istream& operator>> (std::istream& strm, Rational& const num)
	{
		strm >> num.upNum;
		strm >> num.downNum;
		return strm;
	}

	Rational Invert()
	{
		if (upNum >= 0)
		{
			Uint temp = upNum;
			upNum = downNum;
			downNum = temp;
			return *this;
		}
		else
		{
			Uint temp = -upNum;
			upNum = -downNum;
			downNum = temp;
			return *this;
		}
	}

	friend QByteArray& operator>> (QByteArray&, Rational&);
	friend QString& operator<< (QString&, Rational&);

	double decimal() { return (double)upNum / downNum; }
};

